# OctaneRender Module API

This document gives a high-level overview of the module API. The most up-to-date version is always
shipped as part of the latest OctaneRender standalone release. With the module API, developers can
create modules that integrate in the standalone. In other programs modules are usually called
plugins but we prefer modules to avoid confusion with the host application integration plugins for
OctaneRender.

With the module API, the following files are provided:

* Most up-to-date version of this document.
* API header files. All their names start with api (e.g. apiprojectmanager.h).
* API wrapper header and source files. All their names start with octanewrap (e.g.
  octanewrapprojectmanager.h).
* `octane.lib` is provided for linking on Windows.
* Example modules directory.

## Loading modules

Modules are loaded once on startup. Once Octane is running it's not possible anymore to unload
loaded modules or load new modules. Octane searches recursively for shared libraries in the modules
directory. The libraries are recognized by their file extension (.so for Linux, .dll for Windows and
.dylib for macOS). The modules directory can be configured via the preferences dialog. Loading of
modules can be skipped by using the `--no-modules` command line option. (TIP: When Octane seems to
hang at startup, it could be that it crashed because of your module code. You can skip module
loading to verify this).

You can get more info about the module loading by enabling the `moduleLoader` log flag. To enable
this log flag (and other log flags), create a file named `octane_log_flags.txt` in the directory of
the Octane binary. This file should have each log flag on a new line. To print out all the log
flags, add `logFlags` to this file.

## Writing modules

Modules are writing in C++. Each module needs a start and stop function. The start function is
called once when Octane is loaded from the command line. The stop function is called once before
Octane exits. These functions are the entry points for Octane into your code. It's important that
these functions have the correct name and signature and that their symbol is visible in your module
library. You should define these functions as `extern "C"` to avoid name-mangling. The easiest is to
use the macros defined in `apimodule.h`. In the start function, the module should register itself
with Octane. One library (module) is allowed to implement multiple modules, so register can be
called multiple times in the start function. Registration can only be done from within the start
function.

The API is made up of all the header files that start with api. This API is C++ but with some
limitations to avoid problems that can occur at dll boundaries. Because of this, the API isn't
always easy and intuitive to use. That is why we provided C++ convenience wrappers around most of
the api code. If the code is trivial, we don't provide wrappers. All the wrappers are in the files
prefixed with octanewrap. We recommend using the wrappers because it makes life a lot easier. The
wrappers should be compiled as part of the module code. For convenience, we provide
`octanemoduleapi.h` and `octanemoduleapi.cpp` so that you have to include/compile only a single
file.

We try our best to provide good documentation for the API in the header files. If you run into
problems, the forum is the best place to ask for help.

## Module ids

Each module is identified by a unique id. Once an id is assigned to a module, it cannot be re-used
for a different module. Module ids can be registered here (TODO website).

## Module types

There are different types of modules and each type integrates different in Octane: The types are:

* Command module: Modules of this type execute a command. Executing a command is very generic and
  can be everything from saving a file, opening a window, ... . Each command module gets a menu
  entry in the modules menu. When the menu entry is clicked, the command's execute function is
  called. Commands are the most flexible plugins in Octane.
* Work pane module: Work pane modules implement a gui component that can be docked into the Octane
  workspace. Work pane modules have a menu entry in the window menu and when launched they are
  initially created in a separate undocked window. There can be only a single instance of a work
  pane module. Work pane modules are destroyed when a new project is loaded. Users can save the work
  pane module as part of their default layout.

## Threading

The main thread running in OctaneRender is called the "message thread". This is the thread that runs
Octane itself and most of the code is executed by the message thread (user interface, node system
evaluation, ...). Octane will always call your plugin from the main thread unless documented
otherwise. You can only call the API from the main thread except for a few specific classes. This is
documented at the top of those classes (e.g. ApiRenderEngine, ApiLogManager, ...). 

A good practice is to use the macro OCTANE_API_ASSERT_MESSAGE_THREAD defined in octanewrapthread.h
to make sure that you aren't calling the API from the wrong thread.

## Compilation 

If you are using the wrappers, they should be compiled with your module code. Windows and macOS
require some extra things:

* Windows: your module code needs to link against `octane.lib`.
* macOS: you need to specify `-undefined dynamic_lookup` to the linker options.

Compilers we use: VS2019, Xcode 14, gcc 6.3.1.

## Examples

The easiest way to get started with the API is by studying the example modules. You can build the
examples on Windows with the Visual Studio solution `octane-modules.sln`. For Linux and macOS, CMake
files are provided for each example module. You can build all modules by executing the script
`build-modules.sh` The examples we provide are:

* Hello world module: Shows how to register a module, use the log manager and create a window. 
* Work pane module: Shows how to create a work pane module and demonstrates the creation of various
  user interface components.
* Texture commander module: Shows how to use the table component and how to correctly interact with
  the node system and events generated by the node system.

## Warnings

Some warnings and potential pitfalls:

* Your code is not running in a sandbox. A crash in your code will crash Octane.
* Keep an eye on the log output, errors generated by your module will be displayed here.
