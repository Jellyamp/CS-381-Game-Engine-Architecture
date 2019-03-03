#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include "Aspect.h" //Entity381 includes Aspect.h, this is circular! A no-no

class Entity381
{
public:
  Entity381(Ogre::SceneManager* sceneMgr, std::string meshfilename, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  int identity;
  std::string name;

  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  bool isSelected;

  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;

  float deltaVelocity;

  std::vector<Aspect* > aspects;

  void Tick(float dt);


protected:


};

class Sphere: Entity381 {
public:
	Sphere(Ogre::SceneManager* sceneMgr, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Sphere();

};

class Cube: Entity381 {
public:
	Cube(Ogre::SceneManager* sceneMgr, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Cube();

};


#endif // #ifndef __Entity381_h_
