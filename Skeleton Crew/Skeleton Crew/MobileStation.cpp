#include "MobileStation.h"


MobileStation::MobileStation(float X, float Y):Station(X,Y)
{
	acceleration = Vector2f();
	rotation = 0;
	//myEntity = entityType::entity|entityType::station|entityType::mobilestation;
}


MobileStation::~MobileStation(void)
{
}

void MobileStation::cannonControl(float timeElapsed, Job* cannon, vector<Entity*> *nightmares)
{
	
}

void MobileStation::movement(float timeElapsed)
{
	if (KeyManager::getManager()->keyDown(SDL_SCANCODE_W))
	{
		Vector2f dir;
		dir.x = cos(rotation*M_PI/180);
		dir.y = sin(rotation*M_PI/180);
		acceleration.x = dir.x*timeElapsed*ACCELERATION_SPEED*multiplySpeed*lvlMultiplier;
		acceleration.y = dir.y*timeElapsed*ACCELERATION_SPEED*multiplySpeed*lvlMultiplier;
    }
	else if (KeyManager::getManager()->keyDown(SDL_SCANCODE_S))
	{
		velocity*=1-(0.4f*timeElapsed);
    }
	if (KeyManager::getManager()->keyDown(SDL_SCANCODE_A))
	{
		rotation-=velocity.length()/5*timeElapsed;
		if(rotation>=360)
		{
			rotation-=360;
		}
		else if (rotation < 0)
		{
			rotation+=360;
		}
    }
	else if (KeyManager::getManager()->keyDown(SDL_SCANCODE_D))
	{
		rotation+=velocity.length()/5*timeElapsed;
		if(rotation>=360)
		{
			rotation-=360;
		}
		else if (rotation < 0)
		{
			rotation+=360;
		}
    }
}

void MobileStation::AIControl(float timeElapsed, vector<Entity*> *nightmares)
{
}

float MobileStation::calcMoveAngle(Vector2f vel)
{
	float movingDirection=asinf(vel.y/vel.length())*180.0f/M_PI;
	if(movingDirection>=360)
	{
		movingDirection-=360;
	}
	else if (movingDirection < 0)
	{
		movingDirection+=360;
	}
	if(vel.x<0)
	{
		movingDirection=90+(90-movingDirection);
	}
	if(movingDirection>=360)
	{
		movingDirection-=360;
	}
	else if (movingDirection < 0)
	{
		movingDirection+=360;
	}
	if(_isnan(movingDirection))
	{
		movingDirection = 0;
	}
	return movingDirection;
}

void MobileStation::update(float timeElapsed)
{
	float movingDirection = 0;

	velocity.x+=acceleration.x;
	velocity.y+=acceleration.y;

	for(int i = 0; i < attached->size(); i++)
	{
		Vector2f dir = attached->at(i).first->getPos()-position;
		//dir.x +=(cos(attached->at(i).first->getRotation()*M_PI/180)*attached->at(i).second.first.x)-(sin(attached->at(i).first->getRotation()*M_PI/180)*attached->at(i).second.first.y);
		//dir.x +=(sin(attached->at(i).first->getRotation()*M_PI/180)*attached->at(i).second.first.x)+(cos(attached->at(i).first->getRotation()*M_PI/180)*attached->at(i).second.first.y);
		//dir.x-=(position.x+(cos(rotation*M_PI/180)*attached->at(i).second.second.x)-(sin(rotation*M_PI/180)*attached->at(i).second.second.y));
		//dir.y-=(position.y+(sin(rotation*M_PI/180)*attached->at(i).second.second.x)+(cos(rotation*M_PI/180)*attached->at(i).second.second.y));
		dir /= dir.length();
		dir *= 5;
		velocity+=dir;
	}



	if(velocity.length()!=0)
	{
		movingDirection=calcMoveAngle(velocity);
	}
	else
	{
		movingDirection=rotation;
	}

	float differenceAngle = rotation-movingDirection;
	if(differenceAngle>=180)
	{
		differenceAngle-=360;
	}
	else if (differenceAngle < -180)
	{
		differenceAngle+=360;
	}
	Vector2f scale = Vector2f(abs(SDL_cos(differenceAngle)),abs(SDL_sin(differenceAngle)));
	float dragFront = 0.5*DENSITY_OF_WATER*velocity.length()
					*velocity.length()*DRAG_COEFFICIENT_FRONT
					*scale.x*(18.0*2)*(2);
	float dragSide = 0.5*DENSITY_OF_WATER*velocity.length()
					*velocity.length()*DRAG_COEFFICIENT_SIDE
					*scale.y*(52.0*2)*(2);
	float totalDrag = dragFront+dragSide;
	float DragAccel = (totalDrag*(mass/1000000000))*timeElapsed;
	float changeAngle = differenceAngle;//(differenceAngle*(SDL_min(velocity.length()/(velocity.length()*1.5),1)));
	if(changeAngle!=0)
	{
		rotation -= changeAngle*0.005f;
		Vector2f nVel = Vector2f();
		nVel.x = velocity.x*cos((changeAngle*0.005f)*M_PI/180.0f) - velocity.y * sin((changeAngle*0.005f)*M_PI/180.0f);
		nVel.y = velocity.x*sin((changeAngle*0.005f)*M_PI/180.0f) + velocity.y * cos((changeAngle*0.005f)*M_PI/180.0f);
		velocity.x=nVel.x;
		velocity.y=nVel.y;
		/*
		Vector2f moveDist = Vector2f();
		float rotPoint = ((length/2) -(length/6));
		moveDist.x = rotPoint - (rotPoint*cos((changeAngle*0.005f)*M_PI/180.0f) - rotPoint * sin((changeAngle*0.005f)*M_PI/180.0f));
		moveDist.y = rotPoint - (rotPoint*sin((changeAngle*0.005f)*M_PI/180.0f) + rotPoint * cos((changeAngle*0.005f)*M_PI/180.0f));
		position.x+=moveDist.x;
		position.y-=moveDist.y;
		*/
	}
	if(velocity.length()!=0)
	{
		velocity = (velocity / velocity.length()) * SDL_max(velocity.length()-abs(DragAccel),0);
	}
	


	position.x+=velocity.x*timeElapsed;
	position.y+=velocity.y*timeElapsed;
	
	acceleration.x =0;
	acceleration.y = 0;
	Station::update(timeElapsed);
}