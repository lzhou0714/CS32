#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Level.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    it = m_gameActors.begin();
    m_player = nullptr;
}

int StudentWorld::init()
{
    Level lev(assetPath());
    int currLvl  = getLevel();
    ostringstream fileTitle;
    fileTitle << "level";
    fileTitle.fill('0');
    fileTitle << setw(2) << currLvl << ".txt";
    string level_file = fileTitle.str();
    cerr <<  "levels " << level_file << endl;
    
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success)
        placeObjects(lev);
    

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::placeObjects(Level lev)
{

    Level::GridEntry ge;
    for (int i  = 0;i<VIEW_WIDTH;i++)
        for (int j = 0; j<VIEW_HEIGHT;j++)
    {
        ge = lev.getContentsOf(i,j); // x=5, y=10
        switch (ge)
        {
            case Level::empty:
//            cout << "Location 5,10 is empty" << endl;
                break;
            case Level::peach:
                m_player = new Peach(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this);
                break;
            case Level::block:
                m_gameActors.push_back(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                break;
                
        }
    }
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    m_player->doSomething();
    for (auto const& actors: m_gameActors)
    {
        actors->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_player;
    for (auto const& actor :  m_gameActors)
        delete actor;
}

bool StudentWorld::positionBlocked(int x, int y, Actor* object )
{
    int x11 = x;
    int x12 = x  + SPRITE_WIDTH-1;
    int y11 = y;
    int y12 = y+ SPRITE_HEIGHT-1;
    
    for(auto const& actor : m_gameActors)
    {
        
        int x21 = actor->getX();
        int x22 = actor->getX()  + SPRITE_WIDTH-1;
        int y21 = actor->getY();
        int y22 = actor->getY()+ SPRITE_HEIGHT-1;
        
        if (actor->isStructure())
        {
            if (x21 <= x12 && x21 >= x11 && y21 <= y12 && y21 >= y11)
                return true;
            if (x22 <=x12 && x22 >= x11 && y21 <= y12 && y21 >= y11)
                return true;
            if (x22 <= x12 && x22 >= x11 && y22 <= y12 && y22 >= y11)
                return true;
            if (x21 <= x12 && x21 >= x11 && y22 <= y12 && y22 >= y11)
                return true;
        }
    }
    return false;
    
}
