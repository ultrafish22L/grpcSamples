// Copyright (C) 2025 OTOY NZ Ltd.

// Copyright (C) 2016 OTOY NZ Ltd.

#ifndef _API_MODULE_H_
#define _API_MODULE_H_    1

#include "octaneenums.h"
#include "octaneids.h"
#include "octanetypes.h"
#include "octaneversion.h"


namespace Octane
{

class ApiGridLayout;
class ApiImage;
class ApiModuleNodeGraph;


/// Every dynamically loaded module needs to have an entry and exit function with a pre-defined
/// signature. Octane will call these functions after loading and before unloading the module,
/// respectively.
///
/// Note: Octane::registerModule is the only safe function to call from OCTANE_MODULE_START.
/// Most of the API functionality has not yet been initialised when modules are loaded.
///
/// OCTANE_MODULE_START()
/// {
///     ... code that starts my module ...
/// }
/// 
/// OCTANE_MODULE_STOP()
/// {
///     ... code that stops my module ...
/// }
#if defined(_WIN32)
# define OCTANE_MODULE_START extern "C" void __declspec(dllexport) _OctaneModuleStart
# define OCTANE_MODULE_STOP  extern "C" void __declspec(dllexport) _OctaneModuleStop
#else
# define OCTANE_MODULE_START extern "C" void                       _OctaneModuleStart
# define OCTANE_MODULE_STOP  extern "C" void                       _OctaneModuleStop
#endif


///==============================================================================
/// Special Key codes
///
/// Note that the actual values of these are platform-specific and may change
/// without warning, so don't store them anywhere as constants.
namespace ApiSpecialKeyCodes
{
    /// key-code for the space bar
    extern OCTANEAPI_DECL const int SPACE_KEY;
    /// key-code for the escape key
    extern OCTANEAPI_DECL const int ESCAPE_KEY;
    /// key-code for the return key
    extern OCTANEAPI_DECL const int RETURN_KEY;
    /// key-code for the tab key
    extern OCTANEAPI_DECL const int TAB_KEY;
    /// key-code for the delete key (not backspace)
    extern OCTANEAPI_DECL const int DELETE_KEY;
    /// key-code for the backspace key
    extern OCTANEAPI_DECL const int BACKSPACE_KEY;
    /// key-code for the insert key
    extern OCTANEAPI_DECL const int INSERT_KEY;
    /// key-code for the cursor-up key
    extern OCTANEAPI_DECL const int UP_KEY;
    /// key-code for the cursor-down key
    extern OCTANEAPI_DECL const int DOWN_KEY;
    /// key-code for the cursor-left key
    extern OCTANEAPI_DECL const int LEFT_KEY;
    /// key-code for the cursor-right key
    extern OCTANEAPI_DECL const int RIGHT_KEY;
    /// key-code for the page-up key
    extern OCTANEAPI_DECL const int PAGE_UP_KEY;
    /// key-code for the page-down key
    extern OCTANEAPI_DECL const int PAGE_DOWN_KEY;
    /// key-code for the home key
    extern OCTANEAPI_DECL const int HOME_KEY;
    /// key-code for the end key
    extern OCTANEAPI_DECL const int END_KEY;
    /// key-code for the F1 key
    extern OCTANEAPI_DECL const int F1_KEY;
    /// key-code for the F2 key
    extern OCTANEAPI_DECL const int F2_KEY;
    /// key-code for the F3 key
    extern OCTANEAPI_DECL const int F3_KEY;
    /// key-code for the F4 key
    extern OCTANEAPI_DECL const int F4_KEY;
    /// key-code for the F5 key
    extern OCTANEAPI_DECL const int F5_KEY;
    /// key-code for the F6 key
    extern OCTANEAPI_DECL const int F6_KEY;
    /// key-code for the F7 key
    extern OCTANEAPI_DECL const int F7_KEY;
    /// key-code for the F8 key
    extern OCTANEAPI_DECL const int F8_KEY;
    /// key-code for the F9 key
    extern OCTANEAPI_DECL const int F9_KEY;
    /// key-code for the F10 key
    extern OCTANEAPI_DECL const int F10_KEY;
    /// key-code for the F11 key
    extern OCTANEAPI_DECL const int F11_KEY;
    /// key-code for the F12 key
    extern OCTANEAPI_DECL const int F12_KEY;
    /// key-code for the F13 key
    extern OCTANEAPI_DECL const int F13_KEY;
    /// key-code for the F14 key
    extern OCTANEAPI_DECL const int F14_KEY;
    /// key-code for the F15 key
    extern OCTANEAPI_DECL const int F15_KEY;
    /// key-code for the F16 key
    extern OCTANEAPI_DECL const int F16_KEY;

    /// key-code for the 0 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_0;
    /// key-code for the 1 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_1;
    /// key-code for the 2 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_2;
    /// key-code for the 3 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_3;
    /// key-code for the 4 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_4;
    /// key-code for the 5 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_5;
    /// key-code for the 6 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_6;
    /// key-code for the 7 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_7;
    /// key-code for the 8 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_8;
    /// key-code for the 9 on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_9;

    /// key-code for the add sign on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_ADD;
    /// key-code for the subtract sign on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_SUBTRACT;
    /// key-code for the multiply sign on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_MULTIPLY;
    /// key-code for the divide sign on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_DIVIDE;
    /// key-code for the comma on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_SEPARATOR;
    /// key-code for the decimal point sign on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_DECIMAL_POINT;   
    /// key-code for the equals key on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_EQUALS;
    /// key-code for the delete key on the numeric keypad.
    extern OCTANEAPI_DECL const int NUMBER_PAD_DELETE;
};


// Flags that represent the different keys.
// E.g. a KeyPress might represent CTRL+C, SHIFT+ALT+H, etc.
enum KeyModifierFlag
{
    // Indicates no modifier keys. 
    NO_MODIFIERS               = 0,
    // Shift key flag.
    SHIFT_MODIFIER             = 1,
    // CTRL key flag.
    CTRL_MODIFIER              = 2,
    // ALT key flag. 
    ALT_MODIFIER               = 4,
    // Left mouse button flag.
    LEFT_BUTTON_MODIFIER       = 16,
    // Right mouse button flag.
    RIGHT_BUTTON_MODIFIER      = 32,
    // Middle mouse button flag.
    MIDDLE_BUTTON_MODIFIER     = 64,

#if defined(__APPLE__)
    // Command key flag - on windows this is the same as the CTRL key flag.
    COMMAND_MODIFIER          = 8,
    // Popup menu flag - on windows this is the same as rightButtonModifier, on the
    //  Mac it's the same as (rightButtonModifier | ctrlModifier).
    POPUP_MENU_CLICK_MODIFIER  = RIGHT_BUTTON_MODIFIER | CTRL_MODIFIER,
#else
    // Command key flag - on windows this is the same as the CTRL key flag. 
    COMMAND_MODIFIER           = CTRL_MODIFIER,
    // Popup menu flag - on windows this is the same as rightButtonModifier, on the
    // Mac it's the same as (rightButtonModifier | ctrlModifier). 
    POPUP_MENU_CLICK_MODIFIER  = RIGHT_BUTTON_MODIFIER,
#endif

    // Represents a combination of all the shift, alt, ctrl and command key modifiers.
    ALL_KEYBOARD_MODIFIERS     = SHIFT_MODIFIER | CTRL_MODIFIER | ALT_MODIFIER | COMMAND_MODIFIER,
    // Represents a combination of all the mouse buttons at once.
    ALL_MOUSE_BUTTON_MODIFIERS = LEFT_BUTTON_MODIFIER | RIGHT_BUTTON_MODIFIER | MIDDLE_BUTTON_MODIFIER,
    // Represents a combination of all the alt, ctrl and command key modifiers.
    CTRL_ALT_COMMAND_MODIFIERS = CTRL_MODIFIER | ALT_MODIFIER | COMMAND_MODIFIER
};



//--------------------------------------------------------------------------------------------------
/// Info for a command module.
class OCTANEAPI_DECL ApiCommandModuleInfo
{

public:

    /// type for the module run function
    ///
    /// @param [in] workpaneUserData 
    ///     If this command for a toolbar item of a work pane module then, this will be the user data 
    ///     which was provided by the work pane init function. Otherwise NULL.
    typedef bool (*CommandModuleRunFuncT)(
        void *const workpaneUserData);

    /// Creates info for Api command module
    ///
    /// @param[in]  moduleId
    ///     Unique ID for this module. should start from 1000101.
    /// @param[in]  fullName
    ///     Name with categories that will be used to group it in the user interface.
    ///     Must have at least one category to display it in the module menu
    ///     eg: "|Octane examples|Hello world" or |Hello world.
    ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
    /// @param[in]  description
    ///     Describes what the work pane module does.
    /// @param[in]  author
    ///     Name of the author for this module.
    /// @param[in]  versionNumber
    ///     Version number of the module.
    static ApiCommandModuleInfo* create(
        const ModuleIdT   moduleId,
        const char *const fullName,
        const char *const description,
        const char *const author,
        const VersionT    versionNumber);

    /// Destroys a ApiCommandModuleInfo object created by create().
    void destroy();

    /// Function to set the command module run function. The run function will be called every time 
    /// the command is executed.(mandatory)
    void setRunFunction(
        const CommandModuleRunFuncT func);

    /// Function to set icon for a command module. (optional)
    void setIcon(
        const ApiImage *const icon);

    /// Function to assign shortcut key for a command module. (optional)
    ///
    /// @param[in]  shortcutGroupName
    ///     Shortcut group which its belong to.
    /// @param[in]  shortcutKeyCode
    ///     A code that represents the key - this value must be one of special constants listed above
    ///     or an 8-bit character code such as a letter (case is ignored) digit like 'a','c','v'..etc,
    ///     or a simple key like "," or ".". 
    ///     Only works when this command is associated with the Api work pane.
    /// @param[in]  shortcutModifierKeyFlag
    ///     The modifiers to associate with the shortcut Keycode. The value is a combination of
    ///     KeyModifierFlag bitwise or-ed together or 0 if no modifier is required.
    ///     Only used when the passed in shortcutKey is not -1.
    void assignShortcutKey(
        const char *const shortcutGroupName,
        const int         shortcutKeyCode         = -1,
        const int         shortcutModifierKeyFlag = 0);

};



//--------------------------------------------------------------------------------------------------
/// Info for a work pane module.
class OCTANEAPI_DECL ApiWorkPaneModuleInfo
{
public:

    /// Init function type for a work pane module. The module should add it's components to the 
    /// passed in grid.
    /// 
    /// @return
    ///     user data which can be any and this will be passed back when destroy function is called.
    ///     (can be NULL)
    typedef void* (*InitFuncT)(
        ApiGridLayout *const gridLayout);

    /// Cleanup function type for a work pane module.
    ///
    /// @param[in] userData
    ///     user data which was provided by the create function 
    typedef void (*CleanupFuncT)(
        void *const userData);

    /// Creates info for Api work pane
    ///
    /// @param[in]  moduleId
    ///     Unique ID for this module. should start from 1000100
    /// @param[in]  fullName
    ///     Name with categories that will appear in the user interface.
    ///     Must have at least one category to display it in the Windows menu
    ///     eg: "|Octane examples|Hello world" or |Hello world.
    ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
    /// @param[in]  description
    ///     Describes what the work pane module does.
    /// @param[in]  author
    ///     Name of the author for this module.
    /// @param[in]  versionNumber
    ///     Version number of the module.
    static ApiWorkPaneModuleInfo* create(
        const ModuleIdT  moduleId,
        const char       *fullName,
        const char       *description,
        const char       *author,
        const VersionT   versionNumber);

    /// Destroys a ApiWorkPaneModuleInfo object created by create().
    void destroy();

    /// Function to set the workpane module create function. (mandatory)
    void setInitFunction(
        const InitFuncT func);

    /// Function to set the workpane module destroy function. (mandatory)
    void setCleanupFunction(
        const CleanupFuncT func);

    /// Function to a set list of command modules ids that will be displayed in the toolbar
    /// of work pane module. (optional)
    ///
    /// @param[in] toolbarModuleIds
    ///      List containing command module ids.
    /// @param[in] size
    ///      Size of the toolbarModuleIds.
    void setWorkPaneToolbarIds(
        const ModuleIdT *const toolbarModuleIds,
        const size_t           size);
};



//------------------------------------------------------------------------------------------------- 
/// Info for module node graph
class OCTANEAPI_DECL ApiNodeGraphModuleInfo
{
public:

    /// Create function which will be called when a module node graph is created.
    ///
    /// @return value
    ///     user data which can be any and this will be passed back when destroy function is called,
    ///     can be used to identify which data should get deleted.
    
    typedef void* (*CreateFuncT)(
        ApiModuleNodeGraph *const graph);

    /// Destroy function callback function which will be called when a module node graph is getting deleted
    ///
    /// @param[in]  userData
    ///     user data which is provided by the creates function 
    typedef void (*DestroyFuncT)(
        void *const userData);

    /// On evaluate function callback function which will be called after init function and 
    /// and when there is any changes in the input values.
    ///
    /// @param[in]  userData
    ///     user data which is provided by the create function 
    typedef void (*OnEvaluateFuncT)(
        void *const userData);

    /// On trigger function callback function which will be called if the user clicks the trigger
    /// button of the UI.
    ///
    /// @param[in]  userData
    ///     user data which is provided by the create function 
    typedef void(*OnTriggerFuncT)(
        void *const userData);

    /// Creates info for Api node graph module
    /// @param[in]  moduleId
    ///     Unique ID for this module. should start from 1000100
    /// @param[in]  fullName
    ///     Name with categories that will appear in the user interface.
    ///     Must have at least one category to display it in the Windows menu
    ///     eg: "|Octane examples|Hello world" or |Hello world.
    ///     and "Hello world" this will not be shown in the menu, can be used for internal commands
    /// @param[in]  description
    ///     Describes what the module node graph does.
    /// @param[in]  author
    ///     Name of the author for this module.
    /// @param[in]  versionNumber
    ///     Version number of the module.
    static ApiNodeGraphModuleInfo* create(
        const ModuleIdT   moduleId,
        const char *const fullName,
        const char *const description,
        const char *const author,
        const VersionT    versionNumber);

    /// Destroys a ApiNodeGraphModuleInfo object created by create().
    void destroy();

    /// Function to set the create function callback for a node graph module. (mandatory)
    void setCreateFunction(
        const CreateFuncT func);

    /// Function to set the destroy function callback for a node graph module. (mandatory)
    void setDestroyFunction(
        const DestroyFuncT func);

    /// Function to set the evaluate function callback for a node graph module. (mandatory)
    void setOnEvaluateFunction(
        const OnEvaluateFuncT func);

    /// Sets the function to call when the user clicks the trigger button in the node inspector.
    /// (optional) The trigger button will not be displayed if this callback is not set.
    void setOnTriggerFunction(
        const OnTriggerFuncT func);

    /// Sets the output type of the node graph.
    /// (optional) The default output type is PT_UNKNOWN.
    void setOutType(
        const Octane::NodePinType outType);
};



/// Handles the registration of command module type. Modules can only be registered from within
/// the start function of the module. A module implementation is allowed to register different
/// modules (with distinct module ids).
OCTANEAPI_DECL bool registerCommandModule(
    const ApiCommandModuleInfo & moduleInfo);

/// Handles the registration of work pane module type. Modules can only be registered from within
/// the start function of the module. A module implementation is allowed to register different
/// modules (with distinct module ids).
OCTANEAPI_DECL bool registerWorkPaneModule(
    const ApiWorkPaneModuleInfo & moduleInfo);

/// Handles the registration of node graph module type. Modules can only be registered from within
/// the start function of the module. A module implementation is allowed to register different
/// modules (with distinct module ids).
OCTANEAPI_DECL bool registerNodeGraphModule(
    const ApiNodeGraphModuleInfo & moduleInfo);



/// Handles the registration of a statically linked command module. Statically linked modules
/// can only be registered during static initialization. A module implementation is allowed to
/// register different modules (with distinct module ids).
OCTANEAPI_DECL bool registerStaticCommandModule(
    const ApiCommandModuleInfo & moduleInfo);

/// Handles the registration of a statically linked work pane module. Statically linked modules
/// can only be registered during static initialization. A module implementation is allowed to
/// register different modules (with distinct module ids).
OCTANEAPI_DECL bool registerStaticWorkPaneModule(
    const ApiWorkPaneModuleInfo & moduleInfo);

/// Handles the registration of a statically linked node graph module. Statically linked modules
/// can only be registered during static initialization. A module implementation is allowed to
/// register different modules (with distinct module ids).
OCTANEAPI_DECL bool registerStaticNodeGraphModule(
    const ApiNodeGraphModuleInfo & moduleInfo);

} // namespace Octane



#endif // #ifndef _API_MODULE_H_
