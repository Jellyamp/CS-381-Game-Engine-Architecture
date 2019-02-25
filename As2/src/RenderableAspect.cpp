/*
 * RenderableAspect.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alexander Pasinski
 */

#include <OgreVector3.h>
#include "RenderableAspect.h"
#include "Entity381.h"

RenderableAspect::RenderableAspect(Entity381& ent) : Aspect::Aspect(ent)
{
	std::cout << "New Renderable Aspect!" << std::endl;
}

RenderableAspect::~RenderableAspect()
{
	
}

void RenderableAspect::Tick(float dt)
{
	mEntity381->GetSceneNode()->translate(mEntity381->GetPosition() - mEntity381->GetSceneNode()->getPosition());
}
