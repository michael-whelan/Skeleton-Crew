#include "Station.h"

const float Station::DRAG_COEFFICIENT_FRONT = 0.0016f;
const float Station::DRAG_COEFFICIENT_SIDE = 0.0032f;
const float Station::DENSITY_OF_WATER = 999.97f;
const float Station::ACCELERATION_SPEED = 100.0f;
const float Station::HULL_HEALTH = 1000.0f;
const float Station::CANNON_SPEED= 3.0f;
const float Station::CROWS_NEST = 1.0f;
const float Station::RUDDER = 10.0f;
const float Station::CANNONBALL_DAMAGE=150.0f;

Station::Station(float X, float Y):Entity(X,Y),mass(50000),gold(0)
{
	lvlMultiplier = 1;
	multiplyHealth=1;
	multiplySpeed=1;
	multiplyReload=1;
	multiplyCrows=1;
	multiplyTurning=1;
	multiplyDmg=1;
	lookOutLocations = new vector<Job*>();
	driverLocations = new vector<Job*>();
	cannons = new vector<Job*>();
	cannonBalls = new vector<Projectile*>();
	assignedCrew = new vector<Entity*>();
	assignedUnits = new vector<Entity*>();
	health = 1000;
	spawnLocations = new vector<Vector2f>();
	spawnCircles = new vector<Vector2f>();
	spawnLocations->push_back(Vector2f(4100,0));
	spawnLocations->push_back(Vector2f(3000,3000));
	spawnLocations->push_back(Vector2f(3000,-3000));
	spawnLocations->push_back(Vector2f(0,4100));
	spawnLocations->push_back(Vector2f(0,-4100));
	float cosR=cos(rotation*M_PI/180);
	float sinR=sin(rotation*M_PI/180);
	for(int i = 0; i < spawnLocations->size();i++)
	{
		float myPosX = position.x + ((cosR*spawnLocations->at(i).x)-(sinR*spawnLocations->at(i).y));
		float myPosY = position.y + ((sinR*spawnLocations->at(i).x)+(cosR*spawnLocations->at(i).y));
		spawnCircles->push_back(Vector2f(myPosX,myPosY));
	}
	/*
	lookOutLocations.push_back(pair<Vector3f,Unit*>(Vector3f(0 ,0,32),nullptr));
	driverLocations.push_back(pair<Vector3f,Unit*>(Vector3f(-209 ,0,32),nullptr));
	cannons.push_back(pair<Cannon*,Unit*>(new Cannon(-10 ,70,32,this),nullptr));
	*/
	//myEntity = entityType::entity|entityType::station;
}



Station::~Station(void)
{
	vector<Job*>::iterator jobIter = lookOutLocations->begin();
	for(;jobIter!=lookOutLocations->end();)
	{
		delete *jobIter;
		jobIter = lookOutLocations->erase(jobIter);
	}
	jobIter = driverLocations->begin();
	for(;jobIter!=driverLocations->end();)
	{
		delete *jobIter;
		jobIter = driverLocations->erase(jobIter);
	}
	jobIter = cannons->begin();
	for(;jobIter!=cannons->end();)
	{
		delete *jobIter;
		jobIter = cannons->erase(jobIter);
	}
	vector<Projectile*>::iterator cannonballIter = cannonBalls->begin();
	for(;cannonballIter!=cannonBalls->end();)
	{
		delete *cannonballIter;
		cannonballIter = cannonBalls->erase(cannonballIter);
	}
	vector<Entity*>::iterator entityIter = assignedCrew->begin();
	for(;entityIter!=assignedCrew->end();)
	{
		((Unit*)(*entityIter))->setStation(0);
		((Unit*)(*entityIter))->setJob(0);
		//delete ((Unit*)(*entityIter))->getStation();
		entityIter = assignedCrew->erase(entityIter);
	}
	entityIter = assignedUnits->begin();
	for(;entityIter!=assignedUnits->end();)
	{
		((Unit*)(*entityIter))->setStation(0);
		delete ((Unit*)(*entityIter))->getStation();
		entityIter = assignedUnits->erase(entityIter);
	}
	delete lookOutLocations;
	delete driverLocations;
	delete cannons;
	delete cannonBalls;
	delete assignedCrew;
	delete assignedUnits;
}

void Station::movement(float timeElapsed)
{
}

void Station::AIControl(float timeElapsed, vector<Entity*> *crew)
{
}

void Station::encounterSounds()
{
}

void Station::draw(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	//drawing the ship
	//m_animation->Draw(renderer,flipType,dynamicBody->GetPosition().x - (texture.getWidth() / 2), -dynamicBody->GetPosition().y - (texture.getWidth() / 2),8);
	Entity::draw(renderer,scale,offset);
	//rotation = rot;

	for(int i = 0; i < lookOutLocations->size(); i++)
	{
		lookOutLocations->at(i)->draw(renderer,offset,scale);
	}
	for(uint32_t i = 0; i < driverLocations->size(); i++)
	{
		driverLocations->at(i)->draw(renderer,offset,scale);
	} 	
	for(int i = 0; i < cannons->size(); i++)
	{
		cannons->at(i)->draw(renderer,offset,scale);
	}
}

void Station::drawTop(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	for(int i = 0; i < cannonBalls->size(); i++)
	{
		cannonBalls->at(i)->draw(renderer,scale,offset);
	}
	for(int i = 0; i < cannons->size(); i++)
	{
		cannons->at(i)->drawTop(renderer,offset,scale);
	}
	for(int i = 0; i < lookOutLocations->size(); i++)
	{
		lookOutLocations->at(i)->drawTop(renderer,offset,scale);
	}
}


void Station::update(float timeElapsed)
{
	float cosR=cos(rotation*M_PI/180);
	float sinR=sin(rotation*M_PI/180);
	float scale =CameraManager::getManager()->getScale();
	for(int i = 0; i < spawnCircles->size();i++)
	{
		float myPosX = position.x + ((cosR*(spawnLocations->at(i).x/scale))-(sinR*(spawnLocations->at(i).y/scale)));
		float myPosY = position.y + ((sinR*(spawnLocations->at(i).x/scale))+(cosR*(spawnLocations->at(i).y/scale)));
		spawnCircles->at(i).x = myPosX;
		spawnCircles->at(i).y = myPosY;
	}
	vector<Projectile*>::iterator projIter = cannonBalls->begin();
	for(;projIter!=cannonBalls->end();)
	{
		(*projIter)->update(timeElapsed);
		if(!(*projIter)->getAlive())
		{
			delete *projIter;
			projIter= cannonBalls->erase(projIter);
		}
		else
		{
			++projIter;
		}
	}
	for(int i = 0; i < cannons->size(); i++)
	{
		cannons->at(i)->update(timeElapsed);
	}
}

void Station::cannonControl(float timeElapsed, Job* cannon, vector<Entity*> *nightmares)
{
	
}


void Station::hitByCannon(Vector2f pointOfImpact, float damage)
{
	health-=damage;
	for(int i = 0; i < assignedUnits->size(); i++)
	{
		Vector2f unitPos = assignedUnits->at(i)->getPos();
		float dist = sqrt((pointOfImpact.x - unitPos.x)*(pointOfImpact.x - unitPos.x)+(pointOfImpact.y - unitPos.y)*(pointOfImpact.y - unitPos.y));
		
		if(dist == 0)
		{
			((Unit*)assignedUnits->at(i))->Hit(pointOfImpact, damage);
		}
		else
		{
			((Unit*)assignedUnits->at(i))->Hit(pointOfImpact, damage * 1/(1+(dist/25)));
		}
	}
	for(int i = 0; i < assignedCrew->size(); i++)
	{
		Vector2f unitPos = assignedCrew->at(i)->getPos();
		float dist = sqrt((pointOfImpact.x - unitPos.x)*(pointOfImpact.x - unitPos.x)+(pointOfImpact.y - unitPos.y)*(pointOfImpact.y - unitPos.y));
		
		if(dist == 0)
		{
			((Unit*)assignedCrew->at(i))->Hit(pointOfImpact, damage);
		}
		else
		{
			((Unit*)assignedCrew->at(i))->Hit(pointOfImpact, damage * 1/(1+(dist/25)));
		}
	}
}