/**
@file DX11ConstantsMapper.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"


#include "DX11ConstantsMapper.h"

#include "swCommonLib/Common/MemoryLeaks.h"

/**@brief */
uint32					BitsPerPixel		( ResourceFormat fmt )
{
	return (uint32)DX11ConstantsMapper::BitsPerPixel( DX11ConstantsMapper::Get( fmt ) );
}

/**@brief */
uint32					BytesPerPixel		( ResourceFormat fmt )
{
	return (uint32)DX11ConstantsMapper::BytesPerPixel( DX11ConstantsMapper::Get( fmt ) );
}


/**@see ResourceUsage.*/
D3D11_USAGE DX11ResourceUsage[] =
{	
	D3D11_USAGE::D3D11_USAGE_DEFAULT,
	D3D11_USAGE::D3D11_USAGE_DYNAMIC,
	D3D11_USAGE::D3D11_USAGE_IMMUTABLE,
	D3D11_USAGE::D3D11_USAGE_STAGING
};

/**@see PrimitiveTopology.*/
D3D_PRIMITIVE_TOPOLOGY DX11PrimitiveTopology[]
{
	D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
	D3D_PRIMITIVE_TOPOLOGY_LINELIST,
	D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
	D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
	D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
	D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
	D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ
};

/**@see TextureType*/
D3D11_RTV_DIMENSION DX11TextureType[ 9 ]
{
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_UNKNOWN,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_BUFFER,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE1D,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE1DARRAY,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2DMS,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY,
	D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE3D,
};

D3D11_DSV_DIMENSION DX11TextureTypeToDSV[ 9 ]
{
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_UNKNOWN,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_UNKNOWN,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE1D,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE1DARRAY,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DARRAY,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMS,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY,
	D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_UNKNOWN,
};

D3D11_SRV_DIMENSION DX11TextureTypeToSRV[ 9 ]
{
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_UNKNOWN,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_BUFFER,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE1D,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE1DARRAY,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2DARRAY,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2DMS,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY,
	D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE3D,
	//D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURECUBE,
	//D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURECUBEARRAY,
	//D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_BUFFEREX,
};

/**@see ResourceBinding.*/
D3D11_BIND_FLAG	DX11ResourceBinding[ 10 ]
{
	D3D11_BIND_VERTEX_BUFFER,
	D3D11_BIND_INDEX_BUFFER,
	D3D11_BIND_CONSTANT_BUFFER,
	D3D11_BIND_SHADER_RESOURCE,
	D3D11_BIND_STREAM_OUTPUT,
	D3D11_BIND_RENDER_TARGET,
	D3D11_BIND_DEPTH_STENCIL,
	D3D11_BIND_UNORDERED_ACCESS,
	//DirectX 11.1
	//D3D11_BIND_DECODER,
	//D3D11_BIND_VIDEO_ENCODER
	D3D11_BIND_UNORDERED_ACCESS,
	D3D11_BIND_UNORDERED_ACCESS
};

/**@see DepthStencilFormat.*/
DXGI_FORMAT DX11DepthStencilFormat[ 4 ]
{
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
	DXGI_FORMAT_D32_FLOAT,
	DXGI_FORMAT_D24_UNORM_S8_UINT,
	DXGI_FORMAT_D16_UNORM
};

DXGI_FORMAT DX11DepthStencilTypeless[ 4 ]
{
	DXGI_FORMAT_R32G8X24_TYPELESS,
	DXGI_FORMAT_R32_TYPELESS,
	DXGI_FORMAT_R24G8_TYPELESS,
	DXGI_FORMAT_R16_TYPELESS
};

DXGI_FORMAT DX11DepthOnly[ 4 ]
{
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
	DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	DXGI_FORMAT_R16_UNORM
};

DXGI_FORMAT DX11StencilOnly[ 4 ]
{
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,
	DXGI_FORMAT_UNKNOWN
};


D3D11_FILL_MODE		DX11FillMode[ 2 ]
{
	D3D11_FILL_SOLID,
	D3D11_FILL_WIREFRAME
};

D3D11_CULL_MODE		DX11CullMode[ 3 ]
{
	D3D11_CULL_FRONT,
	D3D11_CULL_BACK,
	D3D11_CULL_NONE
};

D3D11_BLEND			DX11BlendFactor[ 12 ]
{
	D3D11_BLEND_ZERO,
	D3D11_BLEND_ONE,
	D3D11_BLEND_SRC_COLOR,
	D3D11_BLEND_DEST_COLOR,
	D3D11_BLEND_SRC_ALPHA,
	D3D11_BLEND_DEST_ALPHA,
	D3D11_BLEND_BLEND_FACTOR,
	D3D11_BLEND_INV_SRC_COLOR,
	D3D11_BLEND_INV_DEST_COLOR,
	D3D11_BLEND_INV_SRC_ALPHA,
	D3D11_BLEND_INV_DEST_ALPHA,
	D3D11_BLEND_INV_BLEND_FACTOR
};

D3D11_BLEND_OP		DX11BlendOperation[ 5 ]
{
	D3D11_BLEND_OP_ADD,
	D3D11_BLEND_OP_SUBTRACT,
	D3D11_BLEND_OP_REV_SUBTRACT,
	D3D11_BLEND_OP_MIN,
	D3D11_BLEND_OP_MAX
};

/**@see ResourceFormat.*/
DXGI_FORMAT DX11ResourceFormat[] =
{
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_R32G32B32A32_TYPELESS,
	DXGI_FORMAT_R32G32B32A32_FLOAT,
	DXGI_FORMAT_R32G32B32A32_UINT,
	DXGI_FORMAT_R32G32B32A32_SINT,
	DXGI_FORMAT_R32G32B32_TYPELESS,
	DXGI_FORMAT_R32G32B32_FLOAT,
	DXGI_FORMAT_R32G32B32_UINT,
	DXGI_FORMAT_R32G32B32_SINT,
	DXGI_FORMAT_R16G16B16A16_TYPELESS,
	DXGI_FORMAT_R16G16B16A16_FLOAT,
	DXGI_FORMAT_R16G16B16A16_UNORM,
	DXGI_FORMAT_R16G16B16A16_UINT,
	DXGI_FORMAT_R16G16B16A16_SNORM,
	DXGI_FORMAT_R16G16B16A16_SINT,
	DXGI_FORMAT_R32G32_TYPELESS,
	DXGI_FORMAT_R32G32_FLOAT,
	DXGI_FORMAT_R32G32_UINT,
	DXGI_FORMAT_R32G32_SINT,
	DXGI_FORMAT_R32G8X24_TYPELESS,
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
	DXGI_FORMAT_R10G10B10A2_TYPELESS,
	DXGI_FORMAT_R10G10B10A2_UNORM,
	DXGI_FORMAT_R10G10B10A2_UINT,
	DXGI_FORMAT_R11G11B10_FLOAT,
	DXGI_FORMAT_R8G8B8A8_TYPELESS,
	DXGI_FORMAT_R8G8B8A8_UNORM,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
	DXGI_FORMAT_R8G8B8A8_UINT,
	DXGI_FORMAT_R8G8B8A8_SNORM,
	DXGI_FORMAT_R8G8B8A8_SINT,
	DXGI_FORMAT_R16G16_TYPELESS,
	DXGI_FORMAT_R16G16_FLOAT,
	DXGI_FORMAT_R16G16_UNORM,
	DXGI_FORMAT_R16G16_UINT,
	DXGI_FORMAT_R16G16_SNORM,
	DXGI_FORMAT_R16G16_SINT,
	DXGI_FORMAT_R32_TYPELESS,
	DXGI_FORMAT_D32_FLOAT,
	DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT_R32_UINT,
	DXGI_FORMAT_R32_SINT,
	DXGI_FORMAT_R24G8_TYPELESS,
	DXGI_FORMAT_D24_UNORM_S8_UINT,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,
	DXGI_FORMAT_R8G8_TYPELESS,
	DXGI_FORMAT_R8G8_UNORM,
	DXGI_FORMAT_R8G8_UINT,
	DXGI_FORMAT_R8G8_SNORM,
	DXGI_FORMAT_R8G8_SINT,
	DXGI_FORMAT_R16_TYPELESS,
	DXGI_FORMAT_R16_FLOAT,
	DXGI_FORMAT_D16_UNORM,
	DXGI_FORMAT_R16_UNORM,
	DXGI_FORMAT_R16_UINT,
	DXGI_FORMAT_R16_SNORM,
	DXGI_FORMAT_R16_SINT,
	DXGI_FORMAT_R8_TYPELESS,
	DXGI_FORMAT_R8_UNORM,
	DXGI_FORMAT_R8_UINT,
	DXGI_FORMAT_R8_SNORM,
	DXGI_FORMAT_R8_SINT,
	DXGI_FORMAT_A8_UNORM,
	DXGI_FORMAT_R1_UNORM,
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
	DXGI_FORMAT_R8G8_B8G8_UNORM,
	DXGI_FORMAT_G8R8_G8B8_UNORM,
	DXGI_FORMAT_BC1_TYPELESS,
	DXGI_FORMAT_BC1_UNORM,
	DXGI_FORMAT_BC1_UNORM_SRGB,
	DXGI_FORMAT_BC2_TYPELESS,
	DXGI_FORMAT_BC2_UNORM,
	DXGI_FORMAT_BC2_UNORM_SRGB,
	DXGI_FORMAT_BC3_TYPELESS,
	DXGI_FORMAT_BC3_UNORM,
	DXGI_FORMAT_BC3_UNORM_SRGB,
	DXGI_FORMAT_BC4_TYPELESS,
	DXGI_FORMAT_BC4_UNORM,
	DXGI_FORMAT_BC4_SNORM,
	DXGI_FORMAT_BC5_TYPELESS,
	DXGI_FORMAT_BC5_UNORM,
	DXGI_FORMAT_BC5_SNORM,
	DXGI_FORMAT_B5G6R5_UNORM,
	DXGI_FORMAT_B5G5R5A1_UNORM,
	DXGI_FORMAT_B8G8R8A8_UNORM,
	DXGI_FORMAT_B8G8R8X8_UNORM,
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
	DXGI_FORMAT_B8G8R8A8_TYPELESS,
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
	DXGI_FORMAT_B8G8R8X8_TYPELESS,
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
	DXGI_FORMAT_BC6H_TYPELESS,
	DXGI_FORMAT_BC6H_UF16,
	DXGI_FORMAT_BC6H_SF16,
	DXGI_FORMAT_BC7_TYPELESS,
	DXGI_FORMAT_BC7_UNORM,
	DXGI_FORMAT_BC7_UNORM_SRGB,
	// DirectX 11.1
	//DXGI_FORMAT_AYUV,
	//DXGI_FORMAT_Y410,
	//DXGI_FORMAT_Y416,
	//DXGI_FORMAT_NV12,
	//DXGI_FORMAT_P010,
	//DXGI_FORMAT_P016,
	//DXGI_FORMAT_420_OPAQUE,
	//DXGI_FORMAT_YUY2,
	//DXGI_FORMAT_Y210,
	//DXGI_FORMAT_Y216,
	//DXGI_FORMAT_NV11,
	//DXGI_FORMAT_AI44,
	//DXGI_FORMAT_IA44,
	//DXGI_FORMAT_P8,
	//DXGI_FORMAT_A8P8,
	//DXGI_FORMAT_B4G4R4A4_UNORM,
	//DXGI_FORMAT_P208,
	//DXGI_FORMAT_V208,
	//DXGI_FORMAT_V408
	// Zast�pione unknownami
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_UNKNOWN
};

/**@brief Przeprowadza odwrotn� konwersj� z natywnego formatu DirectXa do ResourceFormat.*/
ResourceFormat		DX11ConstantsMapper::ConvertBack( DXGI_FORMAT nativeFormat )
{
	for( int i = 0; i < ARRAYSIZE( DX11ResourceFormat ); ++i )
	{
		if( nativeFormat == DX11ResourceFormat[ i ] )
			return static_cast< ResourceFormat >( i );
	}

	return ResourceFormat::RESOURCE_FORMAT_UNKNOWN;
}


//The MIT License (MIT)
//Copyright (c) Microsoft Corporation. All rights reserved.
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
//to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute,
//sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/**@brief Zwraca liczb� bit�w na pixel danego formatu.*/
size_t				DX11ConstantsMapper::BitsPerPixel( DXGI_FORMAT fmt )
{
	switch( fmt )
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
	return 128;

	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
	return 96;

	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	case DXGI_FORMAT_R16G16B16A16_UNORM:
	case DXGI_FORMAT_R16G16B16A16_UINT:
	case DXGI_FORMAT_R16G16B16A16_SNORM:
	case DXGI_FORMAT_R16G16B16A16_SINT:
	case DXGI_FORMAT_R32G32_TYPELESS:
	case DXGI_FORMAT_R32G32_FLOAT:
	case DXGI_FORMAT_R32G32_UINT:
	case DXGI_FORMAT_R32G32_SINT:
	case DXGI_FORMAT_R32G8X24_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
	//case DXGI_FORMAT_Y416:
	//case DXGI_FORMAT_Y210:
	//case DXGI_FORMAT_Y216:
	return 64;

	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
	case DXGI_FORMAT_R10G10B10A2_UNORM:
	case DXGI_FORMAT_R10G10B10A2_UINT:
	case DXGI_FORMAT_R11G11B10_FLOAT:
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	case DXGI_FORMAT_R16G16_TYPELESS:
	case DXGI_FORMAT_R16G16_FLOAT:
	case DXGI_FORMAT_R16G16_UNORM:
	case DXGI_FORMAT_R16G16_UINT:
	case DXGI_FORMAT_R16G16_SNORM:
	case DXGI_FORMAT_R16G16_SINT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_SINT:
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
	//case DXGI_FORMAT_AYUV:
	//case DXGI_FORMAT_Y410:
	//case DXGI_FORMAT_YUY2:
	return 32;

	//case DXGI_FORMAT_P010:
	//case DXGI_FORMAT_P016:
	//return 24;

	case DXGI_FORMAT_R8G8_TYPELESS:
	case DXGI_FORMAT_R8G8_UNORM:
	case DXGI_FORMAT_R8G8_UINT:
	case DXGI_FORMAT_R8G8_SNORM:
	case DXGI_FORMAT_R8G8_SINT:
	case DXGI_FORMAT_R16_TYPELESS:
	case DXGI_FORMAT_R16_FLOAT:
	case DXGI_FORMAT_D16_UNORM:
	case DXGI_FORMAT_R16_UNORM:
	case DXGI_FORMAT_R16_UINT:
	case DXGI_FORMAT_R16_SNORM:
	case DXGI_FORMAT_R16_SINT:
	case DXGI_FORMAT_B5G6R5_UNORM:
	case DXGI_FORMAT_B5G5R5A1_UNORM:
	//case DXGI_FORMAT_A8P8:
	//case DXGI_FORMAT_B4G4R4A4_UNORM:
	return 16;

	//case DXGI_FORMAT_NV12:
	//case DXGI_FORMAT_420_OPAQUE:
	//case DXGI_FORMAT_NV11:
	return 12;

	case DXGI_FORMAT_R8_TYPELESS:
	case DXGI_FORMAT_R8_UNORM:
	case DXGI_FORMAT_R8_UINT:
	case DXGI_FORMAT_R8_SNORM:
	case DXGI_FORMAT_R8_SINT:
	case DXGI_FORMAT_A8_UNORM:
	//case DXGI_FORMAT_AI44:
	//case DXGI_FORMAT_IA44:
	//case DXGI_FORMAT_P8:
	return 8;

	case DXGI_FORMAT_R1_UNORM:
	return 1;

	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
	return 4;

	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
	case DXGI_FORMAT_BC6H_TYPELESS:
	case DXGI_FORMAT_BC6H_UF16:
	case DXGI_FORMAT_BC6H_SF16:
	case DXGI_FORMAT_BC7_TYPELESS:
	case DXGI_FORMAT_BC7_UNORM:
	case DXGI_FORMAT_BC7_UNORM_SRGB:
	return 8;

#if defined(_XBOX_ONE) && defined(_TITLE)

	case DXGI_FORMAT_R10G10B10_7E3_A2_FLOAT:
	case DXGI_FORMAT_R10G10B10_6E4_A2_FLOAT:
	return 32;

	case DXGI_FORMAT_D16_UNORM_S8_UINT:
	case DXGI_FORMAT_R16_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X16_TYPELESS_G8_UINT:
	return 24;

#endif // _XBOX_ONE && _TITLE

	default:
	return 0;
	}
}
