// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _OCTANE_WRAP_CHANGE_MANANGER_H_
#define _OCTANE_WRAP_CHANGE_MANANGER_H_ 1

#include "apichangemanager.h"
#include "apichangemanagerclient.h"
#include "grpcchangeevents.h"


namespace OctaneWrap
{

    //--------------------------------------------------------------------------------------------------
    /// Interface for observers of the node system.
    struct NodeItemObserver : public OctaneGRPC::GRPCChangeObserver
    {
    public:

        NodeItemObserver();

        virtual void onNodeItemChange(
            const OctaneGRPC::GRPCChangeManagerChangeEvent &event) =0;
    };



    //--------------------------------------------------------------------------------------------------
    /// Interface for time observers.
    struct TimeObserver : public OctaneGRPC::GRPCChangeTimeObserver
    {
    public:

        TimeObserver();

        virtual void onTimeChanged(
            const OctaneGRPC::GRPCChangeManagerTimeChangeEvent &event) =0;
    };

} // namespace OctaneWrap


#endif // #ifndef _OCTANE_WRAP_CHANGE_MANANGER_H_
