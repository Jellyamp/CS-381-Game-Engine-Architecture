/*
 * As3.h
 *
 *  Created on: Jan 24, 2017
 *      Author: sushil
 */

#ifndef __As3_h_
#define __As3_h_

#include "BaseApplication.h"
#include <EntityMgr.h>
#include <Types381.h>

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
  //------------------------------------------------------------

  Ogre::SceneNode* cameraNode;

  float deltaDesiredSpeed; // user changes desired speed by this much
  float deltaDesiredHeading; //user changes desired heading by this much

  float keyboardTimer;
  const static float keyTime = 0.1f;

protected:
  virtual void createScene();

};

#endif // #ifndef __As3_h_
