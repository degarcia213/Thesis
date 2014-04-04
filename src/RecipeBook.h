//
//  RecipeBook.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 4/4/14.
//
//

#ifndef __backToTheKitchen__RecipeBook__
#define __backToTheKitchen__RecipeBook__

#include <iostream>
#include "GameObject.h"

static animation_t recipeBookAnim =
{
    184,0,1,2,2,75,0,-1,-1,1
};
static animation_t recipeBookHighlightAnim =
{
    186,0,1,2,2,75,0,-1,-1,1
};
static animation_t bigRecipeBookAnim =
{
    1040,0,1,12,7,75,0,-1,-1,1
};


class RecipeBook : public GameObject {
public:
    
    RecipeBook();
    RecipeBook(int x, int y);
    
    void update();
    
    ofVec2f hitBoxPos;
    int width;
    int height;
    
    ofVec2f bigPos;
    ofVec2f bigHitBoxPos;
    int bigWidth;
    int bigHeight;
};

#endif /* defined(__backToTheKitchen__RecipeBook__) */
