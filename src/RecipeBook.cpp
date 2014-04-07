//
//  RecipeBook.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 4/4/14.
//
//

#include "RecipeBook.h"

RecipeBook::RecipeBook():GameObject()
{
    
}

RecipeBook::RecipeBook(int x, int y):GameObject(x,y)
{
    drawScale = 2;
    width = 40 * drawScale;
    height = 35 * drawScale;
    hitBoxPos.set(pos.x - width/2,pos.y-height/2);
    
    
    IN_USE = false;
    recipeFont.loadFont("fonts/pixel_maz.ttf", 24);
    recipeFont.setLineHeight(12);
    currentPage = 0;
    currentEntry = 0;
    
    bigPos.set(250 * drawScale, ofGetHeight()-(64*drawScale));
    bigWidth = 376 * drawScale;
    bigHeight = 188 * drawScale;
    bigHitBoxPos.set(bigPos.x - (bigWidth/2), bigPos.y - (bigHeight/2));
    
    leftPageTextLocation.set(80 * drawScale, 130 * drawScale);
    rightPageTextLocation.set(265 * drawScale, 130 * drawScale);
    
}

void RecipeBook::update()
{
    GameObject::update();
    
    if (HIGHLIGHTED)
    {
        anim = recipeBookHighlightAnim;
    }
    else
    {
        anim = recipeBookAnim;
    }
    
    hitBoxPos.set(pos.x - width/2,pos.y-height/2);
    bigHitBoxPos.set(bigPos.x - (bigWidth/2), bigPos.y - (bigHeight/2));
    
}

void RecipeBook::draw()
{
        ofSetColor(0,0,0);
        recipeFont.drawString(pages[currentPage], leftPageTextLocation.x, leftPageTextLocation.y);
        recipeFont.drawString(pages[currentPage+1], rightPageTextLocation.x, rightPageTextLocation.y);
    
}

void RecipeBook::importRecipes()
{
    recipeList.open("dishes.txt");
    allRecipes = recipeList.readToBuffer();
    recipeList.close();
    
    string currentLine = allRecipes.getFirstLine();
    while (!allRecipes.isLastLine())
    {
        Recipe r = Recipe(currentLine,
                          currentLine.substr(currentLine.find("= ")+2,currentLine.length()-1));
        recipes.push_back(r);
        currentLine = allRecipes.getNextLine();
        
    }
    
    createPages();
    
}

void RecipeBook::createPages()
{
    pages.clear();
    
    string thisPage = "";
    totalPages = 0;
    
    for (int r = 0; r < recipes.size();r++)
    {
        string thisRecipe;
        thisRecipe = recipes[r].displayText;
        if (thisRecipe.length() > 20) {
            thisRecipe.insert(thisRecipe.find("+"), "\n ");
        }
        thisPage += thisRecipe + "\n\n";
        
        if (currentEntry < 5)
        {
            currentEntry++;
        }
        else
        {
            pages.push_back(thisPage);
            thisPage.clear();
            totalPages ++;
            currentEntry = 0;
        }
    }
    
    
    
}

void RecipeBook::revealRecipe(string _dishName)
{
    for (int r = 0; r < recipes.size();r++)
    {
        if (recipes[r].dishName == _dishName) {
            recipes[r].KNOWN = true;
            recipes[r].update();
            cout << "REVEALED:" + _dishName;
        }
    }
    
    createPages();
}

void RecipeBook::turnPageFwd()
{
    currentPage += 2;
}

void RecipeBook::turnPageBckwd()
{
    currentPage -= 2;
}