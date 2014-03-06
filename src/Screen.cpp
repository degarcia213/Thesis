//
//  Screen.cpp
//  TIME
//
//  Created by Diego Garcia on 12/7/13.
//
//

#include "Screen.h"

Screen::Screen(){

}

Screen::Screen(TimeHandler * _time)
{
        time = _time;
}

void Screen::setup(){
    
}

void Screen::update(){
    
}

void Screen::draw(){
    
}

void Screen::overlay(ofColor _color, int _alpha)
{
    ofSetColor(_color,_alpha);
    ofRect(0,0,ofGetWidth(),ofGetHeight());
}

void Screen::keyPressed(int key){
    
}

void Screen::keyReleased(int key){
    
}

void Screen::mousePressed(int x,int y,int button)
{
    
}

void Screen::mouseDragged(int x,int y,int button)
{
    
}

void Screen::mouseReleased(int x,int y,int button)
{
    
}

void Screen::mouseMoved(int x,int y)
{
    
}