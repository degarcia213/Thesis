//
//  ResponseBtn.h
//  Combining
//
//  Created by Diego Garcia on 11/14/13.
//
//

#ifndef __Combining__ResponseBtn__
#define __Combining__ResponseBtn__

#include <iostream>
#include "ofMain.h"

class ResponseBtn{
public:
    void setup();
    void update();
    void draw();
    void mousePressed();
    void mouseReleased();
    
    string text;
};

#endif /* defined(__Combining__ResponseBtn__) */
