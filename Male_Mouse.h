//
//  Male_Mouse.h
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

#ifndef INHERITANCE_AND_POLYMORPHISM_Male_Mouse
#define INHERITANCE_AND_POLYMORPHISM_Male_Mouse

#include <iostream>
#include "Rodent.h"
#include "World.h"

class Male_Mouse : public Rodent
{
public:
    
    int adultTick; // Creates int variable for adult growth counter

    Male_Mouse(World* aWorld, int xcoord, int ycoord, bool ADULT = true);
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
    
    bool in_range(int xx, int yy);
    
private:
    
    void generateOffspring(int whereX, int whereY);
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Male_Mouse__) */
