#include "cGameObject.h"

#include <iostream>

// Start the unique IDs at 1. Why not?
/*static*/ unsigned int cGameObject::m_nextUniqueID = 1;

cGameObject::cGameObject()
{
	this->scale = 1.0f;	// (not zero)
	this->position = glm::vec3(0.0f);
	this->prevPosition = glm::vec3( NULL );
	this->overwrtiteQOrientationFromEuler( glm::vec3( 0.0f, 0.0f, 0.0f ) );

	this->vel = glm::vec3( 0.0f );
	this->accel = glm::vec3( 0.0f );

	// If you aren't sure what the 4th value should be,
	// make it a 1.0f ("alpha" or transparecy)
	this->diffuseColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	//Assume everything is simulated 
	this->bIsUpdatedInPhysics = true; //??? 
	this->radius = 0.0f;	// Is this the best value??? Who knows?
	this->mass = 0.0f;
	this->inverseMass = 0.0f;
	this->typeOfObject = UNKNOWN;
	
	this->bIsLight = false;
	this->bIsWireFrame = false;
	
	this->myLight = NULL;
	
	//// Set all texture blend values to 0.0f (meaning NO texture)
	//for( int index = 0; index != NUMTEXTURES; index++ )
	//{
	//	this->textureBlend[index] = 0.0f;
	//}

	// Assign unque ID, the increment for next created object
	// (Note: if you write your own copy constructor, be sure to COPY this
	//	value, rather than generate a new one - i.e. call the c'tor again)
	this->m_UniqueID = cGameObject::m_nextUniqueID++;

	//this->pDebugRenderer = NULL;

	//this->bIsSkyBoxObject = false;

	this->type = eTypeOfGO::OTHER;
	this->team = eTeam::NONE;
	this->behaviour = eBehaviour::UNAVAIABLE;
	this->steeringBehaviour = eSteeringBehaviour::NA;
	this->range = NULL;
	this->health = NULL;
	this->maxVel = NULL;
	this->wanderAngle = 0.0f;

	this->mySpeed = sGOSpeed( 0.0f, 0.0f, 0.0f, 0.0f );

	this->currentState = DOING_NOTHING;
	this->bIsRunning = false;
	this->bIsWalking = false;

	// Set to NULL (or 0, or nullptr)
	this->pSimpleSkinnedMesh = NULL;		// 0
	this->pAniState = NULL;					// 0

	return;
}

cGameObject::~cGameObject()
{
	return;
}

bool cGameObject::getAnimationPath( eAnimationType type, std::string &thePath )
{
	for( int i = 0; i != this->myAnimations.size(); i++ )
	{
		if( this->myAnimations[i].type == type )
		{
			thePath = this->myAnimations[i].filePath;
			return true;
		}			
	}

	return false;
}

glm::vec3 cGameObject::getPosition( void )
{
	return this->position;
}

void cGameObject::overwrtiteQOrientationFromEuler( glm::vec3 eulerAxisOrientation )
{
	this->prevOrientation = this->qOrientation;
	// Calcualte the quaternion represnetaiton of this Euler axis
	// NOTE: We are OVERWRITING this..
	this->qOrientation = glm::quat( eulerAxisOrientation );

	return;
}

void cGameObject::adjustQOrientationFormDeltaEuler( glm::vec3 eulerAxisOrientChange )
{
	// How do we combine two matrices?
	// That's also how we combine quaternions...

	// So we want to "add" this change in oriention
	glm::quat qRotationChange = glm::quat( eulerAxisOrientChange );

	// Mulitply it by the current orientation;
	this->qOrientation = this->qOrientation * qRotationChange;

	return;
}

glm::vec3 cGameObject::getFrontVector()
{
	glm::vec3 eulerOrientation = glm::eulerAngles( this->qOrientation );	

	float movAngleDegrees;

	float zDegrees = glm::degrees( eulerOrientation.z );
	float yDegrees = glm::degrees( eulerOrientation.y );
	
	if( zDegrees != 0.0f )
	{	// Corrects the angle using Z value
		movAngleDegrees = ( zDegrees / 2 ) + ( ( zDegrees / 2 ) - abs( yDegrees ) );
		if( yDegrees < 0 )
			movAngleDegrees *= -1;
	}
	else
	{	// Use only the Y value
		movAngleDegrees = yDegrees;
	}

	glm::vec3 frontVector = glm::vec3( glm::sin( glm::radians( movAngleDegrees ) ),
										   0.0f,
										   glm::cos( glm::radians( movAngleDegrees ) ) );	

	return glm::normalize( frontVector );
}

glm::vec3 cGameObject::getRightVector()
{
	glm::vec3 theFrontVector = this->getFrontVector();

	float theta = glm::radians( -90.0f );
	float cosT = cos( theta );
	float sinT = sin( theta );

	glm::vec3 rightVector = glm::vec3( 0.0f );
	rightVector.x = theFrontVector.x * cosT - theFrontVector.z * sinT;
	rightVector.z = theFrontVector.x * sinT + theFrontVector.z * cosT;

	return glm::normalize( rightVector );
}

bool cGameObject::isFacingMe( glm::vec3 targetDirection, glm::vec3 targetPosition )
{
	bool isItFacing;

	// dotProduct( normalize( B - A ), normalize( directionFacingOfA ) )
	float facing = glm::dot( glm::normalize( this->position - targetPosition ), targetDirection );

	if( facing < 0 )	// It's not facing, looking to opposite direction
	{
		isItFacing = false;
	}
	else				// It's in the 180 degrees direction
	{
		if( facing >= 0.5f ) // It's in a 90 degrees cone
			isItFacing = true;
		else
			isItFacing = false;
	}

	std::string facingText;
	if( isItFacing ) facingText = "True";
	else facingText = "False ";

	//std::cout << "Facing: " << isItFacing << " " << facingText << " scale: " << facing << std::endl;
	return isItFacing;
}

//glm::quat cGameObject::getFinalMeshQOrientation( unsigned int meshID )
//{	// Does NOT check for the index of the mesh!
//	return this->m_PhysicalProps.qOrientation * this->vecMeshes[meshID].getQOrientation();
//}
//
//glm::quat cGameObject::getFinalMeshQOrientation( glm::quat &meshQOrientation )
//{	// Does NOT check for the index of the mesh!
//	return this->m_PhysicalProps.qOrientation * meshQOrientation;
//}