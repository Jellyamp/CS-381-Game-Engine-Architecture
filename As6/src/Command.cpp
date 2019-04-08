/*
 * Command.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: Alexander Pasinski
 */

#include <Command.h>


Command::Command(Entity381* ent, COMMAND_TYPE ct)
{
    commandType = ct;
    entity = ent;
}

Command::~Command()
{
    
}

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location, COMMAND_TYPE type)
    : Command(ent, type)
{
    entity = ent;
    MOVE_DISTANCE_THRESHOLD = std::numeric_limits<float>::infinity();
    targetLocation = location;
}

MoveTo::~MoveTo()
{
    
}

void MoveTo::init()
{
    std::cout << "MOVE TO!" << std::endl;
}

void MoveTo::tick(float dt)
{
    Ogre::Vector3 diff = targetLocation - entity->position;
    float angle = atan2(diff.z, diff.x);
    entity->desiredHeading = FixAngle(Ogre::Degree(Ogre::Radian(angle)).valueDegrees());
    entity->desiredSpeed = entity->maxSpeed;
}

bool MoveTo::done()
{
    if(Ogre::Math::Abs(targetLocation.x - entity->position.x) <= 20 && Ogre::Math::Abs(targetLocation.z - entity->position.z) <= 20)
    {
        entity->desiredSpeed = entity->minSpeed;
        return true;
    }
    else
    {
        return false;
    }
}



Follow::Follow(Entity381* ent, Ogre::Vector3 location, Entity381* targetEnt)
    : MoveTo(ent, location, FOLLOW)
{
    entity = ent;
    targetEntity = targetEnt;
    MOVE_DISTANCE_THRESHOLD = std::numeric_limits<float>::infinity();
    targetLocation = location;
}

Follow::~Follow()
{
    
}

void Follow::init()
{
    std::cout << "FOLLOW!" << std::endl;
}

void Follow::tick(float dt)
{
    targetLocation = targetEntity->position;
    Ogre::Vector3 diff = targetLocation - entity->position;
    float angle = atan2(diff.z, diff.x);
    entity->desiredHeading = FixAngle(Ogre::Degree(Ogre::Radian(angle)).valueDegrees());
    entity->desiredSpeed = entity->maxSpeed;
}

bool Follow::done()
{
    if(Ogre::Math::Abs(targetLocation.x - entity->position.x) <= 20 && Ogre::Math::Abs(targetLocation.z - entity->position.z) <= 20)
    {
        entity->desiredSpeed = entity->minSpeed;
        return true;
    }
    else
    {
        return false;
    }
}



Intercept::Intercept(Entity381* ent, Ogre::Vector3 location, Entity381* targetEnt)
    : MoveTo(ent, location, INTERCEPT)
{
    entity = ent;
    targetEntity = targetEnt;
    MOVE_DISTANCE_THRESHOLD = std::numeric_limits<float>::infinity();
    targetLocation = location;
}

Intercept::~Intercept()
{
    
}

void Intercept::init()
{
    std::cout << "INTERCEPT!" << std::endl;
}

void Intercept::tick(float dt)
{
    targetLocation = targetEntity->position;
    Ogre::Vector3 diff = targetLocation - entity->position;
    Ogre::Vector3 relVel = targetEntity->velocity - entity->velocity;
    float tStar;      
    tStar = diff.length()/relVel.length();
    Ogre::Vector3 interceptLocation = targetLocation + (targetEntity->velocity * tStar);
    diff = interceptLocation - entity->position;
    float angle = atan2(diff.z, diff.x);
    entity->desiredHeading = FixAngle(Ogre::Degree(Ogre::Radian(angle)).valueDegrees());
    entity->desiredSpeed = entity->maxSpeed;
}

bool Intercept::done()
{
    if(Ogre::Math::Abs(targetLocation.x - entity->position.x) <= 20 && Ogre::Math::Abs(targetLocation.z - entity->position.z) <= 20)
    {
        entity->desiredSpeed = entity->minSpeed;
        std::cout << "done" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}
