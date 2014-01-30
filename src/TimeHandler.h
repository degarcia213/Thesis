//
//  TimeHandler.h
//  Thesis_Time
//
//  Created by Diego Garcia on 12/8/13.
//
//

#ifndef __Thesis_Time__TimeHandler__
#define __Thesis_Time__TimeHandler__

#include <iostream>
#include "ofMain.h"

class TimeHandler{
public:
    
    TimeHandler();
    TimeHandler(bool _realTime);
    
    void setup();
    void update();
    void draw();
    void drawSunAndMoon();
    void activateMeteor();
    
    float meteorProgress();
    
    ofColor skyColor;
    ofColor nightColor;
    ofColor morningColor;
    ofColor afternoonColor;
    ofColor eveningColor;
    
    ofColor sunColor;
    ofColor moonColor;
    
    ofVec2f sunPosition;
    ofVec2f moonPosition;
    ofVec2f topCenter;
    ofVec2f horizonLeft;
    ofVec2f horizonRight;
    ofVec2f hidden;
    
    ofVec2f meteorStartPosition;
    ofVec2f meteorHitPosition;
    ofVec2f meteorPosition;
    
    int sunRadius;
    int moonRadius;
    
    bool realTime;
    bool meteorActive;
    float meteorSpottedTime;
    float meteorTime;
    float meteorHitTime;
    float meteorSize;
    int meteorStartSize;
    int meteorFinishSize;
    
    int hoursToImpact();
    
    bool METEOR_HIT;
    
    long startTime;
    float currentTime; // leave this a float.
    
    float morningTime;
    float afternoonTime;
    float nightTime;
    float eveningTime;
    
    int minutesPerDay;
    float timePerDay; // leave this a float.
    
    int currentDay;
    int currentHour;
    int oneHour;
    
    
};

#endif /* defined(__Thesis_Time__TimeHandler__) */
