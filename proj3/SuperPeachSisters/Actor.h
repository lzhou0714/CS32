#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, bool isAlive);
    virtual ~Actor() {};
    virtual void doSomething() = 0;
    
private:
    bool m_alive;
    
};
class Peach: public Actor
{
public:
    Peach(int startX, int startY);
    virtual ~Peach() {};
    virtual void doSomething() {};

private:
    bool m_inv;
    int m_hp;
    bool m_starPower;
    bool m_shootPower;
    bool m_jumpPower;

};

class Block: public Actor
{
public:
    Block(int startX, int startY): Actor(IID_BLOCK, startX, startY,  0, 2, true) {}
    virtual ~Block() {};
    virtual void doSomething() {};
private:

};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#endif // ACTOR_H_
