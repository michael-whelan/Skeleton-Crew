#include "ObjectFactory.h"


ObjectFactory::ObjectFactory(void)
{
}


ObjectFactory::~ObjectFactory(void)
{
}

void ObjectFactory::spawnNavy(float xPos, float yPos,Station *ship, vector<Unit*> *units,Entity::entityType type)
{	
	
	for(int i = 0; i < 4; i++)
	{
		EnemyCrew* unit = new EnemyCrew(xPos,yPos,type,ship);
		unit->myState = Unit::states::noneState;
		ship->getAssignedUnits()->push_back(unit);
		units->push_back(unit);
	}
	
}	
int ObjectFactory::numberOfCannons(float f)
{
	if(f == 1)
	{
		return 1;
	}
	else if(f==1.5 ||f==2 )
	{
		return 2;
	}
	else if(f==3 ||f==5 )
	{
		return 3;
	}
}

Ship* ObjectFactory::spawnShip(float xPos, float yPos,vector<Station*> *ships, Entity::entityType type, float strengthLevel)
{
	Texture* mastT = TextureManager::getManager()->blank;
	Texture* helmT=TextureManager::getManager()->blank;
	Texture* crowT=TextureManager::getManager()->blank;
	Texture* shipT=TextureManager::getManager()->blank;
	if(type == Entity::entityType::pirate){
		mastT=TextureManager::getManager()->pirateMast;
		helmT=TextureManager::getManager()->helm;
		crowT=TextureManager::getManager()->pirateCrowNest;
		shipT=TextureManager::getManager()->ship;
	}
	else if(type == Entity::entityType::navy)
	{
		mastT=TextureManager::getManager()->navyMast;
		helmT=TextureManager::getManager()->helm;
		crowT=TextureManager::getManager()->navyCrowNest;
		shipT=TextureManager::getManager()->ship;
	}
	else if(type == Entity::entityType::alien)
	{
		shipT=TextureManager::getManager()->alienShip;
	}
	else if(type == Entity::entityType::neptune)
	{
		shipT=TextureManager::getManager()->neptunesWhale;
	}
	else if(type == Entity::entityType::dreadRoberto)
	{
		mastT=TextureManager::getManager()->dreadRobertsMast;
		helmT=TextureManager::getManager()->dreadRobertsHelm;
		crowT=TextureManager::getManager()->dreadRobertsCrowNest;
		shipT=TextureManager::getManager()->dreadRobertsBoat;
	}
	else if(type == Entity::entityType::daveyJones)
	{
		mastT=TextureManager::getManager()->daveyMast;
		helmT=TextureManager::getManager()->dreadRobertsHelm;
		crowT=TextureManager::getManager()->daveySails;
		shipT=TextureManager::getManager()->dreadRobertsBoat;
	}
	else if(type == Entity::entityType::death)
	{
		mastT=TextureManager::getManager()->deathMast;
		//helmT=TextureManager::getManager()->death;
		crowT=TextureManager::getManager()->deathSails;
		shipT=TextureManager::getManager()->deathShip;
	}
	Ship* enemyShip = new Ship(xPos,yPos,shipT,mastT,strengthLevel);
	int gold = rand()%5000;
	gold += 5000;
	enemyShip->setGold(gold);


	CrowsNest* nest;
	Helm* helm;

	if(type != Entity::entityType::alien)
	{
		nest = new CrowsNest(-150 ,0,32,crowT,enemyShip,nullptr);
		helm = new Helm(-230 ,0,32,helmT,enemyShip,nullptr);

		enemyShip->getCrowNests()->push_back(nest);
	}

	else
	{
		helm = new Helm(0 ,0,32,helmT,enemyShip,nullptr);
	}
	//enemyShip->getCrowNests()->push_back(nest);
	enemyShip->getHelms()->push_back(helm);

	if(type != Entity::entityType::neptune && type != Entity::entityType::alien)
	{
		for(int i = 0; i < numberOfCannons(strengthLevel); i++)
		{
			Vector2f vec = Vector2f(-10 ,70);
			if(i==1)
			{
				vec = Vector2f(-10,-70);
			}
			else if(i ==2)
			{
				vec = Vector2f(190, 0);
			}
			Cannon* cannon = new Cannon(vec.x ,vec.y,32,enemyShip,nullptr);
			enemyShip->getCannons()->push_back(cannon);
		}
	}
	ships->push_back( enemyShip);
	return enemyShip;
}

void ObjectFactory::spawnPirate(float xPos, float yPos,Station *ship, vector<Unit*> *units,Entity::entityType type)
{	
	for(int i = 0; i < 4; i++)
	{
		EnemyCrew* unit = new EnemyCrew(xPos,yPos,type,ship);
		unit->myState = Unit::states::noneState;
		ship->getAssignedUnits()->push_back(unit);
		units->push_back(unit);
	}

}	


void ObjectFactory::spawnIsland(float xPos, float yPos,vector<Station*> *ships, vector<Unit*> *units, vector<GoldChest*> *goldchests)
{
	int islandSpawnNum = rand() % 5;
	int rotation =  rand() % 360;
	switch (islandSpawnNum)
	{
	case 0:
	ships->push_back( new Island(xPos, yPos, 1024*1.5, 1024*1.5, rotation));
	break;
	case 1:
	ships->push_back( new PirateCove(xPos, yPos, 512*3, 512*3, rotation));
	break;
	case 2:
	ships->push_back( new DeathsBank(xPos, yPos, 512*3, 512*3, rotation));
	break;
	default:
	VillageIsland* villageIslandOne = new VillageIsland(xPos, yPos, 1024*2, 1024*2, rotation);
	villageIslandOne->changeRotation(rotation);
		for(int i = 0; i < 5; i++)
		{
			Villager* villager = new Villager(xPos,yPos,villageIslandOne);
			units->push_back(villager);
			villageIslandOne->getAssignedUnits()->push_back(villager);
			GoldChest* goldchestOne = new GoldChest(villageIslandOne->getPos().x,villageIslandOne->getPos().y, 100, 100);
			goldchestOne->changeRotation(rotation);
			goldchests->push_back(goldchestOne);
		}
	ships->push_back(  villageIslandOne); 
	break;
	}
}


void ObjectFactory::spawnSeaCreature(float xPos, float yPos,vector<Station*> *ships)
{
	int seaCreatureSpawnNum = rand() % 7;
	int rotation =  rand() % 360;
	switch (seaCreatureSpawnNum)
	{
	case 0:
	ships->push_back( new Whale(xPos, yPos, rotation));
	break;
	case 1:
	ships->push_back( new Hydra(xPos, yPos, rotation));
	break;
	case 2:
	ships->push_back( new Jellyfish(xPos, yPos, rotation));
	break;
	case 3:
	ships->push_back( new Octopus(xPos, yPos, rotation));
	break;
	case 4:
	ships->push_back( new Squid(xPos, yPos, rotation));
	break;
	case 5:
	ships->push_back( new Serpent(xPos, yPos, rotation));
	break;
	case 6:
	Turtle* myTurtle = new Turtle(xPos ,yPos,rotation);
	Helm* helm = new Helm(0, 10, 32, TextureManager::getManager()->helm,myTurtle);
	myTurtle->getHelms()->push_back(helm);
	ships->push_back(myTurtle);
	break;
	}
}


Station* ObjectFactory::SpawnStation(float xPos, float yPos, Entity::entityType type,float lvl)
{
	if (type &Entity::entityType::island)
	{
		return new Island(xPos, yPos, 1024*1.5, 1024*1.5, 0);
	}
	else if (type &Entity::entityType::shipyard)
	{
		return new PirateCove(xPos, yPos, 1024*1.5, 1024*1.5, 0);
	}
	else if (type &Entity::entityType::bank)
	{
		return new DeathsBank(xPos, yPos, 1024*1.5, 1024*1.5, 0);
	}
	else if (type &Entity::entityType::ship)
	{
		return shipSelect(xPos, yPos,lvl);
	}
	else if (type &Entity::entityType::seacreatures)
	{
		return seaCreatureSelect(xPos,yPos);
		//return new SeaCreature(xPos, yPos);
	}
}

Station* ObjectFactory::shipSelect(float xPos,float yPos,float lvl)
{
	int num = rand() % 2;
	Entity::entityType type;
	if(num ==1)
	{
		type = Entity::entityType::pirate;
	}
	else
	{
		type = Entity::entityType::navy;
	}

	Texture* mastT = TextureManager::getManager()->blank;
	Texture* helmT=TextureManager::getManager()->blank;
	Texture* crowT=TextureManager::getManager()->blank;
	Texture* shipT=TextureManager::getManager()->blank;
	if(type == Entity::entityType::pirate){
		mastT=TextureManager::getManager()->pirateMast;
		helmT=TextureManager::getManager()->helm;
		crowT=TextureManager::getManager()->pirateCrowNest;
		shipT=TextureManager::getManager()->ship;
	}
	else if(type == Entity::entityType::navy)
	{
		mastT=TextureManager::getManager()->navyMast;
		helmT=TextureManager::getManager()->helm;
		crowT=TextureManager::getManager()->navyCrowNest;
		shipT=TextureManager::getManager()->ship;
	}
	Ship* enemyShip = new Ship(xPos,yPos,shipT,mastT,lvl);
	int gold = rand()%5000;
	gold += 5000;
	enemyShip->setGold(gold);

	CrowsNest* nest = new CrowsNest(-150 ,0,32,crowT,enemyShip,nullptr);
	Helm* helm = new Helm(-230 ,0,32,helmT,enemyShip,nullptr);
	
	enemyShip->getCrowNests()->push_back(nest);
	enemyShip->getHelms()->push_back(helm);
	for(int i = 0; i < numberOfCannons(lvl); i++)
	{
		Vector2f vec = Vector2f(-10 ,70);
		if(i==1)
		{
			vec = Vector2f(-10,-70);
		}
		else if(i ==2)
		{
			vec = Vector2f(190, 0);
		}
		Cannon* cannon = new Cannon(vec.x ,vec.y,32,enemyShip,nullptr);
		enemyShip->getCannons()->push_back(cannon);
	}
	return enemyShip;
}

Station* ObjectFactory::seaCreatureSelect(float xPos, float yPos)
{
	int seaCreatureNum = rand() % 7;
	int rotation =  rand() % 360;
	if (seaCreatureNum == 0)
	{
		return new Whale(xPos, yPos, rotation);
	}
	else if (seaCreatureNum == 1)
	{
		return new Hydra(xPos, yPos, rotation);
	}
	else if (seaCreatureNum == 2)
	{
		return new Jellyfish(xPos, yPos, rotation);
	}
	else if (seaCreatureNum == 3)
	{
		return new Octopus(xPos, yPos, rotation);
	}
	else if (seaCreatureNum == 4)
	{
		return new Squid(xPos, yPos, rotation);
	}
	else if (seaCreatureNum == 5)
	{
		return new Serpent(xPos, yPos, rotation);
	}
	else if (seaCreatureNum == 6)
	{
		Turtle* myTurtle = new Turtle(xPos ,yPos,rotation);
		Helm* helm = new Helm(0, 10, 32, TextureManager::getManager()->helm,myTurtle);
		myTurtle->getHelms()->push_back(helm);
		return myTurtle;
	}
}

void ObjectFactory::spawnAlien(float xPos, float yPos,Station *ship, vector<Boss*> *bosses)
{	
	//test
	//ship->setRotation(180.0f);
	
	for(int i = 0; i < 4; i++)
	{
		Alien* alien = new Alien(xPos,yPos,ship);
		alien->myState = Unit::states::noneState;
		ship->getAssignedUnits()->push_back(alien);
		bosses->push_back(alien);
	}
	
}

void ObjectFactory::spawnDavyJones(float xPos, float yPos,Station *ship, vector<Boss*> *bosses, vector<Unit*> *units)
{
	DavyJones *jones = new DavyJones(xPos, yPos, ship);
	bosses->push_back(jones);

	//test
	//ship->setRotation(180.0f);
	//for(int i = 0; i < ship->getCannons()->size(); i++)
	//{
	//	ship->getCannons()->at(i)->rotate(180);
	//}
	
	for(int i = 0; i < 4; i++)
	{
		EnemyCrew* unit = new EnemyCrew(xPos,yPos,Entity::entityType::navy,ship);
		unit->myState = Unit::states::noneState;
		unit->upgradeUnit(Unit::hatUpgrades::petty_officer);
		ship->getAssignedUnits()->push_back(unit);
		units->push_back(unit);
	}
	
}

void ObjectFactory::spawnDreadRoberto(float xPos, float yPos,Station *ship, vector<Boss*> *bosses, vector<Unit*> *units)
{
	DreadRoberto *roberto = new DreadRoberto(xPos, yPos, ship);
	bosses->push_back(roberto);

	//test
	//ship->setRotation(180.0f);
	//for(int i = 0; i < ship->getCannons()->size(); i++)
	//{
	//	ship->getCannons()->at(i)->rotate(180);
	//}
	
	for(int i = 0; i < 4; i++)
	{
		EnemyCrew* unit = new EnemyCrew(xPos,yPos,Entity::entityType::pirate,ship);
		unit->myState = Unit::states::noneState;
		if(i > 1)
		{
			unit->upgradeUnit(Unit::hatUpgrades::petty_officer);
		}
		ship->getAssignedUnits()->push_back(unit);
		
		units->push_back(unit);
	}
	
}

void ObjectFactory::spawnDeath(float xPos, float yPos,Station *ship, vector<Boss*> *bosses, vector<Unit*> *units)
{
	Death *death = new Death(xPos, yPos, ship);
	bosses->push_back(death);

	//test
	//ship->setRotation(180.0f);
	
	for(int i = 0; i < 4; i++)
	{
		EnemyCrew* unit = new EnemyCrew(xPos,yPos,Entity::entityType::ghost,ship);
		unit->myState = Unit::states::noneState;
		int test;
		test = rand()%100;
		if(i == 3)
		{
			if(test>90)
			{
				unit->upgradeUnit(Unit::hatUpgrades::captain);
			}
			else
				unit->upgradeUnit(Unit::hatUpgrades::lieutenant);
		}
		else
			unit->upgradeUnit(Unit::hatUpgrades::petty_officer);

		ship->getAssignedUnits()->push_back(unit);
		units->push_back(unit);
	}
	
}

void ObjectFactory::spawnNeptune(float xPos, float yPos,Station *ship, vector<Boss*> *bosses)
{
	Neptune *neptune = new Neptune(xPos, yPos, ship);
	bosses->push_back(neptune);

	//test
	ship->setRotation(180.0f);
}
