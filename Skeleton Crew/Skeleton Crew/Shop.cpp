#include "Shop.h"


Shop::Shop(float x,float y):HUDElement(x,y)
{
	if(srcRec == nullptr)
	{
		srcRec = new SDL_Rect();
	}

	val = 0;
	textColour.r = 0; textColour.g = 0; textColour.b = 0; textColour.a = 255;
	alive = false;
	xStop = 0;
	position.x= x;
	position.y = y;
	myState = states::buyShip;
	size = TextureManager::getManager()->buyShipBack->getSize();
	tab1Pos = new Vector2f(position.x - size.x/2+274/2,position.y - size.y/2+72/2);
	tab2Pos = new Vector2f(position.x - size.x/2+274/2+274,position.y -size.y/2+72/2);
	tab3Pos = new Vector2f(position.x - size.x/2+274/2+274*2,position.y - size.y/2+72/2);
	shipScale = new Vector2f(520*0.5,180*0.5);
	shipPos = new Vector2f(position.x-(shipScale->x/2),(position.y-shipScale->y/2)+20);
	srcRec->w = shipScale->x*2;
	arrowPosLeft =new Vector2f(320,380);
	arrowPosRight =new Vector2f(940,380);

	current = 0;
	next =0;
	change = false;

	ships.push_back(pair<SDL_Texture*,int>(TextureManager::getManager()->shipLvl1->getTexture(),5000));
	ships.push_back(pair<SDL_Texture*,int>(TextureManager::getManager()->shipLvl2->getTexture(),10000));
	ships.push_back(pair<SDL_Texture*,int>(TextureManager::getManager()->shipLvl2->getTexture(),20000));
	ships.push_back(pair<SDL_Texture*,int>(TextureManager::getManager()->shipLvl3->getTexture(),50000));
	ships.push_back(pair<SDL_Texture*,int>(TextureManager::getManager()->shipLvl3->getTexture(),100000));

	hats.push_back(pair<SDL_Texture*, int>(TextureManager::getManager()->pirateRank1->getTexture(),1100));
	hats.push_back(pair<SDL_Texture*, int>(TextureManager::getManager()->pirateRank2->getTexture(),11000));
	hats.push_back(pair<SDL_Texture*, int>(TextureManager::getManager()->pirateRank3->getTexture(),21000));
	hats.push_back(pair<SDL_Texture*, int>(TextureManager::getManager()->pirateRank4->getTexture(),50000));
	hats.push_back(pair<SDL_Texture*, int>(TextureManager::getManager()->pirateRank5->getTexture(),75000));
	hats.push_back(pair<SDL_Texture*, int>(TextureManager::getManager()->pirateRank6->getTexture(),150000));

	buyBtn = new Vector2f(0,0);

	upgradePrices.push_back(3000);
	upgradePrices.push_back(15000);
	upgradePrices.push_back(30000);
	upgradePrices.push_back(65000);
	upgradePrices.push_back(120000);

	for(int i = 0; i< 6;i++)
	{
		plusBtnPos.push_back(pair<Vector2f,int>(Vector2f(0,0),0));
	}
	for(int i = 0; i< hats.size();i++)
	{
		buyBtnPos.push_back(Vector2f(0,0));
	} 
}

void Shop::update(float timeElapsed,float mouseX,float mouseY,Station *station, HatMenu *hatMenu)
{
	if(mouseX>position.x -size.x/2 &&mouseX<position.x +size.x/2 
		&&mouseY>position.y -size.y/2 && mouseY<position.y +size.y/2 )
	{
		if(sqrt((tab1Pos->x - mouseX)*(tab1Pos->x- mouseX) + (tab1Pos->y- mouseY)*(tab1Pos->y - mouseY))<100)
		{
			myState = Shop::states::upgradeUnit;
		}

		if(sqrt((tab2Pos->x - mouseX)*(tab2Pos->x - mouseX) + (tab2Pos->y - mouseY)*(tab2Pos->y - mouseY))<100)
		{
			myState = Shop::states::upgradeShip;
		}


		if(sqrt((tab3Pos->x- mouseX)*(tab3Pos->x- mouseX) + (tab3Pos->y- mouseY)*(tab3Pos->y - mouseY))<100)
		{
			myState = Shop::states::buyShip;
		}


		if (myState == states::buyShip )
		{
			if(sqrt((arrowPosLeft->x - mouseX)*(arrowPosLeft->x - mouseX) + (arrowPosLeft->y - mouseY)*(arrowPosLeft->y - mouseY))<40
				&&change == false &&current-1>=0)
			{
				change = true;
				next = current-1;
				xStop = shipPos->x+(shipScale->x+100);
			}
			else if(sqrt((arrowPosRight->x - mouseX)*(arrowPosRight->x - mouseX) + (arrowPosRight->y - mouseY)*(arrowPosRight->y - mouseY))<40
				&&change == false && current+1 <ships.size())
			{
				change = true;
				next = current+1;
				xStop = shipPos->x-(shipScale->x+100);
			}
			else if(sqrt((buyBtn->x - mouseX)*(buyBtn->x - mouseX) + (buyBtn->y - mouseY)*(buyBtn->y - mouseY))<40&&change == false)
			{
				station->setGold(station->getGold()-ships.at(current).second);
				switch (current)
				{
				case 0: 
				val  = 1.0f;
				break;
				case 1: 
				val = 1.5f;
				break;
				case 2: 
				val = 2.0f;
				break;
				case 3: 
				val = 3.0f;
				break;
				case 4: 
				val = 5.0f;
				break;
				}
				ObjectFactory::spawnShip(station->getPos().x-200, station->getPos().y-200,ObjectManager::getManager()->stations,Entity::entityType::pirate,val);
			}
		}
		else if(myState == states::upgradeShip)
		{ 
			plusBtnPos.at(0).second = 55*getValue(station->getHealthMultiply());
			plusBtnPos.at(1).second = 55*getValue(station->getReloadMultiply());
			plusBtnPos.at(2).second = 55*getValue(station->getCrowsMultiply());
			plusBtnPos.at(3).second = 55*getValue(station->getSpeedMultiply());
			plusBtnPos.at(4).second = 55*getValue(station->getTurningMultiply());
			plusBtnPos.at(5).second = 55*getValue(station->getDmgMultiply());
			for(int i = 0; i<6;i++)
			{
				if(sqrt((plusBtnPos.at(i).first.x - mouseX)*(plusBtnPos.at(i).first.x- mouseX) + (plusBtnPos.at(i).first.y- mouseY)*(plusBtnPos.at(i).first.y- mouseY))<40)
				{
					switch (i)
					{
					case 0: // Health
					val = getValue(station->getHealthMultiply());
					val++;
					if (station->getGold() >= upgradePrices.at(val-1))
					{
					station->setHealthMultiply(setValue(val));
					station->decreaseGold(upgradePrices.at(val-1));
					}
					break;
					case 1: // Reload
					val = getValue(station->getReloadMultiply());
					val++;
					if (station->getGold() >= upgradePrices.at(val-1))
					{
					station->setReloadMultiply(setValue(val));
					station->decreaseGold(upgradePrices.at(val-1));
					}
					break;
					case 2: // Crows
					val = getValue(station->getCrowsMultiply());
					val++;
					if (station->getGold() >= upgradePrices.at(val-1))
					{
					station->setCrowsMultiply(setValue(val));
					station->decreaseGold(upgradePrices.at(val-1));
					}
					break;
					case 3: // Speed
					val = getValue(station->getSpeedMultiply());
					val++;
					if (station->getGold() >= upgradePrices.at(val-1))
					{
					station->setSpeedMultiply(setValue(val));
					station->decreaseGold(upgradePrices.at(val-1));
					}
					break;
					case 4: // Turning
					val = getValue(station->getTurningMultiply());
					val++;
					if (station->getGold() >= upgradePrices.at(val-1))
					{
					station->setTurningMultiply(setValue(val));
					station->decreaseGold(upgradePrices.at(val-1));
					}
					break;
					case 5: // Damage
					val = getValue(station->getDmgMultiply());
					val++;
					if (station->getGold() >= upgradePrices.at(val-1))
					{
					station->setDmgMultiply(setValue(val));
					station->decreaseGold(upgradePrices.at(val-1));
					}
					break;
					}
				}		
			}
			plusBtnPos.at(0).second = 55*getValue(station->getHealthMultiply());
			plusBtnPos.at(1).second = 55*getValue(station->getReloadMultiply());
			plusBtnPos.at(2).second = 55*getValue(station->getCrowsMultiply());
			plusBtnPos.at(3).second = 55*getValue(station->getSpeedMultiply());
			plusBtnPos.at(4).second = 55*getValue(station->getTurningMultiply());
			plusBtnPos.at(5).second = 55*getValue(station->getDmgMultiply());
		}
		else if(myState == states::upgradeUnit)
		{
			for(int i = 0; i<hats.size();i++)
			{
				if(sqrt((buyBtnPos.at(i).x - mouseX)*(buyBtnPos.at(i).x- mouseX) + (buyBtnPos.at(i).y- mouseY)*(buyBtnPos.at(i).y- mouseY))<80)
				{
					///take gold from players current station
					//if(station->getGold()>hats.at(i).second){
						station->setGold(station->getGold()-hats.at(i).second);
						hatMenu->setHats(i);
						ObjectManager::getManager()->hatsTotal->at(i)++; 
						break;
					//}
				}
			}
		}
	}
	else 
	{
		alive = false;
	}
}

int Shop::getValue(float i)
{
	int temp = i*10;
	switch (temp)
	{
	case 10:
	return 0;
	break;
	case 11:
	return 1;
	break;
	case 12:
	return 2;
	break;
	case 15:
	return 3;
	break;
	case 20:
	return 4;
	break;
	case 30:
	return 5;
	break;
	}
}
float Shop::setValue(int i)
{
	switch (i)
	{
	case 0:
	return 1;
	break;
	case 1:
	return 1.1;
	break;
	case 2:
	return 1.2;
	break;
	case 3:
	return 1.5;
	break;
	case 4:
	return 2;
	break;
	case 5:
	return 3;
	break;
	}
}

void Shop::draw(SDL_Renderer* renderer)
{
	posRec->x = position.x-size.x/2;
	posRec->y = position.y-size.y/2;
	posRec->w = size.x;
	posRec->h = size.y;
	if (myState == states::buyShip )
	{
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->buyShipBack->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
		drawBuyShip(renderer);
	}

	else if (myState == states::upgradeShip)
	{
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->upgradeShipBack->getTexture(),NULL,posRec,NULL,NULL,SDL_FLIP_NONE);
		drawUpgradeShip(renderer);
	}	
	else if (myState == states::upgradeUnit)
	{
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->upgradeUnitBack->getTexture(),NULL,posRec,NULL,NULL,SDL_FLIP_NONE);
		drawBuyHats(renderer);
	}
}

void Shop::drawBuyShip(SDL_Renderer *renderer)
{
	if(shipPos->x < xStop+9 && shipPos->x >xStop -9)
	{
		shipPos->x = xStop;
	}
	if(change)
	{
		if(shipPos->x != xStop)
		{
			if(next > current)
			{
				shipPos->x-=5;
			}
			else if(next<current)
			{
				shipPos->x+=5;
			}
		}
		else 
		{
			current = next;
			change = false;
		}
	}
	for(int i = 0; i<ships.size(); i++)
	{
		posRec->w = shipScale->x-(srcRec->x*0.7);
		posRec->h = shipScale->y;
		posRec->x = shipPos->x +(shipScale->x+100)*i;
		posRec->y = shipPos->y;
		srcRec->h = shipScale->y*2;
		if(posRec->x >240&&posRec->x <700){
			SDL_RenderCopyEx(renderer,ships.at(i).first,NULL,posRec,NULL,NULL,SDL_FLIP_NONE);
		}
	}
	drawTop(renderer);
}

void Shop::drawBuyHats(SDL_Renderer *renderer)
{
	string s;
	int iter=0;
	for(int i = 0; i<hats.size();i++)
	{
		switch (i)
		{
		case 0:
		s = "Rigger";
		break;
		case 1:
		s = "Seaman";
		break;
		case 2:
		s = "Boatswain";
		break;
		case 3:
		s = "First Mate";
		break;
		case 4:
		s = "Captain";
		break;
		case 5:
		s = "Admiral";
		break;
		}
		posRec->w = 32;
		posRec->h = 32;
		posRec->x = 315 - posRec->w/2;
		posRec->y = 300- posRec->h/2+50*i;
		SDL_RenderCopyEx(renderer,hats.at(i).first,NULL,posRec,NULL,NULL,SDL_FLIP_NONE);

		message = TTF_RenderText_Solid(font,s.c_str(), textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
		posRec->x = 350 - posRec->w/2;
		posRec->y+=posRec->h/2;
		posRec->w=message->w;
		posRec->h=message->h;
		posRec->y-=posRec->h/2;
		SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);



		message = TTF_RenderText_Solid(font,std::to_string(hats.at(i).second).c_str(), textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
		posRec->w=message->w;
		posRec->h=message->h;
		posRec->x = 750 - posRec->w/2;
		posRec->y+=posRec->h/2;
		posRec->y-=posRec->h/2;
		SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);

		posRec->w = 128;
		posRec->h = 64;
		posRec->x = 900 - (posRec->w/2);
		posRec->y = 300- (posRec->h/2)+(50*i);
		buyBtnPos.at(iter) = Vector2f(posRec->x,posRec->y);
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->buyBtn->getTexture(),NULL,posRec,NULL,NULL,SDL_FLIP_NONE);
		iter++;
	}
}

void Shop::drawUpgradeShip(SDL_Renderer *renderer)
{
	string s;
	int iter=0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			switch (iter)
			{
			case 0:
			s = "Hull";
			break;
			case 1:
			s = "Cannon";
			break;
			case 2:
			s = "Crows Nest";
			break;
			case 3:
			s = "Sail";
			break;
			case 4:
			s = "Rudder";
			break;
			case 5:
			s = "Cannon Ball";
			break;
			}
			message = TTF_RenderText_Solid(font,s.c_str(), textColour);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
			posRec->w=message->w;
			posRec->h=message->h;
			posRec->x = 390 - posRec->w/2+400*j;
			posRec->y=340 - posRec->h/2+100*i;
			posRec->y-=posRec->h/2;
			SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);

			// Price Text
			int value=0; 
			
				
		if(plusBtnPos.at(iter).second<55*5)
		{
			value = (plusBtnPos.at(iter).second/55) ;///checks what upgrade you are buying							
			int w = 0; int h = 0;
			message = TTF_RenderText_Solid(font,std::to_string(upgradePrices.at(value)).c_str(), textColour);
			text = SDL_CreateTextureFromSurface(renderer, message);
			SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
			posRec->w = message->w;
			posRec->h = message->h;
			posRec->x = 390 - posRec->w/2+400*j;
			posRec->y = 340 - posRec->h/2+100*i + 35;
			SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
			SDL_FreeSurface(message);
			SDL_DestroyTexture(text);
		}

			posRec->w=15+plusBtnPos.at(iter).second;
			posRec->h=20;
			posRec->x = 260 +400*j;
			posRec->y=360 - posRec->h/2+100*i;
			posRec->y-=posRec->h/2;
			SDL_RenderCopyEx(renderer, TextureManager::getManager()->sword->getTexture(), nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);

			posRec->w=32;
			posRec->h=32;
			posRec->x = 550 +400*j;
			posRec->y=360 - posRec->h/2+100*i;
			posRec->y-=posRec->h/2;
			plusBtnPos.at(iter).first = Vector2f(posRec->x,posRec->y);
			SDL_RenderCopyEx(renderer, TextureManager::getManager()->plusBtn->getTexture(), nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);

			iter++;			
		}
	}
}

void Shop::drawTop(SDL_Renderer* renderer)
{
	posRec->x = position.x-size.x/2;
	posRec->y = position.y-size.y/2;
	posRec->w = size.x;
	posRec->h = size.y;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->buyShipBackTop->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
	//draw buy button
	posRec->w = 128;
	posRec->h = 64;
	posRec->x = 610-(posRec->w/2);
	posRec->y = 535- (posRec->h/2);
	buyBtn->x= 610;
	buyBtn->y =535;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->buyBtn->getTexture(),NULL,posRec,NULL,NULL,SDL_FLIP_NONE);

	//draw left_arrow
	posRec->x = arrowPosLeft->x- 128/2;
	posRec->y = arrowPosLeft->y- 64/2;
	posRec->w = 128;
	posRec->h = 64;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->leftArrow->getTexture(),NULL,posRec,NULL,NULL,SDL_FLIP_NONE);

	//draw right_arrow
	posRec->x = arrowPosRight->x-128/2;
	posRec->y = arrowPosRight->y- 64/2;
	posRec->w =128;
	posRec->h = 64;
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->rightArrow->getTexture(),NULL,posRec,NULL,NULL,SDL_FLIP_NONE);
	string s = "Test";
	s = std::to_string(ships.at(current).second);

	message = TTF_RenderText_Solid(font,s.c_str(), textColour);
	text = SDL_CreateTextureFromSurface(renderer, message);
	SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
	posRec->x = 580;// - posRec->w/2;
	posRec->y+=(posRec->h/2)-80;
	posRec->w=message->w;
	posRec->h=message->h;
	posRec->y-=posRec->h/2;
	SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
	SDL_FreeSurface(message);
	SDL_DestroyTexture(text);
}

Shop::~Shop(void)
{
}
