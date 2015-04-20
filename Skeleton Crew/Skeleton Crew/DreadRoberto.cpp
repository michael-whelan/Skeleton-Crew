#include "DreadRoberto.h"


DreadRoberto::DreadRoberto(float X,float Y):Boss(X,Y)
{
	health = baseHealth*3;
	texture = TextureManager::getManager()->dreadRoberts;
	mySpecial = specials::roberto;
	myEntity = entityType::entity|entityType::unit|entityType::pirate;
	damageLevel = 1.5;
}
DreadRoberto::DreadRoberto(float x, float y,Station* station):Boss(x,y,station)
{
	health = baseHealth*3;
	texture = TextureManager::getManager()->dreadRoberts;
	mySpecial = specials::roberto;
	myEntity = entityType::entity|entityType::unit|entityType::pirate;
	damageLevel = 1.5;
}

DreadRoberto::~DreadRoberto(void)
{
}
