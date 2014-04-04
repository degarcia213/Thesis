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
#include "FoodBubble.h"
#include "Grill.h"
#include "Dish.h"

static animation_t skilletBack =
{
    90,0,1,2,1,75,0,-1,-1,1
};

static animation_t skilletFront =
{
    92,0,1,2,1,75,0,-1,-1,1
};
static animation_t sizzleAnim =
{
    58,0,5,2,1,75,0,-1,-1,1
};
static animation_t steamAnim =
{
    52,0,6,1,1,75,0,-1,-1,1
};
static animation_t skilletFlameAnim =
{
    66,0,4,2,1,75,0,-1,-1,1
};

class Skillet : public GameObject {
public:
    
    Skillet();
    Skillet(int x, int y);
    
    void setup();
    void update();
    void draw();
    
    void select();
    void deselect();
    void emptyToTrash();
    void emptyToDish(Dish * d);
    void removeFromSkillet(Ingredient * i);
    
    void mousePressed(int x, int y);
    
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
    bool READY_TO_TRASH;
    bool READY_TO_POUR;
    bool READY_TO_PLATE;
    
    int numContents;
    int maxContents;
    
};

#endif /* defined(__backToTheKitchen__Skillet__) */
