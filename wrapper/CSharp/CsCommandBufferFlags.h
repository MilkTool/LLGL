/*
 * CsCommandBufferFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#pragma once

#include "CsColor.h"

#include <vcclr.h>

#using <System.dll>
#using <System.Core.dll>
#using <System.Runtime.InteropServices.dll>


using namespace System;
using namespace System::Runtime::InteropServices;


namespace LHermanns
{

namespace LLGL
{


/* ----- Flags ----- */

[Flags]
public enum class ClearFlags : System::UInt32
{
    Color           = (1 << 0),
    Depth           = (1 << 1),
    Stencil         = (1 << 2),

    ColorDepth      = (Color | Depth),
    DepthStencil    = (Depth | Stencil),
    All             = (Color | Depth | Stencil),
};


/* ----- Structures ----- */

public ref class ClearValue
{

    public:

        ClearValue();

        property ColorRGBA^     Color;
        property float          Depth;
        property unsigned int   Stencil;

};

public ref class AttachmentClear
{

    public:

        AttachmentClear();
        AttachmentClear(ColorRGBA^ color, unsigned int colorAttachment);
        AttachmentClear(float depth);
        AttachmentClear(unsigned int stencil);
        AttachmentClear(float depth, unsigned int stencil);

        property int            Flags;
        property unsigned int   ColorAttachment;
        property ClearValue^    ClearValue;

};


} // /namespace LLGL

} // /namespace LHermanns



// ================================================================================
