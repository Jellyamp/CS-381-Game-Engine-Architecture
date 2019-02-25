/*
 * RenderableAspect.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_RENDERABLEASPECT_H_
#define INC_RENDERABLEASPECT_H_

#include "Aspect.h"

class RenderableAspect : public Aspect
{
public:
	RenderableAspect(Entity381& ent);
	virtual ~RenderableAspect();
	
	/*
	 * 	@name Tick
	 * 	@brief Updates the aspect.
	 */
	virtual void Tick(float dt);
};


#endif /* INC_RENDERABLEASPECT_H_ */
