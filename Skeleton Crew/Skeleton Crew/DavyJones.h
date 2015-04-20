#pragma once
#include "Boss.h"
class DavyJones : public Boss
{
public:
	DavyJones(float x, float y); /// Constructor with position x and y as floats
	DavyJones(float x, float y, Station* station); /// Overloaded Constructor with pointer to station
	~DavyJones(void); /// Destructor
};

