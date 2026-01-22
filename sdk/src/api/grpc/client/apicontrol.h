// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include <memory>
#include <grpcpp/grpcpp.h>
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL

#include "grpcbase.h"
//#include "grpcapinodeinfo.h" 
//#include "callbackservice.h" 
namespace OctaneGRPC
{
    class GRPCSettings;


    //class ApiNodePinInfo;
    /// Proxy class for ApiControlService
    class ApiControlService : public GRPCBase
    {
        // friend CallbackHandlerImpl;
    public:
        /// Starts a blocking operation on Octane.exe
        ///
        /// This function registers and executes a blocking operation identified by a unique module ID.
        /// While the operation is running, a message can be displayed (e.g., for logging or progress tracking).
        /// Once the operation completes, the provided callback function will be executed.
        ///
        /// @param[in] uniqueModuleId  
        ///     The unique identifier for our module instance
        /// @param[in] message  
        ///     A descriptive message associated with the blocking operation to be displayed in the Modal dialog on Octane
        ///     which is displayed while the blocking operations are progressing.
        /// @param[in] callbackFunc
        ///     A function to be executed once the blocking operation has been initiated. From that function
        ///     our module can then make multiple lengthy calls back into Octane while Octane blocks suer intervention
        ///     by displaying a Modal dialog box.
        /// @param[out] status  
        ///     the result of the gRPC call.
        /// @return  
        ///     TRUE if the blocking operation was started successfully; otherwise, FALSE.
        static bool startBlockingOperation(
            const std::string& uniqueModuleId,
            const std::string& message,
            std::function<void()> callbackFunc);

        /// Configures Octane to save logs relating to the GRPC API to the specified file.
        ///
        /// @param[in] saveLogsToTxtFile  
        ///     Set to TRUE to save API logs to a text file; FALSE to disable file logging to TXT file.
        /// @param[in] path  
        ///     The path to the text file.
        /// @return  
        ///     TRUE if the log path was configured successfully; otherwise, FALSE.
        static bool setApiLogPath(
            bool                  saveLogsToTxtFile,
            const std::string& path);
    private:

        // calls the blocking function
        static void callBlockingFunc();

        // sets the blockigncallback function
        static void setBlockingFunc(std::function<void()> callbackFunc);

        /// Returns a reference to the singleton GRPCSettings object,
        /// which manages global configuration and state related to gRPC communication.
        ///
        /// @return
        ///     A reference to the global GRPCSettings instance.
        static GRPCSettings& getGRPCSettings();

        // the blocking function
        static std::function<void()> sBlockingOperationCallbackFunc;
    };
}