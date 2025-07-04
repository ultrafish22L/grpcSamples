// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _MODULE_NODE_GRAPH_SWITCHER
#define _MODULE_NODE_GRAPH_SWITCHER   1


// API includes
#include "octanegrpcwrappers.h"
#include "apinodearrayclient.h"


class Switcher : public OctaneWrap::NodeGraphModule
{
public:

    /// Default constructor.
    Switcher();

    /// Destructor
    virtual ~Switcher();

    //--- Implementation for OctaneWrap::NodeGraphModule ---

    virtual void onInit() override;

    virtual void onEvaluate() override;

private:

    /// Created input linker node list
    ApiNodeArrayProxy         mInputLinkerNodes;
    /// Created output linker node list
    ApiNodeArrayProxy         mOutLinkerNodes;
    /// To handle the memory of the dynamic inputs name. 
    std::vector<std::string>     mDynamicLinkerNames;


    /// Function to update the input selection linker bounds.
    void updateSelectBounds();

    /// Function to update dynamic input linker nodes.
    void updateDynamicInputs();

    /// Function to update output linker.
    void updateOutputType();

    /// Function to update the connection
    void updateOutputConnection();
};


#endif // _MODULE_NODE_GRAPH_SWITCHER