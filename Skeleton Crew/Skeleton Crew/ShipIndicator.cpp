#include "ShipIndicator.h"

ShipIndicator::ShipIndicator(float x,float y):HUDElement(x,y)
{
	texture = TextureManager::getManager()->ship_indicator1;
	size = texture->getSize();


	backGroundTextureBottom = TextureManager::getManager()->shipMenuBottom;
	backGroundTexture = TextureManager::getManager()->shipMenuBack;

	upArrowTexture = TextureManager::getManager()->upArrow;

	downArrowTexture = TextureManager::getManager()->downArrow;


	scrollLength = 0.0f;
}

ShipIndicator::~ShipIndicator()
{

}

void ShipIndicator::update(float timeElapsed)
{
	ships.clear();
	vector<Station*>::iterator stationIter = ObjectManager::getManager()->stations->begin();
	for(;stationIter!=ObjectManager::getManager()->stations->end();stationIter++)
	{
		if((*stationIter)->getAssignedCrew()->size()>0)
		{
			ships.push_back(pair<Station*, int>((*stationIter), (*stationIter)->getAssignedCrew()->size()));
		}
	}
	if(currentState==open)
	{
		if(KeyManager::getManager()->mouseDown(KeyManager::mouseButtons::left))
		{
			Vector2f mousePos = KeyManager::getManager()->mousePosition();
			if(mousePos.x>=position.x- size.x/2&&mousePos.x<=position.x+ size.x/2)
			{
				int num = ships.size();
				int offset = 0;
				if(ships.size()>=5)
				{
					offset=1;
					if(mousePos.y>=position.y+ (min(1+num,6)*64)&&mousePos.y<=position.y+ ((1+ships.size())*64)+64)
					{
						scrollLength-=64*timeElapsed;
					}
					else if(mousePos.y>=position.y+64&&mousePos.y<=position.y+ (2*64))
					{
						scrollLength+=64*timeElapsed;
					}
					if(scrollLength>0)
					{
						scrollLength=0;
					}
					if(scrollLength<((-64)*(num-4)))
					{
						scrollLength=((-64)*(num-4));
					}
				}
				else
				{
					scrollLength=0;
				}
				if(KeyManager::getManager()->mousePressed(KeyManager::mouseButtons::left))
				{
					if(mousePos.y< position.y + (min(1+num,6)*64) && mousePos.y>=position.y+ ((1+offset)*64))
					{
						int i = ((mousePos.y - position.y-scrollLength)/64)-offset-1;
						ObjectManager::getManager()->selected = (Crew*)ships.at(i).first->getAssignedCrew()->at(rand()%ships.at(i).first->getAssignedCrew()->size());
					}
				}
			}
		}

		//draw down_arrow
	}
	HUDElement::update(timeElapsed);
}

void ShipIndicator::draw(SDL_Renderer* renderer)
{
	if(currentState != menuState::closed)
	{
		int8_t offset = 0;
		posRec->x = position.x- size.x/2;
		int num = ships.size();
		posRec->y = position.y- size.y/2 + ((min(1+num,6)*64)*openPercent);
		posRec->w = backGroundTexture->getSize().x;
		posRec->h = backGroundTexture->getSize().y;
		SDL_RenderCopyEx(renderer,backGroundTextureBottom->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
		posRec->x = position.x- size.x/2;
		posRec->y = position.y;
		posRec->w = backGroundTexture->getSize().x;
		posRec->h = ((min(1+num,6)*64)*openPercent);
		SDL_RenderCopyEx(renderer,backGroundTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
		
		if(ships.size()>=5)
		{
			offset=1;
		}
		for(int i = ships.size()-1; i >= 0; i--)
		{

			posRec->x = position.x - 30;
			posRec->y = min(max(position.y + 32 + (((1+i+offset)*64)*openPercent) + scrollLength, position.y + 32 + (((offset)*64)*openPercent)), position.y + 32 + (((1+4+offset)*64)*openPercent));
			float ratio = ships.at(i).first->getSize().x/ships.at(i).first->getSize().y;
			if(ratio <=1)
			{
				posRec->w = 60*ratio;
				posRec->h = 60;
			}
			else
			{
				ratio = ships.at(i).first->getSize().y/ships.at(i).first->getSize().x;
				posRec->w = 60;
				posRec->h = (60*ratio);
			}
			posRec->y -= posRec->h/2;
			SDL_RenderCopyEx(renderer,ships.at(i).first->getTexture()->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			message = TTF_RenderText_Solid(font,std::to_string(ships.at(i).second).c_str(), textColour);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
			posRec->x+=posRec->w/2;
			posRec->y+=posRec->h/2;
			posRec->w=message->w;
			posRec->h=message->h;
			posRec->x-=posRec->w/2;
			posRec->y-=posRec->h/2;
			SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);
		}
		if(ships.size()>=5)
		{
			posRec->x = position.x- size.x/2;
			posRec->y = position.y- size.y/2 + ((min(1+num,6)*64)*openPercent);
			posRec->w = backGroundTexture->getSize().x;
			posRec->h = backGroundTexture->getSize().y;
			SDL_RenderCopyEx(renderer,backGroundTextureBottom->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
			posRec->x = position.x- size.x/2;
			posRec->y = position.y;
			posRec->w = backGroundTexture->getSize().x;
			posRec->h = min(70*openPercent,64.0f);
			SDL_RenderCopyEx(renderer,backGroundTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			posRec->x = position.x - (downArrowTexture->getSize().x*(50/downArrowTexture->getSize().y)/2);
			posRec->y = position.y + ((min(1+num,6)*64)*openPercent);
			posRec->w = downArrowTexture->getSize().x*(50/downArrowTexture->getSize().y);
			posRec->h = 50;
			SDL_RenderCopyEx(renderer,downArrowTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			posRec->x = position.x- size.x/2;
			posRec->y = position.y+ (64*openPercent);
			posRec->w = backGroundTexture->getSize().x;
			posRec->h = min(70*openPercent,64.0f);
			SDL_RenderCopyEx(renderer,backGroundTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			//draw up_arrow
			posRec->x = position.x  - (upArrowTexture->getSize().x*(50/upArrowTexture->getSize().y)/2);
			posRec->y = position.y + (64*openPercent);
			posRec->w = upArrowTexture->getSize().x*(50/upArrowTexture->getSize().y);
			posRec->h = 50;
			SDL_RenderCopyEx(renderer,upArrowTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			//draw down_arrow
		}
	}
	HUDElement::draw(renderer);

}