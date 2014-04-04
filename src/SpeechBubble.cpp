//
//  SpeechBubble.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/14/14.
//
//

#include "SpeechBubble.h"
#include "testApp.h"

SpeechBubble::SpeechBubble()
{
    
}

SpeechBubble::SpeechBubble(int _x, int _y, int _width, int _height)
{
    pos.set(_x,_y);
    
    width = _width;
    height = _height;
    
    rows = _height/32;
    columns = _width/32;
    
    SHOWN = false;
    
    textColor.set(255,255,255);
    
    drawScale = 2;
    
    if (font.loadFont("fonts/pixel_maz.ttf", 24))
    {
        cout << "FONT LOADED!!!\n";
    }
    else
    {
        cout << "ERROR. SPEECH BUBBLE FONT FAILED TO LOAD.\n";
    }
}

void SpeechBubble::setup()
{
    
}

void SpeechBubble::update()
{
    if (SHOWN)
    {
        addSpriteToRenderer();
    }
}

void SpeechBubble::show(string _text)
{
    SHOWN = true;
    text = _text;
    
    columns = font.stringWidth(_text)/32;
}

void SpeechBubble::hide()
{
    SHOWN = false;
}

void SpeechBubble::draw()
{
    if (SHOWN)
    {
        ofSetColor(textColor);
        font.drawString(text, pos.x + width/2,pos.y + height/2);
        
        
    }
}

void SpeechBubble::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    for (int x = 0; x < columns; x++)
    {
        for (int y = 0; y < rows; y++)
        {
            
            if (x == 0 && y == 0)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&topLeftAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (x == columns-1 && y == 0)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&topRightAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (x == columns-1 && y == rows-1)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&bottomRightAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (x == 0 && y == rows-1)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&bottomLeftAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (x == 0)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&midLeftAnim,pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (y == 0)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&topCenterAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (x == columns-1)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&midRightAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else if (y == rows-1)
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&bottomCenterAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            else
            {
                app->game.speechBubbleRenderer->addCenterRotatedTile(&midCenterAnim, pos.x + (x * (32 * drawScale)), pos.y + (y * (32 * drawScale)), 0, F_NONE, drawScale, 0, NULL, 255,255,255,255);
            }
            
            
        }
    }
    
}