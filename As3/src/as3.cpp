//============================================================================
// Name        : As3.cpp
// Author	   : Alexander Pasinski
// Contributor : Sushil J Louis
// Version     :
// Copyright   : All rights reserved
// Description : Assignment 3
//============================================================================

#include <as3.h>

//const float As3::keyTime = 0.07f;
const float As3::keyTime = 0.05f;

As3::As3(void)
{
    cameraYawWeight = 0.04f;
    cameraPitchWeight = 0.04f;
    cameraRollWeight = 0.04f;
    keyboardTimer = keyTime;
    cameraNode = 0;
    entityMgr = 0;
    surfaceHeight = 0;
    tabAvailable = true;
}

As3::~As3(void)
{
}

void As3::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    mCamera->lookAt(Ogre::Vector3(0, 0, 0));

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0, 80.0, 50.0);

    // a fixed point in the ocean so you can see relative motion
    Ogre::Entity* ogreEntityFixed = mSceneMgr->createEntity("robot.mesh");
    Ogre::SceneNode* sceneNode =
            mSceneMgr->getRootSceneNode()->createChildSceneNode(
                    Ogre::Vector3(0, 100, -200));
    sceneNode->attachObject(ogreEntityFixed);
    sceneNode->showBoundingBox(true);

    // A node to attach the camera to so we can move the camera node instead of the camera.
    cameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    cameraNode->setPosition(0, 200, 500);
    cameraNode->attachObject(mCamera);

    MakeGround();
    MakeSky();

    entityMgr = new EntityMgr(mSceneMgr);
    MakeEnts();
    entityMgr->SelectNextEntity();
}

void As3::MakeEnts()
{
    Ogre::Vector3 pos = Ogre::Vector3(0, 0, 0);

    for(int index = 1; index <= 5; index++)
    {
        entityMgr->CreateEntityOfTypeAtPosition(
                (EntityTypes)(BASE_TYPE + index), pos);
        pos.x += 250;
    }
}

void As3::UpdateCamera(const Ogre::FrameEvent& fe)
{
    float move = 400.0f;

    Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
    
    // Camera up/down/roll controls.
    if(mKeyboard->isKeyDown(OIS::KC_E))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        {
            cameraNode->roll(Ogre::Degree(5 * cameraRollWeight));            
        }
        else
        {
            dirVec.y += move;            
        }
    }
    if(mKeyboard->isKeyDown(OIS::KC_F))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        {
            cameraNode->roll(Ogre::Degree(-5 * cameraRollWeight));            
        }
        else
        {
            dirVec.y -= move;            
        }
    }

    
    // Camera left/right/yaw controls.
    if(mKeyboard->isKeyDown(OIS::KC_A))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        {
            cameraNode->yaw(Ogre::Degree(5 * cameraYawWeight));            
        }
        else
        {
            dirVec.x -= move;            
        }
    }
    if(mKeyboard->isKeyDown(OIS::KC_D))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        {
            cameraNode->yaw(Ogre::Degree(-5 * cameraYawWeight));            
        }
        else
        {
            dirVec.x += move;            
        }
    }

    
    // Camera forward/back/pitch controls.
    if(mKeyboard->isKeyDown(OIS::KC_W))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        {
            cameraNode->pitch(Ogre::Degree(5 * cameraPitchWeight));            
        }
        else
        {
            dirVec.z -= move;            
        }
    }
    if(mKeyboard->isKeyDown(OIS::KC_S))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        {
            cameraNode->pitch(Ogre::Degree(-5 * cameraPitchWeight));            
        }
        else
        {
            dirVec.z += move;            
        }
    }

    cameraNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

}

bool As3::frameRenderingQueued(const Ogre::FrameEvent& fe)
{

    mKeyboard->capture();
    if(mKeyboard->isKeyDown(OIS::KC_Q) || mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        return false;
    }

    mTrayMgr->frameRenderingQueued(fe);

    UpdateCamera(fe);

    UpdateVelocityAndSelection(fe);

    entityMgr->Tick(fe.timeSinceLastFrame);

    return true;
}

void As3::UpdateVelocityAndSelection(const Ogre::FrameEvent& fe)
{
    keyboardTimer -= fe.timeSinceLastEvent;

    // Entity speed controls.
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8))
    {
        keyboardTimer = keyTime;

        entityMgr->selectedEntity->desiredSpeed +=
                entityMgr->selectedEntity->acceleration;

        // Keep speed within min and max speeds.
        if(entityMgr->selectedEntity->desiredSpeed
                > entityMgr->selectedEntity->maxSpeed)
        {
            entityMgr->selectedEntity->desiredSpeed =
                    entityMgr->selectedEntity->maxSpeed;
        }
    }
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2))
    {
        keyboardTimer = keyTime;

        entityMgr->selectedEntity->desiredSpeed -=
                entityMgr->selectedEntity->acceleration;

        // Keep speed within min and max speeds.
        if(entityMgr->selectedEntity->desiredSpeed
                < entityMgr->selectedEntity->minSpeed)
        {
            entityMgr->selectedEntity->desiredSpeed =
                    entityMgr->selectedEntity->minSpeed;
        }
    }
    
    
    // Entity heading controls.
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6))
    {
        keyboardTimer = keyTime;

        entityMgr->selectedEntity->desiredHeading -=
                entityMgr->selectedEntity->turningRate;
    }
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4))
    {
        keyboardTimer = keyTime;

        entityMgr->selectedEntity->desiredHeading +=
                entityMgr->selectedEntity->turningRate;
    }

    
    // Entity stop controls.
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE))
    {
        keyboardTimer = keyTime;

        // Reduce speed to min speed.
        entityMgr->selectedEntity->desiredSpeed =
                entityMgr->selectedEntity->minSpeed;
    }

    
    // Entity selection controls.
    if(tabAvailable == true && (keyboardTimer < 0)
            && mKeyboard->isKeyDown(OIS::KC_TAB))
    {
        tabAvailable = false;
        keyboardTimer = keyTime;
        entityMgr->SelectNextEntity();
    }
}

// Keyboard Key Released
bool As3::keyReleased(const OIS::KeyEvent& ke)
{
    switch(ke.key)
    {
    case OIS::KC_TAB:
        tabAvailable = true;
        break;
    default:
        break;
    }

    return true;
}

void As3::MakeGround()
{

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, surfaceHeight);

    Ogre::MeshManager::getSingleton().createPlane("ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            15000, 15000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(
            groundEntity);
    groundEntity->setCastShadows(false);
    //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
    //groundEntity->setMaterialName("OceanHLSL_GLSL");
    groundEntity->setMaterialName("Ocean2_Cg");
    //groundEntity->setMaterialName("NavyCg");
}

void As3::MakeSky()
{
    mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}

void As3::MakeFog()
{
    Ogre::ColourValue fadeColour(0.2, 0.2, 0.2);
    mWindow->getViewport(0)->setBackgroundColour(fadeColour);
    mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char *argv[])
#endif
{
    // Create application object
    As3 app;

    try
    {
        app.go();
    }
    catch(Ogre::Exception& e)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occurred: "
                << e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
}

#ifdef __cplusplus
}
#endif

