// Copyright (C) 2025 OTOY NZ Ltd.

//////////////////////////////////////////////////////////////////////////////
// WARNING: This code is machine generated. Manual changes will be overridden.
//////////////////////////////////////////////////////////////////////////////

#include "apiprojectmanager_observerclient.h"
#include <cassert>
#include <stdexcept>
#include "octanerenderpasses.h"
#include "octaneimageexport.h"
#include "octaneinfos.h"
#include "octaneids.h"
#include "octanenet.h"
#include "octanemodulesinfo.h"
#include "octanereferenceexport.h"
#include <grpcpp/grpcpp.h>
#include "apiprojectmanager.grpc.pb.h"
#include "stringmgr.h"
#include "convertmatrix.h"
#include "grpcsettings.h"


GRPCSettings & ApiProjectManagerProxy_Observer::getGRPCSettings()
{
    return GRPCSettings::getInstance();
}


