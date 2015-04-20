#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "SDL.h"
#include "SDL_ttf.h"
#include "Texture.h"
class TextureManager
{
private:
	static TextureManager* me;
public:
	TextureManager(void);
	~TextureManager(void);
	void loadTexture();
	static TextureManager* getManager();
	void createArrays();

	//backgrounds
	Texture *background1;
	Texture *background2;
	Texture *background3; 
	
	//boat stuff
	Texture *cannonBall;
	Texture *canon;
	Texture *canonTop;
	Texture *muzzleFlash;
	Texture *arrow;
	Texture *helm;
	Texture *pirateMast;
	Texture *pirateCrowNest;
	Texture *navyMast;
	Texture *navyCrowNest;
	Texture *ship;

	//boss boats
	Texture *dreadRobertsBoat;
	Texture *dreadRobertsHelm;
	Texture *mobyDick;
	Texture *dreadRobertsCrowNest;
	Texture *dreadRobertsMast;
	Texture *alienShip;
	Texture *bossShip;
	Texture *daveySails;
	Texture *daveyMast;
	Texture *daveyHelm;
	Texture *deathSails;
	Texture *deathMast;
	Texture *deathShip;
	Texture *fisherboat;
	Texture *neptunesWhale;

	//bosses
	Texture *krakenTentacle1;
	Texture *krakenTentacle2;
	Texture *krakenTentacle3;
	Texture *krakenTentacle4;
	Texture *krakenTentacle5;
	Texture *krakenTentacle6;
	Texture *alien;
	Texture *death;
	Texture *dreadRoberts;
	Texture *kingNeptune;
	Texture *davyJones;

	//boss units
	Texture *ghostPirate;

	//hats
	Texture *navyRank1;
	Texture *navyRank2;
	Texture *navyRank3;
	Texture *navyRank4;
	Texture *navyRank5;
	Texture *navyRank6;

	//pirate hats
	Texture *pirateRank1;
	Texture *pirateRank2;
	Texture *pirateRank3;
	Texture *pirateRank4;
	Texture *pirateRank5;
	Texture *pirateRank6;
	
	
	//islands
	Texture *bankIsland;
	Texture *emptyIsland;
	Texture *pirateCove;
	Texture *villageIsland;
	Texture *rockyIsland;
	Texture *villageIslandTwo;
	Texture *volcano;

	//misc
	Texture *goldChestClosed;
	Texture *goldChestOpen;
	Texture *circle;
	Texture *fogEffect;
	Texture *goldCoin;
	Texture *sword;
	Texture *tree;
	Texture *grapple;
	Texture *blank;

	//sea creatures
	Texture *hydraSmall;
	Texture *hydraLarge;
	Texture *jellyfish;
	Texture *octopusSmall;
	Texture *octopusLarge;
	Texture *squid;
	Texture *whale;
	Texture *whaleBottom;
	Texture *serpent;
	Texture *turtle;

	//units
	Texture *pirate;
	Texture *skeletonPirate;
	Texture *villager;
	Texture *navy;

	//HUD elements
	Texture *ship_indicator1;
	Texture *ship_indicator2;
	Texture *unit_indicator;
	Texture *minimap;
	Texture *gold_indicator;
	Texture *notoriety1;
	Texture *notoriety2;
	Texture *notoriety3;
	Texture *notoriety4;
	Texture *hatIcon;
	Texture *unitCommandIcon;
	Texture *blankBackground;
	Texture *shipMenuBottom;
	Texture *shipMenuBack;
	Texture *upArrow;
	Texture *downArrow;
	Texture *boardCommand;
	Texture *abandonCommand;
	Texture *lootCommand;
	Texture *mapShipTexture;
	Texture *mapIslandTexture;
	Texture *bankTexture;
	Texture *deposit;
	Texture *withdraw;
	Texture *bankAmount;
	Texture *plusDBbtn;
	Texture *minusDBbtn;

	//Shop images
	Texture *buyShipBack;
	Texture *buyShipBackTop;
	Texture *shipLvl1;
	Texture *shipLvl2;
	Texture *shipLvl3;
	Texture *upgradeUnitBack;
	Texture *upgradeShipBack;
	Texture *leftArrow;
	Texture *rightArrow;
	Texture *buyBtn;
	Texture *plusBtn;

	//menu 
	Texture *menu_screen;
	Texture *deatBackground;
	Texture *optionMenu;
	Texture *playBtn;
	Texture *playBtn2;
	Texture *quitBtn;
	Texture *quitBtn2;
	Texture *replayBtn;
	Texture *replayBtn2;
	Texture *backBtn;
	Texture *backBtn2;
	Texture *optionsBtn;
	Texture *optionsBtn2;
	Texture* upBtn; 
	Texture* downBtn; 
	Texture* leftBtn; 
	Texture* rightBtn; 
	Texture* grappleBtn; 
	Texture* assignBtn; 
	Texture* defaultBtn; 
	Texture* cannonUpBtn; 
	Texture* cannonDownBtn; 
	Texture* cannonLeftBtn; 
	Texture* cannonRightBtn;
	Texture* helmUpBtn; 
	Texture* helmDownBtn; 
	Texture* helmLeftBtn; 
	Texture* helmRightBtn;
	Texture* loadBtn; 
	Texture* loadBtn2;

	//font
	TTF_Font *font;
	TTF_Font *fontInner;
	TTF_Font *fontText;

};
#endif

