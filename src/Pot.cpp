//
//  Pot.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/22/14.
//
//

#include "Pot.h"
#include "testApp.h"

Pot::Pot():GameObject()
{
    
}

Pot::Pot(int x, int y):GameObject(x,y)
{
    
}

void Pot::setup()
{
    GameObject::setup();
    size = 40;
    
    ACTIVE = false;
    HAS_CONTENTS = false;
    BEING_FILLED = false;
    IN_SINK = false;
    FULL = false;
    ON_GRILL = false;
    fillLvl = 0;
    maxFill = 10;
    numContents = 0;
    maxContents = 3;
    angle = 0;
    SELECTED = false;
    BURNER_ACTIVE = false;
    READY_TO_POUR = false;
    READY_TO_TRASH = false;
    READY_TO_PLATE = false;
    
    mouthPos.set(pos.x - 40, pos.y - 40);
    mouthWidth = 80;
    mouthHeight = 20;
    

    for (int i = 0; i < maxContents; i++)
    {
        contentPos.push_back(ofVec2f(i+1*(mouthWidth/maxContents),mouthHeight/2));
        contentDir.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)).normalize());
    }
}

void Pot::update()
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
            contentPos[c]+= contentDir[c];
            contents[c]->boilTime ++;
            contents[c]->angle ++;
            
            if (contentPos[c].x > mouthWidth || contentPos[c].x < 0)
            {
                contentDir[c].x *= -1;
            }
            
            else if (contentPos[c].y > mouthHeight || contentPos[c].y < 0)
            {
                contentDir[c].y *= -1;
            }
        }
        
        contents[c]->pos = mouthPos + contentPos[c];
        contents[c]->update();
    }
    
    if(IN_SINK)
    {
        pos.set(sink->pos.x,sink->pos.y + 10);
        
        if(sink->ACTIVE)
        {
            BEING_FILLED = true;
        }
        else
        {
            BEING_FILLED = false;
        }
        
    }
    else
    {
        BEING_FILLED = false;
    }
    
    if (BEING_FILLED)
    {
        fill();
    }
    
    if (ON_GRILL && FULL && BURNER_ACTIVE)
    {
        ACTIVE = true;
    }
    else
    {
        ACTIVE = false;
    }
    
    mouthPos.set(pos.x - 40, pos.y - 40);
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
    
    for (int c = 0; c < contents.size(); c++)
    {
        contents[c]->drawScale = drawScale;
    }
    
    if (READY_TO_TRASH || READY_TO_PLATE)
    {
        READY_TO_POUR = true;
    }
    else
    {
        READY_TO_POUR = false;
    }
    
    if (!ON_GRILL)
    {
        BURNER_ACTIVE = false;
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

void Pot::mousePressed(int x, int y)
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

void Pot::removeFromPot(Ingredient * i)
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

bool Pot::add(Ingredient * _i)
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

void Pot::fill()
{
    if (fillLvl < maxFill)
    {
        fillLvl++;
    }
    else
    {
        fillLvl = maxFill;
        FULL = true;
    } 
}

void Pot::select()
{
    SELECTED = true;
    bubbles.clear();
    for (int c = 0; c < contents.size();c++)
    {
        int newAng = int(((c+1) * (180/(numContents+1)))-90);
        FoodBubble bubble = FoodBubble(mouthPos.x + ((c+1) * (mouthWidth/(numContents+1))),mouthPos.y - 10,newAng,blueBubble, contents[c]);
        bubble.setup();
        bubbles.push_back(bubble);
    }
}

void Pot::deselect()
{
    SELECTED = false;
    bubbles.clear();
    
}

void Pot::emptyToDish(Dish * d)
{
    
    if (d == NULL)
    {
        testApp * app = (testApp *) ofGetAppPtr();
        d = new Dish(app->game.plate.pos.x,app->game.plate.pos.y);
        app->game.dishes.push_back(d);
        d->setup();
    }
    while (numContents > 0)
    {
        for (int c = 0; c < contents.size(); c++)
        {
            removeFromPot(contents[c]);
            d->addIngredient(contents[c]);
            numContents--;
        }
    }
    
    contents.clear();
}


void Pot::emptyToTrash()
{
    for (int c = 0; c < contents.size();c++)
    {
        contents[c]->type = "removeMe";
    }
    
    while (numContents > 0)
    {
        for (int c = 0; c < contents.size();c++)
        {
            removeFromPot(contents[c]);
        }
    }
    
    contents.clear();
    FULL = false;
    fillLvl = 0;
    
}

void Pot::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    if (SELECTED)
    {
        app->game.overlay(ofColor(4,11,68,127));
    }
    app->game.mainRenderer->addCenterRotatedTile(&potBack, pos.x, pos.y, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
    
    if (fillLvl > 0)
    {
        if (BEING_FILLED)
        {
            app->game.addWater();
            app->game.mainRenderer->addCenteredTile(&fillPotBackAnim, mouthPos.x + mouthWidth/2, ((mouthPos.y + mouthHeight/2) + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
        else if (ACTIVE)
        {
            app->game.mainRenderer->addCenteredTile(&boilPotBackAnim, mouthPos.x + mouthWidth/2, ((mouthPos.y + mouthHeight/2) + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
        else
        {
            app->game.mainRenderer->addCenteredTile(&waterPotBackAnim, mouthPos.x + mouthWidth/2, ((mouthPos.y + mouthHeight/2) + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
    }
    
    if (HAS_CONTENTS)
    {
        for (int c = 0; c < contents.size(); c++)
        {
            contents[c]->drawScale = drawScale;
            contents[c]->addSpriteToRenderer();
        }
    }
    
    if (fillLvl > 0)
    {
        if (BEING_FILLED)
        {
            app->game.addWater();
            app->game.mainRenderer->addCenteredTile(&fillPotFrontAnim, mouthPos.x + mouthWidth/2, ((mouthPos.y + mouthHeight/2) + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
        else if (ACTIVE)
        {
            app->game.mainRenderer->addCenteredTile(&boilPotFrontAnim, mouthPos.x + mouthWidth/2, ((mouthPos.y + mouthHeight/2) + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
        else
        {
            app->game.mainRenderer->addCenteredTile(&waterPotFrontAnim, mouthPos.x + mouthWidth/2, ((mouthPos.y + mouthHeight/2) + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
    }
    app->game.mainRenderer->addCenterRotatedTile(&potFront, pos.x, pos.y, 0, F_NONE, drawScale, angle, NULL, 255,255,255,255);
    
    if (ON_GRILL && BURNER_ACTIVE)
    {
        app->game.mainRenderer->addCenteredTile(&skilletFlameAnim, pos.x + 10, pos.y + 12,0,F_NONE,drawScale,255,255,255,255);
    }
    
    if (SELECTED)
    {
        for (int b = 0; b < bubbles.size();b++)
        {
            bubbles[b].addSpriteToRenderer();
        }
    }
    
    
    
}
