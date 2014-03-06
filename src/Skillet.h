//
//  Skillet.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#ifndef __backToTheKitchen__Skillet__
#define __backToTheKitchen__Skillet__

#include <iostream>
#include "GameObject.h"
#include "Ingredient.h"

static animation_t skilletBack =
{
    90,0,1,2,2,75,0,-1,-1,1
};

static animation_t skilletFront =
{
    92,0,1,2,2,75,0,-1,-1,1
};

class Skillet : public GameObject {
public:
    
    Skillet();
    Skillet(int x, int y);
    
    void setup();
    void update();
    
    void addSpriteToRenderer();
    
    bool ACTIVE;
    vector <Ingredient *> contents;
    
};

#endif /* defined(__backToTheKitchen__Skillet__) */
