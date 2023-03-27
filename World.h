#ifndef WORLD_H
#define WORLD_H
#include "Rodent.h"

// The possible moves
enum Move {UP = 0, DOWN, LEFT, RIGHT};

// The size of this world
const int WORLDSIZE = 19;

// Number of initial males
const int INITIAL_MALE_MICE = 15;

// Number of initial females
const int INITIAL_FEMALE_MICE = 15;

// Time steps between breeding of males
const int BREED_MALE_MICE = 300000000000;

// Time steps between breeding of females
const int BREED_FEMALE_MICE = 800000000000;

// Time steps until females die if they have not eaten
const int STARVE_FEMALE_MICE = 3000000000000;

struct Position
{
    int x;
    int y;
};

class World
{
    public:
        // Constructor: creates and initializes this world. the seed is used for
        // seeding the random behaviour.
        World(unsigned int seed);

        // Destructor.
        ~World();

        // Returns the rodent at the given coordinates.
        Rodent* getAt(int x, int y) const;

        // Sets the rodent org at position (x,y).
        void setAt(int x, int y, Rodent* org);

        // Displays this world.
        void display() const;

        // Simulates one time step in this world.
        void simulateOneStep();

        // Infects random mice in world with Covid
        void InfectMice();

        // Makes all non-infected adult mice immune to Covid
        void makeMiceImmune();

        // Returns a random position in the grid.
        Position randomPosition() const;

        // Returns a random move (UP, DOWN, LEFT or RIGHT).
        Move randomMove() const;

    private:
        // The grid in which the rodents live. According the to image below,
        // the correct iteration order through grid starts at the top left
        // corner (i.e. grid[0][0]), loops through one column at a time and ends
        // at the bottom right corner (i.e. grid[WORLDSIZE-1][WORLDSIZE-1]).
        //
        // grid[0, 0]          , grid[1, 0],      ...,      grid[WORLDSIZE-1, 0]
        // grid[0, 1]          , grid[1, 1],      ...,      grid[WORLDSIZE-1, 1]
        //    .                                                     .
        //    .                                                     .
        //    .                                                     .
        // grid[0, WORLDSIZE-2], grid[1, WORLDSIZE-2], ..., grid[WORLDSIZE-1, WORLDSIZE-2]
        // grid[0, WORLDSIZE-1], grid[1, WORLDSIZE-1], ..., grid[WORLDSIZE-1, WORLDSIZE-1]
		//
		// (See e.g. the destructor for correct iteration through the grid)
        Rodent* grid[WORLDSIZE][WORLDSIZE];

        // Randomly create `count` many rodents of type `orgType`.  This
        // method uses the parameterized constructor in Ant and Bug.
        void createRodents(RodentType orgType, int count);

        // Reset all rodents to not moved. This is necessary because later we
        // iterate through the grid starting from the top left moving to the
        // bottom right looking for an rodent to move. Say if an rodent
        // moves down, we don't want to move the rodent again when we reach
        // it.
        void resetRodents();

        // Make every rodents in this world of type aType move. Make sure to
        // to iterate through grid in order as specified above and only move an
        // rodent if it hasn't moved already.
        void moveRodent(RodentType aType);

        // Remove all dead rodent from this world. Iterates through the grid
        // and uses the method Rodent::isDead() to test if an rodent is
        // dead. For this assignment in this method, only starved bugs will be
        // removed.
        void cleanup();

        // Make every rodent in this world breed. Make sure to iterate
        // through grid in order as specified above and to only breed rodentms
        // that have moved, since breeding places new rodents on the map we
        // don't want to try and breed those.
        void breedRodents();
};

#endif // WORLD_H
