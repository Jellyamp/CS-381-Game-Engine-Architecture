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
    
private:
    void MakeEnts();
    void MakeGround();
    void MakeSky();
    void MakeFog();
    
    Ogre::SceneNode* mCameraNode;
};


#endif /* INC_GAMEMGR_H_ */
