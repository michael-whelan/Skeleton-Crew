#pragma once
#include "Boss.h"
///
///a boss unit
///a enemy that inherits from boss and overides methods to customise special attacks and stats
///
class Alien :public Boss
{
public:
	Alien(float x, float y);///basic constructor for the alien
	Alien(float x, float y, Station* station);///constructor for the alien if they start on a ship
	~Alien(void);///deconstructor for the alien
	void draw(SDL_Renderer* renderer,float scale,Vector2f offset);
};

