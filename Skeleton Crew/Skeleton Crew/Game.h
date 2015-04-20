#pragma once
#ifndef GAME_H
#define GAME_H
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "AnimationManager.h"
#include "CameraManager.h"
#include "GUIManager.h"
#include "SoundManager.h"
#include <time.h>
class Game
{
private:
public:
	Game(void); /// constructor for game
	~Game(void); /// destructor for game 
	void update(float timeElapsed); /// update method for game which has time elapsed as an arguement
	void draw(SDL_Renderer* renderer); /// the draw method which uses the SDL renderer
	int getGold(){return GUIManager::getManager()->getBank()->bankGold;};
	void loadGame(int i){GUIManager::getManager()->setBank(i);};
	Texture* curText; /// the current background texture
	int textureNum; /// the current texture number
	float textureTime; /// the time the texture has been on screen
};
#endif

