/*
 * Aspect.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alexander Pasinski
 */


#include "Aspect.h"
#include "Entity381.h"

Aspect::Aspect(Entity381& ent)
{
	std::cout << "New Aspect!" << std::endl;
	mEntity381 = &ent;
}

Aspect::~Aspect()
{
	
}

void Aspect::Tick(float dt)
{
	
}
