#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor Constructor
Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
:GraphObject(imageID,startX, startY,dir,size,depth)
{
    setVisible(true);
    m_isAlive = false;
}

bool Actor::isAlive()
{
    return m_isAlive;
}

void Actor::setAlive(bool value)
{
    m_isAlive = value;
}

Boulder::Boulder(int x, int y)
:Actor(IID_BOULDER, x, y, down, 1, 1)
{
}

Boulder::~Boulder()
{
}

void Boulder::doSomething()
{
    int x = getX();
    int y = getY();
    moveTo(x,y-1);
}

//dirt constructor
Dirt::Dirt(int x, int y)
:Actor(IID_DIRT, x, y, right, 0.25, 3)
{
}

Dirt::~Dirt()
{
}

void Dirt::doSomething()
{
}

//frackMan constructor and methods
FrackMan::FrackMan(int x, int y)
:Actor(IID_PLAYER, x,y, right, 1.0, 0)
{
    setDirection(right);
    makingMove = false;
    setAlive(true);
}

FrackMan::~FrackMan()
{
}

void FrackMan::doSomething()
{
    if(!isAlive()) //frackman is not alive
        return;
    else
    {
        int x = getX();
        int y = getY();
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
        
    }
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