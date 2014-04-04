//
//  NameDisplay.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/12/14.
//
//

#include "NameDisplay.h"

NameDisplay::NameDisplay()
{
    
}

NameDisplay::NameDisplay(int x, int y, string _name)
{
    pos.set(x,y);
    name = _name;
    currentSize = 0;
    loadFont("fonts/pixel_maz.ttf", 48,false,false,true);
    displayTimer = 0;
    timeToAppear = .2 * ofGetFrameRate();
    timeDisplayed = ofGetFrameRate();
    timeToFade = .2 * ofGetFrameRate();
    APPEARED = false;
    FADING = false;
    DEAD = false;
    drawScale = 2;
}

void NameDisplay::update()
{
    if (!APPEARED)
    {
        if (displayTimer < timeToAppear)
        {
            currentSize += .5 * (1 - currentSize);
            displayTimer++;
        }
        else
        {
            APPEARED = true;
            displayTimer = 0;
        }
    }
    
    if (APPEARED && !FADING)
    {
        if (displayTimer < timeDisplayed)
        {
            currentSize = 1;
            displayTimer++;
        }
        else
        {
            FADING = true;
            displayTimer = timeToFade;
        }
    }
    
    if (FADING)
    {
        if (displayTimer > 0)
        {
            currentSize -= .25 * currentSize;
            displayTimer--;
        }
        else
        {
            DEAD = true;
        }
    }
}

void NameDisplay::draw()
{
    
    float displayWidth = stringWidth(name)/2;
    int finalx = pos.x - displayWidth;
    if (finalx < 0)
    {
        pos.x -= (finalx - (5 * drawScale));
    }
    else if ((pos.x + displayWidth) > ofGetWidth())
    {
        pos.x -= displayWidth/2;
    }
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(currentSize, currentSize, 1);
    ofFill();
    ofSetHexColor(0xff000000);
    ofTrueTypeFont::drawStringAsShapes(name,0 - displayWidth+ (2 * drawScale), -8 * drawScale);
    ofSetHexColor(0xff8cfff0);
    ofTrueTypeFont::drawStringAsShapes(name, 0 - displayWidth, (-10 * drawScale));
    ofPopMatrix();
    
}