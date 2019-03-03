/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */


#include "Entity381.h"

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Ogre::SceneManager* sceneMgr, std::string meshfname, Ogre::Vector3 pos, int ident){

	meshfilename = meshfname;
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;
	isSelected = false;

	name = meshfname + IntToString(identity);

	ogreEntity = sceneMgr->createEntity(meshfilename);
	sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);

	Physics* phx = new Physics(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	deltaVelocity = 0;


}

Entity381::~Entity381(){

}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}


Cube::Cube(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	deltaVelocity = 50.0f;
}
Cube::~Cube(){

}

Sphere::Sphere(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	deltaVelocity = 20.0f;
}
Sphere::~Sphere(){

}



