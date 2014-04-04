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

static animation_t charIdleAnim =
{
    0,0,1,1,1,75,0,-1,-1,1
};

static animation_t charTalkAnim =
{
    1,0,2,1,1,75,0,-1,-1,1
};

static animation_t disgustTalkAnim =
{
    5,0,2,1,1,75,0,-1,-1,1
};

static animation_t disgustAnim =
{
    5,0,1,1,1,75,0,-1,-1,1
};

static animation_t salivateTalkAnim =
{
    1,0,3,1,1,75,0,-1,-1,1
};

static animation_t salivateAnim =
{
    3,0,1,1,1,75,0,-1,-1,1
};

static animation_t canEatAnim =
{
    7,0,1,1,1,75,0,-1,-1,1
};

static animation_t eatAnim =
{
    8,0,4,1,1,75,0,-1,-1,1
};

class Character : public GameObject{
public:
Character();
Character(int x, int y);
    
    void setup();
    void update();
    void draw();
    void addSpriteToRenderer();
    void speak(animation_t _anim);
    void changeAnim(animation_t _anim);
    void turnUpNose();
    void lickLips();
    void prepareToEat();
    
    void makeRequest();
    
    void eat(Dish * d);
    Dish * beingEaten;
    float eatTime;
    float maxEatTime;
    
    void leave();
    
    float speechTimer;
    float maxSpeechTimer;
    
    // HERE'S SOME BASIC STATE STUFF
    
    bool FADING_IN;
    bool FADING_OUT;
    bool LEFT_STORE;
    bool SPEAKING;
    bool TURNING_UP_NOSE;
    bool LICKING_LIPS;
    bool EATING;
    
    int alpha;
    int spriteSheetID;
    

    
    vector <string> greetings;
    vector <string> happyLeavingDialogues;
    vector <string> angryLeavingDialogues;
    vector <string> orderDialogues;
    vector <string> niceSmellDialogues;
    vector <string> badSmellDialogues;
    vector <string> goodDishDialogues;
    vector <string> badDishDialogues;
    
    vector <string> hates;
    vector <string> likes;
    
    int currentRequest;
    
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
    
    ofVec2f mouthPos;
    
    void decidePreferences();
    void enter();
    
    string desiredFlavor;
    
    FORMS DESIRED_FORM;
    string desiredForm;
    
    vector <string> requests;
    
    string desiredIngredientType;
    
    void assessDish(Dish * _d);
    void assessIngredient(Ingredient * _i);
    void addRequest(string _requestText);
    
    bool PLEASED_WITH_DISH;
    
    
    string dishImpressions;
    string rewardType;
    string ingredientReward;
    
    int cashAmt;
    
};

#endif /* defined(__Combining__Character__) */
