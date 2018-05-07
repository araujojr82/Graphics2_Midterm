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

extern bool TVASelected;
extern bool TVAStatus;
extern bool TVBStatus;
extern bool TVAChannel;
extern bool TVBChannel;

extern float TVAStaticCount;
extern float TVBStaticCount;

/*static*/ void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{

	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GLFW_TRUE );

	if( key == GLFW_KEY_TAB && action == GLFW_PRESS )
	{
		if( TVASelected )
		{
			TVAChannel = !TVAChannel;
			TVAStaticCount = 0.0f;
		}			
		else
		{
			TVBChannel = !TVBChannel;
			TVBStaticCount = 0.0f;
		}
			
	}

	//if( key == GLFW_KEY_9 && action == GLFW_PRESS )
	//{
	//	::g_renderID--;
	//	std::cout << "Screen Text ID: " << g_renderID << std::endl;
	//}
	//	

	//if( key == GLFW_KEY_0 && action == GLFW_PRESS )
	//{
	//	::g_renderID++;
	//	std::cout << "Screen Text ID: " << g_renderID << std::endl;
	//}

	if( key == GLFW_KEY_ENTER && action == GLFW_PRESS )
	{
		if( isAltKeyDown( mods, true ) )
		{
			::g_IsWindowFullScreen = !::g_IsWindowFullScreen;
			setWindowFullScreenOrWindowed( ::g_pGLFWWindow, ::g_IsWindowFullScreen );
		}
		else
		{
			if( TVASelected )
				TVAStatus = !TVAStatus;
			else
				TVBStatus = !TVBStatus;
		}
	}
	
	if( key == GLFW_KEY_1 && action == GLFW_PRESS )
	{	
		::g_theQuestionNumber = 1;

		::g_pTheMouseCamera = ::g_pTheCamera1;	// SETTING IT TO DEFAULT CAMERA
	}
	if( key == GLFW_KEY_2 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 2;
		
		::g_pTheMouseCamera = ::g_pTheCamera2;
	}
	if( key == GLFW_KEY_3 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 3;

		::g_camera3Timer = 0.0f;
		
		::g_pTheMouseCamera = ::g_pTheCamera3;
	}
	if( key == GLFW_KEY_4 && action == GLFW_PRESS )
	{
		::g_theQuestionNumber = 4;
		::g_pTheMouseCamera = ::g_pTheCamera0;
	}
	if( key == GLFW_KEY_5 && action == GLFW_PRESS )
	{
		TVASelected = true;
	}
	if( key == GLFW_KEY_6 && action == GLFW_PRESS )
	{
		TVASelected = false;
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