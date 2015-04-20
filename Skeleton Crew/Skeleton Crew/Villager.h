#pragma once
#ifndef VILLAGER_H
#define VILLAGER_H
#include "Unit.h"
class Villager :
	public Unit
{
public:
	///constructor method: creates a new Villager object using the information passed in
	Villager(float x, float y);
	///constructor method: creates a new Villager object using the information passed in
	Villager(float x, float y, Station* stationed);
	///constructor method: creates a new Villager object using the information passed in
	Villager(float x, float y, Station* stationed, states state);
	///Destructor method: deletes this object at termination/clean up
	~Villager(void);
	///stores the amount of gold the village contains
	int gold;
	float getDamage(){return baseDamage * 0.25f;};
};
#endif

