//
//  Ingredient.cpp
//  Combining
//
//  Created by Diego Garcia on 10/22/13.
//
//

#include "Ingredient.h"
#include <fstream>
#include "testApp.h"


Ingredient::Ingredient():GameObject(){
    //setup();
}

Ingredient::Ingredient(string _type, int x, int y):GameObject(x,y){
    type = _type;
    cout << type + "\n";
    setup();
}

void Ingredient::setup(){
    
    GameObject::setup();
    
    drawScale = 2;
    
    /// ESTABLISH FORMS MAP
    
    forms["slab"] = SLAB;
    forms["sliced"] = SLICED;
    forms["cubes"] = CUBES;
    forms["grains"] = GRAINS;
    forms["noodles"] = NOODLES;
    forms["paste"] = PASTE;
    forms["powder"] = POWDER;
    forms["puree"] = PUREE;
    forms["syrup"] = SYRUP;
    forms["liquid"] = LIQUID;
    forms["broth"] = BROTH;
    forms["garnish"] = GARNISH;
    forms["dough"] = DOUGH;
    
    HOLDABLE = true;
    HELD = false;
    CAN_BE_BASE = false;
    USED_IN_SUBDISH = false;
    size = 20;
    
    getIngredientInfo();
    
    // sprites have no offset from mouse because they're not being held
    offset.set(0,0);
    

    
    
    
}

void Ingredient::update(){
    
    GameObject::update();
    
    if (grillTime >= 200){
        type = whenGrilled;
        getIngredientInfo();
        displayName = type;
        spawnDisplay(displayName);
    }
    
    if (boilTime >= 200){
        type = whenBoiled;
        getIngredientInfo();
        displayName = type;
        spawnDisplay(displayName);
    }
    
    if (grindTime >= 200){
        type = whenGround;
        getIngredientInfo();
        displayName = type;
        spawnDisplay(displayName);
    }
    
    
    if (form == POWDER || form == SYRUP || form == GARNISH || form == PASTE)
    {
        CAN_BE_BASE = false;
    }
    
    displayName = type;
    
    testApp * app = (testApp *)ofGetAppPtr();
    anim = app->game.anims[type];
    
}

    /// --- ESTABLISH INGREDIENT TYPE AND RESULTS

void Ingredient::getIngredientInfo(){
    
    ingList.open("ingredients2.txt");
    ofBuffer ingredientList = ingList.readToBuffer();
    string currentLine = ingredientList.getFirstLine();
    std::string lineString = currentLine;
    string thisLineType = "";
    int pos = 1;
    thisLineType = currentLine.substr(0,currentLine.find(", "));
    while(type != thisLineType){
        if (!ingredientList.isLastLine()){
            currentLine = ingredientList.getNextLine();
            thisLineType = currentLine.substr(0,currentLine.find(", "));
        } else {
            cout << "this was left out of the ingredient list. Prepare to crash.";
            break;
        }
    }
    
    //type = currentLine.substr(currentLine.find(type),type.length());
    
    int startPos = currentLine.find(", ");
    int endPos = currentLine.find(", ", startPos+1);
    whenGrilled = currentLine.substr(startPos+2,endPos-startPos-2);
    
    int endPos2 = currentLine.find(", ", endPos+1);
    whenBoiled = currentLine.substr(endPos+2,endPos2-endPos-2);
    
    int endPos3 = currentLine.find(", ", endPos2+1);
    whenGround = currentLine.substr(endPos2+2,endPos3-endPos2-2);
    
    int endPos4 = currentLine.find(", ", endPos3+1);
    sweetness = ofToInt(currentLine.substr(endPos3+2,endPos4-endPos3-2));
    
    int endPos5 = currentLine.find(", ", endPos4+1);
    saltiness = ofToInt(currentLine.substr(endPos4+2,endPos5-endPos4-2));
    
    int endPos6 = currentLine.find(", ", endPos5+1);
    sourness = ofToInt(currentLine.substr(endPos5+2,endPos6-endPos5-2));
    
    int endPos7 = currentLine.find(", ", endPos6+1);
    fattiness = ofToInt(currentLine.substr(endPos6+2,endPos7-endPos6-2));
    
    int endPos8 = currentLine.find(", ", endPos7+1);
    bitterness = ofToInt(currentLine.substr(endPos7+2,endPos8-endPos7-2));
    
    int endPos9 = currentLine.find(", ", endPos8+1);
    umami = ofToInt(currentLine.substr(endPos8+2,endPos9-endPos8-2));
    
    int endPos10 = currentLine.find(", ", endPos9+1);
    form = forms[currentLine.substr(endPos9+2,endPos8-endPos9-2)];
    
    ingList.close();
    
    grindTime = 0;
    grillTime = 0;
    boilTime = 0;
    sitTime = 0;
    
    if (form == SLAB || form == SLICED || form == CUBES || form == NOODLES || form == BROTH || form == GRAINS)
    {
        CAN_BE_BASE = true;
    }
    
    
    
}

void Ingredient::draw(int modx, int mody){
    
    //ofNoFill();
    //ofSetColor(0, 0, 0);
   // ofCircle(pos.x + modx, pos.y + mody, size);
   ofDrawBitmapString(type, pos.x + modx,pos.y + mody);
    
}
