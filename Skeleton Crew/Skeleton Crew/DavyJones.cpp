#include "DavyJones.h"


DavyJones::DavyJones(float X,float Y):Boss(X,Y)
{
	health = baseHealth*5;
	texture = TextureManager::getManager()->davyJones;
	mySpecial = specials::jones; 
	myEntity = entityType::entity|entityType::unit|entityType::navy;
	damageLevel = 5;
}
DavyJones::DavyJones(float x, float y,Station* station):Boss(x,y,station)
{
	health = baseHealth*5;
	texture = TextureManager::getManager()->davyJones;
	mySpecial = specials::jones; 
	myEntity = entityType::entity|entityType::unit|entityType::navy;
	damageLevel = 5;
}

DavyJones::~DavyJones(void)
{
}
