//
//  GameObject.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/5/14.
//
//

#ifndef __backToTheKitchen__GameObject__
#define __backToTheKitchen__GameObject__

#include <iostream>
#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"
#include "NameDisplay.h"

class GameObject{
public:
    GameObject();
    GameObject(int x,int y);
    GameObject(int x, int y, ofImage * _spriteSheet);
    
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void drawDebug();
    virtual void addSpriteToRenderer();
    virtual void mousePressed(int x, int y, int button);
    virtual void spawnDisplay(string _displayText);
    virtual void changeAnim(animation_t _anim);
    virtual void clampAngle();
    
    ofVec2f pos;
    int ID;
    int angle;
    
    int size;
    float drawScale;
    
    int modx;
    int mody;
    
    animation_t anim;
    ofImage * spriteSheet;
    
    string displayName;
    vector <NameDisplay *> nameDisplays;
    
    bool HOLDABLE;
    bool HELD;
    
    bool HIGHLIGHTED;
    
    
};

#endif /* defined(__backToTheKitchen__GameObject__) */
