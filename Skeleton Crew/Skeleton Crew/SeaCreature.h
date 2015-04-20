#pragma once
#ifndef SEACREATURE_H
#define SEACREATURE_H
#include "MobileStation.h"
///The base class for the different sea creatures

class SeaCreature:public MobileStation
{
public:
	SeaCreature(float,float, float);///xposition ,yposition, rotation
	void drawTop(SDL_Renderer*,float,Vector2f);///used to draw the creature on the correct layer

	//void virtual encounterSounds();

	~SeaCreature(void);//Destory object 
	void update(float timeElapsed); ///Updates the sea creatures 
	/*enum states
	{
		attacking, 
		wandering
	};
	states state; */
protected:
	void aimAtPoint(float timeElapsed, Vector2f pos, Vector2f vel); 
	void AIControl(float timeElapsed,vector<Entity*> *nightmares);///controls the A.I. for the sea creatures #
	void action(float timeElapsed);
	Vector2f targetPosition;///position to seek to
	float attackTime;
	float coolTime;
	void virtual changeRotation(float Rot){rotation=rotation+Rot;if(rotation>=360){rotation-=360;}else if (rotation < 0){rotation+=360;}}
	//	void wander(); ///makes the sea creatures wander around the world
	//	void attack(float timeElasped,vector<Entity*>*crew);///makes the sea creaturs attack the player
	//	void seek(Vector2f targetPos);///seek to a certain position
	
};
#endif

