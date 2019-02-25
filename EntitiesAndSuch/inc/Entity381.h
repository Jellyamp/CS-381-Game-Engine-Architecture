/*
 * Entity381.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include "Aspect.h"
#include <vector>

class Entity381
{
public:
	Entity381();
	~Entity381();
	
	/*
	 * 	@name Tick
	 * 	@brief Updates all aspects of the entity.
	 * 	
	 * 	@note This tick function is not virtual as each entity should tick the same way.
	 */
	void Tick(float dt);
	
private:
	std::vector<Aspect*> mAspects;
};



#endif /* INC_ENTITY381_H_ */
