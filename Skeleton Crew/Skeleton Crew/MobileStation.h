#pragma once
#ifndef MOBILESTATION_H
#define MOBILESTATION_H
#include "Station.h"
class MobileStation : public Station
{
protected:
	///method that calculates the anagle that the station object uses to navigate
	float calcMoveAngle(Vector2f velocity);
public:
	///method that is used to contol a cannon on the ship 
	void cannonControl(float timeElapsed, Job* cannon, vector<Entity*> *nightmares);
	///constructor method: creates a new MobileStation object using the information passed in
	MobileStation(float Length, float Breadth);	
	///Destructor method: deletes this object at termination/clean up 
	~MobileStation(void);
	///method that calculates the movement of the station object
	void movement(float timeElapsed);
	///method that controls the A.I. of the MobileSation
	void virtual AIControl(float timeElapsed, vector<Entity*> *nightmares);
	///method used to sink/destroy a ship (mobile station) object
	void sink();
	///method used to update the station object
	void update(float timeElapsed);
};
#endif

