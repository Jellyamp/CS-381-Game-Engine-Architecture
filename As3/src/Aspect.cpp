/*
 * Aspect.cpp
 *
 *  Created on: Mar 2, 2019
 *      Author: Alexander Pasinski
 *      Contributor: Sushil J Louis (Feb 7, 2018)
 */

#include "Aspect.h"
#include "Entity381.h"  //Aspect includes Entity381.h

Aspect::Aspect(Entity381 *ent)
{
    entity = ent;
}

Aspect::~Aspect()
{

}

void Aspect::Tick(float dt)
{

}



Physics::Physics(Entity381* ent)
        : Aspect(ent)
{

}

Physics::~Physics()
{

}

void Physics::Tick(float dt)
{
    if(entity->speed < entity->desiredSpeed)
    {
        entity->speed += entity->acceleration;
        
        if(entity->speed > entity->maxSpeed)
        {
            entity->speed = entity->maxSpeed;
        }
    }
    else if(entity->speed > entity->desiredSpeed)
    {
        entity->speed -= entity->acceleration;
        
        if(entity->speed < entity->minSpeed)
        {
            entity->speed = entity->minSpeed;
        }
    }
    
    
    if(entity->heading < entity->desiredHeading)
    {
        entity->heading += entity->turningRate;
        
        if(entity->heading > 360)
        {
            entity->heading = entity->heading - 360;
        }
    }
    else if(entity->heading > entity->desiredHeading)
    {
        entity->heading -= entity->turningRate;
        
        if(entity->heading < 0)
        {
            entity->heading = 360 - entity->heading;
        }
    }
    
    entity->velocity.x = entity->speed * Ogre::Math::Sin(Ogre::Math::DegreesToRadians(entity->heading));
    entity->velocity.y = entity->speed * Ogre::Math::Cos(Ogre::Math::DegreesToRadians(entity->heading));
    
    
    
    entity->position = entity->position + entity->velocity * dt; //entity381's position will now change every frame (tick)
}



Renderable::Renderable(Entity381* ent)
        : Aspect(ent)
{

}

Renderable::~Renderable()
{

}

void Renderable::Tick(float dt)
{
//do something;
    entity->sceneNode->setPosition(entity->position); //now ogre should render the sceneNode at the new position...
    //bounding boxes are rendered so...
    if(entity->isSelected)
        entity->sceneNode->showBoundingBox(true);
    else
        entity->sceneNode->showBoundingBox(false); //or we could do this in the entity mgr every time tab is pressed....

}
