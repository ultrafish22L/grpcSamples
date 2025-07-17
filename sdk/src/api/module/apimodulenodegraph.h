// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_MODULE_NODE_GRAPH_H_
#define _API_MODULE_NODE_GRAPH_H_    1

#include "apinodesystem.h"
#include "octaneids.h"
#include "octanetypes.h"

namespace Octane
{

class  ApiImage;
class  ApiNode;
struct ApiNodePinInfo;



//-------------------------------------------------------------------------------------------------
/// Module node graph is a graph which allows users to control it using C++ module code. 
///
/// Linkers is the way to connect a node/graph to/from this graph. For each linker a pin is created and
/// nodes with matching pin type can be connected to that pin.
class OCTANEAPI_DECL ApiModuleNodeGraph : public ApiNodeGraph
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
    void setInputLinkers(
        const Octane::ApiNodePinInfo *const inputInfos,
        const uint32_t               inputInfosCount,
        const uint32_2               range = uint32_2::make(0, UINT32_MAX));

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
    void setOutputLinkers(
        const Octane::ApiNodePinInfo *const outputInfos,
        const uint32_t               outputInfosCount,
        const uint32_2               range = uint32_2::make(0, UINT32_MAX));

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
    void insertLinkers(
        const Octane::ApiNodePinInfo *const infos,
        const uint32_t               infosCount,
        const uint32_t               ix,
        const bool                   isInputLinkers);

    /// Function to delete linkers. Must be called only from the init or evaluate function.
    /// 
    // @param[in] infos
    ///     Linker node pin infos which needs to be inserted.
    /// @param[in] infosCount
    ///     Count of the linker node pin infos.
    /// @param[in] range
    ///     The linkers in this range will be deleted and removed from the list. Including range.y
    /// @param[in] isInputLinkers
    ///     Set TRUE if the infos is a input linkers and False for output linkers.
    void removeLinkers(
        const Octane::ApiNodePinInfo *const infos,
        const uint32_2               range,
        const bool                   isInputLinkers);

    /// Assigns a new node pin info to an input linker node. Must be called only from the init or
    /// evaluate function, and can't be called for an input which was changed before this evaluate
    /// call. The pin type of the pin info must match the existing linker node.
    ///
    /// @param[in] linkerNode
    ///     A linker node that need to be modified.
    /// @param[in] info
    ///     Info that needs to set to the linker node.
    void setInputInfo(
        const ApiNode                *const linkerNode,
        const Octane::ApiNodePinInfo &info);

    /// Return if an input was changed since the last evaluation. This is only meaningful when called
    /// from the evaluate function. If this is the first evaluation after loading the script, this.
    /// function returns false.
    bool inputWasChanged(
        const ApiNode *const linkerNode) const;

    /// Reads the input value of a linker node, which can't be done directly using the input pin of
    /// the linker.
    bool getInputValue(const ApiNode *const linkerNode, bool        &value) const;
    bool getInputValue(const ApiNode *const linkerNode, float       &value) const;
    bool getInputValue(const ApiNode *const linkerNode, float_2     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, float_3     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, float_4     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, int32_t     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, int32_2     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, int32_3     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, int32_4     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, MatrixF     &value) const;
    bool getInputValue(const ApiNode *const linkerNode, const char *&value) const;
    bool getInputValue(const ApiNode *const linkerNode, ApiFilePath &value) const;

    /// Sets the input value of a linker node, which can't be done directly using the input pin of
    /// the linker
    void setInputValue(const ApiNode *const linkerNode, const bool         value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const float        value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const float_2      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const float_3      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const float_4      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const int32_t      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const int32_2      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const int32_3      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const int32_4      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const MatrixF      value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const char        *value, const bool evaluate);
    void setInputValue(const ApiNode *const linkerNode, const ApiFilePath  value, const bool evaluate);

    // Resets module graph contents to its initial state as it would be just before init was called.
    // This state will always still contain all linker nodes and may contain some other nodes which are
    // internally created and used by the module node graph. Any other nodes added by the module will be deleted.
    void reset();

    /// Function will cause the evaluate function to be called after time changes
    /// @param[in] shouldEvaluate
    ///     if true the onEvaluate function will be called after time changes
    /// @param[in] interval
    ///     The animation interval which should be associated with the animated graph. 
    void setEvaluateTimeChanges(
        const bool    shouldEvaluate,
        const float_2 timeInterval = float_2::make(0.f ,0.f));

    /// sets a icon for this graph.
    /// @param[in] image
    ///     The image to use. If NULL, the icon will be reverted to a default icon.
    void setIcon(
        const ApiImage *image);

    /// Tells if the time was changed since the last evaluation. This is only meaningful when called
    /// from the evaluate function, and after evaluating on time changes has been enabled with
    /// setEvaluateTimeChanges. 
    bool wasTimeChanged() const;
    
    /// Adds an asset to the graph
    size_t appendAsset(
        const ApiFilePath& filePath);

    /// removes an asset from the graph. This will shift all subsequent assets one down.
    ///
    /// @param[in] index
    ///     "The index of the asset in the array."
    void removeAsset(
        const size_t index);

    /// gets an asset from the graph. can be used this on nodes which have filename and package 
    /// attribute (eg: texture node). or use read asset to grab the data
    ///
    /// @param[in] index
    ///     The index of the asset in the array
    /// @return 
    ///     Returns file path which contains filename and package. The returned filepath should be 
    ///     deleted with destroy().
    ApiFilePath getAsset(
        const size_t index) const;

    /// Returns size of the asset array
    size_t getAssetCount() const;

    /// Reads an asset as a cstring
    /// @param[in] index
    ///     The index of the asset in the array
    /// @param[out] data
    ///      file data, This should deleted via cleanupString().
    /// @param[out] size
    ///      size of the data.
    /// @return 
    /// TRUE if successful.
    /// FALSE if path is not a relative path or if the file doesn't exist, or an error occurs while opening the file.
     bool readAsset(
        const size_t index,
        const char   *&data,
        uint64_t     &size);

    /// Reads a file as a c String
    /// @param[in]  path
    ///      path to a file. filename should be absolute if the file is from file system. or relative if 
    ///      to package and package name should be absolute.
    /// @param[out] data
    ///      file data, This should deleted via freeAssetDataString().
    /// @param[out] size
    ///      size of the data.
    /// @return 
    /// TRUE if successful.
    /// FALSE if path is not a relative path or if the file doesn't exist, or an error occurs while opening the file.
    bool readAsset(
        const ApiFilePath &path,
        const char        *&data,
        uint64_t          &size);

    /// Cleans the string which is returned be readAsset function
    void freeAssetDataString(
        const char *str);

    /// removes all the assets
    void removeAllAssets();

    /// Function to save some settings with the graph when this graph getting saved in a save file.
    ///
    /// @param[in] data
    ///     Data to be stored. 
    void setSaveData(
        const char *data);

    /// Function to retrieve user data which was saved with the graph.
    const char* getSaveData();

    /// Assigns user data pointer. This pointer is not saved in a save file.
    ///
    /// @param[in] data
    ///     data pointer to be assigned
    void setCustomData(
        void * data);

    /// Returns the pointer to the user data, or NULL if it's not set.
    void * customData() const;

    /// Returns TRUE if the underlying module provides an onTrigger callback.
    bool isTriggerEnabled() const;

    /// Calls the onTrigger callback.
    void trigger() const;

    /// Assigns the icon for the trigger button.
    /// If NULL, the icon is reverted to the default one.
    /// This doesn't affect the size of the trigger button.
    /// The assumption is that the module calls this function once during initialization, so UI
    /// doesn't listen to this change.
    void setTriggerButtonIcon(
        const ApiImage * image);

    /// Assigns the tooltip text for the trigger button.
    /// If NULL or empty, the tooltip will be disabled.
    /// The assumption is that the module calls this function once during initialization, so UI 
    /// doesn't listen to this change.
    void setTriggerButtonTooltip(
         const char * tooltip);

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
    void setProgressState(
        bool         progressBarVisible,
        float        progress = -1.0f,
        const char * statusText = nullptr);
};


} // namespace Octane


#endif // #ifndef _API_MODULE_NODE_GRAPH_H_
