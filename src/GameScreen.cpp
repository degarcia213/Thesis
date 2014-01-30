#include "GameScreen.h"

GameScreen::GameScreen():Screen()
{
    
}

GameScreen::GameScreen(TimeHandler * _time):Screen(_time)
{
    
}


//--------------------------------------------------------------
void GameScreen::setup(){
    
    Screen::setup();
    
    // weird system bs
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
    // GAME STATE
    
    VIEW = GAME;
    WON = false;
    
    GRINDING = false;
    HOLDING_INGREDIENT = false;
    
    cash = 0;
    rating = 100;
    
    bg.loadImage("bg.png");
    
    SHAKING = false;
    shakeTimer = 20;
    shakeMod.set(0,0);
    
    foodRenderer = new ofxSpriteSheetRenderer(1,1000,0,26);
    foodRenderer -> loadTexture("rice_sheet.png", 234, GL_NEAREST);
    
    // INITIALIZE TOOLS
    
    
    tableWidth = ofGetWidth()/4 * 3;
    tableHeight = 400;
    tablePos.set(0,200);
    pantryPos.set(tablePos.x + tableWidth,tablePos.y);
    
    trash.set(100, tablePos.y + tableHeight + 100);
    
    grill.set(100, tablePos.y + 250);
    grinder.set(100, tablePos.y + 50);
    bowl.set(100,tablePos.y + 150);
    finalPlate.set(100,tablePos.y + 350);
    
    grillRange = 50;
    bowlRange = 50;
    grindRange = 50;
    plateRange = 50;
    
    
    bookPos.set(750,ofGetHeight()-300);
    bookWidth = 50;
    bookHeight = 70;
    

    ofFile pantryContentList;
    pantryContentList.open("ingredientsObtained.txt");
    pantryContents = pantryContentList.readToBuffer();
    pantryContentList.close();
    
    setupPantry();
    
    recipeList.open("dishes.txt");
    knownList.open("knownRecipes.txt");
    knownRecipes = knownList.readToBuffer();
    allRecipes = recipeList.readToBuffer();
    knownList.close();
    recipeList.close();
    
    setupRecipeBook();
    
    importCharacters();
    
    
    // Initialize customer
    
    customerWidth = 50;
    customerHeight = 75;
    headSize = 25;
    customerBody.set(150, tablePos.y - customerHeight);
    customerHead.set(customerBody.x + .5 * customerWidth, customerBody.y - headSize);
    customerName = "Franke Glannts";
    int randomizer = int(ofRandom(desires.size()));
    customerDesire = desires[randomizer];
    
    customerTimer = Timer(10);
    customerTimer.activate();
    
    nextCustomerTimer = Timer(120);
    
    
    //organize Animations
    
    anims["uncooked rice"] = uncookedRice;
    anims["browned rice"] = brownedRice;
    anims["lightly boiled rice"] = lightlyBoiledRice;
    anims["barely boiled rice"] = lightlyBoiledRice;
    anims["boiled rice"] = boiledRice;
    anims["soggy rice"] = soggyRice;
    anims["crunchy bottom rice"] = crunchyRice;
    anims["ruined ingredient"] = ruined;
    
}

void GameScreen::importCharacters()
{
    ofFile charFile;
    charFile.open("characters.xml");
    ofBuffer buf = charFile.readToBuffer();
    
    ofXml characterList;
    
    characterList.loadFromBuffer(buf);
    characterList.setTo("characters");
    
    int totalChars = characterList.getNumChildren();
    
    for (int i = 0; i < totalChars; i++)
    {
        Character newChar = Character(i);
        characterList.setToChild(i);
        newChar.name = characterList.getAttribute("@name");
        characterList.setTo("desire");
        newChar.desire = characterList.getValue();
        cout << newChar.name + "\n";
        characters.push_back(&newChar);
    }
}

void GameScreen::enterCustomer(int _id)
{
 
    customerInStore = characters[_id];
    
}

void GameScreen::setupRecipeBook(){
    
    recipeBook.clear();
    string currentLine = allRecipes.getFirstLine();
    string knownLine = knownRecipes.getFirstLine();
    while (!allRecipes.isLastLine()){
        bool found = false;
        while (!knownRecipes.isLastLine()){
            if (currentLine.substr(currentLine.find("= ")+2,currentLine.length()-1) == knownLine){
                recipeBook += currentLine + "\n";
                desires.push_back(currentLine.substr(currentLine.find("= ")+2,currentLine.length()-1));
                found = true;
                break;
            }
            knownLine = knownRecipes.getNextLine();
        }
        if (found == false){
            recipeBook += "????\n";
        }
        knownLine = knownRecipes.getFirstLine();
        currentLine = allRecipes.getNextLine();
    }
}

//// --- NOW LET'S MAKE INGREDIENT SPAWNERS!!

void GameScreen::setupPantry(){
    
    // iterate through list of known ingredients
    // add to vector of types, in draw() we'll draw them in the pantry based on their position in the vector.
    
    pantry.clear();
    
    string currentLine = pantryContents.getFirstLine();
    
    while (!pantryContents.isLastLine()) {
        pantry.push_back(currentLine);
        currentLine = pantryContents.getNextLine();
    }
    
    
    
    
    
    
}

//--------------------------------------------------------------
void GameScreen::update(){
    
    Screen::update();
    
    foodRenderer->clear();
    foodRenderer->update(ofGetElapsedTimeMillis());
    
    // --- BY FRAME MANIPULATION OF INGREDIENTS ON SCREEN
    for (int i = 0;i<ingredients.size();i++){
        
        if (ingredients[i]->type == "removeMe"){
            ingredients.erase(ingredients.begin() + i);
        }
        
        if (ingredients[i]->BEINGHELD == false){
            if (ingredients[i]->pos.distance(grill) < grillRange){
                ingredients[i]->grillTime += 1;
            } else if (ingredients[i]->pos.distance(grinder) < grindRange && GRINDING){
                ingredients[i]->grindTime += 1;
            } else if (ingredients[i]->pos.distance(bowl) < bowlRange){
                ingredients[i]->boilTime += 1;
            } else if (ingredients[i]->pos.distance(trash) < grillRange){
                ingredients[i]->type = "removeMe";
            }
        }
        
        if (ingredients[i]->type == customerDesire){
            WON = true;
        }
        
        ingredients[i]->anim = anims[ingredients[i]->type];
        
        foodRenderer->addCenteredTile(&ingredients[i]->anim, ingredients[i]->pos.x, ingredients[i]->pos.y,0,F_NONE,3,255,255,255,255);
        
        ingredients[i]->update();
    }
    
    if (GRINDING){
        SHAKING = true;
    } else {
        SHAKING = false;
        shakeMod.set(0,0);
    }
    
    if (SHAKING){
        shakeMod.interpolate(shakeDest, .75);
        //shakeTimer --;
        if (shakeMod.distance(shakeDest)<1){
            shakeDest.set(ofRandom(-shakeDampener,shakeDampener),ofRandom(-shakeDampener,shakeDampener));
        }
        if (shakeTimer <= 0){
            SHAKING = false;
            shakeMod.set(0,0);
        }
    }
    
    customerTimer.update();
    nextCustomerTimer.update();
    
}

//--------------------------------------------------------------
void GameScreen::draw(){
    
    Screen::draw();
    
    customerTimer.draw();
    nextCustomerTimer.draw();
    
    ofSetColor(0, 255, 255);
    ofDrawBitmapString("Money: " + ofToString(cash), 20,60);
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    
    if (VIEW == RECIPES){
        ofDrawBitmapString(recipeBook, ofPoint(50,50));
        
        ofRect(bookPos.x , bookPos.y, bookWidth, bookHeight);
        ofDrawBitmapString("back", bookPos.x + shakeMod.x,bookPos.y + bookHeight/2 + shakeMod.y);
        
    } else if (VIEW == GAME){
        //ofSetColor(255,255,255);
        bg.draw(ofPoint(0,0));
        
        // --- DRAW STUFF FOR INGREDIENTS
        for (int i = 0;i<ingredients.size();i++){
            ingredients[i]->draw(shakeMod.x,shakeMod.y);
        }
        
        foodRenderer->draw();
        
        ofRect(tablePos.x + shakeMod.x, tablePos.y+ shakeMod.y, tableWidth, tableHeight);
        ofRect(pantryPos.x + shakeMod.x, pantryPos.y + shakeMod.y, 300, tableHeight);
        ofDrawBitmapString("PANTRY", pantryPos.x + shakeMod.x + 150,pantryPos.y + shakeMod.y + tableHeight + 20);
        
        // --- DRAW TOOLS
        //ofDrawBitmapString("You'd better give the customer what he wants.\nCheck the recipe book if you're not sure.\nPress 'r' to reset.", 400,20);
        
        ofCircle(finalPlate.x + shakeMod.x, finalPlate.y + shakeMod.y, plateRange);
        ofDrawBitmapString("Place items here to combine. Pay attention to order of placement.", finalPlate+ shakeMod);
        ofCircle(grinder.x + shakeMod.x, grinder.y + shakeMod.y, grindRange);
        ofDrawBitmapString("Place items here for grinding, click elsewhere in the grinder and drag to grind.", grinder+ shakeMod);
        ofCircle(bowl.x + shakeMod.x, bowl.y + shakeMod.y, bowlRange);
        ofDrawBitmapString("Place items to boil in water.", bowl+ shakeMod);
        ofCircle(grill.x + shakeMod.x, grill.y + shakeMod.y, grillRange);
        ofDrawBitmapString("Place items to grill.", grill + shakeMod);
        ofCircle(trash.x + shakeMod.x,trash.y + shakeMod.y,grillRange);
        ofDrawBitmapString("Throw items away here.", trash + shakeMod);
        
        ofRect(bookPos.x + shakeMod.x, bookPos.y + shakeMod.y, bookWidth, bookHeight);
        ofDrawBitmapString("recipe\nbook", bookPos.x,bookPos.y + bookHeight/2);
        
        // --- DRAW CUSTOMER
        ofCircle(customerHead.x + shakeMod.x, customerHead.y + shakeMod.y, headSize);
        ofRect(customerBody.x + shakeMod.x, customerBody.y + shakeMod.y, customerWidth, customerHeight);
        if (!WON){
            ofDrawBitmapString("I'm " + customerName + " and I want " + customerDesire + ".", ofPoint(customerHead.x + headSize + 40,customerHead.y));
        } else {
            ofDrawBitmapString("Yeah. That's good. I Like that. That's a WINNER.", ofPoint(customerHead.x + headSize + 40,customerHead.y));
            
        }
        
        // -- DRAW PANTRY CONTENTS
        for (int i = 0; i < pantry.size(); i++){
            ofPoint newDrawPos = ofPoint(pantryPos.x + 50 + (120 * int (i/8)), pantryPos.y + 50 + (50 * i));
            ofDrawBitmapString(pantry[i], newDrawPos.x - 20,newDrawPos.y);
            ofCircle(newDrawPos,20);
        }
        
    }
    
    if (ofGetKeyPressed()){
        ofDrawBitmapString(knownRecipes, 50,50);
    }
    
}

void GameScreen::addToPantry(string _ingredient){
    
    string currentPantryContents = pantryContents.getText();
    currentPantryContents.erase(currentPantryContents.find("<"),currentPantryContents.find(">"));
    currentPantryContents.append(_ingredient + "\n");
    currentPantryContents.append("<--- LAST --->");
    pantryContents.set(currentPantryContents);
    setupPantry();
    
}

void GameScreen::checkRecipes(){
    
    recipeList.open("dishes.txt");
    ofBuffer recipeText = recipeList.readToBuffer();
    string currentLine = recipeText.getFirstLine();
    std::string realRecipe = currentLine;
    string recipe = plateContents[0]->type;
    for (int i = 1; i < plateContents.size();i++){
        recipe += " + " + plateContents[i]->type;
    }
    
    realRecipe = currentLine.substr(0,currentLine.find(" ="));
    
    while (recipe != realRecipe){
        if (recipeText.isLastLine()){
            cout << "this isn't a recipe";
            break;
        } else {
            cout << realRecipe + "\n";
            currentLine = recipeText.getNextLine();
            realRecipe = currentLine.substr(0,currentLine.find(" ="));
        }
    }
    
    if (recipe == realRecipe){
        
        string resultingDish = currentLine.substr(currentLine.find(" = ")+3,currentLine.length()-1);
        
        for (int i = 0; i < plateContents.size();i++){
            for (int j = 0; j< ingredients.size();j++){
                if (ingredients[j] == plateContents[i]){
                    ingredients.erase(ingredients.begin() + j);
                }
            }
        }
        ofVec2f newPos = plateContents[0]->pos;
        plateContents.clear();
        ingredients.push_back(new Ingredient(resultingDish,newPos.x,newPos.y));
        plateContents.push_back(ingredients[ingredients.size()-1]);
        bool alreadyKnown = false;
        string knownLine = knownRecipes.getFirstLine();
        while (!knownRecipes.isLastLine()){
            cout << "KNOWN LINE: " + knownLine + "\n" + "RESULTING DISH: " + resultingDish + "\n";
            if (knownLine == resultingDish){
                alreadyKnown = true;
                break;
            }
            knownRecipes.getNextLine();
        }
        if (!alreadyKnown){
            string currentRecipeList = knownRecipes.getText();
            currentRecipeList.erase(currentRecipeList.find("<"),currentRecipeList.find(">"));
            currentRecipeList.append(resultingDish +"\n");
            currentRecipeList.append("<--- LAST --->");
            knownRecipes.set(currentRecipeList);
            setupRecipeBook();
        }
        
    };
    
    recipeList.close();
    
    
}

//--------------------------------------------------------------
void GameScreen::keyPressed(int key){
    
    Screen::keyPressed(key);
    
    if (key == 'r'){
        reset();
    }
    
    if (key == 's'){
        shakeDest.set(ofRandom(-5,5),ofRandom(-5,5));
        shakeTimer = 20;
        SHAKING = true;
    }
    
    if (key == ' '){
        addToPantry("glow worms");
    }
    
}

void GameScreen::reset(){
    ingredients.clear();
    plateContents.clear();
    ingredients.push_back(new Ingredient("uncooked rice", ofGetWidth() - 200, tablePos.y + 30));
    ingredients.push_back(new Ingredient("green tea leaves",ofGetWidth() - 200,tablePos.y + 100));
    ingredients.push_back(new Ingredient("sesame seeds",ofGetWidth() - 250,tablePos.y + 50));
    ingredients.push_back(new Ingredient("red beans",ofGetWidth() - 250,tablePos.y + 120));
    ingredients.push_back(new Ingredient("sugar",ofGetWidth() - 300,tablePos.y + 70));
    
    int randomizer = int(ofRandom(desires.size()));
    customerDesire = desires[randomizer];
    
    WON = false;
}

//--------------------------------------------------------------
void GameScreen::keyReleased(int key){
    Screen::keyReleased(key);
    
}

//--------------------------------------------------------------
void GameScreen::mouseMoved(int x, int y ){
    
    Screen::mouseMoved(x, y);
    
    if (!GRINDING){
        prevMousePos.set(x,y);
    }
    
}

//--------------------------------------------------------------
void GameScreen::mouseDragged(int x, int y, int button){
    
    Screen::mouseDragged(x, y, button);
    
    for(int i = 0; i < ingredients.size();i++){
        if (ingredients[i]->BEINGHELD == true){
            ofVec2f newPos;
            newPos.set(x + ingredients[i]->offset.x,y+ingredients[i]->offset.y);
            ingredients[i]->pos.set(newPos);
        }
    }
    
    if (VIEW == GAME){
        if (ofPoint(x,y).distance(grinder)<grindRange && !HOLDING_INGREDIENT){
            GRINDING = true;
            shakeDampener = ofPoint(x,y).distance(prevMousePos)/10 * 5;
            
        } else {
            GRINDING = false;
        }
    }
    
    prevMousePos.set(x,y);
    
}

//--------------------------------------------------------------
void GameScreen::mousePressed(int x, int y, int button){
    
    Screen::mousePressed(x, y, button);
    
    if (VIEW == GAME){
        for(int i = 0; i < ingredients.size();i++){
            if (ingredients[i]->pos.distance(ofPoint(x,y))<20){
                ingredients[i]->BEINGHELD = true;
                HOLDING_INGREDIENT = true;
                ingredients[i]->offset.set(ingredients[i]->pos - ofPoint(x,y));
                if(ingredients[i]->pos.distance(finalPlate) < plateRange){
                    for (int j = 0;j < plateContents.size();j++){
                        if(ingredients[i]->type == plateContents[j]->type){
                            plateContents.erase(plateContents.begin()+j);
                        }
                    }
                }
            }
        }
        if (!HOLDING_INGREDIENT){
            if (x > bookPos.x && y > bookPos.y && x < bookPos.x + bookWidth && y < bookPos.y + bookHeight){
                VIEW = RECIPES;
            }
            for (int i = 0;i<pantry.size();i++){
                if (ofPoint(x,y).distance(ofPoint(pantryPos.x + 50 + (120 * int (i/8)), pantryPos.y + 50 + (50 * i)))<20){
                    ingredients.push_back(new Ingredient(pantry[i],x,y));
                    ingredients[ingredients.size()-1]->BEINGHELD = true;
                    HOLDING_INGREDIENT = true;
                }
            }
        }
    } else if (VIEW == RECIPES){
        if (x > bookPos.x && y > bookPos.y && x < bookPos.x + bookWidth && y < bookPos.y + bookHeight){
            VIEW = GAME;
        }
    }
    
}

//--------------------------------------------------------------
void GameScreen::mouseReleased(int x, int y, int button){
    
    Screen::mouseReleased(x, y, button);
    
    if (VIEW == GAME) {
        for(int i = 0; i < ingredients.size();i++){
            if (ingredients[i]->BEINGHELD == true){
                ingredients[i]->BEINGHELD = false;
                if (ingredients[i]->pos.distance(finalPlate)<plateRange){
                    plateContents.push_back(ingredients[i]);
                    
                    if (plateContents.size() > 1){
                        checkRecipes();
                    }
                }
            }
        }
    }
    
    GRINDING = false;
    HOLDING_INGREDIENT = false;
}

//--------------------------------------------------------------
void GameScreen::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void GameScreen::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void GameScreen::dragEvent(ofDragInfo dragInfo){ 
    
}