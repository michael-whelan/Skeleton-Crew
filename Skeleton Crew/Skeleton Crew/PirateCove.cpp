#include "PirateCove.h"
#include "Island.h"


PirateCove::PirateCove(float xPos,float yPos, float mWidth, float mHeigth, float mRotation):Island(xPos, yPos, mWidth, mHeigth, mRotation)
{
	texture = TextureManager::getManager()->pirateCove;
	myEntity = entityType::entity|entityType::station|entityType::island|entityType::shipyard;
}


PirateCove::~PirateCove(void)
{
}

