/*
 * InputMgr.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#include "InputMgr.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <macUtils.h>
#endif

const float InputMgr::keyTime = 0.05f;

InputMgr::InputMgr(Engine *engine)
        : Mgr(engine)
{
    mTrayMgr = NULL;
    mCameraMan = NULL;
    mDetailsPanel = NULL;
    mCursorWasVisible = NULL;
    mInputManager = NULL;
    mMouse = NULL;
    mKeyboard = NULL;
    keyboardTimer = keyTime;
}

InputMgr::~InputMgr()
{

}

void InputMgr::Init()
{
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    AttachCamera();
    CreateFrameListener();
}

void InputMgr::LoadLevel()
{

}

void InputMgr::Stop()
{
    if(mTrayMgr)
        delete mTrayMgr;
    if(mCameraMan)
        delete mCameraMan;

    windowClosed(engine->gfxMgr->GetWindow());
}

void InputMgr::Tick(float dt)
{

}

void InputMgr::AttachCamera()
{
    mCameraMan = new OgreBites::SdkCameraMan(engine->gfxMgr->GetCamera());   // Create a default camera controller
}

void InputMgr::CreateFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    engine->gfxMgr->GetWindow()->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

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

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(engine->gfxMgr->GetWindow());

    // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->GetWindow(), this);

    mInputContext.mKeyboard = mKeyboard;
    mInputContext.mMouse = mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->GetWindow(), mInputContext, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

    // Create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    engine->gfxMgr->GetRoot()->addFrameListener(this);
}

bool InputMgr::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
    mKeyboard->capture();
    if(mKeyboard->isKeyDown(OIS::KC_Q))
    {
        return false;
    }

    mTrayMgr->frameRenderingQueued(fe);

    UpdateCamera(fe);
    UpdateVelocityAndSelection(fe);

    return true;
}

void InputMgr::UpdateCamera(const Ogre::FrameEvent& fe)
{
    float move = 400.0f;
    float rotate = 0.1f;

    Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

    if(mKeyboard->isKeyDown(OIS::KC_W))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            engine->gameMgr->GetCameraNode()->pitch(Ogre::Degree(5 * rotate));
        else
            dirVec.z -= move;
    }

    if(mKeyboard->isKeyDown(OIS::KC_S))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            engine->gameMgr->GetCameraNode()->pitch(Ogre::Degree(-5 * rotate));
        else
            dirVec.z += move;        
    }

    if(mKeyboard->isKeyDown(OIS::KC_PGUP))
    {        
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            engine->gameMgr->GetCameraNode()->roll(Ogre::Degree(-5 * rotate));
        else
            dirVec.y += move;   
    }

    if(mKeyboard->isKeyDown(OIS::KC_PGDOWN))
    {        
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            engine->gameMgr->GetCameraNode()->roll(Ogre::Degree(5 * rotate));
        else
            dirVec.y -= move;   
    }

    if(mKeyboard->isKeyDown(OIS::KC_A))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            engine->gameMgr->GetCameraNode()->yaw(Ogre::Degree(5 * rotate));
        else
            dirVec.x -= move;
    }

    if(mKeyboard->isKeyDown(OIS::KC_D))
    {
        if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
            engine->gameMgr->GetCameraNode()->yaw(Ogre::Degree(-5 * rotate));
        else
            dirVec.x += move;
    }

    engine->gameMgr->GetCameraNode()->translate(dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateVelocityAndSelection(const Ogre::FrameEvent& fe)
{
    keyboardTimer -= fe.timeSinceLastEvent;

    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8))
    {
        keyboardTimer = keyTime;
        engine->entityMgr->selectedEntity->desiredSpeed += engine->gameMgr->GetDeltaDesiredSpeed();
    }
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2))
    {
        keyboardTimer = keyTime;
        engine->entityMgr->selectedEntity->desiredSpeed -= engine->gameMgr->GetDeltaDesiredSpeed();
    }
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4))
    {
        keyboardTimer = keyTime;
        engine->entityMgr->selectedEntity->desiredHeading -= engine->gameMgr->GetDeltaDesiredHeading();
        //turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
    }
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6))
    {
        keyboardTimer = keyTime;
        engine->entityMgr->selectedEntity->desiredHeading += engine->gameMgr->GetDeltaDesiredHeading();
    }
    engine->entityMgr->selectedEntity->desiredHeading = FixAngle(engine->entityMgr->selectedEntity->desiredHeading);

    //Set velocity to zero....
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE))
    {
        keyboardTimer = keyTime;
        engine->entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
        engine->entityMgr->selectedEntity->desiredSpeed = engine->entityMgr->selectedEntity->speed = 0;
        engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
    }

    //tab handling
    if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB))
    {
        keyboardTimer = keyTime;
        engine->entityMgr->SelectNextEntity();
    }
}

bool InputMgr::keyPressed(const OIS::KeyEvent &arg)
{
//    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
//
//    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
//    {
//        mTrayMgr->toggleAdvancedFrameStats();
//    }
//    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
//    {
//        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
//        {
//            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
//            mDetailsPanel->show();
//        }
//        else
//        {
//            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
//            mDetailsPanel->hide();
//        }
//    }
//    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
//    {
//        Ogre::String newVal;
//        Ogre::TextureFilterOptions tfo;
//        unsigned int aniso;
//
//        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
//        {
//        case 'B':
//            newVal = "Trilinear";
//            tfo = Ogre::TFO_TRILINEAR;
//            aniso = 1;
//            break;
//        case 'T':
//            newVal = "Anisotropic";
//            tfo = Ogre::TFO_ANISOTROPIC;
//            aniso = 8;
//            break;
//        case 'A':
//            newVal = "None";
//            tfo = Ogre::TFO_NONE;
//            aniso = 1;
//            break;
//        default:
//            newVal = "Bilinear";
//            tfo = Ogre::TFO_BILINEAR;
//            aniso = 1;
//        }
//
//        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
//        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
//        mDetailsPanel->setParamValue(9, newVal);
//    }
//    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
//    {
//        Ogre::String newVal;
//        Ogre::PolygonMode pm;
//
//        switch (engine->gfxMgr->GetCamera()->getPolygonMode())
//        {
//        case Ogre::PM_SOLID:
//            newVal = "Wireframe";
//            pm = Ogre::PM_WIREFRAME;
//            break;
//        case Ogre::PM_WIREFRAME:
//            newVal = "Points";
//            pm = Ogre::PM_POINTS;
//            break;
//        default:
//            newVal = "Solid";
//            pm = Ogre::PM_SOLID;
//        }
//
//        engine->gfxMgr->GetCamera()->setPolygonMode(pm);
//        mDetailsPanel->setParamValue(10, newVal);
//    }
//    else if(arg.key == OIS::KC_F5)   // refresh all textures
//    {
//        Ogre::TextureManager::getSingleton().reloadAll();
//    }
//    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
//    {
//        engine->gfxMgr->GetWindow()->writeContentsToTimestampedFile("screenshot", ".jpg");
//    }
    if (arg.key == OIS::KC_ESCAPE)
    {
        engine->keepRunning = false;
    }
//
//    mCameraMan->injectKeyDown(arg);
    return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent &arg)
{
//    mCameraMan->injectKeyUp(arg);
    return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent &arg)
{
//    if (mTrayMgr->injectMouseMove(arg)) return true;
//    mCameraMan->injectMouseMove(arg);
    return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
//    if (mTrayMgr->injectMouseDown(arg, id)) return true;
//    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
//    if (mTrayMgr->injectMouseUp(arg, id)) return true;
//    mCameraMan->injectMouseUp(arg, id);
    return true;
}

void InputMgr::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

// Unattach OIS before window shutdown (very important under Linux)
void InputMgr::windowClosed(Ogre::RenderWindow* rw)
{
    // Only close for window that created OIS
    if(rw == engine->gfxMgr->GetWindow())
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
