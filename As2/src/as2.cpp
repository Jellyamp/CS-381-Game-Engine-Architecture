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

#include <as2.h>

//---------------------------------------------------------------------------
As2::As2(void)
{
	mSurfaceHeight = 0;
	mCurrentEntity381 = NULL;
	mHouseInitialPosition = Ogre::Vector3(0, 0, 0);
	mCameraPosition = 0;
	mCameraNode = NULL;
	mDirection = 0;
	mCameraRotation = 0;
	mMove = 100;
	mCurrentEntityIndex = 0;
	tempNode = NULL;
}
//---------------------------------------------------------------------------
As2::~As2(void)
{
}

//---------------------------------------------------------------------------
void As2::createScene(void)
{
	// Lighting Setup
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	// Light
	Ogre::Light* lt = createLight("MyLight");
	Ogre::SceneNode* lightNode = createSceneNode("light");
	lightNode->attachObject(lt);
	lightNode->setPosition(500, 500, 500);

	tempNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(0, 100, 0));
	tempNode->yaw(Ogre::Degree(90));

	mCameraNode = tempNode;
	tempNode->attachObject(mCamera);
	
	createGround();
	
	mEntityMgr.CreateEntity();
}

void As2::createGround()
{
    // Plane entity
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, mSurfaceHeight);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
    												10000, 10000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    
    // Floor
    Ogre::SceneNode* floorNode = createSceneNode("floorNode");
    Ogre::Entity* floorEntity = createEntity("ground");
    floorNode->attachObject(floorEntity);
    floorEntity->setCastShadows(false);
    floorEntity->setMaterialName("Ocean2_Cg");
}

void As2::selectNextEntity()
{
}

/*
 * This function creates a new scene node and returns a pointer to it as well as setting a lookup name for later.
 */
Ogre::SceneNode* As2::createSceneNode(Ogre::String nodeName)
{
	return mSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName);
}

/*
 * This function creates a new entity and returns a pointer to it.
 */
Ogre::Entity* As2::createEntity(Ogre::String entityName)
{
	return mSceneMgr->createEntity(entityName);
}

/*
 * This function creates a new light and returns a pointer to it.
 */
Ogre::Light* As2::createLight(Ogre::String lightName)
{
	return mSceneMgr->createLight(lightName);
}

/*
 * This function runs just before the output of every frame.
 */
bool As2::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	mCameraNode->translate(mDirection * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	
	return BaseApplication::frameRenderingQueued(fe);
}


/**********************
 * Keyboard Buffered Input Functions
 **********************/

// Keyboard Key Pressed
bool As2::keyPressed(const OIS::KeyEvent& ke)
{
	if(ke.key == OIS::KC_LSHIFT) // Extended shift input commands.
	{
		if(mKeyboard->isKeyDown(OIS::KC_A))
		{
			// Change camera yaw.
		}
		else if(mKeyboard->isKeyDown(OIS::KC_D))
		{
			// Change camera yaw.
		}
	}
	else	// Normal input commands.
	{
		switch (ke.key)
		{
		// QUIT PROGRAM
		case OIS::KC_Q:
		case OIS::KC_ESCAPE: 
			mShutDown = true;
			break;
			
		// CAMERA MOVE
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
		case OIS::KC_F:
			mDirection.y = -mMove;
			break;
		case OIS::KC_E:
			mDirection.y = mMove;
			break;
		 
		// Current Entity Velocity
		case OIS::KC_NUMPAD2:
			mCurrentEntity381->Accelerate(ZPLUS);
			break;
		case OIS::KC_NUMPAD8:
			mCurrentEntity381->Accelerate(ZMINUS);
			break;
		case OIS::KC_NUMPAD4:
			mCurrentEntity381->Accelerate(XPLUS);
			break;
		case OIS::KC_NUMPAD6:
			mCurrentEntity381->Accelerate(XMINUS);
			break;
		case OIS::KC_PGUP:
			mCurrentEntity381->Accelerate(YPLUS);
			break;
		case OIS::KC_PGDOWN:
			mCurrentEntity381->Accelerate(YMINUS);
			break;
		default:
			break;
		}
	}
	
	return true; 
}

// Keyboard Key Released
bool As2::keyReleased(const OIS::KeyEvent& ke) 
{ 
	switch (ke.key)
	{
	case OIS::KC_LSHIFT:
		break;
		
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
bool As2::mouseMoved(const OIS::MouseEvent& me) 
{ 
	return true; 
}

// Mouse Pressed
bool As2::mousePressed(
  const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{ 
	return true; 
}

// Mouse Released
bool As2::mouseReleased(
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
        As2 app;

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
