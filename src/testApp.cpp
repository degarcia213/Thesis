#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
 
    //--INITIALIZE SCREENS--
    game = GameScreen();
    menu = MenuScreen();
    
    //--CURRENT SCREEN--
    currentScreen = &menu;
    currentScreen->setup();
    
    //--TIME HANDLER;
    time = TimeHandler(false);
    time.setup();
    
    ofSetMinMagFilters(GL_NEAREST, GL_NEAREST);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    currentScreen->update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
    currentScreen->draw();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    currentScreen->keyPressed(key);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    currentScreen->keyReleased(key);

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    currentScreen->mouseMoved(x,y);

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    currentScreen->mouseDragged(x,y,button);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    currentScreen->mousePressed(x, y, button);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    currentScreen->mouseReleased(x, y, button);
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}