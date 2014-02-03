//
//  Ingredient.h
//  Combining
//
//  Created by Diego Garcia on 10/22/13.
//
//

#ifndef __Combining__Ingredient__
#define __Combining__Ingredient__

#include <iostream>
#include <string>
#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"

static animation_t uncookedRice =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
	0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
	1,	/* .totalframes		(int) - the animation length in frames																												*/
	1,	/* .width			(int) - the width of each animation frame in tiles																									*/
	1,	/* .height			(int) - the height of each animation frame in tiles																									*/
	75,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
	0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
	-1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
	-1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
	1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

static animation_t brownedRice =
{
    1,0,1,1,1,75,0,-1,-1,1
};
static animation_t warmRice =
{
    0,0,1,1,1,75,0,-1,-1,1
};
static animation_t toastedRice =
{
    2,0,1,1,1,75,0,-1,-1,1
};
static animation_t dryCrackedRice =
{
    3,0,1,1,1,75,0,-1,-1,1
};
static animation_t lightlyBoiledRice =
{
    4,0,1,1,1,75,0,-1,-1,1
};
static animation_t boiledRice =
{
    5,0,1,1,1,75,0,-1,-1,1
};
static animation_t soggyRice =
{
    6,0,1,1,1,75,0,-1,-1,1
};
static animation_t crunchyRice =
{
    7,0,1,1,1,75,0,-1,-1,1
};
static animation_t ruined =
{
    8,0,1,1,1,75,0,-1,-1,1
};

enum Ing_State{
    FRESH,
    PICKLED,
    ROTTEN,
    OVER_RIPE,
    DRIED,
    SALTED,
    STEAMED,
    BAKED,
    BROILED,
    GRILLED,
    FRIED,
    SMOKED,
};

enum TEXTURES{
    ROCK_LIKE,
    STICKY,
    PASTY,
    CREAMY,
    SANDY,
    CRISPY,
    CRISP,
    SOUPY,
    SOGGY,
    DENSE,
    CRUNCHY,
    JUICY,
    MOIST,
    FLUFFY
};

enum FORMS {
    SLAB,
    SLICED,
    CUBES,
    GRAINS,
    NOODLES,
    PASTE,
    POWDER,
    PUREE,
    SYRUP,
    LIQUID,
    BROTH,
    GARNISH,
    DOUGH,
};

enum HARDNESSES {
    TOUGH,
    MEDIUM_TOUGH,
    SOFT,
};

enum WETNESSES {
    DRIPPING,
    DAMP,
    DRY
};

class Ingredient{
public:
    string type;
    
    
    TEXTURES texture;    // made up of combinations of form, hardness, and wetness.
    
    HARDNESSES hardness;
    FORMS form;
    WETNESSES wetness;
    
    ofVec2f pos;
    ofVec2f offset;
    
    bool BEINGHELD;
    
    bool CAN_BE_BASE;
    
    float boilTime;
    float grillTime;
    float grindTime;
    float sitTime;
    
    map <string,FORMS> forms;
    
    int boilLvl;
    int grillLvl;
    int grindLvl;
    int freshLvl;
    
    float quality;
    string desiredCook;
    int desiredCookLvl;
    int pickiness;
    
    int sweetness;
    int saltiness;
    int fattiness;
    int sourness;
    int bitterness;
    int umami;
    
    int stinkiness;
    
    int complexity;
    int balance;
    
    animation_t anim;
    
    ofFile ingList;
    
    string whenBoiled;
    string whenGrilled;
    string whenGround;
    string whenSits;
    
    string state;
    string name;
    
    Ingredient();
    
    Ingredient(string _type, int x, int y);
    
    virtual void setup();
    virtual void update();
    virtual void draw(int modx, int mody);
    virtual void getIngredientInfo();
    
    
};

#endif /* defined(__Combining__Ingredient__) */
