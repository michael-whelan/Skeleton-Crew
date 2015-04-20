#include "Helm.h"


Helm::Helm(float x,float y, float r, Texture* mtexture, Station* station):Job(x,y,r,station)
{
	texture = mtexture;
}


Helm::Helm(float x,float y, float r, Texture* mtexture, Station* station,Entity* control):Job(x,y,r,station,control)
{
	texture = mtexture;
}


Helm::~Helm(void)
{
}

void Helm::setUpgrade(float f)
{} 

void Helm::movement(float timeElapsed)
{
	if (KeyManager::getManager()->keyDown(Control::getManager()->GetHelmMoveUp()))
	{
		Vector2f dir;
		dir.x = cos(myStation->getRotation()*M_PI/180);
		dir.y = sin(myStation->getRotation()*M_PI/180);
		myStation->setAcceleration(Vector2f(dir.x*timeElapsed*Station::ACCELERATION_SPEED*myStation->getSpeedMultiply()*((Unit*)controller)->getHatStrength(),dir.y*timeElapsed*Station::ACCELERATION_SPEED*myStation->getSpeedMultiply()*((Unit*)controller)->getHatStrength()));
    }
	else if (KeyManager::getManager()->keyDown(Control::getManager()->GetHelmMoveDown()))
	{
		myStation->setVelocity(myStation->getVelocity()*(1-(0.4f*timeElapsed)));
    }
	if (KeyManager::getManager()->keyDown(Control::getManager()->GetHelmMoveLeft()))
	{
		myStation->changeRotation(-myStation->getVelocity().length()/5*timeElapsed);
    }
	else if (KeyManager::getManager()->keyDown(Control::getManager()->GetHelmMoveRight()))
	{
		myStation->changeRotation(myStation->getVelocity().length()/5*timeElapsed);
    }
}

void Helm::AIControl(float timeElapsed,vector<Entity*> *nightmares)
{
	float dist = 5000/CameraManager::getManager()->getScale();
	float num = -1;
	for(int j = 0; j < nightmares->size(); j++)
	{
		if(((Station*)nightmares->at(j))!=myStation)
		{
			bool kill = false; 
			for(int i = 0; i < ((Station*)nightmares->at(j))->getAssignedUnits()->size();i++)
			{
				if(controller->getEntity()!=((Station*)nightmares->at(j))->getAssignedUnits()->at(i)->getEntity())
				{
					kill=true;
				}
			}
			if(((Station*)nightmares->at(j))->getAssignedCrew()->size()>0||kill)
			{
				if(num==-1)
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = myStation->getPos().x + ((cos(rotation*M_PI/180)*position.x)-(sin(rotation*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(rotation*M_PI/180)*position.x)+(cos(rotation*M_PI/180)*position.y));
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
					float myPosX = myStation->getPos().x + ((cos(rotation*M_PI/180)*position.x)-(sin(rotation*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(rotation*M_PI/180)*position.x)+(cos(rotation*M_PI/180)*position.y));
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
	if(num!=-1)
	{
		aimAtPoint(timeElapsed,((Station*)nightmares->at(num))->getPos(),myStation->getVelocity());
	}
	action(timeElapsed);
}


void Helm::aimAtPoint(float timeElapsed, Vector2f pos, Vector2f vel)
{
	float myPosX = myStation->getPos().x + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y));
	float myPosY = myStation->getPos().y + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y));
	Vector2f distBetween = Vector2f(pos.x-myPosX,pos.y-myPosY);
	float time = 826.0f/distBetween.length();
	Vector2f fDist = (myStation->getVelocity()/time)*-1;
	Vector2f fDist2 = (vel/time);
	float rot =  rotation;
	distBetween /= distBetween.length();
	float dir;// = ( ( vel.x) * (pos.y-myStation->getPos().y) - ( vel.y) * (pos.x-myStation->getPos().x));
	//float dir = 0;
	dir = ( ( SDL_cos((myStation->getRotation())*M_PI/180)*180/M_PI) * (distBetween.y) - ( (SDL_sin((myStation->getRotation())*M_PI/180)*180/M_PI)) * (distBetween.x));
	if(dir < -5)
	{
		myStation->changeRotation(-vel.length()/5*timeElapsed);
	}
	else if(dir > 5)
	{
		myStation->changeRotation(vel.length()/5*timeElapsed);
	}
}


void Helm::crewControl(float timeElapsed,vector<Entity*> *nightmares)
{
	float dist = 5000/CameraManager::getManager()->getScale();
	float num = -1;
	for(int j = 0; j < nightmares->size(); j++)
	{
		if(((Station*)nightmares->at(j))!=myStation)
		{
			if(((Station*)nightmares->at(j))->getAssignedUnits()->size()>0)
			{
				if(num==-1)
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = myStation->getPos().x + ((cos(rotation*M_PI/180)*position.x)-(sin(rotation*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(rotation*M_PI/180)*position.x)+(cos(rotation*M_PI/180)*position.y));
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
					float myPosX = myStation->getPos().x + ((cos(rotation*M_PI/180)*position.x)-(sin(rotation*M_PI/180)*position.y));
					float myPosY = myStation->getPos().y + ((sin(rotation*M_PI/180)*position.x)+(cos(rotation*M_PI/180)*position.y));
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
	if(num!=-1)
	{
		aimAtPoint(timeElapsed,((Station*)nightmares->at(num))->getPos(),myStation->getVelocity());
	}
	action(timeElapsed);
}


void Helm::action(float timeElapsed)
{
	Vector2f dir;
	dir.x = cos(myStation->getRotation()*M_PI/180);
	dir.y = sin(myStation->getRotation()*M_PI/180);
		myStation->setAcceleration(Vector2f(dir.x*timeElapsed*Station::ACCELERATION_SPEED*myStation->getSpeedMultiply()*((Unit*)controller)->getHatStrength(),dir.y*timeElapsed*Station::ACCELERATION_SPEED*myStation->getSpeedMultiply()*((Unit*)controller)->getHatStrength()));
} 


void Helm::update(float timeElapsed)
{
}


void Helm::draw(SDL_Renderer* renderer,Vector2f offset,float scale)
{
	posRec->x = (myStation->getPos().x)*scale + ((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(radius/2))*scale;
	posRec->y = (myStation->getPos().y)*scale + ((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(radius/2))*scale;
	posRec->w = radius*scale;//length;
	posRec->h = radius*scale;//breadth;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->circle->getTexture(),nullptr,posRec,myStation->getRotation(),nullptr,SDL_FLIP_NONE);

	if(texture!=nullptr)
	{
		posRec->x = (myStation->getPos().x)*scale + (((cos(myStation->getRotation()*M_PI/180)*position.x)-(sin(myStation->getRotation()*M_PI/180)*position.y)-(26/2))*scale) + (((cos(myStation->getRotation()*M_PI/180)*30)-(sin(myStation->getRotation()*M_PI/180)*0))*scale);
		posRec->y = (myStation->getPos().y)*scale + (((sin(myStation->getRotation()*M_PI/180)*position.x)+(cos(myStation->getRotation()*M_PI/180)*position.y)-(52/2))*scale) + (((sin(myStation->getRotation()*M_PI/180)*30)+(cos(myStation->getRotation()*M_PI/180)*0))*scale);
		posRec->w = 26*scale;//length;
		posRec->h = 52*scale;//breadth;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,myStation->getRotation(),nullptr,SDL_FLIP_NONE);
	}

}

void Helm::drawTop(SDL_Renderer* renderer,Vector2f offset,float scale)
{

}