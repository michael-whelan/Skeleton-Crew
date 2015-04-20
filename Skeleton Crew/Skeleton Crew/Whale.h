#pragma once
#include "SeaCreature.h"
class Whale:public SeaCreature
{
public:
	///constructor method: creates a new Whale object using the information passed in
	Whale(float x,float y, float mRotation);
	///Destructor method: deletes this object at termination/clean up 
	~Whale(void);
	///plays a random whale noise
	void encounterSounds( Vector2f offset);
};

