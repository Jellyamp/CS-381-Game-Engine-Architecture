/*
 * Entity381.cpp
 *
 *  Created on: Mar 2, 2019
 *      Author: Alexander Pasinski
 *      Contributor: Sushil J Louis (Feb 7, 2018)
 */

#include "Entity381.h"

std::string IntToString(int x)
{
    char tmp[10000];
    sprintf(tmp, "%i", x);
    return std::string(tmp);
}

Entity381::Entity381(Ogre::SceneManager* sceneMgr, std::string meshfname,
        Ogre::Vector3 pos, int ident)
{

    isSelected = false;

    identity = ident;

    minSpeed = 0;
    maxSpeed = 0;
    speed = 0;
    heading = 0;
    previousHeading = 0;
    desiredSpeed = 0;
    desiredHeading = 0;
    acceleration = 0;
    turningRate = 0;

    position = pos;
    velocity = Ogre::Vector3(0, 0, 0);

    name = meshfname + IntToString(identity);
    meshfilename = meshfname;
    
    ogreEntity = sceneMgr->createEntity(meshfilename);
    sceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(pos);
    sceneNode->attachObject(ogreEntity);


    Physics* phx = new Physics(this);
    aspects.push_back((Aspect*)phx);
    Renderable * renderable = new Renderable(this);
    aspects.push_back((Aspect*)renderable);

}

Entity381::~Entity381()
{

}

void Entity381::Tick(float dt)
{
    for(unsigned int i = 0; i < aspects.size(); i++)
    {
        aspects[i]->Tick(dt);
    }
}



Destroyer::Destroyer(Ogre::SceneManager * sm, std::string meshfname,
        Ogre::Vector3 pos, int ident)
        : Entity381(sm, meshfname, pos, ident)
{
    acceleration = 50.0f;
    turningRate = 2.0f;
    maxSpeed = 500.0f;
}

Destroyer::~Destroyer()
{

}



Carrier::Carrier(Ogre::SceneManager * sm, std::string meshfname,
        Ogre::Vector3 pos, int ident)
        : Entity381(sm, meshfname, pos, ident)
{
    acceleration = 40.0f;
    turningRate = 2.0f;
    maxSpeed = 400.0f;
}
Carrier::~Carrier()
{

}



Speedboat::Speedboat(Ogre::SceneManager * sm, std::string meshfname,
        Ogre::Vector3 pos, int ident)
        : Entity381(sm, meshfname, pos, ident)
{
    acceleration = 60.0f;
    turningRate = 5.0f;
    maxSpeed = 300.0f;
}

Speedboat::~Speedboat()
{

}



Frigate::Frigate(Ogre::SceneManager * sm, std::string meshfname,
        Ogre::Vector3 pos, int ident)
        : Entity381(sm, meshfname, pos, ident)
{
    acceleration = 30.0f;
    turningRate = 5.0f;
    maxSpeed = 150.0f;
}

Frigate::~Frigate()
{

}



Alien::Alien(Ogre::SceneManager * sm, std::string meshfname, Ogre::Vector3 pos,
        int ident)
        : Entity381(sm, meshfname, pos, ident)
{
    acceleration = 15.0f;
    turningRate = 9.0f;
    maxSpeed = 75.0f;
}

Alien::~Alien()
{

}
