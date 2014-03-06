//
//  Grill.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#include "Grill.h"
#include "testApp.h"

Grill::Grill():GameObject()
{
    
}

Grill::Grill(int x, int y):GameObject(x,y)
{
    
}

void Grill::setup()
{
    GameObject::setup();
    ACTIVE = true;
}

void Grill::update()
{
    GameObject::update();
    
    burner1.set(pos.x + 50,pos.y);
    burner2.set(pos.x - 50,pos.y);
    
    if (ACTIVE)
    {
        anim = grillOn;
    }
    else
    {
        anim = grillOff;
    }
    
}

void Grill::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    app->game.mainRenderer->addCenteredTile(&anim, pos.x, pos.y,0,F_NONE,2,255,255,255,255);
    
    
}

void Grill::draw()
{
    
    ofSetColor(0, 255, 0);
    ofRect(burner1 - 1, 2, 2);
    ofRect(burner2 - 1, 2, 2);
    
}