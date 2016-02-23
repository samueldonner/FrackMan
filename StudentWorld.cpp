#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
:GameWorld(assetDir)
{
    currentLevel = 0;
}

int StudentWorld::init()
{
    fmPointer = new FrackMan(this, 30, 60);
    
    for(int i = 0; i<VIEW_WIDTH; i++)
        for(int j = 0; j<VIEW_HEIGHT-4; j++)
        {
            dirtArray[i][j] = new Dirt(this, i, j);
            if(!(i < 30 || i > 33 || j<4)) //shaft created between x values 30-33 and less than 4
            {
                delete dirtArray[i][j];
                dirtArray[i][j] = nullptr;
            }
            
        }
    boulderPointer = new Boulder( this, 20,50 );
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    int score = 321000;
    int level = 52;
    int lives = 3;
    int health = 80;
    int water = 20;
    int gold = 3;
    int sonar = 1;
    int oilLeft = 2;
    ostringstream gameStats;
    gameStats << "Scr: " << score <<  " Lvl: " << level << " Lives: " << lives
            << " Hlth: " << health << "%" << " Wtr: " << water << " Gld: "
            << gold << " Sonar: " << sonar << " Oil Left: " << oilLeft;
    string s = gameStats.str();
    setGameStatText(s);
    
    fmPointer->move();
    
    boulderPointer->move();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::clearDirt(int startX, int startY)
{
    int endY = startY+3;
    int endX = startX+3;
    if(endY>=59)
         endY = 59;
    if(endX>= 63)
        endX = 63;
    for(int i = startX; i<= endX; i++)
    {
        for(int j = startY; j<= endY; j++)
        {
            if(dirtArray[i][j]!=nullptr)
            {
                delete dirtArray[i][j];
                dirtArray[i][j]=nullptr;
            }
        }
    }
}

bool StudentWorld::canActorMoveTo(Actor* a, int posX, int posY) const
{
    bool theresNoDirt = true;
    
    for(int i = posX; i<= posX+3; i++)
    {
            if(dirtArray[i][posY]!=nullptr)
            {
                theresNoDirt = false;
                break;
            }
    }
    return theresNoDirt;
}

StudentWorld::~StudentWorld()
{
    for(int i = 0; i<VIEW_WIDTH; i++)
        for(int j = 0; j<VIEW_HEIGHT-4; j++)
            delete dirtArray[i][j];
    delete fmPointer;
}

void StudentWorld::cleanUp()
{
    for(int i = 0; i< VIEW_WIDTH; i++)
        for(int j = 0; j<VIEW_HEIGHT-4; j++)
            delete dirtArray[i][j];
    delete fmPointer;
}