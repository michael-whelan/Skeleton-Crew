#pragma once
#ifndef HATMENU_H
#define HATMENU_H
#include "HUDElement.h"
#include <vector>
class HatMenu:public HUDElement
{
public:
	///
	///Constructor method for HatMenu class
	///
	HatMenu(float x,float y);

	///
	///Destructor method for HatMenu class
	///
	~HatMenu(void);
	void setAdm(int f){hats.at(5).second =f;};
	void setCpt(int f){hats.at(4).second =f;};
	void setLtn(int f){hats.at(3).second =f;};
	void setCPO(int f){hats.at(2).second= f;};
	void setPO(int f){hats.at(1).second = f;};
	void setSM(int f){hats.at(0).second = f;};

	void setHats(int index);///returns the hats
	///
	///Draws HatMenu
	///
	void draw(SDL_Renderer* renderer);

	///
	///Returns radius of the HatMenu icon to check if player has clicked on it
	///
	float getRadius();

	Unit::hatUpgrades getHat(int);

	int getIndex(Unit::hatUpgrades);
	///
	///changes state of the menu when called, depending on what its current state is
	///
	void menu();

	///
	///updates HatMenu
	///
	void update(float timeElapsed);
private:
	///
	///vector pair that stores the texture of each kind of hat and how many of each hat the player has
	///
	vector<pair<Texture*, int>> hats;


};
#endif