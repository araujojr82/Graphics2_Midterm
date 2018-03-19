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

	//{// Room model (for stencil buffer example)
	//	::g_Room = new cGameObject();
	//	::g_Room->friendlyName = "Room";
	//	cPhysicalProperties physState;
	//	physState.position = glm::vec3( 0.0f, 0.0, 0.0f );
	//	physState.setOrientationEulerAngles( glm::vec3( 0.0, 0.0, 0.0f ) );
	//	::g_Room->SetPhysState( physState );
	//	sMeshDrawInfo meshInfo;
	//	meshInfo.scale = 50.0;
	//	//		meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
	//	//		meshInfo.bDrawAsWireFrame = true;
	//	//		meshInfo.bUseDebugColour = true;
	//	//		meshInfo.debugDiffuseColour = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f );
	//	meshInfo.name = "Room_2_Bigger_Triangulated.ply";
	//	meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "GuysOnSharkUnicorn.bmp", 0.0f ) );
	//	meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "Utah_Teapot_xyz_n_uv_Enterprise.bmp", 1.0f ) );
	//	::g_Room->vecMeshes.push_back( meshInfo );
	//}
	//{// Stencil mask (matches frame for doorway in Room model)
	//	::g_RoomMaskForStencil = new cGameObject();
	//	::g_RoomMaskForStencil->friendlyName = "RoomDoorMask";
	//	cPhysicalProperties physState;
	//	physState.position = glm::vec3( 0.0f, 0.0, 0.0f );
	//	physState.setOrientationEulerAngles( glm::vec3( 0.0f, 0.0, 0.0f ) );
	//	::g_RoomMaskForStencil->SetPhysState( physState );
	//	sMeshDrawInfo meshInfo;
	//	meshInfo.scale = 50.0;
	//	//meshInfo.bUseDebugColour = true;
	//	//meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
	//	//meshInfo.bDrawAsWireFrame = true;
	//	meshInfo.name = "Just_Inside_Door_Frame_for_Masking.ply";
	//	meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "GuysOnSharkUnicorn.bmp", 1.0f ) );
	//	meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "Utah_Teapot_xyz_n_uv_Enterprise.bmp", 0.0f ) );
	//	::g_RoomMaskForStencil->vecMeshes.push_back( meshInfo );
	//}




	{ // Mirror
		::g_pMirrorObject = new cGameObject();
		::g_pMirrorObject->friendlyName = "Mirror";
		::g_pMirrorObject->scale = 5.0f;
		//::g_pMirrorObject->position = glm::vec3( 0.0f, 1.0f, 3.0f );
		::g_pMirrorObject->position = glm::vec3( 10.0f, -6, -40.0f );	// NEXT TO THE ROVER
		//::g_pMirrorObject->adjustQOrientationFormDeltaEuler( glm::vec3( glm::radians(90.0f), 0.0f, glm::radians( 90.0f ) ) );

		cMesh theMesh;
		theMesh.name = "mirror";

		if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "mirror.ply", theMesh ) )
		//if( !pModelAssetLoader->LoadPlyFileIntoMeshWith_Normals_and_UV( "RetroTV.edited.screenonly.ply", theMesh ) )
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
			meshInfo.scale = ::g_pMirrorObject->scale;
			meshInfo.setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );
			meshInfo.debugDiffuseColour = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
			meshInfo.name = "mirror";
			meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "metal.bmp", 1.0f ) );
			::g_pMirrorObject->vecMeshes.push_back( meshInfo );
			//::g_vecGameObjects.push_back( ::g_pMirrorObject );		// Fastest way to add
	}

	{	// Our skybox object
		::g_pSkyBoxObject = new cGameObject();
		::g_pSkyBoxObject->type = eTypeOfGO::SKYBOX;

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
		meshInfo.vecMeshCubeMaps.push_back( sTextureBindBlendInfo( "space", 1.0f ) );
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
		meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "metal.bmp", 1.0f ) );
		pTempGO->vecMeshes.push_back( meshInfo );
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add

		// Im adding a dummy GO to anchor the camera
		::g_pTheCameraDummy = new cGameObject();
		::g_pTheCameraDummy->friendlyName = "Dummy";
		::g_pTheCameraDummy->position = pTempGO->position;
	}

	{ // Terrain
		cGameObject* pTempGO = new cGameObject();
		pTempGO->friendlyName = "Terrain";
		pTempGO->type = eTypeOfGO::TERRAIN;
		pTempGO->scale = 1.0f;
		pTempGO->position = glm::vec3( 0.0f, 0.0, 0.0f );

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
		meshInfo.vecMehs2DTextures.push_back( sTextureBindBlendInfo( "mars2.bmp", 1.0f ) );
		pTempGO->vecMeshes.push_back( meshInfo );
		::g_vecGameObjects.push_back( pTempGO );		// Fastest way to add
	}
	
	return;
}