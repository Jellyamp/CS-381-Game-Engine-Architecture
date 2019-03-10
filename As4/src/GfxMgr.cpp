/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#include "GfxMgr.h"

GfxMgr::GfxMgr(Engine *engine)
        : Mgr(engine)
{
    mRoot = NULL;
    mCamera = NULL;
    mSceneMgr = NULL;
    mWindow = NULL;
    mResourcesCfg = NULL;
    mPluginsCfg = NULL;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
    mResourcePath = "";
#endif
}

GfxMgr::~GfxMgr()
{

}

void GfxMgr::Init()
{

}

void GfxMgr::LoadLevel()
{

}

void GfxMgr::Stop()
{

}

void GfxMgr::Tick(float dt)
{

}


Ogre::SceneManager* GfxMgr::GetSceneMgr()
{
    return mSceneMgr;
}

Ogre::Camera* GfxMgr::GetCamera()
{
    return mCamera;
}

Ogre::RenderWindow* GfxMgr::GetWindow()
{
    return mWindow;
}



void GfxMgr::CreateCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);
}
