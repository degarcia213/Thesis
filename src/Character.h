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
#include "Ingredient.h"
#include "Dish.h"
#include "GameObject.h"

class Character : public GameObject{
public:
Character();
Character(int x, int y, int _difficulty);
    
    void setup();
    void update();
    void draw();
    
    vector <string> dialogue;
    string currentDialogue;
    
    string name;
    
    int difficulty;
    
    bool WANTS_FORM;
    //
    // ---- possible desired forms are...
    bool WANTS_SOUP;                    //
    bool WANTS_NOODLES;                 //
    bool WANTS_GRAINS;                  //
    // ---------------------------------//
    
    bool WANTS_BALANCE;
    bool WANTS_INGREDIENT;
    bool WANTS_FLAVOR;
    
    void decidePreferences();
    
    string desiredFlavor;
    
    FORMS DESIRED_FORM;
    string desiredForm;
    
    string desiredIngredientType;
    
    void assessDish(Dish * _d);
    bool PLEASED_WITH_DISH;
    
    
    string dishImpressions;
    string rewardType;
    string ingredientReward;
    
    
    
    int cashAmt;
    
};

#endif /* defined(__Combining__Character__) */
