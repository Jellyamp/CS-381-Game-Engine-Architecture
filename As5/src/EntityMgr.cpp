/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>
#include "GameMgr.h"

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	selectedEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *ent = new Entity381(this->engine, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateDDG51(Ogre::Vector3 pos){
	DDG51 *ent = new DDG51(this->engine, "ddg51.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos){
	Carrier *ent = new Carrier(this->engine, "cvn68.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateSpeedBoat(Ogre::Vector3 pos){
	SpeedBoat *ent = new SpeedBoat(this->engine, "cigarette.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateFrigate(Ogre::Vector3 pos){
	Frigate *ent = new Frigate(this->engine, "sleek.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateAlien(Ogre::Vector3 pos){
	Alien *ent = new Alien(this->engine, "alienship.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateBanshee(Ogre::Vector3 pos){
    Banshee *ent = new Banshee(this->engine, "banshee.mesh", pos, count);
    count++;
    entities.push_back((Entity381 *) ent);
}


void EntityMgr::SelectNextEntity(){
	if(selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	if(selectedEntity != 0)
		selectedEntity->isSelected = false;
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;
}

void EntityMgr::SelectEntityByAABB(Ogre::Ray& rayToCheck)
{
    int newIndex = -1;
    std::pair<bool, Ogre::Real> result;
    
    for(std::vector<Entity381*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
    {
        result = rayToCheck.intersects((*iter)->sceneNode->_getWorldAABB());
        if(result.first == true)
        {
            newIndex = iter - entities.begin();
        }
    }
    
    SetSelection(newIndex);
}

void EntityMgr::SelectEntityByDistanceToPoint(Ogre::Ray& rayToCheck)
{
    int newIndex = -1;
    std::pair<bool, Ogre::Real> result;
    result = rayToCheck.intersects(engine->gameMgr->plane);
    Ogre::Vector3 intersectPos;
    float minDistance = std::numeric_limits<float>::infinity();
    float currentDistance = 0;
    
    if(result.first)
    {
        intersectPos = rayToCheck.getPoint(result.second);
        for(std::vector<Entity381*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
        {
            currentDistance = Ogre::Vector3((*iter)->position - intersectPos).length();
            if(currentDistance < minDistance)
            {
                minDistance = currentDistance;
                newIndex = iter - entities.begin();
            }
        }
    }
    
    SetSelection(newIndex);
}

void EntityMgr::SetSelection(int newIndex)
{
    if(newIndex == -1)
    {
        std::cerr << "ERROR: Entity not found" << std::endl;
    }
    else
    {
        if(selectedEntity != NULL)
        {
            selectedEntity->isSelected = false;
        }
        selectedEntityIndex = newIndex;
        selectedEntity = entities[selectedEntityIndex];
        selectedEntity->isSelected = true;
    }
}


void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	switch(entType){
	case DDG51Type:
		CreateDDG51(pos);
		break;
	case CarrierType:
		CreateCarrier(pos);
		break;
	case SpeedBoatType:
		CreateSpeedBoat(pos);
		break;
	case FrigateType:
		CreateFrigate(pos);
		break;
	case AlienType:
		CreateAlien(pos);
		break;
    case BansheeType:
        CreateBanshee(pos);
        break;
	default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < count; i++){
		entities[i]->Tick(dt);
	}
}
