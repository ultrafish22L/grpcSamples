// Copyright (C) 2026 OTOY NZ Ltd.

// myself
#include "octanegrpcwrapmouselistener.h"
//application includes
#include "apimouselistener.h"
 

using namespace OctaneWrap;


MouseListener::MouseListener()
{}


MouseListener::~MouseListener()
{}


void MouseListener::mouseMove(
    const OctaneGRPC::GRPCApiMouseEventData &event) 
{}


void MouseListener::mouseEnter(
    const OctaneGRPC::GRPCApiMouseEventData &event)
{}


void MouseListener::mouseExit(
    const OctaneGRPC::GRPCApiMouseEventData &event)
{}


void MouseListener::mouseDown(
    const OctaneGRPC::GRPCApiMouseEventData &event)
{}


void MouseListener::mouseDrag(
    const OctaneGRPC::GRPCApiMouseEventData &event)
{}


void MouseListener::mouseUp(
    const OctaneGRPC::GRPCApiMouseEventData &event)
{}


void MouseListener::mouseDoubleClick(
    const OctaneGRPC::GRPCApiMouseEventData &event)
{}


void MouseListener::mouseWheelMove (
    const OctaneGRPC::GRPCApiMouseEventData        &event,
    const Octane::ApiMouseWheelDetails &wheel)
{}
