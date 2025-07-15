#pragma once

/**
 * Windows Header Compatibility Layer
 * 
 * This header ensures proper Windows header inclusion order and resolves
 * common conflicts between Windows headers, OpenGL headers, and gRPC headers.
 * 
 * Include this header BEFORE any other headers that might use Windows types.
 */

#ifdef _WIN32

// Define Windows version requirements
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0601  // Windows 7 minimum
#endif

#ifndef WINVER
    #define WINVER 0x0601        // Windows 7 minimum
#endif

// Reduce Windows header bloat
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

// Prevent min/max macro conflicts
#ifndef NOMINMAX
    #define NOMINMAX
#endif

// Prevent winsock conflicts
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

// Include core Windows headers
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Undefine problematic macros that conflict with OpenGL/gRPC
#ifdef APIENTRY
    #undef APIENTRY
#endif

#ifdef WINGDIAPI
    #undef WINGDIAPI
#endif

// Ensure LONGLONG is available for gRPC
#ifndef LONGLONG
    typedef __int64 LONGLONG;
#endif

#endif // _WIN32