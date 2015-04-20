#include "BankGUI.h"


int BankGUI::bankGold;

BankGUI::BankGUI(float x, float y):HUDElement(x,y)
{
	openMenu = false;
	font = TextureManager::getManager()->font;
	text = nullptr;
	textColour.r = 0; textColour.g = 0; textColour.b = 0; textColour.a = 255;
	message = nullptr;
	bankWidth = 854;
	bankHeigth = 480;
	bankX = x;
	bankY = y;
	btnRadius = 64;
	depositBtn.x = bankX - (btnRadius)*3;
	depositBtn.y = 300;
	withdrawBtn.x = bankX + (btnRadius)*3;
	withdrawBtn.y = 300;
	bankAmount.x = bankX;
	bankAmount.y = 300;
	if (bankGold == NULL)
	{
		bankGold = 0;
	}
	transferCount = 0;

	slider.x = bankWidth/2;
	slider.y = bankHeigth/2 + 200;
	minusBtn.x = slider.x -64;
	minusBtn.y = slider.y;
	plusBtn.x = slider.x +400;
	plusBtn.y = slider.y;
}

void BankGUI::update(float timeElapsed)
{
	if(ObjectManager::getManager()->selected)
	{
		if ((Station*)ObjectManager::getManager()->selected->getStation())
		{
			currentStation = ((Station*)ObjectManager::getManager()->selected->getStation());
			if (openMenu)
			{
				mousePos = KeyManager::getManager()->mousePosition();
				if(KeyManager::getManager()->mousePressed(KeyManager::mouseButtons::left))
				{
					if((mousePos.x > bankX-bankWidth && mousePos.x <(bankX+(bankWidth/2)))&&(mousePos.y > bankY- (bankHeigth/2) && mousePos.y < (bankY+(bankHeigth/2))))
					{
						if(sqrt((withdrawBtn.x - mousePos.x)*(withdrawBtn.x- mousePos.x) + (withdrawBtn.y- mousePos.y)*(withdrawBtn.y - mousePos.y))<128)
						{ // Widthdraw

							if (bankGold >= tranferAmount)
							{
								currentStation->increaseGold(tranferAmount);
								bankGold -= tranferAmount;
							}
							else
							{

							}
						}
						if(sqrt((plusBtn.x - mousePos.x)*(plusBtn.x- mousePos.x) + (plusBtn.y- mousePos.y)*(plusBtn.y - mousePos.y))<128)
						{ // Plus
							if (transferCount < 7)
							{
								transferCount ++;
							}

						}
						if(sqrt((minusBtn.x - mousePos.x)*(minusBtn.x- mousePos.x) + (minusBtn.y- mousePos.y)*(minusBtn.y - mousePos.y))<128)
						{ // Minus

							if (transferCount > 0)
							{
								transferCount --;
							}
						}
						else if(sqrt((depositBtn.x - mousePos.x)*(depositBtn.x- mousePos.x) + (depositBtn.y- mousePos.y)*(depositBtn.y - mousePos.y))<128)
						{ //Deposit

							if (currentStation->getGold() >= tranferAmount)
							{
								currentStation->decreaseGold(tranferAmount);
								bankGold += tranferAmount;
							}

						}
					}
					else
					{
						openMenu = false;
						transferCount = 0;
					}
				}
			}
		}
	}
	else 
	{
		openMenu = false;
		transferCount = 0;
	}
}

void BankGUI::draw(SDL_Renderer* renderer)
{
	if (openMenu)
	{
		//Bank background
		posRec->x = (int)(bankX - (bankWidth/2.0f));
		posRec->y = (int)(bankY - (bankHeigth/2.0f));
		posRec->w = (int)(bankWidth);
		posRec->h = (int)(bankHeigth);
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->bankTexture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

		// Deposit button
		posRec->x = (int)(depositBtn.x- btnRadius);
		posRec->y = (int)(depositBtn.y-btnRadius);
		posRec->w = (int)(btnRadius*2.0f);
		posRec->h = (int)(btnRadius*2.0f);
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->deposit->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);

		// Withdraw button
		posRec->x = withdrawBtn.x - btnRadius;
		posRec->y = withdrawBtn.y-btnRadius;
		posRec->w = btnRadius*2;
		posRec->h = btnRadius*2;
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->withdraw->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);


		// Bank Amount
		posRec->x = bankAmount.x - btnRadius;
		posRec->y = bankAmount.y - btnRadius;
		posRec->w = btnRadius*2;
		posRec->h = btnRadius*2;
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->bankAmount->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
		int w = 0; int h = 0;
		message = TTF_RenderText_Solid(font,std::to_string(bankGold).c_str(), textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		posRec->w = message->w;
		posRec->h = message->h;
		posRec->x = bankX-message->w/2;
		posRec->y = bankY - 120;
		SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);

		// Bank Text
		message = TTF_RenderText_Solid(font,"Bank Amount: ", textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		posRec->w = message->w;
		posRec->h = message->h;
		posRec->x = bankX-message->w/2 - 150;
		posRec->y = bankY - 120;
		SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);


		//Slider
		posRec->w=10 + transferCount*50;
		posRec->h=20;
		posRec->x = slider.x ;
		posRec->y = slider.y;
		posRec->y-=posRec->h/2;
		SDL_RenderCopyEx(renderer, TextureManager::getManager()->sword->getTexture(), nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);

		switch (transferCount)
		{
		case 0:
			tranferAmount = 0;
			break;
		case 1:
			tranferAmount = 1000;
			break;
		case 2:
			tranferAmount = 5000;
			break;
		case 3:
			tranferAmount = 10000;
			break;
		case 4:
			tranferAmount = 20000;
			break;
		case 5:
			tranferAmount = 50000;
			break;
		case 6:
			tranferAmount = 75000;
			break;
		case 7:
			tranferAmount = 100000;
			break;
		}
		message = TTF_RenderText_Solid(font,std::to_string(tranferAmount).c_str(), textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		posRec->w = message->w;
		posRec->h = message->h;
		posRec->x= bankX - message->w/2;
		posRec->y= slider.y - 50;
		SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);

		message = TTF_RenderText_Solid(font,"Transfer Amount: ", textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		posRec->w = message->w;
		posRec->h = message->h;
		posRec->x= bankX - message->w/2 - 150;
		posRec->y= slider.y - 50;
		SDL_RenderCopyEx(renderer, text, nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);

		// Minus button
		posRec->w=32;
		posRec->h=32;
		posRec->x = minusBtn.x;
		posRec->y=	minusBtn.y;
		posRec->y-=posRec->h/2;
		SDL_RenderCopyEx(renderer, TextureManager::getManager()->minusDBbtn->getTexture(), nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);

		// Plus button
		posRec->w=32;
		posRec->h=32;
		posRec->x = plusBtn.x;
		posRec->y=	plusBtn.y;
		posRec->y-=posRec->h/2;
		SDL_RenderCopyEx(renderer, TextureManager::getManager()->plusDBbtn->getTexture(), nullptr, posRec, 0, nullptr, SDL_FLIP_NONE);
	}
}
BankGUI::~BankGUI(void)
{
}
