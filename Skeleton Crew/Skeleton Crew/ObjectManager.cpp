#include "ObjectManager.h"



ObjectManager* ObjectManager::me;

ObjectManager* ObjectManager::getManager()
{
	if(!me)
	{
		me=new ObjectManager();
	}
	return me;
}

ObjectManager::ObjectManager(void)
{
	units=new vector<Unit*>(0) ;
	crew=new vector<Crew*>(0) ;
	stations=new vector<Station*>(0);
	bosses = new vector<Boss*>(0);
	goldchests = new vector<GoldChest*>(0);
	hatsTotal = new vector<int>(0);
	for(int i = 0; i< 6;i++)
	{
		hatsTotal->push_back(0);
	}
	//ghostStation = new vector<Station*>(0);
	player = new Player();
}

void ObjectManager::init()
{
}

void ObjectManager::setUp()
{
	spawnIslandMin = 0;
	spawnIslandMax = 3;
	spawnSeaCreatureMin = 3;
	spawnSeaCreatureMax = 6;
	spawnPirateMin = 6;
	spawnPirateMax = 8;
	spawnNavyMin = 8;
	spawnNavyMax = 9;
	Ship* myShip = new Ship(520,180,TextureManager::getManager()->ship,TextureManager::getManager()->pirateMast,1.5);
	stations->push_back(myShip);
	myShip->setGold(25000);
	Crew* myMainMan = new Crew(450,180,myShip,Unit::states::noneState);
	myShip->getAssignedCrew()->push_back(myMainMan);
	crew->push_back(myMainMan);
	selected = myMainMan;
	Crew* myMainMan2 = new Crew(550,180,myShip,Unit::states::noneState);
	myShip->getAssignedCrew()->push_back(myMainMan2);
	crew->push_back(myMainMan2);
	Crew* myMainMan3 = new Crew(550,180,myShip,Unit::states::noneState);
	myShip->getAssignedCrew()->push_back(myMainMan3);
	crew->push_back(myMainMan3);
	Crew* myMainMan4 = new Crew(550,180,myShip,Unit::states::noneState);
	myShip->getAssignedCrew()->push_back(myMainMan4);
	crew->push_back(myMainMan4);
	myShip->getCrowNests()->push_back(new CrowsNest(-150 ,0,32,TextureManager::getManager()->pirateCrowNest,myShip));
	myShip->getHelms()->push_back(new Helm(-230 ,0,32,TextureManager::getManager()->helm,myShip));
	myShip->getCannons()->push_back(new Cannon(-10 ,70,32,myShip));
	myShip->getCannons()->push_back(new Cannon(-10 ,-70,32,myShip));

	//stations->push_back( new DeathsBank(1000, 1000, 512*3, 512*3, 0));
	//stations->push_back( new PirateCove(1000, 1000, 512*3, 512*3, 0));
	//stations->push_back( new PirateCove(2000, 2000, 512*3, 512*3, 0));
	//player
	player = new Player();
	//file.open("creation point.txt");
	if(file.is_open())
	{
		file<<"<<<<<<<<<<<<<game starts here<<<<<<<<<<<<"<<"\n";
		file<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<"\n";
		file<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<"\n";
	}


	file.open("creation point.txt");
	FisherBoat* myBoat = new FisherBoat(500 ,500,0);
	Helm* helm = new Helm(0, 10, 32, nullptr,myBoat);
	myBoat->getHelms()->push_back(helm);
	stations->push_back(myBoat);


}

ObjectManager::~ObjectManager(void)
{
	if(crew)
	{
	vector<Crew*>::iterator crewIter = crew->begin();
	for(;crewIter!=crew->end();)
	{
		if(*crewIter==selected)
		{
			selected=0;
		}
		delete *crewIter;
		crewIter = crew->erase(crewIter);
	}
	delete crew;
	}
	if(units)
	{
	vector<Unit*>::iterator unitIter = units->begin();
	for(;unitIter!=units->end(); )
	{
		delete *unitIter;
		unitIter = units->erase(unitIter);
	}
	delete units;
	}
	if(stations)
	{
	vector<Station*>::iterator stationIter = stations->begin();
	for(;stationIter!=stations->end(); )
	{
		delete *stationIter;
		stationIter = stations->erase(stationIter);
	}
	delete stations;
	}
	if(goldchests)
	{
	vector<GoldChest*>::iterator chestIter = goldchests->begin();
	for(;chestIter!=goldchests->end();)
	{
		delete *chestIter;
		chestIter = goldchests->erase(chestIter);
	}
	delete goldchests;
	}
	if(bosses)
	{
	vector<Boss*>::iterator bossIter = bosses->begin();
	for(;bossIter!=bosses->end();)
	{
		delete *bossIter;
		bossIter = bosses->erase(bossIter);
	}
	delete bosses;
	}

	me =0;

	if(file.is_open())
	{
		file<<"\n\n\n\n\n\n\n\n\n\n";
		file.close();
	}

	delete player;
	player=0;
}

Vector2f ObjectManager::getPlayerPos()
{
	if(selected)
	{
		lastPos = selected->getPos();
	}
	return lastPos;
}

void ObjectManager::spawnEntity(float xPos, float yPos, float radius)
{	
	int spawnNumber, randSceenWidth, randSceenHeigth;
	radius = radius*0.5;
	randSceenWidth = xPos + (rand() % (int)(radius*2)) - radius;
	randSceenHeigth = yPos + (rand() % (int)(radius*2)) - radius;
	spawnNumber = rand() % 10;

	if(file.is_open())
	{
		file<<"created: "<<spawnNumber<<"\n";
		file<<"x: "<<randSceenWidth<<",\t y: "<<randSceenHeigth<<"\n";
		file<<"create criteria:"<<"\n";
		file<<"x: "<<xPos<<",\t y: "<<yPos<<",\t radius: "<<radius<<"\n";
	}
	if (spawnNumber >= spawnIslandMin &&spawnNumber <= spawnIslandMax)
	{
		ObjectFactory::spawnIsland(randSceenWidth, randSceenHeigth,stations,units,goldchests);
	}
	else if (spawnNumber > spawnSeaCreatureMin && spawnNumber <= spawnSeaCreatureMax)
	{
		ObjectFactory::spawnSeaCreature(randSceenWidth, randSceenHeigth,stations);
	}
	else if (spawnNumber > spawnPirateMin &&  spawnNumber <= spawnPirateMax) 
	{
		ObjectFactory::spawnPirate(randSceenWidth, randSceenHeigth,ObjectFactory::spawnShip(randSceenWidth, randSceenHeigth,stations,Entity::entityType::pirate,1),units,Entity::entityType::pirate);
	}
	else if (spawnNumber > spawnNavyMin &&  spawnNumber <= spawnNavyMax) 
	{
		ObjectFactory::spawnNavy(randSceenWidth, randSceenHeigth,ObjectFactory::spawnShip(randSceenWidth, randSceenHeigth,stations,Entity::entityType::navy,1),units,Entity::entityType::navy);///magic number is the level of the ship
	}
	if(file.is_open())
	{
		file<<"created station: "<<stations->size()-1<<"\n";
		file<<"x: "<<stations->at(stations->size()-1)->getPos().x<<",\t y: "<<stations->at(stations->size()-1)->getPos().y<<"\n\n\n";
	}

	//bosses
	if(player->gold > 30000 && bosses->size()<=0 && spawnNumber > 9 &&  spawnNumber <= 10)
	{
		ObjectFactory::spawnDreadRoberto(randSceenWidth, randSceenHeigth, ObjectFactory::spawnShip(selected->getPos().x + 450, selected->getPos().y, stations, Entity::entityType::dreadRoberto, 2),bosses, units);
	}
	else if(player->gold > 60000 && bosses->size()<=0 && spawnNumber > 10 &&  spawnNumber <= 11)
	{
		ObjectFactory::spawnNeptune(randSceenWidth, randSceenHeigth, ObjectFactory::spawnShip(selected->getPos().x + 450, selected->getPos().y, stations, Entity::entityType::neptune, 2),bosses);
	}
	else if(player->gold > 160000 && bosses->size()<=0 && spawnNumber > 11 &&  spawnNumber <= 12)
	{
		ObjectFactory::spawnDavyJones(randSceenWidth, randSceenHeigth, ObjectFactory::spawnShip(selected->getPos().x + 450, selected->getPos().y, stations, Entity::entityType::daveyJones, 3),bosses, units);
	}
	else if(player->gold > 400000 && bosses->size()<=0 && spawnNumber > 12 &&  spawnNumber <= 13)
	{
		ObjectFactory::spawnAlien(randSceenWidth, randSceenHeigth, ObjectFactory::spawnShip(selected->getPos().x + 450, selected->getPos().y, stations, Entity::entityType::alien, 3),bosses);
	}
	else if(player->gold > 700000 && bosses->size()<=0 && spawnNumber > 13 &&  spawnNumber <= 14)
	{
		ObjectFactory::spawnDeath(randSceenWidth, randSceenHeigth, ObjectFactory::spawnShip(selected->getPos().x + 450, selected->getPos().y, stations, Entity::entityType::death, 5),bosses, units);
	}

	else if(player->gold == 5000 && bosses->size()<=0)
	{
		//ObjectFactory::spawnAlien(stations->at(0)->getPos().x, stations->at(0)->getPos().y, stations->at(0),bosses);
		//ObjectFactory::spawnNeptune(stations->at(0)->getPos().x, stations->at(0)->getPos().y, stations->at(0),bosses);
		//ObjectFactory::spawnDreadRoberto(stations->at(0)->getPos().x, stations->at(0)->getPos().y, stations->at(0),bosses, units);
		//ObjectFactory::spawnDavyJones(stations->at(0)->getPos().x, stations->at(0)->getPos().y, stations->at(0),bosses, units);
		//ObjectFactory::spawnDeath(stations->at(0)->getPos().x, stations->at(0)->getPos().y, stations->at(0),bosses, units);
		//ObjectFactory::spawnDeath(stations->at(0)->getPos().x + 600, stations->at(0)->getPos().y, ObjectFactory::spawnShip(stations->at(0)->getPos().x + 600, stations->at(0)->getPos().y, stations, Entity::entityType::death, 5),bosses, units);
	}
	
}

void ObjectManager::update(float timeElapsed)
{	
	if(selected)
	{
		selected->movement(timeElapsed);
	}
	if(KeyManager::getManager()->mousePressed(KeyManager::getManager()->mouseButtons::left))
	{
		for(int i = 0; i < crew->size(); i++)
		{
			if(	KeyManager::getManager()->mousePosition().x + CameraManager::getManager()->getOffSet().x > (crew->at(i)->getPos().x - 16) * CameraManager::getManager()->getScale() 
				&&	KeyManager::getManager()->mousePosition().x + CameraManager::getManager()->getOffSet().x < (crew->at(i)->getPos().x + 16) * CameraManager::getManager()->getScale() 
				&&	KeyManager::getManager()->mousePosition().y + CameraManager::getManager()->getOffSet().y > (crew->at(i)->getPos().y - 16) * CameraManager::getManager()->getScale()  
				&&	KeyManager::getManager()->mousePosition().y + CameraManager::getManager()->getOffSet().y < (crew->at(i)->getPos().y + 16) * CameraManager::getManager()->getScale())
			{
				selected=crew->at(i);
				selected->selectVoice();
			}
		}
	}
	vector<Crew*>::iterator crewIter = crew->begin();
	for(;crewIter!=crew->end();)
	{
		if(*crewIter!=selected)
		{
			(*crewIter)->AIControl(timeElapsed,(vector<Entity*>*)stations);
		}
		else 
		{ // if the crew collides with a gold chest
			for(int j = 0; j < goldchests->size(); j++)
			{
				if ((*crewIter)->getPos().x > goldchests->at(j)->getPos().x - 32 && (*crewIter)->getPos().x < goldchests->at(j)->getPos().x + 32
				&&	(*crewIter)->getPos().y > goldchests->at(j)->getPos().y - 32 && (*crewIter)->getPos().y < goldchests->at(j)->getPos().y + 32)
				{
					goldchests->at(j)->open();
					if((*crewIter)->getStation())
					{
						((Station*)(*crewIter)->getStation())->increaseGold(goldchests->at(j)->getAmount());
					}
					goldchests->at(j)->amount = 0;
				}
			}
		}
		if((*crewIter)->getState()==Unit::grappling)
		{
			(*crewIter)->Seek((*crewIter)->getTargetPos(),timeElapsed, 10);
			if((*crewIter)->getTargetPos().length()==0)
			{
				(*crewIter)->setState(Unit::noneState);
			}
		}
		(*crewIter)->update(timeElapsed);
		if((*crewIter)->getAttackTime()>0)
		{
			if((*crewIter)->getStation())
			{
				for(int j = 0; j < ((Station*)((*crewIter)->getStation()))->getAssignedUnits()->size(); j++)
				{
					Vector2f attackerPos = (*crewIter)->getPos();
					Vector2f attackeePos = ((Station*)((*crewIter)->getStation()))->getAssignedUnits()->at(j)->getPos();
					if( ((attackerPos.x-attackeePos.x)*(attackerPos.x-attackeePos.x)) + 
						((attackerPos.y-attackeePos.y)*(attackerPos.y-attackeePos.y)) < 
						((((*crewIter)->getSize().x/2)+25)*(((*crewIter)->getSize().x/2)+25)) )
					{
						((Unit*)((Station*)((*crewIter)->getStation()))->getAssignedUnits()->at(j))->Hit(attackerPos,((Unit*)(*crewIter))->getDamage()/0.3f*timeElapsed);
					}
				}
			}
		}
		/*
		if((*crewIter)->getHealth() <=0)
		{
			if(*crewIter==selected)
			{
				selected=0;
			}
			for(int i = 0; i < bosses->size(); i++)
			{
				if(bosses->at(i)->mySpecial == Boss::specials::death &&
					sqrt(((bosses->at(i)->getPos().x - (*crewIter)->getPos().x) * (bosses->at(i)->getPos().x - (*crewIter)->getPos().x)) + ((bosses->at(i)->getPos().y - (*crewIter)->getPos().y) * (bosses->at(i)->getPos().y - (*crewIter)->getPos().y)))<1280 && 
					(*crewIter)->AddNewCrew())
				{
					EnemyCrew* u =new EnemyCrew((*crewIter)->getPos().x,(*crewIter)->getPos().y,Entity::ghost,((Station*)(*crewIter)->getStation()));
					u->upgradeUnit((*crewIter)->getHat());
					if((*crewIter)->getStation())
					{
						((Station*)(*crewIter)->getStation())->getAssignedCrew()->push_back(u);
					}
					units->push_back(u);
					player->Notoriety -= 5;
				}
			}

			delete *crewIter;
			crewIter = crew->erase(crewIter);
			player->Notoriety -= 5;

		}
		else*/
		{
			++crewIter;
		}
	
		
		
	}
	/*if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_RCTRL))
	{
		for(int i = 0; i < stations->at(0)->spawnCircles->size();i++)
		{
			if(file.is_open())
			{
				file<<"station: "<<i<<"\n";
				file<<"x: "<<stations->at(0)->getPos().x<<",\t y: "<<stations->at(0)->getPos().y<<"\n";
				file<<"circle: "<<i<<"\n";
				file<<"x: "<<stations->at(0)->spawnCircles->at(i).x<<",\t y: "<<stations->at(0)->spawnCircles->at(i).y<<"\n";
			}
			spawnEntity(stations->at(0)->spawnCircles->at(i).x,stations->at(0)->spawnCircles->at(i).y,4000);
		}
	}*/
	for(int i = 0;i < stations->size(); i++)
	{
		Station* station = stations->at(i);
		station->update(timeElapsed);
		if(station->getEntity() &Entity::entityType::seacreatures)
		{		
			station->AIControl(timeElapsed,(vector<Entity*>*)stations );


			//creatures make a sound based on what they are
			station->encounterSounds();
		}
		if(station->getAssignedCrew()->size() > 0)
		{
			vector<bool> spawnAt = vector<bool>();
			for(int sp = 0; sp < station->spawnCircles->size();sp++)
			{
				spawnAt.push_back(true);
			}
			vector<Station*>::iterator stationIterIn = stations->begin();
			for(;stationIterIn!=stations->end(); ++stationIterIn)
			{
				for(int k = 0; k <station->spawnCircles->size();k++)
				{
					Vector2f point = station->spawnCircles->at(k);
					float xSQR = point.x-(*stationIterIn)->getPos().x;
					float ySQR = point.y-(*stationIterIn)->getPos().y;
					float zSQR = 3500+(*stationIterIn)->getSize().length();
					if((xSQR*xSQR)+(ySQR*ySQR)<zSQR*zSQR)
					{
						spawnAt.at(k)=false;
					}
				}
			}
			for(int sp = 0; sp < station->spawnCircles->size();sp++)
			{
				if(spawnAt.at(sp))
				{
					if(file.is_open())
					{
						file<<"station: "<<i<<"\n";
						file<<"x: "<<station->getPos().x<<", y: "<<station->getPos().y<<"\n";
						file<<"circle: "<<sp<<"\n";
						file<<"x: "<<station->spawnCircles->at(sp).x<<", y: "<<station->spawnCircles->at(sp).y<<"\n";
					}
					spawnEntity(station->spawnCircles->at(sp).x,station->spawnCircles->at(sp).y,4000);
				}
			}
		}




		if(station->getHealth() <=0)
		{
			delete station;
			stations->erase(stations->begin()+i);
			player->Notoriety += 30;
		}
	}
	
	vector<GoldChest*>::iterator chestIter = goldchests->begin();
	for(;chestIter!=goldchests->end();)
	{
		(*chestIter)->update(timeElapsed);
		if ((*chestIter)->openTimer > 5)
		{
			delete *chestIter;
			chestIter = goldchests->erase(chestIter);
		}
		else
		{
			++chestIter;
		}
	}
	for(int i = 0;i < units->size();i++)
	{
		units->at(i)->AIControl(timeElapsed,(vector<Entity*>*)stations);
		if(units->at(i)->getState()==Unit::grappling)
		{
			units->at(i)->Seek(units->at(i)->getTargetPos(),timeElapsed, 10);
			if(units->at(i)->getTargetPos().length()==0)
			{
				units->at(i)->setState(Unit::noneState);
			}
		}
		units->at(i)->update(timeElapsed);

		//check if enemies give up (if they do, they are scared)
		if(player->Notoriety>0)
		{
			if(selected)
			{
				if(sqrt(((selected->getPos().x - units->at(i)->getPos().x) * (selected->getPos().x - units->at(i)->getPos().x)) + ((selected->getPos().y - units->at(i)->getPos().y) * (selected->getPos().y - units->at(i)->getPos().y)))<640)
				{
					if(rand() % 20000 < player->Notoriety)
					{
						//units->at(i)->Hit(units->at(i)->getPos(), units->at(i)->getHealth());
						units->at(i)->setState(Unit::states::scared);
					}
				}
			}
		}

		if(units->at(i)->getAttackTime()>0)
		{
			if(units->at(i)->getStation())
			{
				for(int j = 0; j < ((Station*)(units->at(i)->getStation()))->getAssignedCrew()->size(); j++)
				{
					Vector2f attackerPos = units->at(i)->getPos();
					Vector2f attackeePos = ((Station*)(units->at(i)->getStation()))->getAssignedCrew()->at(j)->getPos();
					if( ((attackerPos.x-attackeePos.x)*(attackerPos.x-attackeePos.x)) + 
						((attackerPos.y-attackeePos.y)*(attackerPos.y-attackeePos.y)) < 
						(((units->at(i)->getSize().x/2)+25)*((units->at(i)->getSize().x/2)+25)) )
					{
						((Unit*)((Station*)(units->at(i)->getStation()))->getAssignedCrew()->at(j))->Hit(attackerPos,((Unit*)units->at(i))->getDamage()/0.3f*timeElapsed);
					}
				}
				for(int j = 0; j < ((Station*)(units->at(i)->getStation()))->getAssignedUnits()->size();j++)
				{
					if(units->at(i)->getEntity()!=((Station*)(units->at(i)->getStation()))->getAssignedUnits()->at(j)->getEntity())
					{
						Vector2f attackerPos = units->at(i)->getPos();
						Vector2f attackeePos = ((Station*)(units->at(i)->getStation()))->getAssignedUnits()->at(j)->getPos();
						if( ((attackerPos.x-attackeePos.x)*(attackerPos.x-attackeePos.x)) + 
							((attackerPos.y-attackeePos.y)*(attackerPos.y-attackeePos.y)) < 
							(((units->at(i)->getSize().x/2)+25)*((units->at(i)->getSize().x/2)+25)) )
						{
							((Unit*)((Station*)(units->at(i)->getStation()))->getAssignedUnits()->at(j))->Hit(attackerPos,((Unit*)units->at(i))->getDamage()/0.3f*timeElapsed);
						}
					}
				}
			}
		}
		if(units->at(i)->getHealth()<=0)
		{
			if(units->at(i)->AddNewCrew())
			{
				Crew* c =new Crew(units->at(i)->getPos().x,units->at(i)->getPos().y,((Station*)units->at(i)->getStation()));
				c->upgradeUnit(units->at(i)->getHat());
				if(units->at(i)->getStation())
				{
					((Station*)units->at(i)->getStation())->getAssignedCrew()->push_back(c);
				}
				crew->push_back(c);
				player->Notoriety += 5;
			}

			delete units->at(i);
			units->at(i)=0;
			units->erase(units->begin()+i);
			player->Notoriety += 5;
		}
	}
	vector<Boss*>::iterator bossIter = bosses->begin();
	for(;bossIter!=bosses->end();)
	{
		(*bossIter)->AIControl(timeElapsed,(vector<Entity*>*)stations);
		//boss special attack stuff
		if((*bossIter)->useSpecialAttack())
		{
			(*bossIter)->specialAttack(timeElapsed, stations, (vector<Unit*>*)crew);
			(*bossIter)->specialAttack(timeElapsed, stations, units);
		}
		(*bossIter)->update(timeElapsed);
		//attacking
		if((*bossIter)->getAttackTime()>0)
		{
			if((*bossIter)->getStation())
			{
				for(int j = 0; j < ((Station*)((*bossIter)->getStation()))->getAssignedCrew()->size(); j++)
				{
					Vector2f attackerPos = (*bossIter)->getPos();
					Vector2f attackeePos = ((Station*)((*bossIter)->getStation()))->getAssignedCrew()->at(j)->getPos();
					if( ((attackerPos.x-attackeePos.x)*(attackerPos.x-attackeePos.x)) + 
						((attackerPos.y-attackeePos.y)*(attackerPos.y-attackeePos.y)) < 
						((((*bossIter)->getSize().x/2)+25)*(((*bossIter)->getSize().x/2)+25)) )
					{
						((Unit*)((Station*)((*bossIter)->getStation()))->getAssignedCrew()->at(j))->Hit(attackerPos,((Unit*)(*bossIter))->getDamage()/0.3f*timeElapsed*(*bossIter)->getDamageLevel());
					}
				}
				for(int j = 0; j < ((Station*)((*bossIter)->getStation()))->getAssignedUnits()->size();j++)
				{
					if((*bossIter)->getEntity()!=((Station*)((*bossIter)->getStation()))->getAssignedUnits()->at(j)->getEntity())
					{
						Vector2f attackerPos = (*bossIter)->getPos();
						Vector2f attackeePos = ((Station*)((*bossIter)->getStation()))->getAssignedUnits()->at(j)->getPos();
						if( ((attackerPos.x-attackeePos.x)*(attackerPos.x-attackeePos.x)) + 
							((attackerPos.y-attackeePos.y)*(attackerPos.y-attackeePos.y)) < 
							((((*bossIter)->getSize().x/2)+25)*(((*bossIter)->getSize().x/2)+25)) )
						{
							((Unit*)((Station*)((*bossIter)->getStation()))->getAssignedUnits()->at(j))->Hit(attackerPos,((Unit*)(*bossIter))->getDamage()/0.3f*timeElapsed*(*bossIter)->getDamageLevel());
						}
					}

				}
			}
		}

		if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_LCTRL))
		{
			(*bossIter)->specialAttack(timeElapsed,stations,units);
		}
		if((*bossIter)->getHealth() < 0)
		{
			delete *bossIter;
			bossIter = bosses->erase(bossIter);
		}
		else
		{
			++bossIter;
		}
	}
	if(player->Notoriety>0)
	{
		player->update(timeElapsed);
	}

}

void ObjectManager::draw(SDL_Renderer* renderer,float scale,Vector2f offset)
{
	for(int i = 0; i < stations->size(); i++)
	{
		stations->at(i)->drawBottom(renderer,scale,offset);
	}
	;
	for(int i = 0; i < stations->size(); i++)
	{
		stations->at(i)->draw(renderer,scale,offset);
	}
	for(int i = 0; i< bosses->size(); i++)
	{
		bosses->at(i)->draw(renderer,scale,offset);
	}
	for(int i = 0; i < units->size(); i++)
	{
		units->at(i)->draw(renderer,scale,offset);
	}
	for(int i = 0; i < crew->size(); i++)
	{
		crew->at(i)->draw(renderer,scale,offset);
	}
	for(int i = 0; i < goldchests->size(); i++)
	{
		goldchests->at(i)->draw(renderer,scale,offset);
	}


	for(int i = 0; i < stations->size(); i++)
	{
		stations->at(i)->drawTop(renderer,scale,offset);
	}

	if(selected)
	{
		SDL_Rect posRec;
		SDL_Color black;
		black.r = 0;
		black.g = 0;
		black.b = 0;
		black.a = 255;
		int w = 0;
		int h = 0;
		std::string nameStr;
		nameStr = selected->getHatName()+' '+selected->getName();
		SDL_Surface* message = TTF_RenderText_Solid(TextureManager::getManager()->fontText,nameStr.c_str(), black);
		SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		std::string healthS;
		healthS = std::to_string((int)selected->getHealth())+'/'+ std::to_string((int)selected->getMaxHealth());
		SDL_Surface* message2 = TTF_RenderText_Solid(TextureManager::getManager()->fontText,healthS.c_str(), black);
		SDL_Texture* text2 = SDL_CreateTextureFromSurface(renderer, message2);
		SDL_QueryTexture(text2, nullptr, nullptr, &w, &h);
		int width = max(message->w,message2->w);
		int height = max(message->h,message2->h);

		posRec.x = ((selected->getPos().x)*scale)-offset.x;
		posRec.y = ((selected->getPos().y)*scale)-64-offset.y;
		posRec.w = height*3;
		posRec.h = width*2;
		posRec.x-= height*3/2;
		posRec.y-= width;
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->blankBackground->getTexture(),nullptr,&posRec,90,nullptr,SDL_RendererFlip::SDL_FLIP_NONE);
	

		posRec.x = ((selected->getPos().x)*scale)-offset.x;
		posRec.y = ((selected->getPos().y)*scale)-64-offset.y;
		posRec.w = message->w;
		posRec.h = message->h;
		posRec.x-= posRec.w/2;
		posRec.y-= posRec.h;
		SDL_RenderCopyEx(renderer, text, nullptr, &posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);

		posRec.x = ((selected->getPos().x)*scale)-offset.x;
		posRec.y = ((selected->getPos().y)*scale)-64-offset.y;
		posRec.w = message2->w;
		posRec.h = message2->h;
		posRec.x-= posRec.w/2;
		SDL_RenderCopyEx(renderer, text2, nullptr, &posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message2);
		SDL_DestroyTexture(text2);
	}
	
}

