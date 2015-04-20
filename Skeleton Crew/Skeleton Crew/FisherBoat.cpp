#include "FisherBoat.h"


FisherBoat::FisherBoat(float X,float Y, float mRotation):MobileStation(X,Y)
{
	position.x = X;
	position.y = Y;
	velocity = Vector2f(10,10);
	rotation = mRotation;
	texture = TextureManager::getManager()->fisherboat;
	size= Vector2f(120,49);
	mass=size.x*size.y;// 50000;
}


FisherBoat::~FisherBoat(void)
{
}
