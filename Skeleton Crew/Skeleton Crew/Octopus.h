#pragma once
#include "SeaCreature.h"
class Octopus:public SeaCreature
{
public:
	///constructor method: creates a new Octopus object using the information passed in
	Octopus(float X, float Y, float mRotation);
	///Destructor method: deletes this object at termination/clean up 
	~Octopus(void);
};

