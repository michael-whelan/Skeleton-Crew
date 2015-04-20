#include "NotorietyIndicator.h"

NotorietyIndicator::NotorietyIndicator(float x, float y):HUDElement(x,y)
{
	texture = TextureManager::getManager()->notoriety1;
	size = texture->getSize();
}

NotorietyIndicator::~NotorietyIndicator()
{

}

void NotorietyIndicator::draw(SDL_Renderer* renderer)
{
	posRec->x = position.x - size.x/2;
	posRec->y = position.y - size.y/2;
	posRec->w = size.x;
	posRec->h = size.y;
	
	if(ObjectManager::getManager()->player->Notoriety==0)
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->notoriety1->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

	else if(ObjectManager::getManager()->player->Notoriety<25)
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->notoriety2->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

	else if(ObjectManager::getManager()->player->Notoriety<50)
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->notoriety3->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

	else
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->notoriety4->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
}