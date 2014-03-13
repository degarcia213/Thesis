//
//  TrashCan.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/12/14.
//
//

#include "TrashCan.h"

TrashCan::TrashCan():GameObject()
{
    anim = trashCanAnim;
}

TrashCan::TrashCan(int x, int y):GameObject(x,y)
{
    anim = trashCanAnim;
}

TrashCan::TrashCan(int x, int y, int width, int height):GameObject(x,y)
{
    mouthPos.set(x,y);
    mouthWidth = width;
    mouthHeight = height;
    
    pos.set(mouthPos.x + width/2,mouthPos.y + height/2);
    
    anim = trashCanAnim;
}

void TrashCan::drawDebug()
{
    ofSetColor(255, 0, 0);
    ofRect(mouthPos,mouthWidth,mouthHeight);
}