#include "Actor.h"
//#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor
Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, bool isAlive,StudentWorld* word ): GraphObject(imageID, startX, startY, startDirection, depth, 1)
{
    m_alive = isAlive;
    
}

//Peach
Peach::Peach(int startX, int startY,StudentWorld* world ):
    Actor(IID_PEACH, startX, startY,  0, 0, true , world )
{
    m_inv= false;
    m_hp  = 1;
    m_starPower = false;
    m_shootPower = false;
    m_jumpPower = false;
}
void Peach::doSomething()
{
    if (!isAlive())
        return;
//    if (ge)
//        
    
}

//Block
//void Block::doSomething()
//{}
