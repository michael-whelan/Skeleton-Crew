#include "Minimap.h"

Minimap::Minimap(float x,float y):HUDElement(x,y)
{
	texture = TextureManager::getManager()->minimap;
	size = texture->getSize();
}

Minimap::~Minimap()
{

}

void Minimap::drawStations(SDL_Renderer* renderer, vector<Station*> *stations, Vector2f offset)
{
	Vector2f diff;
	for(int i = 0; i < stations->size(); i++)
	{
		/*if(stations->at(i)->getPos().x - offset.x > -1280 &&
			stations->at(i)->getPos().x - offset.x < 2360 && 
			stations->at(i)->getPos().y - offset.y > -720 && 
			stations->at(i)->getPos().y - offset.y < 1440)*/
		if(stations->at(i)->getPos().x - offset.x > -3840 &&
			stations->at(i)->getPos().x - offset.x < 5120 && 
			stations->at(i)->getPos().y - offset.y > -2160 && 
			stations->at(i)->getPos().y - offset.y < 2880)
		{
			diff.x = stations->at(i)->getPos().x - offset.x;
			diff.y = stations->at(i)->getPos().y - offset.y;
			posRec->x = position.x + (diff.x/35.0f);
			posRec->y = position.y + (diff.y/35.0f);
			posRec->w = stations->at(i)->getSize().x/35.0f;
			posRec->h = stations->at(i)->getSize().y/35.0f;
			posRec->x -= posRec->w/2;
			posRec->y -= posRec->h/2;
			SDL_RenderCopyEx(renderer,stations->at(i)->getTexture()->getTexture(),nullptr,posRec,stations->at(i)->getRotation(),nullptr,SDL_FLIP_NONE);
		}
	}
}