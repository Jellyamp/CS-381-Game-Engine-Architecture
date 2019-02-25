/*
 * SphereEntity.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#include "SphereEntity.h"

SphereEntity::SphereEntity()
{
	mAspects.push_back(new PhysicsAspect());
}
