//
//  NameDisplay.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 3/12/14.
//
//

#ifndef __backToTheKitchen__NameDisplay__
#define __backToTheKitchen__NameDisplay__

#include <iostream>
#include "ofMain.h"

class NameDisplay : public ofTrueTypeFont
{public:
        NameDisplay();
        NameDisplay(int x, int y, string _name);
        
        string name;
    
    vector <char> characters;
    
    ofVec2f pos;
    
    void update();
    void draw();
    
    bool APPEARED;
    bool FADING;
    bool DEAD;
    
    float currentSize;
    
    float drawScale;
    
    float displayTimer;
    float timeToAppear;
    float timeDisplayed;
    float timeToFade;
        
};

#endif /* defined(__backToTheKitchen__NameDisplay__) */
