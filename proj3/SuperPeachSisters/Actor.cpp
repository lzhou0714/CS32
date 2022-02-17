#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor
Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, bool isAlive): GraphObject(imageID, startX, startY, startDirection, depth, 1)
{
    m_alive = isAlive;
    
}


//Peach
Peach::Peach(int startX, int startY):
    Actor(IID_PEACH, startX, startY,  0, 0,true)
{
    m_inv= false;
    m_hp  = 1;
    m_starPower = false;
    m_shootPower = false;
    m_jumpPower = false;
}
//void Peach::doSomething()
//{
//}

//Block
//void Block::doSomething()
//{}
