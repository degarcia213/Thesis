//
//  Recipe.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 4/6/14.
//
//

#ifndef __backToTheKitchen__Recipe__
#define __backToTheKitchen__Recipe__

#include <iostream>
#include "ofMain.h"

class Recipe
{
public:
    Recipe();
    Recipe(string _text, string _dishName, bool _known = false);
    
    void update();
    
    string dishName;
    string actualText;
    string displayText;
    bool KNOWN;
    
};

#endif /* defined(__backToTheKitchen__Recipe__) */
