#pragma once
#ifndef VILLAGEISLAND_H
#define VILLAGEISLAND_H
#include "GoldChest.h"
#include "Villager.h"
#include "Island.h"
class VillageIsland:public Island
{
public:
	///constructor method: creates a new VillageIsland object using the information passed in
	VillageIsland(float xPos,float yPos, float mWidth, float mHeigth, float mRotation);
	///Destructor method: deletes this object at termination/clean up 
	~VillageIsland(void);
	///method that draws the VillageIsland object
	void draw(SDL_Renderer* renderer,float scale,Vector2f offset);
};
#endif

