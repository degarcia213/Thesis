#pragma once

#include "Screen.h"
#include "Ingredient.h"
#include "ofxSpriteSheetRenderer.h"
#include "Timer.h"
#include "Character.h"
#include "Dish.h"
#include "ServeBtn.h"
#include "Pot.h"
#include "Skillet.h"
#include "Grill.h"
#include "Grinder.h"
#include "Pestle.h"
#include "CuttingBoard.h"
#include "Sink.h"
#include "TrashCan.h"
#include "Plate.h"
#include "SpeechBubble.h"

enum viewType{
    GAME,
    RECIPES,
    INGREDIENTS,
    GRINDERVIEW,
    CUTTINGVIEW,
};

static animation_t overlayAnim =
{
    400,0,1,1,1,75,0,-1,-1,1
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
    
    void updateIngredientsAndAddToScreen();
    
    int selectTimer;
    int selectTime;
    bool CONSIDERING_SELECTION;

    
    void addIngredient(string _type, int x, int y);
    
    bool pointOverlaps(ofVec2f _p, GameObject _obj);
    bool pointOverlaps(ofVec2f _p, ofVec2f _rectPos, int _rectWidth, int _rectHeight);
    
    ofVec2f shakeMod;
    ofVec2f shakeDest;
    int shakeDampener;
    int shakeTimer;
    bool SHAKING;
    
    bool GRINDING;
    bool HOLDING_INGREDIENT;
    
    vector <GameObject *> allElements;
    vector <Ingredient *> ingredients;
    vector <Character *> characters;
    
    Pestle pestle;
    
    
    Character * customerInStore;
    int currentCustomer;
    
    ofxSpriteSheetRenderer * characterRenderer;
    ofxSpriteSheetRenderer * speechBubbleRenderer;
    
    SpeechBubble speechBubble;
    
    Timer customerTimer;
    Timer nextCustomerTimer;
    
    void reset();
    
    int difficulty;
    
    void setupPantry();
    void addToPantry(string _ingredient);
    
    void checkRecipes(Dish * d);
    
    void combineDishes(Dish * d1, Dish * d2);
    
    ofFile recipeList;
    ofFile knownList;
    ofFile characterList;
    
    // -- drawing stuff
    ofImage bg;
    ofImage counterImg;
    ofImage cuttingBG;
    
    ofPoint tablePos;
    int tableWidth;
    int tableHeight;
    
    void loadImage(ofImage _image, string _imagePath, int _timesWidth, int _timesHeight);
    
    ofxSpriteSheetRenderer * mainRenderer;
    map <string,animation_t> anims;
    
    float drawScale;
    
    // UI ELEMENTS
    vector <SimpleButton *> buttons;
    vector <NameDisplay *> uiDisplayText;
    ServeBtn serveButton;
    void overlay(ofColor _color);
    
    
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
    vector <string> pantryContentsList;
    vector <Ingredient *> pantry;
    ofVec2f pantryPos[9];
    
    void addIngredient();
    
    int objID;
    
    //--Customer
    
    ofPoint customerHead;
    ofPoint customerBody;
    int customerHeight;
    int customerWidth;
    int headSize;
    
    void serveCustomer(Dish * _d);
    
    vector <string> customerNames;
    
    
    
    //--TIMER
    
    
    //TRASH
    
    TrashCan trash;
    
    // TOOLS HERE
    Pot pot;
    
    Skillet skillet;
    
    Grill grill;
    
    Grinder grinder;
    Ingredient * foodInGrinder;
    
    CuttingBoard cuttingBoard;
    Ingredient * foodOnBoard;
    
    Sink sink;
    void addWater();
    bool WATER_FLOWING;

    
    ////// --------- THIS STUFF IS OLD AND SHOULD BE DELETED ONCE NEW UI IS FUNCTIONAL
    //ofPoint grill;
    int grillRange;
    
    //BOWL
    ofPoint bowl;
    int bowlRange;
    
    ofPoint prevMousePos;
    
    
    //FINAL PLATE
    
    Plate plate;
    
    ofPoint finalPlate;
    int plateRange;
    vector <Ingredient *> plateContents;
    
    vector <Dish *> dishes;
    
    string dishInPlate;
    int dishSweetness;
    int dishSourness;
    int dishBitterness;
    int dishFattiness;
    int dishUmami;
    int dishSavory;
    
    //ECONOMY STUFF
    int cash;
    
    int rating;
    
};

