#pragma once
#include "Boss.h"
class DreadRoberto: public Boss
{
public:
	DreadRoberto(float x, float y); /// Constructor with position x and y as floats
	DreadRoberto(float x, float y, Station* station);  /// Overloaded Constructor with pointer to station
	~DreadRoberto(void); /// Destructor
};

