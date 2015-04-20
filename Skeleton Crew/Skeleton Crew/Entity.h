#pragma once
#ifndef Entity_H
#define Entity_H
#include "AnimationManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include <vector>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, nullptr */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h> //For collision detection
#include <mutex>
using namespace std;
class Grapple;
class CannonBall;
class Entity
{
protected:
	static int entityCount;
	std::mutex mtx;
	static SDL_Rect* posRec; /// pos rec for drawing
	bool alive; /// the entity is alive bool
	float health; /// the health variable 
	Vector2f size; /// the size of the entity
	float rotation; /// its rotation in 360 degrees
	Vector2f position; /// the x and y position
	Vector2f velocity; /// its velocity in direction x and y
	Texture* texture; /// the image
	Texture* textureTop; /// the image if it needs to be drawn at the top
	Texture* textureBottom; /// the image if it needs to be drawn at the bottom
	vector<pair<Entity*,pair<Vector2f,Vector2f>>> *attached; /// when the entity is attatched to another ship/island
	int myEntity;

public:
	Entity(float x,float y); /// constructor with positions x and y as floats
	~Entity(void); /// destuctor

	int getEntity(){return myEntity;};

	void virtual update(float timeElapsed); /// the update method which takes time elapsed as an arguement since last update
	void virtual movement(float timeElapsed); /// the movement method which also takes tie elapsed
	/// the method for AI control which takes the time elasped and a vector of positions called nightmares
	void virtual AIControl(float timeElapsed, vector<Entity*> *nightmares)=0; 
	/// the draw method, the rendered which is needed for drawing the scale and offset are for when you scroll in and out
	void virtual draw(SDL_Renderer* renderer,float scale,Vector2f offset); 
	/// the draw top method, the rendered which is needed for drawing the scale and offset are for when you scroll in and out
	void virtual drawTop(SDL_Renderer* renderer,float scale,Vector2f offset);
	/// the draw bottom method, the rendered which is needed for drawing the scale and offset are for when you scroll in and out
	void virtual drawBottom(SDL_Renderer* renderer,float scale,Vector2f offset);

	Vector2f virtual getSize(){return size;}; /// getter method	for size
	float virtual getHealth(){return health;};/// getter method	for health
	void virtual setHealth(float h){health=h;};/// setter method	for health
	Vector2f virtual getPos(){return position;}; /// getter method	for position
	float virtual getRotation(){return rotation;}; /// getter method for rotation
	void virtual setRotation(float rot){rotation=rot;}; /// setter method for rotation
	virtual Texture* getTexture(){return texture;}; /// getter method for texture
	Vector2f virtual getVelocity(){return velocity;}; /// getter method for velocity
	void virtual setSize(Vector2f Size){size=Size;}; /// setter method for size with a vector of two floats	
	void virtual setPosition(Vector2f Pos){position=Pos;}; /// setter method for position with a vector of two floats	
	void virtual setVelocity(Vector2f Vel){velocity = Vel;}; /// setter method for velocity with a vector of two floats	
	/// method for being attatched to another ship/island
	virtual vector<pair<Entity*,pair<Vector2f,Vector2f>>>* getAttached(){return attached;}; 
	/// method for changing the position with an arguement of a vector2f position
	void virtual changePosition(Vector2f Pos){position=position+Pos;};
	/// method for changing the velocity with an arguement of a vector2f velocity
	void virtual changeVelocity(Vector2f Vel){velocity=velocity+Vel;};
	/// method for changing the rotation with an arguement of a float rotation
	void virtual changeRotation(float Rot){rotation=rotation+Rot;if(rotation>=360){rotation-=360;}else if (rotation < 0){rotation+=360;}}
	/// method to release the entity from its current ship/island
	void virtual destroyAllAttachments();


	enum entityType
	{
		entity =1,
		unit = 2,
		navy = 4,
		pirate = 8,
		villager = 16,
		crew = 32,
		boss = 64,
		station = 128,
		island = 256,
		shipyard = 512,
		bank = 1024,
		mobilestation=2048,
		ship = 4096,
		seacreatures = 8192,
		turtle = 16384,
		death = 32768,
		dreadRoberto = 65536,
		alien = 131027,
		daveyJones = 262144,
		ghost = 524288,
		neptune = 1048576
	};
};
#include "Grapple.h"
#include "CannonBall.h"
#endif
