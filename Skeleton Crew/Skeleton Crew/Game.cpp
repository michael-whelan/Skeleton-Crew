#include "Game.h"


Game::Game(void)
{
	textureNum = 0;
	textureTime=0;
	curText = TextureManager::getManager()->background1;
}


Game::~Game(void)
{
	delete curText;
}

void Game::update(float timeElapsed)
{

	textureTime+=timeElapsed;
	if(textureTime>0.2)
	{
		textureNum = (textureNum+1)%3;
		switch (textureNum)
		{
		case 0:
			curText = TextureManager::getManager()->background1;
			break;
		case 1:
			curText = TextureManager::getManager()->background2;
			break;
		case 2:
			curText = TextureManager::getManager()->background3;
			break;
		default:
			break;
		}
		textureTime=0;
	}

	SoundManager::getManager()->startMusic(SoundManager::getManager()->backgroundMusic);
	SoundManager::getManager()->update(CameraManager::getManager()->getOffsetNScale());
	ObjectManager::getManager()->update( timeElapsed);
	AnimationManager::getManager()->update( timeElapsed);
	CollisionManager::getManager()->update( timeElapsed);
	float sightIncrease = 0.1;

	//checking if a unit is selected, and if it is that it is on a station, and if it has a station, check if it is in the crow's nest, and if that is true increase the zoom out distance
	if(ObjectManager::getManager()->selected != nullptr)
	{
		if(ObjectManager::getManager()->selected->getStation() != nullptr)
		{
			for(int i = 0; i < ((Station*)ObjectManager::getManager()->selected->getStation())->getCrowNests()->size(); i++)
			{
				if(((Station*)ObjectManager::getManager()->selected->getStation())->getCrowNests()->at(i)->getController() != nullptr)
				{
					sightIncrease *= 1.5f* ((Station*)ObjectManager::getManager()->selected->getStation())->getCrowsMultiply()*
						((Unit*)((Station*)ObjectManager::getManager()->selected->getStation())->getCrowNests()->at(i)->getController())->getHatStrength();
				}
			}
		}
	}

	CameraManager::getManager()->update( timeElapsed, ObjectManager::getManager()->getPlayerPos(), sightIncrease);
	GUIManager::getManager()->update(timeElapsed);
		
	
}

void Game::draw(SDL_Renderer* renderer)
{
	int posX = (int)CameraManager::getManager()->getOffsetNScale().x;
	int posY = (int)CameraManager::getManager()->getOffsetNScale().y;
	posX/=1020; 
	posY/=1020;
	posX-=4;
	posY-=4;
	SDL_Rect posRec;
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			posRec.x = ((posX+i)*(1020*CameraManager::getManager()->getScale()));
			posRec.y = ((posY+j)*(1020*CameraManager::getManager()->getScale()));
			posRec.w = 1024*CameraManager::getManager()->getScale();
			posRec.h = 1024*CameraManager::getManager()->getScale();
			posRec.x-=CameraManager::getManager()->getOffSet().x;
			posRec.y-=CameraManager::getManager()->getOffSet().y;
			SDL_RenderCopyEx(renderer,curText->getTexture(),nullptr,&posRec,0,nullptr,SDL_FLIP_NONE);
		}
	}
	ObjectManager::getManager()->draw( renderer,CameraManager::getManager()->getScale(),CameraManager::getManager()->getOffSet());
	AnimationManager::getManager()->draw( renderer);
	GUIManager::getManager()->draw( renderer, CameraManager::getManager()->getOffSet());
}