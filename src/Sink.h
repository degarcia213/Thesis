//
//  Sink.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/4/14.
//
//

#ifndef __backToTheKitchen__Sink__
#define __backToTheKitchen__Sink__

#include <iostream>
#include "GameObject.h"

static animation_t sinkAnim =
{
    0,0,1,3,2,75,0,-1,-1,1
};

static animation_t waterStartAnim =
{
    3,0,6,1,2,75,0,-1,-1,1
};

static animation_t waterLoopAnim =
{
    8,0,2,1,2,75,0,-1,-1,1
};

class Sink : public GameObject {
public:
    
    Sink();
    Sink(int x, int y);
    
    void update();
    
    animation_t * waterAnim;
    
    ofVec2f nozzle1Pos;
    ofVec2f nozzle2Pos;
    
    bool ACTIVE;
    bool WATER_FLOWING;
    
};

#endif /* defined(__backToTheKitchen__Sink__) */
