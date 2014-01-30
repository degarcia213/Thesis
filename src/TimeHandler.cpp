//
//  TimeHandler.cpp
//  Thesis_Time
//
//  Created by Diego Garcia on 12/8/13.
//
//

#include "TimeHandler.h"

TimeHandler::TimeHandler()
{
    
}

TimeHandler::TimeHandler(bool _realTime){
    
    realTime = _realTime;
    
    if (realTime)
    {
        minutesPerDay = 24 * 60;
        currentHour = ofGetHours();
        timePerDay = minutesPerDay*60*ofGetFrameRate();
        oneHour = timePerDay/24;
        currentDay = 1;
        
        currentTime = ofGetHours() * oneHour;
        currentTime += ofGetMinutes() * (oneHour/60);
        
        
    } else {
        
        minutesPerDay = 1;
        currentDay = 1;
        startTime = 0;
        currentTime = startTime;
        currentHour = 0;
        timePerDay = minutesPerDay*60*ofGetFrameRate();
        oneHour = timePerDay/24;
        
    }
    

    
}

void TimeHandler::setup(){
    
    
    /// CHANGE THIS TO AFFECT THE WAY THE DAY WORKS
    
    /// INITIALIZE COLORS OF SKY
    
    nightColor.set(42,53,102);
    eveningColor.set(244,124,155);
    afternoonColor.set(165,255,248);
    morningColor.set(221,255,246);
    
    skyColor = eveningColor;
    
    sunRadius = 100;
    moonRadius = 80;
    
    topCenter.set(ofGetWidth()/2,40);
    horizonLeft.set(100,200);
    horizonRight.set(ofGetWidth()-100,200);
    hidden.set(ofGetWidth()/2,500);
    
    
    meteorStartSize = 20;
    meteorSize = meteorStartSize;
    meteorFinishSize = 120;
    meteorStartPosition.set(ofGetWidth() - 200,20);
    meteorHitPosition.set(ofGetWidth()/2,200);
    meteorPosition = meteorStartPosition;
    
    METEOR_HIT = false;
    
    activateMeteor();
    
}

void TimeHandler::update(){
    
    
    if(realTime)
    {
        
    }
    else
    {
        if (currentTime < timePerDay){
            currentTime ++;
        } else {
            currentTime = 0;
            currentDay++;
        }
    }
    
    if (meteorActive){
        meteorTime = (((currentDay-1) * timePerDay) + currentTime) - meteorSpottedTime;
        
        meteorPosition = meteorStartPosition + ((meteorHitPosition - meteorStartPosition) * meteorProgress());
        
        meteorSize = meteorStartSize + ((meteorFinishSize - meteorStartSize) * meteorProgress());
        
    }
    
    currentHour = int((currentTime / timePerDay)*24);
    
    if (currentHour < 6)
    {
        skyColor = nightColor.getLerped(morningColor, currentTime/(timePerDay/4));
        sunPosition = horizonRight;
        moonPosition = horizonLeft;
    }
    else if (currentHour < 12)
    {
        skyColor = morningColor.getLerped(afternoonColor, (currentTime- (timePerDay/4))/(timePerDay/4));
        sunPosition = topCenter;
        moonPosition - hidden;
    }
    else if (currentHour < 18)
    {
        skyColor = afternoonColor.getLerped(eveningColor, (currentTime- (timePerDay/2))/(timePerDay/4));
        sunPosition = horizonLeft;
        moonPosition = horizonRight;
        
    }
    else if (currentHour < 24)
    {
        skyColor = eveningColor.getLerped(nightColor, (currentTime- ((timePerDay/4)*3))/(timePerDay/4));
        sunPosition = hidden;
        moonPosition = topCenter;
    }
    
}

void TimeHandler::draw(){
    
}

float TimeHandler::meteorProgress()
{
    cout << ofToString((meteorTime - meteorSpottedTime) / meteorHitTime) + "\n";
    return (meteorTime - meteorSpottedTime) / meteorHitTime;
}

int TimeHandler::hoursToImpact()
{
    return (meteorHitTime - meteorTime)/oneHour;
}

void TimeHandler::activateMeteor()
{
    meteorActive = true;
    meteorSpottedTime = currentTime;
    meteorHitTime = meteorSpottedTime + ( 10 * timePerDay);
}

void TimeHandler::drawSunAndMoon()
{
    ofSetColor(sunColor);
    ofCircle(sunPosition, sunRadius);
    
    ofSetColor(moonColor);
    ofCircle(moonPosition, moonRadius);
    
    ofSetColor(0,0,0);
    ofCircle(meteorPosition, meteorSize);
}
