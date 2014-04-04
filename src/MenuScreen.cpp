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
    
    introText = "PRESS SPACEBAR TO COOK FOR SPIRITS OKAY??";
    
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
