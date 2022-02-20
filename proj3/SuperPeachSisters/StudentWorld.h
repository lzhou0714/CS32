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
    bool positionBlocked(int x,int y, Actor* object);

private:
    list<Actor*> m_gameActors;
    list<Actor*> :: iterator it;
    Peach* m_player;
    void placeObjects(Level lev);
    
    
};

#endif // STUDENTWORLD_H_
