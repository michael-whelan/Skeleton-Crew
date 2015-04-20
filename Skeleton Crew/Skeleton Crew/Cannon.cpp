#include "Cannon.h"

Cannon::Cannon(float x,float y, float r, Station* station):Job(x,y,r,station)
{
	reloadTime = 0;
	maxReloadTime = 3;
}


Cannon::Cannon(float x,float y, float r, Station* station,Entity* control):Job(x,y,r,station,control)
{
	reloadTime = 0;
	maxReloadTime=3;
}


void Cannon::movement(float timeElapsed)
{
	if(KeyManager::getManager()->keyPressed(Control::getManager()->GetCannonMoveUp()))
	{
		action(timeElapsed);
	}
	else if(KeyManager::getManager()->keyPressed(Control::getManager()->GetCannonMoveDown()))
	{
		grapple(timeElapsed);
	}
	if(KeyManager::getManager()->keyDown(Control::getManager()->GetCannonMoveLeft()))
	{
		rotation-=20*timeElapsed;
	}
	else if(KeyManager::getManager()->keyDown(Control::getManager()->GetCannonMoveRight()))
	{
		rotation+=20*timeElapsed;
	}
}

void Cannon::AIControl(float timeElapsed,vector<Entity*> *nightmares)
{
	float dist = 2000*((Unit*)controller)->getHatStrength();
	float num = -1;
	for(int j = 0; j < nightmares->size(); j++)
	{
		if(((Station*)nightmares->at(j))!=myStation)
		{
			bool kill = true;
			if(((Station*)nightmares->at(j))->getAssignedUnits()->size()>0)
			{
				for(int i = 0; i < ((Station*)nightmares->at(j))->getAssignedUnits()->size();i++)
				{
					if(controller->getEntity()==((Station*)nightmares->at(j))->getAssignedUnits()->at(i)->getEntity())
					{
						kill=false;
					}
				}
			}
			else
			{
				if(((Station*)nightmares->at(j))->getAssignedCrew()->size()==0)
				{
					kill=false;
				}
			}
			if(kill)
			{
				if(num==-1)
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = myStation->getPos().x + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y));
					Vector2f distBetween = Vector2f(ePos.x-myPosX,ePos.y-myPosY);
					if(distBetween.length()<dist)
					{
						num=j;
						dist=distBetween.length();
					}
				}
				else
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = myStation->getPos().x + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y));
					Vector2f distBetween = Vector2f(ePos.x-myPosX,ePos.y-myPosY);
					if(distBetween.length()<dist)
					{
						num=j;
						dist=distBetween.length();
					}
				}
			}
		}
	}
	if(num != -1)
	{
		Vector2f ePos = ((Station*)nightmares->at(num))->getPos();
		Vector2f vel = ((Station*)nightmares->at(num))->getVelocity();
		aimAtPoint(timeElapsed,ePos,vel);
	}
}


void Cannon::aimAtPoint(float timeElapsed, Vector2f pos, Vector2f vel)
{
	float myPosX = myStation->getPos().x + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y));
	float myPosY = myStation->getPos().y + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y));
	Vector2f distBetween = Vector2f(pos.x-myPosX,pos.y-myPosY);
	float time = 826.0f/distBetween.length();
	Vector2f fDist = (myStation->getVelocity()/time)*-1;
	Vector2f fDist2 = (vel/time);
	float rot =  rotation;
	if(rot < 0)
	{
		rot+=360;
	}
	if(rot>=360)
	{
		rot -= 360;
	}
	float dir = 0;
	distBetween = Vector2f((pos.x+fDist.x+fDist2.x)-(myPosX),(pos.y+fDist.y+fDist2.y)-(myPosY));
	distBetween /= distBetween.length();
	dir = ( ( SDL_cos((rot)*M_PI/180)*180/M_PI) * (distBetween.y) - ( SDL_sin((rot)*M_PI/180)*180/M_PI) * (distBetween.x));
	if(dir <-2)
	{
		rotation -=20*timeElapsed;
	}
	else if(dir > 2)
	{
		rotation += 20*timeElapsed;
	}
	if( dir <=2 && dir >= -2)
	{
		action(timeElapsed);
	}
}


void Cannon::crewControl(float timeElapsed,vector<Entity*> *nightmares)
{
	float dist = 2000*((Unit*)controller)->getHatStrength();
	float num = -1;
	for(int j = 0; j < nightmares->size(); j++)
	{
		if(((Station*)nightmares->at(j))!=myStation)
		{
			if(((Station*)nightmares->at(j))->getAssignedUnits()->size()>0&&((Station*)nightmares->at(j))->getAssignedCrew()->size()==0)
			{
				if(num==-1)
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = myStation->getPos().x + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y));
					Vector2f distBetween = Vector2f(ePos.x-myPosX,ePos.y-myPosY);
					if(distBetween.length()<dist)
					{
						num=j;
						dist=distBetween.length();
					}
				}
				else
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = myStation->getPos().x + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y));
					Vector2f distBetween = Vector2f(ePos.x-myPosX,ePos.y-myPosY);
					if(distBetween.length()<dist)
					{
						num=j;
						dist=distBetween.length();
					}
				}
			}
		}
	}
	if(num != -1)
	{
		Vector2f ePos = ((Station*)nightmares->at(num))->getPos();
		Vector2f vel = ((Station*)nightmares->at(num))->getVelocity();
		aimAtPoint(timeElapsed,ePos,vel);
	}
}

void Cannon::action(float timeElapsed)
{
	if(reloadTime <= 0)
	{
		Vector2f firePos;
		firePos.x = (myStation->getPos().x) + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y))) + (((cos(rotation*M_PI/180)*46)-(sin(rotation*M_PI/180)*0)));
		firePos.y = (myStation->getPos().y) + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y))) + (((sin(rotation*M_PI/180)*46)+(cos(rotation*M_PI/180)*0)));
		myStation->getCannonBalls()->push_back(new CannonBall(Vector2f(firePos.x,firePos.y),rotation,myStation->getVelocity(),Station::CANNONBALL_DAMAGE*myStation->getDmgMultiply(),1*((Unit*)controller)->getHatStrength(),position));
		reloadTime = maxReloadTime;
	}
	
}

void Cannon::grapple(float timeElapsed)
{
	if(reloadTime <= 0)
	{
		Vector2f firePos;
		firePos.x = (myStation->getPos().x) + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y))) + (((cos(rotation*M_PI/180)*46)-(sin(rotation*M_PI/180)*0)));
		firePos.y = (myStation->getPos().y) + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y))) + (((sin(rotation*M_PI/180)*46)+(cos(rotation*M_PI/180)*0)));
		myStation->getCannonBalls()->push_back(new Grapple(Vector2f(firePos.x,firePos.y),rotation,myStation->getVelocity(),100,1*((Unit*)controller)->getHatStrength(),position));
		reloadTime = maxReloadTime;
	}
	
}


void Cannon::update(float timeElapsed)
{
	if(reloadTime>0)
	{
		reloadTime-=timeElapsed*myStation->getReloadMultiply();
	}

	if (reloadTime >= 2)
	{
		isMuzzleFlash = true;
	}
	else
	{
		isMuzzleFlash = false;
	}
}



void Cannon::draw(SDL_Renderer* renderer,Vector2f offset,float scale)
{
	//rotation = rot;
	posRec->x = (myStation->getPos().x)*scale + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(radius/2))*scale;
	posRec->y = (myStation->getPos().y)*scale + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(radius/2))*scale;
	posRec->w = radius*scale;//length;
	posRec->h = radius*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->circle->getTexture(),nullptr,posRec,myStation->getRotation(),nullptr,SDL_FLIP_NONE);

	posRec->x = (myStation->getPos().x)*scale + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(62/2))*scale) + (((cos(rotation*M_PI/180)*31)-(sin(rotation*M_PI/180)*0))*scale);
	posRec->y = (myStation->getPos().y)*scale + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(26/2))*scale) + (((sin(rotation*M_PI/180)*31)+(cos(rotation*M_PI/180)*0))*scale);
	posRec->w = 62*scale;//length;
	posRec->h = 26*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->canon->getTexture(),nullptr,posRec, rotation,nullptr,SDL_FLIP_NONE);

	if(isMuzzleFlash == true)
	{
		posRec->x = (myStation->getPos().x)*scale + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(62/2))*scale) + (((cos(rotation*M_PI/180)*85)-(sin(rotation*M_PI/180)*0))*scale);
		posRec->y = (myStation->getPos().y)*scale + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(26/2))*scale) + (((sin(rotation*M_PI/180)*85)+(cos(rotation*M_PI/180)*0))*scale);
		posRec->w = 62*scale;//length;-(62/2)
		posRec->h = 26*scale;//breadth;-(26/2)
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->muzzleFlash->getTexture(),nullptr,posRec, rotation,nullptr,SDL_FLIP_NONE);
	}

}
void Cannon::drawTop(SDL_Renderer* renderer,Vector2f offset,float scale)
{
	posRec->x = (myStation->getPos().x)*scale + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(62/2))*scale) + (((cos(rotation*M_PI/180)*31)-(sin(rotation*M_PI/180)*0))*scale);
	posRec->y = (myStation->getPos().y)*scale + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(26/2))*scale) + (((sin(rotation*M_PI/180)*31)+(cos(rotation*M_PI/180)*0))*scale);
	posRec->w = 62*scale;//length;
	posRec->h = 26*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->canonTop->getTexture(),nullptr,posRec, rotation,nullptr,SDL_FLIP_NONE);

	if(controller)
	{
		posRec->x = (myStation->getPos().x)*scale + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(128/2))*scale) + (((cos(rotation*M_PI/180)*192)-(sin(rotation*M_PI/180)*0))*scale);
		posRec->y = (myStation->getPos().y)*scale + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(64/2))*scale) + (((sin(rotation*M_PI/180)*192)+(cos(rotation*M_PI/180)*0))*scale);
		posRec->w = 128*scale;//length;
		posRec->h = 64*scale;//breadth;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->arrow->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
	}

}

Cannon::~Cannon(void)
{
}
