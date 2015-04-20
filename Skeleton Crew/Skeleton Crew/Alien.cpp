#include "Alien.h"


Alien::Alien(float X,float Y):Boss(X,Y)
{
	health = baseHealth*20.0f;
	texture = TextureManager::getManager()->alien;
	mySpecial = specials::jones;
	myEntity = entityType::entity|entityType::unit|entityType::alien;
	damageLevel = 1.0f/2.0f;
}
Alien::Alien(float x, float y,Station* station):Boss(x,y,station)
{
	health = baseHealth*20.0f;
	texture = TextureManager::getManager()->alien;
	mySpecial = specials::alien;
	myEntity = entityType::entity|entityType::unit|entityType::alien;
	damageLevel = 1/2.0f;
}

void Alien::draw(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	Unit::draw(renderer, scale, offset);

	posRec->x = (int)(((position.x-(hitRadius/2))*scale)+ (((cos(rotation*M_PI/180)*16)-(sin(rotation*M_PI/180)*0))*scale));
	posRec->y = (int)(((position.y-(hitRadius/2))*scale)+ (((sin(rotation*M_PI/180)*16)+(cos(rotation*M_PI/180)*0))*scale));
	posRec->w = (int)(hitRadius*scale);
	posRec->h = (int)(hitRadius*scale);
	posRec->x-=(int)(offset.x);
	posRec->y-=(int)(offset.y);
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->circle->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
}

Alien::~Alien(void)
{
}
