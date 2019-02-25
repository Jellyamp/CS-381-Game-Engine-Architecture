/*
 * CubeEntity.cpp
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#include "CubeEntity.h"

CubeEntity::CubeEntity()
{
	std::cout << "New Cube Entity!" << std::endl;
	mAspects.push_back(new PhysicsAspect(*this));
}


