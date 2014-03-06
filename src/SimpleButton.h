//
//  simpleButton.h
//  backToTheKitchen
//
//  Created by Diego Garcia on 2/6/14.
//
//

#ifndef __backToTheKitchen__simpleButton__
#define __backToTheKitchen__simpleButton__

#include <iostream>
#include "GameObject.h"

class SimpleButton : public GameObject
{
public:
    SimpleButton();
    SimpleButton(int x,int y, int _width, int _height, string _text);

    virtual void draw();
    virtual void action();

    int width;
    int height;
    string text;

};

#endif /* defined(__backToTheKitchen__simpleButton__) */
