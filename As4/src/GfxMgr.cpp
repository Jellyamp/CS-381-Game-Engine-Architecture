/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#include "GfxMgr.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <macUtils.h>
#endif

GfxMgr::GfxMgr(Engine *engine)
        : Mgr(engine)
{
    mRoot = NULL;
    mCamera = NULL;
    mSceneMgr = NULL;
    mWindow = NULL;
    mResourcesCfg = Ogre::StringUtil::BLANK;
    mPluginsCfg = Ogre::StringUtil::BLANK;
    mOverlaySystem = NULL;
    
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
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources_d.cfg";
    mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = mResourcePath + "resources.cfg";
    mPluginsCfg = mResourcePath + "plugins.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
#endif
    
    mRoot = new Ogre::Root(mPluginsCfg);
    
    SetupResources();
    
    bool carryOn = Configure();
    if(!carryOn) 
    {
        engine->keepRunning = false;
    }
    
    ChooseSceneManager();
    CreateCamera();
    CreateViewports();
    
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    CreateResourceListener();
    // Load resources
    LoadResources();
}

void GfxMgr::LoadLevel()
{

}

void GfxMgr::Stop()
{
    if (mOverlaySystem) delete mOverlaySystem;

    // Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, engine->inputMgr);
    
    delete mRoot;
}

void GfxMgr::Tick(float dt)
{
    mRoot->renderOneFrame();
}


void GfxMgr::SetupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app.
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location.
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative directories
                archName = Ogre::String(Ogre::macBundlePath() + "/" + archName);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

Ogre::Root* GfxMgr::GetRoot()
{
    return mRoot;
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



bool GfxMgr::Configure(void)
{
    // Show the configuration dialog and initialise the system.
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg.
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise.
        // Here we choose to let the system create a default rendering window by passing 'true'.
        mWindow = mRoot->initialise(true, "CS381 - Assignment Four");

        return true;
    }
    else
    {
        return false;
    }
}

void GfxMgr::ChooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Initialize the OverlaySystem (changed for Ogre 1.9)
    mOverlaySystem = new Ogre::OverlaySystem();
    mSceneMgr->addRenderQueueListener(mOverlaySystem);
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

void GfxMgr::CreateViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void GfxMgr::CreateResourceListener(void)
{
}

void GfxMgr::LoadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

