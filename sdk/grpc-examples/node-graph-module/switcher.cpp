// Copyright (C) 2025 OTOY NZ Ltd.

// module includes
//#include "moduleIds.h"
//self
#include "switcher.h"
#include "apinodepininfoclient.h"
#include "apinodepininfohelper.h"

static const OctaneWrap::EnumPinInfo::ValueT gPinTypes[] = 
{
    { Octane::PT_ANIMATION_SETTINGS, "Animation settings" },
    { Octane::PT_BOOL              , "Bool"               },
    { Octane::PT_CAMERA            , "Camera"             },
    { Octane::PT_DISPLACEMENT      , "Displacement"       },
    { Octane::PT_EMISSION          , "Emission"           },
    { Octane::PT_ENUM              , "Enum"               },
    { Octane::PT_ENVIRONMENT       , "Environment"        },
    { Octane::PT_FILM_SETTINGS     , "Film Settings"      },
    { Octane::PT_FLOAT             , "Float"              },
    { Octane::PT_GEOMETRY          , "Geometry"           },
    { Octane::PT_IMAGER            , "Imager"             },
    { Octane::PT_INT               , "Int"                },
    { Octane::PT_KERNEL            , "Kernel"             },
    { Octane::PT_MATERIAL          , "Material"           },
    { Octane::PT_MEDIUM            , "Medium"             },
    { Octane::PT_OBJECTLAYER       , "Object layer"       },
    { Octane::PT_PHASEFUNCTION     , "Phase function"     },
    { Octane::PT_POSTPROCESSING    , "Post processing"    },
    { Octane::PT_POST_VOLUME       , "Post volume"        },
    { Octane::PT_PROJECTION        , "Projection"         },
    { Octane::PT_RENDER_JOB        , "Render job"         },
    { Octane::PT_RENDER_LAYER      , "Render layer"       },
    { Octane::PT_RENDER_PASSES     , "Render passes"      },
    { Octane::PT_RENDERTARGET      , "Render target"      },
    { Octane::PT_STRING            , "String"             },
    { Octane::PT_TEXTURE           , "Texture"            },
    { Octane::PT_TRANSFORM         , "Transform"          },
    { Octane::PT_VOLUME_RAMP       , "Volume ramp"        },
    { Octane::PT_WORK_PANE         , "Work pane"          }
};


enum 
{
    INPUT_LINKER_SELECTED_INPUT   = 0,
    INPUT_LINKER_INPUT_TYPE       = 1,
    INPUT_LINKER_INPUT_COUNT      = 2,
    INPUT_LINKER_DYNAMIC_START_IX = 3
};


static const OctaneWrap::BoolPinInfo testBoolInfo    = OctaneWrap::BoolPinInfo(true);
static const OctaneWrap::IntPinInfo  countIntpinInfo = OctaneWrap::IntPinInfo(2, 0, 100);
static OctaneWrap::IntPinInfo        indexIntpinInfo = OctaneWrap::IntPinInfo(1, 1, 10);
static OctaneWrap::EnumPinInfo       typeEnumPinInfo = OctaneWrap::EnumPinInfo(gPinTypes,
                                                                               ARRAY_WIDTH(gPinTypes),
                                                                               Octane::PT_KERNEL);

static const OctaneWrap::IntXyPinInfo  xyIntpinInfo = OctaneWrap::IntXyPinInfo(0,4);

static const Octane::ApiNodePinInfo kernelInputLinkerInfo(
    const Octane::NodePinType pinType,
    const std::string         &name)
{
    return OctaneWrap::NodePinInfo(pinType, name.c_str());
}


static const Octane::ApiNodePinInfo gStaticInputInfos[] =
{
    // Selected input 
    OctaneWrap::NodePinInfo(Octane::PT_INT,  "Selected input", &indexIntpinInfo, Octane::NT_INT),
    // input type
    OctaneWrap::NodePinInfo(Octane::PT_ENUM, "Input type",     &typeEnumPinInfo, Octane::NT_ENUM),
    // Input count
    OctaneWrap::NodePinInfo(Octane::PT_INT,  "Input count",    &countIntpinInfo, Octane::NT_INT),
};

static Octane::ApiNodePinInfo gOutputInfo = 
    OctaneWrap::NodePinInfo(Octane::PT_KERNEL, "output");

static std::vector<ApiNodePinInfoProxy> gStaticInputInfosProxies;
static ApiNodePinInfoProxy gOutputInfoProxy;

Switcher::Switcher()
{}


Switcher::~Switcher()
{}


void Switcher::onInit()
{
    // set all the static linkers
    const Octane::uint32_2 range = { 0, ARRAY_WIDTH(gStaticInputInfos) - 1 };

    gOutputInfoProxy = ApiNodePinInfoExService::createApiNodePinInfo(gOutputInfo);

    // create the gStaticInputInfos Octane::ApiNodePinInfo on the server and replace the
    // array as an array of proxies to these objects
    if (gStaticInputInfosProxies.empty())
    {
        gStaticInputInfosProxies = ApiNodePinInfoExService::createApiNodePinInfoArray(gStaticInputInfos, ARRAY_WIDTH(gStaticInputInfos));
    }

    graph()->setInputLinkers(gStaticInputInfosProxies.data(), gStaticInputInfosProxies.size(), range);

    // grab the created linker nodes
    graph()->getInputNodes(mInputLinkerNodes);

    // updated selected input count
    updateSelectBounds();
    // updated dynamic inputs
    updateDynamicInputs();
    // create and update output
    updateOutputType();
    // update output connection
    updateOutputConnection();
}


void Switcher::onEvaluate()
{
    grpc::Status status;
    // updating selection bounds 
    ApiNodeProxy temp = mInputLinkerNodes.get(INPUT_LINKER_INPUT_COUNT);
    if (graph()->inputWasChanged(&temp))
    {
        updateSelectBounds();
    }

    // updating output type
    ApiNodeProxy temp2 = mInputLinkerNodes.get(INPUT_LINKER_INPUT_COUNT);
    if (graph()->inputWasChanged(&temp2))
    {
        updateOutputType();
    }

    // updating dynamic inputs
    ApiNodeProxy temp3 = mInputLinkerNodes.get(INPUT_LINKER_INPUT_COUNT);
    ApiNodeProxy temp4 = mInputLinkerNodes.get(INPUT_LINKER_INPUT_TYPE);
    if (graph()->inputWasChanged(&temp3) ||
        graph()->inputWasChanged(&temp4))
    {
        updateDynamicInputs();
    }

    // update output connection
    updateOutputConnection();
}


void Switcher::updateSelectBounds()
{
    int32_t count = 0;
    ApiNodeProxy temp = mInputLinkerNodes.get(INPUT_LINKER_INPUT_COUNT);
    graph()->getInputValue(&temp, count);

    // update the index bounds.
    indexIntpinInfo.setRange(1, count);
    
    // inform api to set new pin info.
    ApiNodeProxy temp2 = mInputLinkerNodes.get(INPUT_LINKER_SELECTED_INPUT);
    graph()->setInputInfo(&temp2,
        gStaticInputInfosProxies[INPUT_LINKER_SELECTED_INPUT]);
}


void Switcher::updateDynamicInputs()
{
    // grab the count value.
    int32_t count = 0;
    ApiNodeProxy temp = mInputLinkerNodes.get(INPUT_LINKER_INPUT_COUNT);
    graph()->getInputValue( &temp, count);
    int32_t type = -1;

    ApiNodeProxy temp2 = mInputLinkerNodes.get(INPUT_LINKER_INPUT_TYPE);
    graph()->getInputValue( &temp2, type);

    // updating the kernel input linkers to the count value
    // filling up the names list first.
    mDynamicLinkerNames.clear();
    for (int32_t i=0; i< count; ++i)
    {
        char buff[32];
        std::snprintf(buff, ARRAY_WIDTH(buff), "Input%d", (i + 1));
        mDynamicLinkerNames.push_back(buff);
    }

    // creating linker info list
    std::vector<ApiNodePinInfo> newInputInfos;
    for (int32_t i=0; i< count; ++i)
    {
        newInputInfos.push_back(kernelInputLinkerInfo(Octane::NodePinType(type), mDynamicLinkerNames[i]));
    }
    gStaticInputInfosProxies = ApiNodePinInfoExService::createApiNodePinInfoArray(newInputInfos.data(), count);

    // inform api to modify the linker list
    Octane::uint32_2 range = { INPUT_LINKER_DYNAMIC_START_IX, 10000 };
    graph()->setInputLinkers(gStaticInputInfosProxies.data(), gStaticInputInfosProxies.size(), range);
    // grab the new/modified linker nodes
    graph()->getInputNodes(mInputLinkerNodes);
}


void Switcher::updateOutputType()
{
    // create a output linker of selected type
    int32_t index = -1;
    ApiNodeProxy temp = mInputLinkerNodes.get(INPUT_LINKER_INPUT_TYPE);
    graph()->getInputValue(&temp, index);

    gOutputInfo.mType = (Octane::NodePinType)index;
    ApiNodePinInfoExService::updateApiNodePinInfo(gOutputInfoProxy, gOutputInfo);

    graph()->setOutputLinkers(&gOutputInfoProxy, 1, uint32_2::make(0, UINT32_MAX));

    //ApiNodePinInfoProxy::create
    // grab the created linker
    graph()->getOutputNodes(mOutLinkerNodes);
}


void Switcher::updateOutputConnection()
{
    grpc::Status status;
    // grab the index and connect the corresponding linker to the output linker
    int32_t index = -1;
    ApiNodeProxy temp = mInputLinkerNodes.get(INPUT_LINKER_SELECTED_INPUT);
    graph()->getInputValue(&temp, index);

    if (index > 0 && index < mInputLinkerNodes.size())
    {
        ApiNodeProxy temp = mInputLinkerNodes.get(index - 1 + INPUT_LINKER_DYNAMIC_START_IX);

        mOutLinkerNodes.get(0).connectTo(
            Octane::P_INPUT,
            &temp,
            true, false);
    }
    else
    {
        mOutLinkerNodes.get(0).connectTo(Octane::P_INPUT, NULL, true, false);
    }
}
