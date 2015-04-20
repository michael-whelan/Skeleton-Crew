#pragma once
#ifndef NEPTUNE_H
#define NEPTUNE_H
#include "Boss.h"
class Neptune:public Boss
{
public:
	Neptune(float x, float y);///constuctor
	Neptune(float x, float y, Station* station);///Alternative constructor with pointer to station
	~Neptune(void);///destuctor
};
#endif
