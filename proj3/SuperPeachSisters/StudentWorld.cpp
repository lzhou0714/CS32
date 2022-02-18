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
}

int StudentWorld::init()
{
//    m_player = new Peach()
    
//    cerr << "asset path " << assetPath() << endl;
//    cerr << "levels " << getLevel() << endl;
    
    //load items
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
    
    {
//        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        for (int i  = 0;i<VIEW_WIDTH;i++)
            for (int j = 0; j<VIEW_HEIGHT;j++)
        {
            ge = lev.getContentsOf(i,j); // x=5, y=10
            switch (ge)
            {
                case Level::empty:
                cout << "Location 5,10 is empty" << endl;
                break;
    //            case Level::koopa:
    //            cout << "Location 5,10 starts with a koopa" << endl;
    //            break;
    //            case Level::goomba:
    //            cout << "Location 5,10 starts with a goomba” << endl;
    //            break;
                case Level::peach:
                    m_player = new Peach(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this);
                    break;
    //            case Level::flag:
    //            cout << "Location 5,10 is where a flag is" << endl;
    //            break;
                case Level::block:
                    m_gameActors.push_back(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                    break;
    //            case Level::star_goodie_block:
    //            cout << "Location 5,10 has a star goodie block” << endl;
    //            break;
                    
            }
        }
    }
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_player;
}
