/*
 * InputMgr.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#include "InputMgr.h"

InputMgr::InputMgr(Engine *engine)
        : Mgr(engine)
{
    mInputContext = NULL;
    mTrayMgr = NULL;
    mCameraMan = NULL;         
    mDetailsPanel = NULL;      
    mCursorWasVisible = NULL;  
    mShutDown = NULL;
    mInputManager = NULL;
    mMouse = NULL;
    mKeyboard = NULL;
}

InputMgr::~InputMgr()
{

}

void InputMgr::Init()
{
    AttachCamera();
}

void InputMgr::LoadLevel()
{

}

void InputMgr::Stop()
{

}

void InputMgr::Tick(float dt)
{

}


void InputMgr::AttachCamera()
{
    mCameraMan = new OgreBites::SdkCameraMan(engine->gfxMgr->GetCamera());   // Create a default camera controller
}
