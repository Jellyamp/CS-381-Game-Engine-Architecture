/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */


#include <iostream>

#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>

#include <Engine.h>
#include <GfxMgr.h>

GfxMgr::GfxMgr(Engine *engine): Mgr(engine) {

	mRoot = 0;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg   = Ogre::StringUtil::BLANK;
	mWindow = 0;
	mSceneMgr = 0;
	mCamera = 0;
}

GfxMgr::~GfxMgr() {

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

void GfxMgr::Init(){
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
  mPluginsCfg = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
#endif

  mRoot = new Ogre::Root(mPluginsCfg);

  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  Ogre::String name, locType;
  Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

  while (secIt.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator it;

    for (it = settings->begin(); it != settings->end(); ++it)
    {
      locType = it->first;
      name = it->second;

      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
  }

  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	  std::cerr << "Could not find Config File and could not show Config Dialog" << std::endl;

  mWindow = mRoot->initialise(true, "CS381 Game Engine Version 1.0");

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  mCamera = mSceneMgr->createCamera("MainCam");
  mCamera->setPosition(0, 0, 80);
  mCamera->lookAt(0, 0, -300);
  mCamera->setNearClipDistance(5);

  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  mCamera->setAspectRatio(
    Ogre::Real(vp->getActualWidth()) /
    Ogre::Real(vp->getActualHeight()));

  //-----------------------------------------------------------------------
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
  //mRoot->addFrameListener(this);
  //mRoot->startRendering();


}

void GfxMgr::windowClosed(Ogre::RenderWindow *rw){
	mRoot->shutdown();
	engine->keepRunning = false;
}

bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe){
	if(mWindow->isClosed()) return false;
	return true;
}


void GfxMgr::LoadLevel(){

}

void GfxMgr::Stop(){
	mRoot->shutdown();
}

void GfxMgr::Tick(float dt){
//call ogre root render one frame method
	mRoot->renderOneFrame(dt);
	Ogre::WindowEventUtilities::messagePump();
}

