/*
 * SphereEntity.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#include "SphereEntity.h"

SphereEntity::SphereEntity()
{
	std::cout << "New Sphere Entity!" << std::endl;
	mAspects.push_back(new PhysicsAspect());
}
