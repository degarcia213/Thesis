//
//  Recipe.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 4/6/14.
//
//

#include "Recipe.h"

Recipe::Recipe()
{
    
}

Recipe::Recipe(string _text, string _dishName, bool _known)
{
    actualText = _text;
    dishName = _dishName;
    KNOWN = _known;
    if (!KNOWN)
    {
        displayText = "??????";
    }
    else
    {
        displayText = actualText;
    }
}

void Recipe::update()
{
    if (!KNOWN)
    {
        displayText = "??????";
    }
    else
    {
        displayText = actualText;
    }
}




