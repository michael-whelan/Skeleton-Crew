#pragma once
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include <stdio.h>
#include "SDL.h"
using namespace std;
///
///handles animations that dont have bodies
///updates and draws animations that aren't attached to objects e.g. wake,explosion
///
class AnimationManager
{
private:
	static AnimationManager* me;///a static pointer to the animation manager to stop multiple instances being created
public:
	AnimationManager(void);///constructor for the animation manager
	~AnimationManager(void);///deconstructor for the animation manager
	void update(float timeElapsed);///updates animations and removes them when they finish
	static AnimationManager* getManager();///returns a pointer to the animation manager, creates one if it doesn't already exist
	void draw(SDL_Renderer* renderer);///draws the animations currently in use
};

#endif
