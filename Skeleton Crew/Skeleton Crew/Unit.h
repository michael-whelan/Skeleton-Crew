#pragma once
#ifndef UNIT_H
#define UNIT_H
#include "Entity.h"
#include "Control.h"

class Job;
class Unit : public Entity
{
public:
	enum hatUpgrades
	{
		noneHat,
		seaman,
		petty_officer,
		chief_petty_officer,
		lieutenant,
		captain,
		admiral
	};
	enum states
	{
		noneState,
		job,
		boarding,
		following,
		attacking,
		scared,
		grappling
	};
	states myState;


	Unit(float x, float y);
	Unit(float x, float y, Entity* stationed);
	Unit(float x, float y, Entity* stationed, states state);
	~Unit(void);

	
	void virtual update(float timeElapsed);
	void virtual draw(SDL_Renderer* renderer,float scale,Vector2f offset);
	
	
	bool virtual AddNewCrew(); 
	states getState(){return myState;};
	Entity* getStation();
	float getAttackTime(){return attackTime;};
	void setAttackTime(float at){attackTime = at;};
	void setStation(Entity* station){stationedAt = station;};
	void virtual AIControl(float timeElapsed, vector<Entity*> *nightmares);
	void virtual runAroundScared(float timeElapsed); 
	void virtual BoardEnemyShip(Entity* targetShip);
	void virtual Hit(Vector2f direction, float damage);
	hatUpgrades virtual upgradeUnit(hatUpgrades newHat);
	hatUpgrades virtual getHat();
	void setJob(Job* job);
	void virtual doJob(float timeElapsed, vector<Entity*> *nightmares);
	void virtual DefultState(float timeElapsed,vector<Entity*>* enemy, vector<Entity*>* ships);
	void virtual Attack(float timeElapsed,vector<Entity*>* enemy);
	///to be inherited by crew
	void virtual selectVoice (){};

	Grapple* getGrapple(){return personnelGrapple;};
	void setGrapple(Grapple* gp){personnelGrapple = gp;};
	void virtual grapplePoint(Vector2f pos);
	void virtual Seek(Vector2f targetPosition,float timeElapsed, float speed);
	void scream();
	Vector2f getTargetPos(){return targetPos;};
	void setTargetPos(Vector2f tp){targetPos = tp;};
	void setState(states newState){myState = newState;};
	Vector2f getLocalPos(){return localPosition;};
	void setLocalPos(Vector2f lp){localPosition=lp;};
	float getMaxHealth(){return baseHealth*hatStrength[myHat];};
	float getHatStrength(){return hatStrength[myHat];};
	float virtual getDamage(){return baseDamage * hatStrength[myHat];};
	string getHatName(){return hatName[myHat];};

protected:
	void checkJob(Job* job);
	int range;
	float coolTime;
	float attackTime;
	hatUpgrades myHat;
	Entity* stationedAt;
	Vector2f localPosition;
	Job* myJob;
	Grapple* personnelGrapple;
	Vector2f targetPos;
	float grappleColdown;

	static short baseSpeed;
	static short baseHealth;
	static short baseDamage;
	static float hatStrength [];
	static string hatName [];
	static short baseMissChance;


};
#include "Station.h"
#include "Job.h"
#endif
