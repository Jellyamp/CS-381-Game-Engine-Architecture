/*
 * EntityMgr.cpp
 *
 *  Created on: Mar 2, 2019
 *      Author: Alexander Pasinski
 *      Contributor: Sushil J Louis (Feb 7, 2018)
 */

#include "EntityMgr.h"

EntityMgr::EntityMgr(Ogre::SceneManager* sm)
{
    selectedEntity = 0;
    sceneMgr = sm;
    count = 0;
    selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr()
{

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos)
{
    Entity381 *ent = new Entity381(sceneMgr, meshfilename, pos, count);
    count++;
    entities.push_back(ent);
}

void EntityMgr::CreateDestroyer(Ogre::Vector3 pos)
{
    Destroyer *ent = new Destroyer(sceneMgr, "ddg51.mesh", pos, count);
    count++;
    entities.push_back((Entity381 *)ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos)
{
    Carrier *ent = new Carrier(sceneMgr, "cvn68.mesh", pos, count);
    count++;
    entities.push_back((Entity381 *)ent);
}

void EntityMgr::CreateSpeedboat(Ogre::Vector3 pos)
{
    Speedboat *ent = new Speedboat(sceneMgr, "cigarette.mesh", pos, count);
    count++;
    entities.push_back((Entity381 *)ent);
}

void EntityMgr::CreateFrigate(Ogre::Vector3 pos)
{
    Frigate *ent = new Frigate(sceneMgr, "sleek.mesh", pos, count);
    count++;
    entities.push_back((Entity381 *)ent);
}

void EntityMgr::CreateAlien(Ogre::Vector3 pos)
{
    Alien *ent = new Alien(sceneMgr, "alienship.mesh", pos, count);
    count++;
    entities.push_back((Entity381 *)ent);
}

void EntityMgr::SelectNextEntity()
{
    if(selectedEntityIndex >= count - 1)
    {
        selectedEntityIndex = 0;
    }
    else
    {
        selectedEntityIndex++;
    }
    if(selectedEntity != 0)
        selectedEntity->isSelected = false;
    selectedEntity = entities[selectedEntityIndex];
    selectedEntity->isSelected = true;

}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType,
        Ogre::Vector3 pos)
{

    switch(entType)
    {
    case DESTROYER_TYPE:
        CreateDestroyer(pos);
        break;
    case CARRIER_TYPE:
        CreateCarrier(pos);
        break;
    case SPEEDBOAT_TYPE:
        CreateSpeedboat(pos);
        break;
    case FRIGATE_TYPE:
        CreateFrigate(pos);
        break;
    case ALIEN_TYPE:
        CreateAlien(pos);
        break;
    default:
        CreateEntity("robot.mesh", pos);
        break;
    }
}

void EntityMgr::Tick(float dt)
{
    for(int i = 0; i < count; i++)
    {
        entities[i]->Tick(dt);
    }
}
