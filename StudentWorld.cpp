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

void randomXY( int &randomX, int &randomY)
{
    randomX = rand()%(VIEW_WIDTH-3);
    randomY = rand()% (VIEW_HEIGHT - 7);
    while(randomX > 26 && randomX < 34 && randomY > 0)
    {
        randomX = rand()%(VIEW_WIDTH-4);
    }
}

bool moreThanSix(int xPosition, int yPosition, Actor* object2)
{
    double distanceX = (xPosition-object2->getX())*(xPosition-object2->getX());
    double distanceY = (yPosition-object2->getY())*(yPosition-object2->getY());
    double distance = sqrt(distanceX + distanceY);
    if(distance <= 6)
    {
        return false;
    }
    return true;
}

void chooseXY( int &randomX, int &randomY, vector<Actor*> itemVector)
{
    if(itemVector.size()>1)
    {
        int index =0;
        while( index < itemVector.size() )
        {
            while( !moreThanSix(randomX, randomY, itemVector[index]) )
            {
                randomXY(randomX, randomY);
                index = 0;
            }
            index++;
        }
    }
}

void StudentWorld::setXY(string actorType)
{
    int randomX = 0;
    int randomY = 0;
    int counter = 0;
    Actor* actor;
    
    if(actorType == "B")
    {
        counter = min(currentLevel / 2 + 2, 6);
    }
    else if(actorType == "G")
    {
        counter = max(5 - currentLevel / 2, 2);
    }
    else if(actorType == "L")
    {
        counter = min(2 + currentLevel, 20);
    }
    
    for(int i =0; i < counter; i++)
    {
        randomXY(randomX, randomY);
        chooseXY(randomX, randomY, itemVector);
        if(actorType == "B")
        {
            actor = new Boulder( this, randomX , randomY);
        }
        else if(actorType == "G")
        {
            actor = new GoldNugget( this, randomX, randomY, false );
        }
        else if(actorType == "L")
        {
            actor = new OilBarrel( this, randomX, randomY );
        }
        itemVector.push_back(actor);
    }
    
    
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
    
    setXY("B");
    setXY("G");
    setXY("L");
    
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
    //int G = max(5 - currentLevel / 2, 2);
    //int L = min(2 + currentLevel, 20);
    
    for( int i = 0; i < B; i++)
    {
        if( itemVector[i]->isAlive() == true )
        {
            itemVector[i]->move();
        }
    }
    
    for( int i = 0; i < itemVector.size(); i++ )
    {
        if(!(itemVector[i]->isAlive()))
        {
            itemVector.erase(itemVector.begin()+i);
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
}

void StudentWorld::addActor(Actor* a)
{
    
}

void StudentWorld::clearDirt(int startX, int startY, bool sound)
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
                if(sound)
                {
                    playSound(SOUND_DIG);
                }
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
    
    for(int i = 0; i < itemVector.size(); i++)
    {
        if(posY-4 == itemVector[i]->getY() && posX-3<=itemVector[i]->getX() && posX+3>=itemVector[i]->getX() && itemVector[i]->canActorsPassThroughMe() == false)
        {
            canActorMove = false;
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