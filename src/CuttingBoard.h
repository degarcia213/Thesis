//
//  CuttingBoard.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/4/14.
//
//

#ifndef __backToTheKitchen__CuttingBoard__
#define __backToTheKitchen__CuttingBoard__

#include <iostream>
#include "GameObject.h"

static animation_t cuttingBoardAnim =
{
    94,0,1,3,2,75,0,-1,-1,1
};
static animation_t cuttingBoardHighlightAnim =
{
    97,0,1,3,2,75,0,-1,-1,1
};

static animation_t bigCuttingBoardAnim =
{
    1344,0,1,11,7,75,0,-1,-1,1
};


class CuttingBoard : public GameObject {
public:
    
    CuttingBoard();
    CuttingBoard(int x, int y);
    
    void update();
    
    ofVec2f bigCuttingBoardHitBoxPos;
    int bigCuttingBoardWidth;
    int bigCuttingBoardHeight;
    
};

#endif /* defined(__backToTheKitchen__CuttingBoard__) */
