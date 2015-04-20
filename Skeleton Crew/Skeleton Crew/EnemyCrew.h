#pragma once
#ifndef ENEMYCREW_H
#define ENEMYCREW_H
#include "Unit.h"
class EnemyCrew:public Unit
{
public:
	EnemyCrew(float x, float y,entityType type);/// Constructor with position x and y as floats
	EnemyCrew(float x, float y,entityType type,Station* stationed); /// Overloaded Constructor with pointer to station
	~EnemyCrew(void); /// Destructor
};
#endif

