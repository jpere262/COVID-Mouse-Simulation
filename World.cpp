#include <iostream>
#include <Windows.h>
#include <cstdlib>  // for rand
#include <ctime> // for time
#include <conio.h> // for kbhit
#include "World.h"
#include "Male_Mouse.h"
#include "Female_Mouse.h"
#include "Graphic_Design.h"

using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the male mice = 5
    createRodents(MALE_MOUSE, INITIAL_MALE_MICE);
    // creates the female mice = 5
    createRodents(FEMALE_MOUSE, INITIAL_FEMALE_MICE);
}

// Deallocate memory allocated to rodents in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the rodent at the given coordinates
// If the coordinates are not valid, returns NULL
Rodent* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Rodent* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const 
{
    
        int numMaleMice = 0;
        int numFemaleMice = 0;
        int numAdultMice = 0;
        int numBabyMice = 0;
        
        // Change position of display in console 
        gotoxy(40, 8);
        for (int i = 0; i < WORLDSIZE; i++)
        {
            for (int j = 0; j < WORLDSIZE; j++) 
            {
                if (grid[i][j] == NULL) {
                    cout << " .";
                }
                else {

                    if (grid[i][j]->getType() == MALE_MOUSE) {
                        numMaleMice++;
                    }
                    else if (grid[i][j]->getType() == FEMALE_MOUSE) {
                        numFemaleMice++;
                    }
                    if(grid[i][j]->adult) {
                        numAdultMice++;
                    }
                    else if (grid[i][j]->adult == false) {
                        numBabyMice++;
                    }

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    // If adult mouse is uninfected, then yellow
                    SetConsoleTextAttribute(hConsole, 14);
                    // If adult mouse is infected, then red
                    if (grid[i][j]->infected)
                    {
                        SetConsoleTextAttribute(hConsole, 12);
                    }
                    // If adult mouse was infected but cured, then blue (immune)
                    if (grid[i][j]->immune)
                    {
                        SetConsoleTextAttribute(hConsole, 11);
                    }
                    if (grid[i][j]->adult == false)
                    {
                        SetConsoleTextAttribute(hConsole, 2);
                    }
                    cout << " " << grid[i][j]->representation();
                    // Reset grid text color
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            // Keep grid displayed at specific coordinates on console
            gotoxy(40, 9+i);
        }
        // Display count of male/female and adult/baby mice
        gotoxy(44, 28);
        cout << "Male Mice: " << numMaleMice << "    Female Mice: " << numFemaleMice << endl;
        gotoxy(44, 29);
        cout << "Adult Mice: " << numAdultMice << "   Baby Mice: " << numBabyMice << endl;   
 }

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the rodents breed (again which happens under a certain
    // condition).

    // Reset all rodents to not moved
    resetRodents();

    // Move the ants
    moveRodent(MALE_MOUSE);

    // Move the bugs
    moveRodent(FEMALE_MOUSE);

    

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedRodents();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createRodents(RodentType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == MALE_MOUSE) {
                new Male_Mouse(this, p.x, p.y);   // Create a male mouse and put it into the world
            }
            else if (orgType == FEMALE_MOUSE) {
                new Female_Mouse(this, p.x, p.y);   // Create a female mouse and put it into the world
            }
        }
    }
}



// Reset all rodents to not moved
void World::resetRodents() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all rodents of type aType
void World::moveRodent(RodentType aType) {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    // Check if there are non-infected adult mice adjacent to infected mice
                    if (grid[i][j]->infected && grid[i][j]->immune == false)
                    {
                        // Check if there is non-infected adult mouse on left
                        if (i > 0)
                        {
                            if (grid[i - 1][j] != NULL)
                            {
                                if(grid[i - 1][j]->adult == true)
                                {
                                    // 80% chance to infect adult mouse 
                                    if (grid[i - 1][j]->infected == false && grid[i - 1][j]->immune == false)
                                    {
                                        srand(time(0));

                                        int hasCovid;

                                        hasCovid = (rand() % 10) + 1;
                                        if (hasCovid <= 8)
                                        {
                                            Rodent* R = (Rodent*)grid[i - 1][j];
                                            R->infected = true; // Infects selected adult mouse
                                        }
                                    }
                                }
                            }
                        }
                        // Check if there is non-infected adult mouse on right
                        if (i < 18)
                        {
                            if (grid[i + 1][j] != NULL)
                            {
                                if (grid[i + 1][j]->adult == true)
                                {
                                    // 80% chance to infect adult mouse
                                    if (grid[i + 1][j]->infected == false && grid[i + 1][j]->immune == false)
                                    {
                                        srand(time(0));

                                        int hasCovid;

                                        hasCovid = (rand() % 10) + 1;
                                        if (hasCovid <= 8)
                                        {
                                            Rodent* R = (Rodent*)grid[i + 1][j];
                                            R->infected = true;
                                        }
                                    }
                                }
                            }
                        }
                        // Check if there is non-infected adult mouse above
                        if (j > 0)
                        {
                            if (grid[i][j - 1] != NULL)
                            {
                                if (grid[i][j - 1]->adult==true)
                                {
                                    // 80% chance to infect adult mouse
                                    if (grid[i][j - 1]->infected == false && grid[i][j - 1]->immune == false)
                                    {
                                        srand(time(0));

                                        int hasCovid;

                                        hasCovid = (rand() % 10) + 1; 
                                        if (hasCovid <= 8)
                                        {
                                            Rodent* R = (Rodent*)grid[i][j - 1];
                                            R->infected = true; // Infects selected adult mouse
                                        }
                                    }
                                }
                            }
                        }
                        // Check if there is non-infected adult mouse below
                        if (j < 18)
                        {
                            if (grid[i][j + 1] != NULL)
                            {
                                if (grid[i][j + 1]->adult==true)
                                {
                                    // 80% chance to infect adult mouse
                                    if (grid[i][j + 1]->infected == false && grid[i][j + 1]->immune == false)
                                    {
                                        srand(time(0));

                                        int hasCovid;

                                        hasCovid = (rand() % 10) + 1;
                                        if (hasCovid <= 8)
                                        {
                                            Rodent* R = (Rodent*)grid[i][j + 1];
                                            R->infected = true; // Infects selected adult mouse
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Check if female baby mouse is ready to turn into adult
                    if (grid[i][j]->getType() == FEMALE_MOUSE)
                    {
                        Female_Mouse* f = (Female_Mouse*)grid[i][j];
                        if (f->adultTick == 0)
                        {
                                f->adult = true; // Turns selected baby mouse into an adult after a given amount of turns
                                f->adultTick = 10; // Resets adult tick 
                        }
                    }
                    // Check if male baby mouse is ready to turn into adult and check for female pregnancy, left / right / top / bottom
                    if (grid[i][j]->getType() == MALE_MOUSE)
                    {
                        Male_Mouse* m = (Male_Mouse*)grid[i][j];
                        if (m->adultTick == 0)
                        {
                            m->adult = true; // Turns selected baby mouse into an adult after a given amount of turns
                            m->adultTick = 10;
                        }

                        if (m->adult)
                        {
                            // Check if there is female mouse on left
                            if (i > 0)
                            {
                                if (grid[i - 1][j] != NULL)
                                {
                                    if (grid[i - 1][j]->getType() == FEMALE_MOUSE)
                                    {
                                        Female_Mouse* f = (Female_Mouse*)grid[i - 1][j];
                                        // Check if female mouse is adult
                                        if (f->adult)
                                        {
                                            srand(time(0));

                                            int FP;

                                            FP = (rand() % 2) + 1;
                                            // 50% chance of female mouse becoming pregnant
                                            if (FP == 1)
                                            {
                                                // Check if female mouse can be pregnant again (lower chance of pregnancy if she cannot)
                                                if (f->pregAgain == true)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        f->isPregnant = true;
                                                        f->deliverBabyTick = 2;
                                                        f->pregAgain = false;
                                                    }
                                                }
                                                if (f->pregAgain == false)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        // 1% chance of female mouse being impregnated again
                                                        srand(time(0));

                                                        int r2;

                                                        r2 = (rand() % 100) + 1;
                                                        if (r2 == 1)
                                                        {
                                                            f->isPregnant = true;
                                                            f->deliverBabyTick = 2;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            // Check if there is female mouse on the right
                            if (i < 18)
                            {
                                if (grid[i + 1][j] != NULL)
                                {
                                    if (grid[i + 1][j]->getType() == FEMALE_MOUSE)
                                    {
                                        Female_Mouse* f = (Female_Mouse*)grid[i + 1][j];
                                        if (f->adult)
                                        {
                                            srand(time(0));

                                            int FP;

                                            FP = (rand() % 2) + 1;
                                            if (FP == 1)
                                            {
                                                // Check if female mouse can be pregnant again (lower chance of pregnancy if she cannot)
                                                if (f->pregAgain == true)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        f->isPregnant = true;
                                                        f->deliverBabyTick = 2;
                                                        f->pregAgain = false;
                                                    }
                                                }
                                                if (f->pregAgain == false)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        // 1% chance of female mouse being impregnated again
                                                        srand(time(0));

                                                        int r3;

                                                        r3 = (rand() % 100) + 1;
                                                        if (r3 == 1)
                                                        {
                                                            f->isPregnant = true;
                                                            f->deliverBabyTick = 2;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            // Check if there is a female mouse above
                            if (j > 0)
                            {
                                if (grid[i][j - 1] != NULL)
                                {
                                    if (grid[i][j - 1]->getType() == FEMALE_MOUSE)
                                    {
                                        Female_Mouse* f = (Female_Mouse*)grid[i][j - 1];
                                        if (f->adult)
                                        {
                                            srand(time(0));

                                            int FP;

                                            FP = (rand() % 2) + 1;
                                            if (FP == 1)
                                            {
                                                // Check if female mouse can be pregnant again (lower chance of pregnancy if she cannot)
                                                if (f->pregAgain == true)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        f->isPregnant = true;
                                                        f->deliverBabyTick = 2;
                                                        f->pregAgain = false;
                                                    }
                                                }
                                                if (f->pregAgain == false)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        // 1% chance of female mouse being impregnated again
                                                        srand(time(0));

                                                        int r4;

                                                        r4 = (rand() % 100) + 1;
                                                        if (r4 == 1)
                                                        {
                                                            f->isPregnant = true;
                                                            f->deliverBabyTick = 2;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            // Check if there is a female mouse below
                            if (j < 18)
                            {
                                if (grid[i][j + 1] != NULL)
                                {
                                    if (grid[i][j + 1]->getType() == FEMALE_MOUSE)
                                    {
                                        Female_Mouse* f = (Female_Mouse*)grid[i][j + 1];
                                        if (f->adult)
                                        {
                                            srand(time(0));

                                            int FP;

                                            FP = (rand() % 2) + 1;
                                            if (FP == 1)
                                            {
                                                // Check if female mouse can be pregnant again (lower chance of pregnancy if she cannot)
                                                if (f->pregAgain == true)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        f->isPregnant = true;
                                                        f->deliverBabyTick = 2;
                                                        f->pregAgain = false;
                                                    }
                                                }
                                                if (f->pregAgain == false)
                                                {
                                                    // Check if female mouse is pregnant
                                                    if (!f->isPregnant)
                                                    {
                                                        // 1% chance of female mouse being impregnated again
                                                        srand(time(0));

                                                        int r5;

                                                        r5 = (rand() % 100) + 1;
                                                        if (r5 == 1)
                                                        {
                                                            f->isPregnant = true;
                                                            f->deliverBabyTick = 2;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead rodents from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            srand(time(0));
            int D; // Creates variable for random number generator

            D = (rand() % 10) + 1;
            
            // 90% chance to kill off any rodents that have had Covid for 10 turns
            if ((grid[i][j] != NULL) && grid[i][j]->infectedDeathTick==0 && D<=9) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
            // 10% chance that rodent survives and becomes immune to infection
            else if ((grid[i][j] != NULL) && grid[i][j]->infectedDeathTick == 0 && D == 10) {
                Rodent* R = (Rodent*)grid[i][j];
                R->infected = false;
                R->immune = true;
                R->infectedDeathTick = 10;
            }
        }
    }
}

// Make the rodents breed
void World::breedRodents() { 
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if (grid[i][j]->getType() == FEMALE_MOUSE)
                grid[i][j]->breed();
            }
        }
    }
}

// Randomly infect adult mice
void World::InfectMice()
{ 
    int covCount = 0;
    while (covCount <= 2)
    {
        Position p = randomPosition(); // Creates a random position
        if (grid[p.x][p.y] != NULL)
        {
            if (grid[p.x][p.y]->adult)
            {
                // Only infect THREE non-infected mice
                if (!grid[p.x][p.y]->infected)
                {
                    grid[p.x][p.y]->infected = true;
                    covCount++;
                }
            }
        }
    }
}

// Make all non-infected adult mice immune to Covid
void World::makeMiceImmune()
{
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                if (grid[i][j]->adult == true)
                {
                    if (grid[i][j]->infected == false)
                    {
                        grid[i][j]->immune = true;
                    }
                }
            }
        }
    }
}
