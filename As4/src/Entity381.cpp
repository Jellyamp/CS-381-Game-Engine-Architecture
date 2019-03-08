/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */


#include<Entity381.h>
#include<Physics2D.h>

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

	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);

	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;

}

Entity381::~Entity381(){

}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
DDG51::DDG51(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	this->minSpeed = 0;
	this->maxSpeed = 16.0f;//meters per second...
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
}

DDG51::~DDG51(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Carrier::Carrier(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	this->minSpeed = 0;
	this->maxSpeed = 20.0f;//meters per second...
	this->acceleration = 1.0f; // slow
	this->turnRate = 10.0f; //2 degrees per second
}

Carrier::~Carrier(){

}
//-------------------------------------------------------------------------------------------------------------------------------

SpeedBoat::SpeedBoat(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	this->minSpeed = 0;
	this->maxSpeed = 30.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 30.0f; //2 degrees per second
}

SpeedBoat::~SpeedBoat(){

}
//-------------------------------------------------------------------------------------------------------------------------------

Frigate::Frigate(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	this->minSpeed = 0;
	this->maxSpeed = 15.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 20.0f; //2 degrees per second
}

Frigate::~Frigate(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Alien::Alien(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos, int ident):Entity381(sm, meshfname, pos, ident){
	this->minSpeed = 0;
	this->maxSpeed = 50.0f;//meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 40.0f; //2 degrees per second
}

Alien::~Alien(){

}
//-------------------------------------------------------------------------------------------------------------------------------


