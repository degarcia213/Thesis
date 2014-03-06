//
//  CuttingBoard.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/4/14.
//
//

#include "CuttingBoard.h"

CuttingBoard::CuttingBoard():GameObject()
{
    
}

CuttingBoard::CuttingBoard(int x, int y):GameObject(x,y)
{
    bigCuttingBoardHitBoxPos.set(260,100);
    bigCuttingBoardWidth = 676;
    bigCuttingBoardHeight = 416;
}

void CuttingBoard::update()
{
    GameObject::update();
    
    if (HIGHLIGHTED)
    {
        anim = cuttingBoardHighlightAnim;
    }
    else
    {
        anim = cuttingBoardAnim;
    }
}