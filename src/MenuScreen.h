//
//  MenuScreen.h
//  Combining
//
//  Created by Diego Garcia on 1/8/14.
//
//

#ifndef __Combining__MenuScreen__
#define __Combining__MenuScreen__

#include <iostream>
#include "Screen.h"

class MenuScreen : public Screen
{
public:
    
    MenuScreen();
    MenuScreen(TimeHandler * _time);
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
};

#endif /* defined(__Combining__MenuScreen__) */
