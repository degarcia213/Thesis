//
//  Grinder.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/27/14.
//
//

#ifndef __backToTheKitchen__Grinder__
#define __backToTheKitchen__Grinder__

#include <iostream>
#include "GameObject.h"

static animation_t grinderAnim =
{
    110,0,1,2,2,75,0,-1,-1,1
};
static animation_t grinderHighlightAnim =
{
    112,0,1,2,2,75,0,-1,-1,1
};

static animation_t bigGrinderFront =
{
    1440,0,1,11,4,75,0,-1,-1,1
};

static animation_t bigGrinderBack =
{
    1452,0,1,11,4,75,0,-1,-1,1
};



class Grinder : public GameObject {
public:
    
    Grinder();
    Grinder(int x, int y);
    
    void update();
    
    ofVec2f bigGrinderHitBoxPos;
    int bigGrinderHitWidth;
    int bigGrinderHitHeight;
    
};


#endif /* defined(__backToTheKitchen__Grinder__) */
