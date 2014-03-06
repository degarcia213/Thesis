//
//  Grinder.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/27/14.
//
//

#include "Grinder.h"

Grinder::Grinder():GameObject()
{
    
}

Grinder::Grinder(int x, int y):GameObject(x,y)
{
    bigGrinderHitBoxPos.set(160,320);
    bigGrinderHitWidth = 440;
    bigGrinderHitHeight = 220;
}

void Grinder::update()
{
    GameObject::update();
    
    if (HIGHLIGHTED)
    {
        anim = grinderHighlightAnim;
    }
    else
    {
        anim = grinderAnim;
    }
}