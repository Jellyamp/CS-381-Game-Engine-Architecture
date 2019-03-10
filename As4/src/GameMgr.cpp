/*
 * GameMgr.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#include "GameMgr.h"

GameMgr::GameMgr(Engine *engine)
        : Mgr(engine)
{
    mCameraNode = NULL;
    mDeltaDesiredSpeed = 5.0f; //lets say the user can change the desired speed in increments/decrements of 5
    mDeltaDesiredHeading = 5.0f; // lets say the user can change desired heading in increments/decrements of 5 degree
}

GameMgr::~GameMgr()
{

}

void GameMgr::Init()
{

}

void GameMgr::Stop()
{
    DestroyScene();
}

void GameMgr::Tick(float dt)
{
    
}

void GameMgr::LoadLevel()
{
    engine->gfxMgr->GetSceneMgr()->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    engine->gfxMgr->GetCamera()->lookAt(Ogre::Vector3(0, 0, 0));

    
    MakeLight(Ogre::Vector3(20.0, 80.0, 50.0), "MainLight");
    MakeCamera(Ogre::Vector3(0, 200, 500));
    MakeGround();
    MakeSky("Examples/MorningSkyBox");
    MakeEnts();
    
    
    // A fixed point in the ocean so you can see relative motion
    Ogre::Entity* ogreEntityFixed = engine->gfxMgr->GetSceneMgr()->createEntity("robot.mesh");
    Ogre::SceneNode* sceneNode = engine->gfxMgr->GetSceneMgr()->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
    sceneNode->attachObject(ogreEntityFixed);
    sceneNode->showBoundingBox(true);
}


Ogre::SceneNode* GameMgr::GetCameraNode()
{
    return mCameraNode;
}

float GameMgr::GetDeltaDesiredSpeed()
{
    return mDeltaDesiredSpeed;
}
float GameMgr::GetDeltaDesiredHeading()
{
    return mDeltaDesiredHeading;
}


void GameMgr::DestroyScene(void)
{
}

void GameMgr::MakeLight(Ogre::Vector3 pos, Ogre::String name)
{
    Ogre::Light* light = engine->gfxMgr->GetSceneMgr()->createLight(name);
    light->setPosition(pos);
}

void GameMgr::MakeCamera(Ogre::Vector3 pos)
{
    // A node to attach the camera to so we can move the camera node instead of the camera.
    mCameraNode = engine->gfxMgr->GetSceneMgr()->getRootSceneNode()->createChildSceneNode();
    mCameraNode->setPosition(pos);
    mCameraNode->attachObject(engine->gfxMgr->GetCamera());
}

void GameMgr::MakeEnts()
{

    Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 0);
    
    engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
    pos.x += 500;
    engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
    pos.x += 500;
    engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
    pos.x += 500;
    engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
    pos.x += 500;
    engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

    engine->entityMgr->SelectNextEntity(); //sets selection

}

void GameMgr::MakeGround()
{

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane("ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            15000, 15000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* groundEntity = engine->gfxMgr->GetSceneMgr()->createEntity("ground");
    engine->gfxMgr->GetSceneMgr()->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Ocean2_Cg");
}

void GameMgr::MakeSky(Ogre::String skyBoxName)
{
    engine->gfxMgr->GetSceneMgr()->setSkyBox(true, skyBoxName);
}

void GameMgr::MakeFog()
{
    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    engine->gfxMgr->GetWindow()->getViewport(0)->setBackgroundColour(fadeColour);
    engine->gfxMgr->GetSceneMgr()->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
}
