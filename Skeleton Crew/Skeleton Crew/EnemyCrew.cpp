#include "EnemyCrew.h"


EnemyCrew::EnemyCrew(float x, float y,entityType type):Unit(x,y)
{
	myEntity = entityType::entity|entityType::unit|type;
	if(type==entityType::navy)
	{
		texture = TextureManager::getManager()->navy;
		myEntity = entityType::entity|entityType::unit|entityType::navy;
	}
	else if(type==entityType::pirate)
	{
		texture = TextureManager::getManager()->pirate;
		myEntity = entityType::entity|entityType::unit|entityType::pirate;
	}
	else if(type==entityType::ghost)
	{
		texture = TextureManager::getManager()->ghostPirate;
		myEntity = entityType::entity|entityType::unit|entityType::ghost;
	}
}

EnemyCrew::EnemyCrew(float x, float y,entityType type, Station* stationed):Unit(x,y,stationed)
{
	if(type==entityType::navy)
	{
		texture = TextureManager::getManager()->navy;
	}
	else if(type==entityType::pirate)
	{
		texture = TextureManager::getManager()->pirate;
	}
	else if(type==entityType::ghost)
	{
		texture = TextureManager::getManager()->ghostPirate;
	}
	myEntity = entityType::entity|entityType::unit|type;
}


EnemyCrew::~EnemyCrew(void)
{
	int a =1;
}
