#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>

#include <Engine.h>

class Entity381
{
public:
  Entity381(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;
  std::string name;
  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  float acceleration, turnRate, climbRate;
  float minSpeed, maxSpeed, minAltitude, maxAltitude;

  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  bool isSelected, canFly;
  float desiredHeading, desiredSpeed, desiredAltitude;
  float heading, speed, altitude;
  
  std::vector<Aspect* > aspects;

  void Tick(float dt);

protected:


};


class Banshee : Entity381
{
public:
    Banshee(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
    virtual ~Banshee();
};

class Carrier: Entity381 {
public:
	Carrier(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Carrier();

};

class DDG51: Entity381 {
public:
	DDG51(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~DDG51();

};

class SpeedBoat: Entity381 {
public:
	SpeedBoat(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~SpeedBoat();

};

class Frigate: Entity381 {
public:
	Frigate(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Frigate();

};

class Alien: Entity381 {
public:
	Alien(Engine *engine, std::string meshfilename, Ogre::Vector3 pos, int identity);
	virtual ~Alien();

};


#endif // #ifndef __Entity381_h_
