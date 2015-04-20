#include "Death.h"


Death::Death(float x, float y):Boss(x,y)
{
	health = baseHealth*20;//temporary
	texture = TextureManager::getManager()->death;
	mySpecial = specials::death;
	myEntity = entityType::entity|entityType::unit|entityType::ghost;
	damageLevel = 20;
}

Death::Death(float x, float y, Station* station):Boss(x,y, station)
{
	health = baseHealth*20;//temporary
	texture = TextureManager::getManager()->death;
	mySpecial = specials::death;
	myEntity = entityType::entity|entityType::unit|entityType::ghost;
	damageLevel = 20;
}


Death::~Death(void)
{
}
