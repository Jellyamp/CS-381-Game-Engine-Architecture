/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>

EntityMgr::EntityMgr(Ogre::SceneManager* sm){
	selectedEntity = 0;
	sceneMgr = sm;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *ent = new Entity381(sceneMgr, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateDDG51(Ogre::Vector3 pos){
	DDG51 *ent = new DDG51(sceneMgr, "ddg51.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos){
	Carrier *ent = new Carrier(sceneMgr, "cvn68.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateSpeedBoat(Ogre::Vector3 pos){
	SpeedBoat *ent = new SpeedBoat(sceneMgr, "cigarette.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateFrigate(Ogre::Vector3 pos){
	Frigate *ent = new Frigate(sceneMgr, "sleek.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateAlien(Ogre::Vector3 pos){
	Alien *ent = new Alien(sceneMgr, "alienship.mesh", pos, count);
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
	default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt){  //Someone needs to call this tick...
//we have not hooked everything up...
	for(int i = 0; i < count; i++){
		entities[i]->Tick(dt);
	}
}
