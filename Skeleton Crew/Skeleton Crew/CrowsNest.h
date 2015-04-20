#pragma once
#include "job.h"
class CrowsNest :
	public Job
{
public:
	CrowsNest(float x,float y, float radius, Texture* texture ,Station* station);
	CrowsNest(float x,float y, float radius, Texture* texture ,Station* station,Entity* control);
	~CrowsNest(void);

	void setUpgrade(float f);
	void virtual action(float timeElapsed);
	void virtual update(float timeElapsed);
	void virtual movement(float timelapsed);
	void virtual draw(SDL_Renderer*,Vector2f offset,float scale);
	void virtual drawTop(SDL_Renderer*,Vector2f offset,float scale);
	void virtual AIControl(float timelapsed,vector<Entity*> *nightmares);
	void virtual crewControl(float timelapsed,vector<Entity*> *nightmares);
};

