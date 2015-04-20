#include "DeathsBank.h"
#include "Island.h"


DeathsBank::DeathsBank(float xPos,float yPos, float mWidth, float mHeigth, float mRotation):Island(xPos, yPos, mWidth, mHeigth, mRotation)
{
	texture = TextureManager::getManager()->bankIsland;
	myEntity = entityType::entity|entityType::station|entityType::bank;
}


DeathsBank::~DeathsBank(void)
{
}

void DeathsBank::update(float timeElapsed)
{
	Island::update(timeElapsed);
	
}



void DeathsBank::draw(SDL_Renderer* renderer,float scale, Vector2f offset)
{
	Island::draw(renderer,scale,offset);

}