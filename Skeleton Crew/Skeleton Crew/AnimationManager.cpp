#include "AnimationManager.h"


AnimationManager* AnimationManager::me;

AnimationManager* AnimationManager::getManager()
{
	if(!me)
	{
		me=new AnimationManager();
	}
	return me;
}

AnimationManager::AnimationManager(void)
{
}


AnimationManager::~AnimationManager(void)
{
}

void AnimationManager::update(float timeElapsed)
{
}

void AnimationManager::draw(SDL_Renderer* renderer)
{
}