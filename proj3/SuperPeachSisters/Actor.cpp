#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor//////////////////////////////

Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, StudentWorld* world ): GraphObject(imageID, startX, startY, startDirection, depth, 1)
{
    m_alive = true;
    m_world = world;
    
}

//Peach//////////////////////////
Peach::Peach(int startX, int startY,StudentWorld* world ):
    Actor(IID_PEACH, startX, startY,  0, 0,world )
{
    m_inv= false;
    m_hp  = 1;
    m_starPower = false;
    m_shootPower = false;
    m_jumpPower = false;
    remaining_jump_distance = 0;
}

void Peach::jumping()
{

    if (!getWorld()->positionBlocked(getX(), getY()+4))
    {
        moveTo(getX(), getY()+4);
        remaining_jump_distance--;
    }
    else
        remaining_jump_distance = 0;
    
}
void Peach::falling()
{
    for (int i  = 0;i<4;i++)
    {
        if (getWorld()->positionBlocked(getX(), getY()-i))
            return;
    }
    moveTo(getX(), getY()-4);
}
void Peach::doSomething()
{
    if (!isAlive())
        return;
    int val;
    if (remaining_jump_distance>0)
        jumping();
    else
        falling();
    if (getWorld()->getKey(val))
    {
        switch(val)
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(180);
                if (!getWorld()->positionBlocked(getX()-4, getY()))
                    moveTo(getX()-4, getY());
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                if (!getWorld()->positionBlocked(getX()+4, getY()))
                    moveTo(getX()+4, getY());
                break;
            }
            case KEY_PRESS_DOWN:
            {
                if (!getWorld()->positionBlocked(getX(), getY()-4))
                    moveTo(getX(), getY()-4);
                break;
            }
            case KEY_PRESS_UP:
            {
                if (remaining_jump_distance !=0)
                    break;
                if (getWorld()->positionBlocked(getX(), getY()-2))
                {
//                    cerr << "jumpsuppoerted" << endl;
                    if (m_jumpPower)
                        remaining_jump_distance = 12;
                    else
                        remaining_jump_distance = 8;
//                        remaining_jump_distance = 16;

                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                }
                break;
            }
        }
        
    }
}

//void Peach::bonk()
//{}

Block::Block(int startX, int startY,StudentWorld* world,int special): Structure(IID_BLOCK, startX, startY, world )
{
    m_star = false;
    m_shroom = false;
    m_flower = false;
    if (special != 0 ) m_powerUps = true;
    switch (special) {
        case 0:
            break;
        case 1:
            m_flower = true;
            break;

        case 2:
            m_star = true;
            break;
        case 3:
            m_shroom = true;
            break;

    }
}
void Block::bonk()
{
    if (m_powerUps)
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        if (m_flower) getWorld()->addActor(new Flowers(getX(),getY()+8,getWorld()));
        if (m_star) getWorld()->addActor(new Stars(getX(),getY()+8,getWorld()));
        if (m_shroom) getWorld()->addActor(new Mushrooms(getX(),getY()+8,getWorld()));
    }
    else
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    m_powerUps = false;
}

void Flag::bonk()
{
    getWorld()->nextLevel();
}

void Mario::bonk()
{
    getWorld()->endgame();
}
