//
//  SpeechBubble.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/14/14.
//
//

#ifndef __backToTheKitchen__SpeechBubble__
#define __backToTheKitchen__SpeechBubble__

#include <iostream>
#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"

static animation_t topLeftAnim =
{
    0,0,1,1,1,75,0,-1,-1,1
};

static animation_t topCenterAnim =
{
    1,0,1,1,1,75,0,-1,-1,1
};

static animation_t topRightAnim =
{
    2,0,1,1,1,75,0,-1,-1,1
};

static animation_t midLeftAnim =
{
    3,0,1,1,1,75,0,-1,-1,1
};

static animation_t midCenterAnim =
{
    4,0,1,1,1,75,0,-1,-1,1
};

static animation_t midRightAnim =
{
    5,0,1,1,1,75,0,-1,-1,1
};

static animation_t bottomLeftAnim =
{
    6,0,1,1,1,75,0,-1,-1,1
};

static animation_t bottomCenterAnim =
{
    7,0,1,1,1,75,0,-1,-1,1
};

static animation_t bottomRightAnim =
{
    8,0,1,1,1,75,0,-1,-1,1
};

class SpeechBubble
{
public:
    SpeechBubble();
    SpeechBubble(int x, int y, int _width, int _height);
    
    void setup();
    void update();
    void draw();
    void addSpriteToRenderer();
    
    void show(string _text);
    void hide();
    
    bool SHOWN;
    
    string text;
    ofTrueTypeFont font;
    
    ofColor textColor;
    
    ofVec2f pos;
    int width;
    int height;
    
    int rows;
    int columns;
    
    int drawScale;
    
};

#endif /* defined(__backToTheKitchen__SpeechBubble__) */
