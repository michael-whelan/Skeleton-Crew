#include "Jellyfish.h"


Jellyfish::Jellyfish(float X,float Y, float mRotation):SeaCreature(X,Y,mRotation)
{
	texture = TextureManager::getManager()->jellyfish;
	size= Vector2f(105,128);
}


Jellyfish::~Jellyfish(void)
{
}

void Jellyfish::encounterSounds( Vector2f offset){
	int random = rand() % 600;
	
			if (random == 1)
			{
				//play the sound
				SoundManager::getManager()->startSound(SoundManager::getManager()->jellySound, position);
			}
	
}