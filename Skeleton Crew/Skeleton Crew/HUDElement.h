#pragma once
#ifndef HUDELEMENT_H
#define HUDELEMENT_H
#include "TextureManager.h"
#include "ObjectManager.h"
#include "Vector2f.h"
#include "SDL_ttf.h"
class HUDElement
{
public:
	///
	///Constructor method for HUDElement class
	///
	HUDElement(float x,float y);

	///
	///Destructor method for HUDElement class
	///
	~HUDElement(void);

	///
	///Draws an instance of HUDElement class
	///
	void virtual draw(SDL_Renderer* renderer);

	///
	///Updates an instance of HUDElement class
	///
	void virtual update(float timeElapsed);

	///
	///returns position variable, used to check whether player is clicking on the HUD
	///
	Vector2f getPos(){return position;};
	Vector2f getSize(){return size;};
	enum menuState
	{
		closed,
		closing,
		opening,
		open
	};
	menuState currentState;
	void menu();
protected:
	float openPercent;

	///
	///Position on screen of an instance HUDElement
	///
	Vector2f position;

	///
	///stores the height and width of the HUDElement's texture
	///
	Vector2f size;

	///
	///stores the HUDElement's texture
	///
	Texture* texture;

	///
	///used for drawing the HUDElement
	///
	static SDL_Rect* posRec;
	TTF_Font *font;
	TTF_Font *fontInner;
	SDL_Surface *message;
	SDL_Texture *text;
	SDL_Color textColour;
	SDL_Color textColourInner;
};
#endif