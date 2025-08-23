// Copyright (C) 2025 OTOY NZ Ltd.

 

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)

#include "libjuce.h"

#include "grpccallbacks.h"
#include "pointermap.h"
#include "stringmgr.h"
#include "grpclog.h"
#include "modulereg.h"
#include "moduleserver.h"
#include "grpccallbacks.h"
//#include "grpcstreaming.h"
#include "callback.grpc.pb.h"

 

template<typename RequestType,
    typename ResponseType,
    typename BuildRequestFn,
    typename SyncCallFn,
    typename ProcessResponseFn>
    auto doSyncCallback(BuildRequestFn buildRequest,
        SyncCallFn syncCall,
        ProcessResponseFn processResponse)
    -> decltype(processResponse(std::declval<grpc::Status>(), std::declval<ResponseType>()))
{
    // The type we plan to return is deduced from processResponse(...)
    using ReturnT = decltype(processResponse(std::declval<grpc::Status>(), std::declval<ResponseType>()));

    // Promise/future approach returning ReturnT
    std::promise<ReturnT> donePromise;
    auto futureDone = donePromise.get_future();

    // Launch a thread for the blocking call
    std::thread t([&donePromise,
        buildRequest,  // captured by value
        syncCall,
        processResponse]() mutable
        {
            // Build request
            RequestType request;
            buildRequest(request);

            // Make the call
            ResponseType response;
            grpc::ClientContext ctx;
            grpc::Status st = syncCall(&ctx, request, &response);

            // Convert (status, response) to the final result
            ReturnT retVal = processResponse(st, response);

            // Publish to the promise
            donePromise.set_value(retVal);
        });

    // Pump the JUCE message loop until future is ready
    while (true)
    {
        auto statusWait = futureDone.wait_for(std::chrono::milliseconds(0));
        if (statusWait == std::future_status::ready)
        {
            break;
        }
        auto instance = juce::MessageManager::getInstance();
        if (instance->isThisTheMessageThread())
        {
            if (instance->runDispatchLoopUntil(50))
            {
                // If the user closed the app or something triggered a quit, you may exit
                // or decide how to handle it. We'll just continue in this example.
            }
        }
    }

    if (t.joinable())
    {
        t.join();
    }

    // Return the final result
    return futureDone.get();
}


GRPCCallbackMgr::GRPCCallbackMgr()
{
}


GRPCCallbackMgr::~GRPCCallbackMgr()
{
}


int GRPCCallbackMgr::getNextCallbackId(
    const std::string & methodName,
    const std::string & moduleId)
{
    std::lock_guard<std::mutex> lock(mMutex);

    auto & pool = mCallbackPools[methodName];

    if (pool.availableIds.empty())
    {
        for (int i = 1; i <= pool.maxSize; ++i)
        {
            if (pool.usedIds.find(i) == pool.usedIds.end())
            {
                pool.availableIds.push(i);
            }
        }
    }

    if (pool.availableIds.empty())
    {
        throw std::runtime_error("No available callback IDs for method: " + methodName);
    }

    int id = pool.availableIds.top();
    pool.availableIds.pop();
    pool.usedIds.insert(id);

    // Store combined key
    mCallbackIdToModuleId[{methodName, id}] = moduleId;

    return id;
}


void GRPCCallbackMgr::releaseCallbackId(
    const std::string & methodName,
    int                 callbackId)
{
    std::lock_guard<std::mutex> lock(mMutex);

    auto it = mCallbackPools.find(methodName);
    if (it == mCallbackPools.end())
    {
        throw std::runtime_error("Method name not found: " + methodName);
    }

    auto & pool = it->second;

    auto erased = pool.usedIds.erase(callbackId);
    if (erased == 0)
    {
        throw std::runtime_error("Callback ID not found in used IDs for method: " + methodName);
    }

    pool.availableIds.push(callbackId);

    // Remove module mapping
    mCallbackIdToModuleId.erase({methodName, callbackId});
}


void GRPCCallbackMgr::releaseCallbackIdsByModule(
    const std::string & moduleId)
{
    std::lock_guard<std::mutex> lock(mMutex);

    std::vector<std::pair<std::string, int>> callbacksToRelease;

    // First, collect all callbackId entries that belong to the target moduleId
    for (const auto & entry : mCallbackIdToModuleId)
    {
        const auto & key = entry.first; // pair<methodName, callbackId>
        const std::string & storedModuleId = entry.second;

        if (storedModuleId == moduleId)
        {
            callbacksToRelease.push_back(key);
        }
    }

    // Now release them from pools and remove their mapping
    for (const auto & key : callbacksToRelease)
    {
        const std::string & methodName = key.first;
        int callbackId = key.second;

        auto poolIt = mCallbackPools.find(methodName);
        if (poolIt != mCallbackPools.end())
        {
            auto & pool = poolIt->second;

            // Erase from used set if present
            size_t erased = pool.usedIds.erase(callbackId);
            if (erased > 0)
            {
                pool.availableIds.push(callbackId);
            }
        }

        // Remove from moduleId map
        mCallbackIdToModuleId.erase(key);
    }
}


std::string GRPCCallbackMgr::getModuleIdFromCallbackId(
    const std::string & methodName,
    int                 callbackId)
{
    std::lock_guard<std::mutex> lock(mMutex);

    auto it = mCallbackIdToModuleId.find({methodName, callbackId});
    if (it == mCallbackIdToModuleId.end())
    {
        return "";
        /*throw std::runtime_error("No moduleId found for callbackId: " 
            + std::to_string(callbackId) + " for method: " + methodName);*/
    }
    return it->second;
}


std::unique_ptr< octaneapi::CallbackHandler::Stub >& GRPCCallbackMgr::getStub(
    const std::string & uniqueId)
{
    std::lock_guard<std::mutex> lock(mMutex);

    // Try to find the stub
    auto it = mStubMap.find(uniqueId);
    if (it != mStubMap.end())
    {
        return it->second.stub;
    }

    // If not exist yet: create new channel and stub
    const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueId);
    if (!info)
    {
        throw std::invalid_argument("Cannot find module for uniqueId: " + uniqueId);
    }

    auto channel = grpc::CreateChannel("unix:" + info->socketUrl, grpc::InsecureChannelCredentials());
    auto stub = octaneapi::CallbackHandler::NewStub(channel);

    StubInfo stubInfo;
    stubInfo.channel = channel;
    stubInfo.stub = std::move(stub);

    // Save into map
    auto inserted = mStubMap.emplace(uniqueId, std::move(stubInfo));
    return inserted.first->second.stub;
}
class BlockingModalComponent : public juce::Component, private juce::Timer
{
public:
    BlockingModalComponent(std::future<bool>& fut, std::function<void(bool)> onDone)
        : future(fut), onDoneCallback(onDone)
    {
        setOpaque(true);
        setSize(400, 100);
        label.setText("Please wait while operation completes...", juce::dontSendNotification);
        label.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(label);

        startTimer(100); // Check every 100ms
    }

    void resized() override
    {
        label.setBounds(getLocalBounds().reduced(10));
    }

private:
    void timerCallback() override
    {
        if (future.valid() && future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            stopTimer();
            bool result = future.get();
            if (onDoneCallback)
                onDoneCallback(result);
            if (auto* modal = getTopLevelComponent())
                modal->exitModalState(0); // ends the modal loop
        }
    }

    std::future<bool>& future;
    std::function<void(bool)> onDoneCallback;
    juce::Label label;
};

bool GRPCCallbackMgr::performBlockingOperation(
    const std::string & uniqueModuleId)
{
    auto resultPromise = std::make_shared<std::promise<bool>>();
    std::future<bool> resultFuture = resultPromise->get_future();

    juce::MessageManager::callAsync([uniqueModuleId, resultPromise]() {

        // create secondary promise for the gRPC call
        auto rpcPromise = std::make_shared<std::promise<bool>>();
        std::future<bool> rpcFuture = rpcPromise->get_future();

        // Start gRPC in background thread
        std::thread([uniqueModuleId, rpcPromise]() {
            google::protobuf::Empty req;
            octaneapi::CallbackAck ack;
            grpc::ClientContext ctx;

            grpc::Status status = GRPCCallbackMgr::getInstance().getStub(uniqueModuleId)->PerformBlocking(&ctx, req, &ack);

            rpcPromise->set_value(!status.ok());
            }).detach();

            // Show modal dialog
            class BlockingDialog : public juce::Component, private juce::Timer
            {
            public:
                BlockingDialog(std::future<bool>& fut, std::function<void(bool)> doneCallback)
                    : future(fut), onFinished(std::move(doneCallback))
                {
                    setSize(400, 100);
                    label.setText("Please wait, operation is in progress...", juce::dontSendNotification);
                    label.setJustificationType(juce::Justification::centred);
                    addAndMakeVisible(label);
                    startTimer(100);
                }

                bool keyPressed(const juce::KeyPress& key) override
                {
                    if (key == juce::KeyPress::escapeKey)
                    {
                        return true;
                    }
                    return false;
                }

                void resized() override
                {
                    label.setBounds(getLocalBounds().reduced(10));
                }

            private:
                void timerCallback() override
                {
                    if (future.valid() && future.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready)
                    {
                        stopTimer();
                        bool result = future.get();
                        if (onFinished)
                            onFinished(result);

                        if (auto* top = getTopLevelComponent())
                            top->exitModalState(0);
                    }
                }

                std::future<bool>& future;
                std::function<void(bool)> onFinished;
                juce::Label label;
            };

            // Wrap the lambda in a copyable std::function
            auto dialogLambda = [resultPromise](bool res) {
                resultPromise->set_value(res); // safe to copy shared_ptr
            };

            auto* dlg = new juce::DialogWindow("Waiting", juce::Colours::darkgrey, false);
            auto* content = new BlockingDialog(rpcFuture, dialogLambda);
             
            dlg->setVisible(true);
            dlg->setContentOwned(content, true);
            dlg->centreWithSize(400, 100);
            dlg->setAlwaysOnTop(true);
            dlg->setUsingNativeTitleBar(true);
            dlg->setTitleBarButtonsRequired(0, 0); 
            dlg->runModalLoop();
            delete dlg;
        });

    // Back on original (likely gRPC or background) thread:
    // Wait for UI thread to finish dialog and pass back result
    return resultFuture.get();
}


Octane::ApiNode * GRPCCallbackMgr::LoadRenderStateProject(
    int            callbackId,
    const char *   customProjectFileName,
    float          customProjectTime,
    unsigned int   customVersion,
    const void *   customData,
    unsigned int   customDataSize,
    void *         privateCallbackData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr : LoadRenderStateProject");
 
    Octane::ApiNode * resultPtr = doSyncCallback<
        octaneapi::LoadRenderStateProjectRequest,
        octaneapi::LoadRenderStateProjectResponse 
    >(
        [callbackId,
        customProjectFileName,
        customProjectTime,
        customVersion,
        customData,
        customDataSize,
        privateCallbackData](octaneapi::LoadRenderStateProjectRequest& request)
        {
            request.set_callback_id(callbackId);
            if (customProjectFileName)
            {
                request.set_customprojectfilename(customProjectFileName);
            }
            request.set_customprojecttime(customProjectTime);
            request.set_customversion(static_cast<uint64_t>(customVersion));

            if (customData && customDataSize > 0)
            {
                request.set_custom_data(
                    reinterpret_cast<const char*>(customData),
                    customDataSize
                );
            }

            request.set_user_data(reinterpret_cast<uint64_t>(privateCallbackData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::LoadRenderStateProjectRequest& req,
                octaneapi::LoadRenderStateProjectResponse* resp)
        {
            // Perform the synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCLoadRenderStateProject", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->LoadRenderStateProject(ctx, req, resp);
        },

        [&status](grpc::Status st, const octaneapi::LoadRenderStateProjectResponse& resp) -> Octane::ApiNode*
        {
            status = st;
            if (!st.ok())
            {
                // If there's an error, return null
                return nullptr;
            }
            
            // The response includes "moduleNodeGraph" (an ObjectRef).
            // We retrieve the handle, look it up in ObjectReferenceManager.
            // If your code references "ApiNode" or "ApiModuleNodeGraph," adjust as needed.
            const auto & ref = resp.modulenodegraph();
            if (!ref.handle())
            {
                // If there's no handle, return null
                return nullptr;
            }

            uint64_t handle = ref.handle();
            // Convert handle to a pointer using your manager
            auto & objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();
            // Suppose we expect an Octane::ApiNode*
            Octane::ApiNode * nodePtr =
                objMgr.getPointer<Octane::ApiNode>(handle);

            return nodePtr; // On success, that is
        }
        );

    // Return the pointer from doSyncCallback.
    // Null if call failed or if moduleNodeGraph wasn't present.
    return resultPtr;
}


void GRPCCallbackMgr::OnDaemonUpdate(
    int                                                    callbackId,
    const Octane::ApiArray<const Octane::NetDaemonInfo*>&  daemonInfoArray,
    void*                                                  user,
    grpc::Status &                                         status)
{
    GRPCLOG("GRPCCallbackMgr::OnDaemonUpdate");

    doSyncCallback<
        octaneapi::DaemonUpdateRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, &daemonInfoArray, user](octaneapi::DaemonUpdateRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(user));

            // Populate the repeated NetDaemonInfo array
            for (size_t i = 0; i < daemonInfoArray.mSize; ++i)
            {
                const Octane::NetDaemonInfo* src = daemonInfoArray.mData[i];
                if (!src)
                {
                    continue;
                }

                // Add a new NetDaemonInfo to the repeated field
                octaneapi::NetDaemonInfo* dst = request.add_daemoninfoarray();

                // Copy base fields
                dst->set_ipaddress(static_cast<uint32_t>(src->mIpAddress));
                dst->set_name(src->mName ? src->mName : "");
                dst->set_state(static_cast<octaneapi::NetDaemonState>(src->mState));
                dst->set_gpucount(src->mGpuCount);
                dst->set_slaveversion(src->mSlaveVersion);
                dst->set_boundmastername(src->mBoundMasterName ? src->mBoundMasterName : "");

                // Now populate the boundMasterAddress, which is a SocketAddress in the proto.
                octaneapi::SocketAddress * boundAddr = dst->mutable_boundmasteraddress();
                // We'll assume mBoundMasterAddress is something like:
                //   struct SocketAddress { IPv4T mIpAddress; uint16_t mPort; };
                // or similar. Convert it to the proto's two fields:
                boundAddr->set_ipaddress(static_cast<uint32_t>(src->mBoundMasterAddress.mIpAddress));
                boundAddr->set_port(static_cast<uint32_t>(src->mBoundMasterAddress.mPort));
            }
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::DaemonUpdateRequest & request,
                octaneapi::CallbackAck* response)
        {
            // Make the synchronous OnDaemonUpdate call
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnDaemonUpdate", request.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnDaemonUpdate(ctx, request, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& ack) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // success
            return true;
        }
        );

    // The function returns void. doSyncCallback blocks until the call finishes,
    // so by the time we reach here, OnDaemonUpdate() is complete on the server side.
}


void GRPCCallbackMgr::OnStatusUpdate(
    int                             callbackId,
    const Octane::NetRenderStatus & netStatus,
    void *                          userData,
    grpc::Status &                  status)
{
    GRPCLOG("GRPCCallbackMgr::OnStatusUpdate");

    doSyncCallback<
        octaneapi::StatusUpdateRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, &netStatus, userData](octaneapi::StatusUpdateRequest & request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            octaneapi::NetRenderStatus * protoStatus = new octaneapi::NetRenderStatus();

            protoStatus->set_netslavecount(
                static_cast<uint32_t>(netStatus.mNetSlaveCount)
            );
            protoStatus->set_updatingnetslavecount(
                static_cast<uint32_t>(netStatus.mUpdatingNetSlaveCount)
            );
            protoStatus->set_updatednetslavecount(
                static_cast<uint32_t>(netStatus.mUpdatedNetSlaveCount)
            );
            protoStatus->set_pendingsize(
                static_cast<uint64_t>(netStatus.mPendingSize)
            );
            protoStatus->set_totalsize(
                static_cast<uint64_t>(netStatus.mTotalSize)
            );
            protoStatus->set_netgpucount(
                static_cast<uint32_t>(netStatus.mNetGpuCount)
            );
            protoStatus->set_inusenetgpucount(
                static_cast<uint32_t>(netStatus.mInUseNetGpuCount)
            );

            request.set_allocated_status(protoStatus);
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::StatusUpdateRequest & req,
                octaneapi::CallbackAck* resp)
        {
            // Perform the synchronous RPC
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnStatusUpdate", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnStatusUpdate(ctx, req, resp);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck & ack) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;
            return true;
        }
    );
}


void GRPCCallbackMgr::OnTriggerFunc(
    int            callbackId,
    void *         userData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr::OnTriggerFunc");

    doSyncCallback<
        octaneapi::TriggerFuncRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::TriggerFuncRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
        [this](
            grpc::ClientContext *              ctx,
            const octaneapi::TriggerFuncRequest & req,
            octaneapi::CallbackAck *              response)
        {
            // Perform the synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("TriggerFunc", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                  return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->TriggerFunc(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; 
            return true;
        }
    );
}


void GRPCCallbackMgr::OnEvaluateFunc(
    int            callbackId,
    void *         userData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr::OnEvaluateFunc");

    // Switch from async to doSyncCallback
    doSyncCallback<
        octaneapi::EvaluateFuncRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::EvaluateFuncRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::EvaluateFuncRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnEvaluateFunc", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                  return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->EvaluateFunc(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;
            return true;
        }
    );
}


void GRPCCallbackMgr::CleanupFunc(
    int            callbackId,
    void *         userData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr::CleanupFunc");

    // Switch from async to doSyncCallback
    doSyncCallback<
        octaneapi::CleanupFuncRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::CleanupFuncRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::CleanupFuncRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Blocking gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("CleanupFunc", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                  return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->CleanupFunc(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;
            return true;
        }
        );
}


void GRPCCallbackMgr::DestroyFunc(
    int            callbackId,
    void *         userData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr::DestroyFunc");

    // Switch from async approach to doSyncCallback
    doSyncCallback<
    octaneapi::DestroyFuncRequest,
    octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::DestroyFuncRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::DestroyFuncRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Blocking gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("DestroyFunc", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                  return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->DestroyFunc(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::ColorChanged(
    int                      callbackId,
    Octane::ApiColorSwatch & colorSwatch,
    void *                   userData,
    grpc::Status &           status)
{
    GRPCLOG("GRPCCallbackMgr::ColorChanged");

// Convert from async to doSyncCallback
doSyncCallback<
    octaneapi::ColorChangedRequest,  // The request type from your .proto
    octaneapi::CallbackAck           // If no special data is returned
>(
    // 1) BuildRequestFn
    [callbackId, &colorSwatch, userData](octaneapi::ColorChangedRequest& request)
    {
        auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

        // Convert the colorSwatch into an ObjectRef
        uint64_t colorSwatchHandle = objMgr.addPointer(&colorSwatch);
        auto* colorSwatchPtr       = new octaneapi::ObjectRef();
        colorSwatchPtr->set_handle(colorSwatchHandle);
        colorSwatchPtr->set_type(
            octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiColorSwatch
        );

        // Add to the request
        request.set_allocated_apicolorswatch(colorSwatchPtr);
        request.set_callback_id(callbackId);
        request.set_user_data(reinterpret_cast<uint64_t>(userData));
    },

    // 2) SyncCallFn: calls the synchronous version of ColorChanged
        [this](
            grpc::ClientContext* ctx,
            const octaneapi::ColorChangedRequest& req,
            octaneapi::CallbackAck* resp)
    {
        std::string uniqueModuleId = getModuleIdFromCallbackId("ColorChanged", req.callback_id());
        if (uniqueModuleId == "")
        {
            return grpc::Status::OK;
        }
        // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
        const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
        if (!info)
        {
                return grpc::Status::OK;
        }
        return getStub(uniqueModuleId)->ColorChanged(ctx, req, resp);
    },

        // 3) ProcessResponseFn: set the grpc::Status out-parameter
        [&status](grpc::Status st, const octaneapi::CallbackAck& /*unused*/) -> bool
    {
        if (!st.ok())
        {
            status = st;
            return false;
        }
        status = st; // OK
        return true;
    }
    );

}


void * GRPCCallbackMgr::CreateFunc(
    int                          callbackId,
    Octane::ApiModuleNodeGraph * moduleNodeGraph,
    grpc::Status &               status)
{
    GRPCLOG("GRPCCallbackMgr::CreateFunc");

    // We’ll return a void* to the newly created object (or nullptr on error).
    void * createdPtr = doSyncCallback<
        octaneapi::CreateFuncRequest,
        octaneapi::CreateFuncResponse>(
            // 1) BuildRequestFn: populate the request
            [callbackId, moduleNodeGraph](octaneapi::CreateFuncRequest& request)
            {
                auto & objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

                // Convert the moduleNodeGraph pointer into a handle
                uint64_t moduleNodeGraphHandle = objMgr.addPointer(moduleNodeGraph);

                // Build an ObjectRef
                auto * moduleNodeGraphPtr = new octaneapi::ObjectRef();
                moduleNodeGraphPtr->set_handle(moduleNodeGraphHandle);
                moduleNodeGraphPtr->set_type(
                    octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiModuleNodeGraph);

                // Attach it to the request
                request.set_allocated_modulenodegraph(moduleNodeGraphPtr);
                request.set_callback_id(callbackId);
            },

            // 2) SyncCallFn: perform the blocking gRPC call
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::CreateFuncRequest& req,
                    octaneapi::CreateFuncResponse* response)
            {
                // Synchronous version of CreateFunc
                std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCCreateFunc", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->CreateFunc(ctx, req, response);
            },

                // 3) ProcessResponseFn: figure out what to return
                [&status](grpc::Status st, const octaneapi::CreateFuncResponse& resp) -> void*
            {
                if (!st.ok())
                {
                    // On failure, record the error and return nullptr
                    status = st;
                    return nullptr;
                }

                status = st;

                return (void *)resp.user_data(); ;
            }
            );

    // Return the pointer. On success, it’s the newly created object; otherwise nullptr.
    return createdPtr;
}


void * GRPCCallbackMgr::InitFunc(
    int                     callbackId,
    Octane::ApiGridLayout * gridLayout,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::InitFunc");

    auto response = doSyncCallback<
        octaneapi::InitFuncRequest,
        octaneapi::InitFuncResponse>(
            // BuildRequestFn:
            [callbackId, gridLayout](octaneapi::InitFuncRequest& request)
            {
                OctaneGRPC::ObjectReferenceManager & objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

                octaneapi::ObjectRef * gridLayoutPtr = new octaneapi::ObjectRef();
                uint64_t gridLayoutHandle = objMgr.addPointer(gridLayout);
                Octane::ApiGridLayout * objectPtrtest = objMgr.getPointer<Octane::ApiGridLayout>(gridLayoutHandle);
                if(objectPtrtest != gridLayout)
                {
                    assert(false);
                }
                gridLayoutPtr->set_handle(gridLayoutHandle);
                gridLayoutPtr->set_type( octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGridLayout);
                request.set_allocated_apigridlayout(gridLayoutPtr);
                request.set_callback_id(callbackId);
            },
            // SyncCallFn:
            [this](
                grpc::ClientContext * ctx,
                const octaneapi::InitFuncRequest & req,
                octaneapi::InitFuncResponse * response)
            {
                std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCInitFunc", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->InitFunc(ctx, req, response);
            },
            // ProcessResponseFn -> produce the entire proto response
            [](grpc::Status st, const octaneapi::InitFuncResponse & resp) -> octaneapi::InitFuncResponse
            {
                if (!st.ok())
                {
                }
                return resp;
            });
    return (void *)response.user_data();
}


void GRPCCallbackMgr::ApiChangeManagerChangeObserver(
    int                                           callbackId,
    const Octane::ApiChangeManager::ChangeEvent & changeEvent,
    void *                                        userData,
    grpc::Status &                                status)
{
    GRPCLOG("GRPCCallbackMgr::ApiChangeManagerChangeObserver");

    doSyncCallback<
        octaneapi::ChangeManagerObserverRequest,
        octaneapi::CallbackAck
    >(
    // 1) BuildRequestFn
    [callbackId, &changeEvent, userData](octaneapi::ChangeManagerObserverRequest& request)
    {
        auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

        // Set callbackId and userData
        request.set_callback_id(callbackId);
        request.set_user_data(reinterpret_cast<uint64_t>(userData));

        // Create a ChangeEvent to attach
        auto * eventData = new octaneapi::ChangeEvent();

        // changedItem
        auto * changedItemHandlePtr = new octaneapi::ObjectRef();
        uint64_t changedItemHandle = objMgr.addPointer(changeEvent.mChangedItem);
        changedItemHandlePtr->set_handle(changedItemHandle);
        changedItemHandlePtr->set_type(
            octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem
        );
        eventData->set_allocated_changeditem(changedItemHandlePtr);

        // changedOwner
        auto * changedOwnerHandlePtr = new octaneapi::ObjectRef();
        uint64_t changedOwnerHandle = objMgr.addPointer(changeEvent.mChangedOwner);
        changedOwnerHandlePtr->set_handle(changedOwnerHandle);
        changedOwnerHandlePtr->set_type(
            octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem
        );
        eventData->set_allocated_changedowner(changedOwnerHandlePtr);

        for (int h = 0; h < changeEvent.mChangedIndicesSize; ++h)
        {
            eventData->add_changedindices(changeEvent.mChangedIndices[h]);
        }

        // other fields
        eventData->set_changedownerpinix(changeEvent.mChangedOwnerPinIx);
        eventData->set_changedpinix(changeEvent.mChangedPinIx);
        eventData->set_type(
            static_cast<octaneapi::ChangeEvent_Type>(changeEvent.mType)
        );

        // Attach eventData to request
        request.set_allocated_eventdata(eventData);
    },

    // 2) SyncCallFn
        [this](
            grpc::ClientContext* ctx,
            const octaneapi::ChangeManagerObserverRequest& req,
            octaneapi::CallbackAck* resp)
    {
        // Perform the synchronous gRPC call
        std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCChangeObserver", req.callback_id());
        if (uniqueModuleId == "")
        {
            return grpc::Status::OK;
        }
        // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
        const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
        if (!info)
        {
            return grpc::Status::OK;
        }
        return getStub(uniqueModuleId)->ChangeManagerObserver(ctx, req, resp);
    },

        // 3) ProcessResponseFn
        [&status](grpc::Status st, const octaneapi::CallbackAck& unusedResp) -> bool
    {
        if (!st.ok())
        {
            status = st;
            return false;
        }
        //unusedResp.success();
        status = st;  // OK
        return true;
    }
    );

}


void GRPCCallbackMgr::ApiChangeManagerChangeTimeObserver(
    int                                         callbackId,
    const Octane::ApiChangeManager::TimeEvent & timeChangeEvent,
    void *                                      userData,
    grpc::Status &                              status)
{
    GRPCLOG("GRPCCallbackMgr::ApiChangeManagerChangeTimeObserver");

    doSyncCallback<
        octaneapi::ChangeManagerTimeObserverRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, &timeChangeEvent, userData](octaneapi::ChangeManagerTimeObserverRequest& request)
        {
            auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

            // Set callbackId and userData
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            // Build the TimeChangeEvent
            auto * eventData = new octaneapi::TimeChangeEvent();

            // Create an ObjectRef for the root graph
            auto * rootGraphPtr = new octaneapi::ObjectRef();
            uint64_t rootGraphHandle = objMgr.addPointer(timeChangeEvent.mRootGraph);
            rootGraphPtr->set_handle(rootGraphHandle);
            rootGraphPtr->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiItem);

            // Attach this to eventData
            eventData->set_allocated_rootgraph(rootGraphPtr);

            // Finally, attach eventData to the request
            request.set_allocated_eventdata(eventData);
        },

        // 2) SyncCallFn
        [this](
            grpc::ClientContext *                            ctx,
            const octaneapi::ChangeManagerTimeObserverRequest & req,
            octaneapi::CallbackAck *                            resp)
        {
            // Perform the synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCChangeTimeObserver", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->ChangeManagerTimeObserver(ctx, req, resp);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*response*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;
            return true;
        }
        );
}


void GRPCCallbackMgr::ApiProjectManagerProjectManagerObserver(
    int             callbackId,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::ApiProjectManagerProjectManagerObserver");

    // Convert from async to sync using doSyncCallback
    doSyncCallback<
        octaneapi::ObserverRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::ObserverRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::ObserverRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Synchronous gRPC call instead of Async
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCProjectManagerObserver", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->ProjectManagerObserver(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;
            return true;
        }
        );
}


void GRPCCallbackMgr::ApiSelectionManagerSelectionManagerObserver(
    int              callbackId,
    void *           userData,
    grpc::Status &   status)
{
    GRPCLOG("GRPCCallbackMgr::ApiSelectionManagerSelectionManagerObserver");

    doSyncCallback<
        octaneapi::ObserverRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::ObserverRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::ObserverRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Make the blocking gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCSelectionManagerObserver", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->SelectionManagerObserver(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // OK
            return true;
        }
        );
}


bool GRPCCallbackMgr::CommandModuleRunFunc(
    int            callbackId,
    void *         userData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr::CommandModuleRunFunc");

    // Use doSyncCallback to block until the operation completes and return a bool
    bool result = doSyncCallback<
        octaneapi::CommandModuleRunFuncRequest,
        octaneapi::CallbackAck>
        (
            // 1) BuildRequestFn
            [callbackId, userData](octaneapi::CommandModuleRunFuncRequest& req)
            {
                req.set_callback_id(callbackId);
                req.set_user_data(reinterpret_cast<uint64_t>(userData));
            },

            // 2) SyncCallFn
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::CommandModuleRunFuncRequest& req,
                    octaneapi::CallbackAck* resp)
            {
                // Perform the synchronous call
                std::string uniqueModuleId = getModuleIdFromCallbackId("CommandModuleRunFunc", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->CommandModuleRunFunc(ctx, req, resp);
            },

                // 3) ProcessResponseFn -> return bool, set 'status'
                [&status](grpc::Status st, const octaneapi::CallbackAck& resp) -> bool
            {
                // If the call fails, set status and return false
                if (!st.ok())
                {
                    status = st;
                    return false;
                }

                // Mark status as OK. 
                // If your .proto response has a field indicating success/failure, 
                // you can check resp here. For now, assume success if st.ok():
                status = st;
                return resp.success();
            }
            );

    // Return the boolean result from doSyncCallback
    return result;
}


void GRPCCallbackMgr::ObserverCallback(
    int                            callbackId,
    void *                         userData,
    Octane::ApiLocalDB::UpdateType type,
    const char *                   path,
    grpc::Status &                 status)
{
    GRPCLOG("GRPCCallbackMgr::ObserverCallback");

    // Convert the async code to a synchronous doSyncCallback pattern
    doSyncCallback<
        octaneapi::ObserverCallbackRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData, type, path](octaneapi::ObserverCallbackRequest& request)
        {
            // Safely handle if path is null
            std::string safePath = path ? path : "";

            request.set_callback_id(callbackId);
            // "set_allocated_path" expects a std::string* that will be owned by the request
            request.set_allocated_path(new std::string(safePath));
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
            request.set_type(static_cast<int32_t>(type));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::ObserverCallbackRequest& req,
                octaneapi::CallbackAck* response)
        {
            std::string uniqueModuleId = getModuleIdFromCallbackId("ObserverCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->ObserverCallback(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::DbViewLoadedCallback(
    int                  callbackId,
    void *               userData,
    Octane::ItemDbOrigin origin,
    grpc::Status &       status)
{
    GRPCLOG("GRPCCallbackMgr::DbViewLoadedCallback");

    // Use doSyncCallback instead of async call
    doSyncCallback<
        octaneapi::DbViewLoadedRequest, // Adjust to your .proto request type
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData, origin](octaneapi::DbViewLoadedRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
            request.set_origin(static_cast<int32_t>(origin));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::DbViewLoadedRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("DbViewLoadedCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->DbViewLoaded(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::FinishCallback(
    int             callbackId,
    bool            success,
    const char *    errorMsg,
    const char *    sceneGuid,
    const char *    rootGuid,
    const char *    sceneName,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::FinishCallback");

    // Convert synchronous call into doSyncCallback for consistency
    doSyncCallback<
        octaneapi::FinishRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, success, errorMsg, sceneGuid, rootGuid, sceneName, userData]
    (octaneapi::FinishRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
            request.set_success(success);

            // Use empty string if a pointer is null
            request.set_error_msg(errorMsg ? errorMsg : "");
            request.set_scene_guid(sceneGuid ? sceneGuid : "");
            request.set_root_guid(rootGuid ? rootGuid : "");
            request.set_scene_name(sceneName ? sceneName : "");
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::FinishRequest& req,
                octaneapi::CallbackAck* response)
        {
            std::string uniqueModuleId = getModuleIdFromCallbackId("FinishCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->Finish(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::OnTileBlendedCallback(
    int                callbackId,
    void *             userData,
    grpc::Status &     status)
{
    GRPCLOG("GRPCCallbackMgr::OnTileBlendedCallback");

    // Convert from async to sync pattern
    doSyncCallback<
        octaneapi::BasicCallbackRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::BasicCallbackRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::BasicCallbackRequest& request,
                octaneapi::CallbackAck* response)
        {
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnTileBlendedCallback", request.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnTileBlended(ctx, request, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // OK
            return true;
        }
        );

    // The function is void; 'status' indicates success/failure.
}


void GRPCCallbackMgr::OnNewStatisticsCallback(
    int                callbackId,
    void *             userData,
    grpc::Status &     status)
{
    GRPCLOG("GRPCCallbackMgr::OnNewStatisticsCallback");

    // Use doSyncCallback instead of an async call
    doSyncCallback<
        octaneapi::BasicCallbackRequest, // Adjust if your .proto request name differs
        octaneapi::CallbackAck            // No meaningful return data
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::BasicCallbackRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::BasicCallbackRequest& req,
                octaneapi::CallbackAck* response)
        {
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnNewStatisticsCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnNewStatistics(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // success
            return true;
        }
        );

}


void GRPCCallbackMgr::OnNewImageCallback(
    int                                              callbackId,
    const Octane::ApiArray<Octane::ApiRenderImage> & renderImages,
    void *                                           userData,
    grpc::Status &                                   status)
{
    GRPCLOG("GRPCCallbackMgr::OnNewImageCallback");

    octaneapi::OnNewImageRequest request;
    octaneapi::CallbackAck response;
    grpc::ClientContext context;

    request.set_callback_id(callbackId);
    request.set_user_data(reinterpret_cast<uint64_t>(userData));

    //auto* apiImages = new octaneapi::ApiArrayApiRenderImage();
    auto * apiImages = request.mutable_render_images();
    for (size_t i = 0; i < renderImages.mSize; ++i)
    {
        auto * newImage = apiImages->add_data();
        const auto & renderImage = renderImages.mData[i];
        newImage->set_type(static_cast<octaneapi::ImageType>(renderImage.mType));
        newImage->set_colorspace(static_cast<octaneapi::NamedColorSpace>(renderImage.mColorSpace));
        newImage->set_islinear(renderImage.mIsLinear);

        // Use mutable_ instead of set_allocated_
        auto* size = newImage->mutable_size();
        size->set_x(renderImage.mSize.x);
        size->set_y(renderImage.mSize.y); 
        newImage->set_pitch(renderImage.mPitch);

        if (renderImage.mBuffer)
        {
            auto* buffer = newImage->mutable_buffer();  // not set_allocated_*
            size_t imageBufferSize = 0;
            switch (renderImage.mType)
            {
            case Octane::IMAGE_TYPE_LDR_RGBA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 4;
                break;
            case Octane::IMAGE_TYPE_LDR_MONO_ALPHA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 2;
                break;
            case Octane::IMAGE_TYPE_HDR_RGBA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 4;
                break;
            case Octane::IMAGE_TYPE_HDR_MONO_ALPHA:
                imageBufferSize = renderImage.mSize.y * renderImage.mPitch * 2;
                break;
            default:
                assert(false);
            }
            if (renderImage.mBuffer && imageBufferSize > 0) {
                buffer->set_size(static_cast<uint32_t>(imageBufferSize));
                buffer->set_data(reinterpret_cast<const char*>(renderImage.mBuffer), imageBufferSize);
            }
            //newImage->set_allocated_buffer(buffer);
        }

        newImage->set_tonemappedsamplesperpixel(renderImage.mTonemappedSamplesPerPixel);
        newImage->set_calculatedsamplesperpixel(renderImage.mCalculatedSamplesPerPixel);
        newImage->set_regionsamplesperpixel(renderImage.mRegionSamplesPerPixel);
        newImage->set_maxsamplesperpixel(renderImage.mMaxSamplesPerPixel);
        newImage->set_samplespersecond(renderImage.mSamplesPerSecond);
        newImage->set_rendertime(renderImage.mRenderTime);

        auto * level = newImage->mutable_changelevel();
        level->set_value(renderImage.mChangeLevel);
   
        newImage->set_haspendingupdates(renderImage.mHasPendingUpdates);
        newImage->set_subsampling(static_cast<octaneapi::SubSampleMode>(renderImage.mSubSampling));
        newImage->set_hasalpha(renderImage.mHasAlpha);
        newImage->set_premultipliedalphatype(static_cast<octaneapi::PremultipliedAlphaType>(renderImage.mPremultipliedAlphaType));
        newImage->set_keepenvironment(renderImage.mKeepEnvironment);
    }
    //request.set_allocated_render_images(apiImages);

    if (mModuleServer)
    {
        status = mModuleServer->sendNewImageUpdates(request);
        return;
    }
    std::string uniqueModuleId = getModuleIdFromCallbackId("OnNewImageCallback", request.callback_id());
    if (uniqueModuleId == "")
    {
        status = grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "module not found");
        return;
    }
    // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
    const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
    if (!info)
    {
        return;
    }
    status = getStub(uniqueModuleId)->OnNewImage(&context, request, &response);
}


void GRPCCallbackMgr::OnOcioErrorCallback(
    int                                   callbackId,
    const Octane::ApiArray<const char*> & messages,
    bool                                  hasError,
    void *                                userData,
    grpc::Status &                        status)
{
    GRPCLOG("GRPCCallbackMgr::OnOcioErrorCallback");

    // Convert from a direct blocking call to doSyncCallback for consistency
    doSyncCallback<
        octaneapi::OnOcioErrorRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, &messages, hasError, userData](octaneapi::OnOcioErrorRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
            request.set_has_error(hasError);

            // Copy each message from ApiArray<const char*> to request
            for (size_t i = 0; i < messages.mSize; ++i)
            {
                request.add_messages(messages.mData[i] ? messages.mData[i] : "");
            }
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::OnOcioErrorRequest& req,
                octaneapi::CallbackAck* response)
        {
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnOcioErrorCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnOcioError(ctx, req, response);
        },

        // 3) ProcessResponseFn
        [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // OK
            return true;
        }
        );

}


void GRPCCallbackMgr::OnRenderFailureCallback(
    int                callbackId,
    void *             userData,
    grpc::Status &     status)
{
    GRPCLOG("GRPCCallbackMgr::OnRenderFailureCallback");

    // Convert from async to a synchronous call using doSyncCallback
    doSyncCallback<
        octaneapi::BasicCallbackRequest, 
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::BasicCallbackRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::BasicCallbackRequest& req,
                octaneapi::CallbackAck* response)
        {
            std::string uniqueModuleId = getModuleIdFromCallbackId("OnRenderFailureCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnRenderFailure(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // OK
            return true;
        }
        );
}


unsigned long long GRPCCallbackMgr::NextChunkCallback(
    int                callbackId,
    void *             userData,
    unsigned char*&    dataChunk,
    grpc::Status &     status)
{
    GRPCLOG("GRPCCallbackMgr::NextChunkCallback");

    unsigned long long chunkSize = doSyncCallback<
        octaneapi::NextChunkRequest,
        octaneapi::NextChunkResponse>(

            // 1) BuildRequestFn: populate the NextChunkRequest
            [callbackId, userData](octaneapi::NextChunkRequest& request)
            {
                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(userData));
            },

            // 2) SyncCallFn: run the blocking NextChunk call
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::NextChunkRequest& req,
                    octaneapi::NextChunkResponse* resp)
            {
                std::string uniqueModuleId = getModuleIdFromCallbackId("NextChunkCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->NextChunk(ctx, req, resp);
            },

                // 3) ProcessResponseFn: decide how to fill dataChunk and return size
                [&status, &dataChunk](grpc::Status st, const octaneapi::NextChunkResponse& resp)
                -> unsigned long long
            {
                // If the call failed, or chunk is empty, set dataChunk = nullptr, return 0
                if (!st.ok() || resp.chunk_size() == 0)
                {
                    status = st;
                    dataChunk = nullptr;
                    return 0ULL;
                }

                // Otherwise, allocate and copy chunk data
                uint64_t chunkSize = resp.chunk_size();
                dataChunk = new unsigned char[chunkSize];
                std::memcpy(dataChunk, resp.data_chunk().data(), chunkSize);

                // Set status to OK (or whatever 'st' was)
                status = st;
                return chunkSize;
            }
            );

    // Return the chunkSize. dataChunk was allocated if chunkSize > 0.
    return chunkSize;
}


void GRPCCallbackMgr::CheckedCallback(
    int                   callbackId,
    Octane::ApiCheckBox & button,
    void *                userData,
    grpc::Status &        status)
{
    GRPCLOG("GRPCCallbackMgr::CheckedCallback");

    // Convert the async logic into a synchronous doSyncCallback call
    doSyncCallback<
        octaneapi::CheckedRequest,   // Adjust if your .proto message name is different
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, &button, userData](octaneapi::CheckedRequest& request)
        {
            auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            // Create an ObjectRef for the button
            auto* btnPtr = new octaneapi::ObjectRef();
            uint64_t buttonHandle = objMgr.addPointer(&button);
            btnPtr->set_handle(buttonHandle);
            btnPtr->set_type(
                octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiCheckBox);

            request.set_allocated_button(btnPtr);
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::CheckedRequest& request,
                octaneapi::CallbackAck* response)
        {
            // Perform the synchronous gRPC method
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCCheckedCallback", request.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->Checked(ctx, request, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }

            status = st;  // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::ComboBoxChangedCallback(
    int                   callbackId,
    Octane::ApiComboBox & comboBox,
    void *                userData,
    grpc::Status &        status)
{
    GRPCLOG("GRPCCallbackMgr::ComboBoxChangedCallback");

    doSyncCallback<
        octaneapi::ComboBoxChangedRequest,  // Adjust to your actual .proto request type
        octaneapi::CallbackAck              // For callbacks that don't return complex data
    >(
        // 1) BuildRequestFn
        [callbackId, &comboBox, userData](octaneapi::ComboBoxChangedRequest& request)
        {
            auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            // Create ObjectRef for comboBox
            auto* comboBoxPtr = new octaneapi::ObjectRef();
            uint64_t comboBoxHandle = objMgr.addPointer(&comboBox);
            comboBoxPtr->set_handle(comboBoxHandle);
            comboBoxPtr->set_type(
                octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiComboBox);

            request.set_allocated_combo_box(comboBoxPtr);
        },

        // 2) SyncCallFn
        [this](
            grpc::ClientContext* ctx,
            const octaneapi::ComboBoxChangedRequest& req,
            octaneapi::CallbackAck* response)
        {
            // Perform the synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCComboBoxChangedCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->ComboBoxChanged(ctx, req, response);
        },

        // 3) ProcessResponseFn: Here we just update 'status'
        [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;  // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::ApiLogCallbackProc(
    int                                   callbackId,
    Octane::ApiLogManager::LogMessageType type,
    const char *                          message,
    grpc::Status &                        status)
{
    GRPCLOG("GRPCCallbackMgr::ApiLogCallbackProc");

    // Convert from async call to our doSyncCallback pattern
    doSyncCallback<
        octaneapi::ApiLogRequest,   // Adjust if your .proto has a different request type name
        octaneapi::CallbackAck      // If there's no meaningful payload in the response
    >(
        // 1) BuildRequestFn
        [callbackId, type, message](octaneapi::ApiLogRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_log_type(static_cast<int32_t>(type));
            request.set_message(message ? message : "");
        },

        // 2) SyncCallFn
            [this](

                grpc::ClientContext* ctx,
                const octaneapi::ApiLogRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Perform the synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("ApiLogCallbackProc", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->ApiLog(ctx, req, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st;
            return true;
        }
        );

    // The function is void. 'status' shows success or failure.
}


void GRPCCallbackMgr::OnMainWindowCloseCallback(
    int                 callbackId,
    void *              privateData,
    grpc::Status &      status)
{
    GRPCLOG("GRPCCallbackMgr::OnMainWindowCloseCallback");

    // Convert from async to sync version using doSyncCallback.
    doSyncCallback<
        octaneapi::BasicCallbackRequest,
        octaneapi::CallbackAck>(
            // 1) BuildRequestFn
            [callbackId, privateData](octaneapi::BasicCallbackRequest& request)
            {
                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(privateData));
            },

            // 2) SyncCallFn
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::BasicCallbackRequest& req,
                    octaneapi::CallbackAck* response)
            {
                // Perform the blocking gRPC call
                std::string uniqueModuleId = getModuleIdFromCallbackId("OnMainWindowCloseCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->OnMainWindowClose(ctx, req, response);
            },

                // 3) ProcessResponseFn
                [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
            {
                if (!st.ok())
                {
                    status = st;
                    return false;
                }
                status = st;
                return true;
            }
            );
}


void GRPCCallbackMgr::MouseEventCallback(
    int                                  callbackId,
    Octane::ApiMouseEventType            type,
    const Octane::ApiMouseEvent &        event,
    const Octane::ApiMouseWheelDetails & wheelDetails,
    void *                               privateData,
    grpc::Status &                       status)
{
    GRPCLOG("GRPCCallbackMgr::MouseEventCallback");

    // Use doSyncCallback with MouseEventRequest as request type
    // and CallbackAck as response (no meaningful data returned).
    doSyncCallback<
        octaneapi::MouseEventRequest,
        octaneapi::CallbackAck>(
            // 1) BuildRequestFn
            [callbackId, type, &event, &wheelDetails, privateData](octaneapi::MouseEventRequest& request)
    {
        auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

        request.set_callback_id(callbackId);
        request.set_user_data(reinterpret_cast<uint64_t>(privateData));
        request.set_event_type(static_cast<int32_t>(type));

        // Fill the event object
        auto* grpcEvent = request.mutable_event();
        grpcEvent->set_positionx(event.mPositionX);
        grpcEvent->set_positiony(event.mPositionY);
        grpcEvent->set_mousedownposx(event.mMouseDownPosX);
        grpcEvent->set_mousedownposy(event.mMouseDownPosY);
        grpcEvent->set_numberofclicks(event.mNumberOfClicks);

        // Attach event component
        auto* eventComponentPtr = new octaneapi::ObjectRef();
        uint64_t eventComponentHandle =
            objMgr.addPointer(event.mEventComponent);
        eventComponentPtr->set_handle(eventComponentHandle);
        eventComponentPtr->set_type(
            octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
        grpcEvent->set_allocated_eventcomponent(eventComponentPtr);

        // Attach originator
        auto* originatorPtr = new octaneapi::ObjectRef();
        uint64_t originatorComponentHandle =
            objMgr.addPointer(event.mOriginator);
        originatorPtr->set_handle(originatorComponentHandle);
        originatorPtr->set_type(
            octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiGuiComponent);
        grpcEvent->set_allocated_originator(originatorPtr);

        // Fill wheel details
        auto* grpcWheelDetails = request.mutable_wheel_details();
        grpcWheelDetails->set_deltax(wheelDetails.mDeltaX);
        grpcWheelDetails->set_deltay(wheelDetails.mDeltaY);
        grpcWheelDetails->set_isinertial(wheelDetails.mIsInertial);
        grpcWheelDetails->set_isreversed(wheelDetails.mIsReversed);
        grpcWheelDetails->set_issmooth(wheelDetails.mIsSmooth);
    },

            // 2) SyncCallFn
        [this](
            grpc::ClientContext* ctx,
            const octaneapi::MouseEventRequest& req,
            octaneapi::CallbackAck* response)
    {
        // Perform the synchronous gRPC call
        std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCMouseEventCallback", req.callback_id());
        if (uniqueModuleId == "")
        {
            return grpc::Status::OK;
        }
        // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
        const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
        if (!info)
        {
            return grpc::Status::OK;
        }
        return getStub(uniqueModuleId)->MouseEvent(ctx, req, response);
    },

        // 3) ProcessResponseFn
        [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
    {
        if (!st.ok())
        {
            status = st;
            return false;
        }
        status = st;  // OK
        return true;
    }
    );

    // No return value; 'status' indicates success/failure.
}


void GRPCCallbackMgr::DbViewClosingCallback(
    int                     callbackId,
    void *                  userData,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::DbViewClosingCallback");

    // Replace the async call with a doSyncCallback approach
    doSyncCallback<
        octaneapi::BasicCallbackRequest, // Adjust if your .proto request type differs
        octaneapi::CallbackAck           // Return type for "no meaningful data"
    >(
        // 1) BuildRequestFn
        [callbackId, userData](octaneapi::BasicCallbackRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::BasicCallbackRequest& req,
                octaneapi::CallbackAck* response)
        {
            // Perform the synchronous version of DbViewClosing
            std::string uniqueModuleId = getModuleIdFromCallbackId("DbViewClosingCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->DbViewClosing(ctx, req, response);
        },

            // 3) ProcessResponseFn -> just update status
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            // If call fails, set status to the error
            if (!st.ok())
            {
                status = st;
                return false;
            }
            // Otherwise mark success
            status = st;
            return true;
        }
        );

}


void GRPCCallbackMgr::NumericBoxChangedCallback(
    int                     callbackId,
    Octane::ApiNumericBox & numericBox,
    void *                  userData,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::NumericBoxChangedCallback");

    // Use doSyncCallback (request: NumericBoxChangedRequest, response: NumericBoxChangedResponse)
    doSyncCallback<
        octaneapi::NumericBoxChangedRequest,
        octaneapi::CallbackAck>(
            // 1) BuildRequestFn
            [callbackId, &numericBox, userData](octaneapi::NumericBoxChangedRequest& request)
            {
                auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(userData));

                auto* numericBoxPtr = new octaneapi::ObjectRef();
                uint64_t numericBoxHandle = objMgr.addPointer(&numericBox);
                numericBoxPtr->set_handle(numericBoxHandle);
                numericBoxPtr->set_type(
                    octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiNumericBox);

                request.set_allocated_numeric_box(numericBoxPtr);
            },

            // 2) SyncCallFn
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::NumericBoxChangedRequest & req,
                    octaneapi::CallbackAck* response)
            {
                // Perform the synchronous gRPC call
                std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCNumericBoxChangedCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->NumericBoxChanged(ctx, req, response);
            },

                // 3) ProcessResponseFn (update 'status')
                [&status](grpc::Status st, const octaneapi::CallbackAck& resp) -> bool
            {
                if (!st.ok())
                {
                    status = st;
                    return false;
                }
                status = st; // set to OK
                             // If needed, parse resp here for more data
                return true;
            }
            );
}


void GRPCCallbackMgr::Callback(
    int                     callbackId,
    bool                    loading,
    Octane::ApiOcioConfig * config,
    void *                  privateData,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::Callback 1");

    doSyncCallback<
        octaneapi::Callback1Request,   // Adjust if your proto request type is different
        octaneapi::CallbackAck>( // Adjust if your proto response type is different

                                       // 1) BuildRequestFn
            [callbackId, loading, config, privateData](octaneapi::Callback1Request& request)
            {
                auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(privateData));
                request.set_loading(loading);

                // Create an ObjectRef for the config pointer
                auto* ocioConfigPtr = new octaneapi::ObjectRef();
                uint64_t ocioConfigHandle = objMgr.addPointer(config);
                ocioConfigPtr->set_handle(ocioConfigHandle);
                ocioConfigPtr->set_type(
                    octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOcioConfig);

                request.set_allocated_config(ocioConfigPtr);
            },

            // 2) SyncCallFn
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::Callback1Request& req,
                    octaneapi::CallbackAck* response)
            {
                // Perform the synchronous gRPC call
                std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCCallback1", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->Callback1(ctx, req, response);
            },

                // 3) ProcessResponseFn
                [&status](grpc::Status st, const octaneapi::CallbackAck& resp) -> bool
            {
                // If call fails, set 'status'
                if (!st.ok())
                {
                    status = st;
                    return false;
                }

                // Otherwise, set 'status' to OK
                status = st;
                // If needed, you can parse resp for additional data
                return true;
            }
            );

}


void GRPCCallbackMgr::Callback(
    int                     callbackId,
    Octane::ApiOcioConfig * config,
    bool                    contextUsableForConversion,
    void *                  privateData,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::Callback 2");

        // Use doSyncCallback with your request/response proto types
        doSyncCallback<
        octaneapi::Callback2Request,   // Adjust if your .proto is named differently
        octaneapi::CallbackAck>(
            // 1) BuildRequestFn
            [callbackId, config, contextUsableForConversion, privateData]
    (octaneapi::Callback2Request& request)
            {
                // Fill in the request object
                auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(privateData));
                request.set_context_usable(contextUsableForConversion);

                // Create an ObjectRef for config
                auto* ocioConfigPtr = new octaneapi::ObjectRef();
                uint64_t ocioConfigHandle = objMgr.addPointer(config);

                ocioConfigPtr->set_handle(ocioConfigHandle);
                ocioConfigPtr->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiOcioConfig);

                request.set_allocated_config(ocioConfigPtr);
            },

        // 2) SyncCallFn
                [this](

                    grpc::ClientContext* ctx,
                    const octaneapi::Callback2Request& req,
                    octaneapi::CallbackAck* response)
            {
                // Blocking gRPC call instead of an async one
                std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCCallback2", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->Callback2(ctx, req, response);
            },

                // 3) ProcessResponseFn
                //    We'll just set 'status' accordingly. Since the original function is void,
                //    we don't need to return any extra data. We'll return an unused bool or int.
                [&status](grpc::Status st, const octaneapi::CallbackAck& resp) -> bool
            {
                // If call fails, record it in 'status'
                if (!st.ok())
                {
                    status = st;
                    return false;
                }

                // Otherwise, mark success
                status = st;
                // if needed, you can parse resp for more data here
                return true;
            }
            );
}


const char * GRPCCallbackMgr::ApiProjectManagerAssetMissingCallback(
    int             callbackId,
    const char *    fileName,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::ApiProjectManagerAssetMissingCallback");

    // If no fileName provided, return an empty string
    if (!fileName)
    {
        status = grpc::Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            "ApiProjectManagerAssetMissingCallback: fileName is null");
        return {};
    }

    // Use doSyncCallback so the call is performed synchronously
    const char *  resultPtr = doSyncCallback<
        octaneapi::AssetMissingRequest,
        octaneapi::AssetMissingResponse>(
            // 1) BuildRequestFn
            [callbackId, userData, fileName](octaneapi::AssetMissingRequest& request)
            {
                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(userData));
                request.set_file_name(fileName);
            },

            // 2) SyncCallFn
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::AssetMissingRequest& req,
                    octaneapi::AssetMissingResponse* response)
            {
                std::string uniqueModuleId = getModuleIdFromCallbackId("AssetMissingCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->ApiProjectManager_AssetMissing(ctx, req, response);
            },

                // 3) ProcessResponseFn -> produce an std::string
                [&status](grpc::Status st, const octaneapi::AssetMissingResponse& resp) -> const char *
            {
                // If the RPC fails, record the error and return an empty string
                if (!st.ok())
                {
                    status = st;
                    return {};
                }

                // Otherwise, mark status as OK and return the missing path
                status = st;
                return OctaneGRPC::StringManager::getInstance().addString(resp.resolved_file_path());
            }
            );

    // Return the final string to the caller. No manual delete[] needed.
    return  resultPtr;// crash
}


bool GRPCCallbackMgr::UpdateCallback(
    int             callbackId,
    float           percent,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::UpdateCallback");

    // Use doSyncCallback to wrap the blocking call logic
    bool continueUpload = doSyncCallback<
        octaneapi::UpdateRequest,
        octaneapi::UpdateResponse>(
            // 1) BuildRequestFn: fill the UpdateRequest
            [callbackId, userData, percent](octaneapi::UpdateRequest& request)
            {
                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(userData));
                request.set_percent(percent);
            },

            // 2) SyncCallFn: perform the synchronous gRPC call
                [this](
                    grpc::ClientContext* ctx,
                    const octaneapi::UpdateRequest& req,
                    octaneapi::UpdateResponse* response)
            {
                std::string uniqueModuleId = getModuleIdFromCallbackId("UpdateCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->Update(ctx, req, response);
            },

                // 3) ProcessResponseFn: interpret the result, produce a bool
                [&status](grpc::Status st, const octaneapi::UpdateResponse& resp) -> bool
            {
                // If the gRPC call failed, set the status and return false
                if (!st.ok())
                {
                    status = st;
                    return false;
                }
                // Otherwise set status OK and return whether we continue uploading
                status = st;
                return resp.continueupload();
            }
            );

    // Return the final bool
    return continueUpload;
}


bool GRPCCallbackMgr::AsyncUpdateCallback(
    int                callbackId,
    unsigned long long changeLevel,
    void *             userData,
    grpc::Status &     status)
{
    GRPCLOG("GRPCCallbackMgr::AsyncUpdateCallback");

    // Convert the old async code to a synchronous pattern using doSyncCallback:

    // 1) We define the request/response types in the template call
    //    (assuming octaneapi::AsyncUpdateRequest / octaneapi::UpdateResponse in your .proto).
    bool continueUpload = doSyncCallback<
        octaneapi::AsyncUpdateRequest,
        octaneapi::UpdateResponse>(

            // 2) BuildRequestFn: populate the AsyncUpdateRequest
            [callbackId, userData, changeLevel](octaneapi::AsyncUpdateRequest& request)
            {
                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(userData));
                request.set_change_level(changeLevel);
            },

            // 3) SyncCallFn: perform the blocking gRPC call
                [this](
                    grpc::ClientContext *              ctx,
                    const octaneapi::AsyncUpdateRequest & req,
                    octaneapi::UpdateResponse *           response)
            {
                // If your proto defines a synchronous "Update(...)" method, call it here.
                // You may need to adjust the stub method name to match your .proto definition.
                std::string uniqueModuleId = getModuleIdFromCallbackId("AsyncUpdateCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->AsyncUpdate(ctx, req, response);
            },

                // 4) ProcessResponseFn: interpret the (status, response), produce a bool.
                [&status](grpc::Status st, const octaneapi::UpdateResponse & resp) -> bool
            {
                // If gRPC fails, propagate that error status and return false
                if (!st.ok())
                {
                    status = st;
                    return false;
                }

                // Otherwise, we set status to OK, and return whether we "continueUpload."
                // (Adjust to match the actual field in your UpdateResponse.)
                status = grpc::Status::OK;

                // If your proto doesn't have "continue_upload()",
                // you can return some default bool or add new logic here.
                return resp.continueupload(); 
            }
            );

    // Return the final bool to the caller
    return continueUpload;
}


const char * GRPCCallbackMgr::AssetMissingCallback(
    int             callbackId,
    const char *    fileName,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::AssetMissingCallback");

    // If no fileName, can't do anything
    if (!fileName)
    {
        status = grpc::Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            "AssetMissingCallback: fileName is null");
        return nullptr;
    }

    // Use doSyncCallback with your request/response types
    const char* resultPtr = doSyncCallback<
        octaneapi::AssetMissingRequest,
        octaneapi::AssetMissingResponse>(
            // 1) BuildRequestFn: populate the request
            [callbackId, userData, fileName](octaneapi::AssetMissingRequest& request)
            {
                request.set_callback_id(callbackId);
                request.set_user_data(reinterpret_cast<uint64_t>(userData));
                request.set_file_name(fileName);
            },

            // 2) SyncCallFn: perform the blocking RPC
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::AssetMissingRequest& req,
                octaneapi::AssetMissingResponse* resp)
            {
                std::string uniqueModuleId = getModuleIdFromCallbackId("AssetMissingCallback", req.callback_id());
                if (uniqueModuleId == "")
                {
                    return grpc::Status::OK;
                }
                // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
                const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
                if (!info)
                {
                    return grpc::Status::OK;
                }
                return getStub(uniqueModuleId)->AssetMissing(ctx, req, resp);
            },

            // 3) ProcessResponseFn: decide how to handle the final result
            [&status](grpc::Status st, const octaneapi::AssetMissingResponse& resp) -> const char*
            {
                // If the RPC fails, set error status and return nullptr
                if (!st.ok())
                {
                    status = st;
                    return nullptr;
                }

                // Mark status as OK
                status = st;
                return OctaneGRPC::StringManager::getInstance().addString( resp.resolved_file_path());
            }
            );

    // Return the allocated char* to the caller
    // If the RPC failed, resultPtr may be nullptr
    return resultPtr;
}


int GRPCCallbackMgr::NumRowsCallback(
    int             callbackId,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::NumRowsCallback");
 
    // 1) Build the request
    octaneapi::BasicCallbackRequest req;
    req.set_callback_id(callbackId);
    req.set_user_data(reinterpret_cast<uint64_t>(userData));

    // 2) Prepare a response and context
    octaneapi::NumRowsResponse response;
    grpc::ClientContext ctx;

    // 3) Call the synchronous gRPC method directly
    std::string uniqueModuleId = getModuleIdFromCallbackId("NumRowsCallback", req.callback_id());
    if (uniqueModuleId == "")
    {
        return 0;
    }
    // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
    const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
    if (!info)
    {
        return 0;
    }
    grpc::Status st = getStub(uniqueModuleId)->NumRows(&ctx, req, &response);

    // 4) Check success/failure
    if (!st.ok())
    {
        // On failure, record the error and return 0
        status = st;
        return 0;
    }

    // Otherwise mark success, return the row count
    status = st;
    return response.num_rows();

    //// Use doSyncCallback to abstract away threading/promise logic
    //int numRows = doSyncCallback<
    //    octaneapi::BasicCallbackRequest,
    //    octaneapi::NumRowsResponse>(
    //// 1) BuildRequestFn
    //[callbackId, userData](octaneapi::BasicCallbackRequest& request)
    //{
    //    // Populate the request with callbackId and userData
    //    request.set_callback_id(callbackId);
    //    request.set_user_data(reinterpret_cast<uint64_t>(userData));
    //},

    //// 2) SyncCallFn
    //[this](
    // int callbackId,
    // grpc::ClientContext* ctx,
    //        const octaneapi::BasicCallbackRequest& request,
    //        octaneapi::NumRowsResponse* response)
    //{
    //    // Perform the synchronous gRPC call
    //    return getStub()->NumRows(ctx, request, response);
    //},

    //// 3) ProcessResponseFn -> convert (grpc::Status, NumRowsResponse) into an int
    //[&status](grpc::Status st, const octaneapi::NumRowsResponse& resp) -> int
    //{
    //    // If call failed, set out-parameter 'status' and return 0
    //    if (!st.ok())
    //    {
    //        status = st;
    //        return 0;
    //    }

    //    // Otherwise, set 'status' to OK and return the row count
    //    status = st;
    //    return resp.num_rows();
    //}
    // );
    //
    //return numRows;
}


const char * GRPCCallbackMgr::ContentCallback(
    int             callbackId,
    int             row,
    int             column,
    void *          userData,
    grpc::Status &  status)
{
    GRPCLOG("GRPCCallbackMgr::ContentCallback");

    // 1) Build the request
    octaneapi::ContentRequest request;
    request.set_callback_id(callbackId);
    request.set_user_data(reinterpret_cast<uint64_t>(userData));
    request.set_row(row);
    request.set_column(column);

    // 2) Prepare a response + context
    octaneapi::ContentResponse response;
    grpc::ClientContext ctx;

    // 3) Perform the synchronous gRPC call
    std::string uniqueModuleId = getModuleIdFromCallbackId("ContentCallback", request.callback_id());
    if (uniqueModuleId == "")
    {
        return nullptr;
    }
    // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
    const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
    if (!info)
    {
        return nullptr;
    }
    grpc::Status st = getStub(uniqueModuleId)->Content(&ctx, request, &response);

    // 4) Check result
    if (!st.ok())
    {
        // If gRPC call failed
        status = st;
        // Return nullptr (or an empty string) to indicate failure
        return nullptr;
    }

    // Otherwise, copy the server's content into a newly allocated buffer
    // or use a string manager if appropriate
    status = st;
    return OctaneGRPC::StringManager::getInstance().addString(response.content());

    //// Use our generic doSyncCallback to avoid manual thread/promise code
    //const char* resultPtr = doSyncCallback<
    //    octaneapi::ContentRequest,
    //    octaneapi::ContentResponse>(
    //        // 1) BuildRequestFn: populate the ContentRequest
    //        [callbackId, userData, row, column](octaneapi::ContentRequest& req)
    //        {
    //            req.set_callback_id(callbackId);
    //            req.set_user_data(reinterpret_cast<uint64_t>(userData));
    //            req.set_row(row);
    //            req.set_column(column);
    //        },

    //        // 2) SyncCallFn: perform the blocking gRPC call
    //            [this](
    // int callbackId,
    // grpc::ClientContext* ctx,
    //                const octaneapi::ContentRequest& req,
    //                octaneapi::ContentResponse* resp)
    //        {
    //            return getStub()->Content(ctx, req, resp);
    //        },

    //            // 3) ProcessResponseFn: convert (grpc::Status, ContentResponse) to a char*.
    //            //    We also set 'status' here by capturing it by reference.
    //            [&status](grpc::Status st, const octaneapi::ContentResponse& resp) -> const char*
    //        {
    //            // If call failed, return an empty, dynamically allocated string
    //            if (!st.ok())
    //            {
    //                status = st; // Pass the error status back to the caller
    //                return nullptr;
    //            }

    //            // Otherwise, copy resp.content() into a newly allocated buffer
    //            status = st;
    //            return StringManager::getInstance().addString(resp.content());
    //        }
    //        );

    //// Return the allocated char* to the caller
    //return resultPtr;
}


void GRPCCallbackMgr::ButtonClickedCallback(
    int                     callbackId,
    Octane::ApiTextButton & textButton,
    void *                  userData,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::ButtonClickedCallback");

    // We'll store the final grpc::Status from doSyncCallback here:
    grpc::Status finalStatus = doSyncCallback<
        octaneapi::ButtonClickedRequest,
        octaneapi::CallbackAck 
    >(
        // 1) BuildRequestFn: populate the gRPC request
        [callbackId, &textButton, userData](octaneapi::ButtonClickedRequest& request)
        {
            auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

            // Set callbackId and userData
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            // Create an ObjectRef for the textButton
            auto* textButtonPtr = new octaneapi::ObjectRef();
            uint64_t textButtonHandle = objMgr.addPointer(&textButton);
            textButtonPtr->set_handle(textButtonHandle);
            textButtonPtr->set_type(
                octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextButton);

            // Attach it to the request
            request.set_allocated_text_button(textButtonPtr);
        },

        // 2) SyncCallFn: invoke the actual synchronous gRPC call
        [this](
            grpc::ClientContext* ctx,
            const octaneapi::ButtonClickedRequest& req,
            octaneapi::CallbackAck* response)
        {
            // If your .proto method is "rpc ButtonClicked(...) returns (...)"
            // then the stub method name should match (e.g. "ButtonClicked").
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCButtonClickedCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->ButtonClicked(ctx, req, response);
        },

        // 3) ProcessResponseFn: convert (grpc::Status, ResponseType) into whatever you want.
        //    Here, we just return the status to store in "finalStatus."
        [](grpc::Status st, const octaneapi::CallbackAck& resp)
        {
            // Optionally, do something with resp if needed.
            // For now, we just return the final status:
            return st;
        }
        );

    // Set the out-parameter "status" to our final status
    status = finalStatus;

    //auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();
    //auto* call   = new ButtonClickedCallbackCall();

    //call->mRequest.set_callback_id(callbackId);
    //call->mRequest.set_user_data(reinterpret_cast<uint64_t>(userData));

    //auto* textButtonPtr = new octaneapi::ObjectRef();
    //uint64_t textButtonHandle = objMgr.addPointer(&textButton);
    //textButtonPtr->set_handle(textButtonHandle);
    //textButtonPtr->set_type(octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextButton);
    //call->mRequest.set_allocated_text_button(textButtonPtr);

    //call->mReader = getStub()->AsyncButtonClicked(&call->mContext, call->mRequest, mCompletionQueue.get());
    //call->mReader->Finish(&call->mResponse, &call->mStatus, call);

    //status = grpc::Status::OK;
}


void GRPCCallbackMgr::SelectionChangedCallback(
    int            callbackId,
    int            lastRowSelected,
    void *         userData,
    grpc::Status & status)
{
    GRPCLOG("GRPCCallbackMgr::SelectionChangedCallback");

    // Use a doSyncCallback pattern instead of async
    doSyncCallback<
        octaneapi::SelectionChangedRequest, 
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, userData, lastRowSelected](octaneapi::SelectionChangedRequest& request)
        {
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));
            request.set_last_row_selected(lastRowSelected);
        },

        // 2) SyncCallFn
            [this]( 
                grpc::ClientContext* ctx,
                const octaneapi::SelectionChangedRequest& req,
                octaneapi::CallbackAck* resp)
        {
            // Blocking gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("SelectionChangedCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->SelectionChanged(ctx, req, resp);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*unused*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::TextEditorChangedCallback(
    int                     callbackId,
    Octane::ApiTextEditor & textEdit,
    void *                  userData,
    grpc::Status &          status)
{
    GRPCLOG("GRPCCallbackMgr::TextEditorChangedCallback");

    // Convert from async to doSyncCallback
    doSyncCallback<
        octaneapi::TextEditorChangedRequest, // Adjust if needed to match your .proto
        octaneapi::CallbackAck               // For a callback with no extra data
    >(
        // 1) BuildRequestFn
        [callbackId, &textEdit, userData](octaneapi::TextEditorChangedRequest& request)
        {
            auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

            // Set callbackId and userData
            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            // Create an ObjectRef for the text editor
            auto* textEditPtr = new octaneapi::ObjectRef();
            uint64_t textEditHandle = objMgr.addPointer(&textEdit);
            textEditPtr->set_handle(textEditHandle);
            textEditPtr->set_type(
                octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiTextEditor);

            request.set_allocated_text_edit(textEditPtr);
        },

        // 2) SyncCallFn
            [this](
                grpc::ClientContext* ctx,
                const octaneapi::TextEditorChangedRequest& req,
                octaneapi::CallbackAck* resp)
        {
            // Perform the synchronous RPC
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCTextEditorChangedCallback", req.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->TextEditorChanged(ctx, req, resp);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*unused*/) -> bool
        {
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // OK
            return true;
        }
        );
}


void GRPCCallbackMgr::OnWindowCloseCallback(
    int                 callbackId,
    Octane::ApiWindow & window,
    void *              userData,
    grpc::Status &      status)
{
    GRPCLOG("GRPCCallbackMgr::OnWindowCloseCallback");

    // Use doSyncCallback in place of the previous async approach
    doSyncCallback<
        octaneapi::OnWindowCloseRequest,
        octaneapi::CallbackAck
    >(
        // 1) BuildRequestFn
        [callbackId, &window, userData](octaneapi::OnWindowCloseRequest& request)
        {
            auto& objMgr = OctaneGRPC::ObjectReferenceManager::getInstance();

            request.set_callback_id(callbackId);
            request.set_user_data(reinterpret_cast<uint64_t>(userData));

            uint64_t windowHandle = objMgr.addPointer(&window);
            auto* windowPtr = new octaneapi::ObjectRef();
            windowPtr->set_handle(windowHandle);
            windowPtr->set_type(
                octaneapi::ObjectRef_ObjectType::ObjectRef_ObjectType_ApiWindow);

            request.set_allocated_window(windowPtr);
        },

        // 2) SyncCallFn
            [this]( 
                grpc::ClientContext* ctx,
                const octaneapi::OnWindowCloseRequest& request,
                octaneapi::CallbackAck* response)
        {
            // Synchronous gRPC call
            std::string uniqueModuleId = getModuleIdFromCallbackId("GRPCOnWindowCloseCallback", request.callback_id());
            if (uniqueModuleId == "")
            {
                return grpc::Status::OK;
            }
            // only proceed if the unique ID provided by the remote EXE matches the one passed in addModule
            const ModuleRegistry::ModuleInfo * info = ModuleRegistry::getInstance().findModule(uniqueModuleId);
            if (!info)
            {
                return grpc::Status::OK;
            }
            return getStub(uniqueModuleId)->OnWindowClose(ctx, request, response);
        },

            // 3) ProcessResponseFn
            [&status](grpc::Status st, const octaneapi::CallbackAck& /*resp*/) -> bool
        {
            // Update the out-param 'status'
            if (!st.ok())
            {
                status = st;
                return false;
            }
            status = st; // OK
            return true;
        }
        );
}
#endif //#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)