#pragma once
#ifndef SHIPINDICATOR_H
#define SHIPINDICATOR_H
#include "HUDElement.h"
#include <vector>
///This is the hud element that allows you to change which ship you are on
class ShipIndicator:public HUDElement
{
public:
	ShipIndicator(float x,float y);///xposition, yposition
	~ShipIndicator(void);
	void draw(SDL_Renderer* renderer);///draw element
	void menu();
	void update(float timeElapsed);///makes the element slide down correctly
private:
	vector<pair<Station*, int>> ships;///station paired with the number of crew aboard

	Texture* backGroundTexture;///the background of the slider
	Texture* backGroundTextureBottom;///the curved part of the slider
	Texture* upArrowTexture;///used to help with scrolling
	Texture* downArrowTexture;///used to help with scrolling
	float scrollLength;///the size of the menu to be shown
};
#endif