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
    angle = 0;
}

GameObject::GameObject(int x, int y, ofImage * _spriteSheet)
{
    pos.set(x,y);
    spriteSheet = _spriteSheet;
    drawScale = 2;
    setup();
    angle = 0;
}

void GameObject::setup()
{
    modx = 0;
    mody = 0;
    size = 20;
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
}

void GameObject::drawDebug()
{
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofCircle(pos.x + modx, pos.y + mody, size);
    ofDrawBitmapString(displayName, pos.x + modx,pos.y + mody);
    
}

void GameObject::spawnDisplay(string _displayText)
{
    NameDisplay * nameDisplay = new NameDisplay(pos.x, pos.y, _displayText);
    
    testApp * app = (testApp *)ofGetAppPtr();
    app->game.uiDisplayText.push_back(nameDisplay);
}

void GameObject::addSpriteToRenderer()
{
    testApp * app = (testApp *)ofGetAppPtr();
    app->game.mainRenderer->addCenterRotatedTile(&anim, pos.x + modx, pos.y + mody, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
}

void GameObject::mousePressed(int x, int y, int button)
{
    
}