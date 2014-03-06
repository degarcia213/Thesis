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
    
    if (ON_GRILL && FULL && grill->ACTIVE)
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

void Pot::addSpriteToRenderer()
{
    
    testApp * app = (testApp *)ofGetAppPtr();
    
    app->game.mainRenderer->addCenteredTile(&potBack, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    
    if (fillLvl > 0)
    {
        if (BEING_FILLED)
        {
            app->game.addWater();
            app->game.mainRenderer->addCenteredTile(&fillPotAnim, pos.x + (1*drawScale), (pos.y + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
        else if (ACTIVE)
        {
            app->game.mainRenderer->addCenteredTile(&boilPotAnim, pos.x + (1*drawScale), (pos.y + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
        else
        {
            app->game.mainRenderer->addCenteredTile(&waterPotAnim, pos.x + (1*drawScale), (pos.y + (12*drawScale)) - (fillLvl * drawScale),0,F_NONE,drawScale,255,255,255,255);
        }
    }
    
    if (HAS_CONTENTS)
    {
        for (int c = 0; c < contents.size(); c++)
        {
            contents[c]->addSpriteToRenderer();
        }
    }
    
    app->game.mainRenderer->addCenteredTile(&potFront, pos.x, pos.y,0,F_NONE,drawScale,255,255,255,255);
    
    
}
