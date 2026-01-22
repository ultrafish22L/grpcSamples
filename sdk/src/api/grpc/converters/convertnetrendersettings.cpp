// Copyright (C) 2026 OTOY NZ Ltd.

#if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
// myself
#include "convertnetrendersettings.h"
// application includes
#include "stringmgr.h"
#include "objectmgr.h"
#ifdef NO_PCH
#include "apinetrendermanager.grpc.pb.h"
#endif // #ifdef NO_PCH
#include "apinetrendermanager.h"

#if !defined(OCTANE_STANDALONE) && !defined(OCTANE_DLLEXPORT)
#include "grpcapinodeinfo.h"
#else 
struct ApiNodeInfoProxy
{
    //stub
};
#endif

namespace OctaneGRPC
{

void NetRenderSettingsConverter::convert(
    const octaneapi::NetRenderSettings & in,
    Octane::NetRenderSettings & out)
{

    // Found structure 1 NetRenderSettings
    // from proto type = const octaneapi::NetRenderSettings &,
        //to octane type = Octane::NetRenderSettings &
    // list out parameters
    //cl=NetRenderSettings, field.mName = masterPort field.mType = Octane::SocketPortT, protoType=uint32
    out.mMasterPort = in.masterport();////SocketPortT////
    //cl=NetRenderSettings, field.mName = daemonPort field.mType = Octane::SocketPortT, protoType=uint32
    out.mDaemonPort = in.daemonport();////SocketPortT////
    //cl=NetRenderSettings, field.mName = daemonSearchAdapters field.mType = const Octane::IPv4T *, protoType=UintArrayT
    Octane::IPv4T * daemonSearchAdaptersTemp = new Octane::IPv4T[in.daemonsearchadapters().data_size()];////222////
    // Store the array for auto deletion. The pointer returned to the caller will be valid until the next time this function is called.
    ObjectStore::getInstance().addPointer<Octane::IPv4T>("daemonSearchAdapters", daemonSearchAdaptersTemp);
    for(int h = 0; h < in.daemonsearchadapters().data_size(); h++)
    {
         daemonSearchAdaptersTemp[h] = static_cast<Octane::IPv4T>(in.daemonsearchadapters().data(h));
    }
    // memory leak
    out.mDaemonSearchAdapters = daemonSearchAdaptersTemp;
    //cl=NetRenderSettings, field.mName = daemonSearchAdapterCount field.mType = uint32_t, protoType=uint32
    out.mDaemonSearchAdapterCount = in.daemonsearchadaptercount();////simple 3////
    //cl=NetRenderSettings, field.mName = daemonSearchAdresses field.mType = const char *const *, protoType=StringArrayT
    char * * daemonSearchAdressesTemp = new char *[in.daemonsearchadresses().data_size()];////222////
    // Store the array for auto deletion. The pointer returned to the caller will be valid until the next time this function is called.
    ObjectStore::getInstance().addPointer<char*>("daemonSearchAdresses", daemonSearchAdressesTemp);
    for(int h = 0; h < in.daemonsearchadresses().data_size(); h++)
    {
         daemonSearchAdressesTemp[h] = (char*)StringManager::getInstance().addString(in.daemonsearchadresses().data(h));
    }
    // memory leak
    out.mDaemonSearchAdresses = daemonSearchAdressesTemp;
    //cl=NetRenderSettings, field.mName = daemonSearchAddressCount field.mType = uint32_t, protoType=uint32
    out.mDaemonSearchAddressCount = in.daemonsearchaddresscount();////simple 3////
    // all fields resolved OK;
}


void NetRenderSettingsConverter::convert(
    const Octane::NetRenderSettings & in,
    octaneapi::NetRenderSettings & out)
{

    // Found structure 1 NetRenderSettings
    // from octane type = const Octane::NetRenderSettings &,
        //to proto type = octaneapi::NetRenderSettings &
    // list out parameters
    out.set_masterport(in.mMasterPort);////SocketPortT//
    out.set_daemonport(in.mDaemonPort);////SocketPortT//
   // 1D array
    octaneapi::UintArrayT * daemonSearchAdaptersOut = new octaneapi::UintArrayT;////approved////
    for(uint32_t h = 0; h < in.mDaemonSearchAdapterCount; h++)
    {
        daemonSearchAdaptersOut->add_data(in.mDaemonSearchAdapters[h]);
    }
    out.set_allocated_daemonsearchadapters(daemonSearchAdaptersOut);
    out.set_daemonsearchadaptercount(in.mDaemonSearchAdapterCount);////simple 4b////
   // 1D array
    octaneapi::StringArrayT * daemonSearchAdressesOut = new octaneapi::StringArrayT;////approved////
    for(uint32_t h = 0; h < in.mDaemonSearchAddressCount; h++)
    {
        daemonSearchAdressesOut->add_data(in.mDaemonSearchAdresses[h]);
    }
    out.set_allocated_daemonsearchadresses(daemonSearchAdressesOut);
    out.set_daemonsearchaddresscount(in.mDaemonSearchAddressCount);////simple 4b////
    // all fields resolved OK;
}


} // namespace octaneGRPC
#endif // #if !defined(OCTANE_DEMO_VERSION) && !defined(OCTANE_NET_SLAVE)
