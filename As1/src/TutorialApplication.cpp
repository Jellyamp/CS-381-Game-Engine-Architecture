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
As2::As2(void)
{
	mSphereVelocity = 0;
	mSurfaceHeight = 0;
	mBaseSphereAcceleration = 1;
	mSphereNode = NULL;
	mSphereInitialPosition = Ogre::Vector3(0, 200, 0);
	mCameraPosition = 0;
	mBaseCameraVelocity = 0.2;
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

	// Camera
	mCamera->setPosition(0, 200, 600);
	mCameraPosition = mCamera->getPosition();

	// Sphere
    Ogre::Entity* sphereEnt = createEntity("sphere.mesh");
    mSphereNode = createSceneNode("sphereNode");
    mSphereNode->attachObject(sphereEnt);
    mSphereNode->setPosition(mSphereInitialPosition);

    // Plane entity
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, mSurfaceHeight);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
    												10000, 10000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    
    // Floor
    Ogre::SceneNode* floorNode = createSceneNode("floorNode");
    Ogre::Entity* floorEntity = createEntity("ground");
    floorNode->attachObject(floorEntity);
    floorEntity->setCastShadows(false);
    floorEntity->setMaterialName("Examples/Rockwall");
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

bool As2::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	if(!processUnbufferedInput(fe))
	{
		return false;
	}

	// Update sphere position based on current velocity.
	//mSphereNode->setPosition(mSphereNode->getPosition() + mSphereVelocity * fe.timeSinceLastFrame);
	mSphereNode->translate(mSphereVelocity * fe.timeSinceLastFrame); // This works better with kinematic physics than teleporting.
	mCamera->setPosition(mCameraPosition);
	
	return BaseApplication::frameRenderingQueued(fe);
}

bool As2::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	if(mKeyboard->isKeyDown(OIS::KC_SPACE)) // Reset sphere velocity to 0 in all directions.
	{
		mSphereVelocity = 0;
	}
	if(mKeyboard->isKeyDown(OIS::KC_GRAVE)) // Reset the sphere velocity and position.
	{
		mSphereVelocity = 0;
		mSphereNode->setPosition(mSphereInitialPosition);
	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD2)) // Increase the sphere velocity in the z direction.
	{
		mSphereVelocity.z += mBaseSphereAcceleration;
	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD8)) // Increase the sphere velocity in the -z direction.
	{
		mSphereVelocity.z -= mBaseSphereAcceleration;
	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD6)) // Increase the sphere velocity in the x direction.
	{
		mSphereVelocity.x += mBaseSphereAcceleration;
	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD4)) // Increase the sphere velocity in the -x direction.
	{
		mSphereVelocity.x -= mBaseSphereAcceleration;
	}
	if(mKeyboard->isKeyDown(OIS::KC_PGUP)) // Increase the sphere velocity in the y direction.
	{
		mSphereVelocity.y += mBaseSphereAcceleration;
	}
	if(mKeyboard->isKeyDown(OIS::KC_PGDOWN)) // Increase the sphere velocity in the -y direction.
	{
		mSphereVelocity.y -= mBaseSphereAcceleration;
	}
	if(mKeyboard->isKeyDown(OIS::KC_S)) // Move the camera in the z direction.
	{
		mCameraPosition.z += mBaseCameraVelocity;
	}
	if(mKeyboard->isKeyDown(OIS::KC_W)) // Move the camera in the -z direction.
	{
		mCameraPosition.z -= mBaseCameraVelocity;
	}
	if(mKeyboard->isKeyDown(OIS::KC_D)) // Move the camera in the x direction.
	{
		mCameraPosition.x += mBaseCameraVelocity;
	}
	if(mKeyboard->isKeyDown(OIS::KC_A)) // Move the camera in the -x direction.
	{
		mCameraPosition.x -= mBaseCameraVelocity;
	}
	if(mKeyboard->isKeyDown(OIS::KC_E)) // Move the camera in the y direction.
	{
		mCameraPosition.y += mBaseCameraVelocity;
	}
	if(mKeyboard->isKeyDown(OIS::KC_F)) // Move the camera in the -y direction.
	{
		mCameraPosition.y -= mBaseCameraVelocity;
	}

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
