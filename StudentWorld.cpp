#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;
using std::vector;

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
    int currentLevel = getLevel();
    int B = min(currentLevel / 2 + 2, 6);
    int G = max(5 - currentLevel / 2, 2);
    int L = min(2 + currentLevel, 20);
    
    for( int i = 0; i < B; i++ )
    {
        int randomX = rand()%(VIEW_WIDTH-4);
        int randomY = rand()% (VIEW_HEIGHT - 8);
        Actor* newBoulder = new Boulder( this, randomX ,randomY );
        itemVector.push_back(newBoulder);
    }
    for( int i = 0; i < G; i++ )
    {
        int randomX = rand()%(VIEW_WIDTH-4);
        int randomY = rand()% (VIEW_HEIGHT - 8);
        Actor* newNugget = new GoldNugget( this, randomX, randomY, false );
        itemVector.push_back(newNugget);
    }
    for( int i = 0; i < L; i++ )
    {
        int randomX = rand()%(VIEW_WIDTH-4);
        int randomY = rand()% (VIEW_HEIGHT - 8);
        Actor* newBarrel = new OilBarrel( this, randomX, randomY );
        itemVector.push_back(newBarrel);
    }
    
    //boulderPointer = new Boulder( this, 20,10 );
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
    
    int B = min(currentLevel / 2 + 2, 6);
    int G = max(5 - currentLevel / 2, 2);
    int L = min(2 + currentLevel, 20);
    
    for( int i = 0; i < B; i++)
    {
        if( itemVector[i]->isAlive() == true )
        {
            itemVector[i]->move();
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(int i = 0; i< VIEW_WIDTH; i++)
        for(int j = 0; j<VIEW_HEIGHT-4; j++)
            delete dirtArray[i][j];
    delete fmPointer;
    delete boulderPointer;
}

void StudentWorld::addActor(Actor* a)
{
    
}

void StudentWorld::removeDirt(int startX, int startY)
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
    //SINGLE STL
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
                playSound(SOUND_DIG);
            }
        }
    }
}

bool StudentWorld::canActorMoveTo(Actor* a, int posX, int posY) const
{
    bool canActorMove = true;
    
    for(int i = posX; i<= posX+3; i++)
    {
            if(dirtArray[i][posY-1]!=nullptr)
            {
                canActorMove = false;
                break;
            }
    }
    if(posY <= 0 || posY >= 59 || posX <= 0 || posX >= 63)
    {
        canActorMove = false;
    }

    return canActorMove;
}

int StudentWorld::annoyAllNearbyActors(Actor* annoyer, int points, int radius)
{
    return 0;
}

void StudentWorld::revealAllNearbyObjects(int x, int y, int radius)
{
    
}

Actor* StudentWorld::findNearbyFrackMan(Actor* a, int radius) const
{
    return a;
}

void StudentWorld::annoyFrackMan()
{
    
}

void StudentWorld::giveFrackManSonar()
{
    
}

void StudentWorld::giveFrackManWater()
{
    
}

bool StudentWorld::facingTowardFrackMan(Actor* a) const
{
    return true;
}

//GraphObject::Direction StudentWorld::lineOfSightToFrackMan(Actor* a) const
//{
//
//}

bool StudentWorld::isNearFrackMan(Actor* a, int radius) const
{
    return true;
}

//GraphObject::Direction StudentWorld::determineFirstMoveToExit(int x, int y)
//{
//
//}

//GraphObject::Direction StudentWorld::determineFirstMoveToFrackMan(int x, int y)
//{
//
//}

StudentWorld::~StudentWorld()
{
    for(int i = 0; i<VIEW_WIDTH; i++)
        for(int j = 0; j<VIEW_HEIGHT-4; j++)
            delete dirtArray[i][j];
    delete fmPointer;
}