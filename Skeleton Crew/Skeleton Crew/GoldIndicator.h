#pragma once
#ifndef GOLDINDICATOR_H
#define GOLDINDICATOR_H
#include "HUDElement.h"
class GoldIndicator:public HUDElement
{
public:
	GoldIndicator(float,float); /// the constructor with the x and y postion as floats
	~GoldIndicator(void); /// the destructor
private:
	int gold; /// the gold as an int

	//string data;
	
public:
	void draw(SDL_Renderer* renderer); /// the draw method which takes the sdl renderer
};
#endif