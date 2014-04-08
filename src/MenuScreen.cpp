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
    
    introText = "The following is a work in progress.\n\nYou play as a chef trapped in the spirit world after\noffendinng their culinary tastes. Use your mouse to\nmaster their ingredients and create their favorite dishes.\n\nPress the spacebar to begin.";
    
}

///-----
void MenuScreen::update()
{
    
}

///-----
void MenuScreen::draw()
{
    
    ofSetColor(150,150,150);
    ofDrawBitmapString(introText, ofPoint(20,ofGetHeight()/2 + 1));
    ofSetColor(0,0,0);
    ofDrawBitmapString(introText, ofPoint(20,ofGetHeight()/2));
    
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
