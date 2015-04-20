#include "CannonBall.h"


CannonBall::CannonBall(Vector2f pos,float rotate,Vector2f vel,float dmg,float rangeMultiplayer,Vector2f from):Projectile(pos,rotate,vel,dmg,from)
{
	texture=TextureManager::getManager()->cannonBall;
	range = 4333*0.25f*rangeMultiplayer;
	SoundManager::getManager()->startSound(SoundManager::getManager()->CannonFireSound, position);
}

CannonBall::~CannonBall(void)
{
}


void CannonBall::applyAction(Station* stationFrom, Station* stationTo)
{
	stationTo->hitByCannon(position,damage);
	SoundManager::getManager()->startSound(SoundManager::getManager()->CannonBallImpact,position);
}