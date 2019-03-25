/*
 * PhysicsFlight.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: Alexander Pasinski
 */


#include "PhysicsFlight.h"
#include <Entity381.h>
#include <Utils.h>


PhysicsFlight::PhysicsFlight(Entity381* ent):Aspect(ent){

}

PhysicsFlight::~PhysicsFlight(){

}


void PhysicsFlight::Tick(float dt){
    //first, get new speed from desired speed
    if(entity->desiredAltitude > entity->altitude){
        entity->altitude += entity->climbRate * dt;
        entity->altitude = Clamp(entity->minAltitude, entity->maxAltitude, entity->altitude);
        entity->position.y += entity->climbRate * dt;
    } else if (entity->desiredAltitude < entity->altitude){
        entity->altitude -= entity->climbRate * dt;
        entity->altitude = Clamp(entity->minAltitude, entity->maxAltitude, entity->altitude);
        entity->position.y -= entity->climbRate * dt;
    }

    entity->position.y = Clamp(entity->minAltitude, entity->maxAltitude, entity->position.y);
}
