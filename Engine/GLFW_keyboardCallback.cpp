#include "globalOpenGL_GLFW.h"
#include "globalGameStuff.h"

#include <iostream>

#include "cAnimationState.h"

extern cSteeringManager* g_pSteeringManager;

bool isShiftKeyDown( int mods, bool bByItself = true );
bool isCtrlKeyDown( int mods, bool bByItself = true );
bool isAltKeyDown( int mods, bool bByItself = true );

bool bIsWKeyDown = false;

extern GLint g_renderID;

extern bool g_outline;

/*static*/ void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{

	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GLFW_TRUE );

	if( key == GLFW_KEY_0 && action == GLFW_PRESS )
		::g_renderID++;	
	
	if( key == GLFW_KEY_ENTER && action == GLFW_PRESS )
	{
		::g_bIsWireframe = !::g_bIsWireframe;
	}

	//const float CAMERASPEED = 1.0f;

	//switch( key )
	//{
	//	case GLFW_KEY_1:
	//		::g_pLightManager->vecLights[0].attenuation.y *= 0.99f;	// less 1%
	//		break;
	//	case GLFW_KEY_2:
	//		::g_pLightManager->vecLights[0].attenuation.y *= 1.01f; // more 1%
	//		if( ::g_pLightManager->vecLights[0].attenuation.y <= 0.0f )
	//		{
	//			::g_pLightManager->vecLights[0].attenuation.y = 0.001f;	// Some really tiny value
	//		}
	//		break;
	//	case GLFW_KEY_3:	// Quad
	//		::g_pLightManager->vecLights[0].attenuation.z *= 0.99f;	// less 1%
	//		break;
	//	case GLFW_KEY_4:	//  Quad
	//		::g_pLightManager->vecLights[0].attenuation.z *= 1.01f; // more 1%
	//		if( ::g_pLightManager->vecLights[0].attenuation.z <= 0.0f )
	//		{
	//			::g_pLightManager->vecLights[0].attenuation.z = 0.001f;	// Some really tiny value
	//		}
	//		break;
	//		// Lights
	//		// CAMERA and lighting
	//	case GLFW_KEY_A:		// Left
	//		::g_pLightManager->vecLights[0].position.x -= CAMERASPEED;
	//		break;
	//	case GLFW_KEY_D:		// Right
	//		::g_pLightManager->vecLights[0].position.x += CAMERASPEED;
	//		break;
	//	case GLFW_KEY_W:		// Forward (along z)
	//		::g_pLightManager->vecLights[0].position.z += CAMERASPEED;
	//		break;
	//	case GLFW_KEY_S:		// Backwards (along z)
	//		::g_pLightManager->vecLights[0].position.z -= CAMERASPEED;
	//		break;
	//	case GLFW_KEY_Q:		// "Down" (along y axis)
	//		::g_pLightManager->vecLights[0].position.y -= CAMERASPEED;
	//		break;
	//	case GLFW_KEY_E:		// "Up" (along y axis)
	//		::g_pLightManager->vecLights[0].position.y += CAMERASPEED;
	//		break;		
	//};//switch (key)

	//  // HACK: print output to the console
	//  	std::cout << "Light[0] linear atten: "
	//  		<< ::g_pLightManager->vecLights[0].attenuation.y << ", "
	//  		<< ::g_pLightManager->vecLights[0].attenuation.z << std::endl;



	if( key == GLFW_KEY_1 && action == GLFW_PRESS )
	{		
		::g_theQuestionNumber = 1;
		::g_pTheMouseCamera->Position = ::g_pThePlayerGO->position + glm::vec3( -8.0f, 2.0f, -8.0f );
		::g_pTheMouseCamera->Pitch = -5.0f;
		::g_pTheMouseCamera->Yaw = 45.0f;
		::g_pTheMouseCamera->updateCameraVectors();
	}
	if( key == GLFW_KEY_2 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 2;
		
		::g_pTheMouseCamera->Target = ::g_pTheCameraDummy;
		::g_pTheMouseCamera->Pitch = -10.0f;		
		::g_pTheMouseCamera->moveCamera();
	}
	if( key == GLFW_KEY_3 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 3;

		::g_camera3Timer = 0.0f;
		::g_pTheCameraDummy->overwrtiteQOrientationFromEuler( glm::vec3( 0.0f, 0.0f, 0.0f ) );

		::g_pTheMouseCamera->Target = ::g_pTheCameraDummy;
		::g_pTheMouseCamera->Position = ::g_pThePlayerGO->position + glm::vec3( -4.0f, 2.0f, -4.0f );
		::g_pTheMouseCamera->Pitch = -5.0f;
		::g_pTheMouseCamera->moveCamera();
		
	}
	if( key == GLFW_KEY_4 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 4;
	}
	if( key == GLFW_KEY_5 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 5;
	}
	if( key == GLFW_KEY_6 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 6;
	}

	if( key == GLFW_KEY_A && action == GLFW_PRESS )
	{
		::g_pTheCameraDummy->adjustQOrientationFormDeltaEuler( glm::vec3( 0.0f, 0.1f, 0.0f ) );
	}

	if( key == GLFW_KEY_D && action == GLFW_PRESS )
	{
		::g_pTheCameraDummy->adjustQOrientationFormDeltaEuler( glm::vec3( 0.0f, -0.1f, 0.0f ) );
	}
	

	return;
}

// Helper functions
bool isShiftKeyDown( int mods, bool bByItself /*=true*/ )
{
	if( bByItself )
	{	// shift by itself?
		if( mods == GLFW_MOD_SHIFT )	{ return true; }
		else							{ return false; }
	}
	else
	{	// shift with anything else, too
		if( ( mods && GLFW_MOD_SHIFT ) == GLFW_MOD_SHIFT )	{ return true; }
		else												{ return false; }
	}
	// Shouldn't never get here, so return false? I guess?
	return false;
}

bool isCtrlKeyDown( int mods, bool bByItself /*=true*/ )
{
	if( bByItself )
	{	// shift by itself?
		if( mods == GLFW_MOD_CONTROL )	{ return true; }
		else							{ return false; }
	}
	else
	{	// shift with anything else, too
		if( ( mods && GLFW_MOD_CONTROL ) == GLFW_MOD_CONTROL )	{ return true; }
		else												{ return false; }
	}
	// Shouldn't never get here, so return false? I guess?
	return false;
}

bool isAltKeyDown( int mods, bool bByItself /*=true*/ )
{
	if( bByItself )
	{	// shift by itself?
		if( mods == GLFW_MOD_ALT ) { return true; }
		else { return false; }
	}
	else
	{	// shift with anything else, too
		if( ( mods && GLFW_MOD_ALT ) == GLFW_MOD_ALT ) { return true; }
		else { return false; }
	}
	// Shouldn't never get here, so return false? I guess?
	return false;
}