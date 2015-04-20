#pragma once
#ifndef BOSS_H
#define BOSS_H
#include "Unit.h"
///
///the base class for bosses
///
class Boss:public Unit
{
public:
	Boss(float x, float y);///constructor for the boss
	Boss(float x, float y, Station *stationed);///constructor for the boss if they are on a ship
	void specialAttack(float timeElapsed,vector<Station*> *stations,vector<Unit*>*units);///a special effect of the boss that has unique effects
	float getHitRadius(){return hitRadius;};///gets the attack radius for the boss
	~Boss(void);
	enum specials///enum for different bosses
	{
		roberto,
		jones,
		alien,
		death,
		neptune
	};
	specials mySpecial;///what the boss currently is
	void teleport();///teleports the boss to a random point on the ship
	void slowShips(vector<Station*> *stations);///slows ships surrounding the boss
	void attackCircle(vector<Unit*> *units, float timeElapsed);///deals damage to all enemies in a radius
	void charge(vector<Station*> *stations);///deals damage to all enemies in a radius
	bool checkDistance(Vector2f c1,float r1, Vector2f c2, float r2);///checks the distance between two points
	void update(float timeElapsed);
	bool useSpecialAttack();
	float getDamageLevel();
protected:
	float hitRadius;///the hit radius of the boss
	float specialAttackCool;
	float damageLevel;
};
#endif