#include "Squid.h"


Squid::Squid(float X, float Y, float mRotation):SeaCreature(X,Y,mRotation)
{
	texture = TextureManager::getManager()->squid;
	size= Vector2f(256,128);
}


Squid::~Squid(void)
{
}
