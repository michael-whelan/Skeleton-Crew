#pragma once
#ifndef CANNON_H
#define CANNON_H
#include "CannonBall.h"
#include "Grapple.h"
#include "Job.h"
///
///the cannon on the side of ships
///handles ai aiming and firing as well as plaer input depending on who is controlling it
///
class Cannon : public Job
{
private:
	float reloadTime;///time remaining before the next shot
	float maxReloadTime;
	bool isMuzzleFlash;

public:
	Cannon(float x,float y, float radius,Station* station);///constructor for the cannon
	Cannon(float x,float y, float radius,Station* station,Entity* control);///constructor for the cannon when someone is assigned to it
	~Cannon(void);///deconstructor for the cannon
	void setUpgrade(float);
	float getRotation(){return rotation - myStation->getRotation();};///returns the rotation of the cannon
	void virtual action(float timeElapsed);///fires a cannonball
	void virtual grapple(float timeElapsed);///fires a grapplehook
	void virtual update(float timeElapsed);///updates the cannon
	void virtual movement(float timelapsed);///handles player input
	void virtual draw(SDL_Renderer*,Vector2f offset,float scale);///draws the cannon
	void aimAtPoint(float timeElapsed, Vector2f pos, Vector2f vel);///rotates the cannon to aim at a specified point
	void virtual drawTop(SDL_Renderer*,Vector2f offset,float scale);///draws the top of the cannon
	void virtual AIControl(float timelapsed,vector<Entity*> *nightmares);///handles the ai aiming for enemies
	void virtual crewControl(float timelapsed,vector<Entity*> *nightmares);///handles the ai aiming for allies

};
#endif
