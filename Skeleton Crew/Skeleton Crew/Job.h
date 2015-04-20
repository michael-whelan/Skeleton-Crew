#pragma once
#include "Station.h"
class Job
{
protected:
	static int jobCount;
	///
	///Pointer to the entity currently assigned to this Job
	///
	Entity *controller;

	///
	///used to draw Jobs
	///
	static SDL_Rect* posRec;

	///
	///Pointer to the station that the Job is assigned to
	///
	Station* myStation;

	///
	///Position of this Job
	///
	Vector2f position;

	///
	///Rotation of this Job
	///
	float rotation;

	///
	///Radius of this Job
	///
	float radius;

	Texture* texture;
public:
	///
	///Constructor method of Job
	///
	Job(float x,float y, float radius,Station* station);

	///
	///Alternative constructor method of Job
	///
	Job(float x,float y, float radius,Station* station, Entity* control);

	///
	///Destructor method of Job
	///
	~Job(void);

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual action(float timeElapsed)=0;

	///
	///Changes orientation of the Job
	///
	void rotate(float rotationAmt);

	///
	///Returns the radius of the Job
	///
	float getRadius(){return radius;};

	///
	///Returns the position of the Job
	///
	Vector2f getPosition(){return position;};

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual update(float timeElapsed)=0;

	///
	///Returns a pointer to the station that this job is assigned to
	///
	Station* getStation(){return myStation;};

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual movement(float timelapsed)=0;

	///
	///Returns the rotation of the Job
	///
	float virtual getRotation(){return rotation;};

	///
	///Returns a pointer to the entity assigned to the Job
	///
	Entity* getController(){return controller;};

	///
	///Sets an entity assigned to the Job
	///
	void setController(Entity* control){controller=control;};

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual draw(SDL_Renderer*,Vector2f offset,float scale)=0;

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual drawTop(SDL_Renderer*,Vector2f offset,float scale)=0;

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual AIControl(float timelapsed,vector<Entity*> *nightmares)=0;

	///
	///Virtual method that is inherited and overwritten by subclasses
	///
	void virtual crewControl(float timelapsed,vector<Entity*> *nightmares)=0;


};

