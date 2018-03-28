// This file is used to laod the models
#include "cGameObject.h"
#include <vector>
#include "Utilities.h"		// getRandInRange()
#include <glm/glm.hpp>
#include "globalGameStuff.h"

// For the cSimpleAssimpSkinnedMeshLoader class
#include "assimp/cSimpleAssimpSkinnedMeshLoader_OneMesh.h"
#include "assimp/cAssimpBasic.h"

#include "cAnimationState.h"

#include <iostream>

extern std::vector< cGameObject* >  g_vecGameObjects;
extern cGameObject* g_pTheDebugSphere;
extern cGameObject* g_pSkyBoxObject;
extern cGameObject* g_pMirrorObject;

cSimpleAssimpSkinnedMesh* createSkinnedMesh( std::string meshFilename )
{
	cSimpleAssimpSkinnedMesh* theSkinnedMesh = new cSimpleAssimpSkinnedMesh();

	// Load the animation AND the mesh to be used for this model
	if( !theSkinnedMesh->LoadMeshFromFile( meshFilename ) )
	{
		std::cout << "Error: problem loading the skinned mesh" << std::endl;
	}

	return theSkinnedMesh;
}

cSimpleAssimpSkinnedMesh* createSkinnedMesh( std::vector<sAnimDesc> theAnimations )
{
	cSimpleAssimpSkinnedMesh* theSkinnedMesh = new cSimpleAssimpSkinnedMesh();

	for( int i = 0; i != theAnimations.size(); i++ )
	{
		switch( theAnimations[i].type )
		{			
			case eAnimationType::BASE :				
				// Load the animation AND the mesh to be used for this model
				if( !theSkinnedMesh->LoadMeshFromFile( theAnimations[i].filePath ) )
				{
					std::cout << "Error: problem loading the skinned mesh" << std::endl;
				}
				break;
			default:
				// Load just the animation
				if( !theSkinnedMesh->LoadMeshAnimation( theAnimations[i].filePath ) )
				{
					std::cout << "Error: problem loading the skinned mesh" << std::endl;
				}
				break;
		}		
	}

	return theSkinnedMesh;
}

bool createMeshFromSkinnedMesh( cSimpleAssimpSkinnedMesh* theSkinnedMesh, int shaderID, cVAOMeshManager* pVAOManager )
{
	cMesh* pTheMesh = theSkinnedMesh->CreateMeshObjectFromCurrentModel();

	if( pTheMesh )
	{
		if( !pVAOManager->loadMeshIntoVAO( *pTheMesh, shaderID, false ) )
		{
			std::cout << "Could not load skinned mesh model into new VAO" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Could not create a cMesh object from skinned mesh file" << std::endl;
		return false;
	}
	// Delete temporary mesh if still around
	if( pTheMesh )
	{
		delete pTheMesh;
	}
	return true;
}

void LoadModelsIntoScene( int shaderID, cVAOMeshManager* pVAOManager )
{

	cModelAssetLoader* pModelAssetLoader = new cModelAssetLoader();
	pModelAssetLoader->setBasePath( "assets/models/" );

	cAssimpBasic myAssimpLoader;
	std::string error;

	{ // ======================================
	  // CREATING FIRST TV
	  // ======================================
		cGameObject* pTempGO = new cGameObject();
		pTempGO->friendlyName = "TV1";
		pTempGO->scale = 0.1f;
		pTempGO->position = glm::vec3( 7.0f, -6, -30.0f );	// NEXT TO THE ROVER
		pTempGO->textureNames[0] = "metal.bmp";
		pTempGO->textureBlend[0] = 1.0f;

		cMesh theMesh;
		theMesh.name = "tv";

		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "RetroTV.edited.bodyonly_xz.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}

		sMeshDrawInfo meshInfo;
		meshInfo.scale = pTempGO->scale;
		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		meshInfo.name = "tv";
		//meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "metal.bmp", 1.0f ) );
		pTempGO->vecMeshes.push_back( meshInfo );
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
		::g_vecGameObjectsForTVscene.push_back( pTempGO );	// ADDING IT TO THE SCENE VECTOR

	}
	
	{	// ======================================
		// AND THE FIRST SCREEN
		// ======================================
		::g_pTVScreen1 = new cGameObject();
		::g_pTVScreen1->friendlyName = "TVScreen1";
		::g_pTVScreen1->scale = 0.1f;
		::g_pTVScreen1->position = glm::vec3( 7.0f, -6, -30.0f );	// SAME POSITION AS THE TV
		::g_pTVScreen1->textureNames[0] = "tvscreen.bmp";
		::g_pTVScreen1->textureBlend[0] = 1.0f;
		cMesh theMesh;
		theMesh.name = "tvscreen";

		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "RetroTV.edited.screenonly_xz.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}

		sMeshDrawInfo meshInfo;
		meshInfo.scale = ::g_pTVScreen1->scale;
		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		meshInfo.name = "tvscreen";
		//meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "tvscreen.bmp", 1.0f ) );
		::g_pTVScreen1->vecMeshes.push_back( meshInfo );
		//::g_vecGameObjects.push_back( ::g_pTVScreen1 );		// Fastest way to add
	}

	{ // ======================================
	  // CREATING SECOND TV
	  // ======================================
		cGameObject* pTempGO = new cGameObject();
		pTempGO->friendlyName = "TV1";
		pTempGO->scale = 0.1f;
		pTempGO->position = glm::vec3( -7.0f, -6, -30.0f );
		pTempGO->textureNames[0] = "wood.bmp";
		pTempGO->textureBlend[0] = 1.0f;

		cMesh theMesh;
		theMesh.name = "tv";

		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "RetroTV.edited.bodyonly_xz.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}

		sMeshDrawInfo meshInfo;
		meshInfo.scale = pTempGO->scale;
		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		meshInfo.name = "tv";
		//meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "wood.bmp", 1.0f ) );
		pTempGO->vecMeshes.push_back( meshInfo );
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
		::g_vecGameObjectsForTVscene.push_back( pTempGO );	// ADDING IT TO THE SCENE VECTOR

	}

	{	// ======================================
		// AND THE SECOND SCREEN
		// ======================================
		::g_pTVScreen2 = new cGameObject();
		::g_pTVScreen2->friendlyName = "TVScreen1";
		::g_pTVScreen2->scale = 0.1f;
		::g_pTVScreen2->position = glm::vec3( -7.0f, -6, -30.0f );	// SAME POSITION AS THE TV
		::g_pTVScreen2->textureNames[0] = "tvscreen.bmp";
		::g_pTVScreen2->textureBlend[0] = 1.0f;

		cMesh theMesh;
		theMesh.name = "tvscreen";

		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "RetroTV.edited.screenonly_xz.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}

		sMeshDrawInfo meshInfo;
		meshInfo.scale = ::g_pTVScreen2->scale;
		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		meshInfo.name = "tvscreen";
		//meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "tvscreen.bmp", 1.0f ) );
		::g_pTVScreen2->vecMeshes.push_back( meshInfo );
		//::g_vecGameObjects.push_back( ::g_pTVScreen1 );		// Fastest way to add
	}


	//{ // Mirror
	//	::g_pMirrorObject = new cGameObject();
	//	::g_pMirrorObject->friendlyName = "Mirror";
	//	::g_pMirrorObject->scale = 5.0f;
	//	//::g_pMirrorObject->position = glm::vec3( 0.0f, 1.0f, 3.0f );
	//	::g_pMirrorObject->position = glm::vec3( 10.0f, -6, -40.0f );	// NEXT TO THE ROVER
	//	//::g_pMirrorObject->adjustQOrientationFormDeltaEuler( glm::vec3( glm::radians(90.0f), 0.0f, glm::radians( 90.0f ) ) );

	//	cMesh theMesh;
	//	theMesh.name = "mirror";

	//	if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "mirror.ply", theMesh ) )
	//	//if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "RetroTV.edited.screenonly.ply", theMesh ) )
	//	{
	//		std::cout << "Didn't load model" << std::endl;
	//	}
	//	// ***********************************************************************
	//	// NOTE the TRUE so that it keeps the mesh!!!
	//	else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
	//	{
	//		std::cout << "Could not load mesh into VAO" << std::endl;
	//	}
	//	
	//		sMeshDrawInfo meshInfo;
	//		meshInfo.scale = ::g_pMirrorObject->scale;
	//		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
	//		meshInfo.name = "mirror";
	//		meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "metal.bmp", 1.0f ) );
	//		::g_pMirrorObject->vecMeshes.push_back( meshInfo );
	//		//::g_vecGameObjects.push_back( ::g_pMirrorObject );		// Fastest way to add
	//}

	{	// Our skybox object
		::g_pSkyBoxObject = new cGameObject();
		::g_pSkyBoxObject->type = eTypeOfGO::SKYBOX;
		::g_pSkyBoxObject->textureNames[0] = "space";
		::g_pSkyBoxObject->textureBlend[0] = 1.0f;

		cMesh theMesh;

		if( !pModelAssetLoader->LoadPlyFileIntoMeshWithNormals( "skybox_sphere.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}

		sMeshDrawInfo meshInfo;
		meshInfo.scale = 10000.0f;
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		meshInfo.name = theMesh.name;
		//meshInfo.vecMeshCubeMaps.push_back( sTextureBindBlendInfo( "space", 1.0f ) );
		meshInfo.bIsSkyBoxObject = true;
		::g_pSkyBoxObject->vecMeshes.push_back( meshInfo );
		// IS SKYBOX
		::g_vecGameObjects.push_back( ::g_pSkyBoxObject );		// Fastest way to add
	}

	{ // The Rover

		cGameObject* g_pTheCameraDummy = new cGameObject();
		g_pTheCameraDummy->friendlyName = "Dummy";

		cGameObject* pTempGO = new cGameObject();
		pTempGO->friendlyName = "Rover";
		pTempGO->type = eTypeOfGO::CHARACTER;
		pTempGO->scale = 0.01f;
		pTempGO->position = glm::vec3( 10.0f, -6.63, -50.0f );
		pTempGO->textureNames[0] = "metal.bmp";
		pTempGO->textureBlend[0] = 1.0f;

		cMesh theMesh;

		theMesh.name = "rover";
		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "Entire_Lander_45686_faces.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}

		
		sMeshDrawInfo meshInfo;
		meshInfo.scale = pTempGO->scale;
		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		meshInfo.name = theMesh.name;
		//meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "metal.bmp", 1.0f ) );
		pTempGO->vecMeshes.push_back( meshInfo );
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add

		// Im adding a dummy GO to anchor the camera
		::g_pTheCamera2Dummy = new cGameObject();
		::g_pTheCamera2Dummy->friendlyName = "Dummy2";
		::g_pTheCamera2Dummy->position = pTempGO->position;
		
		// Im adding a dummy GO to anchor the camera
		::g_pTheCamera3Dummy = new cGameObject();
		::g_pTheCamera3Dummy->friendlyName = "Dummy3";
		::g_pTheCamera3Dummy->position = pTempGO->position;

	}

	{ // Terrain
		cGameObject* pTempGO = new cGameObject();
		pTempGO->friendlyName = "Terrain";
		pTempGO->type = eTypeOfGO::TERRAIN;
		pTempGO->scale = 1.0f;
		pTempGO->position = glm::vec3( 0.0f, 0.0, 0.0f );
		pTempGO->textureNames[0] = "mars2.bmp";
		pTempGO->textureBlend[0] = 1.0f;

		cMesh theMesh;

		theMesh.name = "terrain";
		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "CuriosityQR.ply", theMesh ) )
		{
			std::cout << "Didn't load model" << std::endl;
		}
		// ***********************************************************************
		// NOTE the TRUE so that it keeps the mesh!!!
		else if( !pVAOManager->loadMeshIntoVAO( theMesh, shaderID, true ) )
		{
			std::cout << "Could not load mesh into VAO" << std::endl;
		}
		
		sMeshDrawInfo meshInfo;
		meshInfo.scale = pTempGO->scale;
		meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		meshInfo.name = theMesh.name;
		//meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "mars2.bmp", 1.0f ) );
		pTempGO->vecMeshes.push_back( meshInfo );
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
	}
	
	return;
}