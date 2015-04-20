#pragma once
#ifndef GOLDCHEST_H
#define GOLDCHEST_H
#include <iostream>
#include "SDL.h"
#include "Vector2f.h"
#include <math.h>
#include "TextureManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
class GoldChest
{
public:
	GoldChest(float xPos,float yPos); /// constructor with x and y position as floats
	GoldChest(float xPos,float yPos,float islandWidth, float islandHeigth); /// overloaded constructor with island width and heigth as floats
	~GoldChest(void); /// destructor
	void draw(SDL_Renderer* renderer,float scale,Vector2f offset); /// draw method using the sdl renderer, scale and offset for the camera scroll
	void update(float timeElapsed); /// the update method which uses a float time elapsed
	Vector2f position; /// the position as a vector of two floats
	SDL_Texture* texture; /// the image of the gold chest
	int amount; /// the amount of gold in the chest
	Vector2f virtual getPos(){return position;}; /// the getter method for the position
	void open(); /// the open method when the chest is made in contacted
	void close(); /// the close method after a while when the chest is ope
	int getAmount(); /// the getter method for the gold
	float openTimer; /// the float time the chest is opened
	float rotation; /// the rotation of the chest
	void changeRotation(float); /// the method to change the rotation
};
#endif

