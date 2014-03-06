//
//  ServeBtn.cpp
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/6/14.
//
//

#include "ServeBtn.h"
#include "testApp.h"

ServeBtn::ServeBtn(){
    
}

ServeBtn::ServeBtn(int x, int y):SimpleButton(x,y,50,20,"SERVE!"){

}

void ServeBtn::action()
{
    SimpleButton::action();
    cout << "fart";
    testApp * app = (testApp *)ofGetAppPtr();
    app->game.serveCustomer();
}