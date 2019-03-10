/*
 * GfxMgr.h
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_GFXMGR_H_
#define INC_GFXMGR_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include "Mgr.h"
#include "Engine.h"
#include "EntityMgr.h"
#include "GameMgr.h"
#include "InputMgr.h"

class GfxMgr : public Mgr
{
public:
    GfxMgr(Engine *engine);
    virtual ~GfxMgr();

    void Init();
    void LoadLevel();
    void Tick(float dt);
    void Stop();
    
    Ogre::SceneManager* GetSceneMgr();
    Ogre::Camera* GetCamera();
    Ogre::RenderWindow* GetWindow();
    
private:
    void CreateCamera(void);
    
    Ogre::Root*                 mRoot;
    Ogre::Camera*               mCamera;
    Ogre::SceneManager*         mSceneMgr;
    Ogre::RenderWindow*         mWindow;
    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;
    
    // Added for Mac compatibility
    Ogre::String                mResourcePath;
};



#endif /* INC_GFXMGR_H_ */
