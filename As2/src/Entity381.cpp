/*
 * Entity381.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alexander Pasinski
 */

#include "Entity381.h"

int Entity381::IDs = 0;

Entity381::Entity381()
{
	mEntityId = Entity381::IDs;
	Entity381::IDs++;
	
	mSceneNode = NULL;
	mEntity = NULL;
	
	mBaseAcceleration = 10;
	
	std::cout << "New Entity!" << std::endl;
}

Entity381::~Entity381()
{
	
}

void Entity381::Tick(float dt)
{
	for(unsigned int index = 0; index < mAspects.size(); index++)
	{
		mAspects[index]->Tick(dt);
	}
}

void Entity381::Accelerate(Directions dir)
{
	switch(dir)
	{
	case XPLUS:
		mVelocity.x += mBaseAcceleration;
		break;
	case XMINUS:
		mVelocity.x -= mBaseAcceleration;
		break;
	case YPLUS:
		mVelocity.y += mBaseAcceleration;
		break;
	case YMINUS:
		mVelocity.y -= mBaseAcceleration;
		break;
	case ZPLUS:
		mVelocity.z += mBaseAcceleration;
		break;
	case ZMINUS:
		mVelocity.z -= mBaseAcceleration;
		break;
	default:
		std::cerr << "Invalid direction for Entity381::Accelerate!" << std::endl;
	}
}
