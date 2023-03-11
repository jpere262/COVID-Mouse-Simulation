//
//  Female_Mouse.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

#include "Female_Mouse.h"
#include "Male_Mouse.h"
#include "Rodent.h"
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

Female_Mouse::Female_Mouse(World* aWorld, int xcoord, int ycoord, bool PREGAGAIN, bool ADULT) : Rodent(aWorld, xcoord, ycoord)
{
    death_tik = 0;
    isPregnant = false; // Female mouse is not pregnant
    deliverBabyTick = 0; // Amount of turns needed for female mouse to give birth
    adultTick = 10; // Amount of turns needed for female mouse to become an adult
    //infectedDeathTick = 10; // Amount of turns until mouse has given chance of death
    adult = ADULT; // Checks if given mouse is adult or not
    pregAgain = PREGAGAIN; // Checks if given mouse can be pregnant again or not
}

void Female_Mouse::move()
{

    death_tik++;

    if (isPregnant) // Decrements pregnancy counter by one every time the female mouse moves, if she is pregnant
        deliverBabyTick--;
    if (!adult) // Decrements adult growth counter by one every time the female mouse moves, if she is a baby
        adultTick--;
    if (infected) // Decrements infection death counter by one every time the female mouse moves, if she is infected
        infectedDeathTick--;
    
    Move mover = world->randomMove();
    switch (mover){
        case UP:
            if(world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
            {
                movesTo(x, y + 1);
            }
            break;
        case DOWN:
            if(world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
            {
                movesTo(x, y - 1);
            }
            break;
        case LEFT:
            if(world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
            {
                movesTo(x - 1, y);
            }
            break;
        case RIGHT:
            if(world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
            {
                movesTo(x + 1, y);
            }
            break;
        default:
            break;
    }
}

void Female_Mouse::generateOffspring(int whereX, int whereY) 
{

    srand(time(0));

    int r;

    r = (rand() % 2) + 1;
    // 50% chance of offspring being female
    if (r == 2)
    {
        new Female_Mouse(this->world, whereX, whereY, true, false);
        breedTicks = 0;
    }
    // 50% chance of offspring being male
    else if (r == 1)
    {
        new Male_Mouse(this->world, whereX, whereY, false);
        breedTicks = 0;
    }
}

void Female_Mouse::breed()
{
    if(isPregnant && deliverBabyTick == 0)
    {
        isPregnant = false; // Resets pregnancy status when giving birth, prevents birth if there is no empty adjacent spot
        breedAtAdjacentCell();
    }
}

bool Female_Mouse::isDead() const
{
    if(death_tik >= STARVE_FEMALE_MICE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

RodentType Female_Mouse::getType() const
{
    return FEMALE_MOUSE;
}


char Female_Mouse::representation()const
{
    
    if (!adult) // Representation for baby female mouse
    {
        return 'b';
    }
    if (isPregnant) // Representation for pregnant female mouse (displays how many turns are left until giving birth)
    {
        return 48 + deliverBabyTick;
    }
    else // Representation for adult female mouse
        return 'F';
}

int Female_Mouse::size() const
{
    return 30;
}

bool Female_Mouse::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
