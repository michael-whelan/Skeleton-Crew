#pragma once
#ifndef STATION_H
#define STATION_H
#include "Entity.h"
class Job;
class Station : public Entity
{
protected:

	vector<Job*> *lookOutLocations;
	vector<Job*> *driverLocations;
	vector<Job*> *cannons;
	vector<Projectile*> *cannonBalls;
	vector<Entity*> *assignedCrew;
	vector<Entity*> *assignedUnits;
	float mass;
	Vector2f acceleration;
	int gold;
	float multiplyHealth, multiplySpeed,multiplyReload,multiplyCrows,multiplyTurning,multiplyDmg;
	float lvlMultiplier;

public:
	static const float DRAG_COEFFICIENT_FRONT;
	static const float DRAG_COEFFICIENT_SIDE;
	static const float DENSITY_OF_WATER;
	static const float ACCELERATION_SPEED;
	//constants used to set the base of each attribute
	static const float HULL_HEALTH;
	static const float CANNON_SPEED;
	static const float CROWS_NEST;
	//static const int SAIL;
	static const float RUDDER;
	static const float CANNONBALL_DAMAGE;

	vector<Vector2f> *spawnLocations;
	vector<Vector2f> *spawnCircles;

	Station(float x, float y);
	~Station(void);


	void virtual update(float timeElapsed);
	void virtual movement(float timeElapsed);
	void hitByCannon(Vector2f pointOfImpact, float damage);
	void virtual cannonControl(float timeElapsed, Job* cannon, vector<Entity*> *nightmares);
	void virtual draw(SDL_Renderer* renderer,float scale,Vector2f offset);
	void virtual drawTop(SDL_Renderer* renderer,float scale,Vector2f offset);
	void virtual AIControl(float timeElapsed,vector<Entity*> *crew);
	///For inheriting to sea creatures, to play sounds
	void virtual encounterSounds();

	void setHealthMultiply(float f){multiplyHealth = f;health*=multiplyHealth;};
	void setReloadMultiply(float f){multiplyReload = f;};
	void setSpeedMultiply(float f){multiplySpeed =f;};
	void setCrowsMultiply(float f){multiplyCrows = f;};
	void setTurningMultiply(float f){multiplyTurning=f;};
	void setDmgMultiply(float f){multiplyDmg = f;};

	float getHealthMultiply(){return multiplyHealth;};
	float getReloadMultiply(){return multiplyReload;};
	float getSpeedMultiply(){return multiplySpeed;};
	float getCrowsMultiply(){return multiplyCrows;};
	float getTurningMultiply(){return multiplyTurning;};
	float getDmgMultiply(){return multiplyDmg;};

	float getLvl(){return lvlMultiplier;};

	float getGold(){return gold;};
	void increaseGold(int g){gold+=g;};
	void decreaseGold(int g){gold-=g;};
	void setGold(int g){gold=g;};
	float getMass(){return mass;};
	vector<Job*>* getCannons(){return cannons;};
	vector<Job*>* getHelms(){return driverLocations;};
	vector<Job*>* getCrowNests(){return lookOutLocations;};
	void setAcceleration(Vector2f accel){acceleration=accel;};
	vector<Projectile*>* getCannonBalls(){return cannonBalls;};
	vector<Entity*>* getAssignedCrew(){return assignedCrew;};
	vector<Entity*>* getAssignedUnits(){return assignedUnits;};

};
#include "Unit.h"
#include "Job.h"
#endif