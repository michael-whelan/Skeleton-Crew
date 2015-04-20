#pragma once
#ifndef DEATHSBANK_H
#define DEATHSABANK_H
#include "Island.h"
#include "ObjectManager.h"
class DeathsBank:public Island
{
public:
	///constructor method: creates a new VillageIsland object using the information passed in
	DeathsBank(float xPos,float yPos, float mWidth, float mHeigth, float mRotation);
	///Destructor method: deletes this object at termination/clean up 
	~DeathsBank(void);
	void update(float timeElapsed);
	void draw(SDL_Renderer* renderer,float scale,Vector2f offset);

	Station* currentStation;
};
#endif