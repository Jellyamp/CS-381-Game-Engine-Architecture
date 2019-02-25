/*
 * RotatorAspect.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alexander Pasinski
 */

#include <OgreVector3.h>
#include "RotatorAspect.h"
#include "Entity381.h"

RotatorAspect::RotatorAspect(Entity381& ent) : Aspect::Aspect(ent)
{
	std::cout << "New Renderable Aspect!" << std::endl;
}

RotatorAspect::~RotatorAspect()
{
	
}

void RotatorAspect::Tick(float dt)
{
	mEntity381->GetSceneNode()->yaw(Ogre::Radian(Ogre::Degree(5*dt)));
}
