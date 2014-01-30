//
//  Screen.h
//  TIME
//
//  Created by Diego Garcia on 12/7/13.
//
//

#ifndef __TIME__Screen__
#define __TIME__Screen__

#include <iostream>
#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"
#include "TimeHandler.h"

class Screen {
public:
    Screen();
    Screen(TimeHandler * _time);
    
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void mousePressed(int x,int y,int button);
    virtual void mouseDragged(int x,int y,int button);
    virtual void mouseReleased(int x,int y,int button);
    virtual void mouseMoved(int x,int y);
    
    TimeHandler * time;

};

#endif /* defined(__TIME__Screen__) */
