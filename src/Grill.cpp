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
    anim = grillOff;
    B1_ACTIVE = false;
    B2_ACTIVE = true;
}

void Grill::update()
{
    GameObject::update();
    
    burner1.set(pos.x + (25 * drawScale),pos.y);
    burner2.set(pos.x - (25 * drawScale),pos.y);
    
    knob1.set(pos.x - (1 * drawScale),pos.y + (2 * drawScale));
    knob2.set(pos.x + (3 * drawScale),pos.y - (4 * drawScale));
    
}

void Grill::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    app->game.mainRenderer->addCenteredTile(&anim, pos.x, pos.y,0,F_NONE,2,255,255,255,255);
    
    if (B1_ACTIVE)
    {
        app->game.mainRenderer->addCenteredTile(&grillFlameAnim, burner1.x + (1 * drawScale), burner1.y - (1 * drawScale),0,F_NONE,2,255,255,255,255);
    }
    if (B2_ACTIVE)
    {
        app->game.mainRenderer->addCenteredTile(&grillFlameAnim, burner2.x + (1 * drawScale), burner2.y- (1 * drawScale),0,F_NONE,2,255,255,255,255);
    }
    
    
}

void Grill::drawDebug()
{
    
    ofSetColor(0, 255, 0);
    ofRect(burner1 - 1, 2, 2);
    ofRect(burner2 - 1, 2, 2);
    ofSetColor(255,0,0);
    ofRect(knob1 - 1, 2, 2);
    ofRect(knob2 - 1, 2, 2);
    
}