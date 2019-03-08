//============================================================================
// Name        : As3.cpp
// Author      : Sushil J Louis
// Version     :
// Copyright   : All rights reserved
// Description : Assignment 1
//============================================================================

#include <as3.h>
#include <Utils.h>

As3::As3(void)
{
	keyboardTimer = keyTime;
	cameraNode = 0;
	entityMgr = 0;

	deltaDesiredSpeed = 5.0f; //lets say the user can change the desired speed in increments/decrements of 5
	deltaDesiredHeading = 5.0f; // lets say the user can change desired heading in increments/decrements of 5 degree
	//we can tune this later
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
  Ogre::SceneNode* sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
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
}

void As3::MakeEnts(){

	Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 0);
	entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 500;
	entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x += 500;
	entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x += 500;
	entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x += 500;
	entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);


	entityMgr->SelectNextEntity(); //sets selection

}

void As3::UpdateCamera(const Ogre::FrameEvent& fe){
	float move = 400.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	  if (mKeyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (mKeyboard->isKeyDown(OIS::KC_E))
	    dirVec.y += move;

	  if (mKeyboard->isKeyDown(OIS::KC_F))
	    dirVec.y -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_A))
	  {
	    if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		      cameraNode->yaw(Ogre::Degree(5 * rotate));
	    else
	      dirVec.x -= move;
	  }

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	  {
	    if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	      cameraNode->yaw(Ogre::Degree(-5 * rotate));
	    else
	      dirVec.x += move;
	  }

	  cameraNode->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

}

bool As3::frameRenderingQueued(const Ogre::FrameEvent& fe){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_Q)){
		return false;
	}

	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(fe);

	UpdateVelocityAndSelection(fe);

	entityMgr->Tick(fe.timeSinceLastFrame);

	return true;
}


void As3::UpdateVelocityAndSelection(const Ogre::FrameEvent& fe){
	keyboardTimer -= fe.timeSinceLastEvent;

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)){
		keyboardTimer = keyTime;
		entityMgr->selectedEntity->desiredSpeed += deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)){
		keyboardTimer = keyTime;
		entityMgr->selectedEntity->desiredSpeed -= deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)){
		keyboardTimer = keyTime;
		entityMgr->selectedEntity->desiredHeading -= deltaDesiredHeading;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)){
		keyboardTimer = keyTime;
		entityMgr->selectedEntity->desiredHeading += deltaDesiredHeading;
	}
	entityMgr->selectedEntity->desiredHeading = FixAngle(entityMgr->selectedEntity->desiredHeading);

	//Set velocity to zero....
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		keyboardTimer = keyTime;
		entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
		entityMgr->selectedEntity->desiredSpeed = entityMgr->selectedEntity->speed = 0;
		entityMgr->selectedEntity->desiredHeading = entityMgr->selectedEntity->heading;
	}

	//tab handling
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)){
		keyboardTimer = keyTime;
		entityMgr->SelectNextEntity();
	}

}

void As3::MakeGround(){

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	  Ogre::MeshManager::getSingleton().createPlane(
	    "ground",
	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	    plane,
	    15000, 15000, 20, 20,
	    true,
	    1, 5, 5,
	    Ogre::Vector3::UNIT_Z);

	  Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	  mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  groundEntity->setCastShadows(false);
	  //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	  //groundEntity->setMaterialName("OceanHLSL_GLSL");
	  groundEntity->setMaterialName("Ocean2_Cg");
	  //groundEntity->setMaterialName("NavyCg");
}

void As3::MakeSky(){
	mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}

void As3::MakeFog(){
	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
}


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


