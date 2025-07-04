// Copyright (C) 2025 OTOY NZ Ltd.

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
    const GRPCApiMouseEventData &event) 
{}


void MouseListener::mouseEnter(
    const GRPCApiMouseEventData &event)
{}


void MouseListener::mouseExit(
    const GRPCApiMouseEventData &event)
{}


void MouseListener::mouseDown(
    const GRPCApiMouseEventData &event)
{}


void MouseListener::mouseDrag(
    const GRPCApiMouseEventData &event)
{}


void MouseListener::mouseUp(
    const GRPCApiMouseEventData &event)
{}


void MouseListener::mouseDoubleClick(
    const GRPCApiMouseEventData &event)
{}


void MouseListener::mouseWheelMove (
    const GRPCApiMouseEventData        &event,
    const Octane::ApiMouseWheelDetails &wheel)
{}
