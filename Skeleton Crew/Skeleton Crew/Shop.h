#pragma once
#include "TextureManager.h"
#include "HUDElement.h"
#include "HatMenu.h"


///The GUI that controls the buying of ship upgrades, unit hats and ships
class Shop: public HUDElement
{
public:
	Shop(float x,float y);
	enum states///controls which menu is active
	{
		upgradeShip,
		upgradeUnit,
		buyShip
	};
	states myState;///the current active menu
	Vector2f getTab1(){return *tab1Pos;};///
	Vector2f getTab2(){return *tab2Pos;};///These are the positions of each of the tabs that cycle the different menus
	Vector2f getTab3(){return *tab3Pos;};///
	bool getAlive(){return alive;};
	void update(float timeElapsed,float,float,Station*, HatMenu* );///recieves mouse position, used for finding where was clicked
	int getValue(float);
	float setValue(int);
	void draw(SDL_Renderer* renderer);///Draw the shop
	void drawTop(SDL_Renderer* renderer);
	void drawBuyShip(SDL_Renderer* renderer);
	void drawUpgradeShip(SDL_Renderer* renderer);
	void drawBuyHats(SDL_Renderer* renderer);
	float getRadius(){ return 100;};///the size of the tab radius - for mouse collision
	float val;
	void setAlive(bool){alive = true;}
	~Shop(void);

private:
	bool alive;
	SDL_Rect *srcRec;
	Vector2f *tab1Pos,*tab2Pos,*tab3Pos;///the tab positions
	Vector2f *arrowPosLeft,*arrowPosRight;///the positions of thew arrows for the ship buy menu
	Vector2f *buyBtn;///the position of the buy button when buying ships 
	vector <pair<SDL_Texture*,int>>ships;///ships and their prices for buyships
	vector<pair<SDL_Texture*, int>> hats;///hats and their prices
	vector<pair<Vector2f,int>>plusBtnPos;///position of the plus icon and the width of the bar
	vector<int>upgradePrices;///prices of ship upgrades
	vector<Vector2f>buyBtnPos;///buy button position in the hats screen
	Vector2f *shipScale,*shipPos;///
	float xStop;///the stop xpos for cycling through ships to buy
	int next;///next ship in cycle
	int current;///current ship in cycle
	bool change;///bool to start moving the ships so you can cycle through
};

