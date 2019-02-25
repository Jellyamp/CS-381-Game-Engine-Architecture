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

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes ent, Ogre::Vector3 pos)
{
	SphereEntity* newSphereEnt = NULL;
	CubeEntity* newCubeEnt = NULL;
	
	// Will use a switch statement to create a selected entity.
	switch(ent)
	{
	case SPHERE_ENT:
		newSphereEnt = new SphereEntity();
		newSphereEnt->GetEntity() = CreateEntity("sphere.mesh");
		newSphereEnt->GetSceneNode() = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		newSphereEnt->GetSceneNode()->attachObject(newSphereEnt->GetEntity());
		newSphereEnt->GetSceneNode()->setPosition(pos);
		newSphereEnt->SetPosition(pos);
		mEntities.push_back(newSphereEnt);
		break;
	case CUBE_ENT:
		newCubeEnt = new CubeEntity();
		newCubeEnt->GetEntity() = CreateEntity("cube.mesh");
		newCubeEnt->GetSceneNode() = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		newCubeEnt->GetSceneNode()->attachObject(newCubeEnt->GetEntity());
		newCubeEnt->GetSceneNode()->setPosition(pos);
		newCubeEnt->SetPosition(pos);
		mEntities.push_back(newCubeEnt);
		break;
	}
}

void EntityMgr::DestroyEntity(Entity381*& ent)
{
	// Will iterate over the vector to find the entity to destroy.
	for(std::vector<Entity381*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
	{
		if(*it == ent)
		{
			mEntities.erase(it);
		}
	}
}

Entity381*& EntityMgr::GetNextEntity(Entity381*& ent)
{
	if(ent == NULL && mEntities.size() > 0)
	{
		mCurrentEntity381 = mEntities[0];
		return mCurrentEntity381;
	}
	
	bool found = false;
	// Will iterate over the vector to find the next entity.
	std::vector<Entity381*>::iterator it = mEntities.begin();
	while(it != mEntities.end() && found == false)
	{
		if(*it == ent && (it + 1) != mEntities.end())
		{
			found = true;
		}
		it++;
	}
	
	if(it == mEntities.end())
	{
		mCurrentEntity381 = mEntities[0];
		return mCurrentEntity381;
	}
	
	if(found)
	{
		mCurrentEntity381 = *it;
		return mCurrentEntity381;
	}
	else
	{
		std::cerr << "Entity not found" << std::endl;
	}
}


Ogre::SceneManager*& EntityMgr::GetSceneMgr()
{
	return mSceneMgr;
}

void EntityMgr::SetSceneMgr(Ogre::SceneManager*& sceneMgr)
{
	mSceneMgr = sceneMgr;
}

Ogre::Entity* EntityMgr::CreateEntity(Ogre::String entityName)
{
	return mSceneMgr->createEntity(entityName);
}
