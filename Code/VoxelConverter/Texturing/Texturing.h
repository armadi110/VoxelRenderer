#pragma once

#include "VoxelConverter/Texturing/OctreeAccessor.h"
#include "TexturingEnums.h"
#include "Samplers/Samplers.h"

#include "swCommonLib/System/Path.h"





/**@brief Object for texturing octree containing UV coordinates in place of colors.*/
class Texturing
{
private:

	WrappingMode	m_wrappingModeX;
	WrappingMode	m_wrappingModeY;

	OctreeAccessor	m_octree;

	bool			m_flipU;
	bool			m_flipV;

protected:
public:
	
	explicit		Texturing		( OctreeAccessor octree );
	explicit		Texturing		( OctreeAccessor octree, bool flipU, bool flipV );
					~Texturing		() = default;


	bool			TextureOctree	( const filesystem::Path& filePath, SamplerType samplingType, Size texIdx );

private:

	template< typename SamplerObject >
	void			TextureOctreeWithSampler		( const TextureAccessor& tex, OctreeAccessor& octree, Size texIdx );
};


