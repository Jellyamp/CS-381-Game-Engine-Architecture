/*
 * GameMgr.h
 *
 *  Created on: Mar 9, 2019
 *      Author: Alexander Pasinski
 */

#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_

#include "Mgr.h"
#include "Engine.h"
#include "GfxMgr.h"
#include "EntityMgr.h"
#include "InputMgr.h"

class GameMgr : public Mgr
{
public:
    GameMgr(Engine *engine);
    virtual ~GameMgr();

    void Init();
    void LoadLevel();
    void Tick(float dt);
    void Stop();
    
    Ogre::SceneNode* GetCameraNode();
    float GetDeltaDesiredSpeed();
    float GetDeltaDesiredHeading();
    
private:
    void DestroyScene();
    void MakeEnts();
    void MakeLight(Ogre::Vector3 pos, Ogre::String name);
    void MakeCamera(Ogre::Vector3 pos);
    void MakeGround();
    void MakeSky(Ogre::String skyBoxName);
    void MakeFog();
    
    Ogre::SceneNode* mCameraNode;
    float mDeltaDesiredSpeed; // user changes desired speed by this much
    float mDeltaDesiredHeading; //user changes desired heading by this much
};


#endif /* INC_GAMEMGR_H_ */
