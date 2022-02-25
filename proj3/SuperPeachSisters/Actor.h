#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//#include "StudentWorld.h"
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, StudentWorld* world );
    virtual ~Actor() {}
    virtual void doSomething() = 0;
    bool isAlive() {return m_alive;}
    virtual bool isStructure(){return false;}//things that are structures can't overlap
    StudentWorld* getWorld() const {return m_world;}
  
private:
    bool m_alive;
    StudentWorld *m_world;
    
};

//Peach///////////////////////
class Peach: public Actor
{
public:
    Peach(int startX, int startY, StudentWorld* world  );
    virtual ~Peach() {}
    virtual void doSomething();
    

private:
    bool m_inv;
    int m_hp;
    bool m_starPower;
    bool m_shootPower;
    bool m_jumpPower;
    int remaining_jump_distance;
    
    void jumping();
    void falling();

};
class Structure: public Actor
{
public:
    Structure(int imageID, int startX, int startY,StudentWorld* world): Actor(imageID, startX, startY,  0, 2, world){}
    virtual ~Structure() {};
    virtual void doSomething() {};
    virtual bool isStructure(){return true;}
};


//Block///////////////////////////////////////
class Block: public Structure
{
public:
    Block(int startX, int startY,StudentWorld* world,int special);
    virtual ~Block() {}
    
private:
//    bool m_powerUps;
    bool m_star;
    bool m_shroom;
    bool m_flower;

};

//Pipe//////////////////////////////////
class Pipe: public Structure
{
public:
    Pipe(int startX, int startY,StudentWorld* world ): Structure(IID_PIPE, startX, startY, world ) {}
    virtual ~Pipe() {};
    virtual void doSomething() {};
private:

};

//Target///////////
class Target: public Actor
{
public:
    Target(int imageID, int startX, int startY,StudentWorld* world): Actor(imageID, startX, startY,  0, 1, world){}
    virtual ~Target() {};
    virtual void doSomething() {};

};
class Flag: public Target
{
public:
    Flag(int startX, int startY, StudentWorld* world ): Target( IID_FLAG, startX, startY,world){}
    virtual ~Flag() {};
    virtual void doSomething() {};

};
class Mario: public Target
{
public:
    Mario(int startX, int startY, StudentWorld* world ): Target(IID_MARIO, startX, startY,world){}
    virtual ~Mario() {};
    virtual void doSomething() {};
    
};

//powerUps/////////////////
class PowerUps: public Actor
{
public:
    PowerUps(int imageID, int startX, int startY,StudentWorld* world): Actor(imageID, startX, startY,  0, 1, world){}
    virtual ~PowerUps() {};
    virtual void doSomething() {};

};
class Flowers: public PowerUps
{
public:
    Flowers(int startX, int startY, StudentWorld* world ): PowerUps(IID_FLOWER, startX, startY,world){}

    virtual ~Flowers() {};
    virtual void doSomething() {};
};
class Mushrooms: public PowerUps
{
public:
    Mushrooms(int startX, int startY, StudentWorld* world ): PowerUps(IID_MUSHROOM, startX, startY,world){}

    virtual ~Mushrooms() {};
    virtual void doSomething() {};
};
class Stars: public PowerUps
{
public:
    Stars(int startX, int startY, StudentWorld* world ): PowerUps(IID_STAR, startX, startY,world){}
    virtual ~Stars() {};
    virtual void doSomething() {};

};
//Projectiles///////////
class Projectiles: public Actor
{
public:
    Projectiles(int imageID, int startX, int startY,StudentWorld* world, int dir): Actor(imageID, startX, startY,  dir, 1, world){}
    virtual ~Projectiles() {};
    virtual void doSomething() {};
};
class PeachFireBalls: public Projectiles
{
public:
    PeachFireBalls(int startX, int startY, int dir, StudentWorld* world): Projectiles(IID_PEACH_FIRE, startX, startY,world,dir){}
    virtual ~PeachFireBalls() {};
    virtual void doSomething() {};

};
class PiranhasFireBalls: public Projectiles
{
public:
    PiranhasFireBalls(int startX, int startY, int dir, StudentWorld* world): Projectiles(IID_PIRANHA_FIRE, startX, startY,world,dir){}
    virtual ~PiranhasFireBalls() {};
    virtual void doSomething() {};

};
class Shells: public Projectiles
{
public:
    Shells(int startX, int startY, StudentWorld* world,int dir): Projectiles(IID_SHELL, startX, startY,world,dir){}
    virtual ~Shells() {};
    virtual void doSomething() {};
};

//enemies////////////
class Enemies: public Actor
{
public:
    Enemies(int imageID, int startX, int startY,StudentWorld* world, int dir): Actor(imageID, startX, startY,  dir, 1, world){}
    //direction randomly chosen to be either 0 or 180
    virtual ~Enemies() {};
    virtual void doSomething() {};
};
class Goombas: public Enemies
{
public:
    Goombas(int startX, int startY,StudentWorld* world, int dir): Enemies(IID_GOOMBA, startX,startY,world,dir){}
    virtual ~Goombas() {};
    virtual void doSomething() {};

};
class Koopas: public Enemies
{
public:
    Koopas(int startX, int startY,StudentWorld* world, int dir): Enemies(IID_KOOPA, startX,startY,world,dir){}
    virtual ~Koopas() {};
    virtual void doSomething() {};

};
class Piranhas: public Enemies
{
public:
    Piranhas(int startX, int startY,StudentWorld* world, int dir): Enemies(IID_PIRANHA, startX,startY,world,dir){}
    virtual ~Piranhas() {};
    virtual void doSomething() {};
};



// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#endif // ACTOR_H_
