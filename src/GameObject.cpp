//
//  GameObject.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/5/14.
//
//

#include "GameObject.h"
#include "testApp.h"

GameObject::GameObject()
{
    
}

GameObject::GameObject(int x, int y)
{
    pos.set(x,y);
}

GameObject::GameObject(int x, int y, ofImage * _spriteSheet)
{
    pos.set(x,y);
    spriteSheet = _spriteSheet;
    drawScale = 2;
    setup();
}

void GameObject::setup()
{
    modx = 0;
    mody = 0;
    size = 20;
    angle = 0;
    HOLDABLE = false;
    HELD = false;
    HIGHLIGHTED = false;
    
}

void GameObject::update()
{
    if (HELD)
    {
        pos = ofPoint(ofGetMouseX(),ofGetMouseY());
        drawScale = 3;
    }
    else
    {
        drawScale = 2;
    }
    
    if (angle < 0)
    {
        angle += 360;
    }
    else if (angle > 360)
    {
        angle -= 360;
    }
}

void GameObject::draw()
{
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofCircle(pos.x + modx, pos.y + mody, size);
    ofDrawBitmapString(displayName, pos.x + modx,pos.y + mody);
    
}

void GameObject::addSpriteToRenderer()
{
    testApp * app = (testApp *)ofGetAppPtr();
    app->game.mainRenderer->addCenterRotatedTile(&anim, pos.x + modx, pos.y + mody, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
}

void GameObject::mousePressed(int x, int y, int button)
{
    
}