#include "Hydra.h"


Hydra::Hydra(float X,float Y, float mRotation):SeaCreature(X,Y, mRotation)
{
	texture = TextureManager::getManager()->hydraSmall;
	size= Vector2f(256*1.6,130*1.6);
}


Hydra::~Hydra(void)
{
}

void Hydra::encounterSounds( Vector2f offset){
	int random = rand() % 600;
	
			if (random == 1)
			{
				SoundManager::getManager()->startSound(SoundManager::getManager()->hydraSound,position);
			}
	
}