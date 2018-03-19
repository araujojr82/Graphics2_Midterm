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

	if( key == GLFW_KEY_1 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 1;
	}
	if( key == GLFW_KEY_2 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 2;
		
		::g_pTheMouseCamera->Target = ::g_pTheCameraDummy;
		//::g_pTheMouseCamera->Position.y + 5.0f;
		::g_pTheMouseCamera->Pitch = -10.0f;
		
		::g_pTheMouseCamera->moveCamera();
		//::g_pTheMouseCamera->updateCameraVectors();
	}
	if( key == GLFW_KEY_3 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 3;
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