//
//  ServeBtn.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/6/14.
//
//

#ifndef __backToTheKitchen__ServeBtn__
#define __backToTheKitchen__ServeBtn__

#include <iostream>
#include "SimpleButton.h"

class ServeBtn : public SimpleButton
{
public:
    ServeBtn();
    ServeBtn(int x,int y);
    
    virtual void action();
};

#endif /* defined(__backToTheKitchen__ServeBtn__) */
