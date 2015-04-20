#include "Menu.h"
#include "SoundManager.h"
#include "ObjectManager.h"
///Construtor 
Menu::Menu(void)
{   ///initialise class varirables
	///Set the intial gameState to the main menu
	loadedGame = false;
	successLoad=false;
	loadBtn = false;
	gameState = mainMenu; 
	///Set the width of the screen
	screenSize.x = 1280;
	///Set the breadth of the screen
	screenSize.y = 780;
	///Set the width of the button
	buttonSize.x = 128;
	///Set the breadth of the button
	buttonSize.y = 64;
	///Set the width of the small button
	smallbtnSize.x = 100;
	///Set the breadth of the small button
	smallbtnSize.y = 50;
	///If the rectangle is not intialised
	font = TextureManager::getManager()->font;
	text = nullptr;
	textColour.r = 0; textColour.g = 0; textColour.b = 0; textColour.a = 255;
	message = nullptr;
	if(!screenPos)
	{
		/// create a new one 
		screenPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	loadMsg = " ";
	if(loadMessagePos==nullptr)
	{
		loadMessagePos = new SDL_Rect();
	}

	buttonSize.x = 128;
	buttonSize.y = 64;
	if(!playButtonPos)
	{
		/// create a new one 
		playButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!quitButtonPos)
	{
		/// create a new one 
		quitButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!restartButtonPos)
	{
		/// create a new one 
		restartButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!quitButtonPosMain)
	{
		/// create a new one 
		quitButtonPosMain = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!optionsButtonPos)
	{
		/// create a new one 
		optionsButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!loadButtonPos)
	{
		/// create a new one 
		loadButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!backButtonPos)
	{
		/// create a new one 
		backButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!defaultButtonPos)
	{
		/// create a new one 
		defaultButtonPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!upBtnPos)
	{
		/// create a new one 
		upBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!downBtnPos)
	{
		/// create a new one 
		downBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!leftBtnPos)
	{
		/// create a new one 
		leftBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!rightBtnPos)
	{
		/// create a new one 
		rightBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!grappleBtnPos)
	{
		/// create a new one 
		grappleBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!assignBtnPos)
	{
		/// create a new one 
		assignBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!cannonUpBtnPos)
	{
		/// create a new one 
		cannonUpBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!cannonDownBtnPos)
	{
		/// create a new one 
		cannonDownBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!cannonLeftBtnPos)
	{
		/// create a new one 
		cannonLeftBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!cannonRightBtnPos)
	{
		/// create a new one 
		cannonRightBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!helmUpBtnPos)
	{
		/// create a new one 
		helmUpBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!helmDownBtnPos)
	{
		/// create a new one 
		helmDownBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!helmLeftBtnPos)
	{
		/// create a new one 
		helmLeftBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!helmRightBtnPos)
	{
		/// create a new one 
		helmRightBtnPos = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosUp)
	{
		/// create a new one 
		textPosUp = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosDown)
	{
		/// create a new one 
		textPosDown = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosLeft)
	{
		/// create a new one 
		textPosLeft = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosRight)
	{
		/// create a new one 
		textPosRight = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosGrapple)
	{
		/// create a new one 
		textPosGrapple = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosAssign)
	{
		/// create a new one 
		textPosAssign = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosCannonUp)
	{
		/// create a new one 
		textPosCannonUp = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosCannonDown)
	{
		/// create a new one 
		textPosCannonDown = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosCannonLeft)
	{
		/// create a new one 
		textPosCannonLeft = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosCannonRight)
	{
		/// create a new one 
		textPosCannonRight = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosHelmUp)
	{
		/// create a new one 
		textPosHelmUp = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosHelmDown)
	{
		/// create a new one 
		textPosHelmDown = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosHelmLeft)
	{
		/// create a new one 
		textPosHelmLeft = new SDL_Rect();
	}
	///If the rectangle is not intialised
	if(!textPosHelmRight)
	{
		/// create a new one 
		textPosHelmRight = new SDL_Rect();
	}
	///Up string
	//stringUp = " ";
	///Init text
	textUp = nullptr;
	///Init message
	messageUp = nullptr;
	///Down string
	//stringDown = " ";
	///Init text
	textDown = nullptr;
	///Init message
	messageDown = nullptr;
	///left string
	//stringLeft = " ";
	///Init text
	textLeft = nullptr;
	///Init message
	messageLeft = nullptr;
	///right string
	//stringRight = " ";
	///Init text
	textRight = nullptr;
	///Init message
	messageRight = nullptr;
	///Grapple string
	//stringGrapple = " ";
	///Init text
	textGrapple = nullptr;
	///Init message
	messageGrapple = nullptr;
	///Assign string
	//stringAssign = " ";
	///Init text
	textAssign = nullptr;
	///Init message
	messageAssign = nullptr;
	///Cannon up string
	//stringCannonUp = " ";
	///Init text
	textCannonUp = nullptr;
	///Init message
	messageCannonUp = nullptr;
	///cannon down string
	//stringCannonDown = " ";
	///Init text
	textCannonDown = nullptr;
	///Init message
	messageCannonDown = nullptr;
	///cannon left string
	//stringCannonLeft = " ";
	///Init text
	textCannonLeft = nullptr;
	///Init message
	messageCannonLeft = nullptr;
	///cannon right string
	//stringCannonRight = " ";
	///Init text
	textCannonRight = nullptr;
	///Init message
	messageCannonRight = nullptr;
	///Helm up string
	//stringHelmUp = " ";
	///Init text
	textHelmUp = nullptr;
	///Init message
	messageHelmUp = nullptr;
	///helm down string
	//stringHelmDown = " ";
	///Init text
	textHelmDown = nullptr;
	///Init message
	messageHelmDown = nullptr;
	///helm left string
	//stringHelmLeft = " ";
	///Init text
	textHelmLeft = nullptr;
	///Init message
	messageHelmLeft = nullptr;
	///helm right string
	//stringHelmRight = " ";
	///Init text
	textHelmRight = nullptr;
	///Init message
	messageHelmRight = nullptr;
	///Check if mouse is over button
	playOverBtn = false; 
	///Check if mouse is over button
	quitOverBtn = false; 
	///Check if mouse is over button
	restartOverBtn = false;
	///Check if mouse is over button
	optionsOverBtn = false; 
	///Check if mouse is over button
	backOverBtn = false;
	///For text
	font = TextureManager::getManager()->font;
	///Text colour
	textColour.r = 0; textColour.g = 0; textColour.b = 0; textColour.a = 255;
	//Check to see if you can assgin a new key to the up Command
	setUpkey = false; 
	//Check to see if you can assgin a new key to the up Command
	setGrapplekey = false; 
	//Check to see if you can assgin a new key to the up Command
	setAssignkey = false; 
	///Check to see if the mouse is over this buttons location
	loadOverBtn = false;
	///display default key in the text beside the command
	stringUp = SDL_GetScancodeName(Control::getManager()->GetMoveUpCommand());
	///display default key in the text beside the command
	stringDown = SDL_GetScancodeName(Control::getManager()->GetMoveDownCommand());
	///display default key in the text beside the command
	stringLeft = SDL_GetScancodeName(Control::getManager()->GetMoveLeftCommand());
	///display default key in the text beside the command
	stringRight = SDL_GetScancodeName(Control::getManager()->GetMoveRightCommand());
	///display default key in the text beside the command
	stringGrapple = SDL_GetScancodeName(Control::getManager()->GetGrappleCommand());
	///display default key in the text beside the command
	stringAssign = SDL_GetScancodeName(Control::getManager()->GetAssignCommand());
	///display default key in the text beside the command
	stringCannonUp = SDL_GetScancodeName(Control::getManager()->GetCannonMoveUp());
	///display default key in the text beside the command
	stringCannonDown = SDL_GetScancodeName(Control::getManager()->GetCannonMoveDown());
	///display default key in the text beside the command
	stringCannonLeft = SDL_GetScancodeName(Control::getManager()->GetCannonMoveLeft());
	///display default key in the text beside the command
	stringCannonRight = SDL_GetScancodeName(Control::getManager()->GetCannonMoveRight());
	///display default key in the text beside the command
	stringHelmUp = SDL_GetScancodeName(Control::getManager()->GetHelmMoveUp());
	///display default key in the text beside the command
	stringHelmDown =  SDL_GetScancodeName(Control::getManager()->GetHelmMoveDown());
	///display default key in the text beside the command
	stringHelmLeft =  SDL_GetScancodeName(Control::getManager()->GetHelmMoveLeft());
	///display default key in the text beside the command
	stringHelmRight = SDL_GetScancodeName(Control::getManager()->GetHelmMoveRight());
}

///Destrutor
Menu::~Menu(void)
{
	Control::getManager()->SaveCommands(); 
}
///Update class
void Menu::update(float timeElapsed)
{
	///If the gameState is the mainMenu
	if(gameState == mainMenu)
	{
		///Update the main menuMain
		MainMenuUpdate();
	}
	///If the game state is the deathScreen
	else if(gameState == deathScreen)
	{
		///Update the death screen
		DeathScreenUpdate();
	}
	///If the gameState is the optionsScreen
	else if(gameState == optionsScreen)
	{
		///Update the options screen
		OptionsMenuUpdate(); 
	}
}
///Draw class
void Menu::draw(SDL_Renderer* renderer)
{
	///If gameState is the mainMenu
	if(gameState == mainMenu)
	{
		///Draw th main menu
		DrawMainMenu(renderer);	
		
	}
	///If the games state is the death screen
	else if(gameState == deathScreen)
	{
		///Draw the deathScreen
		DrawDeathScreen(renderer);
	}
	///If the gameState is the optionsScreen
	if(gameState == optionsScreen)
	{
		///Draw the options screen
		DrawOptionsMenu(renderer);	
	}
}
///Draw text on the screen
void Menu::DrawTextOnScreen(SDL_Surface *msg,SDL_Texture *txt, SDL_Rect* txtPos, string str, SDL_Renderer* renderer)
{
	///Draw text
	///Init method varirables 
	int w = 0; int h = 0;
	///set the message
	msg = TTF_RenderText_Solid(font,str.c_str(), textColour);
	///Set the text breadth to be the same as the message
	txtPos->w = msg->w;
	///Set the text height to be the same as the message
	txtPos->h = msg->h;
	///Create the surface the text will be displayed on
	txt = SDL_CreateTextureFromSurface(renderer, msg);
	///Set the assests of the texture to be rendered 
	SDL_QueryTexture(txt, nullptr, nullptr, &w, &h);
	///Copy the texture to the current rendering targt
	SDL_RenderCopyEx(renderer, txt, nullptr, txtPos, 0, nullptr, SDL_FLIP_NONE);
	///Clear the surface
	SDL_FreeSurface(msg);
	///Destroy the text
	SDL_DestroyTexture(txt);
}
///Rebind all the button commands to their defult keys
void Menu::ResetButtons()
{
	///Reset buttons
	Control::getManager()->GetDeaultCommands(); 
	///display default key in the text beside the command
	stringUp = SDL_GetScancodeName(Control::getManager()->GetMoveUpCommand());
	///display default key in the text beside the command
	stringDown = SDL_GetScancodeName(Control::getManager()->GetMoveDownCommand());
	///display default key in the text beside the command
	stringLeft = SDL_GetScancodeName(Control::getManager()->GetMoveLeftCommand());
	///display default key in the text beside the command
	stringRight = SDL_GetScancodeName(Control::getManager()->GetMoveRightCommand());
	///display default key in the text beside the command
	stringGrapple = SDL_GetScancodeName(Control::getManager()->GetGrappleCommand());
	///display default key in the text beside the command
	stringAssign = SDL_GetScancodeName(Control::getManager()->GetAssignCommand());
	///display default key in the text beside the command
	stringCannonUp = SDL_GetScancodeName(Control::getManager()->GetCannonMoveUp());
	///display default key in the text beside the command
	stringCannonDown = SDL_GetScancodeName(Control::getManager()->GetCannonMoveDown());
	///display default key in the text beside the command
	stringCannonLeft = SDL_GetScancodeName(Control::getManager()->GetCannonMoveLeft());
	///display default key in the text beside the command
	stringCannonRight = SDL_GetScancodeName(Control::getManager()->GetCannonMoveRight());
	///display default key in the text beside the command
	stringHelmUp = SDL_GetScancodeName(Control::getManager()->GetHelmMoveUp());
	///display default key in the text beside the command
	stringHelmDown =  SDL_GetScancodeName(Control::getManager()->GetHelmMoveDown());
	///display default key in the text beside the command
	stringHelmLeft =  SDL_GetScancodeName(Control::getManager()->GetHelmMoveLeft());
	///display default key in the text beside the command
	stringHelmRight = SDL_GetScancodeName(Control::getManager()->GetHelmMoveRight());
}
///Update the main menu 
void Menu::MainMenuUpdate()
{
	///Play main menu music
	SoundManager::getManager()->startMusic(SoundManager::getManager()->menuMusic);
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > playButtonPos->x && KeyManager::getManager()->mousePosition().x < playButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > playButtonPos->y && KeyManager::getManager()->mousePosition().y < playButtonPos->y + buttonSize.y)
	{
		///set the check to true
		playOverBtn = true; 
		///Check if the left mouse button is clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			///Switch the game state to be inGame
			gameState = inGame; 
			///Stop the main menu music
			SoundManager::getManager()->stopMusic();
			if(!successLoad)
			{
				ObjectManager::getManager()->setUp();
			}
		}
	}
	///if the mouse is not over the button image
	else
	{ 
		///set the check to false
		playOverBtn = false; 
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > quitButtonPosMain->x && KeyManager::getManager()->mousePosition().x < quitButtonPosMain->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > quitButtonPosMain->y && KeyManager::getManager()->mousePosition().y < quitButtonPosMain->y + buttonSize.y)
	{
		///set the check to true
		quitOverBtn = true; 
		///Check if the left mouse button is clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			playOverBtn = true; 
			//gameState = inGame; 
			KeyManager::getManager()->setQuit(true); 
		}
	}
	///if the mouse is not over the button image
	else
	{
		///set the check to false
		quitOverBtn = false; 
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > optionsButtonPos->x && KeyManager::getManager()->mousePosition().x < optionsButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > optionsButtonPos->y && KeyManager::getManager()->mousePosition().y < optionsButtonPos->y + buttonSize.y)
	{
		///set the check to true
		optionsOverBtn = true; 
		///Check if the left mouse button is clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			///Set the game state to be the optionsMenu
			gameState = optionsScreen;; 
		}
	}
	///if the mouse is not over the button image
	else
	{
		///set the check to false
		optionsOverBtn = false; 
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > loadButtonPos->x && KeyManager::getManager()->mousePosition().x < loadButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > loadButtonPos->y && KeyManager::getManager()->mousePosition().y < loadButtonPos->y + buttonSize.y)
	{
		///set the check to true
		loadOverBtn = true; 
		///Check if the left mouse button is clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//loadedGame=true;
			loadBtn = true;
		}
	}
	///if the mouse is not over the button image
	else
	{
		///set the check to false
		loadOverBtn = false; 
	}
}
///Draw the main menu
void Menu::DrawMainMenu(SDL_Renderer* renderer)
{
	///Method varirables used to space the buttons 
	int btnOffSetX = 60, btnOffSetY = 700, btnSpacing = 150; 
	///Draw background at this position and size
	screenPos->x = 0; 
	screenPos->y = 0; 
	screenPos->w = screenSize.x;
	screenPos->h = screenSize.y;

	///Draw play button at this position and size
	playButtonPos->x = screenSize.x/2 -  btnOffSetX; 
	playButtonPos->y = screenSize.y - btnOffSetY; 
	playButtonPos->w = buttonSize.x;
	playButtonPos->h = buttonSize.y;

	///Draw options button at this position and size
	optionsButtonPos->x = screenSize.x/2 -  btnOffSetX; 
	optionsButtonPos->y = screenSize.y - (btnOffSetY - btnSpacing); 
	optionsButtonPos->w = buttonSize.x;
	optionsButtonPos->h = buttonSize.y;

	///Draw load button at this position and size
	loadButtonPos->x = screenSize.x/2 -  btnOffSetX; 
	loadButtonPos->y = screenSize.y - (btnOffSetY - btnSpacing - btnSpacing); 
	loadButtonPos->w = buttonSize.x;
	loadButtonPos->h = buttonSize.y;

	///Draw quit button at this position and size
	quitButtonPosMain->x = screenSize.x/2 -  btnOffSetX; 
	quitButtonPosMain->y = screenSize.y - (btnOffSetY - btnSpacing - btnSpacing - btnSpacing); 
	quitButtonPosMain->w = buttonSize.x;
	quitButtonPosMain->h = buttonSize.y;

	///Draw background
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->menu_screen->getTexture(),nullptr,screenPos,0,nullptr,SDL_FLIP_NONE);

	///if mouse isn't over the buttons image
	if(playOverBtn == false)
	{   
		///Draw default button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->playBtn->getTexture(),nullptr,playButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	/// if it is over the button image
	else
	{   ///Draw the highlighted button image 
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->playBtn2->getTexture(),nullptr,playButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///if mouse isn't over the buttons image
	if(quitOverBtn == false)
	{   
		///Draw default button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->quitBtn->getTexture(),nullptr,quitButtonPosMain,0,nullptr,SDL_FLIP_NONE);
	}
	/// if it is over the button image
	else
	{
		///Draw the highlighted button image 
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->quitBtn2->getTexture(),nullptr,quitButtonPosMain,0,nullptr,SDL_FLIP_NONE);
	}
	///if mouse isn't over the buttons images
	if(optionsOverBtn == false)
	{
		///Draw the default button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->optionsBtn->getTexture(),nullptr,optionsButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	/// if it is over the button image
	else
	{
		///Draw the highlighted button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->optionsBtn2->getTexture(),nullptr,optionsButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///if mouse isn't over the buttons images
	if(loadOverBtn == false)
	{
		///Draw the default button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->loadBtn->getTexture(),nullptr,loadButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	/// if it is over the button image
	else
	{
		///Draw the highlighted button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->loadBtn2->getTexture(),nullptr,loadButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
		message = TTF_RenderText_Solid(font,loadMsg.c_str() , textColour);
		text = SDL_CreateTextureFromSurface(renderer, message);
		SDL_QueryTexture(text, nullptr, nullptr, &message->w, &message->h);
		loadMessagePos->w = message->w;
		loadMessagePos->h = message->h;
		loadMessagePos->x = 1000-message->w;
		loadMessagePos->y = 650;
		SDL_RenderCopyEx(renderer, text, nullptr, loadMessagePos, 0, NULL, SDL_FLIP_NONE);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text);
}
///Update the death screen
void Menu::DeathScreenUpdate()
{
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > quitButtonPos->x && KeyManager::getManager()->mousePosition().x < quitButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > quitButtonPos->y && KeyManager::getManager()->mousePosition().y < quitButtonPos->y + buttonSize.y)

	{
		///set the check to true
		quitOverBtn = true; 
		///Check if the left mouse button is clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Return to main menu
			gameState = mainMenu; 
		}
	}
	///if the mouse is not over the button image
	else
	{
		///set the check to false
		quitOverBtn = false; 
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > restartButtonPos->x && KeyManager::getManager()->mousePosition().x < restartButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > restartButtonPos->y && KeyManager::getManager()->mousePosition().y < restartButtonPos->y + buttonSize.y)
	{
		///set the check to true
		restartOverBtn = true; 
		///Check if the left mouse button is clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			///Delete all the game objects 
			delete ObjectManager::getManager();
			///Set the game state to be inGame
			ObjectManager::getManager()->setUp();
			gameState = inGame;
		}
	}
	///if the mouse is not over the button image
	else
	{
		///set the check to false
		restartOverBtn = false; 
	}
}
///Draw the death screen
void Menu::DrawDeathScreen(SDL_Renderer* renderer)
{
	//Draw quit button at this position and size
	quitButtonPos->x = 500; 
	quitButtonPos->y = 500; 
	quitButtonPos->w = buttonSize.x;
	quitButtonPos->h = buttonSize.y;
	//Draw restart button at this position and size
	restartButtonPos->x = 700; 
	restartButtonPos->y = 500; 
	restartButtonPos->w = buttonSize.x;
	restartButtonPos->h = buttonSize.y;
	///Draw deathScreen background image
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->deatBackground->getTexture(),nullptr,screenPos,0,nullptr,SDL_FLIP_NONE);
	///If the mouse is on the button image
	if(quitOverBtn == false)
	{
		///Draw highlighted button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->quitBtn->getTexture(),nullptr,quitButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///If the mouse is not on the button image
	else
	{
		///Draw default button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->quitBtn2->getTexture(),nullptr,quitButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///If the mouse is on the button image
	if(restartOverBtn == false)
	{
		///Draw highlighted button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->replayBtn->getTexture(),nullptr,restartButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///If the mouse is not on the button image
	else
	{
		///Draw default button image
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->replayBtn2->getTexture(),nullptr,restartButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
}
///Update the options menu
void Menu::OptionsMenuUpdate()
{
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > backButtonPos->x && KeyManager::getManager()->mousePosition().x < backButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > backButtonPos->y && KeyManager::getManager()->mousePosition().y < backButtonPos->y + buttonSize.y)
	{
		///set the check to true
		backOverBtn = true; 
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Return to main menu
			gameState = mainMenu;
		}
	}
	///if mouse is not over the button image
	else
	{
		///set the check to false
		backOverBtn = false; 
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > defaultButtonPos->x && KeyManager::getManager()->mousePosition().x < defaultButtonPos->x + buttonSize.x &&
		KeyManager::getManager()->mousePosition().y  > defaultButtonPos->y && KeyManager::getManager()->mousePosition().y < defaultButtonPos->y + buttonSize.y)
	{
		restartOverBtn = true;
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Reset all buttons
			ResetButtons(); 
			setDownkey = false;
			setLeftkey = false;
			setRightkey = false;
			setUpkey = false;
			setGrapplekey  = false;
			setCannonUpkey = false;
			setCannonDownkey = false;
			setCannonLeftkey = false;
			setCannonRightkey = false;
			setAssignkey = false;
			setHelmUpkey = false;
			setHelmRightkey = false; 
			setHelmDownkey = false;
			setHelmLeftkey = false;
		}
	}
	///Check if mouse is not over the button image
	else
	{
		restartOverBtn = false;
		//backOverBtn = false; 
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > upBtnPos->x && KeyManager::getManager()->mousePosition().x < upBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > upBtnPos->y && KeyManager::getManager()->mousePosition().y < upBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			///Display text press a button
			stringUp = "Press a key";
			///Set the check for binding the ket to true
			setUpkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > downBtnPos->x && KeyManager::getManager()->mousePosition().x < downBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > downBtnPos->y && KeyManager::getManager()->mousePosition().y < downBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringDown = "Press a key";
			///Set the check for binding the ket to true
			setDownkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > leftBtnPos->x && KeyManager::getManager()->mousePosition().x < leftBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > leftBtnPos->y && KeyManager::getManager()->mousePosition().y < leftBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringLeft = "Press a key";
			///Set the check for binding the ket to true
			setLeftkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > rightBtnPos->x && KeyManager::getManager()->mousePosition().x < rightBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > rightBtnPos->y && KeyManager::getManager()->mousePosition().y < rightBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringRight = "Press a key";
			///Set the check for binding the ket to true
			setRightkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > grappleBtnPos->x && KeyManager::getManager()->mousePosition().x < grappleBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > grappleBtnPos->y && KeyManager::getManager()->mousePosition().y < grappleBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringGrapple = "Press a key";
			///Set the check for binding the ket to true
			setGrapplekey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > assignBtnPos->x && KeyManager::getManager()->mousePosition().x < assignBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > assignBtnPos->y && KeyManager::getManager()->mousePosition().y < assignBtnPos->y + smallbtnSize.y)
	{

		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringAssign = "Press a key";
			///Set the check for binding the ket to true
			setAssignkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > cannonUpBtnPos->x && KeyManager::getManager()->mousePosition().x < cannonUpBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > cannonUpBtnPos->y && KeyManager::getManager()->mousePosition().y < cannonUpBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringCannonUp = "Press a key";
			///Set the check for binding the ket to true
			setCannonUpkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > cannonDownBtnPos->x && KeyManager::getManager()->mousePosition().x < cannonDownBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > cannonDownBtnPos->y && KeyManager::getManager()->mousePosition().y < cannonDownBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringCannonDown = "Press a key";
			///Set the check for binding the ket to true
			setCannonDownkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > cannonLeftBtnPos->x && KeyManager::getManager()->mousePosition().x < cannonLeftBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > cannonLeftBtnPos->y && KeyManager::getManager()->mousePosition().y < cannonLeftBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringCannonLeft = "Press a key";
			///Set the check for binding the ket to true
			setCannonLeftkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > cannonRightBtnPos->x && KeyManager::getManager()->mousePosition().x < cannonRightBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > cannonRightBtnPos->y && KeyManager::getManager()->mousePosition().y < cannonRightBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringCannonRight = "Press a key";
			///Set the check for binding the ket to true
			setCannonRightkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > helmUpBtnPos->x && KeyManager::getManager()->mousePosition().x < helmUpBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > helmUpBtnPos->y && KeyManager::getManager()->mousePosition().y < helmUpBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringHelmUp = "Press a key";
			///Set the check for binding the ket to true
			setHelmUpkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > helmDownBtnPos->x && KeyManager::getManager()->mousePosition().x < helmDownBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > helmDownBtnPos->y && KeyManager::getManager()->mousePosition().y < helmDownBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringHelmDown = "Press a key";
			///Set the check for binding the ket to true
			setHelmDownkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > helmLeftBtnPos->x && KeyManager::getManager()->mousePosition().x < helmLeftBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > helmLeftBtnPos->y && KeyManager::getManager()->mousePosition().y < helmLeftBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringHelmLeft = "Press a key";
			///Set the check for binding the ket to true
			setHelmLeftkey = true; 
		}
	}
	///Check if mouse is over the button image
	if(KeyManager::getManager()->mousePosition().x  > helmRightBtnPos->x && KeyManager::getManager()->mousePosition().x < helmRightBtnPos->x + smallbtnSize.x &&
		KeyManager::getManager()->mousePosition().y  > helmRightBtnPos->y && KeyManager::getManager()->mousePosition().y < helmRightBtnPos->y + smallbtnSize.y)
	{
		///If the left mouse button has been clicked
		if(KeyManager::getManager()->mousePressed(KeyManager::left))
		{
			//Display text press a button
			stringHelmRight = "Press a key";
			///Set the check for binding the ket to true
			setHelmRightkey = true; 
		}
	}
	///If binding this key check is true
	if(setUpkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setGrapplekey = false;
		setAssignkey = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false; 
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setDownkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setUpkey = false;
		setLeftkey = false;
		setRightkey = false;
		setGrapplekey = false;
		setAssignkey = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 

	}
	///If binding this key check is true
	else if(setLeftkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setUpkey = false;
		setRightkey = false;
		setGrapplekey = false;
		setAssignkey = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setRightkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setGrapplekey = false;
		setUpkey = false;
		setAssignkey = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setGrapplekey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setAssignkey = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setAssignkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setCannonUpkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setAssignkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setCannonDownkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setAssignkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setCannonLeftkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setAssignkey = false;
		setCannonRightkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setCannonRightkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setAssignkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setHelmUpkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setAssignkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setHelmDownkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setAssignkey = false;
		setHelmUpkey = false;
		setHelmLeftkey = false;
		setHelmRightkey = false; 
	}
	///If binding this key check is true
	else if(setHelmLeftkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setAssignkey = false;
		setHelmUpkey = false;
		setHelmRightkey = false; 
		setHelmDownkey = false;
	}
	///If binding this key check is true
	else if(setHelmRightkey == true)
	{
		///Set all other checks to false so you don't 
		///bind the wrong key 
		setDownkey = false;
		setLeftkey = false;
		setRightkey = false;
		setUpkey = false;
		setGrapplekey  = false;
		setCannonUpkey = false;
		setCannonDownkey = false;
		setCannonLeftkey = false;
		setCannonRightkey = false;
		setAssignkey = false;
		setHelmUpkey = false;
		setHelmDownkey = false;
		setHelmLeftkey = false;
	}

	///Check the keys form 0 to 85 for presses
	for(int i =0; i < 85; i++)
	{   ///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setUpkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetMoveUpCommand((SDL_Scancode)i);
			///Save the new command in the txt file 
			//Control::getManager()->SaveCommands(0,i);
			///Display new button 
			stringUp = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setUpkey = false;
		}

		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setDownkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetMoveDownCommand((SDL_Scancode)i);
			///Display new button 
			stringDown = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setDownkey = false;
		}

		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setLeftkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetMoveLeftCommand((SDL_Scancode)i);
			///Display new button 
			stringLeft = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setLeftkey = false;
		}

		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setRightkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetMoveRightCommand((SDL_Scancode)i);
			///Display new button 
			stringRight = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setRightkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setGrapplekey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetGrappleCommand((SDL_Scancode)i);
			///Display new button 
			stringGrapple = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setGrapplekey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setAssignkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetAssignCommand((SDL_Scancode)i);
			///Display new button 
			stringAssign = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setAssignkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setCannonUpkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetCannonMoveUp((SDL_Scancode)i);
			///Display new button 
			stringCannonUp = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setCannonUpkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setCannonDownkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetCannonMoveDown((SDL_Scancode)i);
			///Display new button 
			stringCannonDown = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setCannonDownkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setCannonLeftkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetCannonMoveLeft((SDL_Scancode)i);
			///Display new button 
			stringCannonLeft = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setCannonLeftkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setCannonRightkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetCannonMoveRight((SDL_Scancode)i);
			///Display new button 
			stringCannonRight = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setCannonRightkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setHelmUpkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetHelmMoveUp((SDL_Scancode)i);
			///Display new button 
			stringHelmUp = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setHelmUpkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setHelmDownkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetHemlMoveDown((SDL_Scancode)i);
			///Display new button 
			stringHelmDown = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setHelmDownkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setHelmLeftkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetHelmMoveLeft((SDL_Scancode)i);
			///Display new button 
			stringHelmLeft = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setHelmLeftkey = false;
		}
		///Get the key that was pressed
		if(KeyManager::getManager()->keyPressed((SDL_Scancode)i) && setHelmRightkey)
		{
			///Set the command button the the key that was pressed 
			Control::getManager()->SetHelmMoveRight((SDL_Scancode)i);
			///Display new button 
			stringHelmRight = SDL_GetScancodeName((SDL_Scancode)i);
			///Set the check for binding the key to false
			setHelmRightkey = false;
		}
	}	



}
///Draw the options menu
void Menu::DrawOptionsMenu(SDL_Renderer* renderer)
{
	///Draw default button  at this position and size
	defaultButtonPos->x = 1000; 
	defaultButtonPos->y = 500; 
	defaultButtonPos->w = buttonSize.x;
	defaultButtonPos->h = buttonSize.y;

	///Draw back button at this position and size
	backButtonPos->x = 1000; 
	backButtonPos->y = 600; 
	backButtonPos->w = buttonSize.x;
	backButtonPos->h = buttonSize.y;

	///Draw up button at this position and size
	upBtnPos->x = 100; 
	upBtnPos->y = 240; 
	upBtnPos->w = smallbtnSize.x;
	upBtnPos->h = smallbtnSize.y;

	///Draw down button at this position and size
	downBtnPos->x = 100; 
	downBtnPos->y = 360; 
	downBtnPos->w = smallbtnSize.x;
	downBtnPos->h = smallbtnSize.y;

	///Draw left button at this position and size
	leftBtnPos->x = 100; 
	leftBtnPos->y = 500; 
	leftBtnPos->w = smallbtnSize.x;
	leftBtnPos->h = smallbtnSize.y;

	///Draw right button at this position and size
	rightBtnPos->x = 100; 
	rightBtnPos->y = 640; 
	rightBtnPos->w = smallbtnSize.x;
	rightBtnPos->h = smallbtnSize.y;

	///Draw grapple button at this position and size
	grappleBtnPos->x = 400; 
	grappleBtnPos->y = 240; 
	grappleBtnPos->w = smallbtnSize.x;
	grappleBtnPos->h = smallbtnSize.y;

	///Draw assign button at this position and size
	assignBtnPos->x = 400; 
	assignBtnPos->y = 360; 
	assignBtnPos->w = smallbtnSize.x;
	assignBtnPos->h = smallbtnSize.y;

	///Draw cannon up button at this position and size
	cannonUpBtnPos->x = 400; 
	cannonUpBtnPos->y = 500; 
	cannonUpBtnPos->w = smallbtnSize.x;
	cannonUpBtnPos->h = smallbtnSize.y;

	///Draw cannon down button at this position and size
	cannonDownBtnPos->x = 400; 
	cannonDownBtnPos->y = 640; 
	cannonDownBtnPos->w = smallbtnSize.x;
	cannonDownBtnPos->h = smallbtnSize.y;

	///Draw cannon letf button at this position and size
	cannonLeftBtnPos->x = 700; 
	cannonLeftBtnPos->y = 240; 
	cannonLeftBtnPos->w = smallbtnSize.x;
	cannonLeftBtnPos->h = smallbtnSize.y;

	///Draw cannon right button at this position and size
	cannonRightBtnPos->x = 700; 
	cannonRightBtnPos->y = 360; 
	cannonRightBtnPos->w = smallbtnSize.x;
	cannonRightBtnPos->h = smallbtnSize.y;

	///Draw helm up button at this position and size
	helmUpBtnPos->x = 1000; 
	helmUpBtnPos->y = 240; 
	helmUpBtnPos->w = smallbtnSize.x;
	helmUpBtnPos->h = smallbtnSize.y;

	///Draw helm down button at this position and size
	helmDownBtnPos->x = 1000; 
	helmDownBtnPos->y = 360; 
	helmDownBtnPos->w = smallbtnSize.x;
	helmDownBtnPos->h = smallbtnSize.y;

	///Draw helm left button at this position and size
	helmLeftBtnPos->x = 700; 
	helmLeftBtnPos->y = 500; 
	helmLeftBtnPos->w = smallbtnSize.x;
	helmLeftBtnPos->h = smallbtnSize.y;

	///Draw helm right button at this position and size
	helmRightBtnPos->x = 700; 
	helmRightBtnPos->y = 640; 
	helmRightBtnPos->w = smallbtnSize.x;
	helmRightBtnPos->h = smallbtnSize.y;

	///Draw a background at this position and size
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->optionMenu->getTexture(),nullptr,screenPos,0,nullptr,SDL_FLIP_NONE);
	///If the mouse is over the button
	if(backOverBtn == false)
	{
		///Draw the highlighted button
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->backBtn->getTexture(),nullptr,backButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///if the mouse is not over the button
	else
	{   
		///Draw the fefault button
		SDL_RenderCopyEx(renderer,TextureManager::getManager()->backBtn2->getTexture(),nullptr,backButtonPos,0,nullptr,SDL_FLIP_NONE);
	}
	///Draw defult button
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->defaultBtn->getTexture(),nullptr,defaultButtonPos,0,nullptr,SDL_FLIP_NONE);

	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->upBtn->getTexture(),nullptr,upBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->downBtn->getTexture(),nullptr,downBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->leftBtn->getTexture(),nullptr,leftBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->rightBtn->getTexture(),nullptr,rightBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->grappleBtn->getTexture(),nullptr,grappleBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->assignBtn->getTexture(),nullptr,assignBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->cannonUpBtn->getTexture(),nullptr,cannonUpBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->cannonDownBtn->getTexture(),nullptr,cannonDownBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->cannonLeftBtn->getTexture(),nullptr,cannonLeftBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->cannonRightBtn->getTexture(),nullptr,cannonRightBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->helmUpBtn->getTexture(),nullptr,helmUpBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->helmDownBtn->getTexture(),nullptr,helmDownBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->helmLeftBtn->getTexture(),nullptr,helmLeftBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Draw button 
	SDL_RenderCopyEx(renderer,TextureManager::getManager()->helmRightBtn->getTexture(),nullptr,helmRightBtnPos,0,nullptr,SDL_FLIP_NONE);
	///Set the text position
	textPosUp->x = 230;
	textPosUp->y = 240;
	///Draw text on screen
	DrawTextOnScreen(messageUp,textUp,textPosUp,stringUp,renderer);
	///Set the text position
	textPosDown->x = 230;
	textPosDown->y = 360;
	///Draw text on screen
	DrawTextOnScreen(messageDown,textDown,textPosDown,stringDown,renderer);
	///Set the text position
	textPosLeft->x = 230;
	textPosLeft->y = 500;
	///Draw text on screen
	DrawTextOnScreen(messageLeft,textLeft,textPosLeft,stringLeft,renderer);
	///Set the text position
	textPosRight->x = 230;
	textPosRight->y = 640;
	///Draw text on screen
	DrawTextOnScreen(messageRight,textRight,textPosRight,stringRight,renderer);
	///Set the text position
	textPosGrapple->x = 530;
	textPosGrapple->y = 240;
	///Draw text on screen
	DrawTextOnScreen(messageGrapple,textGrapple,textPosGrapple,stringGrapple,renderer);
	///Set the text position
	textPosAssign->x = 530;
	textPosAssign->y = 360;
	///Draw text on screen
	DrawTextOnScreen(messageAssign,textAssign,textPosAssign,stringAssign,renderer);
	///Set the text position
	textPosCannonUp->x = 530;
	textPosCannonUp->y = 500;
	///Draw text on screen
	DrawTextOnScreen(messageCannonUp,textCannonUp,textPosCannonUp,stringCannonUp,renderer);
	///Set the text position
	textPosCannonDown->x = 530;
	textPosCannonDown->y = 640;
	///Draw text on screen
	DrawTextOnScreen(messageCannonDown,textCannonDown,textPosCannonDown,stringCannonDown,renderer);
	///Set the text position
	textPosCannonLeft->x = 830;
	textPosCannonLeft->y = 240;
	///Draw text on screen
	DrawTextOnScreen(messageCannonLeft,textCannonLeft,textPosCannonLeft,stringCannonLeft,renderer);
	///Set the text position
	textPosCannonRight->x = 830;
	textPosCannonRight->y = 360;
	///Draw text on screen
	DrawTextOnScreen(messageCannonRight,textCannonRight,textPosCannonRight,stringCannonRight,renderer);
	///Set the text position
	textPosHelmUp->x = 1130;
	textPosHelmUp->y = 240;
	///Draw text on screen
	DrawTextOnScreen(messageHelmUp,textHelmUp,textPosHelmUp,stringHelmUp,renderer);
	///Set the text position
	textPosHelmDown->x = 1130;
	textPosHelmDown->y = 360;
	///Draw text on screen
	DrawTextOnScreen(messageHelmDown,textHelmDown,textPosHelmDown,stringHelmDown,renderer);
	///Set the text position
	textPosHelmLeft->x = 830;
	textPosHelmLeft->y = 500;
	///Draw text on screen
	DrawTextOnScreen(messageHelmLeft,textHelmLeft,textPosHelmLeft,stringHelmLeft,renderer);
	///Set the text position
	textPosHelmRight->x = 830;
	textPosHelmRight->y = 640;
	///Draw text on screen
	DrawTextOnScreen(messageHelmRight,textHelmRight,textPosHelmRight,stringHelmRight,renderer);

}

