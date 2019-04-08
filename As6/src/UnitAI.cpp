/*
 * UnitAI.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: Alexander Pasinski
 */

#include <UnitAI.h>

UnitAI::UnitAI(Entity381* ent, AspectType aType)
    : Aspect(ent, aType)
{
    //entity = ent;
}

UnitAI::~UnitAI()
{
    for(std::list<Command*>::iterator iter = commands.begin(); iter != commands.end(); iter++)
    {
        delete (*iter);
    }
        
    commands.clear();
}

void UnitAI::Tick(float dt)
{
    if(commands.size() > 0)
    {        
        if(commands.front()->done())
        {
            delete commands.front();
            commands.pop_front();
        }
        else
        {
            commands.front()->tick(dt);
        }
    }
}

void UnitAI::SetCommand(Command *c)
{
    for(std::list<Command*>::iterator iter = commands.begin(); iter != commands.end(); iter++)
    {
        delete (*iter);
    }
    
    commands.clear();
    
    AddCommand(c);
}

void UnitAI::AddCommand(Command *c)
{
    commands.push_back(c);
}
