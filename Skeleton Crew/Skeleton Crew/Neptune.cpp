#include "Neptune.h"


Neptune::Neptune(float x, float y):Boss(x,y)
{
	health = baseHealth*10;//temporary
	texture = TextureManager::getManager()->kingNeptune;
	mySpecial = specials::neptune;
	//myEntity = entityType::entity|entityType::unit|entityType::seacreatures;
	damageLevel = 4;
}

Neptune::Neptune(float x, float y, Station* station):Boss(x,y, station)
{
	health = baseHealth*10;//temporary
	texture = TextureManager::getManager()->kingNeptune;
	mySpecial = specials::neptune;
	//myEntity = entityType::entity|entityType::unit|entityType::seacreatures;
	damageLevel = 4;
}


Neptune::~Neptune(void)
{
}
