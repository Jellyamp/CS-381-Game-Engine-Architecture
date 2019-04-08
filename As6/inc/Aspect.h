#ifndef __Aspect_h_
#define __Aspect_h_

#include<OgreVector3.h>
#include <iterator>

enum AspectType
{
    RENDERABLE,
    PHYSICS_2D,
    PHYSICS_3D,
    UNIT_AI,
};

class Entity381;    //Forward declaration of the Entity381 class

class Aspect
{
public:
  Aspect(Entity381* ent, AspectType aType);
  virtual ~Aspect();

  Entity381* entity;
  AspectType aspectType;

  virtual void Tick(float dt);


protected:

};



class Renderable : Aspect
{
public:
	Renderable(Entity381* ent, AspectType aspectType);
	~Renderable();

	void Tick(float dt);
};



#endif // #ifndef __Aspect_h_
