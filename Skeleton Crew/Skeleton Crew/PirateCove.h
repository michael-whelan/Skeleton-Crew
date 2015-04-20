#pragma once
#ifndef PIRATECOVE_H
#define PIRATECOVE_H
#include "Island.h"
class PirateCove:public Island
{
public:
	
	///constructor method: creates a new PirateCove object using the information passed in
	PirateCove(float xPos,float yPos, float mWidth, float mHeigth, float mRotation);
	///Destructor method: deletes this object at termination/clean up 
	~PirateCove(void);
};
#endif

