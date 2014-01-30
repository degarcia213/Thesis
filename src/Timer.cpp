//
//  Timer.cpp
//  Combining
//
//  Created by Diego Garcia on 1/8/14.
//
//

#include "Timer.h"

Timer::Timer()
{
    
}

///---
Timer::Timer(int seconds)
{
    startTime = 0;
    currentTime = startTime;
    timeLimit = seconds * ofGetFrameRate();
    ACTIVE = false;
    TIME_UP = false;
}

void Timer::setup()
{
    
}

void Timer::activate()
{
    ACTIVE = true;
}

void Timer::reset(int seconds)
{
    startTime = 0;
    currentTime = startTime;
    timeLimit = seconds * ofGetFrameRate();
    ACTIVE = false;
    TIME_UP = false;
}

void Timer::reset()
{
    ACTIVE = false;
    TIME_UP = false;
    startTime = 0;
    currentTime = startTime;
}


void Timer::update()
{
    
    if (ACTIVE && !TIME_UP)
    {
        if (currentTime < timeLimit)
        {
            currentTime ++;
        } else {
            TIME_UP = true;
        }
    }
    
}


void Timer::draw()
{
    if (ACTIVE)
    {
    ofSetColor(0, 255, 0);
    ofRect(20,20,100 - (100* (currentTime / timeLimit)),20);
    }
    
}
