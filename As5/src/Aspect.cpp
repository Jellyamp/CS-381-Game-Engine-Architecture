/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include<Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h


Aspect::Aspect(Entity381 *ent){
	entity = ent;
}

Aspect::~Aspect(){

}

void Aspect::Tick(float dt){

}




Renderable::Renderable(Entity381* ent):Aspect(ent){

}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
//do something;
	entity->sceneNode->setPosition(entity->position); //now ogre should render the sceneNode at the new position...
	entity->sceneNode->resetOrientation(); // yaw is relative to 0
	entity->sceneNode->yaw(Ogre::Degree(-entity->heading));
	//bounding boxes are rendered so...
	if(entity->isSelected)
	{
		entity->sceneNode->showBoundingBox(true);
	}
	else
	{	    
		entity->sceneNode->showBoundingBox(false); //or we could do this in the entity mgr every time tab is pressed....
	}

}
