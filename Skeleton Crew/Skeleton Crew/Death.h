#pragma once
#ifndef DEATH_H
#define DEATH_H
#include "Boss.h"
class Death:public Boss
{
public:
	Death(float x, float y);///Constructor 
	Death(float x, float y, Station* station);///Alternative constructor with pointer to station
	~Death(void);///Destructor
};
#endif

