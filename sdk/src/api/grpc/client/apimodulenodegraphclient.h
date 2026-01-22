// Copyright (C) 2026 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
namespace OctaneGRPC
{
    class ApiNodePinInfoProxy;
    class ApiNodeProxy;
    class ApiImageProxy;
}
#include "apinodegraphclient.h"


#include "apimodulenodegraph.h"


namespace OctaneGRPC
{
    class Convert;
    class GRPCSettings;
}


namespace OctaneGRPC
{

/// Proxy class for ApiModuleNodeGraph
class ApiModuleNodeGraphProxy : public ApiNodeGraphProxy
{
public:
    /// Function to set input linker to a graph. This function add, delete and modify info of the linkers nodes in a
    /// specified range. This function can be used for any operations but we have insertLinkers, removeLinkers for additional help.
    /// Must be called only from the init or evaluate function Note: Use getInputNodes to grab created linker list.
    ///
    /// @param[in] inputInfos
    ///     Input pin infos list.
    /// @param[in] infosCount
    ///     Count of the infosCount.
     /// @param[in] range
    ///     The linkers in this range will be modified or deleted from the list. Including range.y
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setInputLinkers(
            const ApiNodePinInfoProxy *const          inputInfos,
            const uint32_t                            inputInfosCount,
            const OctaneVec::uint32_2                 range
            );

    /// Function to set output linker to a graph. Use insertLinkers, removeLinkers and
    /// modifyLinkers for other operations. Must be called only from the init or evaluate function
    /// Note: Use getInputNodes to grab created linker list.
    ///
    /// @param[in] outputInfos
    ///     Output pin infos list.
    /// @param[in] infosCount
    ///     Count of the outputInfos.
    /// @param[in] range
    ///     The linkers in this range will be modified or deleted from the list. Including range.y
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setOutputLinkers(
            const ApiNodePinInfoProxy *const          outputInfos,
            const uint32_t                            outputInfosCount,
            const OctaneVec::uint32_2                 range
            );

    /// Function to insert linkers. Must be called only from the init or evaluate function.
    ///
    /// @param[in] infos
    ///     Linker node pin infos list which needs to be inserted.
    /// @param[in] infosCount
    ///     Count of the linker node pin infos.
    /// @param[in] ix
    ///     Position in the linker list where the new linkers needs to be inserted.
    /// @param[in] isInputLinkers
    ///     Set TRUE if the infos is a input linkers and False for output linkers.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void insertLinkers(
            const ApiNodePinInfoProxy *const          infos,
            const uint32_t                            infosCount,
            const uint32_t                            ix,
            const bool                                isInputLinkers
            );

    ///     Linker node pin infos which needs to be inserted.
    /// @param[in] infosCount
    ///     Count of the linker node pin infos.
    /// @param[in] range
    ///     The linkers in this range will be deleted and removed from the list. Including range.y
    /// @param[in] isInputLinkers
    ///     Set TRUE if the infos is a input linkers and False for output linkers.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void removeLinkers(
            const ApiNodePinInfoProxy *const          infos,
            const OctaneVec::uint32_2                 range,
            const bool                                isInputLinkers
            );

    /// Assigns a new node pin info to an input linker node. Must be called only from the init or
    /// evaluate function, and can't be called for an input which was changed before this evaluate
    /// call. The pin type of the pin info must match the existing linker node.
    ///
    /// @param[in] linkerNode
    ///     A linker node that need to be modified.
    /// @param[in] info
    ///     Info that needs to set to the linker node.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setInputInfo(
            const ApiNodeProxy *const                 linkerNode,
            const ApiNodePinInfoProxy &               info
            );

    /// Return if an input was changed since the last evaluation. This is only meaningful when called
    /// from the evaluate function. If this is the first evaluation after loading the script, this.
    /// function returns false.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool inputWasChanged(
            const ApiNodeProxy *const   linkerNode
            ) const;

    /// Reads the input value of a linker node, which can't be done directly using the input pin of
    /// the linker.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            bool &                                    value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            float &                                   value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::float_2 &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::float_3 &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::float_4 &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            int32_t &                                 value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::int32_2 &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::int32_3 &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::int32_4 &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            OctaneVec::MatrixF &                      value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            std::string &                             value
            ) const;

    bool getInputValue(
            const ApiNodeProxy *const                 linkerNode,
            Octane::ApiFilePath &                     value
            ) const;

    /// Sets the input value of a linker node, which can't be done directly using the input pin of
    /// the linker
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const bool                                value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const float                               value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::float_2                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::float_3                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::float_4                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const int32_t                             value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::int32_2                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::int32_3                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::int32_4                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const OctaneVec::MatrixF                  value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const char *                              value,
            const bool                                evaluate
            );

    void setInputValue(
            const ApiNodeProxy *const                 linkerNode,
            const Octane::ApiFilePath                 value,
            const bool                                evaluate
            );

    void reset();

    /// Function will cause the evaluate function to be called after time changes
    /// @param[in] shouldEvaluate
    ///     if true the onEvaluate function will be called after time changes
    /// @param[in] interval
    ///     The animation interval which should be associated with the animated graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setEvaluateTimeChanges(
            const bool                                shouldEvaluate,
            const OctaneVec::float_2                  timeInterval
            );

    /// sets a icon for this graph.
    /// @param[in] image
    ///     The image to use. If NULL, the icon will be reverted to a default icon.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setIcon(
            const ApiImageProxy *   image
            );

    /// Tells if the time was changed since the last evaluation. This is only meaningful when called
    /// from the evaluate function, and after evaluating on time changes has been enabled with
    /// setEvaluateTimeChanges.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool wasTimeChanged() const;

    /// Adds an asset to the graph
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t appendAsset(
            const Octane::ApiFilePath &   filePath
            );

    /// removes an asset from the graph. This will shift all subsequent assets one down.
    ///
    /// @param[in] index
    ///     "The index of the asset in the array."
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void removeAsset(
            const size_t   index
            );

    /// gets an asset from the graph. can be used this on nodes which have filename and package
    /// attribute (eg: texture node). or use read asset to grab the data
    ///
    /// @param[in] index
    ///     The index of the asset in the array
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     Returns file path which contains filename and package. The returned filepath should be
    ///     deleted with destroy().
    Octane::ApiFilePath getAsset(
            const size_t   index
            ) const;

    /// Returns size of the asset array
    /// @param[out] status
    ///     Contains the status of the gRPC call
    size_t getAssetCount() const;

    /// Reads an asset as a cstring
    /// @param[in] index
    ///     The index of the asset in the array
    /// @param[out] data
    ///      file data, This should deleted via cleanupString().
    /// @param[out] size
    ///      size of the data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    /// TRUE if successful.
    /// FALSE if path is not a relative path or if the file doesn't exist, or an error occurs while opening the file.
    bool readAsset(
            const size_t                              index,
            std::string &                             data,
            uint64_t &                                size
            );

    /// Reads a file as a c String
    /// @param[in]  path
    ///      path to a file. filename should be absolute if the file is from file system. or relative if
    ///      to package and package name should be absolute.
    /// @param[out] data
    ///      file data, This should deleted via freeAssetDataString().
    /// @param[out] size
    ///      size of the data.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    /// TRUE if successful.
    /// FALSE if path is not a relative path or if the file doesn't exist, or an error occurs while opening the file.
    bool readAsset(
            const Octane::ApiFilePath &               path,
            std::string &                             data,
            uint64_t &                                size
            );

    /// removes all the assets
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void removeAllAssets();

    /// Function to save some settings with the graph when this graph getting saved in a save file.
    ///
    /// @param[in] data
    ///     Data to be stored.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setSaveData(
            const char *   data
            );

    /// Function to retrieve user data which was saved with the graph.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string getSaveData();

    /// Assigns user data pointer. This pointer is not saved in a save file.
    ///
    /// @param[in] data
    ///     data pointer to be assigned
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setCustomData(
            void *   data
            );

    /// Returns TRUE if the underlying module provides an onTrigger callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    bool isTriggerEnabled() const;

    /// Calls the onTrigger callback.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void trigger() const;

    /// Assigns the icon for the trigger button.
    /// If NULL, the icon is reverted to the default one.
    /// This doesn't affect the size of the trigger button.
    /// The assumption is that the module calls this function once during initialization, so UI
    /// doesn't listen to this change.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setTriggerButtonIcon(
            const ApiImageProxy *   image
            );

    /// Assigns the tooltip text for the trigger button.
    /// If NULL or empty, the tooltip will be disabled.
    /// The assumption is that the module calls this function once during initialization, so UI
    /// doesn't listen to this change.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setTriggerButtonTooltip(
            const char *   tooltip
            );

    /// Updates the progress bar visibility, progress value and status label text.
    /// It's safe to call this function from the worker threads.
    ///
    /// @param[in] progressBarVisible
    ///     Whether the progress bar should be visible
    /// @param[in] progress
    ///     Value in range [0..100] will set the progress bar value. Any negative value will switch
    ///     the progress bar to the "busy" mode. If progressBarVisible is false, this parameter is
    ///     ignored.
    /// @param[in] statusText
    ///     The text for the status label. If null or empty, the status label will be hidden.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void setProgressState(
            bool                                      progressBarVisible,
            float                                     progress,
            const char *                              statusText
            );

    static GRPCSettings & getGRPCSettings();
};

} // end of namespace
