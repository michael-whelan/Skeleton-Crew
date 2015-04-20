#pragma once
#include "Grapple.h"
#include "Cannon.h"
#include "Helm.h"
#include "CrowsNest.h"
#include "EnemyCrew.h"
#include "Crew.h"
#include <vector>
#include <time.h>
#include "Ship.h"
#include "Island.h"
#include "VillageIsland.h"
#include "PirateCove.h"
#include "Boss.h"
#include "DreadRoberto.h"
#include "DavyJones.h"
#include "Death.h"
#include "Alien.h"
#include "Whale.h"
#include "Hydra.h"
#include "Octopus.h"
#include "Squid.h"
#include "Jellyfish.h"
#include "GoldChest.h"
#include "Turtle.h"
#include "Menu.h" 
#include "Serpent.h"
//#include "Player.h"
#include "DeathsBank.h"
#include "FisherBoat.h"
#include "Neptune.h"
class ObjectFactory
{
public:
	ObjectFactory(void);
	~ObjectFactory(void);
	void static spawnNavy(float xPos, float yPos,Station *ships, vector<Unit*> *units,Entity::entityType type);
	void static spawnPirate(float xPos, float yPos,Station *ship, vector<Unit*> *units,Entity::entityType type);
	static Ship* spawnShip(float xPos, float yPos,vector<Station*> *ships,Entity::entityType type, float strengthLevel);
	static int numberOfCannons(float);
	void static spawnIsland(float xPos, float yPos,vector<Station*> *ships, vector<Unit*> *units, vector<GoldChest*> *goldchests);
	void static spawnSeaCreature(float xPos, float yPos,vector<Station*> *ships);
	static Station* SpawnStation(float xPos, float yPos, Entity::entityType,float lvl);
	static Station* seaCreatureSelect(float x, float y);
	static Station* shipSelect(float x, float y,float lvl);
	void static spawnAlien(float xPos, float yPos,Station *ship, vector<Boss*> *bosses);
	void static spawnDavyJones(float xPos, float yPos,Station *ship, vector<Boss*> *bosses, vector<Unit*> *units);
	void static spawnDreadRoberto(float xPos, float yPos,Station *ship, vector<Boss*> *bosses, vector<Unit*> *units);
	void static spawnDeath(float xPos, float yPos,Station *ship, vector<Boss*> *bosses, vector<Unit*> *units);
	void static spawnNeptune(float xPos, float yPos,Station *ship, vector<Boss*> *bosses);
};
