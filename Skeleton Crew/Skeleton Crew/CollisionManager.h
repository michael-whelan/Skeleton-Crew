#pragma once
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "GUIManager.h"
#include "Vector3f.h"
#include <stdio.h>
#include <vector>
#include "ObjectManager.h"
using namespace std;
///
///the collision manager for the game
///handles all collisions between islands and other islands or projectiles
///detects collision in incrementing complexity before handling the outcome
///
class CollisionManager
{
private:
	static CollisionManager* me;///a static pointer to the class to stop multiple instances being created
public:
	CollisionManager(void);///constructor for collision manager
	~CollisionManager(void);///destructor for the collision manager
	void checkCollision();
	void checkAllCollisions();///loops through all ships in the game and checks if they collide
	void update(float timeElapsed);///calls collision check
	static CollisionManager* getManager();///returns the collision manager pointer, if it doesn't exist it creates it
	bool checkDistance(Vector2f c1,float r1, Vector2f c2, float r2);///a basic distance check between objects
	float CheckForCollisionSAT(vector<Vector2f> corners1, vector<Vector2f> corners2);///checks for sat collision between objects to see if its possible they collide
	void collisionResponse(Station* ship1, Station* ship2);///handles the physics involved in the collision of two ships
	bool perPixel(Texture* tex1, Texture* tex2, Vector2f pos1, Vector2f pos2, Vector2f size1, Vector2f size2, float rot1, float rot2);///checks for collision between the pixels in the two textures objects have
	bool collisionStationStaion(Station* ship1, Station* ship2);///decides which checks need to be made between two ships based on the distance from player
	bool collisionStationProjectile(Station* ship, Projectile* ball);///decides which checks need to be made between a ship and a projectile based on distance from the player
};
#endif

