#include "VillageIsland.h"
#include "Island.h"

VillageIsland::VillageIsland(float xPos,float yPos, float mWidth, float mHeigth, float mRotation):Island(xPos, yPos, mWidth, mHeigth, mRotation)
{
	int type = rand()% 2;
	if (type ==0)
	{
	texture = TextureManager::getManager()->villageIsland;	
	}
	else if (type == 1)
	{
		texture = TextureManager::getManager()->villageIslandTwo;	
	}	
}

VillageIsland::~VillageIsland(void)
{
}


void VillageIsland::draw(SDL_Renderer* renderer,float scale, Vector2f offset)
{
	Island::draw(renderer,scale,offset);
}
