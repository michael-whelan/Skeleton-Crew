#pragma once
#ifndef BANKGUI_H
#define BANKGUI_H
#include "HUDElement.h"


class BankGUI: public HUDElement
{
private:
	bool openMenu;
public:
	BankGUI(float x,float y);
	void update(float timeElapsed);
	void draw(SDL_Renderer* renderer);
	void setMenu(bool b){openMenu = b;};
	bool getMenu(){return openMenu;};
	TTF_Font *font;
	SDL_Surface *message;
	SDL_Texture *text;
	SDL_Color textColour;
	float bankX, bankY, bankWidth, bankHeigth, btnRadius;
	static int bankGold;
	int tranferAmount, transferCount;
	Vector2f depositBtn,withdrawBtn, bankAmount, mousePos, slider, minusBtn, plusBtn;
	void setGold(int i){bankGold = i;};
	Station* currentStation;
	~BankGUI(void);
};
#endif

