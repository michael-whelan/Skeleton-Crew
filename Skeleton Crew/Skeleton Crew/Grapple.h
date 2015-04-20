#pragma once
#ifndef GRAPPLE_H
#define GRAPPLE_H
#include "AnimationManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Projectile.h"
class Grapple : public Projectile
{
public:
	/// the constrcutor which has a position and a distance
	Grapple(Vector2f pos,float rotate,Vector2f vel,float dmg,float rangeMultiplayer,Vector2f from); 
	~Grapple(void); /// the destructor
	/// the apply action method which will move the grapple from one station to another
	void virtual applyAction(Station* stationFrom, Station* stationTo);
};
#endif

