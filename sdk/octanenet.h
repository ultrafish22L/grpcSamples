// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_NET_H_
#define _OCTANE_NET_H_


// library includes
#include "octanetypes.h"
#include "octanevectypes.h"



namespace Octane
{

//--------------------------------------------------------------------------------------------------
// Network rendering


/// Represents an IP v4 address. The memory layout of the 4 bytes is defined by the function
/// ipComponent(), i.e.
///     A = (address >> 24) & 0xff 
///     B = (address >> 16) & 0xff
///     C = (address >> 8 ) & 0xff
///     D = (address >> 0 ) & 0xff
/// represents the address A.B.C.D
typedef uint32_t IPv4T;

/// Represents the port address of a socket
typedef uint16_t SocketPortT;

/// max subnet mask length in bits (for IP v4)
#define MAX_SUBNET_LENGTH 32

/// the localhost subnet
const Octane::IPv4T LOCALHOST_SUBNET = 0x7f000000;

/// home sweet home
const Octane::IPv4T LOCALHOST = 0x7f000001;

/// the first user space port (ephemeral port)
const SocketPortT MIN_PORT_NUMBER = 1024;

/// the largest allowd port number
const SocketPortT MAX_PORT_NUMBER = 65535; 

/// The various states a network render daemon can be in.
enum NetDaemonState
{
    /// Daemon is in an unknown state.
    DAEMON_STATE_UNKNOWN,
    /// The render node that is managed by the daemon has an invalid version.
    DAEMON_SLAVE_HAS_INVALID_VERSION,
    /// The render node that is managed by the daemon is not bound to a master.
    DAEMON_SLAVE_UNBOUND,
    /// The render node that is managed by the daemon is bound to another master.
    DAEMON_SLAVE_BOUND_TO_OTHER,

    /// The render node that is managed by the daemon is bound to this master and authenticating.
    DAEMON_SLAVE_AUTHENTICATING,
    /// The render node that is managed by the daemon is bound to this master and running.
    DAEMON_SLAVE_RUNNING,
    /// The render node that is managed by the daemon is bound to this master, but its license got
    /// deactivated and it shut sdown.
    DAEMON_SLAVE_DEACTIVATED,
    /// The render node that is managed by the daemon is bound to this master, but has crashed.
    DAEMON_SLAVE_CRASHED,
};


inline bool daemonSlaveIsBoundToMe(
    const NetDaemonState state)
{
    return (state == DAEMON_SLAVE_AUTHENTICATING) ||
           (state == DAEMON_SLAVE_RUNNING) ||
           (state == DAEMON_SLAVE_DEACTIVATED) ||
           (state == DAEMON_SLAVE_CRASHED);
}


/// Networking transport modes.
enum NetTransportMode
{
    /// The standard TCP/IP stack, which usually uses Ethernet/Wireless.
    NET_MODE_TCP,
};


/// Stores the information about an automatically detected subnetwork.
struct NetInterfaceInfo
{
    /// The IP address of this network adapter.
    IPv4T mAdapterIP;
    /// The network address, i.e. base address of the sub-net this interface/adapter is connected to.
    IPv4T mBaseAddress;
    /// The sub-net mask, defining the range of the sub-net.
    IPv4T mMask;
};



//-------------------------------------------------------------------------------------------------
/// Represents the address of a network endpoint (a.k.a. a socket).
struct SocketAddress
{
    /// the ip address of the socket
    IPv4T       mIpAddress;
    /// the port number of the socket
    SocketPortT mPort;

    /// creates a fresh socket address
    inline SocketAddress(
        const IPv4T       ipAddress = 0,
        const SocketPortT port      = 0);

    /// checks if this address makes sense
    inline bool isValid() const;
};



inline SocketAddress::SocketAddress(
    const IPv4T       ipAddress,
    const SocketPortT port)
:
    mIpAddress(ipAddress),
    mPort(port)
{}


inline bool SocketAddress::isValid() const
{
    return mIpAddress && mPort;
}


inline bool operator==(
    const SocketAddress &sa1,
    const SocketAddress &sa2)
{
    return (sa1.mIpAddress == sa2.mIpAddress) && (sa1.mPort == sa2.mPort);
}


inline bool operator<(
    const SocketAddress &sa1,
    const SocketAddress &sa2)
{
    return (sa1.mIpAddress < sa2.mIpAddress) ||
           ((sa1.mIpAddress == sa2.mIpAddress) && (sa1.mPort < sa2.mPort));
}



//-------------------------------------------------------------------------------------------------
// Stores the current status of the net render master.
struct NetRenderStatus
{
    /// The number of active render nodes.
    unsigned int mNetSlaveCount;
    /// The number of active render nodes that are currently updating for the most recent change.
    unsigned int mUpdatingNetSlaveCount;
    /// The number of active render nodes that have finished updating for the most recent change. If
    /// mUpdatedNetSlaveCount >= mUpdatingNetSlaveCount, we have finished updating and mPendingSize
    /// should be 0.
    unsigned int mUpdatedNetSlaveCount;
    /// The number of bytes that still need to be sent to the render nodes for the most recent
    /// change.
    size_t       mPendingSize;
    /// The total number of bytes that need to be sent for the most recent change.
    size_t       mTotalSize;
    /// The total number of GPUs available on all active render nodes.
    unsigned int mNetGpuCount;
    /// The number of GPUs available on render render nodes that are in an updated state.
    unsigned int mInUseNetGpuCount;
    /// Tells if the current scene can be rendered by net render nodes
    bool         mCanRenderUsingRenderNodes;

    /// Resets and nullifies everything.
    inline void clear()
    {
        mNetSlaveCount = 0;
        mUpdatingNetSlaveCount = 0;
        mUpdatedNetSlaveCount = 0;
        mPendingSize = 0;
        mTotalSize = 0;
        mNetGpuCount = 0;
        mInUseNetGpuCount = 0;
        mCanRenderUsingRenderNodes = false;
    }
};



//-------------------------------------------------------------------------------------------------
// Stores information about a network rendering daemon that provides functionality to remotely
// start/stop network render nodes.
struct NetDaemonInfo
{
    /// The IP address of the daemon.
    IPv4T          mIpAddress;
    /// The name of the daemon.
    const char     *mName;
    /// The state it is in right now.
    NetDaemonState mState;
    /// The number of GPUs the daemon can use.
    uint32_t       mGpuCount;
    /// The Octane version of the render node.
    uint32_t       mSlaveVersion;
    /// The address of the master bound (working) for this daemon.
    SocketAddress  mBoundMasterAddress;
    /// The nick name of the master bound (working) for this daemon or "" if the daemon is currently
    /// not bound.
    const char     *mBoundMasterName;
};



//-------------------------------------------------------------------------------------------------
// The network configuration parameters.
struct NetRenderSettings 
{
    /// Network port on which the net render master listens for render node connections.
    /// Valid port ranges [1025, 65535] -- a value of 0 means Octane chooses the master port
    SocketPortT       mMasterPort;
    /// Network port on which net render daemons listen for search messages of masters.
    /// Valid port ranges [1025, 65535]
    SocketPortT       mDaemonPort;
    /// Array of IP addresses of the adapters that should scan their connected subnet for daemons.
    /// The array pointer can be NULL.
    const IPv4T       *mDaemonSearchAdapters;
    /// The number of entries in the array of mDaemonSearchAdapters.
    uint32_t          mDaemonSearchAdapterCount;
    /// Array of dedicated addresses to scan for daemons. Each entry can either be a host name or an
    /// IP address. The pointer can be NULL.
    const char *const *mDaemonSearchAdresses;
    /// The number of entries in the array of mDaemonAdresses.
    uint32_t          mDaemonSearchAddressCount;
};



//-------------------------------------------------------------------------------------------------
// Various util functions

/// Returns the n-th component of an IPv4 address. The component index ranges from 0 to 3,
/// representing an address in the form of
///     c0.c1.c2.c3.
inline uint8_t ipComponent(
    const IPv4T        address,
    const unsigned int componentIx)
{
    return (address >> ((3 - componentIx) * 8)) & 0xff;
}


/// Sets the n-th component of an IPv4 address.
inline void setIpComponent(
    IPv4T              &address,
    const unsigned int componentIx,
    const uint8_t      value)
{
    const int shift = (3 - componentIx) * 8;
    address = ((IPv4T)value << shift) |
              (address & ~((IPv4T)0xff << shift));
}


/// Creates an IPv4 address from 4 discrete components.
inline Octane::IPv4T setIp(
    const uint8_t a,
    const uint8_t b,
    const uint8_t c,
    const uint8_t d)
{
    return ((a << 24) | (b << 16) | (c << 8) | (d << 0));
}


/// Reverse the order of the bytes in place.
OCTANEAPI_DECL void reverseByteOrder(
    uint8_t      *bytes,
    const size_t length);

/// Counts the trailing zeros in an IP address.
OCTANEAPI_DECL int countTrailingZeros(
    const Octane::IPv4T address);

/// Returns the maximum possible number of hosts on the subnet network interface.
///
///@param[in] subnetInterface
///     the interface information of a subnet
///@return
///     the count of hosts
OCTANEAPI_DECL size_t maxHosts(
    const Octane::NetInterfaceInfo &subnetInterface);

} // namespace Octane



#endif // #ifndef _OCTANE_NET_H_
