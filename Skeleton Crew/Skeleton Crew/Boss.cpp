#include "Boss.h"

Boss::Boss(float x, float y):Unit(x,y)
{
	position.x = x;
	position.y = y;
	hitRadius = 0;
	myEntity = entityType::entity|entityType::unit|entityType::boss;
	specialAttackCool = 10.0f;
}

Boss::Boss(float x, float y,Station *stationed):Unit(x,y, stationed)
{
	position.x = x;
	position.y = y;
	hitRadius = 0;
	myEntity = entityType::entity|entityType::unit|entityType::boss;
	specialAttackCool = 0.0f;
	stationed->getAssignedUnits()->push_back(this);
}


void Boss::specialAttack(float timeElapsed, vector<Station*> *stations,vector<Unit*> *units)
{
	if(specialAttackCool<=0.0f)
	{
		if(mySpecial == specials::roberto)
		{
			teleport();
		}
		else if(mySpecial == specials::jones)
		{
			hitRadius = 1200;
			slowShips(stations);
		}
		else if(mySpecial == specials::alien)
		{
			hitRadius = 600;
			attackCircle(units, timeElapsed);
		}
		else if(mySpecial == specials::neptune)
		{
			charge(stations);
		}
		specialAttackCool += 10.0f;
	}
}

void Boss::teleport()
{
	localPosition.x = rand() %((int)stationedAt->getSize().x) -stationedAt->getSize().x/2;
	localPosition.y = rand() %((int)stationedAt->getSize().y)-stationedAt->getSize().y/2;
}

void Boss::slowShips(vector<Station*> *stations)
{
	for(int i = 0;i<stations->size();i++)
	{
		if(checkDistance(stations->at(i)->getPos(),stations->at(i)->getSize().x,position,hitRadius)&& stations->at(i) != stationedAt)
		{
			stations->at(i)->setVelocity(stations->at(i)->getVelocity()/6);
		}
	}
}

void Boss::attackCircle(vector<Unit*> *units, float timeElapsed)
{
	for(int i = 0;i<units->size();i++)
	{
		if(checkDistance(units->at(i)->getPos(),units->at(i)->getSize().x,position,hitRadius))
		{
			units->at(i)->Hit(Vector2f(position.x-units->at(i)->getPos().x,position.y-units->at(i)->getPos().y),getDamage()*2);
		}
	}
}

void Boss::charge(vector<Station*> *stations)
{
	stationedAt->changeVelocity(Vector2f(stationedAt->getVelocity().x*10, stationedAt->getVelocity().y*10));
}

bool Boss::checkDistance(Vector2f c1, float r1, Vector2f c2, float r2)
{
	return ( ( ( (c1.x - c2.x) * (c1.x - c2.x) ) + ( (c1.y - c2.y) * (c1.y - c2.y) ) ) < (r1 + r2)*(r1 + r2));
}

void Boss::update(float timeElapsed)
{
	Unit::update(timeElapsed);

	specialAttackCool-=timeElapsed;
	if(specialAttackCool <=0.0f)
	{
		specialAttackCool = 0.0f;
	}
}

bool Boss::useSpecialAttack()
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

float Boss::getDamageLevel()
{
	return damageLevel;
}

Boss::~Boss(void)
{
}
