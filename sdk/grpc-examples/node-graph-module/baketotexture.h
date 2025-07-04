// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _MODULE_NODE_GRAPH_BAKE_TO_TEXTURE_
#define _MODULE_NODE_GRAPH_BAKE_TO_TEXTURE_   1


// API includes
#include "octanegrpcwrappers.h"
// 
#include "apinodearrayclient.h"
#include "apiimageclient.h"
#include "apinodeclient.h"

class BakeToTexture : public OctaneWrap::NodeGraphModule
{
public:

    /// Constructor
    BakeToTexture();

    /// Destructor
    virtual ~BakeToTexture();

    //--- Implementation for OctaneWrap::NodeGraphModule ---

    virtual void onInit() override;

    virtual void onEvaluate() override;

private:

    /// Created input linker node list
    ApiNodeArrayProxy       mInputLinkerNodes;
    /// Created output linker node list
    ApiNodeArrayProxy       mOutLinkerNodes;
    /// To handle the memory of the dynamic inputs name. 
    std::vector<std::string>   mDynamicLinkerNames;
    /// Icon of this node graph
    ApiImageProxy           mIconImage;
    /// internal image node which will be connected to the output linker node.
    ApiNodeProxy            mImageNode;
};



#endif // _MODULE_NODE_GRAPH_BAKE_TO_TEXTURE_