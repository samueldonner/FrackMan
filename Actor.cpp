#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//================Actor===================//================Actor===================
//================Actor===================//================Actor===================
//================Actor===================//================Actor===================
//================Actor===================//================Actor===================
//================Actor===================//================Actor===================

Actor::Actor(StudentWorld* world, int startX, int startY, Direction startDir,
             bool visible, int imageID, double size, int depth):GraphObject(imageID, startX, startY, startDir, size, depth)
{
    setVisible(true);
    m_isAlive = true;
    m_studentWorld = world;
}

bool Actor::isAlive() const
{
    return m_isAlive;
}

void Actor::setDead()
{
    m_isAlive = false;
}

bool Actor::annoy(unsigned int amt)
{
    return true;
}

StudentWorld* Actor::getWorld() const
{
    return m_studentWorld;
}

bool Actor::canActorsPassThroughMe() const
{
    return true;
}

bool Actor::canDigThroughDirt() const
{
    return true;
}

bool Actor::canPickThingsUp() const
{
    return true;
}

bool Actor::huntsFrackMan() const
{
    return true;
}

bool Actor::needsToBePickedUpToFinishLevel() const
{
    return true;
}

bool Actor::moveToIfPossible(int x, int y)
{
    if( x > 59 )
        return false;
    if( y > 63 )
        return false;
    moveTo(x,y);
    return true;
}



//================Agent===================//================Agent===================
//================Agent===================//================Agent===================
//================Agent===================//================Agent===================
//================Agent===================//================Agent===================
//================Agent===================//================Agent===================

Agent::Agent(StudentWorld* world, int startX, int startY, Direction startDir,
      int imageID, unsigned int hitPoints)
:Actor(world, startX, startY, startDir, true, imageID, 1, 0)
{
    
}

unsigned int Agent::getHitPoints() const
{
    return 0;
}

bool Agent::annoy(unsigned int amount)
{
    return true;
}

bool Agent::canPickThingsUp() const
{
    return true;
}

//================FrackMan===================//================FrackMan===================
//================FrackMan===================//================FrackMan===================
//================FrackMan===================//================FrackMan===================
//================FrackMan===================//================FrackMan===================
//================FrackMan===================//================FrackMan===================

FrackMan::FrackMan(StudentWorld* world, int startX, int startY)
:Agent(world, startX, startY, right, IID_PLAYER, 10)
{
    setDirection(right);
    makingMove = false;
}

void FrackMan::move()
{
    int x = getX();
    int y = getY();
    if(!isAlive()) //frackman is not alive
        return;
    else
    {
        Direction directionMoving = getDirection();
        if(makingMove == true)
        {
            
            if(directionMoving == down)
            {
                if(y!=0)
                {
                    moveTo(x, y-1);
                    makingMove = false;
                }
                else
                    moveTo(x,y);
            }
            else if(directionMoving == right)
            {
                if(x!=60)
                {
                    moveTo(x+1, y);
                    makingMove = false;
                }
                else
                    moveTo(x,y);
            }
            else if(directionMoving == left)
            {
                if( x!=0 )
                {
                    moveTo(x-1, y);
                    makingMove = false;
                }
                else
                    moveTo(x,y);
            }
            else if(directionMoving == up)
            {
                if(y!=60)
                {
                    moveTo(x , y+1);
                    makingMove = false;
                }
                else
                    moveTo(x,y);
            }
            
        }
        makingMove = true;
    }
    getWorld()->clearDirt(x, y);
}

void FrackMan::keyEvent(int key)
{
    makingMove = true;
    if(key == KEY_PRESS_LEFT)
        setDirection(left);
    else if(key == KEY_PRESS_UP)
        setDirection(up);
    else if(key == KEY_PRESS_DOWN)
        setDirection(down);
    else if(key == KEY_PRESS_RIGHT)
        setDirection(right);
    else
        makingMove = false;
}

bool FrackMan::annoy(unsigned int amount)
{
    //TO DO:
    return true;
}

void FrackMan::addGold()
{
    //TO DO:
}

bool FrackMan::canDigThroughDirt() const
{
    return true;
}


void addSonar()
{
    //TO DO:
}

void addWater()
{
    //TO DO:
}

unsigned int FrackMan::getGold() const
{
    //TO DO:
    return 0;
}

unsigned int FrackMan::getSonar() const
{
    //TO DO:
    return 0;
}

// Get amount of water
unsigned int FrackMan::getWater() const
{
    //TO DO:
    return 0;
}

//================Dirt===================//================Dirt===================
//================Dirt===================//================Dirt===================
//================Dirt===================//================Dirt===================
//================Dirt===================//================Dirt===================
//================Dirt===================//================Dirt===================

Dirt::Dirt(StudentWorld* world, int startX, int startY)
:Actor(world, startX, startY, right, true, IID_DIRT, .25, 3)
{
}

void Dirt::move()
{
}


//================Boulder===================//================Boulder===================
//================Boulder===================//================Boulder===================
//================Boulder===================//================Boulder===================
//================Boulder===================//================Boulder===================
//================Boulder===================//================Boulder===================

Boulder::Boulder(StudentWorld* world, int startX, int startY)
:Actor(world, startX, startY, down, true, IID_BOULDER, 1, 1)
{
}

void Boulder::move()
{
    int x = getX();
    int y = getY();
    moveTo(x,y-1);
}

bool Boulder::canActorsPassThroughMe() const
{
    return true;
}



