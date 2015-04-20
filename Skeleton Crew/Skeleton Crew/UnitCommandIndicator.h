#pragma once
#ifndef UNITCOMMANDINDICATOR_H
#define UNITCOMMANDINDICATOR_H
#include "HUDElement.h"
#include <vector>
#include <functional>
using namespace std;
class UnitCommandIndicator:public HUDElement
{
public:
	UnitCommandIndicator(float, float);
	~UnitCommandIndicator(void);
	void draw(SDL_Renderer* renderer);
	void update(float timeElapsed);

private:
	vector<pair<string, void (UnitCommandIndicator::*)()>> commands;

	Vector2f boardPos;
	Vector2f abandonPos;
	Vector2f lootPos;

	void detach();
	void loot();
	void board();

	Texture* backGroundTexture;///the background of the slider
};
#endif