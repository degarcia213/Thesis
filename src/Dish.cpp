//
//  Dish.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/5/14.
//
//

#include "Dish.h"
#include "testApp.h"

Dish::Dish():GameObject()
{
    
}

Dish::Dish(int x,int y):GameObject(x,y)
{
    
    setup();
    
}

void Dish::setup()
{
    GameObject::setup();
    HOLDABLE = true;
    baseCount = 0;
    garnishCount = 0;
    HAS_BROTH = false;
    complexity = 0;
    balance = 0;
    
    sweetness = 0;
    saltiness = 0;
    sourness = 0;
    fattiness = 0;
    bitterness = 0;
    umami = 0;
    
    size = 50;
    
    EXISTS = false;
    SHOWING_CONTENTS = false;
    REMOVE_ME = false;
}

void Dish::update()
{
    GameObject::update();
    
    if (HAS_BROTH || baseCount > 0 || garnishCount > 0)
    {
        EXISTS = true;
    }
    
    for (int b = 0; b < baseCount;b++)
    {
        base[b]->pos = pos;
    }
    if (HAS_BROTH)
    {
        broth->pos = pos;
    }
    for (int g = 0; g < garnishCount;g++)
    {
        garnish[g]->pos = pos;
    }
    
    
}

void Dish::addIngredient(Ingredient * _i)
{
    
    bool wasAdded = false;
    
    if (_i->CAN_BE_BASE)
    {
        if (baseCount == 0)
        {
            base[0] = _i;
            baseCount ++;
            wasAdded = true;
            
        } else if (baseCount < MAX_BASE_COUNT){
            if (_i->form == BROTH)
            {
                if (base[0]->form != BROTH)
                {
                    broth = _i;
                    HAS_BROTH = true;
                    wasAdded = true;
                }
            } else if (base[0]->form == BROTH) {
                broth = base[0];
                base[0] = _i;
                HAS_BROTH = true;
                wasAdded = true;
            }
            else
            {
            base[baseCount] = _i;
            baseCount ++;
            wasAdded = true;
            }
        }
    }
    else
    {
        if (garnishCount < MAX_GARNISH_COUNT)
        {
            garnish[garnishCount] = _i;
            garnishCount+=1;
            wasAdded = true;
        }
        
    }
    
    if (wasAdded)
    {
        sweetness += _i->sweetness;
        saltiness += _i->saltiness;
        sourness += _i->sourness;
        fattiness += _i->fattiness;
        bitterness += _i->bitterness;
        umami += _i->umami;
        
    }
    
    displayName = createName();
    calculateBalance();
    
    if (!wasAdded)
    {
        testApp* app = (testApp *)ofGetAppPtr();
        app->game.addIngredient(_i->type,app->game.finalPlate.x + 20, app->game.finalPlate.y);
    }
}

void Dish::removeIngredient(int _ID)
{
    
    bool wasRemoved = false;
    Ingredient * removed;
    
    for (int b = 0; b < baseCount; b++)
    {
      if(base[b]->ID == _ID)
      {
          if (b < baseCount-1)
          {
              base[b]=base[b+1];
          }
          baseCount-=1;
          removed = base[b];
          wasRemoved = true;
      }
    }
    
    if (HAS_BROTH)
    {
        if (broth->ID == _ID)
        {
            HAS_BROTH = false;
            wasRemoved = true;
            removed = broth;
        }
    }
    
    for (int g = 0; g < garnishCount; g++)
    {
        if(garnish[g]->ID == _ID)
        {
            if (g < garnishCount-1)
            {
                garnish[g]=garnish[g+1];
            }
            garnishCount-=1;
            wasRemoved = true;
            removed = garnish[g];
        }
    }
    
    if (wasRemoved)
    {
        
        sweetness -= removed->sweetness;
        saltiness -= removed->saltiness;
        sourness -= removed->sourness;
        fattiness -= removed->fattiness;
        bitterness -= removed->bitterness;
        umami -= removed->umami;
        
    }
    
    displayName = createName();
    calculateBalance();
    
    
}

string Dish::createName(){
    
    string name;
    
    if (!HAS_SUBDISH)
    {
        if (baseCount > 0)
        {
            name += base[0]->displayName;
            for (int b = 1; b < baseCount;b++)
            {
                name += " and " + base[b]->displayName;
            }
        }
        
        if (HAS_BROTH)
        {
            name += " in " + broth->displayName;
        }
        
        if (garnishCount > 0)
        {
            if (baseCount > 0)
            {
                name += " with " + garnish[0]->displayName;
            }
            else
            {
                name += garnish[0]->displayName;
            }
            
            for (int g = 1; g < garnishCount; g++)
            {
                name += " and " + garnish[g]->displayName;
            }
        }
    }
    else
    {
        name = subdish;
        
        if (baseCount > 0)
        {
            if (!base[0]->USED_IN_SUBDISH)
            {
            name += "with " + base[0]->displayName;
            }
            for (int b = 1; b < baseCount;b++)
            {
                if (!base[b]->USED_IN_SUBDISH)
                {
                    if (!base[0]->USED_IN_SUBDISH)
                    {
                        name += " and " + base[b]->displayName;
                    }
                    else
                    {
                        name += " with " + base[b]->displayName;
                    }
                }
            }
        }
        
        if (HAS_BROTH)
        {
            if (!broth->USED_IN_SUBDISH)
            {
            name += " in " + broth->displayName;
            }
        }
        
        if (garnishCount > 0)
        {
            if (!garnish[0]->USED_IN_SUBDISH)
            {
                name += " with " + garnish[0]->displayName;
            }
            
            for (int g = 1; g < garnishCount; g++)
            {
                if (garnish[g]->USED_IN_SUBDISH)
                {
                    name += " and " + garnish[g]->displayName;
                }
            }
        }
        
    }

    return name;
}

void Dish::calculateBalance()
{
    
    balance = 10;
    complexity = 0;
    int balanceMod = 0;
    
    if (sweetness > 0)
    {
        balanceMod += sweetness;
        complexity += 1;
    }
    if (saltiness > 0)
    {
        balanceMod += saltiness;
        complexity += 1;
    }
    if (sourness > 0)
    {
        balanceMod += sourness;
        complexity += 1;
    }
    if (fattiness > 0)
    {
        balanceMod += fattiness;
        complexity += 1;
    }
    if (bitterness > 0)
    {
        balanceMod += bitterness;
        complexity += 1;
    }
    if (umami > 0)
    {
        balanceMod += umami;
        complexity += 1;
    }
    
    if (balanceMod > 0)
    {
        balanceMod/=complexity;
        
        balance -= balanceMod;
        if (balance < 0)
        {
            balance = 0;
        }
    }
    
    vector<int> flavors;
    flavors.push_back(sweetness);
    flavors.push_back(saltiness);
    flavors.push_back(sourness);
    flavors.push_back(fattiness);
    flavors.push_back(bitterness);
    flavors.push_back(umami);
    
    prominentFlavor = flavors[0];
    for (int f = 1; f < flavors.size();f++)
    {
        if (flavors[f] > prominentFlavor)
        {
            prominentFlavor = flavors[f];
        }
    }
    
    
}

bool Dish::CONTAINS(string _t)
{
    bool containsIt = false;
    for (int b = 0; b < baseCount;b++)
    {
        if (base[b]->type == _t)
        {
            containsIt = true;
        }
    }
    if (HAS_BROTH)
    {
        if (broth->type == _t)
        {
            containsIt = true;
        }
    }
    for (int g = 0; g < garnishCount;g++)
    {
        if (garnish[g]->type == _t)
        {
            containsIt = true;
        }
    }
    
    if (containsIt)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Dish::draw()
{
    if (EXISTS)
    {
    GameObject::draw();
    ofDrawBitmapString(displayName, pos.x + modx,pos.y + mody + 50);
        
        if (SHOWING_CONTENTS)
        {
            for (int b = 0; b < baseCount;b++)
            {
                base[b]->draw(0, 0);
            }
            if (HAS_BROTH)
            {
                broth->draw(0, 0);
            }
            for (int g = 0; g < garnishCount;g++)
            {
                garnish[g]->draw(0, 0);
            }
        }
    }
}

void Dish::addSpriteToRenderer()
{
    testApp* app = (testApp *)ofGetAppPtr();
    
    for (int b = 0; b < baseCount;b++)
    {
        base[b]->addSpriteToRenderer();
    }
    if (HAS_BROTH)
    {
        broth->addSpriteToRenderer();
    }
    for (int g = 0; g < garnishCount;g++)
    {
        garnish[g]->addSpriteToRenderer();
    }
    
}