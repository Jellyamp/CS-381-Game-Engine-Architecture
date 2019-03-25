/*
 * Physics2D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: sushil
 */

#ifndef PHYSICSFLIGHT_H_
#define PHYSICSFLIGHT_H_

#include <Aspect.h>

class PhysicsFlight : Aspect
{
public:
    PhysicsFlight(Entity381* ent);
	~PhysicsFlight();

	void Tick(float dt);
};



#endif /* PHYSICSFLIGHT_H_ */
