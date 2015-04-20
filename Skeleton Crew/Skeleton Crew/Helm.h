#pragma once
#include "job.h"
class Helm :
	public Job
{
public:
	///
	///Constructor method for Helm class
	///
	Helm(float x,float y, float radius, Texture* texture,Station* station);

	///
	///alternative constructor method for Helm class
	///
	Helm(float x,float y, float radius, Texture* texture,Station* station,Entity* control);

	///
	///Destructor method for Helm class
	///
	~Helm(void);
	void setUpgrade(float f);
	///
	///method for moving ship forward
	///
	void virtual action(float timeElapsed);

	///
	///updates instance of helm
	///
	void virtual update(float timeElapsed);

	///
	///gets player input and the action method
	///
	void virtual movement(float timelapsed);

	///
	///draws the helm
	///
	void virtual draw(SDL_Renderer*,Vector2f offset,float scale);

	///
	///method for AI control of the helm
	///
	void aimAtPoint(float timeElapsed, Vector2f pos, Vector2f vel);

	///
	///redraws top of helm, giving the appearence of crew hands passing through the teering wheel
	///
	void virtual drawTop(SDL_Renderer*,Vector2f offset,float scale);

	///
	///Enemy AI control of helm
	///
	void virtual AIControl(float timelapsed,vector<Entity*> *nightmares);

	///
	///Allied AI control of helm
	///
	void virtual crewControl(float timelapsed,vector<Entity*> *nightmares);
};

