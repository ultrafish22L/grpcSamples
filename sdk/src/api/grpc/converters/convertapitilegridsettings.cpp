// Copyright (C) 2025 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertapitilegridsettings.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apitilegrid.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apitilegrid.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
class ApiNodeInfoProxy
{
    //stub
};
#endif

void ApiTileGridSettingsConverter::convert(
    const octaneapi::ApiTileGridSettings & in,
    Octane::ApiTileGridSettings & out)
{

    // Found structure 1 ApiTileGridSettings
    // from proto type = const octaneapi::ApiTileGridSettings &,
        //to octane type = Octane::ApiTileGridSettings &
    // list out parameters
    //cl=ApiTileGridSettings, field.mName = parent field.mType = const char *, protoType=string
    out.mParent =  (char*)StringManager::getInstance().addString(in.parent());
    //cl=ApiTileGridSettings, field.mName = gridSize field.mType = Octane::uint32_2, protoType=uint32_2
    out.mGridSize = {
       in.gridsize().x(),
       in.gridsize().y() };
    //cl=ApiTileGridSettings, field.mName = gridFlipV field.mType = bool, protoType=bool
    out.mGridFlipV = in.gridflipv();////simple 3////
    //cl=ApiTileGridSettings, field.mName = start field.mType = uint32_t, protoType=uint32
    out.mStart = in.start();////simple 3////
    // all fields resolved OK;
}


void ApiTileGridSettingsConverter::convert(
    const Octane::ApiTileGridSettings & in,
    octaneapi::ApiTileGridSettings & out)
{

    // Found structure 1 ApiTileGridSettings
    // from octane type = const Octane::ApiTileGridSettings &,
        //to proto type = octaneapi::ApiTileGridSettings &
    // list out parameters

    std::string * parentStr = new std::string();////approved//// 
    *parentStr = StringManager::checkString(in.mParent);
    out.set_allocated_parent(parentStr);

    octaneapi::uint32_2 * gridSizeOut = new octaneapi::uint32_2;////approved////
    gridSizeOut->set_x(in.mGridSize.x);
    gridSizeOut->set_y(in.mGridSize.y);
    out.set_allocated_gridsize(gridSizeOut);
    out.set_gridflipv(in.mGridFlipV);////simple 4b////
    out.set_start(in.mStart);////simple 4b////
    // all fields resolved OK;
}


#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
