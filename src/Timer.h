//
//  Timer.h
//  Combining
//
//  Created by Diego Garcia on 1/8/14.
//
//

#ifndef __Combining__Timer__
#define __Combining__Timer__

#include <iostream>
#include "ofMain.h"

class Timer{
public:
    Timer();
    Timer(int seconds);
    
    void setup();
    void activate();
    void reset();
    void reset(int seconds);
    void update();
    void draw();
    
    float timeLimit;
    float currentTime;
    float startTime;
    
    bool ACTIVE;
    bool TIME_UP;
    
};

#endif /* defined(__Combining__Timer__) */
