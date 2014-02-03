//
//  Ingredient.cpp
//  Combining
//
//  Created by Diego Garcia on 10/22/13.
//
//

#include "Ingredient.h"
#include <fstream>


Ingredient::Ingredient(){
    //setup();
}

Ingredient::Ingredient(string _type, int x, int y){
    type = _type;
    pos.set(x,y);
    cout << type + "\n";
    setup();
}

void Ingredient::setup(){
    
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
    
    getIngredientInfo();
    
    BEINGHELD = false;
    CAN_BE_BASE = true;
    
    // sprites have no offset from mouse because they're not being held
    offset.set(0,0);
    
    
    
}

void Ingredient::update(){
    
    if (grillTime >= 200){
        type = whenGrilled;
        getIngredientInfo();
    }
    
    if (boilTime >= 200){
        type = whenBoiled;
        getIngredientInfo();
    }
    
    if (grindTime >= 200){
        type = whenGround;
        getIngredientInfo();
    }
    
    
    if (form == POWDER || form == SYRUP || form == GARNISH || form == PASTE)
    {
        CAN_BE_BASE = false;
    } else {
        CAN_BE_BASE = true;
    }
    
}

    /// --- ESTABLISH INGREDIENT TYPE AND RESULTS

void Ingredient::getIngredientInfo(){
    
    ingList.open("ingredients2.txt");
    ofBuffer ingredientList = ingList.readToBuffer();
    string currentLine = ingredientList.getFirstLine();
    std::string lineString = currentLine;
    int pos = 1;
    while(ofIsStringInString(currentLine, type) == false){
        while (currentLine.find(type)!=0){
            if (!ingredientList.isLastLine()){
            currentLine = ingredientList.getNextLine();
            } else {
                cout << "this was left out of the ingredient list. Prepare to crash.";
                break;
            }
        }
    }
    
    type = currentLine.substr(currentLine.find(type),type.length());
    
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
    
    
    
}

void Ingredient::draw(int modx, int mody){
    
    name = state + " " + type;
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofCircle(pos.x + modx, pos.y + mody, 20);
    ofDrawBitmapString(type, pos.x + modx,pos.y + mody);
}
