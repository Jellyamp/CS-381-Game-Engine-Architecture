#ifndef __Aspect_h_
#define __Aspect_h_

#include <OgreVector3.h>

class Entity381;    //Forward declaration of the Entity381 class

class Aspect
{
public:
  Aspect(Entity381* ent);
  virtual ~Aspect();

  Entity381* entity;

  virtual void Tick(float dt);


protected:

};

class Physics : Aspect
{
public:
	Physics(Entity381 *ent);
	~Physics();

	void Tick(float dt);
};


class Renderable : Aspect
{
public:
	Renderable(Entity381* ent);
	~Renderable();

	void Tick(float dt);
};



#endif // #ifndef __Aspect_h_
