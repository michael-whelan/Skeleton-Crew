#pragma once
#ifndef CREW_H
#define CREW_H
#include "Unit.h"
#include "KeyManager.h"
#include "Vector2f.h"
#include <math.h>
///
///the players units in the game
///
class Crew:public Unit
{
public:
	static vector<string> nameOptions;
	Crew(float x, float y);///creates a crew member
	Crew(float x, float y, Station* station);///creates a crew member on a specific ship
	Crew(float x, float y, Station* station, states state);///creates a crew member on with a specific state
	~Crew(void);///deconstructor for the crew
	void update(float timeElapsed);///updates the crew
	void movement(float timeElapsed);///handles player input
	void virtual AIControl(float timeElapsed, vector<Entity*> *nightmares);///handles ai
	void OutOfBounds(float timeElapsed);///checks the point is on the ship
	void Crew::grapplePoint(Vector2f pos);///grapples to a specified point on the ship
	///to be inherited by crew
	void selectVoice ();
	string getName(){return name;};
private:
	void checkRole();///checks available jobs
	void doJob(float timeElasped, vector<Entity*> *nightmares);///does the job currently assigned
	string name;
	
	
};
#endif

