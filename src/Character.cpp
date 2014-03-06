//
//  Character.cpp
//  Combining
//
//  Created by Diego Garcia on 11/14/13.
//
//

#include "Character.h"
#include "testApp.h"

Character::Character(): GameObject(){
    
    WANTS_FORM = false;
    WANTS_FLAVOR = false;
    WANTS_BALANCE = false;
    WANTS_INGREDIENT = false;
    
}

Character::Character(int x, int y, int _difficulty):GameObject(x,y){
    
    WANTS_FORM = false;
    WANTS_FLAVOR = false;
    WANTS_BALANCE = false;
    WANTS_INGREDIENT = false;
    WANTS_SOUP = false;
    WANTS_NOODLES = false;
    WANTS_GRAINS = false;
    
    difficulty = _difficulty;
}

void Character::setup(){
    
    GameObject::setup();
    
    decidePreferences();
    
    currentDialogue = "Hi! I'm " + name + ".\n";
    
    if (WANTS_FLAVOR)
    {
        currentDialogue += "I want something " + desiredFlavor + ".\n";
    }
    
    if (WANTS_FORM)
    {
        if (WANTS_SOUP)
        {
            currentDialogue += "Let's make it soup.\n";
        }
        else if (WANTS_NOODLES)
        {
            currentDialogue += "Make sure it has noodles.\n";
        }
        else if (WANTS_GRAINS)
        {
            currentDialogue += "Some Grains would be nice.\n";
        }
    }
    
    if (WANTS_INGREDIENT)
    {
        currentDialogue += "It'd be great if it had " + desiredIngredientType + ".\n";
    }
    
    if (WANTS_BALANCE)
    {
        currentDialogue += "I'm into the idea of something complex but nicely balanced.\n";
    }
}

void Character::update(){
    
}

void Character::decidePreferences()
{
    
    if (difficulty < 4)
    {
        int randNum = int(ofRandom(4));
        int randNum2 = int(ofRandom(4));
        int randNum3 = int(ofRandom(4));
        
        while(randNum2 == randNum)
        {
            cout << "bla";
            randNum2 = int(ofRandom(4));
        }
        
        while (randNum3 == randNum || randNum3 == randNum2)
        {
            cout << "keh";
            randNum3 = int(ofRandom(4));
        }
        
        switch (randNum) {
            case 0:
                WANTS_FORM = true;
                break;
            case 1:
                WANTS_FLAVOR = true;
                break;
            case 2:
                WANTS_BALANCE = true;
                break;
            case 3:
                WANTS_INGREDIENT = true;
                break;
            default:
                break;
        }
        
        if (difficulty > 1)
        {
            switch (randNum2) {
                case 0:
                    WANTS_FORM = true;
                    break;
                case 1:
                    WANTS_FLAVOR = true;
                    break;
                case 2:
                    WANTS_BALANCE = true;
                    break;
                case 3:
                    WANTS_INGREDIENT = true;
                    break;
                default:
                    break;
            }
            
        }
        
        if (difficulty > 2)
        {
            switch (randNum3) {
                case 0:
                    WANTS_FORM = true;
                    break;
                case 1:
                    WANTS_FLAVOR = true;
                    break;
                case 2:
                    WANTS_BALANCE = true;
                    break;
                case 3:
                    WANTS_INGREDIENT = true;
                    break;
                default:
                    break;
            }
            
        }
    }
    else
    {
        WANTS_FORM = true;
        WANTS_FLAVOR = true;
        WANTS_BALANCE = true;
        WANTS_INGREDIENT = true;
    }
    
    
    // add difficulty stuff here. For higher difficulties, the customer is pickier.

    
    if (WANTS_FORM)
    {
        int randForm = ofRandom(3);
        
        if (randForm == 0)
        {
            WANTS_SOUP = true;
        } else if (randForm == 1)
        {
            WANTS_NOODLES = true;
        } else if (randForm == 2)
        {
            WANTS_GRAINS = true;
        }
        
    }
    if (WANTS_FLAVOR)
    {
        int randFlavNum = int(ofRandom(6));
        
        switch (randFlavNum) {
            case 0:
                desiredFlavor = "sweet";
                break;
            case 1:
                desiredFlavor = "salty";
                break;
            case 2:
                desiredFlavor = "sour";
                break;
            case 3:
                desiredFlavor = "fatty";
                break;
            case 4:
                desiredFlavor = "bitter";
                break;
            case 5:
                desiredFlavor = "umami";
                break;
                
            default:
                break;
        }
    }
    
    if (WANTS_INGREDIENT)
    {
        testApp * app = (testApp *)ofGetAppPtr();
        desiredIngredientType = app->game.pantryContentsList[(int)ofRandom(app->game.pantry.size())];
    }
    
       
    
}

void Character::assessDish(Dish *_d)
{
    dishImpressions = "";
    PLEASED_WITH_DISH = true;
    bool PLEASED_WITH_FLAVOR = false;
    bool PLEASED_WITH_FORM = false;
    bool PLEASED_WITH_CONTENTS = false;
    bool PLEASED_WITH_BALANCE = false;
    
    if (WANTS_FLAVOR)
    {
        if (desiredFlavor == "sweet")
        {
            if (_d->sweetness == _d->prominentFlavor)
            {
                PLEASED_WITH_FLAVOR = true;
            }
        }
         else if (desiredFlavor == "salty")
        {
            if (_d->saltiness == _d->prominentFlavor)
            {
                PLEASED_WITH_FLAVOR = true;
            }
        }
         else if (desiredFlavor == "sour")
        {
            if (_d->sourness == _d->prominentFlavor)
            {
                PLEASED_WITH_FLAVOR = true;
            }
        }
         else if (desiredFlavor == "fatty")
        {
            if (_d->fattiness == _d->prominentFlavor)
            {
                PLEASED_WITH_FLAVOR = true;
            }
        }
          else if (desiredFlavor == "bitter")
        {
            if (_d->bitterness == _d->prominentFlavor)
            {
                PLEASED_WITH_FLAVOR = true;
            }
        }
           else if (desiredFlavor == "umami")
        {
            if (_d->umami == _d->prominentFlavor)
            {
                PLEASED_WITH_FLAVOR = true;
            }
        }
        if (!PLEASED_WITH_FLAVOR)
        {
            PLEASED_WITH_DISH = false;
            dishImpressions += "It's not " + desiredFlavor + " enough!\n";
        }
        else
        {
            dishImpressions += "Nice and " + desiredFlavor + "!\n";
        }
    }
    
    if (WANTS_BALANCE)
    {
        if (_d->complexity < 3)
        {
            PLEASED_WITH_DISH = false;
            dishImpressions += "This dish is too simple.\n";
        }
        
        if (_d->balance < 80)
        {
            PLEASED_WITH_DISH = false;
            dishImpressions += "It's not balanced!\n";
        }
    }
    
    if (WANTS_FORM)
    {
        if (WANTS_SOUP)
        {
            if (!_d->HAS_BROTH)
            {
                PLEASED_WITH_DISH = false;
                dishImpressions += "I wanted soup!\n";
            }
        }
        if (WANTS_NOODLES)
        {
            bool hasNoodles = false;
            for (int b = 0; b < _d->baseCount;b++)
            {
                if (_d->base[b]->form == NOODLES)
                {
                    hasNoodles = true;
                    string noodleType = _d->base[b]->type;
                    dishImpressions += "Mmm! My " + noodleType + "!\n";
                }
            }
            if (!hasNoodles)
            {
                PLEASED_WITH_DISH = false;
                dishImpressions += "I wanted noodles!\n";
            }
        }
        if (WANTS_GRAINS)
        {
            bool hasGrains = false;
            for (int b = 0; b < _d->baseCount;b++)
            {
                if (_d->base[b]->form == GRAINS)
                {
                    hasGrains = true;
                    string grainType = _d->base[b]->type;
                    dishImpressions += "The " + grainType + " makes for a nice grain.\n";
                }
            }
            if (!hasGrains)
            {
                PLEASED_WITH_DISH = false;
                dishImpressions += "I wanted grains!\n";
            }

        }
    }
    
    if (WANTS_INGREDIENT)
    {
        if (!_d->CONTAINS(desiredIngredientType))
        {
            PLEASED_WITH_DISH = false;
            dishImpressions += "Didn't you hear me say I wanted " + desiredIngredientType + "?\n";
        }
        else
        {
            dishImpressions += "I really do love " + desiredIngredientType + ".\n";
        }
    }
    
    if (PLEASED_WITH_DISH)
    {
        dishImpressions += "This will do just fine!";
    }
    else
    {
        dishImpressions += "This is no good.";
    }
    currentDialogue = dishImpressions;
}

void Character::draw(){
    
    
    
}