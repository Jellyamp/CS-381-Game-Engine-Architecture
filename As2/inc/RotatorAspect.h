/*
 * RotatorAspect.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_ROTATORASPECT_H_
#define INC_ROTATORASPECT_H_

#include "Aspect.h"

class RotatorAspect : public Aspect
{
public:
	RotatorAspect(Entity381& ent);
	virtual ~RotatorAspect();
	
	/*
	 * 	@name Tick
	 * 	@brief Updates the aspect.
	 */
	virtual void Tick(float dt);
};


#endif /* INC_ROTATORASPECT_H_ */
