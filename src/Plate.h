//
//  Plate.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/12/14.
//
//

#ifndef __backToTheKitchen__Plate__
#define __backToTheKitchen__Plate__

#include <iostream>
#include "GameObject.h"

static animation_t plateAnim =
{
    108,0,1,2,1,75,0,-1,-1,1
};

class Plate : public GameObject{
public:
    Plate();
    Plate(int x, int y);
    
    
    
    
};

#endif /* defined(__backToTheKitchen__Plate__) */
