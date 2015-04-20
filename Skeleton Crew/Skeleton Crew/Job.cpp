#include "Job.h"

SDL_Rect* Job::posRec;
int Job::jobCount=0;

Job::Job(float x,float y, float radius,Station* station):position(x,y),rotation(0),radius(radius),myStation(station),controller(0)
{
	if(!posRec)
	{
		posRec = new SDL_Rect();
	}
}


Job::Job(float x,float y, float radius,Station* station, Entity* control):position(x,y),rotation(0),radius(radius),myStation(station),controller(control)
{
	if(!posRec)
	{
		posRec = new SDL_Rect();
	}
}//station update move towards binded tagets


void Job::rotate(float rotationAmt)
{
	rotation+=rotationAmt;
	if(rotation>=360)
	{
		rotation-=360;
	}
	else if (rotation < 0)
	{
		rotation+=360;
	}
}


Job::~Job(void)
{
	if(controller)
	{
		((Unit*)controller)->setJob(0);
	}
}
