#pragma once

#include "Screen.h"
#include "Ingredient.h"
#include "ofxSpriteSheetRenderer.h"
#include "Timer.h"
#include "Character.h"

enum viewType{
    GAME,
    RECIPES,
    INGREDIENTS,
};

class GameScreen : public Screen{
    
public:
    
    GameScreen();
    GameScreen(TimeHandler * _time);
    
    virtual void setup();
    virtual void update();
    virtual void draw();
    
    void enterCustomer(int _id);
    
    void importCharacters();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVec2f shakeMod;
    ofVec2f shakeDest;
    int shakeDampener;
    int shakeTimer;
    bool SHAKING;
    
    bool GRINDING;
    bool HOLDING_INGREDIENT;
    
    vector <Ingredient *> ingredients;
    vector <Character *> characters;
    
    Character * customerInStore;
    
    Timer customerTimer;
    Timer nextCustomerTimer;
    
    void reset();
    
    void setupPantry();
    void addToPantry(string _ingredient);
    
    void checkRecipes();
    ofFile recipeList;
    ofFile knownList;
    
    // -- drawing stuff
    ofImage bg;
    
    ofPoint tablePos;
    int tableWidth;
    int tableHeight;
    
    ofxSpriteSheetRenderer * foodRenderer;
    map <string,animation_t> anims;
    
    
    // RECIPE BOOK STUFF
    ofPoint bookPos;
    ofPoint backBtn;
    int bookWidth;
    int bookHeight;
    string recipeBook;
    vector <string> recipes;
    vector <string> desires;
    
    
    viewType VIEW;
    bool WON;
    
    void setupRecipeBook();
    ofBuffer allRecipes;
    ofBuffer knownRecipes;
    
    // PANTRY
    ofBuffer pantryContents;
    vector <string> pantry;
    ofPoint pantryPos;
    
    //--Customer
    
    ofPoint customerHead;
    ofPoint customerBody;
    int customerHeight;
    int customerWidth;
    int headSize;
    string customerName;
    string customerDesire;
    
    //--TIMER
    
    
    //TRASH
    ofPoint trash;
    
    
    //GRILL
    ofPoint grill;
    int grillRange;
    
    //BOWL
    ofPoint bowl;
    int bowlRange;
    
    
    //GRINDER
    ofPoint grinder;
    int grindRange;
    
    ofPoint prevMousePos;
    
    
    //FINAL PLATE
    ofPoint finalPlate;
    int plateRange;
    vector <Ingredient *> plateContents;
    
    //ECONOMY STUFF
    int cash;
    
    int rating;
    
};

