/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class As2 : public BaseApplication
{
public:
    As2(void);
    virtual ~As2(void);

protected:
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
    
    /*
     * Helper functions to shorten code segments and increase readability.
     */
    Ogre::SceneNode* createSceneNode(Ogre::String nodeName);
    Ogre::Entity* createEntity(Ogre::String entityName);
    Ogre::Light* createLight(Ogre::String lightName);

private:
    bool processUnbufferedInput(const Ogre::FrameEvent& fe);

    Ogre::SceneNode* mSphereNode; 			// A scene node pointer for the current sphere object.
    
    Ogre::Vector3 mSphereVelocity; 			// The current velocity of the sphere in x, y, and z respectively.
    Ogre::Vector3 mSphereInitialPosition;	// The initial position of the sphere.
    Ogre::Vector3 mCameraPosition; 			// The current position of the camera.
    
    float mBaseSphereAcceleration; 			// The base acceleration of the sphere when its velocity is increased.
    float mBaseCameraVelocity; 				// The base velocity that the camera will move by whenever a key is pressed.
    float mSurfaceHeight; 					// The height of the plane along the axis that it was created on.
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
