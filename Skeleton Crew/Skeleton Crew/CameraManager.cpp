#include "CameraManager.h"
#include <math.h>

CameraManager* CameraManager::me;

CameraManager* CameraManager::getManager()
{
	if(!me)
	{
		me=new CameraManager();
	}
	return me;
}

CameraManager::CameraManager(void)
{
	scale = 1;
}


CameraManager::~CameraManager(void)
{
}

float CameraManager::getScale()
{
	return scale;
}
Vector2f CameraManager::getOffSet()
{
	return Vector2f((offSet.x*scale)-640,(offSet.y*scale)-360);
}

void CameraManager::update(float timeElapsed,Vector2f playerPos, float sightIncrease)
{


	scale+=(KeyManager::getManager()->scrollChange()/10.0f);

	
	if(scale < SDL_max(0.8f-sightIncrease,0.2f))
	{
		scale = SDL_max(0.8f-sightIncrease,0.2f);
	}
	if(scale > 1)
	{
		scale =1;
	}

	Vector2f dif;
	dif.x = ((playerPos.x))-offSet.x;
	dif.y = ((playerPos.y))-offSet.y;

	if(dif.length()>100)
	{
		offSet.x += dif.x*10*timeElapsed;
		offSet.y += dif.y*10*timeElapsed;
	}
	else
	{
		offSet.x = ((playerPos.x));
		offSet.y = ((playerPos.y));
	}
}