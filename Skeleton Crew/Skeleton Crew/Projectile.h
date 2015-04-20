#pragma once
#include "AnimationManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Vector2f.h"

///This projectile class is the base for cannonball.
///It is an object that is created with an initial velocity that won't change until destruction.

class Station;
class Projectile
{
protected:
	static SDL_Rect* posRec;///THe static rectangle that will be re-used for every projectile
	Vector2f position;///The vector position
	Vector2f size;///vector size
	bool alive;///the check that the projectile is alive, if alive draw/update
	float range;///this is the variable that dictates the distance a projectile can travel, changes depending on level of unit in control
	Vector2f velocity;///The velocity vector
	static const int speed = 826;//the initial speed of a cannon ball, this is based on an 18lb cannonball
	float rotation;
	float damage;///The amount of damage dealt by the projectile, changes depending on level of unit in control
	Texture* texture;///the image used for the projectile
	Vector2f firedFrom;///dictates the position the projectile starts
public:
	Projectile(Vector2f pos,float rotate,Vector2f vel,float dmg,Vector2f from);///Initial position, texture rotation, initial velocity,damage,initial position
	~Projectile(void);
	void update(float timeElapsed);///the update that controls the mopving of position along the velocity
	void draw(SDL_Renderer* renderer,float scale,Vector2f offset);///draws and scales the image of the projectile depending on zoom of player
	bool getAlive();
	Vector2f getPos(){return position;};
	Vector2f getSize(){return size;};
	float getRotation(){return rotation;};
	float getDamage(){return damage;};
	virtual Texture* getTexture(){return texture;};
	void virtual applyAction(Station* stationFrom, Station* stationTo)=0;
};
#include "Station.h"