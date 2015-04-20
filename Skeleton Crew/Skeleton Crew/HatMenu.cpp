#include "HatMenu.h"

HatMenu::HatMenu(float x,float y):HUDElement(x,y)
{
	texture = TextureManager::getManager()->blankBackground;
	size = texture->getSize()/2;

	hats.push_back(pair<Texture*, int>(TextureManager::getManager()->pirateRank1, 0));
	hats.push_back(pair<Texture*, int>(TextureManager::getManager()->pirateRank2, 0));
	hats.push_back(pair<Texture*, int>(TextureManager::getManager()->pirateRank3, 0));
	hats.push_back(pair<Texture*, int>(TextureManager::getManager()->pirateRank4, 0));
	hats.push_back(pair<Texture*, int>(TextureManager::getManager()->pirateRank5, 0));
	hats.push_back(pair<Texture*, int>(TextureManager::getManager()->pirateRank6, 0));

	currentState = menuState::closed;
}

HatMenu::~HatMenu()
{

}

void HatMenu::update(float timeElapsed)
{
	HUDElement::update(timeElapsed);
	if(currentState == menuState::open)
	{
		if(KeyManager::getManager()->mousePressed(KeyManager::mouseButtons::left))
		{
			Vector2f mousePos = KeyManager::getManager()->mousePosition();
			for(int i = 0; i< hats.size(); i++)
			{
				if(hats.at(i).second >0)
				{
					if(sqrt((position.x +(((1+i)*size.x)*openPercent) - mousePos.x)*(position.x +(((1+i)*size.x)*openPercent)- mousePos.x) + 
						(position.y- mousePos.y)*(position.y- mousePos.y))<(size.x/2))
					{
						if(ObjectManager::getManager()->selected)
						{
							int num = getIndex(ObjectManager::getManager()->selected->upgradeUnit(getHat(i)));
							if(num>=0)
							{
								hats.at(num).second++;
							}
							hats.at(i).second--;
						}
					}
				}
			}
		}
	}
}

int HatMenu::getIndex(Unit::hatUpgrades i)
{
	if(i == Unit::hatUpgrades::seaman)
	{
		return 0;
	}
	else if(i ==  Unit::hatUpgrades::petty_officer)
	{
		return 1;
	}
	else if(i ==  Unit::hatUpgrades::chief_petty_officer)
	{
		return 2;
	}
	else if(i ==  Unit::hatUpgrades::lieutenant)
	{
		return 3;
	}
	else if(i ==  Unit::hatUpgrades::captain)
	{
		return 4;
	}
	else if(i ==  Unit::hatUpgrades::admiral)
	{
		return 5;
	}
	return -1;
}

Unit::hatUpgrades HatMenu::getHat(int i)
{
	if(i ==0)
	{
		return Unit::hatUpgrades::seaman;
	}
	else if(i == 1)
	{
		return Unit::hatUpgrades::petty_officer;
	}
	else if(i == 2)
	{
		return Unit::hatUpgrades::chief_petty_officer;
	}
	else if(i == 3)
	{
		return Unit::hatUpgrades::lieutenant;
	}
	else if(i == 4)
	{
		return Unit::hatUpgrades::captain;
	}
	else if(i == 5)
	{
		return Unit::hatUpgrades::admiral;
	}

}

void HatMenu::draw(SDL_Renderer* renderer)
{
	
	if(currentState != menuState::closed)
	{
		for(int i = hats.size()-1; i >= 0; i--)
		{
			//posRec->x = 0 + (size.x * (i + 1));
			posRec->x = position.x +(((1+i)*size.x)*openPercent);
			posRec->y = position.y - size.y/2;
			posRec->w = size.x;
			posRec->h = size.y;
			posRec->x -= posRec->w/2;
			SDL_RenderCopyEx(renderer,TextureManager::getManager()->blankBackground->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

			posRec->x = position.x + (((1+i)*size.x)*openPercent);
			posRec->y = position.y - hats.at(i).first->getSize().y/6*5;
			posRec->w = hats.at(i).first->getSize().x;
			posRec->h = hats.at(i).first->getSize().y;
			posRec->x -= posRec->w/2;
			SDL_RenderCopyEx(renderer,hats.at(i).first->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);


			
			message = TTF_RenderText_Solid(font,std::to_string(hats.at(i).second).c_str(), textColour);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
			posRec->x = position.x +(((1+i)*size.x)*openPercent);
			posRec->y = position.y;
			posRec->w=message->w;
			posRec->h=message->h;
			posRec->x-=posRec->w/2;
			//posRec->y+=posRec->h;
			SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);
		}
	}
	HUDElement::draw(renderer);
	posRec->x = position.x - hats.at(0).first->getSize().x/2;
	posRec->y = position.y - hats.at(0).first->getSize().y/2;
	posRec->w = hats.at(0).first->getSize().x;
	posRec->h = hats.at(0).first->getSize().y;
	SDL_RenderCopyEx(renderer,hats.at(0).first->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
}
void HatMenu::setHats(int index)
{
	hats.at(index).second++;
}

void HatMenu::menu()
{
	if(currentState == menuState::opening||currentState == menuState::open)
	{
		currentState = menuState::closing;
	}
	else if(currentState == menuState::closing||currentState == menuState::closed)
	{
		currentState = menuState::opening;
	}
}
