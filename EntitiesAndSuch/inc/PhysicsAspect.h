/*
 * PhysicsAspect.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_PHYSICSASPECT_H_
#define INC_PHYSICSASPECT_H_

#include "Aspect.h"

class PhysicsAspect : Aspect
{
public:
	PhysicsAspect();
	virtual ~PhysicsAspect();
	
	/*
	 * 	@name Tick
	 * 	@brief Updates the aspect.
	 */
	virtual void tick(float dt);
};


#endif /* INC_PHYSICSASPECT_H_ */
