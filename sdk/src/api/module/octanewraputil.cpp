// Copyright (C) 2026 OTOY NZ Ltd.

// system includes
#include <cassert>
#include <cstdarg>
#include <cstdio>
// api includes
#include "apilogmanager.h"
// myself
#include "octanewraputil.h"


void OctaneWrap::__debugAssert(
    const char *filename,
    const int  lineNb,
    const bool condition,
    const char *fmt,
    ...)
{
    if (!condition)
    {

        va_list args;
        va_start(args, fmt);
        char message[1024];
        vsnprintf(message, 1024, fmt, args);
        va_end(args);
        
        Octane::ApiLogManager::logFmt("ASSERT: '%s' (%s:%d)", message, filename, lineNb);
        assert(false);
    }
}
