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
    
    getIngredientInfo();
    
    BEINGHELD = false;
    
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
    
}

    /// --- ESTABLISH INGREDIENT TYPE AND RESULTS

void Ingredient::getIngredientInfo(){
    
    ingList.open("ingredients.txt");
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
