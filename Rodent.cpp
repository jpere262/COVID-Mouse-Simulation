#include <iostream>
#include "Rodent.h"
#include "World.h"

// Create an rodent at the given coordinates in the given world.
Rodent::Rodent(World* aWorld, int xcoord, int ycoord) {
    world = aWorld;
    x = xcoord;
    y = ycoord;
    breedTicks = 0;
    moved = false;
    infected = false; // Rodent is not infected
    immune = false; // Rodent is not immune to infection
    infectedDeathTick = 10; // Amount of turns until mouse has given chance of death
    world->setAt(x, y, this);
}

// flags the rodent as moved or not
void Rodent::setMoved(bool hasMoved) {
    Rodent::moved = hasMoved;
}

// has the rodent moved or not?
bool Rodent::hasMoved() const {
    return moved;
}

// moves the rodent from coordinates (x,y) to (xNew,yNew)
void Rodent::movesTo(int xNew, int yNew) {

        world->setAt(xNew, yNew, world->getAt(x, y));
    
        world->setAt(x, y, NULL);
        
        x = xNew;
        y = yNew;
    
    world->getAt(x, y)->setMoved(true);
}

// Breeds an rodent at an adjacent cell. This method calls the
// generateOffspring() method.
void Rodent::breedAtAdjacentCell()  {
    
    if((world->getAt(x, y + 1) == NULL) && in_range(x, y + 1))
    {
        generateOffspring(x, y + 1);
    }
    else if((world->getAt(x, y - 1) == NULL) && in_range(x, y - 1))
    {
        generateOffspring(x, y - 1);
    }
    else if((world->getAt(x - 1, y) == NULL)  && in_range(x - 1, y))
    {
        generateOffspring(x - 1, y);
    }
    else if((world->getAt(x + 1, y) == NULL)  && in_range(x + 1, y))
    {
        generateOffspring(x + 1, y);
    }
}


bool Rodent::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
// Returns true if rodent is dead, false otherwise.
bool Rodent::isDead() const {
    return false;
}
