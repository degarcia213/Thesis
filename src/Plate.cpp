//
//  Plate.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/12/14.
//
//

#include "Plate.h"

Plate::Plate():GameObject()
{
    
}

Plate::Plate(int x, int y):GameObject(x,y)
{
    anim = plateAnim;
}
