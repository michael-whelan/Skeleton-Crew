#pragma once
#ifndef MENU_H
#define MENU_H
#include "KeyManager.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "Control.h"

class Menu
{
private:
	TTF_Font *font;
	SDL_Surface *message;
	SDL_Texture *text;
	SDL_Color textColour;
	string loadMsg;
	bool loadedGame;
	bool loadBtn;
public:
	bool successLoad;
	///constructor method: creates a new Menu object using the information passed in
	Menu(void);
	///Destructor method: deletes this object at termination/clean up 
	~Menu(void);
	///Method used to update the menu object
	void update(float timeElapsed);
	/// method used to draw the menu 
	void draw(SDL_Renderer* renderer);
	///Draw text on screen
	void DrawTextOnScreen(SDL_Surface *msg,SDL_Texture *txt, SDL_Rect* txtPos, string str, SDL_Renderer* renderer); 
	///Reset all the buttons to their default keys
	void ResetButtons();
	///Update Main Menu
	void MainMenuUpdate(); 
	///Draw the option's menu
	void DrawMainMenu(SDL_Renderer* renderer); 
	///Update DeathScreen
	void DeathScreenUpdate();
	///Draw DeathScreen
	void DrawDeathScreen(SDL_Renderer* renderer); 
	///Update Options Menu
	void OptionsMenuUpdate();
	///Draw the option's menu
	void DrawOptionsMenu(SDL_Renderer* renderer); 


	bool getLoadBtn(){return loadBtn;};
	void setLoadBtn(bool b){loadBtn = b;};
	/// enumeration used to represent the different state the menu can be in or needs to know about
	enum state 
	{
		mainMenu, /// the menu is displayed
		inGame, /// no menu is displayed
		deathScreen, /// screen displayed when the game is over
		optionsScreen /// the screen that shows the games options 
	};
	/// state object used to switch between different game states
	state gameState; 
	/// stores the screen size of the game
	Vector2f screenSize; 
	/// store the screen's x and y coordinates 
	SDL_Rect* screenPos;
	/// stores the size of the button
	Vector2f buttonSize; 
	/// stores the button's x and y coordinates 
	SDL_Rect* playButtonPos; 
	///boolean used to detect if the mouse is currently over the button 
	bool playOverBtn;  
	/// stores the button's x and y coordinates 
	SDL_Rect* quitButtonPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* quitButtonPosMain;

	void setLoadMsg(string msg){loadMsg = msg;};

	void setLoadedGame(bool b){loadedGame = b;};
	bool getLoadedGame(){return loadedGame;};

	SDL_Rect*loadMessagePos;
	///boolean used to detect if the mouse is currently over the button 
	bool quitOverBtn; 
	/// stores the button's x and y coordinates 
	SDL_Rect* restartButtonPos; 
	///boolean used to detect if the mouse is currently over the button 
	bool restartOverBtn; 
	/// stores the button's x and y coordinates 
	SDL_Rect* optionsButtonPos; 
	///boolean used to detect if the mouse is currently over the button 
	bool optionsOverBtn; 
	/// stores the button's x and y coordinates 
	SDL_Rect* loadButtonPos; 
	///boolean used to detect if the mouse is currently over the button 
	bool loadOverBtn;  
	/// stores the button's x and y coordinates 
	SDL_Rect* backButtonPos; 
	///boolean used to detect if the mouse is currently over the button
	bool backOverBtn; 
	/// stores the button's x and y coordinates 
	SDL_Rect* defaultButtonPos; 
	/// stores the size of the small button
	Vector2f smallbtnSize; 
	/// stores the button's x and y coordinates 
	SDL_Rect* upBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* downBtnPos; 
	/// stores the size of the small button
	SDL_Rect* leftBtnPos;  
	/// stores the button's x and y coordinates 
	SDL_Rect* rightBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* grappleBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* assignBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* cannonUpBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* cannonDownBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* cannonLeftBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* cannonRightBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* helmUpBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* helmDownBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* helmLeftBtnPos; 
	/// stores the button's x and y coordinates 
	SDL_Rect* helmRightBtnPos; 
	///Message we want to display
	SDL_Surface *messageUp;
	///The actual text we want to write to the screen
	SDL_Texture *textUp;
	///Text position on screen
	SDL_Rect* textPosUp; 
	///String beside the up button 
	std::string stringUp;
	///Message we want to display
	SDL_Surface *messageDown;
	///The actual text we want to write to the screen
	SDL_Texture *textDown;
	///Text position on screen
	SDL_Rect* textPosDown; 
	///String beside the up button 
	std::string stringDown;
	///Message we want to display
	SDL_Surface *messageLeft;
	///The actual text we want to write to the screen
	SDL_Texture *textLeft;
	///Text position on screen
	SDL_Rect* textPosLeft; 
	///String beside the up button 
	std::string stringLeft;
	///Message we want to display
	SDL_Surface *messageRight;
	///The actual text we want to write to the screen
	SDL_Texture *textRight;
	///Text position on screen
	SDL_Rect* textPosRight; 
	///String beside the up button 
	std::string stringRight;
	///Message we want to display
	SDL_Surface *messageGrapple;
	///The actual text we want to write to the screen
	SDL_Texture *textGrapple;
	///Text position on screen
	SDL_Rect* textPosGrapple; 
	///String beside the up button 
	std::string stringGrapple;
	///Message we want to display
	SDL_Surface *messageAssign;
	///The actual text we want to write to the screen
	SDL_Texture *textAssign;
	///Text position on screen
	SDL_Rect* textPosAssign; 
	///String beside the up button 
	std::string stringAssign;
	///Message we want to display
	SDL_Surface *messageCannonUp;
	///The actual text we want to write to the screen
	SDL_Texture *textCannonUp;
	///Text position on screen
	SDL_Rect* textPosCannonUp; 
	///String beside the up button 
	std::string stringCannonUp;
	///Message we want to display
	SDL_Surface *messageCannonDown;
	///The actual text we want to write to the screen
	SDL_Texture *textCannonDown;
	///Text position on screen
	SDL_Rect* textPosCannonDown; 
	///String beside the up button 
	std::string stringCannonDown;
	///Message we want to display
	SDL_Surface *messageCannonLeft;
	///The actual text we want to write to the screen
	SDL_Texture *textCannonLeft;
	///Text position on screen
	SDL_Rect* textPosCannonLeft; 
	///String beside the up button 
	std::string stringCannonLeft;
	///Message we want to display
	SDL_Surface *messageCannonRight;
	///The actual text we want to write to the screen
	SDL_Texture *textCannonRight;
	///Text position on screen
	SDL_Rect* textPosCannonRight; 
	///String beside the up button 
	std::string stringCannonRight;
	///Message we want to display
	SDL_Surface *messageHelmUp;
	///The actual text we want to write to the screen
	SDL_Texture *textHelmUp;
	///Text position on screen
	SDL_Rect* textPosHelmUp; 
	///String beside the up button 
	std::string stringHelmUp;
	///Message we want to display
	SDL_Surface *messageHelmDown;
	///The actual text we want to write to the screen
	SDL_Texture *textHelmDown;
	///Text position on screen
	SDL_Rect* textPosHelmDown; 
	///String beside the up button 
	std::string stringHelmDown;
	///Message we want to display
	SDL_Surface *messageHelmLeft;
	///The actual text we want to write to the screen
	SDL_Texture *textHelmLeft;
	///Text position on screen
	SDL_Rect* textPosHelmLeft; 
	///String beside the up button 
	std::string stringHelmLeft;
	///Message we want to display
	SDL_Surface *messageHelmRight;
	///The actual text we want to write to the screen
	SDL_Texture *textHelmRight;
	///Text position on screen
	SDL_Rect* textPosHelmRight; 
	///String beside the up button 
	std::string stringHelmRight;

    ///Check if you can set a new key
	bool setUpkey; 
	///Check if you can set a new key
	bool setDownkey; 
	///Check if you can set a new key
	bool setLeftkey; 
	///Check if you can set a new key
	bool setRightkey; 	
	///Check if you can set a new key
	bool setGrapplekey; 
	///Check if you can set a new key
	bool setAssignkey; 
	///Check if you can set a new key
	bool setCannonUpkey; 
	///Check if you can set a new key
	bool setCannonDownkey; 
	///Check if you can set a new key
	bool setCannonLeftkey; 
	///Check if you can set a new key
	bool setCannonRightkey; 
	///Check if you can set a new key
	bool setHelmUpkey; 
	///Check if you can set a new key
	bool setHelmDownkey; 
	///Check if you can set a new key
	bool setHelmLeftkey; 
	///Check if you can set a new key
	bool setHelmRightkey; 
};
#endif

