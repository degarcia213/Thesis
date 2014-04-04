//
//  Grill.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#ifndef __backToTheKitchen__Grill__
#define __backToTheKitchen__Grill__

#include <iostream>
#include "GameObject.h"

static animation_t grillOff =
{
    100,0,1,4,2,75,0,-1,-1,1
};

static animation_t grillFlameAnim =
{
    104,0,1,1,1,75,0,-1,-1,1
};

class Grill : public GameObject {
public:
    
    Grill();
    Grill(int x, int y);
    
    void setup();
    void update();
    void drawDebug();
    
    ofVec2f burner1;
    ofVec2f burner2;
    
    ofVec2f hitBoxPos;
    int width;
    int height;
    
    bool B1_ACTIVE;
    bool B2_ACTIVE;
    
    void addSpriteToRenderer();
    
};



#endif /* defined(__backToTheKitchen__Grill__) */
