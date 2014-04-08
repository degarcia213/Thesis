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

Character::Character(int x, int y):GameObject(x,y){
    
    WANTS_FORM = false;
    WANTS_FLAVOR = false;
    WANTS_BALANCE = false;
    WANTS_INGREDIENT = false;
    WANTS_SOUP = false;
    WANTS_NOODLES = false;
    WANTS_GRAINS = false;
    
    anim = charIdleAnim;
    
    setup();
}

void Character::setup(){
    
    GameObject::setup();
    
    decidePreferences();
    
    FADING_IN = false;
    FADING_OUT = false;
    LEFT_STORE = false;
    SPEAKING = false;
    TURNING_UP_NOSE = false;
    LICKING_LIPS = false;
    PLEASED_WITH_DISH = false;
    maxSpeechTimer = 3;
    speechTimer = maxSpeechTimer;
    
    EATING = false;
    eatTime = 0;
    maxEatTime = 1;
    
    currentRequest = 0;
    
    alpha = 0;
    
    anim = charIdleAnim;
}

void Character::enter()
{
    currentDialogue = greetings[int(ofRandom(greetings.size()-1))];
    changeAnim(charIdleAnim);
    FADING_IN = true;
}

void Character::speak(animation_t _anim)
{
    SPEAKING = true;
    speechTimer = maxSpeechTimer;
    if(currentDialogue.length() > 35)
    {
        currentDialogue.insert(currentDialogue.find(" ",35)+1, "\n");
    }
    changeAnim(_anim);
}

void Character::changeAnim(animation_t _anim)
{
    GameObject::changeAnim(_anim);
    
    anim.index += spriteSheetID * 13;
    
}

void Character::update(){
    GameObject::update();
    
    if (FADING_IN)
    {
        if (alpha < 240)
        {
            alpha += int(.1 * (255-alpha));
        }
        else
        {
            FADING_IN = false;
            makeRequest();
            alpha = 255;
        }
    }
    else if (FADING_OUT)
    {
        if (alpha > 5)
        {
            alpha -= (.75 * alpha);
        } else
        {
            alpha = 0;
            FADING_OUT = false;
            LEFT_STORE = true;
        }
    }
    
    if (SPEAKING)
    {
        if (speechTimer > 0)
        {
            speechTimer -= 1/ofGetFrameRate();
        }
        else
        {
            SPEAKING = false;
            TURNING_UP_NOSE = false;
            LICKING_LIPS = false;
            changeAnim(charIdleAnim);
        }
    }
    
    if (EATING)
    {
        if (eatTime > 0)
        {
            eatTime -= 1/ofGetFrameRate();
        }
        else
        {
            EATING = false;
            eatTime = 0;
            assessDish(beingEaten);
        }
    }
    
    mouthPos = pos;
    
}

void Character::prepareToEat()
{
    changeAnim(canEatAnim);
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
    
       
    
}

void Character::eat(Dish * d)
{
    EATING = true;
    eatTime = maxEatTime;
    beingEaten = d;
    
    /// HERE WE CAN ADD DIFFERENT EAT ANIMATIONS BASED ON WHETHER OR NOT THE DISH IS SOMETHING THE CHARACTER IS DOWN WITH
    changeAnim(eatAnim);
    
}

void Character::assessIngredient(Ingredient *_i)
{
    changeAnim(eatAnim);
    
}

void Character::assessDish(Dish *_d)
{
//    dishImpressions = "";
//    PLEASED_WITH_DISH = true;
//    bool PLEASED_WITH_FLAVOR = false;
//    bool PLEASED_WITH_FORM = false;
//    bool PLEASED_WITH_CONTENTS = false;
//    bool PLEASED_WITH_BALANCE = false;
//    
//    if (WANTS_FLAVOR)
//    {
//        if (desiredFlavor == "sweet")
//        {
//            if (_d->sweetness == _d->prominentFlavor)
//            {
//                PLEASED_WITH_FLAVOR = true;
//            }
//        }
//         else if (desiredFlavor == "salty")
//        {
//            if (_d->saltiness == _d->prominentFlavor)
//            {
//                PLEASED_WITH_FLAVOR = true;
//            }
//        }
//         else if (desiredFlavor == "sour")
//        {
//            if (_d->sourness == _d->prominentFlavor)
//            {
//                PLEASED_WITH_FLAVOR = true;
//            }
//        }
//         else if (desiredFlavor == "fatty")
//        {
//            if (_d->fattiness == _d->prominentFlavor)
//            {
//                PLEASED_WITH_FLAVOR = true;
//            }
//        }
//          else if (desiredFlavor == "bitter")
//        {
//            if (_d->bitterness == _d->prominentFlavor)
//            {
//                PLEASED_WITH_FLAVOR = true;
//            }
//        }
//           else if (desiredFlavor == "umami")
//        {
//            if (_d->umami == _d->prominentFlavor)
//            {
//                PLEASED_WITH_FLAVOR = true;
//            }
//        }
//        if (!PLEASED_WITH_FLAVOR)
//        {
//            PLEASED_WITH_DISH = false;
//            dishImpressions += "It's not " + desiredFlavor + " enough!\n";
//        }
//        else
//        {
//            dishImpressions += "Nice and " + desiredFlavor + "!\n";
//        }
//    }
//    
//    if (WANTS_BALANCE)
//    {
//        if (_d->complexity < 3)
//        {
//            PLEASED_WITH_DISH = false;
//            dishImpressions += "This dish is too simple.\n";
//        }
//        
//        if (_d->balance < 80)
//        {
//            PLEASED_WITH_DISH = false;
//            dishImpressions += "It's not balanced!\n";
//        }
//    }
//    
//    if (WANTS_FORM)
//    {
//        if (WANTS_SOUP)
//        {
//            if (!_d->HAS_BROTH)
//            {
//                PLEASED_WITH_DISH = false;
//                dishImpressions += "I wanted soup!\n";
//            }
//        }
//        if (WANTS_NOODLES)
//        {
//            bool hasNoodles = false;
//            for (int b = 0; b < _d->baseCount;b++)
//            {
//                if (_d->base[b]->form == NOODLES)
//                {
//                    hasNoodles = true;
//                    string noodleType = _d->base[b]->type;
//                    dishImpressions += "Mmm! My " + noodleType + "!\n";
//                }
//            }
//            if (!hasNoodles)
//            {
//                PLEASED_WITH_DISH = false;
//                dishImpressions += "I wanted noodles!\n";
//            }
//        }
//        if (WANTS_GRAINS)
//        {
//            bool hasGrains = false;
//            for (int b = 0; b < _d->baseCount;b++)
//            {
//                if (_d->base[b]->form == GRAINS)
//                {
//                    hasGrains = true;
//                    string grainType = _d->base[b]->type;
//                    dishImpressions += "The " + grainType + " makes for a nice grain.\n";
//                }
//            }
//            if (!hasGrains)
//            {
//                PLEASED_WITH_DISH = false;
//                dishImpressions += "I wanted grains!\n";
//            }
//
//        }
//    }
//    
//    if (WANTS_INGREDIENT)
//    {
//        if (!_d->CONTAINS(desiredIngredientType))
//        {
//            PLEASED_WITH_DISH = false;
//            dishImpressions += "Didn't you hear me say I wanted " + desiredIngredientType + "?\n";
//        }
//        else
//        {
//            dishImpressions += "I really do love " + desiredIngredientType + ".\n";
//        }
//    }
    
    
    if (beingEaten->displayName == requests[currentRequest]
        || (beingEaten->HAS_SUBDISH && beingEaten->subdish->type == requests[currentRequest]))
    {
        cout << "CURRENT REQUEST IS " + requests[currentRequest] + "\n";
        PLEASED_WITH_DISH = true;
    }
    else
    {
        PLEASED_WITH_DISH = false;
    }
    
    if (PLEASED_WITH_DISH)
    {
        currentDialogue = "This will do just fine!";
        // here we can have a happy speak anim.
        if (currentRequest < requests.size()-1)
        {
            currentRequest ++;
            makeRequest();
            speak(charTalkAnim);
        }
        else
        {
            leave();
        }
    }
    else
    {
        currentDialogue = "I wanted " + requests[currentRequest] + "! This is no good.";
        // here we can have an unhappy speak anim.
        speak(charTalkAnim);
    }
}

void Character::turnUpNose()
{
    if (!TURNING_UP_NOSE)
    {
        if(badSmellDialogues.size() > 0)
        {
            currentDialogue = badSmellDialogues[int(ofRandom(badSmellDialogues.size()))];
            speak(disgustTalkAnim);
        }
        else
        {
            changeAnim(disgustAnim);
        }
        TURNING_UP_NOSE = true;
    }
}

void Character::lickLips()
{
    if (!LICKING_LIPS)
    {
        if (niceSmellDialogues.size()>0)
        {
            currentDialogue = niceSmellDialogues[int(ofRandom(niceSmellDialogues.size()))];
            speak(salivateTalkAnim);
        }
        else
        {
            changeAnim(salivateAnim);
        }
        LICKING_LIPS = true;
    }
    
}

void Character::addRequest(string _requestText)
{
    requests.push_back(_requestText);
}

void Character::makeRequest()
{
    currentDialogue += "I think I'll have " + requests[currentRequest];
    speak(charTalkAnim);
}

void Character::leave()
{
    FADING_OUT = true;
}

void Character::draw(){
    
    
    
}

void Character::addSpriteToRenderer()
{
    testApp * app = (testApp *)ofGetAppPtr();
    
    app->game.characterRenderer->addCenterRotatedTile(&anim, pos.x, pos.y, 0, F_NONE, drawScale, angle, NULL, 255,255,255,alpha);
}