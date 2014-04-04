//
//  Skillet.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#include "Skillet.h"
#include "testApp.h"

Skillet::Skillet():GameObject()
{
    
}

Skillet::Skillet(int x, int y):GameObject(x,y)
{
    
}

void Skillet::setup()
{
    GameObject::setup();
    size = 40;
    
    ACTIVE = false;
    HAS_CONTENTS = false;
    BEING_FILLED = false;
    IN_SINK = false;
    ON_GRILL = false;
    numContents = 0;
    maxContents = 1;
    SELECTED = false;
    BURNER_ACTIVE = false;
    
    mouthPos.set(pos.x - 40, pos.y - 40);
    mouthWidth = 80;
    mouthHeight = 20;
    
    
    for (int i = 0; i < maxContents; i++)
    {
        contentPos.push_back(ofVec2f(i+1*(mouthWidth/maxContents)/2,mouthHeight/2));
        contentDir.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)).normalize());
    }
}

void Skillet::update()
{
    GameObject::update();
    
    if (contents.size() > 0)
    {
        HAS_CONTENTS = true;
    }
    else
    {
        HAS_CONTENTS = false;
    }
    
    for (int c = 0; c < contents.size(); c++)
    {
        if (ACTIVE)
        {
            contents[c]->grillTime ++;
        }
        
        contents[c]->pos = mouthPos + contentPos[c];
        contents[c]->update();
    }
    
    if (ON_GRILL && BURNER_ACTIVE)
    {
        ACTIVE = true;
    }
    else
    {
        ACTIVE = false;
    }
    
    mouthPos.set(pos.x - 50, pos.y - 10);
    mouthWidth = 80;
    mouthHeight = 20;
    
    if (SELECTED)
    {
        for (int b = 0; b < bubbles.size();b++)
        {
            bubbles[b].update();
            bubbles[b].pos.set(mouthPos.x + ((b+1) * (mouthWidth/(numContents+1))),mouthPos.y - 50);
        }
    }
    
    if (!ON_GRILL)
    {
        BURNER_ACTIVE = false;
    }
    
    for (int c = 0; c < contents.size(); c++)
    {
        contents[c]->drawScale = drawScale;
    }
    
    if (READY_TO_TRASH)
    {
        READY_TO_POUR = true;
    }
    else
    {
        READY_TO_POUR = false;
    }
    
    if (READY_TO_POUR)
    {
        angle = -45;
    }
    else
    {
        angle = 0;
    }
    
    clampAngle();

}

void Skillet::draw()
{
    ofSetColor(255, 0, 0);
    ofRect(mouthPos,mouthWidth,mouthHeight);
}

void Skillet::mousePressed(int x, int y)
{
    
    for (int b = 0; b < bubbles.size();b++)
    {
        if (ofVec2f(x,y).distance(bubbles[b].bubblePos)<40)
        {
            contents.erase(contents.begin() + b);
            testApp * app = (testApp *)ofGetAppPtr();
            bubbles[b].content->HELD = true;
            bubbles[b].content->angle = 0;
            app->game.ingredients.push_back(bubbles[b].content);
            app->game.HOLDING_INGREDIENT = true;
            numContents--;
            break;
        }
    }
}

bool Skillet::add(Ingredient * _i)
{
    
    if (numContents < maxContents)
    {
        _i->drawScale = 2;
        contents.push_back(_i);
        
        numContents ++;
        return true;
    }
    else
    {
        return false;
    }
    
}

void Skillet::emptyToTrash()
{
    for (int c = 0; c < contents.size();c++)
    {
        contents[c]->type = "removeMe";
    }
    
    while (numContents > 0)
    {
        for (int c = 0; c < contents.size();c++)
        {
            removeFromSkillet(contents[c]);
        }
    }
    
    contents.clear();
    
    fillLvl = 0;
}

void Skillet::removeFromSkillet(Ingredient *i)
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    app->game.ingredients.push_back(i);
    
    for (int c = 0; c < contents.size();c++)
    {
        if (contents[c]->ID == i->ID)
        {
            contents.erase(contents.begin()+c);
            numContents--;
        }
    }
    
}

void Skillet::select()
{
    SELECTED = true;
    bubbles.clear();
    for (int c = 0; c < contents.size();c++)
    {
        int newAng = int(((c+1) * (180/(numContents+1)))-90);
        FoodBubble bubble = FoodBubble(mouthPos.x + ((c+1) * (mouthWidth/(numContents+1))),mouthPos.y - 10,newAng,redBubble, contents[c]);
        bubble.setup();
        bubbles.push_back(bubble);
    }
}

void Skillet::deselect()
{
    SELECTED = false;
    bubbles.clear();
    
}


void Skillet::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    if (SELECTED)
    {
        app->game.overlay(ofColor(4,11,68,127));
    }
    
    app->game.mainRenderer->addCenterRotatedTile(&skilletBack, pos.x, pos.y, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
    
    if (ACTIVE && HAS_CONTENTS)
    {
        app->game.mainRenderer->addCenteredTile(&steamAnim, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    }
    
    for (int c = 0; c < contents.size(); c++)
    {
        contents[c]->addSpriteToRenderer();
    }
    
    if (ACTIVE && HAS_CONTENTS)
    {
        app->game.mainRenderer->addCenteredTile(&sizzleAnim, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    }
    app->game.mainRenderer->addCenterRotatedTile(&skilletFront, pos.x, pos.y, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
    
    if (ACTIVE)
    {
        app->game.mainRenderer->addCenteredTile(&skilletFlameAnim, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    }
    
    if (SELECTED)
    {
        for (int b = 0; b < bubbles.size();b++)
        {
            bubbles[b].addSpriteToRenderer();
        }
    }
    
    
}
