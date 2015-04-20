#pragma once
#ifndef NOTORIETYINDICATOR_H
#define NOTORIETYINDICATOR_H
#include "HUDElement.h"
class NotorietyIndicator:public HUDElement
{
public:
	///constructor method: creates a new NotorietyIndicator object using the information passed in
	NotorietyIndicator(float x,float y);
	///Destructor method: deletes this object at termination/clean up
	~NotorietyIndicator(void);

	void draw(SDL_Renderer* renderer);
};
#endif