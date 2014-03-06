//
//  simpleButton.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/6/14.
//
//

#include "SimpleButton.h"

SimpleButton::SimpleButton():GameObject()
{
    
}

SimpleButton::SimpleButton(int x, int y, int _width, int _height, string _text):GameObject(x,y)
{
    width = _width;
    height = _height;
    text = _text;
}

void SimpleButton::action()
{
    
}

void SimpleButton::draw()
{
    ofSetColor(0, 0, 0);
    ofRect(pos.x, pos.y, width, height);
    ofDrawBitmapString(text, pos.x + 1, pos.y + height/2);
}
