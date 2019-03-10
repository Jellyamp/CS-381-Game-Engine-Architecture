#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <iterator>

class Entity381;

#include "Mgr.h"
#include "Engine.h"
#include "GfxMgr.h"
#include "GameMgr.h"
#include "InputMgr.h"
#include "Entity381.h"
#include "Types381.h"

class EntityMgr : public Mgr
{
public:
    EntityMgr(Engine *engine);
    virtual ~EntityMgr();

    void Init();
    void LoadLevel();
    void Tick(float dt);
    void Stop();

    std::vector<Entity381*> entities;
    Entity381* selectedEntity;
    int selectedEntityIndex;

    void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);
    void SelectNextEntity();

protected:

private:
    void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
    void CreateDDG51(Ogre::Vector3 pos);
    void CreateCarrier(Ogre::Vector3 pos);
    void CreateSpeedBoat(Ogre::Vector3 pos);
    void CreateFrigate(Ogre::Vector3 pos);
    void CreateAlien(Ogre::Vector3 pos);
    int count;
};

#endif // #ifndef __EntityMgr_h_
