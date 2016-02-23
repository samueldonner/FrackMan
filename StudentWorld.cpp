#include "StudentWorld.h"
#include <string>
#include <iostream>
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
    fmPointer = new FrackMan(30, 60);
    boulderPointer = new Boulder( 20,50 );
    for(int i = 0; i<VIEW_WIDTH; i++)
        for(int j = 0; j<VIEW_HEIGHT-4; j++)
        {
            dirtArray[i][j] = new Dirt(i, j);
            if(!(i < 30 || i > 33 || j<4)) //shaft created between x values 30-33 and less than 4
            {
                delete dirtArray[i][j];
                dirtArray[i][j] = nullptr;
            }
            
        }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    int pressKey;
    int frackManY = fmPointer->getY();
    int frackManX = fmPointer->getX();
    int boulderY = boulderPointer->getY();
    int boulderX = boulderPointer->getX();
    getKey(pressKey);
    fmPointer->keyEvent(pressKey);
    fmPointer->doSomething();
    if(noDirt(boulderX,boulderY))
    {
        boulderPointer->doSomething();
    }
    removeDirt(frackManX, frackManY, frackManX+3, frackManY+3);
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::removeDirt(int startX, int startY, int endX, int endY)
{
    if(endY>= 59)
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

bool StudentWorld::noDirt(int posX, int posY)
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