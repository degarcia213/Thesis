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
#include "FoodBubble.h"
#include "Dish.h"

static animation_t potBack =
{
    82,0,1,2,2,75,0,-1,-1,1
};

static animation_t potFront =
{
    84,0,1,2,2,75,0,-1,-1,1
};

static animation_t waterPotBackAnim =
{
    10,0,1,2,1,75,0,-1,-1,1
};
static animation_t waterPotFrontAnim =
{
    12,0,1,2,1,75,0,-1,-1,1
};
static animation_t boilPotBackAnim =
{
    14,0,4,2,1,75,0,-1,-1,1
};
static animation_t boilPotFrontAnim =
{
    22,0,4,2,1,75,0,-1,-1,1
};

static animation_t fillPotBackAnim =
{
    30,0,2,2,1,75,0,-1,-1,1
};
static animation_t fillPotFrontAnim =
{
    34,0,2,2,1,75,0,-1,-1,1
};

class Pot : public GameObject {
public:
    
    Pot();
    Pot(int x, int y);
    
    void setup();
    void update();
    
    void fill();
    void empty();
    void select();
    void deselect();
    void emptyToTrash();
    void emptyToDish(Dish * d);
    void removeFromPot(Ingredient * i);
    
    void mousePressed(int x, int y);
    
    Sink * sink;
    Grill * grill;
    
    bool BURNER_ACTIVE;
    
    ofVec2f mouthPos;
    int mouthWidth;
    int mouthHeight;
    
    void addSpriteToRenderer();
    bool add(Ingredient * _i);
    
    bool ACTIVE;
    vector <Ingredient *> contents;
    vector <ofVec2f> contentPos;
    vector <ofVec2f> contentDir;
    
    vector <FoodBubble> bubbles;
    
    int fillLvl;
    int maxFill;
    
    bool BEING_FILLED;
    bool HAS_CONTENTS;
    bool FULL;
    bool IN_SINK;
    bool ON_GRILL;
    bool SELECTED;
    bool READY_TO_POUR;
    bool READY_TO_TRASH;
    bool READY_TO_PLATE;
    
    int numContents;
    int maxContents;
    
};

#endif /* defined(__backToTheKitchen__Pot__) */
