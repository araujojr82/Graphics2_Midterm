#include "ModelUtilities.h" 
#include "cVAOMeshManager.h"
#include "cMesh.h"
#include <sstream>
#include <vector>
#include "cGameObject.h"
#include "cModelAssetLoader.h"
#include "assimp/cAssimpBasic.h"
#include <iostream>
#include "assimp/cSimpleAssimpSkinnedMeshLoader_OneMesh.h"

// Returns 0 or NULL if not found
cGameObject* findObjectByFriendlyName( std::string friendlyName, std::vector<cGameObject*> &vec_pGameObjects )
{
	// Linear search, baby!
	unsigned int numObjects = ( unsigned int )vec_pGameObjects.size();
	for( unsigned int index = 0; index != numObjects; index++ )
	{
		if( vec_pGameObjects[index]->friendlyName == friendlyName )
		{
			return vec_pGameObjects[index];
		}
	}
	// Didn't find it
	return NULL;
}

cGameObject* findObjectByUniqueID( unsigned int ID, std::vector<cGameObject*> &vec_pGameObjects )
{
	// Linear search, baby!
	unsigned int numObjects = ( unsigned int )vec_pGameObjects.size();
	for( unsigned int index = 0; index != numObjects; index++ )
	{
		if( ID = vec_pGameObjects[index]->getUniqueID() )
		{
			return vec_pGameObjects[index];
		}
	}
	// Didn't find it
	return NULL;
}



bool Load3DModelsIntoMeshManager( int shaderID,
								  cVAOMeshManager* pVAOManager,
								  cModelAssetLoader* pModelAssetLoader,
								  std::string &error )
{
	std::stringstream ssError;
	bool bAllGood = true;


	////// *******************************************************
	////    ___  _    _                      _  __  __           _     
	////   / __|| |__(_) _ _   _ _   ___  __| ||  \/  | ___  ___| |_   
	////   \__ \| / /| || ' \ | ' \ / -_)/ _` || |\/| |/ -_)(_-<| ' \  
	////   |___/|_\_\|_||_||_||_||_|\___|\__,_||_|  |_|\___|/__/|_||_| 
	////                                                               
	//::g_pRPGSkinnedMesh = new cSimpleAssimpSkinnedMesh();

	//if( !::g_pRPGSkinnedMesh->LoadMeshFromFile( "assets/models/rick/Idle.fbx" ) )
	//{
	//	std::cout << "Error: problem loading the skinned mesh" << std::endl;
	//}
	//// Now load another animation file...
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Breathing Idle.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Crouched Sneaking Left.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Crouched Sneaking Right.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Gangnam Style.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Jumping.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Left Strafe Walk.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Right Strafe Walk.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Running.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Walking Backward.fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "assets/models/rick/Walking.fbx" );


	//::g_pRPGSkinnedMesh->friendlyName = "Rick";

	//cMesh* pTheMesh = ::g_pRPGSkinnedMesh->CreateMeshObjectFromCurrentModel();

	//if( pTheMesh )
	//{
	//	if( !pVAOManager->loadMeshIntoVAO( *pTheMesh, shaderID, false ) )
	//	{
	//		std::cout << "Could not load skinned mesh model into new VAO" << std::endl;
	//	}
	//}
	//else
	//{
	//	std::cout << "Could not create a cMesh object from skinned mesh file" << std::endl;
	//}
	//// Delete temporary mesh if still around
	//if( pTheMesh )
	//{
	//	delete pTheMesh;
	//}

	//****************************************************************************************

	if( !bAllGood )
	{
		// Copy the error string stream into the error string that
		//	gets "returned" (through pass by reference)
		error = ssError.str();
	}

	return bAllGood;
}