// Possible interfaces for actors.  You may use all, some, or none
// of this, as you wish.

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int startX, int startY, Direction startDir,
          bool visible, int imageID, double size, int depth);
    
    // Action to perform each tick.
    virtual void move() = 0;
    
    // Is this actor alive?
    bool isAlive() const; // DONE!!
    
    // Mark this actor as dead.
    void setDead(); // DONE!!
    
    // Annoy this actor.
    virtual bool annoy(unsigned int amt);
    
    // Get this actor's world
    StudentWorld* getWorld() const; // DONE!!
    
    // Can other actors pass through this actor?
    virtual bool canActorsPassThroughMe() const;
    
    // Can this actor dig through dirt?
    virtual bool canDigThroughDirt() const;
    
    // Can this actor pick items up?
    virtual bool canPickThingsUp() const;
    
    // Does this actor hunt the FrackMan?
    virtual bool huntsFrackMan() const;
    
    // Can this actor need to be picked up to finish the level?
    virtual bool needsToBePickedUpToFinishLevel() const;
    
    // Move this actor to x,y if possible, and return true; otherwise,
    // return false without moving.
    bool moveToIfPossible(int x, int y);
private:
    bool m_isAlive;
    StudentWorld* m_studentWorld;
};

class Agent : public Actor
{
public:
    Agent(StudentWorld* world, int startX, int startY, Direction startDir,
          int imageID, unsigned int hitPoints);
    
    // Pick up a gold nugget.
    virtual void addGold() = 0;
    
    // How many hit points does this actor have left?
    unsigned int getHitPoints() const;
    
    virtual bool annoy(unsigned int amount);
    virtual bool canPickThingsUp() const;
private:
    
};

class FrackMan : public Agent
{
public:
    FrackMan(StudentWorld* world, int startX, int startY);
    virtual void move();
    void keyEvent(int key);
    
    virtual bool annoy(unsigned int amount);
    virtual void addGold();
    virtual bool canDigThroughDirt() const;
    
    // Pick up a sonar kit.
    void addSonar();
    
    // Pick up water.
    void addWater();
    
    // Get amount of gold
    unsigned int getGold() const;
    
    // Get amount of sonar charges
    unsigned int getSonar() const;
    
    // Get amount of water
    unsigned int getWater() const;
private:
    bool makingMove;
};

class Protester : public Agent
{
public:
    Protester(StudentWorld* world, int startX, int startY, int imageID,
              unsigned int hitPoints, unsigned int score);
    virtual void move();
    virtual bool annoy(unsigned int amount);
    virtual void addGold();
    virtual bool huntsFrackMan() const;
    
    // Set state to having gien up protest
    void setMustLeaveOilField();
    
    // Set number of ticks until next move
    void setTicksToNextMove();
};

class RegularProtester : public Protester
{
public:
    RegularProtester(StudentWorld* world, int startX, int startY, int imageID);
    virtual void move();
    virtual void addGold();
};

class HardcoreProtester : public Protester
{
public:
    HardcoreProtester(StudentWorld* world, int startX, int startY, int imageID);
    virtual void move();
    virtual void addGold();
};

class Dirt : public Actor
{
public:
    Dirt(StudentWorld* world, int startX, int startY);
    virtual void move();
};

class Boulder : public Actor
{
public:
    Boulder(StudentWorld* world, int startX, int startY);
    virtual void move();
    virtual bool canActorsPassThroughMe() const;
};

class Squirt : public Actor
{
public:
    Squirt(StudentWorld* world, int startX, int startY, Direction startDir);
    virtual void move();
};

class ActivatingObject : public Actor
{
public:
    ActivatingObject(StudentWorld* world, int startX, int startY, int imageID,
                     int soundToPlay, bool activateOnPlayer,
                     bool activateOnProtester, bool initallyActive);
    virtual void move();
    
    // Set number of ticks until this object dies
    void setTicksToLive();
};

class OilBarrel : public ActivatingObject
{
public:
    OilBarrel(StudentWorld* world, int startX, int startY);
    virtual void move();
    virtual bool needsToBePickedUpToFinishLevel() const;
};

class GoldNugget : public ActivatingObject
{
public:
    GoldNugget(StudentWorld* world, int startX, int startY, bool temporary);
    virtual void move();
};

class SonarKit : public ActivatingObject
{
public:
    SonarKit(StudentWorld* world, int startX, int startY);
    virtual void move();
};

class WaterPool : public ActivatingObject
{
public:
    WaterPool(StudentWorld* world, int startX, int startY);
    virtual void move();
};

#endif // ACTOR_H_