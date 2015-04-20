#pragma once
#ifndef ISLAND_H
#define ISLAND_H
#include <iostream>
#include "SDL.h"
#include "Vector2f.h"
#include <math.h>
#include "TextureManager.h"
#include "KeyManager.h"
#include "Station.h"
class Island:public Station
{
public:
	///
	///Constructor of Island
	///
	Island(float xPos,float yPos, float mLength, float mBreadth, float mRotation);

	///
	///Destructor of Island
	///
	~Island(void);

	///
	///Draws top layer of the island
	///
	void drawTop(SDL_Renderer*,float,Vector2f);

	///
	///Updates Island
	///
	void update(float timeElapsed);

	///
	///deletes Island
	///
	void kill();
};

#endif