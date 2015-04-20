#include "Grapple.h"


Grapple::Grapple(Vector2f pos,float rotate,Vector2f vel,float dmg,float rangeMultiplayer,Vector2f from):Projectile(pos,rotate,vel,dmg,from)
{
	texture=TextureManager::getManager()->grapple;
	range = 190*rangeMultiplayer;
	SoundManager::getManager()->startSound(SoundManager::getManager()->GrappleFireSound, position);
}


Grapple::~Grapple(void)
{
}


void Grapple::applyAction(Station* stationFrom, Station* stationTo)
{
	Vector2f here = position-stationTo->getPos();
	Vector2f hereF;
	hereF.x = (cos(-stationTo->getRotation()*M_PI/180)*here.x)-(sin(-stationTo->getRotation()*M_PI/180)*here.y);
	hereF.y = (sin(-stationTo->getRotation()*M_PI/180)*here.x)+(cos(-stationTo->getRotation()*M_PI/180)*here.y);
	stationFrom->getAttached()->push_back(pair<Entity*,pair<Vector2f,Vector2f>>(stationTo,pair<Vector2f,Vector2f>(hereF,firedFrom)));
	stationTo->getAttached()->push_back(pair<Entity*,pair<Vector2f,Vector2f>>(stationFrom,pair<Vector2f,Vector2f>(firedFrom,hereF)));
	stationTo->hitByCannon(position,damage);
}