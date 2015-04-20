#include "Island.h"
#include "Station.h"


Island::Island(float xPos,float yPos, float mLength, float mBreadth, float mRotation):Station(xPos,yPos)
{
	int type = rand()% 2;
	if (type ==0)
	{
		texture = TextureManager::getManager()->emptyIsland;
	}
	else if (type == 1)
	{
		texture = TextureManager::getManager()->rockyIsland;
	}
	rotation = mRotation;
	size = Vector2f(mLength,mBreadth);
	mass=10000000000;
	myEntity = entityType::entity|entityType::station|entityType::island;
}


Island::~Island(void)
{
}

void Island::drawTop(SDL_Renderer* renderer,float scale,Vector2f offset) 
{
}


void Island::update(float timeElapsed)
{
	velocity = Vector2f();
	health = 10000;
}
	
