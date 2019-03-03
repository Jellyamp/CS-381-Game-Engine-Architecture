/*
 * As2.h
 *
 *  Created on: Jan 24, 2017
 *      Author: sushil
 */

#ifndef __As2_h_
#define __As2_h_

#include "BaseApplication.h"
#include "EntityMgr.h"
#include "Types381.h"

class As2 : public BaseApplication
{
public:
  As2();
  virtual ~As2();
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

  void MakeGround();
  void MakeSky();
  void MakeFog();
  void MakeEnts();

  void UpdateCamera(const Ogre::FrameEvent& fe);
  void UpdateVelocityAndSelection(const Ogre::FrameEvent& fe);


  EntityMgr *entityMgr;
  //------------------------------------------------------------

  Ogre::SceneNode* cameraNode;

  float yaw;
  float deltaVelocity;
  float keyboardTimer;
  float surfaceHeight;
  const static float keyTime;

protected:
  virtual void createScene();

};

#endif // #ifndef __As2_h_
