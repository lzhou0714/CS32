#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
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
    m_gameComplete = false;
    m_levelComplete = false;
}

int StudentWorld::init()
{
    
    m_gameComplete = false;
    m_levelComplete = false;
    
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
                m_gameActors.push_back(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this,0));
                break;
            case Level::pipe:
                m_gameActors.push_back(new Pipe(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                break;
            case Level::flag:
                m_gameActors.push_back(new Flag(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
//                m_targetX = i*SPRITE_WIDTH;
//                m_targetY = j*SPRITE_HEIGHT;
                break;
            case Level::mario:
                m_gameActors.push_back(new Mario(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
//                m_targetX = i*SPRITE_WIDTH;
//                m_targetY = j*SPRITE_HEIGHT;
                break;
            case Level::flower_goodie_block:
                m_gameActors.push_back(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this,1));

                break;
            case Level::star_goodie_block:                m_gameActors.push_back(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this,2));

                break;
            case Level::mushroom_goodie_block:
                m_gameActors.push_back(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this,3));

                break;
            case Level::goomba:
                m_gameActors.push_back(new Goombas(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this, 180*(rand()%2)));

                break;
            case Level::koopa:
                m_gameActors.push_back(new Koopas(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this, 180*(rand()%2)));
            
                break;
            case Level::piranha:
                m_gameActors.push_back(new Piranhas(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this, 180*(rand()%2)));
                break;
        }
    }
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    m_player->doSomething();
    for (auto const& actor: m_gameActors)
    {
        if (actor->isAlive())
        {
            actor->doSomething();
            if (!m_player->isAlive())
            {
                playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
            }
            //need something here to check for overlap with targts
            if (m_gameComplete)
            {
                cerr << "reached mario" <<  endl;
                playSound(SOUND_GAME_OVER);
                return GWSTATUS_PLAYER_WON;
            }
            if (m_levelComplete)
            {
                cerr << "reached flag" << endl;
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
            
                

        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    m_gameComplete = false;
    m_levelComplete = false;

    delete m_player;
    for (auto const& actor :  m_gameActors)
        delete actor;
    m_gameActors.clear();
}

bool StudentWorld::positionBlocked(int x, int y)
{
    
    for(auto const& actor : m_gameActors)
    {
        if (x < actor->getX()+SPRITE_WIDTH-1 && x+SPRITE_WIDTH-1 > actor->getX())
        {
            if (y < actor->getY()+SPRITE_WIDTH-1 && y+SPRITE_WIDTH-1 > actor->getY())
            {
                actor->bonk();

                if (actor->isStructure())
                {
                    return true;
                }
            }
        }
    }
    return false;
    
    //        if (actor->isStructure())
    //        {
    //            if (actor->getX() <= x+SPRITE_WIDTH-1 && actor->getX() >= x && actor->getY() <= y+SPRITE_HEIGHT-1 && actor->getY() >= y)
    //                return true;
    //            if (actor->getX()+SPRITE_WIDTH-1 <=x+SPRITE_WIDTH-1 && actor->getX()+SPRITE_WIDTH-1 >= x && actor->getY() <= y+SPRITE_HEIGHT-1 && actor->getY() >= y)
    //                return true;
    //            if (actor->getX()+SPRITE_WIDTH-1 <= x+SPRITE_WIDTH-1 && actor->getX() + SPRITE_WIDTH-1 >= x && actor->getY()+SPRITE_HEIGHT-1 <= y+SPRITE_HEIGHT-1 && actor->getY()+SPRITE_HEIGHT-1 >= y)
    //                return true;
    //            if (actor->getX() <= x+SPRITE_WIDTH-1 && actor->getX()>= x && actor->getY()+SPRITE_HEIGHT-1 <= y+SPRITE_HEIGHT-1 && actor->getY()+SPRITE_HEIGHT-1 >= y)
    //                return true;
    //        }
    
}

void StudentWorld::addActor(Actor* actor)
{
    m_gameActors.push_back(actor);
}
