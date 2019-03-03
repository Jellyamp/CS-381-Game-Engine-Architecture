/*
 * As3.h
 *
 *  Created on: Mar 2, 2019
 *      Author: Alexander Pasinski
 *      Contributor: Sushil J Louis
 */

#ifndef __As2_h_
#define __As2_h_

#include "BaseApplication.h"
#include "EntityMgr.h"
#include "Types381.h"

class As3 : public BaseApplication
{
public:
    As3();
    virtual ~As3();

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

    void MakeGround();
    void MakeSky();
    void MakeFog();
    void MakeEnts();

    void UpdateCamera(const Ogre::FrameEvent& fe);
    void UpdateVelocityAndSelection(const Ogre::FrameEvent& fe);

    EntityMgr *entityMgr;

    Ogre::SceneNode* cameraNode;

    float yaw;
    float acceleration;
    float keyboardTimer;
    float surfaceHeight;

    const static float keyTime;

protected:
    virtual void createScene();

};

#endif // #ifndef __As2_h_
