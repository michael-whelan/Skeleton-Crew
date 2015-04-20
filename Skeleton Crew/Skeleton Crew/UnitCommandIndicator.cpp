#include "UnitCommandIndicator.h"

UnitCommandIndicator::UnitCommandIndicator(float x,float y):HUDElement(x,y)
{
	texture = TextureManager::getManager()->unitCommandIcon;
	size = texture->getSize();
	backGroundTexture = TextureManager::getManager()->blankBackground;

	currentState = menuState::closed;

}

UnitCommandIndicator::~UnitCommandIndicator()
{

}

void UnitCommandIndicator::update(float timeElapsed)
{
	commands.clear();
	if(ObjectManager::getManager()->selected)
	{
		if(ObjectManager::getManager()->selected->getStation())
		{
			if(ObjectManager::getManager()->selected->getStation()->getAttached()->size()>0)
			{
				commands.push_back(pair<string, void (UnitCommandIndicator::*)()>("Board",&UnitCommandIndicator::board));
				commands.push_back(pair<string, void (UnitCommandIndicator::*)()>("Loot",&UnitCommandIndicator::loot));
				commands.push_back(pair<string, void (UnitCommandIndicator::*)()>("Detach",&UnitCommandIndicator::detach));
			}
			if(currentState==menuState::open)
			{
				if(KeyManager::getManager()->mousePressed(KeyManager::mouseButtons::left))
				{
					Vector2f mousePos = KeyManager::getManager()->mousePosition();
					if(mousePos.x>position.x - (size.x/2)&&mousePos.x<position.x + (size.x/2))
					{
						for(int i = commands.size()-1; i >= 0; i--)
						{
							if(mousePos.y>position.y - ((1+i)*size.y)- (size.x/2) &&mousePos.y<position.y - ((1+i)*size.y)+ (size.x/2))
							{
								(this->*(commands.at(i).second))();
							}
						}
					}
				}
			}
		}
	}
	
	HUDElement::update(timeElapsed);
}

void UnitCommandIndicator::draw(SDL_Renderer* renderer)
{
	if(currentState != menuState::closed)
	{
		for(int i = commands.size()-1; i >= 0; i--)
		{

			posRec->x = position.x - (size.x/2);
			posRec->y = position.y - (((1+i)*size.y)*openPercent);
			posRec->w = size.x;
			posRec->h = size.y;
			posRec->y -= posRec->h/2;
			SDL_RenderCopyEx(renderer,backGroundTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			message = TTF_RenderText_Solid(font,commands.at(i).first.c_str(), textColour);
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

			message = TTF_RenderText_Solid(fontInner,commands.at(i).first.c_str(), textColourInner);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
			posRec->x+=posRec->w/2;
			posRec->y+=posRec->h/2;
			posRec->w=message->w;
			posRec->h=message->h;
			posRec->x-=posRec->w/2;
			posRec->y-=posRec->h/2;
			SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		}
	}
	HUDElement::draw(renderer);
}



void UnitCommandIndicator::detach()
{
	Crew* selected = ObjectManager::getManager()->selected;
	if(selected)
	{
		if(selected->getStation())
		{
			Station* station = (Station*)selected->getStation();
			station->destroyAllAttachments();
		}
	}
}


void UnitCommandIndicator::loot()
{
	Crew* selected = ObjectManager::getManager()->selected;
	if(selected)
	{
		if(selected->getStation())
		{
			Station* station = (Station*)selected->getStation();
			for(int i = 0; i < station->getAttached()->size();i++)
			{
				station->increaseGold(((Station*)station->getAttached()->at(i).first)->getGold());
				((Station*)station->getAttached()->at(i).first)->setGold(0);
			}
		}
	}
}


void UnitCommandIndicator::board()
{
	Crew* selected = ObjectManager::getManager()->selected;
	if(selected)
	{
		if(selected->getStation())
		{
			Station* station = (Station*)selected->getStation();
			float cosS1=cos(-station->getRotation()*M_PI/180);
			float sinS1=sin(-station->getRotation()*M_PI/180);
			for(int i = 0; i < station->getAttached()->size();i++)
			{
				Vector2f dir = station->getAttached()->at(i).first->getPos()-station->getPos();
				dir = Vector2f((cosS1*dir.x)-(sinS1*dir.y),
								(sinS1*dir.x)+(cosS1*dir.y));
				if((selected->getLocalPos().y>0&&dir.y>0)||(selected->getLocalPos().y<0&&dir.y<0))
				{
					Vector2f point = station->getAttached()->at(i).second.first;
					///add code here and in ship board method to use grapple point code!!!
					Station* station2 = (Station*)station->getAttached()->at(i).first;
					point = Vector2f((cos(station2->getRotation()*M_PI/180)*point.x)-(sin(station2->getRotation()*M_PI/180)*point.y),
								(sin(station2->getRotation()*M_PI/180)*point.x)+(cos(station2->getRotation()*M_PI/180)*point.y));
					point+=station2->getPos();
					for(int j = 0; j < ((Station*)station)->getAssignedCrew()->size();)
					{
						((Unit*)station->getAssignedCrew()->at(j))->setStation(station->getAttached()->at(i).first);
						((Station*)station->getAttached()->at(i).first)->getAssignedCrew()->push_back(station->getAssignedCrew()->at(j));
						((Unit*)station->getAssignedCrew()->at(j))->setJob(0);
						((Unit*)station->getAssignedCrew()->at(j))->grapplePoint(point);
						station->getAssignedCrew()->erase(station->getAssignedCrew()->begin()+j);
					}
					break;
				}	
			}
		}
	}
}