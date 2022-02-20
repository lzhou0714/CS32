#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor//////////////////////////////

Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, bool isAlive,StudentWorld* world ): GraphObject(imageID, startX, startY, startDirection, depth, 1)
{
    m_alive = isAlive;
    m_world = world;
    
}

//Peach//////////////////////////
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
    int val;
    if (getWorld()->getKey(val))
    {
        switch(val)
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(180);
                if (!getWorld()->positionBlocked(getX()-4, getY() ,this))
                    moveTo(getX()-4, getY());
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                if (!getWorld()->positionBlocked(getX()+4, getY(), this))
                    moveTo(getX()+4, getY());
                break;
            }
            case KEY_PRESS_DOWN:
            {
                if (!getWorld()->positionBlocked(getX(), getY()-4, this))
                    moveTo(getX(), getY()-4);
                break;
            }
            case KEY_PRESS_UP:
            {
                if (!getWorld()->positionBlocked(getX(), getY()+4, this))
                    moveTo(getX(), getY()+4);
                break;
            }
        }
        
    }
}
