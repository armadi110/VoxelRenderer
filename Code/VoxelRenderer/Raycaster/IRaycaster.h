#pragma once


#include "swGraphicAPI/Resources/MeshResources.h"
#include "VoxelRenderer/SVO/Octree.h"
#include "VoxelRenderer/Actors/CameraActor.h"
#include "VoxelRenderer/Application/Light/LightModule.h"


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "swGraphicAPI/Rendering/IRenderer.h"

#include "swInputLibrary/InputCore/KeyboardState.h"
#include "swInputLibrary/InputCore/MouseState.h"

#include "ShellMeshTools/ShellMesh/ShellMesh.h"



namespace vr
{

/**@brief */
class IRaycaster
{
private:
protected:
public:
	explicit		IRaycaster		() = default;
					~IRaycaster		() = default;

	virtual void	RenderShellMeshes	( TimeType time, const std::vector< ShellMeshPtr >& shellMeshes, CameraActor* camera )				{}
	virtual void	Render				( TimeType time, OctreePtr octree, RenderTargetObject* svoRenderTarget, CameraActor* camera )		= 0;
	virtual void	Init				( IRenderer* renderer, ResourceManager* resourceManager, LightModulePtr lights )					= 0;

	virtual void	ProcessInput		( const sw::input::MouseState& mouse, const sw::input::KeyboardState& keyboard )					= 0;
};

DEFINE_UPTR_TYPE( IRaycaster );

}
