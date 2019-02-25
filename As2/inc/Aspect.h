/*
 * Aspect.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_ASPECT_H_
#define INC_ASPECT_H_

#include <iostream>

class Aspect
{
public:
	Aspect();
	virtual ~Aspect();
	
	/*
	 * 	@name Tick
	 * 	@brief Updates the aspect.
	 * 	
	 * 	@note This tick function is virtual because each Aspect might tick slightly differently.
	 */
	virtual void Tick(float dt);
};



#endif /* INC_ASPECT_H_ */
