/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UnitAI.h>
#include <Command.h>

#include <Utils.h>

const float InputMgr::keyTime = 0.5f;

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	this->selectionDistanceSquaredThreshold = std::numeric_limits<float>::infinity();
	this->mouseMode = true;
	this->interceptMode = true;
	this->lShiftDown = false;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	mMouse->capture();
//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);

}

void InputMgr::UpdateCamera(float dt){
    float move = 400.0f;
	float rotate = 0.1f;
    if(lShiftDown)
    {
        move *= 2;
        rotate *= 2;
    }
	
	keyboardTimer -= dt;

    Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
    
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_GRAVE))
    {
        keyboardTimer = keyTime;
        if(engine->gfxMgr->firstPerson == true)
        {
            engine->gfxMgr->firstPerson = false;
            engine->entityMgr->selectedEntity->cameraNode->detachObject(engine->gfxMgr->mCamera);
            engine->gameMgr->cameraNode->attachObject(engine->gfxMgr->mCamera);
        }
        else
        {
            engine->gfxMgr->firstPerson = true;
            engine->gameMgr->cameraNode->detachObject(engine->gfxMgr->mCamera);
            engine->entityMgr->selectedEntity->cameraNode->attachObject(engine->gfxMgr->mCamera);
        }
    }
    
    if(!engine->gfxMgr->firstPerson)
    {
        if (mKeyboard->isKeyDown(OIS::KC_W))
            dirVec.z -= move;
        
        if (mKeyboard->isKeyDown(OIS::KC_S))
            dirVec.z += move;
        
        if (mKeyboard->isKeyDown(OIS::KC_R))
            dirVec.y += move;
        
        if (mKeyboard->isKeyDown(OIS::KC_F))
        {
            dirVec.y -= move;
        }
        
        
        if (mKeyboard->isKeyDown(OIS::KC_A))
        {
            dirVec.x -= move;
        }
        if (mKeyboard->isKeyDown(OIS::KC_D))
        {
            dirVec.x += move;
        }
        
        if(mKeyboard->isKeyDown(OIS::KC_Q))
        {
            engine->gameMgr->cameraNode->yaw(Ogre::Degree(5 * rotate));
        }
        if(mKeyboard->isKeyDown(OIS::KC_E))
        {
            engine->gameMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate));
        }
        
        if(mKeyboard->isKeyDown(OIS::KC_Z))
        {
            engine->gameMgr->cameraNode->pitch(Ogre::Degree(5 * rotate));
        }
        if(mKeyboard->isKeyDown(OIS::KC_X))
        {
            engine->gameMgr->cameraNode->pitch(Ogre::Degree(-5 * rotate));
        }
        
        engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
        if(engine->gameMgr->cameraNode->getPosition().y < engine->gfxMgr->oceanHeight)
        {
            engine->gameMgr->cameraNode->setPosition(engine->gameMgr->cameraNode->getPosition().x, 5, engine->gameMgr->cameraNode->getPosition().z);
        }
    }
    
}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed += deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed -= deltaDesiredSpeed;
	}


	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD9)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0){
			engine->entityMgr->selectedFlyingEntity->desiredAltitude += deltaDesiredAltitude;
		}
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD3)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0)
			engine->entityMgr->selectedFlyingEntity->desiredAltitude -= deltaDesiredAltitude;
	}


	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading -= deltaDesiredHeading;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading += deltaDesiredHeading;
	}
	engine->entityMgr->selectedEntity->desiredHeading = FixAngle(engine->entityMgr->selectedEntity->desiredHeading);




	//Set velocity to zero....
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
		engine->entityMgr->selectedEntity->desiredSpeed = engine->entityMgr->selectedEntity->speed = 0;
		engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
	}

	//tab handling
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)){
		keyboardTimer = keyTime;
		if(engine->gfxMgr->firstPerson)
		{
		    engine->entityMgr->selectedEntity->cameraNode->detachObject(engine->gfxMgr->mCamera);
		}
		engine->entityMgr->SelectNextEntity();
		if(engine->gfxMgr->firstPerson)
		{
		    engine->entityMgr->selectedEntity->cameraNode->attachObject(engine->gfxMgr->mCamera);
		}
	}
	
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_G))
	{
	    keyboardTimer = keyTime;
	    mouseMode = !mouseMode;
	}
	
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_I))
    {
        keyboardTimer = keyTime;
        interceptMode = !interceptMode;
    }
}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
    if(ke.key == OIS::KC_LSHIFT)
    {
        lShiftDown = true;
    }
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
    if(ke.key == OIS::KC_LSHIFT)
    {
        lShiftDown = false;
    }
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
	if(OIS::MB_Left == mid){
		std::cout << "Left mouse press" << std::endl;
		HandleMouseSelection(me);
	}
	if(OIS::MB_Right == mid)
	{
	    std::cout << "Right mouse press" << std::endl;
	    HandleAI(me);
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	return true;
}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::HandleMouseSelection(const OIS::MouseEvent &me){
	const OIS::MouseState &ms = mMouse->getMouseState();
	int index = -1;
	Ogre::Viewport* vp = engine->gfxMgr->mSceneMgr->getCurrentViewport();
	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float)vp->getActualWidth(), ms.Y.abs/(float)vp->getActualHeight());
	
	if(mouseMode == true) // By distance
	{	    
        std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
        if(result.first){
            Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
            float minDistanceSquared = std::numeric_limits<float>::infinity();
            float distanceSquared; //because squareroot is expensive
            for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++){
                distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->entities[i]->position);
                if (distanceSquared < selectionDistanceSquaredThreshold){
                    if (distanceSquared < minDistanceSquared){
                        index = i;
                        minDistanceSquared = distanceSquared;
                    }
                }
            }
            if(engine->gfxMgr->firstPerson)
            {
                engine->entityMgr->selectedEntity->cameraNode->detachObject(engine->gfxMgr->mCamera);
            }
            engine->entityMgr->Select(index);
            if(engine->gfxMgr->firstPerson)
            {
                engine->entityMgr->selectedEntity->cameraNode->attachObject(engine->gfxMgr->mCamera);
            }
        }
	}
	else // By AABB
	{
	    index = engine->entityMgr->selectedEntityIndex;
	    for(std::vector<Entity381*>::iterator iter = engine->entityMgr->entities.begin(); iter != engine->entityMgr->entities.end(); iter++)
        {
	        std::pair<bool, float> result = mouseRay.intersects((*iter)->sceneNode->_getWorldAABB());
            if(result.first == true)
            {
                index = iter - engine->entityMgr->entities.begin();
            }
        }
        if(engine->gfxMgr->firstPerson)
        {
            engine->entityMgr->selectedEntity->cameraNode->detachObject(engine->gfxMgr->mCamera);
        }
        engine->entityMgr->Select(index);
        if(engine->gfxMgr->firstPerson)
        {
            engine->entityMgr->selectedEntity->cameraNode->attachObject(engine->gfxMgr->mCamera);
        }
	}
}




void InputMgr::HandleAI(const OIS::MouseEvent &me){
    const OIS::MouseState &ms = mMouse->getMouseState();
    Ogre::Viewport* vp = engine->gfxMgr->mSceneMgr->getCurrentViewport();
    Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float)vp->getActualWidth(), ms.Y.abs/(float)vp->getActualHeight());
    bool entityFound = false;
    
    Entity381* currentEntity = engine->entityMgr->selectedEntity;
    
    for(std::vector<Entity381*>::iterator iter = engine->entityMgr->entities.begin(); iter != engine->entityMgr->entities.end() && !entityFound; iter++)
    {
        std::pair<bool, float> result = mouseRay.intersects((*iter)->sceneNode->_getWorldAABB());
        if(result.first == true)
        {
            entityFound = true;
            Entity381* entity = *iter;
            for(unsigned int i = 0; i < currentEntity->aspects.size(); i++)
            {
                if(currentEntity->aspects[i]->aspectType == UNIT_AI)
                {
                    if(interceptMode)
                    {                        
                        Intercept* newCommand = new Intercept(currentEntity, entity->position, entity);
                        newCommand->init();
                        if(lShiftDown)
                        {
                            ((UnitAI*)currentEntity->aspects[i])->AddCommand((Command*)newCommand);                        
                        }
                        else
                        {
                            ((UnitAI*)currentEntity->aspects[i])->SetCommand((Command*)newCommand);  
                        }
                    }
                    else
                    {
                        Follow* newCommand = new Follow(currentEntity, entity->position, entity);
                        newCommand->init();
                        if(lShiftDown)
                        {
                            ((UnitAI*)currentEntity->aspects[i])->AddCommand((Command*)newCommand);                        
                        }
                        else
                        {
                            ((UnitAI*)currentEntity->aspects[i])->SetCommand((Command*)newCommand);  
                        }
                    }
                }
            }
        }
    }
    if(!entityFound)
    {
        std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
        if(result.first){
            std::cout << "Hello" << std::endl;
            Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
            for(unsigned int i = 0; i < currentEntity->aspects.size(); i++)
            {
                if(currentEntity->aspects[i]->aspectType == UNIT_AI)
                {
                    MoveTo* newCommand = new MoveTo(currentEntity, posUnderMouse, MOVE_TO);
                    newCommand->init();
                    if(lShiftDown)
                    {
                        ((UnitAI*)currentEntity->aspects[i])->AddCommand((Command*)newCommand);                        
                    }
                    else
                    {
                        ((UnitAI*)currentEntity->aspects[i])->SetCommand((Command*)newCommand);  
                    }
                }
            }
        }
    }
}


