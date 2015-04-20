#include "GoldChest.h"

GoldChest::GoldChest(float xPos,float yPos)
{
	texture = TextureManager::getManager()->goldChestClosed->getTexture();
	position.x = xPos ;
	position.y = yPos;
	amount = rand() % 50 + 1;
	openTimer = 0;
}
GoldChest::GoldChest(float xPos,float yPos,float mIslandWidth, float mIslandHeigth)
{
	texture = TextureManager::getManager()->goldChestClosed->getTexture();
	position.x = xPos -((int)mIslandWidth/4) + rand() % (((int)mIslandWidth + 1)/2);
	position.y = yPos -((int)mIslandHeigth/4) + rand() % (((int)mIslandHeigth + 1)/2);
	amount = rand() % 50 + 1;
	openTimer = 0;
}

GoldChest::~GoldChest(void)
{
}

void GoldChest::draw(SDL_Renderer* renderer,float scale,Vector2f offset) 
{
	SDL_Rect posRec;
	posRec.x = (position.x-(32/2))*scale;
	posRec.y = (position.y-(32/2))*scale;
	posRec.w = 32*scale;
	posRec.h = 32*scale;
	posRec.x-=offset.x;
	posRec.y-=offset.y;
	SDL_RenderCopyEx(renderer,texture,nullptr,&posRec,0,nullptr,SDL_FLIP_NONE);
}


void GoldChest::update(float timeElapsed)
{
	if (texture == TextureManager::getManager()->goldChestOpen->getTexture())
	{
		openTimer+= timeElapsed;
	}
}

void GoldChest::open()
{
	if (texture !=  TextureManager::getManager()->goldChestOpen->getTexture())
	{
		texture = TextureManager::getManager()->goldChestOpen->getTexture();
		//Play open chest sound here!!
		SoundManager::getManager()->startSound(SoundManager::getManager()->coin, position);
	}
}
void GoldChest::close()
{
	texture = TextureManager::getManager()->goldChestClosed->getTexture();
}
int GoldChest::getAmount()
{
	return amount;
}

void GoldChest::changeRotation(float mRotation)
{
	rotation = mRotation;
}