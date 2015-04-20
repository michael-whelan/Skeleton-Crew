#include "Crew.h"

vector<string> Crew::nameOptions = vector<string>();

Crew::Crew(float x, float y):Unit(x,y)
{
	health = baseHealth;
	texture = TextureManager::getManager()->skeletonPirate;
	myEntity = entityType::entity|entityType::unit|entityType::crew;
	name = nameOptions[rand()%nameOptions.size()];
}

Crew::Crew(float x, float y,Station* station, states state):Unit(x,y,station)
{
	health = baseHealth;
	myState = state;
	texture = TextureManager::getManager()->skeletonPirate;
	myEntity = entityType::entity|entityType::unit|entityType::crew;
	name = nameOptions[rand()%nameOptions.size()];
}

Crew::Crew(float x, float y,Station* station):Unit(x,y,station)
{
	health = baseHealth;
	texture = TextureManager::getManager()->skeletonPirate;
	myEntity = entityType::entity|entityType::unit|entityType::crew;
	name = nameOptions[rand()%nameOptions.size()];
}



Crew::~Crew(void)
{
}



void Crew::update(float timeElapsed)
{
	Unit::update(timeElapsed);
}


void Crew::OutOfBounds(float timeElapsed)
{
	int xp = localPosition.x+(velocity.x*timeElapsed)+(stationedAt->getSize().x/2);
	int yp = localPosition.y+(velocity.y*timeElapsed)+(stationedAt->getSize().y/2);
	Vector2f ratio = Vector2f(1/stationedAt->getSize().x*stationedAt->getTexture()->getSize().x,1/stationedAt->getSize().y*stationedAt->getTexture()->getSize().y);
	if(xp>0 && xp < stationedAt->getSize().x && yp>0 && yp < stationedAt->getSize().y)
	{
		Uint32 pixel = stationedAt->getTexture()->get_pixel32((localPosition.x+(stationedAt->getSize().x/2))*ratio.x,(localPosition.y+(stationedAt->getSize().y/2))*ratio.y);
		if(pixel != Texture::transparent && pixel != 0)
		{
			pixel = stationedAt->getTexture()->get_pixel32(xp*ratio.x,yp*ratio.y);
			if(pixel == Texture::transparent || pixel == 0)
			{
				velocity.x = 0;
				velocity.y = 0;
			}
		}
	}
	else
	{
		if((localPosition.x+(stationedAt->getSize().x/2)<0&&velocity.x <0)||(localPosition.x+(stationedAt->getSize().x/2)>stationedAt->getSize().x&&velocity.x >0))
		{
			velocity.x = 0;
		}
		if((localPosition.y+(stationedAt->getSize().y/2)<0&&velocity.y <0)||(localPosition.y+(stationedAt->getSize().y/2)>stationedAt->getSize().y&&velocity.y >0))
		{
			velocity.y = 0;
		}
	}
}

void Crew::movement(float timeElapsed)
{
	if(myState!=grappling)
	{
		if(myState==states::job)
		{
			if(stationedAt)
			{
				if(myJob)
				{
					if(myJob->getController()==this&&myJob->getStation()==stationedAt)
					{
						myJob->movement(timeElapsed);
						localPosition = myJob->getPosition();
						rotation = stationedAt->getRotation()+myJob->getRotation();
					}
				}
			}
		}
		else
		{
			if(KeyManager::getManager()->keyDown(Control::getManager()->GetGrappleCommand()))
			{
				if(!personnelGrapple&&grappleColdown<=0)
				{
					float xDiff = KeyManager::getManager()->mousePosition().x + CameraManager::getManager()->getOffSet().x - (position.x) * CameraManager::getManager()->getScale();
					float yDiff = KeyManager::getManager()->mousePosition().y + CameraManager::getManager()->getOffSet().y - (position.y) * CameraManager::getManager()->getScale();
					float rot = (atan2(yDiff,xDiff)) *(180/M_PI);
					personnelGrapple=new Grapple(position,rot,Vector2f(0,0),0,3,localPosition);
					grappleColdown=5;
				}
			}
			if (KeyManager::getManager()->keyDown(Control::getManager()->GetMoveUpCommand()))
			{
				if(stationedAt)
				{
					velocity.x += -cos((stationedAt->getRotation()-90)*M_PI/180)*baseSpeed*hatStrength[myHat];
					velocity.y += sin((stationedAt->getRotation()-90)*M_PI/180)*baseSpeed*hatStrength[myHat];
					OutOfBounds(timeElapsed);
				}
				else
				{
					velocity.y -= baseSpeed*hatStrength[myHat];
				}
			}
			if (KeyManager::getManager()->keyDown(Control::getManager()->GetMoveDownCommand()))
			{
				if(stationedAt)
				{
					velocity.x += cos((stationedAt->getRotation()-90)*M_PI/180)*baseSpeed*hatStrength[myHat];
					velocity.y += -sin((stationedAt->getRotation()-90)*M_PI/180)*baseSpeed*hatStrength[myHat];
					OutOfBounds(timeElapsed);
				}
				else
				{
					velocity.y +=baseSpeed*hatStrength[myHat];
				}
			}
			if (KeyManager::getManager()->keyDown(Control::getManager()->GetMoveLeftCommand()))
			{
				if(stationedAt)
				{
					velocity.x += -cos((stationedAt->getRotation())*M_PI/180)*baseSpeed*hatStrength[myHat];
					velocity.y += sin((stationedAt->getRotation())*M_PI/180)*baseSpeed*hatStrength[myHat];
					OutOfBounds(timeElapsed);
				}
				else
				{
					velocity.x -=baseSpeed*hatStrength[myHat];
				}
			}
			if (KeyManager::getManager()->keyDown(Control::getManager()->GetMoveRightCommand()))
			{
				if(stationedAt)
				{
					velocity.x += cos((stationedAt->getRotation())*M_PI/180)*baseSpeed*hatStrength[myHat];
					velocity.y += -sin((stationedAt->getRotation())*M_PI/180)*baseSpeed*hatStrength[myHat];
					OutOfBounds(timeElapsed);
				}
				else
				{
					velocity.x +=baseSpeed*hatStrength[myHat];
				}
			}
			if (KeyManager::getManager()->mouseDown(KeyManager::getManager()->mouseButtons::right) && coolTime<= 0)
			{
				attackTime=0.3f;
				coolTime=attackTime+0.3f;
				//myState = states::attacking; 
				//myState = states::raiding;
			}

			//var angle = Math.atan2(stage.mouseY - jetSprite.y, stage.mouseX - jetSprite.x );
			//angle = angle * (180/Math.PI);
			float xDiff = KeyManager::getManager()->mousePosition().x + CameraManager::getManager()->getOffSet().x - (position.x) * CameraManager::getManager()->getScale();
			float yDiff = KeyManager::getManager()->mousePosition().y + CameraManager::getManager()->getOffSet().y - (position.y) * CameraManager::getManager()->getScale();
			rotation = (atan2(yDiff,xDiff)) *(180/M_PI);
		}
		if (KeyManager::getManager()->keyPressed(Control::getManager()->GetAssignCommand()))
		{
			if(myState==states::job)
			{
				myState=states::noneState;
				setJob(0);
			}
			else
			{
				checkRole();
			}
		}
	}
}



void Crew::checkRole()
{
	if(stationedAt)
	{
		//Check if Crewman is in range of the crows nest
		for(int i = 0; i < ((Station*)stationedAt)->getHelms()->size();i++)
		{
			if(myState!=states::job)
			{
				checkJob(((Station*)stationedAt)->getHelms()->at(i));
			}
		}
		for(int i = 0; i < ((Station*)stationedAt)->getCannons()->size();i++)
		{
			if(myState!=states::job)
			{
				checkJob(((Station*)stationedAt)->getCannons()->at(i));
			}
		}
		for(int i = 0; i < ((Station*)stationedAt)->getCrowNests()->size();i++)
		{
			if(myState!=states::job)
			{
				checkJob(((Station*)stationedAt)->getCrowNests()->at(i));
			}
		}
		if(myState!=states::job)
		{
			for(int i = 0; i < stationedAt->getAttached()->size();i++)
			{
				Vector2f dir = stationedAt->getAttached()->at(i).first->getPos()-stationedAt->getPos();
				dir = Vector2f((cos(-stationedAt->getRotation()*M_PI/180)*dir.x)-(sin(-stationedAt->getRotation()*M_PI/180)*dir.y),
								(sin(-stationedAt->getRotation()*M_PI/180)*dir.x)+(cos(-stationedAt->getRotation()*M_PI/180)*dir.y));
				if((localPosition.y>0&&dir.y>0)||(localPosition.y<0&&dir.y<0))
				{
					for(int j = 0; j < ((Station*)stationedAt)->getAssignedCrew()->size(); j++)
					{
						if(((Station*)stationedAt)->getAssignedCrew()->at(j)==this)
						{
							((Station*)stationedAt)->getAssignedCrew()->erase(((Station*)stationedAt)->getAssignedCrew()->begin()+j);
							break;
						}
					}
					///add code here and in ship board method to use grapple point code!!!
					((Station*)stationedAt->getAttached()->at(i).first)->getAssignedCrew()->push_back(this);
					Vector2f point = stationedAt->getAttached()->at(i).second.first;
					stationedAt=stationedAt->getAttached()->at(i).first;
					point = Vector2f((cos(stationedAt->getRotation()*M_PI/180)*point.x)-(sin(stationedAt->getRotation()*M_PI/180)*point.y),
								(sin(stationedAt->getRotation()*M_PI/180)*point.x)+(cos(stationedAt->getRotation()*M_PI/180)*point.y));
					point+=stationedAt->getPos();
					grapplePoint(point);
					break;
				}
				
			}
		}
	}
	else
	{
		myState = states::noneState;
	}
}



void Crew::AIControl(float timeElapsed, vector<Entity*> *nightmares)
{
	vector<Entity*> *enemy = new vector<Entity*>();
	if(stationedAt)
	{
		vector<Entity*> *nm = ((Station*)stationedAt)->getAssignedUnits();
		enemy->insert(enemy->end(),nm->begin(),nm->end());
	}
	switch(myState)
	{
		case job:
			doJob(timeElapsed, nightmares);
			break;
		case scared:
			runAroundScared(timeElapsed);
			 break; 
		case attacking:
			Attack(timeElapsed,enemy);
			 break; 
		case noneState:
			DefultState(timeElapsed,enemy,nightmares);
			 break; 
	}
	enemy->clear();
	delete enemy;
}
	

	

void Crew::grapplePoint(Vector2f pos)
{
	Vector2f endPos;
	endPos.x = ((cos((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).x)))-(sin((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).y))));
	endPos.y = ((sin((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).x)))+(cos((-stationedAt->getRotation())*M_PI/180)*(((position - stationedAt->getPos()).y))));
	localPosition=endPos;
	//localPosition.x = stationedAt->getPos().x + ((cos(stationedAt->getRotation()*M_PI/180)*(endPos.x))-(sin(-stationedAt->getRotation()*M_PI/180)*(endPos.y)));
	//localPosition.y = stationedAt->getPos().y + ((sin(stationedAt->getRotation()*M_PI/180)*(endPos.x))+(cos(-stationedAt->getRotation()*M_PI/180)*(endPos.y)));
	myState = grappling;
	endPos.x = ((cos((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).x)))-(sin((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).y))));
	endPos.y = ((sin((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).x)))+(cos((-stationedAt->getRotation())*M_PI/180)*(((pos - stationedAt->getPos()).y))));
	targetPos = endPos;
	if(personnelGrapple)
	{
		delete personnelGrapple;
	}
	personnelGrapple = 0;
}


	void Crew::selectVoice (){
		
				//play a random voice clip
				int randomVoice = rand() % 5 + 1;
				if (randomVoice == 5)
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->pirateSound5,position );
				}
				else if (randomVoice == 4)
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->pirateSound4,position );
				}else if (randomVoice == 3)
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->pirateSound3,position );
				}else if (randomVoice == 2)
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->pirateSound2,position );					 
				}
				else
				{
					SoundManager::getManager()->startSound(SoundManager::getManager()->pirateSound1,position );
				}
	};
void Crew::doJob(float timeElapsed, vector<Entity*> *nightmares )
{
	if(stationedAt)
	{
		if(((Station*)stationedAt)->getAssignedUnits()->size()>0)
		{
			if(myJob)
			{
				setJob(0);
			}
			myState= states::attacking;
		}
		else
		{
			if(myJob)
			{
				if(myJob->getController()==this&&myJob->getStation()==stationedAt)
				{
					myJob->crewControl(timeElapsed,nightmares);
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
void Crew::AIControl(float timeElapsed, vector<Entity*> *nightmares)
{
	if(myState == states::scared)
	{	
		runAroundScared(timeElapsed);
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
	else
	{
		if(stationedAt)
		{
			if(targetPos.length()==0)
			{
				targetPos = Vector2f(-((int)stationedAt->getSize().x/2) + rand() % ((int)stationedAt->getSize().x),
										-((int)stationedAt->getSize().y/2) + rand() % ((int)stationedAt->getSize().y));
			}
	
			Seek(targetPos, timeElapsed);
		}
	}
}*/
