/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#include "EntityMgr.h"

void EntityMgr::Tick(float dt)
{
	for(unsigned int index = 0; index < mEntities.size(); index++)
	{
		mEntities[index]->Tick(dt);
	}
}

void EntityMgr::CreateEntity()
{
	// Will use a switch statement to create a selected entity.
	mEntities.push_back(new SphereEntity());
}

void EntityMgr::DestroyEntity()
{
	// Will iterate over the vector to find the entity to destroy.
}

