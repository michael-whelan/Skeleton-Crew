#include "Villager.h"


Villager::Villager(float x, float y):Unit(x,y)
{
	myState = states::noneState; 
	texture = TextureManager::getManager()->villager;
	health = 50;
	myEntity = entityType::entity|entityType::unit|entityType::villager;
}

Villager::Villager(float x, float y, Station* stationed):Unit(x,y,stationed)
{
	myState = states::noneState;
	texture = TextureManager::getManager()->villager;
	health = 50;
	myEntity = entityType::entity|entityType::unit|entityType::villager;
}

Villager::Villager(float x, float y, Station* stationed, states state):Unit(x,y,stationed,state)
{
	texture = TextureManager::getManager()->villager;
	health = 50;
	myEntity = entityType::entity|entityType::unit|entityType::villager;
}

Villager::~Villager(void)
{
}
