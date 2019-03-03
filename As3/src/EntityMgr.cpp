/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include "EntityMgr.h"

EntityMgr::EntityMgr(Ogre::SceneManager* sm) {
	selectedEntity = 0;
	sceneMgr = sm;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr() {

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos) {
	Entity381 *ent = new Entity381(sceneMgr, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateCube(Ogre::Vector3 pos) {
	Cube *ent = new Cube(sceneMgr, "cube.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateSphere(Ogre::Vector3 pos) {
	Sphere *ent = new Sphere(sceneMgr, "sphere.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::SelectNextEntity() {
	if (selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	if (selectedEntity != 0)
		selectedEntity->isSelected = false;
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;

}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType,
		Ogre::Vector3 pos) {

	switch (entType) {
	case CubeType:
		CreateCube(pos);
		break;
	case SphereType:
		CreateSphere(pos);
		break;
	default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt) {
	for (int i = 0; i < count; i++) {
		entities[i]->Tick(dt);
	}
}
