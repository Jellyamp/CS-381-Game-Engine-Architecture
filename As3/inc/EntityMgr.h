#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>

#include "Entity381.h"
#include "Types381.h"

class EntityMgr
{
public:
  EntityMgr(Ogre::SceneManager* sm);
  virtual ~EntityMgr();

  std::vector<Entity381*> entities;
  Entity381* selectedEntity;
  int selectedEntityIndex;
  Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);
  void SelectNextEntity();

  void Tick(float dt);

protected:

private:
  void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
  void CreateCube(Ogre::Vector3 pos);
  void CreateSphere(Ogre::Vector3 pos);
  int count;

};

#endif // #ifndef __EntityMgr_h_
