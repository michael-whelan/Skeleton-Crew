#pragma once
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <time.h>
#include "ObjectFactory.h"
#include "PacketStream.h"
#include "Player.h"
#include <thread>
#include <stdlib.h>
using namespace std;
class ObjectManager
{
private:
	///public objectManager object
	static ObjectManager* me;
	/// vector used to store the last position of an object
	Vector2f lastPos;

public:
	Player* player;
	///crew object used to control a selected crew memeber
	Crew* selected;
	///constructor method: creates a new ObjectManager object
	ObjectManager(void);
	///Destructor method: deletes this object at termination/clean up 
	~ObjectManager(void);
	///the initalise method used to create everything at start up
	void init();
	///Get method used to return the player's position
	Vector2f getPlayerPos();
	///Method used to update all the objects in the object manager
	void update(float timeElapsed);
	///Method used to draw all objects on screen
	void draw(SDL_Renderer* renderer,float scale,Vector2f offset);
	///Method that creates multiple station objects 
	void spawnEntity(float, float,float);
	///get method used to return the object manager
	static ObjectManager* getManager();
	///container of unit objects
	vector<Unit*> *units;
	///container of boss objects
	vector<Boss*> *bosses;
	///container of crew objects
	vector<Crew*> *crew;
	///container of station objects
	vector<Station*> *stations;
	///container of goldChest objects 
	vector<GoldChest*> *goldchests;
	///total number of hats bought
	vector<int> *hatsTotal;
	ofstream file;
	int spawnIslandMin, spawnIslandMax, spawnSeaCreatureMin, spawnSeaCreatureMax, spawnPirateMin, spawnPirateMax, spawnNavyMin, spawnNavyMax;
	void setUp();
};
#endif
