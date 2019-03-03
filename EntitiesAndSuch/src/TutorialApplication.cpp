/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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

#include "../inc/TutorialApplication.h"

//---------------------------------------------------------------------------
As3::As3(void)
{
	mSurfaceHeight = 0;
	mHouseNode = NULL;
	mHouseInitialPosition = Ogre::Vector3(0, 0, 0);
	mCameraPosition = 0;
	mCameraNode = NULL;
	mDirection = 0;
	mMove = 100;
}
//---------------------------------------------------------------------------
As3::~As3(void)
{
}

//---------------------------------------------------------------------------
void As3::createScene(void)
{
	Ogre::SceneNode* tempNode = NULL; // Used for temporary management of scene nodes.
	
	// Lighting Setup
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	// Light
	Ogre::Light* lt = createLight("MyLight");
	Ogre::SceneNode* lightNode = createSceneNode("light");
	lightNode->attachObject(lt);
	lightNode->setPosition(500, 500, 500);

	tempNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(1200, -370, 0));
	tempNode->yaw(Ogre::Degree(90));

	mCameraNode = tempNode;
	tempNode->attachObject(mCamera);
	
	tempNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Ogre::Vector3(-500, -370, 1000));
	tempNode->yaw(Ogre::Degree(-30));

	// House
    Ogre::Entity* houseEnt = createEntity("tudorhouse.mesh");
    mHouseNode = createSceneNode("sphereNode");
    mHouseNode->attachObject(houseEnt);
    mHouseNode->setPosition(mHouseInitialPosition);
}

/*
 * This function creates a new scene node and returns a pointer to it as well as setting a lookup name for later.
 */
Ogre::SceneNode* As3::createSceneNode(Ogre::String nodeName)
{
	return mSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName);
}

/*
 * This function creates a new entity and returns a pointer to it.
 */
Ogre::Entity* As3::createEntity(Ogre::String entityName)
{
	return mSceneMgr->createEntity(entityName);
}

/*
 * This function creates a new light and returns a pointer to it.
 */
Ogre::Light* As3::createLight(Ogre::String lightName)
{
	return mSceneMgr->createLight(lightName);
}

/*
 * This function runs just before the output of every frame.
 */
bool As3::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	mCameraNode->translate(mDirection * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	
	return BaseApplication::frameRenderingQueued(fe);
}


/**********************
 * Keyboard Buffered Input Functions
 **********************/

// Keyboard Key Pressed
bool As3::keyPressed(const OIS::KeyEvent& ke) 
{ 
	switch (ke.key)
	{
		case OIS::KC_ESCAPE: 
			mShutDown = true;
			break;
			
		case OIS::KC_1:
			mCamera->getParentSceneNode()->detachObject(mCamera);
			mCameraNode = mSceneMgr->getSceneNode("CamNode1");
			mCameraNode->attachObject(mCamera);
			break;
		case OIS::KC_2:
			mCamera->getParentSceneNode()->detachObject(mCamera);
			mCameraNode = mSceneMgr->getSceneNode("CamNode2");
			mCameraNode->attachObject(mCamera);
			break;
			
		case OIS::KC_UP:
		case OIS::KC_W:
		    mDirection.z = -mMove;
		    break;
		  
		case OIS::KC_DOWN:
		case OIS::KC_S:
		    mDirection.z = mMove;
		    break;
		  
		case OIS::KC_LEFT:
		case OIS::KC_A:
		    mDirection.x = -mMove;
		    break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
		    mDirection.x = mMove;
		    break;
		 
		case OIS::KC_PGDOWN:
		case OIS::KC_E:
		    mDirection.y = -mMove;
		    break;
		  
		case OIS::KC_PGUP:
		case OIS::KC_Q:
		    mDirection.y = mMove;
		    break;
		default:
			break;
	}
	
	return true; 
}

// Keyboard Key Released
bool As3::keyReleased(const OIS::KeyEvent& ke) 
{ 
	switch (ke.key)
	{
		case OIS::KC_UP:
		case OIS::KC_W:
			mDirection.z = 0;
			break;
	
		case OIS::KC_DOWN:
		case OIS::KC_S:
			mDirection.z = 0;
			break;
	
		case OIS::KC_LEFT:
		case OIS::KC_A:
			mDirection.x = 0;
			break;
	
		case OIS::KC_RIGHT:
		case OIS::KC_D:
			mDirection.x = 0;
			break;
	
		case OIS::KC_PGDOWN:
		case OIS::KC_E:
			mDirection.y = 0;
			break;
	
		case OIS::KC_PGUP:
		case OIS::KC_Q:
			mDirection.y = 0;
			break;
	
		default:
			break;
	}
	return true; 
}


/**********************
 * Mouse Buffered Input Functions
 **********************/

// Mouse Moved
bool As3::mouseMoved(const OIS::MouseEvent& me) 
{ 
	return true; 
}

// Mouse Pressed
bool As3::mousePressed(
  const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{ 
	return true; 
}

// Mouse Released
bool As3::mouseReleased(
  const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{ 
	return true; 
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        As3 app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
