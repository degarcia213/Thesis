//
//  Skillet.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#include "Skillet.h"
#include "testApp.h"

Skillet::Skillet():GameObject()
{
    
}

Skillet::Skillet(int x, int y):GameObject(x,y)
{
    
}

void Skillet::setup()
{
    GameObject::setup();
    HOLDABLE = true;
    HELD = false;
    ACTIVE = false;
}

void Skillet::update()
{
    GameObject::update();
    
    if (ACTIVE)
    {
        for (int c = 0; c < contents.size(); c++)
        {
            contents[c]->boilTime ++;
        }
    }
    
}

void Skillet::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    app->game.mainRenderer->addCenteredTile(&skilletBack, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    
    
    for (int c = 0; c < contents.size(); c++)
    {
        contents[c]->addSpriteToRenderer();
    }
    
    app->game.mainRenderer->addCenteredTile(&skilletFront, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    
    
}
