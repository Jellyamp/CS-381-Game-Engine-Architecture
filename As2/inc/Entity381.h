/*
 * Entity381.h
 *
 *  Created on: Feb 11, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <string>
#include <vector>
#include <iostream>
#include <OgreEntity.h>
#include "Aspect.h"

enum Directions
{
	XPLUS,
	XMINUS,
	YPLUS,
	YMINUS,
	ZPLUS,
	ZMINUS
};

class Entity381
{
public:
	Entity381();
	virtual ~Entity381();
	
	Ogre::Vector3 GetPosition();
	void SetPosition(Ogre::Vector3 pos);
	
	Ogre::Vector3 GetVelocity();
	void Accelerate(Directions dir);
	
	/*
	 * 	@name Tick
	 * 	@brief Updates all aspects of the entity.
	 * 	
	 * 	@note This tick function is not virtual as each entity should tick the same way.
	 */
	void Tick(float dt);
	
protected:
	static int IDs;
	int mEntityId;
	
	std::string mEntityName;
	
	Ogre::Vector3 mPosition;
	Ogre::Vector3 mVelocity;
	
	float mBaseAcceleration;
	
	Ogre::SceneNode* mSceneNode;
	
	Ogre::Entity* mEntity;
	
	std::vector<Aspect*> mAspects;
};



#endif /* INC_ENTITY381_H_ */
