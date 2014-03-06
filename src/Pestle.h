//
//  Pestle.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/27/14.
//
//

#ifndef __backToTheKitchen__Pestle__
#define __backToTheKitchen__Pestle__

#include <iostream>
#include "GameObject.h"

static animation_t bigPestle =
{
    1360,0,1,9,2,75,0,-1,-1,1
};

class Pestle:public GameObject
{
public:
    
    Pestle();
    Pestle(int x,int y);
    
    void mousePressed(int x,int y);
    void mouseDragged(int x, int y);
    void mouseMoved(int x, int y);
    void mouseReleased(int x, int y);
    void rotateToImpact();
    void addSpriteToRenderer();
    
    void update();
    void setup();
    
    bool GRINDING;

    ofVec2f impactPos;
    ofVec2f impactDest;
    int boundLeft;
    int boundRight;
    int restHeight;
    int angle;
    

};

#endif /* defined(__backToTheKitchen__Pestle__) */
