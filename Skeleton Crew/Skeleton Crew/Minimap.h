#pragma once
#ifndef MINIMAP_H
#define MINIMAP_H
#include "HUDElement.h"
#include <vector>
class Minimap:public HUDElement
{
public:
	///
	///constructor method: creates a new Minimap object using the information passed in
	///
	Minimap(float ,float);
	///
	///Destructor method: deletes this object at termination/clean up 
	///
	~Minimap(void);

	///
	///draws the islands and ships on the minimap
	///
	void drawStations(SDL_Renderer* renderer, vector<Station*> *stations, Vector2f offset);
private:
};
#endif