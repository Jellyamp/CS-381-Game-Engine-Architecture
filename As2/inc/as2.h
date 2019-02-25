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

#include "EntityMgr.h"
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
    virtual bool keyPressed(const OIS::KeyEvent& ke);
    virtual bool keyReleased(const OIS::KeyEvent& ke);
    virtual bool mouseMoved(const OIS::MouseEvent& me);
    virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
    
    /*
     * Helper functions to shorten code segments and increase readability.
     */
    void createGround();
    void selectNextEntity();
    Ogre::SceneNode* createSceneNode(Ogre::String nodeName);
    Ogre::Entity* createEntity(Ogre::String entityName);
    Ogre::Light* createLight(Ogre::String lightName);

private:
    bool processUnbufferedInput(const Ogre::FrameEvent& fe);

    EntityMgr mEntityMgr;
    
    std::vector<Entity381*> m381Entities;	// A list of the Entity381 objects in the scene.
    
    Entity381* mCurrentEntity381;			// The currently selected 381 entity.
    
    int mCurrentEntityIndex;				// The current entity index.
    
    Ogre::SceneNode* mCameraNode;			// A scene node pointer for the current camera object.
    Ogre::SceneNode* tempNode;

    Ogre::Vector3 mHouseInitialPosition;	// The initial position of the sphere.
    Ogre::Vector3 mCameraPosition; 			// The current position of the camera.
    Ogre::Vector3 mDirection;				// The current direction vector for the current camera.
    Ogre::Vector3 mCameraRotation;			// The current camera rotation.
    
    float mMove;							// The base velocity of the camera.
    float mSurfaceHeight; 					// The height of the plane along the axis that it was created on.
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
