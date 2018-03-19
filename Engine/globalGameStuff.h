#ifndef _globalGameStuff_HG_
#define _globalGameStuff_HG_

// This is all the global 'game' stuff, so:
// - not OpenGL rendering stuff (unless we can't help it)
// - just 'engine' or game play stuff

#include "cGameObject.h"
#include <vector>
#include <glm/vec3.hpp>
#include "cLightManager.h"
#include "cModelAssetLoader.h"
#include "cMouseCamera.h"
#include "cSteeringManager.h"

// ******************************************************************
// These require the inclusion of the OpenGL and-or GLFW headers
#include "cVAOMeshManager.h"
#include "cShaderManager.h"
#include "Texture/CTextureManager.h"
#include "cDebugRenderer.h"
// ******************************************************************

// Remember to #include <vector>...
extern std::vector< cGameObject* >  g_vecGameObjects;

extern bool g_bIsWireframe;

// Returns 0 or NULL if not found
cGameObject* findObjectByFriendlyName( std::string friendlyName, std::vector<cGameObject*> &vec_pGameObjects );
cGameObject* findObjectByUniqueID( unsigned int ID, std::vector<cGameObject*> &vec_pGameObjects );

extern cLightManager*	g_pLightManager;	// (theMain.cpp)
											// Super basic physics update function
//void PhysicsStep( double deltaTime );

const std::string PLAYERNAME = "Rover";		// Now that we have a lookup
extern unsigned int g_theQuestionNumber;
extern cGameObject* g_pTheCameraDummy;

extern cGameObject* g_pThePlayerGO;

extern cModelAssetLoader* g_pModelAssetLoader;	// (ModelUtilies.cpp)

extern cMouseCamera* g_pTheMouseCamera;

extern cVAOMeshManager*			g_pVAOManager;		// (theMain.cpp)
extern cShaderManager*			g_pShaderManager;	// (theMain.cpp)
extern CTextureManager*			g_pTextureManager;	// (theMain.cpp)
extern cDebugRenderer*			g_pDebugRenderer;	// (theMain.cpp)

void RenderScene( std::vector< cGameObject* > &vec_pGOs, GLFWwindow* pGLFWWindow, double deltaTime );

extern	GLFWwindow* g_pGLFWWindow;	// In TheMain.cpp
extern bool g_IsWindowFullScreen;	// false at start
void setWindowFullScreenOrWindowed( GLFWwindow* pTheWindow, bool IsFullScreen );	// In TheMain.cpp

#endif
