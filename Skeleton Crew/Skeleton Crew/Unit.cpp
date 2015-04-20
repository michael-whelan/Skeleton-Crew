#include "Unit.h"

float Unit::hatStrength[7] = {1,1.1f,1.5f,2,3,5,10};
string Unit::hatName[7] = {"","Rigger","Seaman","Boatswain","First Mate","Captain","Admiral"};
short Unit::baseHealth=100;
short Unit::baseMissChance=40;
short Unit::baseDamage=25;
short Unit::baseSpeed=50;

Unit::Unit(float x, float y):Entity(x,y)
{
	size = Vector2f(52,52);
	localPosition.x = 0;
	localPosition.y =0;
	stationedAt=0;
	myHat = hatUpgrades::noneHat;
	myState = states::noneState;
	myEntity = entityType::entity|entityType::unit;
	grappleColdown=0;
	myJob=0;
}


Unit::Unit(float x, float y, Entity* stationed):Entity(x,y)
{
	size = Vector2f(52,52);
	if(stationed)
	{
		stationedAt=stationed;
		localPosition.x = x - stationedAt->getPos().x;
		localPosition.y = y - stationedAt->getPos().y;
	}
	myHat = hatUpgrades::noneHat;
	myState = states::noneState;
	myEntity = entityType::entity|entityType::unit;
	grappleColdown=0;
	myJob=0;
}

Unit::Unit(float x, float y,Entity* stationed,states state):Entity(x,y)
{ 
	size = Vector2f(52,52);
	myHat = hatUpgrades::noneHat;
	myState = state;
	stationedAt = stationed;
	localPosition.x = x - stationedAt->getPos().x;
	localPosition.y = y - stationedAt->getPos().y;
	myEntity = entityType::entity|entityType::unit;
	grappleColdown=0;
	myJob=0;
}

Unit::~Unit(void)
{
	if(stationedAt)
	{
		if(((Station*)stationedAt)->getAssignedCrew())
		{
			vector<Entity*>::iterator entityIter = ((Station*)stationedAt)->getAssignedCrew()->begin();
			for(; entityIter != ((Station*)stationedAt)->getAssignedCrew()->end();)
			{
				if(*entityIter==this)
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->deathCry,position);
					entityIter = ((Station*)stationedAt)->getAssignedCrew()->erase(entityIter);
				}
				else
				{
					++entityIter;
				}
			}
		}
		if(((Station*)stationedAt)->getAssignedUnits())
		{
			vector<Entity*>::iterator entityIter = ((Station*)stationedAt)->getAssignedUnits()->begin();
			for(; entityIter != ((Station*)stationedAt)->getAssignedUnits()->end();)
			{
				if(*entityIter==this)
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->deathCry,position);
					entityIter = ((Station*)stationedAt)->getAssignedUnits()->erase(entityIter);
				}
				else
				{
					++entityIter;
				}
			}
		}
	}
	if(myJob)
	{
		if(myJob->getController()==this)
		{
			myJob->setController(0);
		}
	}
}

void Unit::update(float timeElapsed)
{
	if(personnelGrapple)
	{
		personnelGrapple->update(timeElapsed);
		if(!personnelGrapple->getAlive())
		{
			delete personnelGrapple;
			personnelGrapple=0;
		}
	}
	if(stationedAt)
	{
		localPosition.x+=velocity.x*timeElapsed;
		localPosition.y+=velocity.y*timeElapsed;
	}
	else
	{
		position.x+=velocity.x*timeElapsed;
		position.y+=velocity.y*timeElapsed;
	}
	if(attackTime>0)
	{
		attackTime -= timeElapsed;
	}
	if(coolTime>0)
	{
		coolTime -=timeElapsed;
	}
	if(grappleColdown>0)
	{
		grappleColdown-=timeElapsed;
	}
	velocity.x =0;
	velocity.y = 0;

}

void Unit::AIControl(float timeElapsed, vector<Entity*> *nightmares)
{
	vector<Entity*> *enemy = new vector<Entity*>();
	if(stationedAt)
	{
		enemy->insert(enemy->end(),((Station*)stationedAt)->getAssignedCrew()->begin(),((Station*)stationedAt)->getAssignedCrew()->end());
		for(int i = 0; i < ((Station*)stationedAt)->getAssignedUnits()->size();i++)
		{
			if(myEntity!=((Station*)stationedAt)->getAssignedUnits()->at(i)->getEntity())
			{
				enemy->push_back(((Station*)stationedAt)->getAssignedUnits()->at(i));
			}
		}
	}
	switch(myState)
	{
		case noneState:
			DefultState(timeElapsed,enemy,nightmares);
			break; 
		case job:
			doJob(timeElapsed, nightmares);
			break;
		case boarding:
			break;
		case following:
			break;
		case attacking:
			Attack(timeElapsed,enemy);//needs work
			break;
		case scared:
			runAroundScared(timeElapsed);
			break;
	}
	enemy->clear();
	delete enemy;
}

/*
--------------------
Command the villagers to run around the village 
--------------------
*/
void Unit::runAroundScared(float timeElapsed)
{
	//Run around the island 
	//Seek to a random position on island
	if(stationedAt)
	{
		if(targetPos.length()==0)
		{
			bool found = false;
			int xp;
			int yp;
			while (!found)
			{
				xp=rand() % ((int)stationedAt->getSize().x);
				yp=rand() % ((int)stationedAt->getSize().y);
				Vector2f ratio = Vector2f(1/stationedAt->getSize().x*stationedAt->getTexture()->getSize().x,1/stationedAt->getSize().y*stationedAt->getTexture()->getSize().y);
				if(xp>0 && xp < stationedAt->getSize().x && yp>0 && yp < stationedAt->getSize().y)
				{
					Uint32 pixel = stationedAt->getTexture()->get_pixel32(xp*ratio.x,yp*ratio.y);
					if(pixel != Texture::transparent && pixel != 0)
					{
						found = true;
						scream();
					}
				}
			}
			targetPos = Vector2f(xp-(stationedAt->getSize().x/2),yp-(stationedAt->getSize().y/2));
		}

		Seek(targetPos, timeElapsed, 1.5f);
	}
}

/*
----------------------
Default states an A.I. has when no other jobs are 
----------------------
*/
void Unit::DefultState(float timeElapsed, vector<Entity*>* enemy, vector<Entity*>* ships)
{
	if(stationedAt)
	{ 
		if(enemy->size()>0)
		{
			myState= states::attacking;
		}
		else 
		{
			Job* findJob = 0;
			Vector2f dist;
			Station* s = (Station*)stationedAt;
			for(int i = 0; i < s->getHelms()->size();i++)
			{
				if(!s->getHelms()->at(i)->getController())
				{
					if(!findJob)
					{
						dist = localPosition - s->getHelms()->at(i)->getPosition();
						findJob = s->getHelms()->at(i);
					}
					else
					{
						Vector2f temp = localPosition - s->getHelms()->at(i)->getPosition();
						if(temp.length() < dist.length())
						{
							findJob = s->getHelms()->at(i);
							dist = temp;
						}
					}
				}
			}
			if(!findJob)
			{
				for(int i = 0; i < s->getCannons()->size();i++)
				{
					if(!s->getCannons()->at(i)->getController())
					{
						if(!findJob)
						{
							dist = localPosition - s->getCannons()->at(i)->getPosition();
							findJob = s->getCannons()->at(i);
						}
						else
						{
							Vector2f temp = localPosition - s->getCannons()->at(i)->getPosition();
							if(temp.length() < dist.length())
							{
								findJob = s->getCannons()->at(i);
								dist = temp;
							}
						}
					}
				}
			}
			if(!findJob)
			{
				for(int i = 0; i < s->getCrowNests()->size();i++)
				{
					if(!s->getCrowNests()->at(i)->getController())
					{
						if(!findJob)
						{
							dist = localPosition - s->getCrowNests()->at(i)->getPosition();
							findJob = s->getCrowNests()->at(i);
						}
						else
						{
							Vector2f temp = localPosition - s->getCrowNests()->at(i)->getPosition();
							if(temp.length() < dist.length())
							{
								findJob = s->getCrowNests()->at(i);
								dist = temp;
							}
						}
					}
				}
			}
			if(findJob)
			{
				Seek(findJob->getPosition(),timeElapsed,1);
				if(dist.length()-(5*hatStrength[myHat])<findJob->getRadius())
				{
					checkJob(findJob);
				}
			}
			else
			{
				float dist = 190*4;
				Vector2f endPos;
				bool f = false;
				for(int i = 0; i < ships->size(); i++)
				{
					if(ships->at(i)!=stationedAt)
					{
						if(((Station*)ships->at(i))->getAssignedCrew()>0||((Station*)ships->at(i))->getAssignedUnits()>0)
						{
							Vector2f pos = position-ships->at(i)->getPos();
							if(pos.length()<dist)
							{
								dist = pos.length();
								endPos = ships->at(i)->getPos();
								f=true;
							}
						}
					}
				}
				if(f)
				{
					if(!personnelGrapple&&grappleColdown<=0)
					{
						float xDiff = endPos.x - (position.x) ;
						float yDiff = endPos.y - (position.y) ;
						float rot = (atan2(yDiff,xDiff)) *(180/M_PI);
						personnelGrapple=new Grapple(position,rot,Vector2f(0,0),0,3,localPosition);
						grappleColdown=5;
					}
				}
				if(targetPos.length()==0)
				{
					bool found = false;
					int xp;
					int yp;
					while (!found)
					{
						xp=rand() % ((int)stationedAt->getSize().x);
						yp=rand() % ((int)stationedAt->getSize().y);
						Vector2f ratio = Vector2f(1/stationedAt->getSize().x*stationedAt->getTexture()->getSize().x,1/stationedAt->getSize().y*stationedAt->getTexture()->getSize().y);
						if(xp>0 && xp < stationedAt->getSize().x && yp>0 && yp < stationedAt->getSize().y)
						{
							Uint32 pixel = stationedAt->getTexture()->get_pixel32(xp*ratio.x,yp*ratio.y);
							if(pixel != Texture::transparent && pixel != 0)
							{
								found = true;
							}
						}
					}
					targetPos = Vector2f(xp-(stationedAt->getSize().x/2),yp-(stationedAt->getSize().y/2));
				}
				Seek(targetPos, timeElapsed,1);

			}
		}
	}
	else
	{
		float dist = 190*4;
		Vector2f endPos;
		bool f = false;
		for(int i = 0; i < ships->size(); i++)
		{
			Vector2f pos = position-ships->at(i)->getPos();
			if(pos.length()<dist)
			{
				dist = pos.length();
				endPos = ships->at(i)->getPos();
				f=true;
			}
		}
		if(f)
		{
			if(!personnelGrapple&&grappleColdown<=0)
			{
				float xDiff = endPos.x - (position.x) ;
				float yDiff = endPos.y - (position.y) ;
				float rot = (atan2(yDiff,xDiff)) *(180/M_PI);
				personnelGrapple=new Grapple(position,rot,Vector2f(0,0),0,3,localPosition);
				grappleColdown=5;
			}
		}
	}
}

/*
---------------------
called by the AI, plays a scream sound
---------------------
*/
void Unit::scream(){
	int random = rand() % 600;
						if (random == 1)
						{
							random = rand() % 2 + 1;
							if( random == 1){
								SoundManager::getManager()->startSound(SoundManager::getManager()->scream1, position);
							}
							else
							{
								SoundManager::getManager()->startSound(SoundManager::getManager()->scream2, position);
							}
						}
}
/*
---------------------
Assigns a job to a unit
---------------------
*/
void Unit::doJob(float timeElapsed, vector<Entity*> *nightmares)
{
	if(stationedAt)
	{
		if(((Station*)stationedAt)->getAssignedCrew()->size()>0)
		{
			if(myJob)
			{
				setJob(0);
			}
			myState= states::attacking;
		}
		else
		{
			for(int i = 0; i < ((Station*)stationedAt)->getAssignedUnits()->size();i++)
			{
				if(myEntity!=((Station*)stationedAt)->getAssignedUnits()->at(i)->getEntity())
				{
					if(myJob)
					{
						setJob(0);
					}
					myState= states::attacking;
				}
			}
			if(myJob)
			{
				if(myJob->getController()==this&&myJob->getStation()==stationedAt)
				{
					myJob->AIControl(timeElapsed,nightmares);
					localPosition = myJob->getPosition();
					rotation = stationedAt->getRotation() + myJob->getRotation();
				}
			}
			else
			{
				setJob(0);
				myState= states::noneState;
			}
		}
	}
}
/*
-------------
Attacking: hand to hand combat
-------------
*/

void Unit::Attack(float timeElasped, vector<Entity*>* enemy)
{
	int length = enemy->size();
	if(length==0)
	{
		myState = states::noneState;
	}
	else
	{
		int num = 0;
		Vector2f dist = ((Unit*)enemy->at(0))->getLocalPos() - localPosition;
		for(int i = 0; i < length; i++)
		{
			Vector2f temp;
			temp = ((Unit*)enemy->at(i))->getLocalPos() - localPosition;
			if(temp.length() < dist.length())
			{
				dist = temp;
				num = i;
			}
		}
		Seek(((Unit*)enemy->at(num))->getLocalPos(),timeElasped,1);
		if(dist.length()<=((size.x/2)+25))
		{
			if (coolTime<= 0)
			{
				attackTime=0.3f;
				coolTime=attackTime+0.3f;
			}
		}
	}
}

void Unit::draw(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	if(stationedAt)
	{
		position.x=stationedAt->getPos().x+(cosf(stationedAt->getRotation()*M_PI/180)*localPosition.x)-(sinf(stationedAt->getRotation()*M_PI/180)*localPosition.y);
		position.y=stationedAt->getPos().y+(sinf(stationedAt->getRotation()*M_PI/180)*localPosition.x)+(cosf(stationedAt->getRotation()*M_PI/180)*localPosition.y);
	}
	//Entity::draw(renderer,scale,offset);
	posRec->x = ((position.x-(size.x/2))*scale)+ (((cos(rotation*M_PI/180)*16)-(sin(rotation*M_PI/180)*0))*scale);
	posRec->y = ((position.y-(size.y/2))*scale)+ (((sin(rotation*M_PI/180)*16)+(cos(rotation*M_PI/180)*0))*scale);
	posRec->w = size.x*scale;
	posRec->h = size.y*scale;
	posRec->x-=offset.x;
	posRec->y-=offset.y;
	float angle =  rotation*M_PI/180;
	SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,rotation,nullptr,SDL_FLIP_NONE);
	if(attackTime>0)
	{
		posRec->x = (position.x-2.5)*scale; 
		posRec->y = (position.y-20)*scale;
		posRec->w = 5*scale;
		posRec->h = 40*scale;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->sword->getTexture(),nullptr,posRec,rotation + 90,nullptr,SDL_FLIP_NONE);
	}
	if(myHat!=hatUpgrades::noneHat)
	{
		//Entity::draw(renderer,scale,offset);
		posRec->x = ((position.x-(32/2))*scale);//+ (((cos(rotation*M_PI/180)*-16)-(sin(rotation*M_PI/180)*0))*scale);
		posRec->y = ((position.y-(32/2))*scale);//+ (((sin(rotation*M_PI/180)*-16)+(cos(rotation*M_PI/180)*0))*scale);
		posRec->w = 32*scale;
		posRec->h = 32*scale;
		posRec->x-=offset.x;
		posRec->y-=offset.y;
		float angle =  rotation*M_PI/180;
		Texture* t = nullptr;
		switch (myHat)
		{
		case Unit::noneHat:
			t = nullptr;
			break;
		case Unit::seaman:
			t = TextureManager::getManager()->pirateRank1;
			break;
		case Unit::petty_officer:
			t = TextureManager::getManager()->pirateRank2;
			break;
		case Unit::chief_petty_officer:
			t = TextureManager::getManager()->pirateRank3;
			break;
		case Unit::lieutenant:
			t = TextureManager::getManager()->pirateRank4;
			break;
		case Unit::captain:
			t = TextureManager::getManager()->pirateRank5;
			break;
		case Unit::admiral:
			t = TextureManager::getManager()->pirateRank6;
			break;
		default:
			break;
		}
		if(t)
		{
			SDL_RenderCopyEx(renderer,t->getTexture(),nullptr,posRec,rotation-90,nullptr,SDL_FLIP_NONE);
		}
	}
	if(personnelGrapple)
	{
		personnelGrapple->draw(renderer,scale,offset);
	}
}

/*
-----------------------
Board enemy ship: Use this method to command a selected unit 
to board an enemy ship 
-----------------------
*/
void Unit::BoardEnemyShip(Entity* targetShip)
{
	for(int j = 0; j < ((Station*)stationedAt)->getAssignedCrew()->size(); j++)
	{
		if(((Station*)stationedAt)->getAssignedCrew()->at(j)==this)
		{
			((Station*)stationedAt)->getAssignedCrew()->erase(((Station*)stationedAt)->getAssignedCrew()->begin()+j);
			break;
		}
	}
	((Station*)targetShip)->getAssignedCrew()->push_back(this);
	stationedAt=targetShip;
	targetPos = targetShip->getPos();
}


Unit::hatUpgrades Unit::upgradeUnit(Unit::hatUpgrades newHat)
{
	float scale = health/getMaxHealth();
	Unit::hatUpgrades oldHat = myHat;
	myHat = newHat;
	health = scale*getMaxHealth();
	return oldHat;
}

Unit::hatUpgrades Unit::getHat()
{
	return myHat;
}

void Unit::Seek(Vector2f targetPosition, float timeE, float speed)
{
	Vector2f seekDir = Vector2f(0,0);
	seekDir.x = targetPosition.x - localPosition.x;
	seekDir.y = targetPosition.y - localPosition.y;
	if(seekDir.length()>5*hatStrength[myHat])
	{
		seekDir = seekDir/seekDir.length();
		rotation = asinf(velocity.y/velocity.length())*180.0f/M_PI;
		if(rotation>=360)
		{
			rotation-=360;
		}
		else if (rotation < 0)
		{
			rotation+=360;
		}
		if(velocity.x<0)
		{
			rotation=90+(90-rotation);
		}
		if(rotation>=360)
		{
			rotation-=360;
		}
		else if (rotation < 0)
		{
			rotation+=360;
		}
		if(_isnan(rotation))
		{
			rotation = 0;
		}
	}
	else
	{
		seekDir=Vector2f(0,0);
		targetPos=Vector2f(0,0);
	}
	seekDir*=baseSpeed * speed*hatStrength[myHat];
	velocity.x += seekDir.x;
	velocity.y += seekDir.y;
}

bool Unit::AddNewCrew()
{ 
	int chance = rand() % 3;  //range 0 to 2 inclusive
	if(chance == 0)
	{
		return true; 
	}
	else 
	{
		return false;
	}
}

void Unit::Hit(Vector2f direction, float damage)
{
	health-=damage;
}


Entity* Unit::getStation()
{
	return stationedAt;
}

void Unit::setJob(Job* job)
{
	if(myJob)
	{
		if(myJob->getController()==this)
		{
			myJob->setController(0);
		}
	}
	if(!job)
	{
		myState=states::noneState;
	}
	myJob = job;
}

void Unit::grapplePoint(Vector2f pos)
{
	Vector2f endPos;
	if(stationedAt)
	{
		endPos.x = ((cos((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).x)))-(sin((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).y))));
		endPos.y = ((sin((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).x)))+(cos((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).y))));
		localPosition=endPos;
		//localPosition.x = stationedAt->getPos().x + ((cos(stationedAt->getRotation()*M_PI/180)*(endPos.x))-(sin(-stationedAt->getRotation()*M_PI/180)*(endPos.y)));
		//localPosition.y = stationedAt->getPos().y + ((sin(stationedAt->getRotation()*M_PI/180)*(endPos.x))+(cos(-stationedAt->getRotation()*M_PI/180)*(endPos.y)));
		myState = grappling;
		endPos.x = ((cos((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).x)))-(sin((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).y))));
		endPos.y = ((sin((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).x)))+(cos((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).y))));
		targetPos = endPos;
	}
	if(personnelGrapple)
	{
		delete personnelGrapple;
	}
	personnelGrapple = 0;
	//((Station*)stationedAt)->getAssignedUnits()->push_back(this);
}




void Unit::checkJob(Job* job)
{
	if(!job->getController())
	{
		float x = job->getPosition().x - localPosition.x;
		float y = job->getPosition().y - localPosition.y;
		float z = job->getRadius() + 8 + 5*hatStrength[myHat];
		if(x*x + y*y < z*z)
		{
			job->setController(this);
			setJob(job);
			myState = states::job;
			velocity.x=0;
			velocity.y=0;
			localPosition.x=job->getPosition().x;
			localPosition.y=job->getPosition().y;
		}
	}
}

/*
	if(KeyManager::getManager()->mousePressed(KeyManager::left) && crew == true)
	{
		if( KeyManager::getManager()->mousePosition().x + CameraManager::getManager()->getOffSet().x > (position.x -16) *CameraManager::getManager()->getScale() && KeyManager::getManager()->mousePosition().x+ CameraManager::getManager()->getOffSet().x < (position.x + 16)*CameraManager::getManager()->getScale() && 
			KeyManager::getManager()->mousePosition().y+ CameraManager::getManager()->getOffSet().y > (position.y -16)*CameraManager::getManager()->getScale()  && KeyManager::getManager()->mousePosition().y+ CameraManager::getManager()->getOffSet().y < (position.y + 16)*CameraManager::getManager()->getScale())
		{
			selected = true;
		}
	}
	
	BoardEnemyShip(targetShip);
	if(KeyManager::getManager()->mousePressed(KeyManager::left) && crew == false)
	{
		if( KeyManager::getManager()->mousePosition().x > position.x  && KeyManager::getManager()->mousePosition().x < position.x + 30 && 
			KeyManager::getManager()->mousePosition().y > position.y  && KeyManager::getManager()->mousePosition().y < position.y + 30 )
		{
			alive = false; 
		}
	}







	
	else if(myState==states::driving)
	{
		if(stationedAt != nullptr)
		{
			for(int i = 0; i < ((Station*)stationedAt)->getHelms()->size();i++)
			{
				if(((Station*)stationedAt)->getHelms()->at(i).second == this)
				{
					stationedAt->AIControl(timeElapsed,nightmares);
					localPosition = Vector2f(((Station*)stationedAt)->getHelms()->at(i).first.x,((Station*)stationedAt)->getHelms()->at(i).first.y);
					rotation = stationedAt->getRotation();
				}
			}
		}
	}
	else if(myState==states::cannon)
	{
		if(stationedAt != nullptr)
		{
			for(int i = 0; i < ((Station*)stationedAt)->getCannons()->size();i++)
			{
				if(((Station*)stationedAt)->getCannons()->at(i).second == this)
				{
					((Station*)stationedAt)->cannonControl(timeElapsed,((Station*)stationedAt)->getCannons()->at(i).first,nightmares);
					localPosition = ((Station*)stationedAt)->getCannons()->at(i).first->getPosition();
					rotation = ((Station*)stationedAt)->getCannons()->at(i).first->getRotation();
				}
			}
		}
	}
	else if(myState==states::crow)
	{
		if(stationedAt != nullptr)
		{
			for(int i = 0; i < ((Station*)stationedAt)->getCrowNests()->size();i++)
			{
				if(((Station*)stationedAt)->getCrowNests()->at(i).second == this)
				{
					localPosition = Vector2f(((Station*)stationedAt)->getCrowNests()->at(i).first.x,((Station*)stationedAt)->getCrowNests()->at(i).first.y);
				}
			}
		}
	}
	*/