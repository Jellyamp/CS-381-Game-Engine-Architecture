/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include "Aspect.h"
#include "Entity381.h"  //Aspect includes Entity381.h


Aspect::Aspect(Entity381 *ent){
	entity = ent;
}

Aspect::~Aspect(){

}

void Aspect::Tick(float dt){

}

Physics::Physics(Entity381* ent):Aspect(ent){

}

Physics::~Physics(){

}

void Physics::Tick(float dt){
//do something;
	entity->position = entity->position + entity->velocity * dt; //entity381's position will now change every frame (tick)
}


Renderable::Renderable(Entity381* ent):Aspect(ent){

}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
//do something;
	entity->sceneNode->setPosition(entity->position); //now ogre should render the sceneNode at the new position...
	//bounding boxes are rendered so...
	if(entity->isSelected)
		entity->sceneNode->showBoundingBox(true);
	else
		entity->sceneNode->showBoundingBox(false); //or we could do this in the entity mgr every time tab is pressed....

}
