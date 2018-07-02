/*
 * ShaderProgramFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_SHADER_PROGRAM_FLAGS_H
#define LLGL_SHADER_PROGRAM_FLAGS_H


#include "ForwardDecls.h"
#include "VertexFormat.h"
#include "StreamOutputFormat.h"
#include "ShaderUniformFlags.h"
#include "ResourceFlags.h"
#include "BufferFlags.h"
#include <vector>
#include <string>


namespace LLGL
{


/* ----- Structures ----- */

//TODO: rename to ShaderProgramDescriptor
/**
\brief Descriptor structure for graphics shader programs.
\see RenderSystem::CreateShaderProgram(const GraphicsShaderProgramDescriptor&)
\see RenderSystem::CreateShader
*/
struct GraphicsShaderProgramDescriptor
{
    /**
    \brief Vertex format list. This may also be empty, if the vertex shader has no input attributes.
    \see VertexFormat
    */
    std::vector<VertexFormat>   vertexFormats;

    //TODO: add FragmentFormat structure to provide CPU side fragment binding for OpenGL
    #if 0
    FragmentFormat              fragmentFormat;
    #endif

    /**
    \brief Specifies the vertex shader. Each graphics shader program must have at least a vertex shader.
    \remarks The shader must be created with the ShaderType::Vertex type.
    */
    Shader*                     vertexShader            = nullptr;

    /**
    \brief Specifies the tessellation-control shader (also referred to as "Hull Shader").
    \remarks If this is used, the counter part must also be specified (i.e. <code>tessEvaluationShader</code>).
    \see tessEvaluationShader
    */
    Shader*                     tessControlShader       = nullptr;

    /**
    \brief Specifies the tessellation-evaluation shader (also referred to as "Domain Shader").
    \remarks If this is used, the counter part must also be specified (i.e. <code>tessControlShader</code>).
    \see tessControlShader
    */
    Shader*                     tessEvaluationShader    = nullptr;

    //! Specifies an optional geometry shader.
    Shader*                     geometryShader          = nullptr;

    /**
    \brief Specifies an optional fragment shader (also referred to as "Pixel Shader").
    \remarks If no fragment shader is specified, generated fragments are discarded by the output merger
    and only the stream-output functionality is used by either the vertex or geometry shader.
    */
    Shader*                     fragmentShader          = nullptr;
};

/**
\brief Descriptor structure for compute shader programs.
\see RenderSystem::CreateShaderProgram(const ComputeShaderProgramDescriptor&)
\see RenderSystem::CreateShader
*/
struct ComputeShaderProgramDescriptor
{
    /**
    \brief Specifies the compute shader. By default null.
    \remarks This must not be null when passed to the CreateShaderProgram function.
    */
    Shader* computeShader = nullptr;
};

/**
\brief Shader reflection descriptor structure.
\remarks Contains all information of resources and attributes that can be queried from a shader program.
\see ShaderProgram::QueryReflectionDesc
*/
struct ShaderReflectionDescriptor
{
    /**
    \brief Shader reflection resource view structure.
    \remarks A mapping between this structure and a binding descriptor may look like this:
    \code
    auto myShaderReflectionDesc = myShaderProgram->QueryReflectionDesc();
    LLGL::PipelineLayoutDescriptor myPipelineLayoutDesc;
    for (const auto& myResourceView : myShaderReflectionDesc) {
        BindingDescriptor myBindingDesc;
        myBindingDesc.type          = myResourceView.type;
        myBindingDesc.stageFlags    = myResourceView.stageFlags;
        myBindingDesc.slot          = myResourceView.slot;
        myBindingDesc.arraySize     = myResourceView.arraySize;
        myPipelineLayoutDesc.bindings.push_back(myBindingDesc);
    }
    \endcode
    \see BindingDescriptor
    */
    struct ResourceView
    {
        //! Name of the shader resource, i.e. the identifier used in the shader.
        std::string         name;

        //! Resource view type for this layout binding. By default ResourceType::Undefined.
        ResourceType        type                = ResourceType::Undefined;

        /**
        \brief Specifies in which shader stages the resource is located. By default 0.
        \remarks This can be a bitwise OR combination of the StageFlags bitmasks.
        \see StageFlags
        */
        long                stageFlags          = 0;

        /**
        \brief Specifies the zero-based binding slot. By default 0.
        \remarks If the binding slot could be not queried by the shader reflection, the value is Constants::invalidSlot.
        \see Constants::invalidSlot
        */
        std::uint32_t       slot                = 0;

        /**
        \brief Specifies the number of binding slots for an array resource. By default 1.
        \note For Vulkan, this number specifies the size of an array of resources (e.g. an array of uniform buffers).
        */
        std::uint32_t       arraySize           = 1;

        /**
        \brief Specifies the size (in bytes) for a constant buffer resource.
        \remarks Additional attribute exclusively used for constant buffer resources.
        For all other resources, i.e. when 'type' is not equal to 'ResourceType::ConstantBuffer', this attribute is zero.
        \see ResourceType::ConstantBuffer
        */
        std::uint32_t       constantBufferSize  = 0;

        /**
        \brief Specifies the sub-type of a storage buffer resource.
        \remarks Additional attribute exclusively used for storage buffer resources.
        */
        StorageBufferType   storageBufferType   = StorageBufferType::Undefined;
    };

    //! List of all vertex attributes.
    std::vector<VertexAttribute>        vertexAttributes;

    //! List of all stream-output attributes.
    std::vector<StreamOutputAttribute>  streamOutputAttributes;

    //! List of all shader reflection resource views.
    std::vector<ResourceView>           resourceViews;

    /**
    \brief List of all uniforms.
    \note Only supported with: OpenGL, Vulkan.
    */
    std::vector<UniformDescriptor>      uniforms;
};


} // /namespace LLGL


#endif



// ================================================================================
