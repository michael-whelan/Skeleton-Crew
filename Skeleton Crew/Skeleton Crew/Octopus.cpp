#include "Octopus.h"


Octopus::Octopus(float X, float Y, float mRotation):SeaCreature(X,Y, mRotation)
{
	texture = TextureManager::getManager()->octopusSmall;
	size= Vector2f(128,200);
}


Octopus::~Octopus(void)
{
}
