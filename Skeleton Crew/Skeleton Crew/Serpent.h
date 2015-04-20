#pragma once
#include "seacreature.h"
///one of the sea creatures that will attack
class Serpent :
	public SeaCreature
{
public:
	Serpent(float X, float Y, float mRotation);///xposition,yposition,rotation
	~Serpent(void);
};



