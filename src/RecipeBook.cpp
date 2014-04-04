//
//  RecipeBook.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 4/4/14.
//
//

#include "RecipeBook.h"

RecipeBook::RecipeBook():GameObject()
{
    
}

RecipeBook::RecipeBook(int x, int y):GameObject(x,y)
{
    drawScale = 2;
    width = 40 * drawScale;
    height = 35 * drawScale;
    hitBoxPos.set(pos.x - width/2,pos.y-height/2);
    
    bigPos.set(250 * drawScale, ofGetHeight()-(64*drawScale));
    bigWidth = 376 * drawScale;
    bigHeight = 188 * drawScale;
    bigHitBoxPos.set(bigPos.x - (bigWidth/2), bigPos.y - (bigHeight/2));
    
}

void RecipeBook::update()
{
    GameObject::update();
    
    if (HIGHLIGHTED)
    {
        anim = recipeBookHighlightAnim;
    }
    else
    {
        anim = recipeBookAnim;
    }
    
    hitBoxPos.set(pos.x - width/2,pos.y-height/2);
    bigHitBoxPos.set(bigPos.x - (bigWidth/2), bigPos.y - (bigHeight/2));
}