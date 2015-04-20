#include "Projectile.h"

SDL_Rect* Projectile::posRec;

Projectile::Projectile(Vector2f pos,float rotate,Vector2f vel,float dmg,Vector2f from):size(14,14),position(pos),damage(dmg),alive(true),rotation(rotate),firedFrom(from)
{
	if(!posRec)
	{
		posRec = new SDL_Rect();
	}
	velocity.x = vel.x+(SDL_cos(rotation*M_PI/180)*speed);
	velocity.y = vel.y+(SDL_sin(rotation*M_PI/180)*speed);
	
	
}


Projectile::~Projectile(void)
{
}


void Projectile::update(float timeElapsed)
{
	if(alive)
	{
		position.x+=velocity.x*timeElapsed;
		position.y+=velocity.y*timeElapsed;

		if(range>0)
		{
			range-=velocity.length()*timeElapsed;
		}
		if(range<=0)
		{
			alive = false;
		}
	}
}

bool Projectile::getAlive()
{
	return alive;
}


void Projectile::draw(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	posRec->x = (position.x-(size.x/2))*scale;
	posRec->y = (position.y-(size.y/2))*scale;
	posRec->w = size.x*scale;
	posRec->h = size.y*scale;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
}