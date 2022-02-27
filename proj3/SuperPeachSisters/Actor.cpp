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
    time_to_recharge = 0;

}

void Peach::jumping()
{

     Actor* blocker;
    if (!getWorld()->positionBlocked(getX(), getY()+4,blocker))
    {
        moveTo(getX(), getY()+4);
        remaining_jump_distance--;
    }
    else
    {
        if (blocker->isStructure())
            blocker->bonk();
        remaining_jump_distance = 0;
    }
    
}
void Peach::falling()
{
    Actor* blocker;
    for (int i  = 0;i<4;i++)
    {
        if (getWorld()->positionBlocked(getX(), getY()-i,blocker))
            return;
    }
    moveTo(getX(), getY()-4);
}
void Peach::doSomething()
{
    if (!isAlive())
        return;
    
    if (isInvincible())
    {
        remaining_invincibility--;
        if (remaining_invincibility ==0)
            m_starPower = false;
    }
    if (isTempInvincible())
        temp_invincibility--;
    
    Actor* blocker  = nullptr;
    //sus////////////////////////
    if (getWorld()->positionBlocked(getX(), getY(), blocker))
    {
        blocker->bonk();
    }
    ///////////////////////////////////////////
    if (remaining_jump_distance>0)
        jumping();
    else
        falling();
    
    if (time_to_recharge>0)
        time_to_recharge--;
    int val;
    if (getWorld()->getKey(val))
    {
         Actor* blocker = nullptr;
        switch(val)
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(180);
                if (!getWorld()->positionBlocked(getX()-4, getY(), blocker))
                {
                    moveTo(getX()-4, getY());
                }
                else
                {
                    if (blocker->isStructure())
                        blocker->bonk();
                }
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                if (!getWorld()->positionBlocked(getX()+4, getY(), blocker))
                {
                    moveTo(getX()+4, getY());
                }
                else
                {
                    if (blocker->isStructure())
                        blocker->bonk();
                }
                break;
            }
            case KEY_PRESS_UP:
            {
                if (remaining_jump_distance !=0)
                    break;
                if (getWorld()->positionBlocked(getX(), getY()-2, blocker))
                {
//                    cerr << "jumpsuppoerted" << endl;
                    if (m_jumpPower)
                        remaining_jump_distance = 12;
                    else
                        remaining_jump_distance = 8;
//                        remaining_jump_distance = 80;
                    cerr << "playing jump sound" << endl;
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                }
                break;
            }
            case KEY_PRESS_SPACE:
            {
                if (hasShootPower() && time_to_recharge==0)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    int x;
                    if (getDirection() == 0)
                        x= getX()+4;
                    else
                        x = getX()-4;
                    getWorld()->addActor(new PeachFireBalls(x,getY(),getDirection(),getWorld()));
                    time_to_recharge = 8;
                }
                
                break;
            }
        }
        
    }
}

void Peach::bonk()
{
    if (isInvincible())
        return;
    m_hp--;
    temp_invincibility = 10;
    m_shootPower = false;
    m_jumpPower = false;
    if (m_hp>0)
    {
        cerr << "m_hp: " << m_hp << endl;
        getWorld()->playSound(SOUND_PLAYER_HURT);
    }
    else
    {
        setAlive(false);
    }
}

//Block////////////////////////
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
        cerr << "playing powerup sound" << endl;

        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        if (m_flower) getWorld()->addActor(new Flowers(getX(),getY()+8,getWorld()));
        if (m_star) getWorld()->addActor(new Stars(getX(),getY()+8,getWorld()));
        if (m_shroom) getWorld()->addActor(new Mushrooms(getX(),getY()+8,getWorld()));
    }
    else
    {
        cerr << "block bonked" << endl;
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    m_powerUps = false;
}

//Target/////////////////
void Target::doSomething()
{
    if (!isAlive())
        return;
    Actor* bonker = nullptr;
    if (getWorld()->overlapsPeach(getX(), getY(),bonker))
    {
        getWorld()->increaseScore(1000);
        setAlive(false);
        doSomethingAux();
    }

}
void Flag::doSomethingAux()
{
    getWorld()->nextLevel();

}
void Mario::doSomethingAux()
{
    getWorld()->increaseScore(1000);
    getWorld()->endgame();
}

 
//powerups///////////////////////////////
void PowerUps::doSomething()
{
    Actor* bonker = nullptr;
    if (getWorld()->overlapsPeach(getX(), getY(),bonker))
    {
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        doSomethingAux();
        setAlive(false);
        return; //returns if overlaps peach
    }
    Actor* blocker1 = nullptr;
    Actor* blocker2 = nullptr;
    if (!getWorld()->positionBlocked(getX(), getY()-2, blocker1))
        moveTo(getX(), getY()-2);
    if (getDirection() == 0)
    {
        if (!getWorld()->positionBlocked(getX()+2, getY(), blocker2) || (blocker2 !=nullptr && !blocker2->isStructure()))
            moveTo(getX()+2, getY());
        else if (blocker2->isStructure())
        {
            setDirection(180);
            return;
        }
    }
    else
    {
        if (!getWorld()->positionBlocked(getX()-2, getY(), blocker2)|| (blocker2 !=nullptr && !blocker2->isStructure()))
            moveTo(getX()-2, getY());
        else if (blocker2->isStructure())
        {
            setDirection(0);
            return;
        }
    }
    
    
}
void Mushrooms::doSomethingAux()
{
    getWorld()->increaseScore(75);
    getWorld()->grantJumpPower();
    getWorld()->setPeachHP(2);
}


void Stars::doSomethingAux()
{
    getWorld()->increaseScore(100);
    getWorld()->grantInvincibility(150);
}

void Flowers::doSomethingAux()
{
    getWorld()->increaseScore(50);
    getWorld()->grantShootPower();
    getWorld()->setPeachHP(2);
}

void Projectiles::doSomething()
{
    if (!isAlive())
        return;
    Actor* blocker1 = nullptr;
    Actor* blocker2 = nullptr;

    
    if (!getWorld()->positionBlocked(getX(), getY(), blocker1) && blocker1!=nullptr)
        doSomethingAux(blocker1);
    if (!getWorld()->positionBlocked(getX(), getY()-2, blocker1))
        moveTo(getX(), getY()-2);
//    if (blocker1!=nullptr && blocker1->isStructure())
    if (getDirection() == 0)
    {
        if (!getWorld()->positionBlocked(getX()+2, getY(), blocker2) || (blocker2 !=nullptr && !blocker2->isStructure() && !blocker2->isEnemy()))
            moveTo(getX()+2, getY());
    }
    else
    {
        if (!getWorld()->positionBlocked(getX()-2, getY(), blocker2)|| (blocker2 !=nullptr && !blocker2->isStructure() && !blocker2->isEnemy()))
            moveTo(getX()-2, getY());
    }
    if (blocker2 !=nullptr && blocker2 !=this)
    {
        if (blocker2->isStructure())
        {
            setAlive(false);
            return;
        }
        doSomethingAux(blocker2);


    }

//    check if the object that blocks the object is enemy

}
void Projectiles::doSomethingAux(Actor* blocker)
{
    if (blocker->isEnemy())
    {
        setAlive(false);
        blocker->takeDamage();
    }
}

void PiranhasFireBalls::doSomethingAux(Actor* peach)
{
    if (getWorld()->overlapsPeach(getX(), getY(), peach))
    {
        peach->bonk();
    }
}

//Enemies///////////////////
void Enemies::doSomething()
{
    if (!isAlive())
        return;
    Actor* bonker = nullptr;
    if (getWorld()->overlapsPeach(getX(), getY(),bonker))
    {
        Peach* peach = getWorld()->getPeach();
        if (peach->isInvincible())
        {
            setAlive(false);
            return;
        }
        if (!peach->isTempInvincible())
        {
        peach->bonk();
        return;
        }
    }
    Actor* blocker1;
    Actor* blocker2;
    if (getDirection() == 0)
    {
        bool blocked = getWorld()->positionBlocked(getX()+1, getY(), blocker2);
        if (!getWorld()->positionBlocked(getX()+1+SPRITE_WIDTH, getY()-2, blocker1) || (blocker2 !=nullptr && blocker2->isStructure()))
        {
            setDirection(180);
            return;
        }
        else if (!blocked || (blocker2 !=nullptr && !blocker2->isStructure()))
        {
            moveTo(getX()+1, getY());
        }
    }
    else
    {
        bool blocked = getWorld()->positionBlocked(getX()-1, getY(), blocker2);

        if (!getWorld()->positionBlocked(getX()-1-SPRITE_WIDTH, getY()-2, blocker1) || (blocker2 !=nullptr && blocker2->isStructure()))
        {
            setDirection(0);
            return;
        }
        else if (!blocked|| (blocker2 !=nullptr && !blocker2->isStructure()))
        {

            moveTo(getX()-1, getY());
        }

    }
    

}
void Enemies::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_KICK);
}

void Enemies::takeDamage()
{
    getWorld()->increaseScore(100);
    setAlive(false);
    
}

void Koopas::takeDamage()
{
    getWorld()->increaseScore(100);
    setAlive(false);
    getWorld()->addActor(new Shells(getX(),getY(),getWorld(),getDirection()));
}

void Piranhas::doSomething()
{
    if (!isAlive())
        return;
    increaseAnimationNumber();
    Actor* peach = nullptr;
    if (getWorld()->overlapsPeach(getX(), getY(),peach))
    {
        peach->bonk();
        return;
    }
    if ((getWorld()->getPeach()->getY()) <= getY()+ 1.5*SPRITE_HEIGHT && (getWorld()->getPeach()->getY()) >= getY()-1.5*SPRITE_HEIGHT  )
    {
        if ((getWorld()->getPeach()->getX())<getX())
        {
            setDirection(180);
        }
        else
            setDirection(0);
        if (m_firingDelay>0)
        {
            m_firingDelay--;
            return;
        }
        else if ((getWorld()->getPeach()->getX()) <= getX()+ 8*SPRITE_WIDTH && (getWorld()->getPeach()->getX()) >= getX()-8*SPRITE_WIDTH  )
        {
            getWorld()->addActor(new PiranhasFireBalls(getX(),getY(),getDirection(),getWorld()));
            getWorld()->playSound(SOUND_PLAYER_FIRE);
            m_firingDelay = 40;
        }
        
    }
    else
        return;
    
}
