#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Game.h"
#include "Menu.h"
#include <sstream>
#include <iostream>
///Controls whether the game of menu is active
class SceneManager
{
private:
	static SceneManager* me;//contains the scenemanager
	bool loadedGame;
	vector<Station*> *Loadedstations;
	vector<Crew*> *LoadedCrew;
	vector<EnemyCrew*> *LoadedUnit;
	vector<int> *hatsTotal;
public:
	SceneManager(void);
	~SceneManager(void);
	static SceneManager* getManager();///return self
	void saveGame();
	void loadGame();
	void update(float timeElapsed);///Run the current scene - game/menu
	void draw(SDL_Renderer* renderer);///Draw the current scene - game/menu
	Entity::entityType selectUnitType();
	Menu* menu;
	Game* game;
};
#endif

