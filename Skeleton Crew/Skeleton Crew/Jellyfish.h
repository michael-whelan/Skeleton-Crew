#pragma once
#include "seacreature.h"
class Jellyfish :public SeaCreature
{
public:
	///
	///Constructor of Jellyfish
	///
	Jellyfish(float X, float Y, float mRotation);

	///
	///Destructor of Jellyfish
	///
	~Jellyfish(void);

	///
	///Plays sounds when the player is in range
	///
	void encounterSounds( Vector2f offset);
};

