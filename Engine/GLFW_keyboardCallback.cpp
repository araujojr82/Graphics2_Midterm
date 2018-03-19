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
	
	switch( key )
	{
	case GLFW_KEY_A:		// Left
		if( isShiftKeyDown( mods, true ) )
		{
			if( action == GLFW_PRESS )
			{
				
			}
			if( action == GLFW_RELEASE )
			{
				
			}
		}
		else
		{	
			if( action == GLFW_PRESS )
			{
				
			}
			if( action == GLFW_RELEASE )
			{
				
			}
		}
		break;
	case GLFW_KEY_D:		// Right

		if( isShiftKeyDown( mods, true ) )
		{
			if( action == GLFW_PRESS )
			{
				
			}
			if( action == GLFW_RELEASE )
			{
				
			}
		}
		else
		{
			if( action == GLFW_PRESS )
			{
				
			}
			if( action == GLFW_RELEASE )
			{
				
			}
		}
		break;
	case GLFW_KEY_W:		// Forward
		if( isShiftKeyDown( mods, true ) )
		{
			if( action == GLFW_PRESS )
			{
				
			}
			if( action == GLFW_RELEASE )
			{
			
			}
		}
		else
		{
			if( action == GLFW_PRESS )
			{
			
			}
			if( action == GLFW_RELEASE )
			{
			
			}
		}
		break;
	case GLFW_KEY_S:		// Backwards
		if( action == GLFW_PRESS )
		{
		
		}
		if( action == GLFW_RELEASE )
		{
		
		}				
		break;
	case GLFW_KEY_Q:		// Turn Left
		if( action == GLFW_PRESS )
		{
		
		}
		if( action == GLFW_RELEASE )
		{
		
		}
		break;
	case GLFW_KEY_E:		// Turn Right

		if( action == GLFW_PRESS )
		{
		
		}
		if( action == GLFW_RELEASE )
		{

		}
		break;

	case GLFW_KEY_T:		// Perform Action

		if( action == GLFW_PRESS )
		{
		}
		break;

	case GLFW_KEY_SPACE:
		if( action == GLFW_PRESS )
		{						

		}
		break;

	case GLFW_KEY_UP:
		break;

	case GLFW_KEY_DOWN:
		break;

	case GLFW_KEY_LEFT:		
		break;

	case GLFW_KEY_RIGHT:		
		break;
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