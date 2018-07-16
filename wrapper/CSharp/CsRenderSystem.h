/*
 * CsRenderSystem.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#pragma once

#include <vcclr.h>
#include <vector>
#include <LLGL/RenderSystem.h>
#include "CsRenderSystemFlags.h"
#include "CsRenderContext.h"
#include "CsRenderContextFlags.h"

#using <System.dll>
#using <System.Core.dll>
#using <System.Runtime.InteropServices.dll>


using namespace System;
using namespace System::Runtime::InteropServices;


namespace LHermanns
{

namespace LLGL
{


public ref class RenderSystem
{

    public:

        /* ----- Common ----- */

        ~RenderSystem();

        static Collections::Generic::List<String^>^ FindModules();

        static RenderSystem^ Load(String^ moduleName);

        static void Unload(RenderSystem^ renderSystem);

        property int ID
        {
            int get();
        }

        property String^ Name
        {
            String^ get();
        }

        property RendererInfo^ Info
        {
            RendererInfo^ get();
        }

        #if 0

        property RenderingCapabilities^ RenderingCaps
        {
            RenderingCapabilities^ get();
        }

        property RenderSystemConfiguration^ Configuration
        {
            RenderSystemConfiguration^ get();
            void set(RenderSystemConfiguration^ config);
        }

        #endif

        /* ----- Render Context ----- */

        RenderContext^ CreateRenderContext(RenderContextDescriptor^ desc);

        //RenderContext^ CreateRenderContext(RenderContextDescriptor^ desc, Surface^ surface);

        void Release(RenderContext^ renderContext);

        #if 0

        /* ----- Command queues ----- */

        property CommandQueue^ CommandQueue
        {
            LHermanns::LLGL::CommandQueue^ get();
        }

        /* ----- Command buffers ----- */

        CommandBuffer^ CreateCommandBuffer();

        CommandBufferExt^ CreateCommandBufferExt();

        void Release(CommandBuffer^ commandBuffer);

        /* ----- Buffers ------ */

        Buffer^ CreateBuffer(BufferDescriptor^ desc);
        Buffer^ CreateBuffer(BufferDescriptor^ desc, array<System::Byte>^ initialData);

        //BufferArray^ CreateBufferArray(std::uint32_t numBuffers, Buffer* const * bufferArray);

        void Release(Buffer^ buffer);

        //void Release(BufferArray^ bufferArray);

        void WriteBuffer(Buffer^ buffer, array<System::Byte>^ data, System::UIntPtr dataSize, System::UIntPtr offset);

        //void* MapBuffer(Buffer^ buffer, CPUAccess access);

        //void UnmapBuffer(Buffer^ buffer);

        /* ----- Textures ----- */

        Texture^ CreateTexture(TextureDescriptor^ textureDesc);
        Texture^ CreateTexture(TextureDescriptor^ textureDesc, SrcImageDescriptor^ imageDesc);

        void Release(Texture^ texture);

        void WriteTexture(Texture^ texture, SubTextureDescriptor^ subTextureDesc, SrcImageDescriptor^ imageDesc);
        void ReadTexture(Texture^ texture, unsigned int mipLevel, DstImageDescriptor^ imageDesc);

        void GenerateMips(Texture^ texture);
        void GenerateMips(Texture^ texture, unsigned int baseMipLevel, unsigned int numMipLevels, unsigned int baseArrayLayer, unsigned int numArrayLayers);

        /* ----- Samplers ---- */

        Sampler^ CreateSampler(SamplerDescriptor^ desc);

        void Release(Sampler^ sampler);

        /* ----- Resource Heaps ----- */

        ResourceHeap^ CreateResourceHeap(ResourceHeapDescriptor^ desc);

        void Release(ResourceHeap^ resourceHeap);

        /* ----- Render Targets ----- */

        RenderTarget^ CreateRenderTarget(RenderTargetDescriptor^ desc);

        void Release(RenderTarget^ renderTarget);

        /* ----- Shader ----- */

        Shader^ CreateShader(ShaderDescriptor^ desc);

        ShaderProgram^ CreateShaderProgram(ShaderProgramDescriptor^ desc);

        void Release(Shader^ shader);

        void Release(ShaderProgram^ shaderProgram);

        /* ----- Pipeline Layouts ----- */

        PipelineLayout^ CreatePipelineLayout(PipelineLayoutDescriptor^ desc);

        void Release(PipelineLayout^ pipelineLayout);

        /* ----- Pipeline States ----- */

        GraphicsPipeline^ CreateGraphicsPipeline(GraphicsPipelineDescriptor^ desc);

        ComputePipeline^ CreateComputePipeline(ComputePipelineDescriptor^ desc);

        void Release(GraphicsPipeline^ graphicsPipeline);

        void Release(ComputePipeline^ computePipeline);

        /* ----- Queries ----- */

        Query^ CreateQuery(QueryDescriptor^ desc);

        void Release(Query^ query);

        /* ----- Fences ----- */

        Fence^ CreateFence();

        void Release(Fence^ fence);

        #endif

    private:

        RenderSystem(std::unique_ptr<::LLGL::RenderSystem>&& instance);

    private:

        ::LLGL::RenderSystem* instance_ = nullptr;

};


} // /namespace LLGL

} // /namespace LHermanns



// ================================================================================