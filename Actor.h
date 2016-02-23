#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startingX, int startingY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
    virtual ~Actor() {};
    virtual void doSomething() = 0;
    virtual bool isAlive();
    void setAlive(bool value);
private:
    bool m_isAlive;
    
};

class Dirt: public Actor
{
    
public:
    Dirt(int x, int y);
    virtual ~Dirt();
    virtual void doSomething();
};

class Boulder: public Actor
{
public:
    Boulder(int x, int y);
    virtual ~Boulder();
    virtual void doSomething();
};

class FrackMan: public Actor
{
public:
    FrackMan(int x, int y);
    virtual ~FrackMan();
    virtual void doSomething();
    void keyEvent(int key);
    
private:
    bool makingMove;
};

#endif // ACTOR_H_