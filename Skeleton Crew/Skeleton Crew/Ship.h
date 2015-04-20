#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "Grapple.h"
#include "CannonBall.h"
#include "KeyManager.h"
#include "MobileStation.h"

///THe ship station this is mostly using the mobile station classes
class Ship:public MobileStation
{
protected:
	Texture* mastTexture;
public:
	Ship(float X, float Y,Texture* texture,Texture* mast,float strengthLvl);///initializes position
	Ship(float X, float Y);///initializes position
	~Ship(void);
	int gold;//each ship will carry an amount of gold
	void virtual drawTop(SDL_Renderer* renderer,float scale,Vector2f offset);

};
#endif

