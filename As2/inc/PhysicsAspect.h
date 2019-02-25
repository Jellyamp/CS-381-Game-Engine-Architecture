/*
 * PhysicsAspect.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_PHYSICSASPECT_H_
#define INC_PHYSICSASPECT_H_

#include "Aspect.h"

class PhysicsAspect : public Aspect
{
public:
	PhysicsAspect(Entity381& ent);
	virtual ~PhysicsAspect();
	
	/*
	 * 	@name Tick
	 * 	@brief Updates the aspect.
	 */
	virtual void Tick(float dt);
};


#endif /* INC_PHYSICSASPECT_H_ */
