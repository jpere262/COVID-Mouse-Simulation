//
//  Male_Mouse.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//
#include <cstdlib>

#include <iostream>
#include "Male_Mouse.h"
#include "Rodent.h"
#include "World.h"
using namespace std;

Male_Mouse::Male_Mouse(World* aWorld, int xcoord, int ycoord, bool ADULT) : Rodent(aWorld, xcoord, ycoord)
{
    adult = ADULT; // Checks if given mouse is an adult or not
    adultTick = 10; // Amount of turns until male mouse turns into an adult
    //infectedDeathTick = 10; // Amount of turns until mouse has given chance of death
}

void Male_Mouse::move()
{
    if (!adult) // Decrements adult growth counter by one every time the male mouse moves, if he is a baby
        adultTick--;
    if (infected) // Decrements infection death counter by one every time the male mouse moves, if he is infected
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

void Male_Mouse::breed()
{
    if(breedTicks >= BREED_FEMALE_MICE)
    {
        breedAtAdjacentCell();
    }
}


void Male_Mouse::generateOffspring(int whereX, int whereY)
{
    new Male_Mouse(this->world, whereX, whereY);
    breedTicks = 0;
}

RodentType Male_Mouse::getType() const
{
    return MALE_MOUSE;
}

char Male_Mouse::representation() const
{
    if (!adult) // Representation for baby male mouse
    {
        return 'p';
    }
    else // Representation for adult male mouse
    {
        return 'M';
    }
}

int Male_Mouse::size() const
{
    return 10;
}

bool Male_Mouse::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
