#include "GoldIndicator.h"

GoldIndicator::GoldIndicator(float x,float y):HUDElement(x,y)
{
	//position.x = 1280.0f;
	//position.y = 720.0f;
	texture = TextureManager::getManager()->gold_indicator;
	size = texture->getSize();
	//position.y = 0;
	//position.x -= ((position.x/2) + (size.x/2));



}

GoldIndicator::~GoldIndicator()
{

}

void GoldIndicator::draw(SDL_Renderer* renderer)
{
	posRec->x = position.x-size.x/2;
	posRec->y = position.y-size.y/2;
	posRec->w = size.x;
	posRec->h = size.y;
	SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
	if(ObjectManager::getManager()->selected)
	{
		if(ObjectManager::getManager()->selected->getStation())
		{
			posRec->x = position.x;
			posRec->y = position.y;
			int w = 0; int h = 0;
			message = TTF_RenderText_Solid(font,std::to_string((int)((Station*)ObjectManager::getManager()->selected->getStation())->getGold()).c_str(), textColour);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
			posRec->w = message->w;
			posRec->h = message->h;
			posRec->x-= posRec->w/2;
			posRec->y-= posRec->h/2;
			SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);
		}
	}
	
}