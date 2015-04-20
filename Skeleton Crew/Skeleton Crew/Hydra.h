#pragma once
#include "SeaCreature.h"
class Hydra:public SeaCreature
{
public:
	///
	///Constructor of Hydra
	///
	Hydra(float x,float y, float mRotation);

	///
	///Destructor of Hydra
	///
	~Hydra(void);

	///
	///Plays sounds when the player is in range
	///
	void encounterSounds( Vector2f offset);
};


