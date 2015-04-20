#pragma once
#ifndef CANNONBALL_H
#define CANNONBALL_H
#include "Projectile.h"
///
///the cannonball fired from cannons
///
class CannonBall: public Projectile
{
private:
public:
	CannonBall(Vector2f pos,float rotate,Vector2f vel,float dmg,float rangeMultiplayer,Vector2f from);///constructor for the cannonball
	~CannonBall(void);///destructor for the cannonball
	void virtual applyAction(Station* stationFrom, Station* stationTo);///applies collision response after it has hit a ship or island
};
#endif

