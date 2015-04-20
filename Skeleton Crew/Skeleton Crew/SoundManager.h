#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include "Vector2f.h"

///This is where all sounds are player through
class SoundManager
{
private:
	static SoundManager* me;///self
public:
	bool sound;
	SoundManager(void);
	~SoundManager(void);
	bool loadSound();
	///for sound effects
	void startSound(Mix_Chunk* soundEffect,Vector2f soundPosition);///Starts playing the passed sounds if the object is in range of the player

	///for music
	void startMusic(Mix_Music* music);///used to  start sounds that will loop
	void stopMusic();///stops something that was set to loop
	void pauseResumeMusic();///called to pause/ resume the currently playing music
	void update(Vector2f camraPosition);

	static SoundManager* getManager();///get self

	Vector2f camraPos;
	

	//music
	Mix_Music* menuMusic;
	Mix_Music* deathFightMusic;
	Mix_Music* backgroundMusic;///the background music for gameplay

	///Sound effects
	Mix_Chunk* shipSound;///splash for when driver takes control
	Mix_Chunk* CannonFireSound;///when a cannon is fired
	Mix_Chunk* GrappleFireSound;///when a cannon is fired
	Mix_Chunk* CannonBallImpact;///when a cannonball hits something
	Mix_Chunk* coin;
	Mix_Chunk* deathCry;//when a unit is killed
	Mix_Chunk* whaleSound;
	Mix_Chunk* turtleSound;
	Mix_Chunk* jellySound;
	Mix_Chunk* hydraSound;
	Mix_Chunk* hydraDadSound;
	Mix_Chunk* scream1;//for scared villagers	
	Mix_Chunk* scream2;//for scared villagers

	///for when you select  a unit
	Mix_Chunk* pirateSound1;
	Mix_Chunk* pirateSound2;
	Mix_Chunk* pirateSound3;
	Mix_Chunk* pirateSound4;
	Mix_Chunk* pirateSound5;


	

};
#endif

