// A possible interface for StudentWorld.  You may use all, some, or none
// of this, as you wish.

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GraphObject.h"
#include "GameWorld.h"
#include <string>
#include <list>

class Actor;
class FrackMan;
class Boulder;
class Dirt;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    // Add an actor to the world.
    void addActor(Actor* a);
    
    // Clear a 4x4 region of dirt.
    void clearDirt(int x, int y);  // DONE!!!
    void removeDirt(int x, int y);  // DONE!!!
    
    // Can actor move to x,y?
    bool canActorMoveTo(Actor* a, int x, int y) const;
    
    // Annoy all other actors within radius of annoyer, returning the
    // number of actors annoyed.
    int annoyAllNearbyActors(Actor* annoyer, int points, int radius);
    
    // Reveal all objects within radius of x,y.
    void revealAllNearbyObjects(int x, int y, int radius);
    
    // If the FrackMan is within radius of a, return a pointer to the
    // FrackMan, otherwise null.
    Actor* findNearbyFrackMan(Actor* a, int radius) const;
    
    // If at least one actor that can pick things up is within radius of a,
    // return a pointer to one of them, otherwise null.
    Actor* findNearbyPickerUpper(Actor* a, int radius) const;
    
    // Annoy the FrackMan.
    void annoyFrackMan();
    
    // Give FrackMan some sonar charges.
    void giveFrackManSonar();
    
    // Give FrackMan some water.
    void giveFrackManWater();
    
    // Is the Actor a facing toward the FrackMan?
    bool facingTowardFrackMan(Actor* a) const;
    
    // If the Actor a has a clear line of sight to the FrackMan, return
    // the direction to the FrackMan, otherwise GraphObject::none.
    GraphObject::Direction lineOfSightToFrackMan(Actor* a) const;
    
    // Return whether the Actor a is within radius of FrackMan.
    bool isNearFrackMan(Actor* a, int radius) const;
    
    // Determine the direction of the first move a quitting protester
    // makes to leave the oil field.
    GraphObject::Direction determineFirstMoveToExit(int x, int y);
    
    // Determine the direction of the first move a hardcore protester
    // makes to approach the FrackMan.
    GraphObject::Direction determineFirstMoveToFrackMan(int x, int y);
    
private:
    int currentLevel;
    FrackMan* fmPointer;
    Boulder* boulderPointer;
    Dirt* dirtArray[VIEW_WIDTH][VIEW_HEIGHT-4];
};

#endif // STUDENTWORLD_H_