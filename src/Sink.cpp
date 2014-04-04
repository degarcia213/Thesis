//
//  Sink.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/4/14.
//
//

#include "Sink.h"

Sink::Sink():GameObject()
{
    
}

Sink::Sink(int x, int y):GameObject(x,y)
{
    anim = sinkAnim;
    ACTIVE = false;
    
}

void Sink::setup()
{
    GameObject::setup();
    size = 75;
}

void Sink::update()
{
    GameObject::update();
    
    
    if (ACTIVE)
    {
        if (!WATER_FLOWING)
        {
            // set equal to start up
            waterAnim = &waterStartAnim;
            
            // check if frame is equal to total - 1 (frame starts at 0, total counts from 1).
            if (waterAnim->frame == waterAnim->total_frames-1)
            {
                // if so, flip boolean, reset start anim to 0, and switch to new anim so we never see frame 0.
                WATER_FLOWING = true;
                waterAnim->frame = 0;
                waterAnim = &waterLoopAnim;
            }
        }
        else
        {
            waterAnim = &waterLoopAnim;
        }
    }
}