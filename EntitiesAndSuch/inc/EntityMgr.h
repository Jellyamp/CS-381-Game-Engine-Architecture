/*
 * EntityMgr.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include "Entity381.h"
#include <vector>

class EntityMgr
{
public:
	/*
	 * 	@name Tick
	 * 	@brief Updates every entity in the mEntities vector.
	 */
	void Tick(float dt);
	
	/*
	 * 	@name CreateEntity
	 * 	@brief Creates a new entity.
	 */
	void CreateEntity();
	
	/*
	 * 	@name DestroyEntity
	 * 	@brief Destroys an entity.
	 */
	// TODO: Will need a parameter for the entity to be destroyed (reference or id).
	void DestroyEntity();
	
private:
	std::vector<Entity381*> mEntities;
};



#endif /* INC_ENTITYMGR_H_ */
