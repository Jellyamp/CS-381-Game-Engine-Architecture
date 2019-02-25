/*
 * EntityMgr.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <vector>
#include <iterator>
#include <OgreSceneManager.h>
#include "Entity381.h"
#include "SphereEntity.h"
#include "CubeEntity.h"

enum EntityTypes
{
	SPHERE_ENT,
	CUBE_ENT,
};

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
	void CreateEntityOfTypeAtPosition(EntityTypes ent, Ogre::Vector3 pos);
	
	/*
	 * 	@name DestroyEntity
	 * 	@brief Destroys an entity.
	 */
	void DestroyEntity(Entity381*& ent);
	
	/*
	 * @name GetNextEntity
	 * @brief Gets the next entity in the vector.
	 */
	Entity381*& GetNextEntity(Entity381*& ent);
	
	
	Ogre::SceneManager*& GetSceneMgr();
	void SetSceneMgr(Ogre::SceneManager*& sceneMgr);
	
	Ogre::Entity* CreateEntity(Ogre::String entityName);
	
private:
	std::vector<Entity381*> mEntities;
	
	Entity381* mCurrentEntity381;
	
	Ogre::SceneManager* mSceneMgr;
};



#endif /* INC_ENTITYMGR_H_ */
