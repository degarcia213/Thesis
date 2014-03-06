//
//  Pot.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#ifndef __backToTheKitchen__Pot__
#define __backToTheKitchen__Pot__

#include <iostream>
#include "Ingredient.h"
#include "Sink.h"
#include "Grill.h"

static animation_t potBack =
{
    82,0,1,2,2,75,0,-1,-1,1
};

static animation_t potFront =
{
    84,0,1,2,2,75,0,-1,-1,1
};

static animation_t waterPotAnim =
{
    10,0,1,2,2,75,0,-1,-1,1
};
static animation_t boilPotAnim =
{
    12,0,4,2,2,75,0,-1,-1,1
};

static animation_t fillPotAnim =
{
    20,0,2,2,2,75,0,-1,-1,1
};

class Pot : public GameObject {
public:
    
    Pot();
    Pot(int x, int y);
    
    void setup();
    void update();
    
    void fill();
    void empty();
    
    Sink * sink;
    Grill * grill;
    
    ofVec2f mouthPos;
    int mouthWidth;
    int mouthHeight;
    
    void addSpriteToRenderer();
    bool add(Ingredient * _i);
    
    bool ACTIVE;
    vector <Ingredient *> contents;
    vector <ofVec2f> contentPos;
    vector <ofVec2f> contentDir;
    
    int fillLvl;
    int maxFill;
    
    bool BEING_FILLED;
    bool HAS_CONTENTS;
    bool FULL;
    bool IN_SINK;
    bool ON_GRILL;
    
    int numContents;
    int maxContents;
    
};

#endif /* defined(__backToTheKitchen__Pot__) */
