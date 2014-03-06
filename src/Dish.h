//
//  Dish.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/5/14.
//
//

#ifndef __backToTheKitchen__Dish__
#define __backToTheKitchen__Dish__
#define MAX_BASE_COUNT 2
#define MAX_GARNISH_COUNT 3

#include <iostream>
#include "ofMain.h"
#include "GameObject.h"
#include "Ingredient.h"

class Dish : public GameObject{
public:
    Dish();
    Dish(int x,int y);
    
    void setup();
    void update();
    void draw();
    
    bool SHOWING_CONTENTS;
    
    
    // --- CREATION STUFF
    string createName();
    
    void addIngredient(Ingredient * _i);
    void removeIngredient(int _ID);
    void checkForSubdish();
    bool CONTAINS(string _t);
    
    bool EXISTS;

    int baseCount;
    Ingredient * base[MAX_BASE_COUNT];

    bool HAS_BROTH;
    Ingredient * broth;

    int garnishCount;
    Ingredient * garnish[MAX_GARNISH_COUNT];
    
    bool HAS_SUBDISH;
    string subdish;
    
    string type;
    
    // --- FLAVOR STUFF
    
    int sweetness;
    int saltiness;
    int sourness;
    int fattiness;
    int bitterness;
    int umami;
    
    int prominentFlavor;
    
    void calculateBalance();
    
    int balance;
    int complexity;




};


#endif /* defined(__backToTheKitchen__Dish__) */
