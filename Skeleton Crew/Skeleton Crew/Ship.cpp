#include "Ship.h"


Ship::Ship(float X, float Y,Texture* mtexture,Texture* mast,float strengthLvl):MobileStation(X,Y)
{
	texture = mtexture;
	size=texture->getSize();
	mastTexture = mast;
	myEntity = entityType::entity|entityType::station|entityType::mobilestation|entityType::ship;
	gold = rand()%5000;
	gold += 5000;
	lvlMultiplier = strengthLvl;
	health*= strengthLvl;
	mass=size.x*size.y;// 50000;
}

Ship::Ship(float X, float Y):MobileStation(X,Y)
{
	texture = TextureManager::getManager()->ship;
	mastTexture = TextureManager::getManager()->pirateMast;
	size=texture->getSize();
	myEntity = entityType::entity|entityType::station|entityType::mobilestation|entityType::ship;
	//gold = rand()%5000;
	//gold += 5000;
}

Ship::~Ship(void)
{
}


void Ship::drawTop(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	Station::drawTop(renderer,scale,offset);
	posRec->x = (position.x)*scale + ((cos(rotation*M_PI/180)*50)-(51/2))*scale;
	posRec->y = (position.y)*scale + ((sin(rotation*M_PI/180)*50)-(324/2))*scale;
	posRec->w = 51*scale;//length;
	posRec->h = 324*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,mastTexture->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);	
}