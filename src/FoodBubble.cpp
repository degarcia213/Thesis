//
//  foodBubble.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/6/14.
//
//

#include "FoodBubble.h"
#include "testApp.h"

FoodBubble::FoodBubble():GameObject()
{
    
}

FoodBubble::FoodBubble(int _x, int _y, int _angle, animation_t _bubbleAnim, Ingredient * _content):GameObject(_x,_y)
{
    angle = _angle;
    lineAnim = foodBubbleAnim;
    bubbleAlpha = 0;
    content = _content;
    bubbleAnim = _bubbleAnim;
    maxBubbleAlpha = 180;
    
    bubblePos.set(pos.x,pos.y - 20);
    bubblePos.rotate(angle,pos);
}

void FoodBubble::update()
{
    GameObject::update();
    if (lineAnim.frame == lineAnim.total_frames-1 && bubbleAlpha < maxBubbleAlpha)
    {
        if (maxBubbleAlpha - bubbleAlpha > 2)
        {
            bubbleAlpha += .5 * (maxBubbleAlpha - bubbleAlpha);
        }
        else
        {
            bubbleAlpha = maxBubbleAlpha;
        }
    }
    
    bubblePos.set(pos.x,pos.y - 20);
    bubblePos.rotate(angle,pos);
}

void FoodBubble::addSpriteToRenderer()
{
 
    testApp * app = (testApp *)ofGetAppPtr();
    app->game.mainRenderer->addCenterRotatedTile(&bubbleAnim, bubblePos.x + modx, bubblePos.y + mody, 0, F_NONE, drawScale, 0, NULL, 255,255,255,bubbleAlpha);
    app->game.mainRenderer->addCenterRotatedTile(&lineAnim, pos.x + modx, pos.y + mody, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
    app->game.mainRenderer->addCenterRotatedTile(&content->anim, bubblePos.x + modx, bubblePos.y + mody, 0, F_NONE, drawScale, 0, NULL, 255,255,255, 255 * (bubbleAlpha / maxBubbleAlpha));
    
}
