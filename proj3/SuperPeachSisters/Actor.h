#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//#include "StudentWorld.h"
class StudentWorld;
class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, bool isAlive, StudentWorld* world );
    virtual ~Actor() {};
    virtual void doSomething() = 0;
    bool isAlive() {return m_alive;}
    StudentWorld* getWorld() const {return m_world;}
    
private:
    bool m_alive;
    StudentWorld *m_world;
    
};
class Peach: public Actor
{
public:
    Peach(int startX, int startY, StudentWorld* world  );
    virtual ~Peach() {};
    virtual void doSomething();

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
    Block(int startX, int startY,StudentWorld* world ): Actor(IID_BLOCK, startX, startY,  0, 2, true, world ) {}
    virtual ~Block() {};
    virtual void doSomething() {};
private:

};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#endif // ACTOR_H_
