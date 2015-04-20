#include "HUDElement.h"

SDL_Rect* HUDElement::posRec;

HUDElement::HUDElement(float x,float y):position(x,y),openPercent(0)
{
	if(posRec == nullptr)
	{
		posRec = new SDL_Rect();
	}
	//font stuff
	font = TextureManager::getManager()->font;
	fontInner = TextureManager::getManager()->fontInner;
	text = nullptr;
	textColour.r = 255; textColour.g = 255; textColour.b = 255; textColour.a = 255;
	textColourInner.r = 0; textColourInner.g = 0; textColourInner.b = 0; textColourInner.a = 255;
	message = nullptr;
	currentState = menuState::closed;
}


HUDElement::~HUDElement(void)
{
}

void HUDElement::update(float timeElapsed)
{
	if(currentState==opening)
	{
		openPercent+=timeElapsed;
		if(openPercent>=1)
		{
			currentState=open;
			openPercent=1;
		}
	}
	if(currentState==closing)
	{
		openPercent-=timeElapsed;
		if(openPercent<=0)
		{
			currentState=closed;
			openPercent=0;
		}
	}
}

void HUDElement::draw(SDL_Renderer* renderer)
{
	posRec->x = position.x - size.x/2;
	posRec->y = position.y - size.y/2;
	posRec->w = size.x;
	posRec->h = size.y;
	SDL_RenderCopyEx(renderer,texture->getTexture(),nullptr,posRec,0,nullptr,SDL_FLIP_NONE);
}


void HUDElement::menu()
{
	if(currentState == menuState::opening)
	{
		currentState = menuState::closing;
	}
	else if(currentState == menuState::closing)
	{
		currentState = menuState::opening;
	}
	else if(currentState == menuState::closed)
	{
		currentState = menuState::opening;
	}
	else if(currentState == menuState::open)
	{
		currentState = menuState::closing;
	}
}