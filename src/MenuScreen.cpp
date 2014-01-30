//
//  MenuScreen.cpp
//  Combining
//
//  Created by Diego Garcia on 1/8/14.
//
//

#include "MenuScreen.h"
#include "testApp.h"

///-----
MenuScreen::MenuScreen()
{
    
}

///-----
MenuScreen::MenuScreen(TimeHandler * _time)
{
    
}

///-----
void MenuScreen::setup()
{
    
}

///-----
void MenuScreen::update()
{
    
}

///-----
void MenuScreen::draw()
{
    
    ofSetColor(150,150,150);
    ofDrawBitmapString("you have been trapped in the world of the spirits after offending their culinary tastes.\nIn order to return to your world you must learn their recipes and master the preparation of their favorite dishes.\nExperiment with the ingredients you acquire. Fill your recipe book and raise the status of your humble restaurant.\n\nPRESS SPACE TO BEGIN.", ofPoint(20,ofGetHeight()/2 + 1));
    ofSetColor(0,0,0);
    ofDrawBitmapString("you have been trapped in the world of the spirits after offending their culinary tastes.\nIn order to return to your world you must learn their recipes and master the preparation of their favorite dishes.\nExperiment with the ingredients you acquire. Fill your recipe book and raise the status of your humble restaurant.\n\nPRESS SPACE TO BEGIN.", ofPoint(20,ofGetHeight()/2));
    
}

///-----
void MenuScreen::keyPressed(int key)
{
    switch (key)
    {
        case ' ':
            testApp* app = (testApp*)ofGetAppPtr();
            app->currentScreen = &app->game;
            app->currentScreen->setup();
            break;
    }
}
