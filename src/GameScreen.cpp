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
    
    xTranslate = 0;
    yTranslate = 0;
    
    FGDamp = 8;
    MGDamp = 16;
    BGDamp = 24;
    
    drawScale = 2;
    
    // weird system bs
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
    mouseX = ofGetWidth()/2;
    lastMouseX = ofGetWidth()/2;
    
    mouseY = ofGetHeight()/2;
    lastMouseY = mouseY;
    
    heldObjPos.set(250 * drawScale, ofGetHeight()-(64*drawScale));
    
    // GAME STATE
    
    currentCustomer = 0;
    
    VIEW = GAME;
    WON = false;
    difficulty = false;
    
    GRINDING = false;
    HOLDING_INGREDIENT = false;
    
    
    
    cash = 0;
    rating = 100;
    
    selectTimer = 0;
    selectTime = 10;
    CONSIDERING_SELECTION = false;
    
    ofSetMinMagFilters(GL_NEAREST, GL_NEAREST);
    
    bg.loadImage("sprites/bg_temp.png");
    bg.resize(960, 540);
    bgXPos = 0;
    bgYPos = 0;
    
    counterImg.loadImage("sprites/counterTop.png");
    counterImg.resize(960, 540);
    counterXPos = 0;
    counterYPos = 0;
    cuttingBG.loadImage("sprites/cuttingBGImg.png");
    cuttingBG.resize(960, 540);
    
    SHAKING = false;
    shakeTimer = 20;
    shakeMod.set(0,0);
    
    mainRenderer = new ofxSpriteSheetRenderer(1,1000,0,32);
    mainRenderer -> loadTexture("sprites/master_sheet.png", 1280, GL_NEAREST);
    
    characterRenderer = new ofxSpriteSheetRenderer(1,1000,0,256);
    characterRenderer -> loadTexture("sprites/characters/characterSheet.png", 3328, GL_NEAREST);
    
    speechBubbleRenderer = new ofxSpriteSheetRenderer(1,1000,0,32);
    speechBubbleRenderer -> loadTexture("sprites/characters/neutral_bubble_sheet.png", 96, GL_NEAREST);
    
    speechBubble = SpeechBubble(215 * drawScale,25 * drawScale,200,100);
    
    // INITIALIZE TOOLS
    
    
    tableWidth = ofGetWidth()/4 * 3;
    tableHeight = 400;
    tablePos.set(0,200);
    
    trash = TrashCan(0,246 * drawScale, 90 * drawScale, 24 * drawScale);
    trash.setup();
    foregroundContent.push_back(&trash);
    
    plate = Plate(160 * drawScale, 170 * drawScale);
    plate.setup();
    foregroundContent.push_back(&plate);
    
    bowl.set(100,tablePos.y + 150);
    finalPlate.set(100,tablePos.y + 350);
    
    grinder = Grinder(320,480);
    grinder.setup();
    foregroundContent.push_back(&grinder);
    
    cuttingBoard = CuttingBoard(440,480);
    cuttingBoard.setup();
    foregroundContent.push_back(&cuttingBoard);
    
    pestle = Pestle(480,200);
    //foregroundContent.push_back()
    
    grill = Grill(130,351);
    grill.setup();
    foregroundContent.push_back(&grill);
    
    sink = Sink(880,320);
    sink.setup();
    foregroundContent.push_back(&sink);
    WATER_FLOWING = false;
    
    recipeBook = RecipeBook(275 * drawScale,180 * drawScale);
    recipeBook.setup();
    recipeBook.importRecipes();
    recipeBook.revealRecipe("raw genmaicha");
    foregroundContent.push_back(&recipeBook);
    
    pot = Pot(50,444);
    pot.setup();
    pot.sink = &sink;
    pot.grill = &grill;
    foregroundContent.push_back(&pot);
    
    skillet = Skillet(150,444);
    skillet.setup();
    skillet.grill = &grill;
    foregroundContent.push_back(&skillet);
    
    
    bookPos.set(750,ofGetHeight()-300);
    bookWidth = 50;
    bookHeight = 70;
    
    /// ---- INITIAL PANTRY POSITIONS;
    pantryPos[0].set(680,404);
    pantryPos[1].set(810,404);
    pantryPos[2].set(930,404);
    pantryPos[3].set(630,464);
    pantryPos[4].set(760,464);
    pantryPos[5].set(890,464);
    pantryPos[6].set(560,520);
    pantryPos[7].set(690,520);
    pantryPos[8].set(820,520);

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
    
    //setupRecipeBook();
    
    customerNames.push_back("shadow");
    
    random_shuffle(customerNames.begin(), customerNames.end());
    
    importCharacters();
    
    enterCustomer(currentCustomer);
    
    
    //organize Animations----------------------
    anims["TEST_DISH"] = rawSalmonAnim;
    anims["TEST_DISH2"] = grilledSalmonAnim;
    anims["uncooked rice"] = uncookedRice;
    anims["browned rice"] = brownedRice;
    anims["lightly boiled rice"] = lightlyBoiledRice;
    anims["barely boiled rice"] = lightlyBoiledRice;
    anims["boiled rice"] = boiledRice;
    anims["soggy rice"] = soggyRice;
    anims["toasted rice"] = toastedRice;
    anims["warm rice"] = warmRice;
    anims["crunchy bottom rice"] = crunchyRice;
    anims["ruined ingredient"] = ruined;
    anims["rice flour"] = riceFlourAnim;
    anims["toasted rice powder"] = toastedRiceFlourAnim;
    anims["mochi"] = mochiAnim;
    anims["yakimochi"] = yakiMochiAnim;
    anims["daifuku"] = daifukuAnim;
    anims["goma daifuku"] = gomaDaifukuAnim;
    anims["green tea mochi"] = greenTeaMochiAnim;
    anims["green tea daifuku"] = greenTeaDaifukuAnim;
    anims["kurogoma mochi"] = kurogomaMochiAnim;
    anims["kurogoma daifuku"] = kurogomaDaifukuAnim;
    anims["caramelized sugar"] = caramelizedSugar;
    anims["simple syrup"] = simpleSyrup;
    anims["sugar"] = sugarAnim;
    anims["powdered sugar"] = powderedSugarAnim;
    anims["raw red beans"] = rawRedBeansAnim;
    anims["hot wet red beans"] = rawRedBeansAnim;
    anims["boiled red beans"] = cookedRedBeansAnim;
    anims["mashed red beans"] = mashedRedBeansAnim;
    anims["sweet red bean paste"] = sweetRedBeanPasteAnim;
    anims["sesame seeds"] = sesameSeedsAnim;
    anims["black sesame seeds"] = blackSesameSeedsAnim;
    anims["sesame powder"] = powderedSesameSeedsAnim;
    anims["glow worms"] = glowWormAnim;
    anims["warm glow worms"] = glowWormAnim;
    anims["lightly boiled glow worms"] = lightlyBoiledGlowWormAnim;
    anims["boiled glow worms"] = boiledGlowWormAnim;
    anims["pale tasteless glow worms"] = tastelessGlowWormAnim;
    anims["crispy boiled glow worms"] = crispyBoiledGlowWormAnim;
    anims["crispy glow worms"] = crispyGlowWormAnim;
    anims["crunchy glow worms"] = crunchyGlowWormAnim;
    anims["sticky glow worms"] = stickyGlowWormAnim;
    anims["glow worm paste"] = glowWormPasteAnim;
    anims["raw ox meat"] = rawOxAnim;
    anims["rotten ox meat"] = rottenOxAnim;
    anims["raw salmon"] = rawSalmonAnim;
    anims["grilled salmon"] = grilledSalmonAnim;
    anims["uncooked soba noodles"] = rawSobaAnim;
    anims["green tea leaves"] = greenTeaLeavesAnim;
    anims["raw genmaicha"] = rawGenMaiAnim;
    anims["genmaicha"] = GenMaiAnim;
    anims["matcha powder"] = matchaPwdrAnim;
    anims["matcha"] = matchaAnim;
    
    

    
    dishSweetness = 0;
    dishSavory = 0;
    dishSourness = 0;
    dishFattiness = 0;
    dishBitterness = 0;
    dishUmami = 0;
    
    objID = 0;
    
}

void GameScreen::importCharacters()
{
    characterList.open("characterList.txt");
    ofBuffer charBuf = characterList.readToBuffer();
    
    string currentLine = charBuf.getFirstLine();
    
    bool LOADING_CHARACTER = false;
    
    int thisChar = 0;
    
    while (!charBuf.isLastLine())
    {
        if(!LOADING_CHARACTER)
        {
            if (currentLine != "{")
            {
                currentLine = charBuf.getNextLine();
            }
            else
            {
                LOADING_CHARACTER = true;
            }
        }
        else
        {
            Character * newChar = new Character(230,300);
            
            while(currentLine != "}")
            {
                currentLine = charBuf.getNextLine();
                
                if (currentLine.substr(0,6) == "name: ")
                {
                    newChar->name = currentLine.substr(6,currentLine.length()-1);
                    
                }
                else if (currentLine.substr(0,10) == "greeting: ")
                {
                    string greeting = currentLine.substr(10,currentLine.length()-1);
                    newChar->greetings.push_back(greeting);
                }
                else if (currentLine.substr(0,15) == "happy farewell: ")
                {
                    string happyFarewell = currentLine.substr(15,currentLine.length()-1);
                    newChar->happyLeavingDialogues.push_back(happyFarewell);
                }
                else if (currentLine.substr(0,15) == "angry farewell: ")
                {
                    string angryFarewell = currentLine.substr(15,currentLine.length()-1);
                    newChar->happyLeavingDialogues.push_back(angryFarewell);
                }
                else if (currentLine.substr(0,12) == "nice smell: ")
                {
                    string niceSmell = currentLine.substr(12,currentLine.length()-1);
                    newChar->niceSmellDialogues.push_back(niceSmell);
                }
                else if (currentLine.substr(0,11) == "bad smell: ")
                {
                    string badSmell = currentLine.substr(11,currentLine.length()-1);
                    newChar->badSmellDialogues.push_back(badSmell);
                }
                else if (currentLine.substr(0,7) == "hates: ")
                {
                    string hateDish = currentLine.substr(7,currentLine.length()-1);
                    newChar->hates.push_back(hateDish);
                }
                else if (currentLine.substr(0,7) == "likes: ")
                {
                    string likeDish = currentLine.substr(7,currentLine.length()-1);
                    newChar->likes.push_back(likeDish);
                }
                else if (currentLine.substr(0,8) == "mouthx: ")
                {
                    newChar->mouthPos.x = ofToInt(currentLine.substr(8,currentLine.length()-1));
                }
                else if (currentLine.substr(0,8) == "mouthy: ")
                {
                    newChar->mouthPos.y = ofToInt(currentLine.substr(8,currentLine.length()-1));
                }
                else if (currentLine.substr(0,9) == "request: ")
                {
                    newChar->addRequest(currentLine.substr(9,currentLine.length()-1));
                }
            }
            
            if (currentLine == "}")
            {
                LOADING_CHARACTER = false;
                
                newChar->ID = objID;
                newChar->spriteSheetID = thisChar;
                objID++;
                newChar->setup();
                thisChar++;
                
                
                characters.push_back(newChar);
            }
            
        }
    }
    
}

void GameScreen::enterCustomer(int _id)
{
 
    customerInStore = characters[_id];
    customerInStore->setup();
    
    speechBubbleRenderer -> loadTexture("sprites/characters/" + customerInStore->name + "_bubble.png", 96, GL_NEAREST);
    
    //characterRenderer -> loadTexture("sprites/characters/" + characters[_id]->name + "_sheet.png", 1280, GL_NEAREST);
    
    customerInStore->enter();
    
}

void GameScreen::setupRecipeBook(){
    
    string currentLine = allRecipes.getFirstLine();
    string knownLine = knownRecipes.getFirstLine();
    while (!allRecipes.isLastLine()){
        bool found = false;
        while (!knownRecipes.isLastLine()){
            if (currentLine.substr(currentLine.find("= ")+2,currentLine.length()-1) == knownLine){
                desires.push_back(currentLine.substr(currentLine.find("= ")+2,currentLine.length()-1));
                found = true;
                break;
            }
            knownLine = knownRecipes.getNextLine();
        }
        knownLine = knownRecipes.getFirstLine();
        currentLine = allRecipes.getNextLine();
    }
}

//// --- NOW LET'S MAKE INGREDIENT SPAWNERS!!

void GameScreen::setupPantry(){
    
    // iterate through list of known ingredients
    // add to vector of types, in draw() we'll draw them in the pantry based on their position in the vector.
    
    pantryContentsList.clear();
    
    string currentLine = pantryContents.getFirstLine();
    
    while (!pantryContents.isLastLine()) {
        pantryContentsList.push_back(currentLine);
        currentLine = pantryContents.getNextLine();
    }
    
    for (int i = 0; i < 8; i++)
    {
        Ingredient * newPantryIng = new Ingredient(pantryContentsList[i],pantryPos[i].x,pantryPos[i].y);
        pantry.push_back(newPantryIng);
        foregroundContent.push_back(newPantryIng);
    }

}

//--------------------------------------------------------------
void GameScreen::update(){
    
    Screen::update();
    
    xTranslate = (ofGetWidth()/2) - ofGetMouseX();
    
    // NON VIEW SPECIFIC STUFF GOES HERE
    mainRenderer->clear();
    mainRenderer->update(ofGetElapsedTimeMillis());
    
    characterRenderer->clear();
    characterRenderer->update(ofGetElapsedTimeMillis());
    
    speechBubbleRenderer->clear();
    speechBubbleRenderer->update(ofGetElapsedTimeMillis());
    
    
    if (skillet.pos.distance(grill.burner1) < 10 || skillet.pos.distance(grill.burner2) < 10)
    {
        skillet.ACTIVE = true;
    }
    
    if (pot.pos.distance(grill.burner1) < 10 || pot.pos.distance(grill.burner2) < 10)
    {
        pot.ACTIVE = true;
    }
    
    
    if (CONSIDERING_SELECTION)
    {
        if (selectTimer < selectTime)
        {
            selectTimer++;
        }
        else
        {
            CONSIDERING_SELECTION = false;
        }
    }
    
    if (skillet.HAS_CONTENTS && skillet.ACTIVE)
    {
        bool FOUND_MATCH = false;
        for (int i = 0; i < skillet.contents.size();i++)
        {
            for (int h = 0; h < customerInStore->hates.size();h++)
            {
                if (skillet.contents[i]->type == customerInStore->hates[h])
                {
                    customerInStore->turnUpNose();
                    break;
                }
                
            }
            for (int l = 0; l < customerInStore->likes.size();l++)
            {
                if (skillet.contents[i]->type == customerInStore->likes[l])
                {
                    customerInStore->lickLips();
                    break;
                }
            }
        }
    }
    
    if (customerInStore->LEFT_STORE)
    {
        currentCustomer++;
        if (currentCustomer >= characters.size())
        {
            currentCustomer = 0;
        }
        enterCustomer(currentCustomer);
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
    
    for (int d = 0; d < dishes.size();d++)
    {
        dishes[d]->update();
    }
    customerTimer.update();
    nextCustomerTimer.update();
    
    for (int n = 0; n < uiDisplayText.size();n++)
    {
        uiDisplayText[n]->update();
        if (uiDisplayText[n]->DEAD)
        {
            uiDisplayText.erase(uiDisplayText.begin() + n);
        }
    }

    switch (VIEW)
    {
        case GAME:
            /// NOW MAIN COUNTER VIEW STUFF

        {
                updateIngredientsAndAddToScreen();
        }
        break;
        case GRINDERVIEW:
            /// NOW GRINDER VIEW STUFF
        {
            updateIngredientsAndAddToScreen();
            overlay(ofColor(4,11,68,127));
            mainRenderer->addCenteredTile(&bigGrinderBack, heldObjPos.x, heldObjPos.y,0,F_NONE,2,255,255,255,255);
            foodInGrinder->pos.set(500,ofGetHeight()-128);
            foodInGrinder->update();
            foodInGrinder->drawScale = 10;
            foodInGrinder->addSpriteToRenderer();
            pestle.update();
            pestle.addSpriteToRenderer();
            mainRenderer->addCenteredTile(&bigGrinderFront, heldObjPos.x, heldObjPos.y,0,F_NONE,2,255,255,255,255);
            
        }
        break;
        case RECIPES:
        {
            updateIngredientsAndAddToScreen();
            overlay(ofColor(4,11,68,127));
            mainRenderer->addCenteredTile(&bigRecipeBookAnim, recipeBook.bigPos.x, recipeBook.bigPos.y,0,F_NONE,2,255,255,255,255);
        }
        break;
        case CUTTINGVIEW:
        {
            mainRenderer->addCenteredTile(&bigCuttingBoardAnim, 600, 300,0,F_NONE,2,255,255,255,255);
            foodOnBoard->pos.set(500,ofGetHeight()-128);
            foodOnBoard->update();
            foodOnBoard->drawScale = 10;
            foodOnBoard->addSpriteToRenderer();

        }
            break;
    }
    
}

//--------------------------------------------------------------
void GameScreen::draw(){
    ofPushMatrix();
    Screen::draw();
    
    customerTimer.draw();
    nextCustomerTimer.draw();
    
    ofSetColor(0, 255, 255);
    ofDrawBitmapString("Money: " + ofToString(cash), 20,60);
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    
    ofSetColor(255,255,255);
    
    bg.draw(ofPoint(bgXPos,bgYPos));
    
    characterRenderer->draw();
    
    counterImg.draw(counterXPos,counterYPos);
    
    
    switch (VIEW)
    {
        case RECIPES:
        {
            mainRenderer->draw();
            recipeBook.draw();
        }
            break;
        case GAME:
        {
            mainRenderer->draw();
            ofDrawBitmapString(dishInPlate, ofGetWidth() - dishInPlate.size()*8 - 20, 20);
            for (int d = 0; d < dishes.size();d++)
            {
                dishes[d]->draw();
            }
            //grill.drawDebug();
            
            if (customerInStore->SPEAKING)
            {
                speechBubble.show(customerInStore->currentDialogue);
            }
            else
            {
                speechBubble.hide();
            }
            
            speechBubbleRenderer->draw();
            
            speechBubble.draw();
            
        }
            break;
        case GRINDERVIEW:
        {
            mainRenderer->draw();
            speechBubble.draw();
        }
            break;
        case CUTTINGVIEW:
        {
            cuttingBG.draw(0,0);
            mainRenderer->draw();
        }
            break;
    }
    
    for (int n = 0; n < uiDisplayText.size();n++)
    {
        uiDisplayText[n]->draw();
    }
    
    if (ofGetKeyPressed()){
        ofDrawBitmapString(knownRecipes, 50,50);
    }
    
    ofPopMatrix();
}

void GameScreen::updateIngredientsAndAddToScreen()
{
    
    customerInStore->update();
    characterRenderer->addCenterRotatedTile(&customerInStore->anim, customerInStore->pos.x, customerInStore->pos.y, 0, F_NONE, drawScale, customerInStore->angle, NULL, 255,255,255,customerInStore->alpha);
    
    sink.update();
    sink.addSpriteToRenderer();
    if (sink.ACTIVE)
    {
        addWater();
    }
    
    trash.update();
    trash.addSpriteToRenderer();
    
    plate.update();
    plate.addSpriteToRenderer();
    
    grill.update();
    grill.addSpriteToRenderer();
    
    skillet.update();
    skillet.addSpriteToRenderer();
    
    recipeBook.update();
    recipeBook.addSpriteToRenderer();
    
    pot.update();
    pot.addSpriteToRenderer();
    
    grinder.update();
    grinder.addSpriteToRenderer();
    
    cuttingBoard.update();
    cuttingBoard.addSpriteToRenderer();
    
    speechBubble.update();
    
    
    // -- DRAW PANTRY CONTENTS
    for (int i = 0; i < 8; i++){
        pantry[i]->update();
        pantry[i]->anim = anims[pantry[i]->type];
        pantry[i]->addSpriteToRenderer();
    }

    
    // --- BY FRAME MANIPULATION OF INGREDIENTS ON SCREEN
    for (int i = 0;i<ingredients.size();i++){
        
        if (ingredients[i]->type == "removeMe"){
            ingredients.erase(ingredients.begin() + i);
        }
        
        if (ingredients[i]->HELD == false){
            if (pointOverlaps(ingredients[i]->pos, trash.mouthPos,trash.mouthWidth,trash.mouthHeight)){
                ingredients[i]->type = "removeMe";
            }
        }
        
        ingredients[i]->anim = anims[ingredients[i]->type];
        
        ingredients[i]->addSpriteToRenderer();
        
        ingredients[i]->update();
    }
    
    for (int d = 0; d < dishes.size();d++)
    {
        if (dishes[d]->REMOVE_ME)
        {
            dishes.erase(dishes.begin()+d);
        }
        
        if (!dishes[d]->HELD)
        {
            if (pointOverlaps(dishes[d]->pos, trash.mouthPos,trash.mouthWidth,trash.mouthHeight))
            {
                dishes[d]->REMOVE_ME = true;
            }
        }
        
        dishes[d]->addSpriteToRenderer();
    }
    
    if(pot.IN_SINK)
    {
        pot.BEING_FILLED = true;
    }
    



}

void GameScreen::addWater()
{
        mainRenderer->addCenteredTile(sink.waterAnim, sink.pos.x + 10, sink.pos.y,0,F_NONE,sink.drawScale,255,255,255,255);
}

void GameScreen::addToPantry(string _ingredient){
    
    string currentPantryContents = pantryContents.getText();
    currentPantryContents.erase(currentPantryContents.find("<"),currentPantryContents.find(">"));
    currentPantryContents.append(_ingredient + "\n");
    currentPantryContents.append("<--- LAST --->");
    pantryContents.set(currentPantryContents);
    setupPantry();
    
}

bool GameScreen::pointOverlaps(ofVec2f _p, GameObject _obj)
{
    if (_p.distance(_obj.pos) < _obj.size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameScreen::pointOverlaps(ofVec2f _p, ofVec2f _rectPos, int _rectWidth, int _rectHeight)
{
    if (_p.x > _rectPos.x &&
        _p.y > _rectPos.y &&
        _p.x < _rectPos.x + _rectWidth &&
        _p.y < _rectPos.y + _rectHeight)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GameScreen::serveCustomer(Dish * _d)
{
    //This is broken now that we're supporting more than one dish at a time. How should we handle this?
    customerInStore->assessDish(_d);
}

void GameScreen::overlay(ofColor _color)
{
    mainRenderer->addCenteredTile(&overlayAnim, ofGetWidth()/2, ofGetHeight()/2,0,F_NONE,500,_color.r,_color.g,_color.b,_color.a);
}

void GameScreen::addIngredient(string _type, int x, int y)
{
    //add the ingredient to the stage. (take out of pantry).
    Ingredient * ing = new Ingredient(_type,x,y);
    ing->ID = objID;
    objID++;
    ingredients.push_back(ing);
    foregroundContent.push_back(ing);
}

void GameScreen::combineDishes(Dish *d1, Dish *d2)
{
    // can't do this yet! Do I want to?
}

void GameScreen::checkRecipes(Dish * d){
    
    vector<Ingredient *> dishComponents;
    
    for (int b = 0; b < d->baseCount;b++)
    {
        dishComponents.push_back(d->base[b]);
    }
    if (d->HAS_BROTH)
    {
        dishComponents.push_back(d->broth);
    }
    for (int g = 0; g < d->garnishCount;g++)
    {
        dishComponents.push_back(d->garnish[g]);
    }
    if (d->HAS_SUBDISH)
    {
        dishComponents.push_back(d->subdish);
    }


   
    recipeList.open("dishes.txt");
    ofBuffer recipeText = recipeList.readToBuffer();
    string currentLine = recipeText.getFirstLine();
    
    // -- let's iterate through the recipe list and check the components of the dish against each recipe.
    while (!recipeText.isLastLine()) {
        
        vector<string> typesInRecipe;
        int numIng = std::count(currentLine.begin(),currentLine.end(),'+') + 1;
        
        // get each component of the current line of the recipe list.
        int startChar = 0;
        for (int i = 0; i < numIng; i++)
        {
            string ingredientType = "";
            if (i == numIng - 1)
            {
                ingredientType = currentLine.substr(startChar,currentLine.find(" = ",startChar) - startChar);
            }
            else
            {
                ingredientType = currentLine.substr(startChar,currentLine.find(" + ",startChar) - startChar);
            }
            
            startChar = currentLine.find(" + ") + 3;
            typesInRecipe.push_back(ingredientType);
            
        }
        
        // get the resultant dish of this line's recipe
        startChar = currentLine.find(" = ") + 3;
        string recipeResult = currentLine.substr(startChar,currentLine.find("\n") - startChar);
        
        // now let's check if the plated dish contains one of these recipes.
        
        bool containsAllElements = false;
        
        for (int i = 0; i < typesInRecipe.size();i++)
        {
            // we reset this to false every iteration so that the break system below will work.
            containsAllElements = false;
            bool containsThisElement = false;
            
            for (int c = 0; c < dishComponents.size();c++)
            {
                if (dishComponents[c]->type == typesInRecipe[i])
                {
                    containsThisElement = true;
                    dishComponents[c]->USED_IN_SUBDISH = true;
                }
            }
            
            // if the dish doesn't contain this type from the recipe, we break without setting containsAllElements back to true, so that the check following these nested loops will come out false.
            if (!containsThisElement)
            {
                break;
            }
            else
            {
                containsAllElements = true;
            }
        }
        
        if (containsAllElements)
        {
            for (int dc = 0; dc < dishComponents.size(); dc++)
            {
                if (dishComponents[dc]->USED_IN_SUBDISH)
                {
                    d->removeIngredient(dishComponents[dc]->ID);
                }
            }
            
            d->subdishName = recipeResult;
            recipeBook.revealRecipe(recipeResult);
            d->subdish = new Ingredient(d->subdishName,d->pos.x,d->pos.y);
            d->subdish->setup();
            d->HAS_SUBDISH = true;
            break;
        }
        else
        {
            for (int c = 0; c < dishComponents.size();c++)
            {
                dishComponents[c]->USED_IN_SUBDISH = false;
            }
            currentLine = recipeText.getNextLine();
        }
    }
    
    recipeList.close();
    d->createName();
     
    
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
    if (key == 'c'){
        customerInStore->leave();
    }
    
}

void GameScreen::reset(){
    ingredients.clear();
    plateContents.clear();
    
    WON = false;
}

//--------------------------------------------------------------
void GameScreen::keyReleased(int key){
    Screen::keyReleased(key);
    
}

void GameScreen::parallax(int x, int y)
{
    lastMouseX = mouseX;
    mouseX = x;
    
    lastMouseY = mouseY;
    mouseY = y;
    
    float foregroundOffsetX = (lastMouseX - mouseX)/FGDamp;
    float midgroundOffsetX = (lastMouseX - mouseX)/MGDamp;
    float backgroundOffsetX = (lastMouseX - mouseX)/BGDamp;
    
    float foregroundOffsetY = (lastMouseY - mouseY)/(FGDamp*2);
    float midgroundOffsetY = (lastMouseY - mouseY)/(MGDamp*2);
    float backgroundOffsetY = (lastMouseY - mouseY)/(BGDamp*2);
    
    // TRANSLATE FOREGROUND
    for (int c = 0; c < foregroundContent.size();c++)
    {
        foregroundContent[c]->pos.x += foregroundOffsetX;
        foregroundContent[c]->pos.y += foregroundOffsetY;
    }
    
    counterXPos += foregroundOffsetX;
    counterYPos += foregroundOffsetY;
    
    // TRANSLATE MIDGROUND
    
    for (int c = 0; c < midgroundContent.size(); c++)
    {
        midgroundContent[c]->pos += ofVec2f(midgroundOffsetX,midgroundOffsetY);
    }
    
    recipeBook.bigPos += ofVec2f(midgroundOffsetX,midgroundOffsetY);
    recipeBook.leftPageTextLocation += ofVec2f(midgroundOffsetX,midgroundOffsetY);
    recipeBook.rightPageTextLocation += ofVec2f(midgroundOffsetX,midgroundOffsetY);
    
    
    customerInStore->pos.x += midgroundOffsetX;
    customerInStore->pos.y += midgroundOffsetY;
    speechBubble.pos.x += midgroundOffsetX;
    speechBubble.pos.y += midgroundOffsetY;
    
    // TRANSLATE BACKGROUND
    
    bgXPos += backgroundOffsetX;
    bgYPos += backgroundOffsetY;
    
}

//--------------------------------------------------------------
void GameScreen::mouseMoved(int x, int y ){
    
    Screen::mouseMoved(x, y);
    
    if (!GRINDING){
        prevMousePos.set(x,y);
    }
    
    switch (VIEW)
    {
        case GAME:
        {
            for (int p = 0; p < pantry.size();p++)
            {
                if (pantry[p]->pos.distance(ofPoint(x,y)) < 50)
                {
                    if (pantry[p]->nameDisplays.size() < 1)
                    {
                    pantry[p]->spawnDisplay(pantry[p]->type);
                    }
                }
            }
            
            if (pointOverlaps(ofVec2f(x,y), recipeBook.hitBoxPos, recipeBook.width, recipeBook.height))
            {
                recipeBook.HIGHLIGHTED = true;
            }
            else
            {
                recipeBook.HIGHLIGHTED = false;
            }
            
            if (ofVec2f(x,y).distance(pot.pos) < pot.size && pot.HAS_CONTENTS && !pot.SELECTED)
            {
                pot.select();
            }
            else if (pot.SELECTED && !pointOverlaps(ofVec2f(x,y), pot.selectedHitBoxPos,pot.selectedHitBoxWidth,pot.selectedHitBoxHeight))
            {
                pot.deselect();
            }
            
            if (!pot.SELECTED && ofVec2f(x,y).distance(skillet.pos) < skillet.size && skillet.HAS_CONTENTS && !skillet.SELECTED)
            {
                skillet.select();
            }
            else if (skillet.SELECTED && !pointOverlaps(ofVec2f(x,y), skillet.selectedHitBoxPos,skillet.selectedHitBoxWidth,skillet.selectedHitBoxHeight))
            {
                skillet.deselect();
            }
            
            
            
        }
        break;
        case GRINDERVIEW:
        {
            pestle.mouseMoved(x, y);
        }
            break;
    }
    
    parallax(x, y);
}
//--------------------------------------------------------------
void GameScreen::mouseDragged(int x, int y, int button){
    
    Screen::mouseDragged(x, y, button);

    parallax(x, y);
    
    for(int i = 0; i < ingredients.size();i++){
        if (ingredients[i]->HELD == true){
            ofVec2f newPos;
            newPos.set(x + ingredients[i]->offset.x,y+ingredients[i]->offset.y);
            ingredients[i]->pos.set(newPos);
        }
    }
    
    switch (VIEW)
    {
        case GAME:
            
        
            
        if (HOLDING_INGREDIENT)
        {
            if (grinder.pos.distance(ofPoint(x,y))<grinder.size)
            {
                grinder.HIGHLIGHTED = true;
            }
            else
            {
                grinder.HIGHLIGHTED = false;
            }
            
            if (cuttingBoard.pos.distance(ofPoint(x,y))<cuttingBoard.size)
            {
                cuttingBoard.HIGHLIGHTED = true;
            }
            else
            {
                cuttingBoard.HIGHLIGHTED = false;
            }
            if(customerInStore->mouthPos.distance(ofPoint(x,y))<50)
            {
                customerInStore->prepareToEat();
            }
            if (pot.HELD)
            {
                if (pot.pos.distance(trash.pos) < trash.size && pot.HAS_CONTENTS)
                {
                    pot.READY_TO_TRASH = true;
                }
                else
                {
                    
                    if (pot.pos.distance(plate.pos) < plate.size && pot.HAS_CONTENTS)
                    {
                        pot.READY_TO_PLATE = true;
                        break;
                    }
                    else
                    {
                        pot.READY_TO_TRASH = false;
                        pot.READY_TO_PLATE = false;
                    }
                    
                    for (int d = 0; d < dishes.size();d++)
                    {
                        if (pot.pos.distance(dishes[d]->pos) < dishes[d]->size)
                        {
                            pot.READY_TO_PLATE = true;
                            break;
                        }
                    }
                }
            }
            
            if (skillet.HELD)
            {
                if (skillet.pos.distance(trash.pos)<trash.size && skillet.HAS_CONTENTS)
                {
                    skillet.READY_TO_TRASH = true;
                }
                else
                {
                    if (skillet.pos.distance(plate.pos) < plate.size && skillet.HAS_CONTENTS)
                    {
                        skillet.READY_TO_PLATE = true;
                        break;
                    }
                    else
                    {
                        skillet.READY_TO_TRASH = false;
                        skillet.READY_TO_PLATE = false;
                    }
                    
                    for (int d = 0; d < dishes.size();d++)
                    {
                        if (skillet.pos.distance(dishes[d]->pos) < dishes[d]->size && skillet.HAS_CONTENTS)
                        {
                            skillet.READY_TO_PLATE = true;
                            break;
                        }
                    }
                    
                }
            }
        }
            break;
        case GRINDERVIEW:
        {
            SHAKING = true;
            foodInGrinder->grindTime++;
            pestle.mouseDragged(x,y);
        }
            break;
        
    }
    
    prevMousePos.set(x,y);
    
}

//--------------------------------------------------------------
void GameScreen::mousePressed(int x, int y, int button){
    
    Screen::mousePressed(x, y, button);
    
    switch (VIEW)
    {
        case GAME:
        {
            
            if (pot.SELECTED)
            {
                pot.mousePressed(x, y);
                pot.deselect();
            }
            
            if (skillet.SELECTED)
            {
                skillet.mousePressed(x, y);
                skillet.deselect();
            }
            
            for(int i = ingredients.size()-1; i > -1;i--){
                if (ingredients[i]->pos.distance(ofPoint(x,y))<20){
                    ingredients[i]->HELD = true;
                    HOLDING_INGREDIENT = true;
                    ingredients[i]->offset.set(ingredients[i]->pos - ofPoint(x,y));
                    break;
                }
            }
            if (!HOLDING_INGREDIENT){
                
                for (int i = 0;i<pantry.size();i++){
                    if (ofPoint(x,y).distance(ofPoint(pantry[i]->pos.x, pantry[i]->pos.y))<pantry[i]->size){
                        addIngredient(pantryContentsList[i],x,y);
                        ingredients[ingredients.size()-1]->HELD = true;
                        HOLDING_INGREDIENT = true;
                        break;
                    }
                }
                
                for (int b = 0; b < buttons.size();b++)
                {
                    if (x > buttons[b]->pos.x && x < buttons[b]->pos.x + buttons[b]->width && y > buttons[b]->pos.y && y < buttons[b]->pos.y + buttons[b]->height)
                    {
                        buttons[b]->action();
                    }
                }
                
                if (!HOLDING_INGREDIENT)
                {
                    for (int d = dishes.size()-1; d > -1;d--)
                    {
                        if (dishes[d]->pos.distance(ofPoint(x,y))<dishes[d]->size)
                        {
                            dishes[d]->HELD = true;
                            HOLDING_INGREDIENT = true;
                            break;
                        }
                    }
                }
                
                if (!HOLDING_INGREDIENT)
                {
                    if (pot.pos.distance(ofPoint(x,y))<pot.size)
                    {
                        pot.HELD = true;
                        HOLDING_INGREDIENT = true;
                        pot.IN_SINK = false;
                        pot.ON_GRILL = false;
                        CONSIDERING_SELECTION = true;
                        selectTimer = 0;
                        break;
                    }
                }
                
                if (!HOLDING_INGREDIENT)
                {
                    if (skillet.pos.distance(ofPoint(x,y))<skillet.size)
                    {
                        skillet.HELD = true;
                        HOLDING_INGREDIENT = true;
                        skillet.ON_GRILL = false;
                        CONSIDERING_SELECTION = true;
                        selectTimer = 0;
                        break;
                    }
                }
                
                if (!HOLDING_INGREDIENT && ofPoint(x,y).distance(sink.pos) < sink.size)
                {
                    sink.ACTIVE = !sink.ACTIVE;
                    sink.WATER_FLOWING = false;
                    break;
                }
                
                if (recipeBook.HIGHLIGHTED)
                {
                    VIEW = RECIPES;
                    recipeBook.IN_USE = true;
                }
                
                if (pointOverlaps(ofPoint(x,y), grill.hitBoxPos, grill.width, grill.height))
                {
                    grill.B1_ACTIVE = !grill.B1_ACTIVE;
                    grill.B2_ACTIVE = !grill.B2_ACTIVE;
                }
                
            }
            
        }
            break;
        case RECIPES:
        {
            if (!pointOverlaps(ofPoint(x,y), recipeBook.bigHitBoxPos, recipeBook.bigWidth, recipeBook.bigHeight))
            {
                VIEW = GAME;
            }
        }
            break;
        case GRINDERVIEW:
        {
            if (pointOverlaps(ofVec2f(x,y), grinder.bigGrinderHitBoxPos, grinder.bigGrinderHitWidth, grinder.bigGrinderHitHeight))
            {
                pestle.mousePressed(x,y);
            }
            else
            {
                foodInGrinder->pos.set(grinder.pos.x + 3*grinder.size,grinder.pos.y);
                foodInGrinder->HELD = false;
                grinder.HIGHLIGHTED = false;
                ingredients.push_back(foodInGrinder);
                VIEW = GAME;
            }
        }
            break;
        case CUTTINGVIEW:
        {
            if (pointOverlaps(ofVec2f(x,y),cuttingBoard.bigCuttingBoardHitBoxPos,cuttingBoard.bigCuttingBoardWidth,cuttingBoard.bigCuttingBoardHeight))
            {
                
            }
            else
            {
                foodOnBoard->pos.set(cuttingBoard.pos.x + 3*cuttingBoard.size,cuttingBoard.pos.y);
                foodOnBoard->HELD = false;
                cuttingBoard.HIGHLIGHTED = false;
                ingredients.push_back(foodOnBoard);
                VIEW = GAME;
            }
        }
            break;
    }
}


//--------------------------------------------------------------
void GameScreen::mouseReleased(int x, int y, int button){
    Screen::mouseReleased(x, y, button);
    
    switch (VIEW) {
        case GAME:
            if(grinder.HIGHLIGHTED)
            {
                for (int i = 0; i<ingredients.size();i++)
                {
                    if (ingredients[i]->HELD)
                    {
                        foodInGrinder = ingredients[i];
                        ingredients[i]->HELD = false;
                        ingredients.erase(ingredients.begin()+i);
                        HOLDING_INGREDIENT = false;
                        break;
                    }
                }
                VIEW = GRINDERVIEW;
            }
            else if (cuttingBoard.HIGHLIGHTED)
            {
                for (int i = 0; i<ingredients.size();i++)
                {
                    if (ingredients[i]->HELD)
                    {
                        foodOnBoard = ingredients[i];
                        ingredients[i]->HELD = false;
                        ingredients.erase(ingredients.begin()+i);
                        HOLDING_INGREDIENT = false;
                        break;
                    }
                }
                VIEW = CUTTINGVIEW;
            }
            else if (pot.HELD)
            {
//                if (CONSIDERING_SELECTION)
//                {
//                    if (!pot.SELECTED && pot.HAS_CONTENTS)
//                    {
//                        pot.select();
//                        break;
//                    }
//                }
//              // PUT ELSE BELOW  
                if (pot.pos.distance(sink.pos)<sink.size)
                {
                    pot.IN_SINK = true;
                    break;
                }
                else if(pot.pos.distance(grill.burner1)<pot.size)
                {
                    pot.ON_GRILL = true;
                    pot.pos.x = grill.burner1.x + (4 * drawScale);
                    pot.pos.y = grill.burner1.y - (12 * drawScale);
                    pot.BURNER_ACTIVE = grill.B1_ACTIVE;
                    break;
                }
                else if (pot.pos.distance(grill.burner2)<pot.size)
                {
                    pot.ON_GRILL = true;
                    pot.pos.x = grill.burner2.x + (4 * drawScale);
                    pot.pos.y = grill.burner2.y - (12 * drawScale);
                    pot.BURNER_ACTIVE = grill.B2_ACTIVE;
                    break;
                }
                else if (pot.READY_TO_TRASH)
                {
                    pot.emptyToTrash();
                    break;
                }
                else if (pot.READY_TO_PLATE)
                {
                    bool PLATED = false;
                    for (int d = dishes.size()-1; d > -1; d--)
                    {
                        if (pot.pos.distance(dishes[d]->pos) < dishes[d]->size)
                        {
                            pot.emptyToDish(dishes[d]);
                            PLATED = true;
                        }
                    }
                    
                    if (!PLATED)
                    {
                        if (pot.pos.distance(plate.pos)<plate.size)
                        {
                            pot.emptyToDish(NULL);
                            pot.READY_TO_PLATE = false;
                            PLATED = true;
                        }
                    }
                    
                    
                }
            }
            else if(skillet.HELD)
            {
             
                if (CONSIDERING_SELECTION)
                {
//                    if (!skillet.SELECTED && skillet.HAS_CONTENTS)
//                    {
//                        skillet.select();
//                        break;
//                    }
                }
                else if (skillet.pos.distance(grill.burner1)<skillet.size)
                {
                    skillet.ON_GRILL = true;
                    skillet.pos.x = grill.burner1.x + (6 * drawScale);
                    skillet.pos.y = grill.burner1.y - (5 * drawScale);
                    skillet.BURNER_ACTIVE = grill.B1_ACTIVE;
                    break;
                }
                else if  (skillet.pos.distance(grill.burner2)<skillet.size)
                {
                    skillet.ON_GRILL = true;
                    skillet.pos.x = grill.burner2.x + (6 * drawScale);
                    skillet.pos.y = grill.burner2.y - (5 * drawScale);
                    skillet.BURNER_ACTIVE = grill.B2_ACTIVE;
                    break;
                }
                else if (skillet.READY_TO_TRASH)
                {
                    skillet.emptyToTrash();
                    break;
                }
                else if (skillet.READY_TO_PLATE)
                {
                    bool PLATED = false;
                    for (int d = dishes.size()-1; d > -1; d--)
                    {
                        if (skillet.pos.distance(dishes[d]->pos) < dishes[d]->size)
                        {
                            skillet.emptyToDish(dishes[d]);
                            PLATED = true;
                        }
                    }
                    
                    if (!PLATED)
                    {
                        if (skillet.pos.distance(plate.pos)<plate.size)
                        {
                            skillet.emptyToDish(NULL);
                            skillet.READY_TO_PLATE = false;
                            PLATED = true;
                        }
                    }
                }

            }
            else if (customerInStore->mouthPos.distance(ofPoint(x,y))<50 && HOLDING_INGREDIENT)
            {
                bool EATEN = false;
                
                for (int i = 0; i < ingredients.size();i++)
                {
                    if (ingredients[i]->HELD)
                    {
                        customerInStore->speak(charTalkAnim);
                        customerInStore->currentDialogue = "Hey, you could at least put it on a plate.";
                        ingredients[i]->type = "removeMe";
                        EATEN = true;
                        break;
                    }
                }
                
                if (!EATEN)
                {
                    for (int d = 0; d < dishes.size();d++)
                    {
                        if (dishes[d]->HELD)
                        {
                            customerInStore->eat(dishes[d]);
                            dishes[d]->REMOVE_ME = true;
                            break;
                        }
                    }
                }
                
            }
            else{
                for(int i = 0; i < ingredients.size();i++)
                {
                    if (ingredients[i]->HELD == true)
                    {
                        bool ADDED = false;
                        ingredients[i]->HELD = false;
                        
                        if (!ADDED && pointOverlaps(ingredients[i]->pos, pot.mouthPos, pot.mouthWidth, pot.mouthHeight))
                        {
                            if(pot.add(ingredients[i]))
                            {
                                ingredients.erase(ingredients.begin()+i);
                                break;
                            }
                            else
                            {
                                ingredients[i]->pos.set(pot.pos.x,pot.pos.y);
                                break;
                            }
                            
                        }
                        else if (!ADDED && pointOverlaps(ingredients[i]->pos,skillet.mouthPos, skillet.mouthWidth,skillet.mouthHeight))
                        {
                            if(skillet.add(ingredients[i]))
                            {
                                ingredients.erase(ingredients.begin()+i);
                                break;
                            }
                            else
                            {
                                ingredients[i]->pos.set(skillet.pos.x,skillet.pos.y);
                                break;
                            }
                        }

                        
                        for (int d= 0; d < dishes.size();d++)
                        {
                            if (ingredients[i]->pos.distance(dishes[d]->pos) < dishes[d]->size)
                            {
                                dishes[d]->addIngredient(ingredients[i]);
                                ingredients.erase(ingredients.begin() + i);
                                checkRecipes(dishes[d]);
                                ADDED = true;
                                break;
                            }
                        }
                        
                        if (!ADDED && ingredients[i]->pos.distance(plate.pos)<plate.size)
                        {
                            
                            Dish * dish = new Dish(plate.pos.x,plate.pos.y);
                            dish->addIngredient(ingredients[i]);
                            ingredients.erase(ingredients.begin() + i);
                            checkRecipes(dish);
                            dishes.push_back(dish);
                            foregroundContent.push_back(dish);
                            break;
                        }
                    }
                }
            }
            break;
        case GRINDERVIEW:
        {
            pestle.mouseReleased(x, y);
        }
            break;
    }
    
    for (int d = 0; d < dishes.size();d++)
    {
        dishes[d]->HELD = false;
    }
    skillet.HELD = false;
    pot.HELD = false;
    pot.READY_TO_TRASH = false;
    skillet.READY_TO_TRASH = false;
    GRINDING = false;
    HOLDING_INGREDIENT = false;
}

void GameScreen::loadImage(ofImage _image, string _imagePath, int _timesWidth, int _timesHeight)
{
    ofPixels pix;
    ofLoadImage(pix,_imagePath);
    pix.resize(pix.getWidth() * _timesWidth,pix.getHeight() * _timesHeight);
    _image.setFromPixels(pix);
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