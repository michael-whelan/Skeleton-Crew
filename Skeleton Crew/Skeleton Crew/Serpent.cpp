#include "Serpent.h"


Serpent::Serpent(float X, float Y, float mRotation):SeaCreature(X,Y,mRotation)
{
	texture = TextureManager::getManager()->serpent;
	size= Vector2f(40,128);
}


Serpent::~Serpent(void)
{
}

