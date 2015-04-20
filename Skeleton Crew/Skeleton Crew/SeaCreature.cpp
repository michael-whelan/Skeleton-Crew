#include "SeaCreature.h"


SeaCreature::SeaCreature(float X,float Y, float mRotation):MobileStation(X,Y)
{
	position.x = X;
	position.y = Y;
	velocity = Vector2f(10,10);
	rotation = mRotation;
	myEntity = entityType::entity|entityType::station|entityType::mobilestation|entityType::seacreatures;
//	state = attacking;
}


SeaCreature::~SeaCreature(void)
{

}

void SeaCreature::drawTop(SDL_Renderer*,float,Vector2f)
{

}


void SeaCreature::update(float timeElapsed)
{
	MobileStation::update(timeElapsed); 
}

void SeaCreature::AIControl(float timeElapsed,vector<Entity*> *nightmares)
{
	float dist = -1;
	float num = -1;
	for(int j = 0; j < nightmares->size(); j++)
	{
		if(((Station*)nightmares->at(j))!=this)
		{
			/*bool kill = false;
			for(int i = 0; i < this->getAssignedUnits()->size();i++)
			{
				if(this->getEntity()!=this->getAssignedUnits()->at(i)->getEntity())
				{
					kill=true;
				}
			}*/
			if(((Station*)nightmares->at(j))->getAssignedCrew()->size()>0/*||kill*/)
			{
				if(num==-1)
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = this->getPos().x;// + ((cos(rotation*M_PI/180)*position.x)-(sin(rotation*M_PI/180)*position.y));
					float myPosY = this->getPos().y;// + ((sin(rotation*M_PI/180)*position.x)+(cos(rotation*M_PI/180)*position.y));
					Vector2f distBetween = Vector2f(ePos.x-myPosX,ePos.y-myPosY);
					num=j;
					dist=distBetween.length();
				}
				else
				{
					Vector2f ePos = ((Station*)nightmares->at(j))->getPos();
					float myPosX = this->getPos().x;// + ((cos(rotation*M_PI/180)*position.x)-(sin(rotation*M_PI/180)*position.y));
					float myPosY = this->getPos().y;// + ((sin(rotation*M_PI/180)*position.x)+(cos(rotation*M_PI/180)*position.y));
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
		aimAtPoint(timeElapsed,((Station*)nightmares->at(num))->getPos(),this->getVelocity());
	}
	action(timeElapsed);
	//switch(state)
	//{
	//case wandering:
	////	wander();
	//	break;
	//case attacking:
	//	attack(timeElapsed,crew);
	//	break; 
	//}

	//Vector2f seekDir = Vector2f(0,0);
	//for(int i = 0; i < crew->size(); i++)
	//{
	//	seekDir.x = crew->at(i)->getPos().x - position.x;
	//	seekDir.y = crew->at(i)->getPos().y - position.y;
	//	if(seekDir.length()<100)
	//	{
	//		//seekDir = seekDir/seekDir.length();
	//		state = attacking; 
	//	}
	//}
}
///makes the sea creatures wander around the world
//void SeaCreature::wander()
//{
//	velocity = Vector2f(10,10);
////	position.x += velocity.x;
////	position.y += velocity.y;
//}
/////makes the sea creaturs attack the player
//
//void SeaCreature::attack(float timeElasped,vector<Entity*>*crew)
//{
//	velocity = Vector2f(10,10);
//	int length = crew->size();
//	if(length==0)
//	{
//		state = states::wandering;
//	}
//	else
//	{
//		int num = 0;
//		Vector2f dist = ((Unit*)crew->at(0))->getPos() - position;
//		for(int i = 0; i < length; i++)
//		{
//			Vector2f temp;
//			temp = ((Unit*)crew->at(i))->getPos() - position;
//			if(temp.length() < dist.length())
//			{
//				dist = temp;
//				num = i;
//			}
//		}
//		seek(((Unit*)crew->at(num))->getPos());
//		if(dist.length()<=((size.x/2)+25))
//		{
//			attackTime=0.3f;
//			coolTime=attackTime+0.3f;
//			if (coolTime<= 0)
//			{
//				attackTime=0.3f;
//				coolTime=attackTime+0.3f;
//			}
//		}
//	}
//}
//
//void SeaCreature::seek(Vector2f targetPos)
//{
//	Vector2f seekDir = Vector2f(0,0);
//	seekDir.x = targetPos.x - position.x;
//	seekDir.y = targetPos.y - position.y;
//	if(seekDir.length()>5)
//	{
//		seekDir = seekDir/seekDir.length();
//		rotation = asinf(velocity.y/velocity.length())*180.0f/M_PI;
//		if(rotation>=360)
//		{
//			rotation-=360;
//		}
//		else if (rotation < 0)
//		{
//			rotation+=360;
//		}
//		if(velocity.x<0)
//		{
//			rotation=90+(90-rotation);
//		}
//		if(rotation>=360)
//		{
//			rotation-=360;
//		}
//		else if (rotation < 0)
//		{
//			rotation+=360;
//		}
//		if(_isnan(rotation))
//		{
//			rotation = 0;
//		}
//	}
//	else
//	{
//		seekDir=Vector2f(0,0);
//		targetPos=Vector2f(0,0);
//	}
//	seekDir*=1 * speed;
//	velocity.x += seekDir.x;
//	velocity.y += seekDir.y;
//}

void SeaCreature::action(float timeElapsed)
{
	Vector2f dir;
	dir.x = cos(this->getRotation()*M_PI/180);
	dir.y = sin(this->getRotation()*M_PI/180);
	this->setAcceleration(Vector2f(dir.x*timeElapsed*Station::ACCELERATION_SPEED,dir.y*timeElapsed*Station::ACCELERATION_SPEED));
}

void SeaCreature::aimAtPoint(float timeElapsed, Vector2f pos, Vector2f vel)
{
	float myPosX = this->getPos().x;//+ ((cos(this->getRotation()*M_PI/180)*position.x)-(sin(this->getRotation()*M_PI/180)*position.y));
	float myPosY = this->getPos().y ;//+ ((sin(this->getRotation()*M_PI/180)*position.x)+(cos(this->getRotation()*M_PI/180)*position.y));
	Vector2f distBetween = Vector2f(pos.x-myPosX,pos.y-myPosY);
	float time = 826.0f/distBetween.length();
	Vector2f fDist = (this->getVelocity()/time)*-1;
	Vector2f fDist2 = (vel/time);
	float rot =  rotation;
	distBetween /= distBetween.length();
	float dir;// = ( ( vel.x) * (pos.y-myStation->getPos().y) - ( vel.y) * (pos.x-myStation->getPos().x));
	//float dir = 0;
	dir = ( ( SDL_cos((this->getRotation())*M_PI/180)*180/M_PI) * (distBetween.y) - ( (SDL_sin((this->getRotation())*M_PI/180)*180/M_PI)) * (distBetween.x));
	if(dir < -5)
	{
		this->changeRotation(-vel.length()/5*timeElapsed);
	}
	else if(dir > 5)
	{
		this->changeRotation(vel.length()/5*timeElapsed);
	}
}

