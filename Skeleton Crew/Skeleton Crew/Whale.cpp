#include "Whale.h"


Whale::Whale(float X,float Y, float mRotation):SeaCreature(X,Y, mRotation)
{
	textureTop = nullptr;
	texture = TextureManager::getManager()->whale;
	textureBottom = TextureManager::getManager()->whaleBottom;
	size= Vector2f(256*1.6,195*1.6);
}

Whale::~Whale(void)
{
}

void Whale::encounterSounds( Vector2f offset){
	int random = rand() % 600;
	
		if (random == 1)
		{
			SoundManager::getManager()->startSound(SoundManager::getManager()->whaleSound, position);
		}
	
}