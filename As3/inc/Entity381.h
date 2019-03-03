/*
 * Entity381.h
 *
 *  Created on: Mar 2, 2019
 *      Author: Alexander Pasinski
 *      Contributor: Sushil J Louis
 */

#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include "Aspect.h" //Entity381 includes Aspect.h, this is circular! A no-no

class Entity381
{
public:
    Entity381(Ogre::SceneManager* sceneMgr, std::string meshfilename,
            Ogre::Vector3 pos, int identity);
    virtual ~Entity381();

    bool isSelected;

    int identity;

    float minSpeed;
    float maxSpeed;
    float speed;
    float heading;
    float desiredSpeed;
    float desiredHeading;
    float acceleration;
    float turningRate;

    Ogre::Vector3 position;
    Ogre::Vector3 velocity;

    std::string name;
    std::string meshfilename;
    
    Ogre::Entity* ogreEntity;
    Ogre::SceneNode* sceneNode;

    std::vector<Aspect*> aspects;

    void Tick(float dt);

protected:

};



class Destroyer : Entity381
{
public:
    Destroyer(Ogre::SceneManager* sceneMgr, std::string meshfilename,
            Ogre::Vector3 pos, int identity);
    virtual ~Destroyer();

};



class Carrier : Entity381
{
public:
    Carrier(Ogre::SceneManager* sceneMgr, std::string meshfilename,
            Ogre::Vector3 pos, int identity);
    virtual ~Carrier();

};



class Speedboat : Entity381
{
public:
    Speedboat(Ogre::SceneManager* sceneMgr, std::string meshfilename,
            Ogre::Vector3 pos, int identity);
    virtual ~Speedboat();

};



class Frigate : Entity381
{
public:
    Frigate(Ogre::SceneManager* sceneMgr, std::string meshfilename,
            Ogre::Vector3 pos, int identity);
    virtual ~Frigate();

};



class Alien : Entity381
{
public:
    Alien(Ogre::SceneManager* sceneMgr, std::string meshfilename,
            Ogre::Vector3 pos, int identity);
    virtual ~Alien();

};

#endif // #ifndef __Entity381_h_
