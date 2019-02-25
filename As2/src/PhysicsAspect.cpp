/*
 * PhysicsAspect.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alexander Pasinski
 */

#include <OgreVector3.h>
#include "PhysicsAspect.h"
#include "Entity381.h"

PhysicsAspect::PhysicsAspect(Entity381& ent) : Aspect::Aspect(ent)
{
	std::cout << "New Physics Aspect!" << std::endl;
}

PhysicsAspect::~PhysicsAspect()
{
	
}

void PhysicsAspect::Tick(float dt)
{
	mEntity381->SetPosition(mEntity381->GetPosition() + mEntity381->GetVelocity() * dt);
}
