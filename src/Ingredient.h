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
#include "GameObject.h"
#include "ofxSpriteSheetRenderer.h"

static animation_t uncookedRice =
{	244,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
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
    245,0,1,1,1,75,0,-1,-1,1
};
static animation_t warmRice =
{
    244,0,1,1,1,75,0,-1,-1,1
};
static animation_t toastedRice =
{
    246,0,1,1,1,75,0,-1,-1,1
};
static animation_t dryCrackedRice =
{
    247,0,1,1,1,75,0,-1,-1,1
};
static animation_t lightlyBoiledRice =
{
    248,0,1,1,1,75,0,-1,-1,1
};
static animation_t boiledRice =
{
    249,0,1,1,1,75,0,-1,-1,1
};
static animation_t soggyRice =
{
    250,0,1,1,1,75,0,-1,-1,1
};
static animation_t crunchyRice =
{
    251,0,1,1,1,75,0,-1,-1,1
};
static animation_t ruined =
{
    252,0,1,1,1,75,0,-1,-1,1
};
static animation_t riceFlourAnim =
{
    253,0,1,1,1,75,0,-1,-1,1
};
static animation_t toastedRiceFlourAnim =
{
    254,0,1,1,1,75,0,-1,-1,1
};
static animation_t mochiAnim =
{
    255,0,1,1,1,75,0,-1,-1,1
};
static animation_t yakiMochiAnim =
{
    256,0,1,1,1,75,0,-1,-1,1
};
static animation_t daifukuAnim =
{
    257,0,1,1,1,75,0,-1,-1,1
};
static animation_t gomaDaifukuAnim =
{
    258,0,1,1,1,75,0,-1,-1,1
};
static animation_t greenTeaMochiAnim =
{
    259,0,1,1,1,75,0,-1,-1,1
};
static animation_t greenTeaDaifukuAnim =
{
    260,0,1,1,1,75,0,-1,-1,1
};
static animation_t kurogomaMochiAnim =
{
    261,0,1,1,1,75,0,-1,-1,1
};
static animation_t kurogomaDaifukuAnim =
{
    262,0,1,1,1,75,0,-1,-1,1
};
static animation_t caramelizedSugar =
{
    240,0,1,1,1,75,0,-1,-1,1
};
static animation_t simpleSyrup =
{
    241,0,1,1,1,75,0,-1,-1,1
};
static animation_t sugarAnim =
{
    242,0,1,1,1,75,0,-1,-1,1
};
static animation_t powderedSugarAnim =
{
    243,0,1,1,1,75,0,-1,-1,1
};
static animation_t rawRedBeansAnim =
{
    280,0,1,1,1,75,0,-1,-1,1
};
static animation_t cookedRedBeansAnim =
{
    281,0,1,1,1,75,0,-1,-1,1
};
static animation_t mashedRedBeansAnim =
{
    282,0,1,1,1,75,0,-1,-1,1
};
static animation_t sweetRedBeanPasteAnim =
{
    283,0,1,1,1,75,0,-1,-1,1
};
static animation_t sesameSeedsAnim =
{
    284,0,1,1,1,75,0,-1,-1,1
};
static animation_t blackSesameSeedsAnim =
{
    285,0,1,1,1,75,0,-1,-1,1
};
static animation_t powderedSesameSeedsAnim =
{
    286,0,1,1,1,75,0,-1,-1,1
};
static animation_t glowWormAnim =
{
    288,0,1,2,1,75,0,-1,-1,1
};
static animation_t lightlyBoiledGlowWormAnim =
{
    290,0,1,2,1,75,0,-1,-1,1
};
static animation_t boiledGlowWormAnim =
{
    292,0,1,2,1,75,0,-1,-1,1
};
static animation_t tastelessGlowWormAnim =
{
    294,0,1,2,1,75,0,-1,-1,1
};
static animation_t crispyBoiledGlowWormAnim =
{
    296,0,1,2,1,75,0,-1,-1,1
};
static animation_t crispyGlowWormAnim =
{
    298,0,1,2,1,75,0,-1,-1,1
};
static animation_t crunchyGlowWormAnim =
{
    300,0,1,2,1,75,0,-1,-1,1
};
static animation_t stickyGlowWormAnim =
{
    302,0,1,2,1,75,0,-1,-1,1
};
static animation_t glowWormPasteAnim =
{
    304,0,1,2,1,75,0,-1,-1,1
};
static animation_t rawOxAnim =
{
    320,0,1,2,1,75,0,-1,-1,1
};
static animation_t rottenOxAnim =
{
    322,0,1,2,1,75,0,-1,-1,1
};
static animation_t rawSalmonAnim =
{
    328,0,1,1,1,75,0,-1,-1,1
};
static animation_t grilledSalmonAnim =
{
    329,0,1,1,1,75,0,-1,-1,1
};
static animation_t rawSobaAnim =
{
    360,0,1,2,1,75,0,-1,-1,1
};
static animation_t greenTeaLeavesAnim =
{
    181,0,1,1,1,75,0,-1,-1,1
};
static animation_t rawGenMaiAnim =
{
    182,0,1,1,1,75,0,-1,-1,1
};
static animation_t matchaPwdrAnim =
{
    183,0,1,1,1,75,0,-1,-1,1
};
static animation_t greenTeaAnim =
{
    201,0,1,1,1,75,0,-1,-1,1
};
static animation_t GenMaiAnim =
{
    202,0,1,1,1,75,0,-1,-1,1
};
static animation_t matchaAnim =
{
    203,0,1,1,1,75,0,-1,-1,1
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
    NUM_FORMS
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

class Ingredient: public GameObject{
public:
    string type;
    
    
    TEXTURES texture;    // made up of combinations of form, hardness, and wetness.
    
    HARDNESSES hardness;
    FORMS form;
    WETNESSES wetness;
    ofVec2f offset;
    
    bool USED_IN_SUBDISH;
    
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
    
    ofFile ingList;
    
    string whenBoiled;
    string whenGrilled;
    string whenGround;
    string whenSits;
    
    string state;
    string displayName;
    
    Ingredient();
    
    Ingredient(string _type, int x, int y);
    
    virtual void setup();
    virtual void update();
    virtual void draw(int modx, int mody);
    virtual void getIngredientInfo();
    
    
};

#endif /* defined(__Combining__Ingredient__) */
