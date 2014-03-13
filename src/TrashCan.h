//
//  TrashCan.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/12/14.
//
//

#ifndef __backToTheKitchen__TrashCan__
#define __backToTheKitchen__TrashCan__

#include <iostream>
#include "GameObject.h"

static animation_t trashCanAnim =
{
    114,0,1,3,1,75,0,-1,-1,1
};

class TrashCan : public GameObject
{
public:
    TrashCan();
    TrashCan(int x, int y);
    TrashCan(int x, int y, int width, int height);
    
    void drawDebug();
    
    ofVec2f mouthPos;
    int mouthWidth;
    int mouthHeight;
    
};

#endif /* defined(__backToTheKitchen__TrashCan__) */
