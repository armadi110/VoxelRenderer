#include "ShellMeshRenderer.h"

#include "VoxelRenderer/Application/RenderingHelpers.h"

#include "swGraphicAPI/Resources/ResourcesFactory.h"

#include "Structures/ShaderCameraBuffer.h"




using namespace DirectX;
using namespace sw::input;



namespace vr
{


//====================================================================================//
//			Helpers	
//====================================================================================//


// ================================ //
//
DirectX::XMFLOAT4X4				Transpose				( DirectX::XMFLOAT4X4 mat )
{
	auto matrix = XMLoadFloat4x4( &mat );
	matrix = DirectX::XMMatrixTranspose( matrix );
	XMStoreFloat4x4( &mat, matrix );
	return mat;
}




//====================================================================================//
//			Rendering	
//====================================================================================//


// ================================ //
//
ShellMeshRenderer::ShellMeshRenderer()
	:	m_height( 0 )
	,	m_width( 0 )
{
	m_helperConsts.ShowBlendWeightsIdx = 0;
}

// ================================ //
//
void				ShellMeshRenderer::RenderShellMeshes( TimeType time, const std::vector< ShellMeshPtr >& shellMeshes, CameraActor* camera )
{
	if( m_width != camera->GetWidth() || m_height != camera->GetHeight() )
		ReallocateRenderTarget( (uint16)camera->GetWidth(), (uint16)camera->GetHeight() );

	UpdateCamera( camera );
	UpdateHelperConstants();

	RenderingHelper::ClearRenderTargetAndDepth( m_renderer, m_shellMeshTarget.Ptr(), DirectX::XMFLOAT4( 0.0, 0.0, 0.0, 0.0 ), 1.0f );
	RenderingHelper::SetRenderTarget( m_renderer, m_shellMeshTarget.Ptr(), m_rasterizerState.Ptr(), m_blendingState.Ptr(), m_depthStencilState.Ptr() );

	SetShaderStateCommand shaderState;
	RenderingHelper::ClearTextureState( shaderState );

	shaderState.VertexShader = m_vertexShader.Ptr();
	shaderState.PixelShader = m_pixelShader.Ptr();

	m_renderer->SetShaderState( shaderState );

	RenderingHelper::BindBuffer( m_renderer, m_cameraBuffer.Ptr(), 0, (uint8)ShaderType::VertexShader );
	RenderingHelper::BindBuffer( m_renderer, m_helperConstants.Ptr(), 3, (uint8)ShaderType::VertexShader );

	for( auto & shellMesh : shellMeshes )
	{
		UpdateAnimation( time, shellMesh );
		UpdateMeshBuffer( shellMesh );

		RenderingHelper::BindBuffer( m_renderer, m_bonesBuffer.Ptr(), 1, (uint8)ShaderType::VertexShader );
		RenderingHelper::BindBuffer( m_renderer, m_meshTransformBuffer.Ptr(), 2, (uint8)ShaderType::VertexShader );

		DrawCommand drawCommand;
		drawCommand.BaseVertex = 0;
		drawCommand.BufferOffset = 0;
		drawCommand.NumVertices = (uint32)shellMesh->GetNumIndicies();
		drawCommand.Topology = PrimitiveTopology::PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		drawCommand.VertexBuffer = shellMesh->GetVertexBuffer();
		drawCommand.IndexBufer = shellMesh->GetIndexBuffer();
		drawCommand.ExtendedIndex = true;
		drawCommand.Layout = m_layout.Ptr();

		m_renderer->Draw( drawCommand );
	}
}

// ================================ //
//
void				ShellMeshRenderer::Render			( TimeType time, OctreePtr octree, RenderTargetObject* svoRenderTarget, CameraActor* camera )
{
	m_blitEffect->Blit( m_renderer, m_shellMeshTarget->GetColorBuffer(), svoRenderTarget );
}

// ================================ //
//
void				ShellMeshRenderer::Init				( IRenderer* renderer, ResourceManager* resourceManager, LightModulePtr lights )
{
	m_resourceManager = resourceManager;
	m_renderer = renderer;

	m_blendingState = resourceManager->GetBlendingState( BlendingInfo() );
	m_rasterizerState = resourceManager->GetRasterizerState( RasterizerStateInfo() );
	m_depthStencilState = resourceManager->GetDepthStencilState( DepthStencilInfo() );

	// Layout
	auto animLayoutDesc = ShellMesh::CreateShellLayout();
	
	ShaderInputLayout* layout;

	m_vertexShader = resourceManager->LoadVertexShader( L"Shaders/ShellMesh/ShellMeshVS.hlsl", "main", &layout, animLayoutDesc );
	m_pixelShader = resourceManager->LoadPixelShader( L"Shaders/ShellMesh/ShellMeshPS.hlsl", "main" );

	m_layout = layout;

	m_blitEffect = std::unique_ptr< BlitEffect >( new BlitEffect( m_resourceManager ) );
}

// ================================ //
//
void				ShellMeshRenderer::ProcessInput		( const sw::input::MouseState& mouse, const sw::input::KeyboardState& keyboard )
{
	if( keyboard[ Keyboard::PhysicalKeys::KEY_1 ].IsKeyDownEvent() )
	{
		m_vertexShader = m_resourceManager->LoadVertexShader( L"Shaders/ShellMesh/ShellMeshVS.hlsl", "main" );
		m_pixelShader = m_resourceManager->LoadPixelShader( L"Shaders/ShellMesh/ShellMeshPS.hlsl", "main" );
	}
	else if( keyboard[ Keyboard::PhysicalKeys::KEY_2 ].IsKeyDownEvent() )
	{
		m_vertexShader = m_resourceManager->LoadVertexShader( L"Shaders/ShellMesh/ShellMeshVS.hlsl", "main" );
		m_pixelShader = m_resourceManager->LoadPixelShader( L"Shaders/ShellMesh/ShellMeshWeightsPS.hlsl", "main" );
	}
	else if( keyboard[ Keyboard::PhysicalKeys::KEY_3 ].IsKeyDownEvent() )
	{
		m_vertexShader = m_resourceManager->LoadVertexShader( L"Shaders/ShellMesh/ShellMeshAnimVS.hlsl", "main" );
		m_pixelShader = m_resourceManager->LoadPixelShader( L"Shaders/ShellMesh/ShellMeshAnimPS.hlsl", "main" );
	}
	else if( keyboard[ Keyboard::PhysicalKeys::KEY_4 ].IsKeyDownEvent() )
	{
		m_vertexShader = m_resourceManager->LoadVertexShader( L"Shaders/ShellMesh/ShellMeshPaintWeightsVS.hlsl", "main" );
		m_pixelShader = m_resourceManager->LoadPixelShader( L"Shaders/ShellMesh/ShellMeshPaintWeightsPS.hlsl", "main" );
	}
	else if( keyboard[ Keyboard::PhysicalKeys::KEY_ADD ].IsKeyDownEvent() )
	{
		m_helperConsts.ShowBlendWeightsIdx++;
	}
	else if( keyboard[ Keyboard::PhysicalKeys::KEY_NUMPADMINUS ].IsKeyDownEvent() )
	{
		if( m_helperConsts.ShowBlendWeightsIdx > 0 )
			m_helperConsts.ShowBlendWeightsIdx--;
	}
}


//====================================================================================//
//			Data transfer to GPU	
//====================================================================================//


// ================================ //
//
void				ShellMeshRenderer::UpdateCamera		( CameraActor* camera )
{
	CameraData data = camera->GetCameraData();

	CameraConstants cameraData;
	cameraData.ProjectionMatrix = Transpose( camera->GetProjection() );
	cameraData.ViewMatrix = Transpose( camera->GetView() );
	cameraData.CameraPosition = data.Position;

	if( !m_cameraBuffer )
		m_cameraBuffer = m_resourceManager->CreateConstantsBuffer( L"Camera constant buffer", (uint8*)&cameraData, sizeof( CameraConstants ) );
	else
		RenderingHelper::UpdateBuffer( m_renderer, m_cameraBuffer.Ptr(), cameraData );

}

// ================================ //
//
void				ShellMeshRenderer::UpdateAnimation			( TimeType time, ShellMeshPtr shellMesh )
{
	auto bonesTransforms = shellMesh->Evaluate( time );

	if( bonesTransforms.size() > 200 )
		throw std::runtime_error( "Number of bones exceeds max value." );

	uint32 bufferSize = sizeof( Transform ) * (uint32)bonesTransforms.size();

	if( !m_bonesBuffer )
	{
		m_bonesBuffer = m_resourceManager->CreateConstantsBuffer( L"BonesTransforms", (uint8*)bonesTransforms.data(), bufferSize );
		return;
	}

	if( m_bonesBuffer->GetElementSize() != bufferSize )
	{
		// @todo Here we should free previous buffer.
		m_bonesBuffer = m_resourceManager->CreateConstantsBuffer( L"BonesTransforms", (uint8*)bonesTransforms.data(), bufferSize );
		return;
	}

	UpdateBufferCommand updateCommand;
	updateCommand.Buffer = m_bonesBuffer.Ptr();
	updateCommand.FillData = (uint8*)bonesTransforms.data();
	updateCommand.Size = bufferSize;

	m_renderer->UpdateBuffer( updateCommand );
}

// ================================ //
//
void				ShellMeshRenderer::UpdateMeshBuffer			( ShellMeshPtr shellMesh )
{
	MeshContants meshConstants;
	meshConstants.Translate = shellMesh->GetTranslate();
	meshConstants.Scale = shellMesh->GetScale();

	uint32 bufferSize = sizeof( MeshContants );

	if( !m_meshTransformBuffer )
	{
		m_meshTransformBuffer = m_resourceManager->CreateConstantsBuffer( L"ShellMeshTransforms", (uint8*)&meshConstants, bufferSize );
		return;
	}

	UpdateBufferCommand updateCommand;
	updateCommand.Buffer = m_meshTransformBuffer.Ptr();
	updateCommand.FillData = (uint8*)&meshConstants;
	updateCommand.Size = bufferSize;

	m_renderer->UpdateBuffer( updateCommand );
}

// ================================ //
//
void				ShellMeshRenderer::ReallocateRenderTarget	( uint16 newWidth, uint16 newHeight )
{
	// Allocate render target for shell mesh rendering result.
	RenderTargetDescriptor descriptor;
	descriptor.TextureWidth = newWidth;
	descriptor.TextureHeight = newHeight;
	descriptor.TextureType = TextureType::TEXTURE_TYPE_TEXTURE2D;
	descriptor.ColorBuffFormat = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	descriptor.DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D16_UNORM;
	descriptor.Usage = ResourceUsage::RESOURCE_USAGE_DEFAULT;

	m_shellMeshTarget = m_resourceManager->CreateRenderTarget( L"::ShellMeshTarget", descriptor );
	assert( m_shellMeshTarget );
}

// ================================ //
//
void				ShellMeshRenderer::UpdateHelperConstants	()
{
	uint32 bufferSize = sizeof( HelperConstants );

	if( !m_helperConstants )
	{
		m_helperConstants = m_resourceManager->CreateConstantsBuffer( L"HelperConstants", (uint8*)&m_helperConsts, bufferSize );
		return;
	}

	UpdateBufferCommand updateCommand;
	updateCommand.Buffer = m_helperConstants.Ptr();
	updateCommand.FillData = (uint8*)&m_helperConsts;
	updateCommand.Size = bufferSize;

	m_renderer->UpdateBuffer( updateCommand );
}

}	// vr


