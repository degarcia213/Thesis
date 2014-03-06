//
//  Pestle.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/27/14.
//
//

#include "Pestle.h"
#include "testApp.h"

Pestle::Pestle():GameObject()
{
    
}

Pestle::Pestle(int x, int y):GameObject(x,y)
{
    setup();
}

void Pestle::setup()
{
    GameObject::setup();
    impactPos.set(pos.x-260,pos.y);
    anim = bigPestle;
    drawScale = 2;
    restHeight = 250;
    impactPos.y = ofGetHeight() - restHeight;
    boundLeft = 160;
    boundRight = 800;
    GRINDING = false;
}

void Pestle::update()
{
    GameObject::update();
    angle = -90;// + (45 * (impactPos.x/640));
    
    
    // ADD ANGLE OF DISPLAY MODIFICATION
    if (angle > 360)
    {
        angle -= 360;
    }
    else if (angle < 0)
    {
        angle += 360;
    }
    
    impactPos.x = impactDest.x;
    
    if (GRINDING)
    {
        impactPos.interpolate(impactDest,.5);
        pos.x = impactPos.x;
        pos.y = impactPos.y - 250;
        
        cout << "pos is " + ofToString(impactPos) + ", dest is " + ofToString(impactDest) + "\n";
    }
    else
    {
        impactPos.interpolate(ofVec2f(pos.x,restHeight),.5);
        pos.x = impactPos.x;
        pos.y = impactPos.y - 250;
    }
    
}

void Pestle::rotateToImpact()
{
    
}

void Pestle::addSpriteToRenderer()
{
    testApp * app = (testApp *)ofGetAppPtr();
    
    // add sprite addition code. But also, we might just have each object have its own renderer which takes the spritesheet from the constructor. Can we do that?
    
    app->game.mainRenderer->addCenterRotatedTile(&anim, pos.x, pos.y, 0, F_NONE, 2, angle, NULL, 255,255,255,255);
}

void Pestle::mousePressed(int x, int y)
{
    GRINDING = true;
}

void Pestle::mouseMoved(int x, int y)
{
    impactDest.set(x,y);
    if (impactDest.x < boundLeft)
    {
        impactDest.x = boundLeft;
    }
    else if (impactDest.x > boundRight)
    {
        impactDest.x = boundRight;
    }
}

void Pestle::mouseDragged(int x, int y)
{
    mouseMoved(x, y);
}

void Pestle::mouseReleased(int x, int y)
{
    GRINDING = false;
}
