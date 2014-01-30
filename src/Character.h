//
//  Character.h
//  Combining
//
//  Created by Diego Garcia on 11/14/13.
//
//

#ifndef __Combining__Character__
#define __Combining__Character__

#include <iostream>
#include "ofMain.h"

class Character{
public:
Character();
Character(int _id);
    
    void setup();
    void update();
    void draw();
    
    vector <string> dialogue;
    string currentDialogue;
    
    string name;
    string desire;
    
    string rewardType;
    string ingredientReward;
    
    int cashAmt;
    
};

#endif /* defined(__Combining__Character__) */
