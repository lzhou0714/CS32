#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>
#include "Actor.h"

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld() { cleanUp(); }
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    bool checkOverlap(int x,int y,Actor* a) const;
    bool overlapsPeach(int x,int y, Actor*& actor) const;
    bool positionBlocked(int x, int y,  Actor*& blocker);
    void addActor(Actor* actor);
    void endgame(){m_gameComplete = true;}
    void nextLevel() {m_levelComplete = true;}
    void grantInvincibility(int ticks);

      // Grant Peach Shoot Power.
    void grantShootPower();
      // Grant Peach Jump Power.
    void grantJumpPower();
    void setPeachHP(int hp) const {m_player->setHP(hp);}




private:
    list<Actor*> m_gameActors;
    list<Actor*> :: iterator it;
    Peach* m_player;
    void placeObjects(Level lev);
    bool m_gameComplete;
    bool m_levelComplete;
    string m_StatusText;
//    string m_powerUpsStatusText;
//    int m_targetX;
//    int m_targetY;
    
};



#endif // STUDENTWORLD_H_
