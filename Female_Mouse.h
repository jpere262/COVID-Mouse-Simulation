//
//  Female_Mouse.h
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

#pragma once
#ifndef INHERITANCE_AND_POLYMORPHISM_Female_Mouse
#define INHERITANCE_AND_POLYMORPHISM_Female_Mouse

#include <iostream>

#include "World.h"
#include "Rodent.h"

class Female_Mouse : public Rodent
{
public:
    
    bool isPregnant; // Creates bool variable to check if female mouse is pregnant
    bool pregAgain; // Creates bool variable to check if female mouse can be pregnant again (with original chances)
    int deliverBabyTick; // Creates int variable for a female mouse pregnancy counter
    int adultTick; // Creates int variable for adult growth counter

    Female_Mouse() {};

    Female_Mouse(World* aWorld, int xcoord, int ycoord, bool PREGAGAIN = true, bool ADULT = true);

    // In the given world moves this organism.
    void move();
    
    // Makes this organism breed.
    void breed();
    
    // Returns the type of this organism.
    RodentType getType() const;
    
    // The character representation of this organism.
    char representation() const;
    
    // The size of this organism.
    int size() const;
    // Returns true if organism is dead, false otherwise.
    bool isDead() const;
    
    bool in_range(int xx, int yy);
    
private:
    
    void generateOffspring(int whereX, int whereY);
    int death_tik;
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Female_Mouse__) */
