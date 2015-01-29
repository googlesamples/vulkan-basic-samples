/*
 * XGL
 *
 * Copyright (C) 2014 LunarG, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *   Chia-I Wu <olv@lunarg.com>
 */

#include "genhw/genhw.h"
#include "dev.h"
#include "gpu.h"
#include "format.h"

struct intel_vf_cap {
   int vertex_element;
};

struct intel_sampler_cap {
   int sampling;
   int filtering;
   int shadow_map;
   int chroma_key;
};

struct intel_dp_cap {
   int rt_write;
   int rt_write_blending;
   int typed_write;
   int media_color_processing;
};

/*
 * This table is based on:
 *
 *  - the Sandy Bridge PRM, volume 4 part 1, page 88-97
 *  - the Ivy Bridge PRM, volume 2 part 1, page 97-99
 *  - the Haswell PRM, volume 7, page 467-470
 */
static const struct intel_vf_cap intel_vf_caps[] = {
#define CAP(vertex_element) { INTEL_GEN(vertex_element) }
   [GEN6_FORMAT_R32G32B32A32_FLOAT]       = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_SINT]        = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_UINT]        = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_UNORM]       = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_SNORM]       = CAP(  1),
   [GEN6_FORMAT_R64G64_FLOAT]             = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_SSCALED]     = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_USCALED]     = CAP(  1),
   [GEN6_FORMAT_R32G32B32A32_SFIXED]      = CAP(7.5),
   [GEN6_FORMAT_R32G32B32_FLOAT]          = CAP(  1),
   [GEN6_FORMAT_R32G32B32_SINT]           = CAP(  1),
   [GEN6_FORMAT_R32G32B32_UINT]           = CAP(  1),
   [GEN6_FORMAT_R32G32B32_UNORM]          = CAP(  1),
   [GEN6_FORMAT_R32G32B32_SNORM]          = CAP(  1),
   [GEN6_FORMAT_R32G32B32_SSCALED]        = CAP(  1),
   [GEN6_FORMAT_R32G32B32_USCALED]        = CAP(  1),
   [GEN6_FORMAT_R32G32B32_SFIXED]         = CAP(7.5),
   [GEN6_FORMAT_R16G16B16A16_UNORM]       = CAP(  1),
   [GEN6_FORMAT_R16G16B16A16_SNORM]       = CAP(  1),
   [GEN6_FORMAT_R16G16B16A16_SINT]        = CAP(  1),
   [GEN6_FORMAT_R16G16B16A16_UINT]        = CAP(  1),
   [GEN6_FORMAT_R16G16B16A16_FLOAT]       = CAP(  1),
   [GEN6_FORMAT_R32G32_FLOAT]             = CAP(  1),
   [GEN6_FORMAT_R32G32_SINT]              = CAP(  1),
   [GEN6_FORMAT_R32G32_UINT]              = CAP(  1),
   [GEN6_FORMAT_R32G32_UNORM]             = CAP(  1),
   [GEN6_FORMAT_R32G32_SNORM]             = CAP(  1),
   [GEN6_FORMAT_R64_FLOAT]                = CAP(  1),
   [GEN6_FORMAT_R16G16B16A16_SSCALED]     = CAP(  1),
   [GEN6_FORMAT_R16G16B16A16_USCALED]     = CAP(  1),
   [GEN6_FORMAT_R32G32_SSCALED]           = CAP(  1),
   [GEN6_FORMAT_R32G32_USCALED]           = CAP(  1),
   [GEN6_FORMAT_R32G32_SFIXED]            = CAP(7.5),
   [GEN6_FORMAT_B8G8R8A8_UNORM]           = CAP(  1),
   [GEN6_FORMAT_R10G10B10A2_UNORM]        = CAP(  1),
   [GEN6_FORMAT_R10G10B10A2_UINT]         = CAP(  1),
   [GEN6_FORMAT_R10G10B10_SNORM_A2_UNORM] = CAP(  1),
   [GEN6_FORMAT_R8G8B8A8_UNORM]           = CAP(  1),
   [GEN6_FORMAT_R8G8B8A8_SNORM]           = CAP(  1),
   [GEN6_FORMAT_R8G8B8A8_SINT]            = CAP(  1),
   [GEN6_FORMAT_R8G8B8A8_UINT]            = CAP(  1),
   [GEN6_FORMAT_R16G16_UNORM]             = CAP(  1),
   [GEN6_FORMAT_R16G16_SNORM]             = CAP(  1),
   [GEN6_FORMAT_R16G16_SINT]              = CAP(  1),
   [GEN6_FORMAT_R16G16_UINT]              = CAP(  1),
   [GEN6_FORMAT_R16G16_FLOAT]             = CAP(  1),
   [GEN6_FORMAT_B10G10R10A2_UNORM]        = CAP(7.5),
   [GEN6_FORMAT_R11G11B10_FLOAT]          = CAP(  1),
   [GEN6_FORMAT_R32_SINT]                 = CAP(  1),
   [GEN6_FORMAT_R32_UINT]                 = CAP(  1),
   [GEN6_FORMAT_R32_FLOAT]                = CAP(  1),
   [GEN6_FORMAT_R32_UNORM]                = CAP(  1),
   [GEN6_FORMAT_R32_SNORM]                = CAP(  1),
   [GEN6_FORMAT_R10G10B10X2_USCALED]      = CAP(  1),
   [GEN6_FORMAT_R8G8B8A8_SSCALED]         = CAP(  1),
   [GEN6_FORMAT_R8G8B8A8_USCALED]         = CAP(  1),
   [GEN6_FORMAT_R16G16_SSCALED]           = CAP(  1),
   [GEN6_FORMAT_R16G16_USCALED]           = CAP(  1),
   [GEN6_FORMAT_R32_SSCALED]              = CAP(  1),
   [GEN6_FORMAT_R32_USCALED]              = CAP(  1),
   [GEN6_FORMAT_R8G8_UNORM]               = CAP(  1),
   [GEN6_FORMAT_R8G8_SNORM]               = CAP(  1),
   [GEN6_FORMAT_R8G8_SINT]                = CAP(  1),
   [GEN6_FORMAT_R8G8_UINT]                = CAP(  1),
   [GEN6_FORMAT_R16_UNORM]                = CAP(  1),
   [GEN6_FORMAT_R16_SNORM]                = CAP(  1),
   [GEN6_FORMAT_R16_SINT]                 = CAP(  1),
   [GEN6_FORMAT_R16_UINT]                 = CAP(  1),
   [GEN6_FORMAT_R16_FLOAT]                = CAP(  1),
   [GEN6_FORMAT_R8G8_SSCALED]             = CAP(  1),
   [GEN6_FORMAT_R8G8_USCALED]             = CAP(  1),
   [GEN6_FORMAT_R16_SSCALED]              = CAP(  1),
   [GEN6_FORMAT_R16_USCALED]              = CAP(  1),
   [GEN6_FORMAT_R8_UNORM]                 = CAP(  1),
   [GEN6_FORMAT_R8_SNORM]                 = CAP(  1),
   [GEN6_FORMAT_R8_SINT]                  = CAP(  1),
   [GEN6_FORMAT_R8_UINT]                  = CAP(  1),
   [GEN6_FORMAT_R8_SSCALED]               = CAP(  1),
   [GEN6_FORMAT_R8_USCALED]               = CAP(  1),
   [GEN6_FORMAT_R8G8B8_UNORM]             = CAP(  1),
   [GEN6_FORMAT_R8G8B8_SNORM]             = CAP(  1),
   [GEN6_FORMAT_R8G8B8_SSCALED]           = CAP(  1),
   [GEN6_FORMAT_R8G8B8_USCALED]           = CAP(  1),
   [GEN6_FORMAT_R64G64B64A64_FLOAT]       = CAP(  1),
   [GEN6_FORMAT_R64G64B64_FLOAT]          = CAP(  1),
   [GEN6_FORMAT_R16G16B16_FLOAT]          = CAP(  6),
   [GEN6_FORMAT_R16G16B16_UNORM]          = CAP(  1),
   [GEN6_FORMAT_R16G16B16_SNORM]          = CAP(  1),
   [GEN6_FORMAT_R16G16B16_SSCALED]        = CAP(  1),
   [GEN6_FORMAT_R16G16B16_USCALED]        = CAP(  1),
   [GEN6_FORMAT_R16G16B16_UINT]           = CAP(7.5),
   [GEN6_FORMAT_R16G16B16_SINT]           = CAP(7.5),
   [GEN6_FORMAT_R32_SFIXED]               = CAP(7.5),
   [GEN6_FORMAT_R10G10B10A2_SNORM]        = CAP(7.5),
   [GEN6_FORMAT_R10G10B10A2_USCALED]      = CAP(7.5),
   [GEN6_FORMAT_R10G10B10A2_SSCALED]      = CAP(7.5),
   [GEN6_FORMAT_R10G10B10A2_SINT]         = CAP(7.5),
   [GEN6_FORMAT_B10G10R10A2_SNORM]        = CAP(7.5),
   [GEN6_FORMAT_B10G10R10A2_USCALED]      = CAP(7.5),
   [GEN6_FORMAT_B10G10R10A2_SSCALED]      = CAP(7.5),
   [GEN6_FORMAT_B10G10R10A2_UINT]         = CAP(7.5),
   [GEN6_FORMAT_B10G10R10A2_SINT]         = CAP(7.5),
   [GEN6_FORMAT_R8G8B8_UINT]              = CAP(7.5),
   [GEN6_FORMAT_R8G8B8_SINT]              = CAP(7.5),
#undef CAP
};

/*
 * This table is based on:
 *
 *  - the Sandy Bridge PRM, volume 4 part 1, page 88-97
 *  - the Ivy Bridge PRM, volume 4 part 1, page 84-87
 */
static const struct intel_sampler_cap intel_sampler_caps[] = {
#define CAP(sampling, filtering, shadow_map, chroma_key) \
   { INTEL_GEN(sampling), INTEL_GEN(filtering), INTEL_GEN(shadow_map), INTEL_GEN(chroma_key) }
   [GEN6_FORMAT_R32G32B32A32_FLOAT]       = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_R32G32B32A32_SINT]        = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32G32B32A32_UINT]        = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32G32B32X32_FLOAT]       = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_R32G32B32_FLOAT]          = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_R32G32B32_SINT]           = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32G32B32_UINT]           = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16G16B16A16_UNORM]       = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16G16B16A16_SNORM]       = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16G16B16A16_SINT]        = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16G16B16A16_UINT]        = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16G16B16A16_FLOAT]       = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R32G32_FLOAT]             = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_R32G32_SINT]              = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32G32_UINT]              = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32_FLOAT_X8X24_TYPELESS] = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_X32_TYPELESS_G8X24_UINT]  = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_L32A32_FLOAT]             = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_R16G16B16X16_UNORM]       = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16G16B16X16_FLOAT]       = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_A32X32_FLOAT]             = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_L32X32_FLOAT]             = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_I32X32_FLOAT]             = CAP(  1,   5,   0,   0),
   [GEN6_FORMAT_B8G8R8A8_UNORM]           = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_B8G8R8A8_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R10G10B10A2_UNORM]        = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R10G10B10A2_UNORM_SRGB]   = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R10G10B10A2_UINT]         = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R10G10B10_SNORM_A2_UNORM] = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8B8A8_UNORM]           = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8B8A8_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8B8A8_SNORM]           = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8B8A8_SINT]            = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R8G8B8A8_UINT]            = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16G16_UNORM]             = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16G16_SNORM]             = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16G16_SINT]              = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16G16_UINT]              = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16G16_FLOAT]             = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B10G10R10A2_UNORM]        = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B10G10R10A2_UNORM_SRGB]   = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R11G11B10_FLOAT]          = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R32_SINT]                 = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32_UINT]                 = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R32_FLOAT]                = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_R24_UNORM_X8_TYPELESS]    = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_X24_TYPELESS_G8_UINT]     = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_L16A16_UNORM]             = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_I24X8_UNORM]              = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_L24X8_UNORM]              = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_A24X8_UNORM]              = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_I32_FLOAT]                = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_L32_FLOAT]                = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_A32_FLOAT]                = CAP(  1,   5,   1,   0),
   [GEN6_FORMAT_B8G8R8X8_UNORM]           = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_B8G8R8X8_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8B8X8_UNORM]           = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8B8X8_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R9G9B9E5_SHAREDEXP]       = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B10G10R10X2_UNORM]        = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_L16A16_FLOAT]             = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B5G6R5_UNORM]             = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_B5G6R5_UNORM_SRGB]        = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B5G5R5A1_UNORM]           = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_B5G5R5A1_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B4G4R4A4_UNORM]           = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_B4G4R4A4_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8_UNORM]               = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8_SNORM]               = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_R8G8_SINT]                = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R8G8_UINT]                = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16_UNORM]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_R16_SNORM]                = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16_SINT]                 = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16_UINT]                 = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R16_FLOAT]                = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_A8P8_UNORM_PALETTE0]      = CAP(  5,   5,   0,   0),
   [GEN6_FORMAT_A8P8_UNORM_PALETTE1]      = CAP(  5,   5,   0,   0),
   [GEN6_FORMAT_I16_UNORM]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_L16_UNORM]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_A16_UNORM]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_L8A8_UNORM]               = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_I16_FLOAT]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_L16_FLOAT]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_A16_FLOAT]                = CAP(  1,   1,   1,   0),
   [GEN6_FORMAT_L8A8_UNORM_SRGB]          = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_R5G5_SNORM_B6_UNORM]      = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_P8A8_UNORM_PALETTE0]      = CAP(  5,   5,   0,   0),
   [GEN6_FORMAT_P8A8_UNORM_PALETTE1]      = CAP(  5,   5,   0,   0),
   [GEN6_FORMAT_R8_UNORM]                 = CAP(  1,   1,   0, 4.5),
   [GEN6_FORMAT_R8_SNORM]                 = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8_SINT]                  = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_R8_UINT]                  = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_A8_UNORM]                 = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_I8_UNORM]                 = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_L8_UNORM]                 = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_P4A4_UNORM_PALETTE0]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_A4P4_UNORM_PALETTE0]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_P8_UNORM_PALETTE0]        = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_L8_UNORM_SRGB]            = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_P8_UNORM_PALETTE1]        = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_P4A4_UNORM_PALETTE1]      = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_A4P4_UNORM_PALETTE1]      = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_DXT1_RGB_SRGB]            = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_R1_UNORM]                 = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_YCRCB_NORMAL]             = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_YCRCB_SWAPUVY]            = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_P2_UNORM_PALETTE0]        = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_P2_UNORM_PALETTE1]        = CAP(4.5, 4.5,   0,   0),
   [GEN6_FORMAT_BC1_UNORM]                = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_BC2_UNORM]                = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_BC3_UNORM]                = CAP(  1,   1,   0,   1),
   [GEN6_FORMAT_BC4_UNORM]                = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_BC5_UNORM]                = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_BC1_UNORM_SRGB]           = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_BC2_UNORM_SRGB]           = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_BC3_UNORM_SRGB]           = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_MONO8]                    = CAP(  1,   0,   0,   0),
   [GEN6_FORMAT_YCRCB_SWAPUV]             = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_YCRCB_SWAPY]              = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_DXT1_RGB]                 = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_FXT1]                     = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_BC4_SNORM]                = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_BC5_SNORM]                = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R16G16B16_FLOAT]          = CAP(  5,   5,   0,   0),
   [GEN6_FORMAT_BC6H_SF16]                = CAP(  7,   7,   0,   0),
   [GEN6_FORMAT_BC7_UNORM]                = CAP(  7,   7,   0,   0),
   [GEN6_FORMAT_BC7_UNORM_SRGB]           = CAP(  7,   7,   0,   0),
   [GEN6_FORMAT_BC6H_UF16]                = CAP(  7,   7,   0,   0),
#undef CAP
};

/*
 * This table is based on:
 *
 *  - the Sandy Bridge PRM, volume 4 part 1, page 88-97
 *  - the Ivy Bridge PRM, volume 4 part 1, page 172, 252-253, and 277-278
 *  - the Haswell PRM, volume 7, page 262-264
 */
static const struct intel_dp_cap intel_dp_caps[] = {
#define CAP(rt_write, rt_write_blending, typed_write, media_color_processing) \
   { INTEL_GEN(rt_write), INTEL_GEN(rt_write_blending), INTEL_GEN(typed_write), INTEL_GEN(media_color_processing) }
   [GEN6_FORMAT_R32G32B32A32_FLOAT]       = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_R32G32B32A32_SINT]        = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R32G32B32A32_UINT]        = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16G16B16A16_UNORM]       = CAP(  1, 4.5,   7,   6),
   [GEN6_FORMAT_R16G16B16A16_SNORM]       = CAP(  1,   6,   7,   0),
   [GEN6_FORMAT_R16G16B16A16_SINT]        = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16G16B16A16_UINT]        = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16G16B16A16_FLOAT]       = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_R32G32_FLOAT]             = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_R32G32_SINT]              = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R32G32_UINT]              = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_B8G8R8A8_UNORM]           = CAP(  1,   1,   7,   6),
   [GEN6_FORMAT_B8G8R8A8_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R10G10B10A2_UNORM]        = CAP(  1,   1,   7,   6),
   [GEN6_FORMAT_R10G10B10A2_UNORM_SRGB]   = CAP(  0,   0,   0,   6),
   [GEN6_FORMAT_R10G10B10A2_UINT]         = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R8G8B8A8_UNORM]           = CAP(  1,   1,   7,   6),
   [GEN6_FORMAT_R8G8B8A8_UNORM_SRGB]      = CAP(  1,   1,   0,   6),
   [GEN6_FORMAT_R8G8B8A8_SNORM]           = CAP(  1,   6,   7,   0),
   [GEN6_FORMAT_R8G8B8A8_SINT]            = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R8G8B8A8_UINT]            = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16G16_UNORM]             = CAP(  1, 4.5,   7,   0),
   [GEN6_FORMAT_R16G16_SNORM]             = CAP(  1,   6,   7,   0),
   [GEN6_FORMAT_R16G16_SINT]              = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16G16_UINT]              = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16G16_FLOAT]             = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B10G10R10A2_UNORM]        = CAP(  1,   1,   7,   6),
   [GEN6_FORMAT_B10G10R10A2_UNORM_SRGB]   = CAP(  1,   1,   0,   6),
   [GEN6_FORMAT_R11G11B10_FLOAT]          = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_R32_SINT]                 = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R32_UINT]                 = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R32_FLOAT]                = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B8G8R8X8_UNORM]           = CAP(  0,   0,   0,   6),
   [GEN6_FORMAT_B5G6R5_UNORM]             = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B5G6R5_UNORM_SRGB]        = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B5G5R5A1_UNORM]           = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B5G5R5A1_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_B4G4R4A4_UNORM]           = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B4G4R4A4_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8G8_UNORM]               = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_R8G8_SNORM]               = CAP(  1,   6,   7,   0),
   [GEN6_FORMAT_R8G8_SINT]                = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R8G8_UINT]                = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16_UNORM]                = CAP(  1, 4.5,   7,   7),
   [GEN6_FORMAT_R16_SNORM]                = CAP(  1,   6,   7,   0),
   [GEN6_FORMAT_R16_SINT]                 = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16_UINT]                 = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R16_FLOAT]                = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B5G5R5X1_UNORM]           = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_B5G5R5X1_UNORM_SRGB]      = CAP(  1,   1,   0,   0),
   [GEN6_FORMAT_R8_UNORM]                 = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_R8_SNORM]                 = CAP(  1,   6,   7,   0),
   [GEN6_FORMAT_R8_SINT]                  = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_R8_UINT]                  = CAP(  1,   0,   7,   0),
   [GEN6_FORMAT_A8_UNORM]                 = CAP(  1,   1,   7,   0),
   [GEN6_FORMAT_YCRCB_NORMAL]             = CAP(  1,   0,   0,   6),
   [GEN6_FORMAT_YCRCB_SWAPUVY]            = CAP(  1,   0,   0,   6),
   [GEN6_FORMAT_YCRCB_SWAPUV]             = CAP(  1,   0,   0,   6),
   [GEN6_FORMAT_YCRCB_SWAPY]              = CAP(  1,   0,   0,   6),
#undef CAP
};

static const int intel_color_mapping[XGL_NUM_FMT] = {
    [XGL_FMT_R4G4_UNORM]           = 0,
    [XGL_FMT_R4G4_USCALED]         = 0,
    [XGL_FMT_R4G4B4A4_UNORM]       = 0,
    [XGL_FMT_R4G4B4A4_USCALED]     = 0,
    [XGL_FMT_R5G6B5_UNORM]         = 0,
    [XGL_FMT_R5G6B5_USCALED]       = 0,
    [XGL_FMT_R5G5B5A1_UNORM]       = 0,
    [XGL_FMT_R5G5B5A1_USCALED]     = 0,
    [XGL_FMT_R8_UNORM]             = GEN6_FORMAT_R8_UNORM,
    [XGL_FMT_R8_SNORM]             = GEN6_FORMAT_R8_SNORM,
    [XGL_FMT_R8_USCALED]           = GEN6_FORMAT_R8_USCALED,
    [XGL_FMT_R8_SSCALED]           = GEN6_FORMAT_R8_SSCALED,
    [XGL_FMT_R8_UINT]              = GEN6_FORMAT_R8_UINT,
    [XGL_FMT_R8_SINT]              = GEN6_FORMAT_R8_SINT,
    [XGL_FMT_R8_SRGB]              = 0,
    [XGL_FMT_R8G8_UNORM]           = GEN6_FORMAT_R8G8_UNORM,
    [XGL_FMT_R8G8_SNORM]           = GEN6_FORMAT_R8G8_SNORM,
    [XGL_FMT_R8G8_USCALED]         = GEN6_FORMAT_R8G8_USCALED,
    [XGL_FMT_R8G8_SSCALED]         = GEN6_FORMAT_R8G8_SSCALED,
    [XGL_FMT_R8G8_UINT]            = GEN6_FORMAT_R8G8_UINT,
    [XGL_FMT_R8G8_SINT]            = GEN6_FORMAT_R8G8_SINT,
    [XGL_FMT_R8G8_SRGB]            = 0,
    [XGL_FMT_R8G8B8_UNORM]         = GEN6_FORMAT_R8G8B8_UNORM,
    [XGL_FMT_R8G8B8_SNORM]         = GEN6_FORMAT_R8G8B8_SNORM,
    [XGL_FMT_R8G8B8_USCALED]       = GEN6_FORMAT_R8G8B8_USCALED,
    [XGL_FMT_R8G8B8_SSCALED]       = GEN6_FORMAT_R8G8B8_SSCALED,
    [XGL_FMT_R8G8B8_UINT]          = GEN6_FORMAT_R8G8B8_UINT,
    [XGL_FMT_R8G8B8_SINT]          = GEN6_FORMAT_R8G8B8_SINT,
    [XGL_FMT_R8G8B8_SRGB]          = GEN6_FORMAT_R8G8B8_UNORM_SRGB,
    [XGL_FMT_R8G8B8A8_UNORM]       = GEN6_FORMAT_R8G8B8A8_UNORM,
    [XGL_FMT_R8G8B8A8_SNORM]       = GEN6_FORMAT_R8G8B8A8_SNORM,
    [XGL_FMT_R8G8B8A8_USCALED]     = GEN6_FORMAT_R8G8B8A8_USCALED,
    [XGL_FMT_R8G8B8A8_SSCALED]     = GEN6_FORMAT_R8G8B8A8_SSCALED,
    [XGL_FMT_R8G8B8A8_UINT]        = GEN6_FORMAT_R8G8B8A8_UINT,
    [XGL_FMT_R8G8B8A8_SINT]        = GEN6_FORMAT_R8G8B8A8_SINT,
    [XGL_FMT_R8G8B8A8_SRGB]        = GEN6_FORMAT_R8G8B8A8_UNORM_SRGB,
    [XGL_FMT_R10G10B10A2_UNORM]    = GEN6_FORMAT_R10G10B10A2_UNORM,
    [XGL_FMT_R10G10B10A2_SNORM]    = GEN6_FORMAT_R10G10B10A2_SNORM,
    [XGL_FMT_R10G10B10A2_USCALED]  = GEN6_FORMAT_R10G10B10A2_USCALED,
    [XGL_FMT_R10G10B10A2_SSCALED]  = GEN6_FORMAT_R10G10B10A2_SSCALED,
    [XGL_FMT_R10G10B10A2_UINT]     = GEN6_FORMAT_R10G10B10A2_UINT,
    [XGL_FMT_R10G10B10A2_SINT]     = GEN6_FORMAT_R10G10B10A2_SINT,
    [XGL_FMT_R16_UNORM]            = GEN6_FORMAT_R16_UNORM,
    [XGL_FMT_R16_SNORM]            = GEN6_FORMAT_R16_SNORM,
    [XGL_FMT_R16_USCALED]          = GEN6_FORMAT_R16_USCALED,
    [XGL_FMT_R16_SSCALED]          = GEN6_FORMAT_R16_SSCALED,
    [XGL_FMT_R16_UINT]             = GEN6_FORMAT_R16_UINT,
    [XGL_FMT_R16_SINT]             = GEN6_FORMAT_R16_SINT,
    [XGL_FMT_R16_SFLOAT]           = GEN6_FORMAT_R16_FLOAT,
    [XGL_FMT_R16G16_UNORM]         = GEN6_FORMAT_R16G16_UNORM,
    [XGL_FMT_R16G16_SNORM]         = GEN6_FORMAT_R16G16_SNORM,
    [XGL_FMT_R16G16_USCALED]       = GEN6_FORMAT_R16G16_USCALED,
    [XGL_FMT_R16G16_SSCALED]       = GEN6_FORMAT_R16G16_SSCALED,
    [XGL_FMT_R16G16_UINT]          = GEN6_FORMAT_R16G16_UINT,
    [XGL_FMT_R16G16_SINT]          = GEN6_FORMAT_R16G16_SINT,
    [XGL_FMT_R16G16_SFLOAT]        = GEN6_FORMAT_R16G16_FLOAT,
    [XGL_FMT_R16G16B16_UNORM]      = GEN6_FORMAT_R16G16B16_UNORM,
    [XGL_FMT_R16G16B16_SNORM]      = GEN6_FORMAT_R16G16B16_SNORM,
    [XGL_FMT_R16G16B16_USCALED]    = GEN6_FORMAT_R16G16B16_USCALED,
    [XGL_FMT_R16G16B16_SSCALED]    = GEN6_FORMAT_R16G16B16_SSCALED,
    [XGL_FMT_R16G16B16_UINT]       = GEN6_FORMAT_R16G16B16_UINT,
    [XGL_FMT_R16G16B16_SINT]       = GEN6_FORMAT_R16G16B16_SINT,
    [XGL_FMT_R16G16B16_SFLOAT]     = 0,
    [XGL_FMT_R16G16B16A16_UNORM]   = GEN6_FORMAT_R16G16B16A16_UNORM,
    [XGL_FMT_R16G16B16A16_SNORM]   = GEN6_FORMAT_R16G16B16A16_SNORM,
    [XGL_FMT_R16G16B16A16_USCALED] = GEN6_FORMAT_R16G16B16A16_USCALED,
    [XGL_FMT_R16G16B16A16_SSCALED] = GEN6_FORMAT_R16G16B16A16_SSCALED,
    [XGL_FMT_R16G16B16A16_UINT]    = GEN6_FORMAT_R16G16B16A16_UINT,
    [XGL_FMT_R16G16B16A16_SINT]    = GEN6_FORMAT_R16G16B16A16_SINT,
    [XGL_FMT_R16G16B16A16_SFLOAT]  = GEN6_FORMAT_R16G16B16A16_FLOAT,
    [XGL_FMT_R32_UINT]             = GEN6_FORMAT_R32_UINT,
    [XGL_FMT_R32_SINT]             = GEN6_FORMAT_R32_SINT,
    [XGL_FMT_R32_SFLOAT]           = GEN6_FORMAT_R32_FLOAT,
    [XGL_FMT_R32G32_UINT]          = GEN6_FORMAT_R32G32_UINT,
    [XGL_FMT_R32G32_SINT]          = GEN6_FORMAT_R32G32_SINT,
    [XGL_FMT_R32G32_SFLOAT]        = GEN6_FORMAT_R32G32_FLOAT,
    [XGL_FMT_R32G32B32_UINT]       = GEN6_FORMAT_R32G32B32_UINT,
    [XGL_FMT_R32G32B32_SINT]       = GEN6_FORMAT_R32G32B32_SINT,
    [XGL_FMT_R32G32B32_SFLOAT]     = GEN6_FORMAT_R32G32B32_FLOAT,
    [XGL_FMT_R32G32B32A32_UINT]    = GEN6_FORMAT_R32G32B32A32_UINT,
    [XGL_FMT_R32G32B32A32_SINT]    = GEN6_FORMAT_R32G32B32A32_SINT,
    [XGL_FMT_R32G32B32A32_SFLOAT]  = GEN6_FORMAT_R32G32B32A32_FLOAT,
    [XGL_FMT_R64_SFLOAT]           = GEN6_FORMAT_R64_FLOAT,
    [XGL_FMT_R64G64_SFLOAT]        = GEN6_FORMAT_R64G64_FLOAT,
    [XGL_FMT_R64G64B64_SFLOAT]     = GEN6_FORMAT_R64G64B64_FLOAT,
    [XGL_FMT_R64G64B64A64_SFLOAT]  = GEN6_FORMAT_R64G64B64A64_FLOAT,
    [XGL_FMT_R11G11B10_UFLOAT]     = GEN6_FORMAT_R11G11B10_FLOAT,
    [XGL_FMT_R9G9B9E5_UFLOAT]      = GEN6_FORMAT_R9G9B9E5_SHAREDEXP,
    [XGL_FMT_BC1_UNORM]            = GEN6_FORMAT_BC1_UNORM,
    [XGL_FMT_BC1_SRGB]             = GEN6_FORMAT_BC1_UNORM_SRGB,
    [XGL_FMT_BC2_UNORM]            = GEN6_FORMAT_BC2_UNORM,
    [XGL_FMT_BC2_SRGB]             = GEN6_FORMAT_BC2_UNORM_SRGB,
    [XGL_FMT_BC3_UNORM]            = GEN6_FORMAT_BC3_UNORM,
    [XGL_FMT_BC3_SRGB]             = GEN6_FORMAT_BC3_UNORM_SRGB,
    [XGL_FMT_BC4_UNORM]            = GEN6_FORMAT_BC4_UNORM,
    [XGL_FMT_BC4_SNORM]            = GEN6_FORMAT_BC4_SNORM,
    [XGL_FMT_BC5_UNORM]            = GEN6_FORMAT_BC5_UNORM,
    [XGL_FMT_BC5_SNORM]            = GEN6_FORMAT_BC5_SNORM,
    [XGL_FMT_BC6H_UFLOAT]          = GEN6_FORMAT_BC6H_UF16,
    [XGL_FMT_BC6H_SFLOAT]          = GEN6_FORMAT_BC6H_SF16,
    [XGL_FMT_BC7_UNORM]            = GEN6_FORMAT_BC7_UNORM,
    [XGL_FMT_BC7_SRGB]             = GEN6_FORMAT_BC7_UNORM_SRGB,
    /* TODO: Implement for remaining compressed formats. */
    [XGL_FMT_ETC2_R8G8B8_UNORM]    = 0,
    [XGL_FMT_ETC2_R8G8B8A1_UNORM]  = 0,
    [XGL_FMT_ETC2_R8G8B8A8_UNORM]  = 0,
    [XGL_FMT_EAC_R11_UNORM]        = 0,
    [XGL_FMT_EAC_R11_SNORM]        = 0,
    [XGL_FMT_EAC_R11G11_UNORM]     = 0,
    [XGL_FMT_EAC_R11G11_SNORM]     = 0,
    [XGL_FMT_ASTC_4x4_UNORM]       = 0,
    [XGL_FMT_ASTC_4x4_SRGB]        = 0,
    [XGL_FMT_ASTC_4x5_UNORM]       = 0,
    [XGL_FMT_ASTC_4x5_SRGB]        = 0,
    [XGL_FMT_ASTC_5x5_UNORM]       = 0,
    [XGL_FMT_ASTC_5x5_SRGB]        = 0,
    [XGL_FMT_ASTC_6x5_UNORM]       = 0,
    [XGL_FMT_ASTC_6x5_SRGB]        = 0,
    [XGL_FMT_ASTC_6x6_UNORM]       = 0,
    [XGL_FMT_ASTC_6x6_SRGB]        = 0,
    [XGL_FMT_ASTC_8x5_UNORM]       = 0,
    [XGL_FMT_ASTC_8x5_SRGB]        = 0,
    [XGL_FMT_ASTC_8x6_UNORM]       = 0,
    [XGL_FMT_ASTC_8x6_SRGB]        = 0,
    [XGL_FMT_ASTC_8x8_UNORM]       = 0,
    [XGL_FMT_ASTC_8x8_SRGB]        = 0,
    [XGL_FMT_ASTC_10x5_UNORM]      = 0,
    [XGL_FMT_ASTC_10x5_SRGB]       = 0,
    [XGL_FMT_ASTC_10x6_UNORM]      = 0,
    [XGL_FMT_ASTC_10x6_SRGB]       = 0,
    [XGL_FMT_ASTC_10x8_UNORM]      = 0,
    [XGL_FMT_ASTC_10x8_SRGB]       = 0,
    [XGL_FMT_ASTC_10x10_UNORM]     = 0,
    [XGL_FMT_ASTC_10x10_SRGB]      = 0,
    [XGL_FMT_ASTC_12x10_UNORM]     = 0,
    [XGL_FMT_ASTC_12x10_SRGB]      = 0,
    [XGL_FMT_ASTC_12x12_UNORM]     = 0,
    [XGL_FMT_ASTC_12x12_SRGB]      = 0,
    [XGL_FMT_B5G6R5_UNORM]         = GEN6_FORMAT_B5G6R5_UNORM,
    [XGL_FMT_B5G6R5_USCALED]       = 0,
    [XGL_FMT_B8G8R8_UNORM]         = 0,
    [XGL_FMT_B8G8R8_SNORM]         = 0,
    [XGL_FMT_B8G8R8_USCALED]       = 0,
    [XGL_FMT_B8G8R8_SSCALED]       = 0,
    [XGL_FMT_B8G8R8_UINT]          = 0,
    [XGL_FMT_B8G8R8_SINT]          = 0,
    [XGL_FMT_B8G8R8_SRGB]          = GEN6_FORMAT_B5G6R5_UNORM_SRGB,
    [XGL_FMT_B8G8R8A8_UNORM]       = GEN6_FORMAT_B8G8R8A8_UNORM,
    [XGL_FMT_B8G8R8A8_SNORM]       = 0,
    [XGL_FMT_B8G8R8A8_USCALED]     = 0,
    [XGL_FMT_B8G8R8A8_SSCALED]     = 0,
    [XGL_FMT_B8G8R8A8_UINT]        = 0,
    [XGL_FMT_B8G8R8A8_SINT]        = 0,
    [XGL_FMT_B8G8R8A8_SRGB]        = GEN6_FORMAT_B8G8R8A8_UNORM_SRGB,
    [XGL_FMT_B10G10R10A2_UNORM]    = GEN6_FORMAT_B10G10R10A2_UNORM,
    [XGL_FMT_B10G10R10A2_SNORM]    = GEN6_FORMAT_B10G10R10A2_SNORM,
    [XGL_FMT_B10G10R10A2_USCALED]  = GEN6_FORMAT_B10G10R10A2_USCALED,
    [XGL_FMT_B10G10R10A2_SSCALED]  = GEN6_FORMAT_B10G10R10A2_SSCALED,
    [XGL_FMT_B10G10R10A2_UINT]     = GEN6_FORMAT_B10G10R10A2_UINT,
    [XGL_FMT_B10G10R10A2_SINT]     = GEN6_FORMAT_B10G10R10A2_SINT
};

int intel_format_translate_color(const struct intel_gpu *gpu,
                                 XGL_FORMAT format)
{
    int fmt;

    assert(!icd_format_is_undef(format));
    assert(!icd_format_is_ds(format));

    fmt = intel_color_mapping[format];
    /* TODO: Implement for remaining compressed formats. */

    /* GEN6_FORMAT_R32G32B32A32_FLOAT happens to be 0 */
    if (format == XGL_FMT_R32G32B32A32_SFLOAT)
        assert(fmt == 0);
    else if (!fmt)
        fmt = -1;

    return fmt;
}

static XGL_FLAGS intel_format_get_color_features(const struct intel_dev *dev,
                                                 XGL_FORMAT format)
{
    const int fmt = intel_format_translate_color(dev->gpu, format);
    const struct intel_vf_cap *vf;
    const struct intel_sampler_cap *sampler;
    const struct intel_dp_cap *dp;
    XGL_FLAGS features;

    if (fmt < 0)
        return 0;

    sampler = (fmt < ARRAY_SIZE(intel_sampler_caps)) ?
        &intel_sampler_caps[fmt] : NULL;
    vf = (fmt < ARRAY_SIZE(intel_vf_caps)) ?  &intel_vf_caps[fmt] : NULL;
    dp = (fmt < ARRAY_SIZE(intel_dp_caps)) ?  &intel_dp_caps[fmt] : NULL;

    features = XGL_FORMAT_MEMORY_SHADER_ACCESS_BIT;

#define TEST(dev, func, cap) ((func) && (func)->cap && \
        intel_gpu_gen((dev)->gpu) >= (func)->cap)
    if (TEST(dev, vf, vertex_element)) {
        /* no feature bit to set */
    }

    if (TEST(dev, sampler, sampling)) {
        if (icd_format_is_int(format) ||
            TEST(dev, sampler, filtering))
            features |= XGL_FORMAT_IMAGE_SHADER_READ_BIT;
    }

    if (TEST(dev, dp, typed_write))
        features |= XGL_FORMAT_IMAGE_SHADER_WRITE_BIT;

    if (TEST(dev, dp, rt_write)) {
        features |= XGL_FORMAT_COLOR_ATTACHMENT_WRITE_BIT;

        if (TEST(dev, dp, rt_write_blending))
            features |= XGL_FORMAT_COLOR_ATTACHMENT_BLEND_BIT;

        if (features & XGL_FORMAT_IMAGE_SHADER_READ_BIT) {
            features |= XGL_FORMAT_IMAGE_COPY_BIT |
                        XGL_FORMAT_CONVERSION_BIT;
        }
    }
#undef TEST

    return features;
}

static XGL_FLAGS intel_format_get_ds_features(const struct intel_dev *dev,
                                              XGL_FORMAT format)
{
    XGL_FLAGS features;

    assert(icd_format_is_ds(format));

    switch (format) {
    case XGL_FMT_S8_UINT:
        features = XGL_FORMAT_STENCIL_ATTACHMENT_BIT;;
        break;
    case XGL_FMT_D16_UNORM:
    case XGL_FMT_D24_UNORM:
    case XGL_FMT_D32_SFLOAT:
        features = XGL_FORMAT_DEPTH_ATTACHMENT_BIT;
        break;
    case XGL_FMT_D16_UNORM_S8_UINT:
    case XGL_FMT_D24_UNORM_S8_UINT:
    case XGL_FMT_D32_SFLOAT_S8_UINT:
        features = XGL_FORMAT_DEPTH_ATTACHMENT_BIT |
                   XGL_FORMAT_STENCIL_ATTACHMENT_BIT;
        break;
    default:
        features = 0;
        break;
    }

    return features;
}

static XGL_FLAGS intel_format_get_raw_features(const struct intel_dev *dev,
                                               XGL_FORMAT format)
{
    return (format == XGL_FMT_UNDEFINED) ?
        XGL_FORMAT_MEMORY_SHADER_ACCESS_BIT : 0;
}

static void intel_format_get_props(const struct intel_dev *dev,
                                   XGL_FORMAT format,
                                   XGL_FORMAT_PROPERTIES *props)
{
    if (icd_format_is_undef(format)) {
        props->linearTilingFeatures =
            intel_format_get_raw_features(dev, format);
        props->optimalTilingFeatures = 0;
    } else if(icd_format_is_color(format)) {
        props->linearTilingFeatures =
            intel_format_get_color_features(dev, format);
        props->optimalTilingFeatures = props->linearTilingFeatures;
    } else if(icd_format_is_ds(format)) {
        props->linearTilingFeatures = 0;
        props->optimalTilingFeatures =
            intel_format_get_ds_features(dev, format);
    } else {
        props->linearTilingFeatures = 0;
        props->optimalTilingFeatures = 0;
    }
}

ICD_EXPORT XGL_RESULT XGLAPI xglGetFormatInfo(
    XGL_DEVICE                                  device,
    XGL_FORMAT                                  format,
    XGL_FORMAT_INFO_TYPE                        infoType,
    size_t*                                     pDataSize,
    void*                                       pData)
{
    const struct intel_dev *dev = intel_dev(device);
    XGL_RESULT ret = XGL_SUCCESS;

    switch (infoType) {
    case XGL_INFO_TYPE_FORMAT_PROPERTIES:
        *pDataSize = sizeof(XGL_FORMAT_PROPERTIES);
        if (pData == NULL)
            return ret;
        intel_format_get_props(dev, format, pData);
        break;
    default:
        ret = XGL_ERROR_INVALID_VALUE;
        break;
    }

    return ret;
}
