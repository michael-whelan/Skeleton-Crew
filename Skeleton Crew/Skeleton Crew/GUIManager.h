#pragma once
#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "KeyManager.h"
#include "ShipIndicator.h"
#include "NotorietyIndicator.h"
#include "Minimap.h"
#include "HatMenu.h"
#include "GoldIndicator.h"
#include "UnitCommandIndicator.h"
#include "Shop.h"
#include "BankGUI.h"
#include <math.h>
#include <vector>
class GUIManager
{
private:
	///
	///Pointer to this manager
	///
	static GUIManager* me;

	///
	///pointer to an instance of the ShipIndicator class
	///
	ShipIndicator *shipIndicator;

	///
	///pointer to an instance of the NotorietyIndicator class
	///
	NotorietyIndicator *notorietyIndicator;

	///
	///pointer to an instance of the Minimap class
	///
	Minimap *minimap;

	///
	///pointer to an instance of the GoldIndicator class
	///
	GoldIndicator *goldIndicator;

	///
	///pointer to an instance of the UnitCommandIndicator class
	///
	UnitCommandIndicator *commandIndicator;

	///
	///pointer to an instance of the Shop class
	///
	Shop *shopScreen;

	///pointer to the Bank GUI
	BankGUI *bankScreen;

	vector<HUDElement*> *uiElements;
public:
	///
	///Constructor method of this class
	///
	GUIManager(void);

	///
	///Destructor method of this class
	///
	~GUIManager(void);

	///
	///returns the pointer to this class, allowing other methods to access public variables and methods
	///
	static GUIManager* getManager();

	///
	///Creates interactable interfaces
	///
	void createGUI();

	BankGUI* getBank(){return bankScreen;};

	HUDElement* getHatMenu(){return uiElements->at(1);};

	void setBank(int i){bankScreen->setGold(i);};

	Shop* getShop(){return shopScreen;};
	///
	///Draws GUI
	///
	void draw(SDL_Renderer* renderer, Vector2f offset);

	///
	///Updates GUI
	///
	void update(float timeElapsed);
};
#endif

