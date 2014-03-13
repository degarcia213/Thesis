//
//  foodBubble.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/6/14.
//
//

#ifndef __backToTheKitchen__foodBubble__
#define __backToTheKitchen__foodBubble__

#include <iostream>
#include "GameObject.h"
#include "Ingredient.h"

static animation_t foodBubbleAnim =
{
    440,0,8,2,2,50,0,1,-1,1
};

static animation_t redBubble =
{
    456,0,1,2,2,75,0,-1,-1,1
};
static animation_t greenBubble =
{
    458,0,1,2,2,75,0,-1,-1,1
};
static animation_t blueBubble =
{
    460,0,1,2,2,75,0,-1,-1,1
};

class FoodBubble:public GameObject
{
public:
    FoodBubble();
    FoodBubble(int _x, int _y, int _angle, animation_t _bubbleAnim, Ingredient * _content);
    
    void update();
    void addSpriteToRenderer();
    
    ofVec2f bubblePos;
    
    animation_t lineAnim;
    animation_t bubbleAnim;
    Ingredient * content;
    
    float bubbleAlpha;
    float maxBubbleAlpha;
};

#endif /* defined(__backToTheKitchen__foodBubble__) */
