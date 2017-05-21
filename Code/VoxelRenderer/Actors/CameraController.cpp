
#include "CameraController.h"
#include "DynamicActor.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< SpectatorCameraController >( "SpectatorCameraController" );
}


using namespace DirectX;
using namespace sw::input;



/**@brief */
SpectatorCameraController::SpectatorCameraController( const sw::input::MouseState& mouse, const sw::input::KeyboardState& keyboard )
	:	m_mouse( mouse )
	,	m_keyboard( keyboard )
	,	m_verticalAngle( 0.0f )
	,	m_horizontalAngle( 0.0f )
{
	m_moveSpeed = 0.10f;
	m_buttonRotSpeed = 1.0f;
	m_axisRotSpeed = 120.0f;
	m_zoomSpeed = 100.0f;
}

/**@brief */
SpectatorCameraController::~SpectatorCameraController()
{}




/*Funkcja g��wna odpowiedzialna za sterowanie ruchem obiektu.*/
void		SpectatorCameraController::ControlObjectPre		( DynamicActor* actor, IControllersState* globalState )
{
	// Turn left and right
	if( m_keyboard[ Keyboard::PhysicalKeys::KEY_Q ].IsPressed() &&
		!m_keyboard[ Keyboard::PhysicalKeys::KEY_E ].IsPressed() )
	{
		m_horizontalAngle += -m_buttonRotSpeed;
	}
	else if( m_keyboard[ Keyboard::PhysicalKeys::KEY_E ].IsPressed() &&
		!m_keyboard[ Keyboard::PhysicalKeys::KEY_Q ].IsPressed() )
	{
		m_horizontalAngle += m_buttonRotSpeed;
	}



	XMVECTOR forward = XMVectorSet( 0.0, 0.0, 0.0, 0.0 );
	XMVECTOR left = XMVectorSet( 0.0, 0.0, 0.0, 0.0 );
	XMVECTOR up = XMVectorSet( 0.0, 0.0, 0.0, 0.0 );

	// Forward and backward movement along seeing direction.
	if( m_keyboard[ Keyboard::PhysicalKeys::KEY_W ] && !m_keyboard[ Keyboard::PhysicalKeys::KEY_S ] )
	{
		forward = ForwardVector( actor );
		forward *= m_moveSpeed;
	}
	else if( m_keyboard[ Keyboard::PhysicalKeys::KEY_S ] && !m_keyboard[ Keyboard::PhysicalKeys::KEY_W ] )
	{
		forward = BackwardVector( actor );
		forward *= m_moveSpeed;
	}

	if( m_mouse.GetAxesState()[ Mouse::PhysicalAxes::WHEEL ] != 0.0f )
	{
		forward += ForwardVector( actor ) * m_zoomSpeed * m_mouse.GetAxesState()[ Mouse::PhysicalAxes::WHEEL ];
	}

	// Left and right movement
	if( m_keyboard[ Keyboard::PhysicalKeys::KEY_A ] && !m_keyboard[ Keyboard::PhysicalKeys::KEY_D ] )
	{
		left = LeftVector( actor );
		left *= m_moveSpeed;
	}
	else if( m_keyboard[ Keyboard::PhysicalKeys::KEY_D ] && !m_keyboard[ Keyboard::PhysicalKeys::KEY_A ] )
	{
		left = RightVector( actor );
		left *= m_moveSpeed;
	}

	// Up and Down movement
	if( m_keyboard[ Keyboard::PhysicalKeys::KEY_R ] && !m_keyboard[ Keyboard::PhysicalKeys::KEY_F ] )
		up = XMVectorSet( 0.0, 1.0, 0.0, 0.0 ) * m_moveSpeed;
	else if( m_keyboard[ Keyboard::PhysicalKeys::KEY_F ] && !m_keyboard[ Keyboard::PhysicalKeys::KEY_R ] )
		up = XMVectorSet( 0.0, -1.0, 0.0, 0.0 ) * m_moveSpeed;


	if( m_mouse.RightButton()->IsPressed() )
	{
		float yAxis = m_mouse.GetAxesState()[ Mouse::PhysicalAxes::Y_AXIS ];
		if( yAxis != 0.0f )
			m_verticalAngle += yAxis * m_axisRotSpeed;

		float xAxis = m_mouse.GetAxesState()[ Mouse::PhysicalAxes::X_AXIS ];
		if( xAxis != 0.0f )
			m_horizontalAngle += xAxis * m_axisRotSpeed;
	}

	XMVECTOR verticalRotationQuat = XMQuaternionRotationNormal( RightVector( actor ), m_verticalAngle );
	XMVECTOR horizontalRotationQuat = XMQuaternionRotationNormal( XMVectorSet( 0.0, 1.0, 0.0, 0.0 ), m_horizontalAngle );

	actor->TeleportOrientation( XMQuaternionMultiply( verticalRotationQuat, horizontalRotationQuat ) );

	// Teleport after rotations. RightVector uses actor orientation.
	XMVECTOR translation = forward + left + up;
	actor->Teleport( actor->GetPosition() + translation );

}

/**@brief Funkcja nic nie robi.

W trybie debug funkcja zatrzymuje si� na assercie.*/
void SpectatorCameraController::ControlObjectPost( DynamicActor* actor, IControllersState* globalState )
{
	//assert( !"This is only pre controlled class." );
}

// ================================ //
//
void	SpectatorCameraController::Initialize		( DynamicActor* actor )
{}

//====================================================================================//
//			Helpers	
//====================================================================================//

// ================================ //
//
DirectX::XMVECTOR			SpectatorCameraController::ForwardVector	( DynamicActor* actor )
{
	XMVECTOR versor = XMVectorSet( 0.0, 0.0, -1.0, 0.0 );
	XMVECTOR orientation = actor->GetOrientation();
	return XMVector3Rotate( versor, orientation );
}

// ================================ //
//
DirectX::XMVECTOR			SpectatorCameraController::BackwardVector	( DynamicActor* actor )
{
	return XMVectorNegate( ForwardVector( actor ) );
}

// ================================ //
//
DirectX::XMVECTOR			SpectatorCameraController::LeftVector		( DynamicActor* actor )
{
	return XMVectorNegate( RightVector( actor ) );
}

// ================================ //
//
DirectX::XMVECTOR			SpectatorCameraController::RightVector		( DynamicActor* actor )
{
	XMVECTOR versor = XMVectorSet( 1.0, 0.0, 0.0, 0.0 );
	XMVECTOR orientation = actor->GetOrientation();
	return XMVector3Rotate( versor, orientation );
}
