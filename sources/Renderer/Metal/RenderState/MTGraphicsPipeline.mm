/*
 * MTGraphicsPipeline.mm
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "MTGraphicsPipeline.h"
#include "../../CheckedCast.h"
#include "../Shader/MTShaderProgram.h"
#include "../MTTypes.h"
#include <LLGL/GraphicsPipelineFlags.h>
#include <string>
#include <stdexcept>


namespace LLGL
{


static void MTThrowIfFailed(NSError* error, const char* info)
{
    if (error != nullptr)
    {
        std::string s = info;
        
        NSString* errorMsg = [error localizedDescription];
        s += [errorMsg cStringUsingEncoding:NSUTF8StringEncoding];
        
        throw std::runtime_error(s);
    }
}

static BOOL MTBoolean(bool value)
{
    return (value ? YES : NO);
}

static MTLPrimitiveTopologyClass GetMTLPrimitiveTopologyClass(const PrimitiveTopology topology)
{
    switch (topology)
    {
        case PrimitiveTopology::PointList:      return MTLPrimitiveTopologyClassPoint;
        case PrimitiveTopology::LineList:       /* pass */
        case PrimitiveTopology::LineStrip:      return MTLPrimitiveTopologyClassLine;
        case PrimitiveTopology::TriangleList:   /* pass */
        case PrimitiveTopology::TriangleStrip:  return MTLPrimitiveTopologyClassTriangle;
        default:                                return MTLPrimitiveTopologyClassUnspecified;
    }
}

MTGraphicsPipeline::MTGraphicsPipeline(id<MTLDevice> device, const GraphicsPipelineDescriptor& desc)
{
    /* Get native shader functions */
    auto shaderProgramMT = LLGL_CAST(MTShaderProgram*, desc.shaderProgram);
    if (!shaderProgramMT)
        throw std::invalid_argument("failed to create graphics pipeline due to missing shader program");
    
    /* Convert standalone parameters */
    primitiveType_ = MTTypes::Map(desc.primitiveTopology);

    /* Create render pipeline state */
    MTLRenderPipelineDescriptor* renderPipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
    {
        renderPipelineDesc.vertexDescriptor         = shaderProgramMT->GetMTLVertexDesc();
        renderPipelineDesc.alphaToCoverageEnabled   = MTBoolean(desc.blend.alphaToCoverageEnabled);
        renderPipelineDesc.alphaToOneEnabled        = NO;
        renderPipelineDesc.fragmentFunction         = shaderProgramMT->GetFragmentMTLFunction();
        renderPipelineDesc.vertexFunction           = shaderProgramMT->GetVertexMTLFunction();
        renderPipelineDesc.inputPrimitiveTopology   = GetMTLPrimitiveTopologyClass(desc.primitiveTopology);
        
        //TODO...
        renderPipelineDesc.colorAttachments[0].pixelFormat  = MTLPixelFormatBGRA8Unorm_sRGB;
        renderPipelineDesc.depthAttachmentPixelFormat       = MTLPixelFormatDepth32Float_Stencil8;
        renderPipelineDesc.stencilAttachmentPixelFormat     = MTLPixelFormatDepth32Float_Stencil8;
        
        if (shaderProgramMT->GetFragmentMTLFunction() != nil)
        {
            renderPipelineDesc.rasterizationEnabled = YES;
            renderPipelineDesc.sampleCount          = desc.rasterizer.multiSampling.SampleCount();
        }
        else
       	{
            renderPipelineDesc.rasterizationEnabled = NO;
        }
    }
    NSError* error = nullptr;
    renderPipelineState_ = [device newRenderPipelineStateWithDescriptor:renderPipelineDesc error:&error];
    
    if (!renderPipelineState_)
        MTThrowIfFailed(error, "creating Metal render pipeline state failed");
    
    /* Create depth-stencil state */
    MTLDepthStencilDescriptor* depthStencilDesc = [[MTLDepthStencilDescriptor alloc] init];
    {
        /* Convert depth descriptor */
        depthStencilDesc.depthWriteEnabled      = MTBoolean(desc.depth.writeEnabled);
        depthStencilDesc.depthCompareFunction   = (desc.depth.testEnabled ? MTTypes::Map(desc.depth.compareOp) : MTLCompareFunctionAlways);
        
        /* Convert stencil descriptor */
        //TODO...
    }
    depthStencilState_ = [device newDepthStencilStateWithDescriptor:depthStencilDesc];
}

void MTGraphicsPipeline::Bind(id<MTLRenderCommandEncoder> cmdEncoder)
{
    [cmdEncoder setRenderPipelineState:renderPipelineState_];
    [cmdEncoder setDepthStencilState:depthStencilState_];
}


} // /namespace LLGL



// ================================================================================