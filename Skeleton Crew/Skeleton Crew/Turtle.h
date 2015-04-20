#pragma once
#ifndef TURTLE_H
#define TURTLE_H
#include "MobileStation.h"
class Turtle : public MobileStation
{
public:
	Turtle(float,float, float);
	~Turtle(void);
	void encounterSounds(Vector2f offset);
};
#endif

