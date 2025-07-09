// Copyright (C) 2025 OTOY NZ Ltd.

// system includes
#include <cstring>
// myself
#include "baketotexture.h"
#include "apirenderengineclient.h"
#include "apinodepininfohelper.h"
#include "grpcapinodeinfo.h"
#include "apinodepininfoclient.h"

static float rgbToFloat(
    const float red,
    const float green,
    const float blue)
{
    return 0.2126f * red + 0.7152f * green + 0.0722f * blue;
}


static const OctaneWrap::EnumPinInfo::ValueT gOutputTypes[] = 
{
    { Octane::IMAGE_TYPE_LDR_RGBA, "LDR RGB"       },
    { Octane::IMAGE_TYPE_LDR_MONO, "LDR greyscale" },
    { Octane::IMAGE_TYPE_HDR_RGBA, "HDR RGB"       },
    { Octane::IMAGE_TYPE_HDR_MONO, "HDR greyscale" },
};


static OctaneWrap::FloatPinInfo objectPinInfo     = OctaneWrap::FloatPinInfo(1.f);
static OctaneWrap::IntXyPinInfo resolutionPinInfo = OctaneWrap::IntXyPinInfo(1024, 1024);
static OctaneWrap::IntPinInfo   samplesPinInfo    = 
    OctaneWrap::IntPinInfo(32,
                           1,
                           1000000,
                           OctaneWrap::IntPinInfo::ALLOW_LOG | OctaneWrap::IntPinInfo::DEFAULT_IS_LOG,
                           1,
                           100000);

static OctaneWrap::EnumPinInfo outputTypePinInfo =
    OctaneWrap::EnumPinInfo(gOutputTypes, ARRAY_WIDTH(gOutputTypes), Octane::IMAGE_TYPE_LDR_MONO);

enum 
{
    INPUT_LINKER_RESOLUTION  = 0,
    INPUT_LINKER_MAX_SAMPLES = 1,
    INPUT_LINKER_OBJECT_SIZE = 2,
    INPUT_LINKER_OUTPUT_TYPE = 3,
    INPUT_LINKER_INPUT_NODE  = 4,
};


static const Octane::ApiNodePinInfo gStaticInputInfos[] =
{
    OctaneWrap::NodePinInfo(Octane::PT_INT,     "Resolution",  &resolutionPinInfo, Octane::NT_IMAGE_RESOLUTION),
    OctaneWrap::NodePinInfo(Octane::PT_INT,     "Resolution",  &resolutionPinInfo, Octane::NT_IMAGE_RESOLUTION),
    OctaneWrap::NodePinInfo(Octane::PT_INT,     "Max samples", &samplesPinInfo,    Octane::NT_INT),
    OctaneWrap::NodePinInfo(Octane::PT_FLOAT,   "Object size", &objectPinInfo,     Octane::NT_FLOAT),
    OctaneWrap::NodePinInfo(Octane::PT_ENUM,    "Output type", &outputTypePinInfo, Octane::NT_ENUM),
    OctaneWrap::NodePinInfo(Octane::PT_TEXTURE, "Input")
};

static Octane::ApiNodePinInfo gOutputInfo = 
    OctaneWrap::NodePinInfo(Octane::PT_TEXTURE, "output", Octane::NT_TEX_FLOATIMAGE);


BakeToTexture::BakeToTexture()
//:
    //mImageNode(NULL)
{}


BakeToTexture::~BakeToTexture()
{}


template<class T>
void assignResultBufferToImageNode(
       const T *const        srcBuffer,
       const Octane::int32_2 resolution,
       Octane::ImageType     imageType,
       ApiNodeProxy *        imageNode)
{
    const uint8_t  channels = 4;
    uint64_t       destBufSize     = 0;
    T              *destBuffer  = NULL;
    if (imageType == Octane::IMAGE_TYPE_HDR_MONO || imageType == Octane::IMAGE_TYPE_LDR_MONO)
    {
        destBufSize   = resolution.x * resolution.y;
        destBuffer = new T[destBufSize];

        // loop through bottom to flip Y
        for (int32_t row = resolution.y - 1; row >=0; --row)
        {
            const uint64_t startDestBufIx = (uint64_t)((resolution.y - 1) - row) * resolution.x;
            const uint64_t startSrcBufIx  = ((uint64_t)row * resolution.x) * channels;
            const uint64_t endSrcBufIx    = startSrcBufIx + resolution.x * channels;

            // convert and copy the row
            for (int32_t colIx = startSrcBufIx, destBufIx = startDestBufIx;
                colIx < endSrcBufIx;
                colIx += channels, ++destBufIx)
            {
                destBuffer[destBufIx] = rgbToFloat(srcBuffer[colIx + 0],
                                                   srcBuffer[colIx + 1],
                                                   srcBuffer[colIx + 2]);
            }
        }
    }
    else if (imageType == Octane::IMAGE_TYPE_HDR_RGBA || imageType == Octane::IMAGE_TYPE_LDR_RGBA)
    {
        const uint32_t lineLength = resolution.x * channels;
        destBufSize               = (uint64_t)resolution.y * lineLength;
        destBuffer                = new T[destBufSize];

        // looping thorough bottom to flip Y
        for (int32_t row = resolution.y - 1; row >=0; --row)
        {
            // copy the row
            const uint64_t destBufIx = (uint64_t)((resolution.y - 1) - row) * lineLength;
            const uint64_t srcBufIx  = (uint64_t)row * lineLength;
            memcpy(destBuffer + destBufIx, srcBuffer + srcBufIx, lineLength * sizeof(T));
        }
    }

    // assign buffer and other infos.
    uint32_t test = 0;
    imageNode->set(Octane::A_FILENAME, "", false);
    imageNode->set(Octane::A_PACKAGE, "", false);
    imageNode->set(Octane::A_BUFFER, (unsigned char*)destBuffer, destBufSize * sizeof(T), false);
    imageNode->set(Octane::A_SIZE, resolution, false);
    imageNode->set(Octane::A_TYPE, imageType, true);

    // clear the buffer
    delete [] destBuffer;

}


void BakeToTexture::onInit()
{
    // set all the static linkers
    const Octane::uint32_2 range = { 0, ARRAY_WIDTH(gStaticInputInfos) - 1 };

    // create the gStaticInputInfos Octane::ApiNodePinInfo on the server and replace the
    // array as an array of proxies to these objects
    std::vector<ApiNodePinInfoProxy> nodePinInfoArray = 
        ApiNodePinInfoExService::createApiNodePinInfoArray(gStaticInputInfos, ARRAY_WIDTH(gStaticInputInfos));

    ApiNodePinInfoProxy outputInfoProxy = ApiNodePinInfoExService::createApiNodePinInfo(gOutputInfo);

#ifdef NODE_GRAPH_EXAMPLE
    graph()->setInputLinkers(nodePinInfoArray.data(), nodePinInfoArray.size(), range, status);
    graph()->setOutputLinkers(&outputInfoProxy, 1, uint32_2::make(0, UINT32_MAX),status);
#endif
    // grab the created linker nodes
    graph()->getInputNodes(mInputLinkerNodes);
    graph()->getOutputNodes(mOutLinkerNodes);
}


void BakeToTexture::onEvaluate()
{
    if (!(mInputLinkerNodes.get(INPUT_LINKER_INPUT_NODE).inputNode(Octane::P_INPUT, false).isNull()))
    {
        // get the resolution
        Octane::int32_2 resolution = Octane::int32_2::make(1024, 1024);
        ApiNodeProxy temp = mInputLinkerNodes.get(INPUT_LINKER_RESOLUTION);
        graph()->getInputValue(&temp, resolution);

        // get the max samples
        int32_t maxSamples = 32;
        ApiNodeProxy temp2 = mInputLinkerNodes.get(INPUT_LINKER_MAX_SAMPLES);
        graph()->getInputValue(&temp2, maxSamples); 

        float objectSize = 1.0f;
        ApiNodeProxy temp3 = mInputLinkerNodes.get(INPUT_LINKER_OBJECT_SIZE);
        graph()->getInputValue(&temp3, objectSize);

        int32_t outputType = Octane::IMAGE_TYPE_LDR_MONO;
        ApiNodeProxy temp4 = mInputLinkerNodes.get(INPUT_LINKER_OUTPUT_TYPE);
        graph()->getInputValue(&temp4, outputType);

        // create a texture node
        if (!mImageNode.isNull() || mImageNode.info().mType != outputType)
        {
            if (!mImageNode.isNull())
            { 
                mImageNode.destroy();
            }
            // finding the nodetype to create texture node
            Octane::NodeType nodeType;
            if (outputType == Octane::IMAGE_TYPE_LDR_MONO || outputType == Octane::IMAGE_TYPE_HDR_MONO)
            {
                nodeType = Octane::NT_TEX_FLOATIMAGE;
            }
            else
            {
                nodeType = Octane::NT_TEX_IMAGE;
            }
            mImageNode = ApiNodeProxy::create(nodeType, *graph(), true);
        }

        // preview render
        const uint8_t  channels = 4;
        const uint64_t bufSize  = (uint64_t)resolution.x * resolution.y * channels;
        if (outputType == Octane::IMAGE_TYPE_LDR_RGBA || outputType == Octane::IMAGE_TYPE_LDR_MONO)
        {
            unsigned char *resultBuffer = new unsigned char[bufSize];
            ApiNodeProxy temp5 = mInputLinkerNodes.get(INPUT_LINKER_OUTPUT_TYPE).inputNode(Octane::P_INPUT, false);
            ApiRenderEngineProxy::previewMaterial(&temp5,
                                                     resolution.x,
                                                     resolution.y,
                                                     maxSamples,
                                                     objectSize,
                                                     Octane::PREVIEW_PLANE,
                                                     resultBuffer
                                                     );

            // assign to output linker
            assignResultBufferToImageNode<unsigned char>(resultBuffer, resolution, (Octane::ImageType)outputType, &mImageNode);
            delete [] resultBuffer;
        }
        else
        {
            float *resultBuffer = new float[bufSize];
            ApiNodeProxy temp6 = mInputLinkerNodes.get(INPUT_LINKER_INPUT_NODE).inputNode(Octane::P_INPUT, false);
            ApiRenderEngineProxy::previewMaterialHdr(&temp6,
                                                        resolution.x,
                                                        resolution.y,
                                                        maxSamples,
                                                        objectSize,
                                                        Octane::PREVIEW_PLANE,
                                                        resultBuffer,
                                                        false
                                                        );

            assignResultBufferToImageNode<float>(resultBuffer, resolution, (Octane::ImageType)outputType, &mImageNode);
            delete [] resultBuffer;
        }

        // connect the created texture node to the output linker
        mOutLinkerNodes.get(0).connectTo(Octane::P_INPUT, &mImageNode, true, false);
    }
    else
    {
        if (!mImageNode.isNull())
        {
            mImageNode.destroy();
            //mImageNode = NULL;
        }
    }
}

