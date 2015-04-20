#pragma once
#ifndef CONTROL_H
#define CONTROL_H
#include "SDL.h"

using namespace std;

class Control 
{
private:
	///public control object
	static Control* me;
	///The key that controls the up movement command
	SDL_Scancode moveUpKey; 
	///The key that controls the down movement command
	SDL_Scancode moveDownKey;
	///The key that controls the left movement command
	SDL_Scancode moveLeftKey;
	///The key that controls the right movement command
	SDL_Scancode moveRightKey;
	///The key that controls the grapple command
	SDL_Scancode grapppleKey;
	///The key that controls the assign command
	SDL_Scancode assignKey;
	///The key that controls the up movement command
	SDL_Scancode cannonMoveUp; 
	///The key that controls the down movement command
	SDL_Scancode cannonMoveDown;
	///The key that controls the left movement command
	SDL_Scancode cannonMoveLeft;
	///The key that controls the right movement command
	SDL_Scancode cannonMoveRight;
		///The key that controls the up movement command
	SDL_Scancode helmMoveUp; 
	///The key that controls the down movement command
	SDL_Scancode helmMoveDown;
	///The key that controls the left movement command
	SDL_Scancode helmMoveLeft;
	///The key that controls the right movement command
	SDL_Scancode helmMoveRight;


public:
	///Init
	Control(void);
	///Destroy
	~Control();
	/// the public keyManager object
	static Control* getManager();
	///Set the button that uses the up command
	void SetMoveUpCommand(SDL_Scancode currentKey){ moveUpKey = currentKey;};
	///Get the button used for the up command
	SDL_Scancode GetMoveUpCommand(){return moveUpKey;};
	///Set the button that uses the up command
	void SetMoveDownCommand(SDL_Scancode currentKey){ moveDownKey = currentKey;};
	///Get the button used for the up command
	SDL_Scancode GetMoveDownCommand(){return moveDownKey;};
	///Set the button that uses the up command
	void SetMoveLeftCommand(SDL_Scancode currentKey){ moveLeftKey = currentKey;};
	///Get the button used for the up command
	SDL_Scancode GetMoveLeftCommand(){return moveLeftKey;};
	///Set the button that uses the up command
	void SetMoveRightCommand(SDL_Scancode currentKey){ moveRightKey = currentKey;};
	///Get the button used for the up command	
	SDL_Scancode GetMoveRightCommand(){return moveRightKey;};
	///Set the button that uses the grapple command
	void SetGrappleCommand(SDL_Scancode currentKey){ grapppleKey = currentKey;};
	///Get the button used for the grapple command
	SDL_Scancode GetGrappleCommand(){return grapppleKey;};
	///Set the button that uses the assign command
	void SetAssignCommand(SDL_Scancode currentKey){ assignKey = currentKey;};
	///Get the button used for the assign command	
	SDL_Scancode GetAssignCommand(){return assignKey;};
	///Set the button that uses the up command for the cannon
	void SetCannonMoveUp(SDL_Scancode currentKey){ cannonMoveUp = currentKey;};
	///Get the button used for the up command for the cannon
	SDL_Scancode GetCannonMoveUp(){return cannonMoveUp;};
	///Set the button that uses the up command for the cannon
	void SetCannonMoveDown(SDL_Scancode currentKey){ cannonMoveDown = currentKey;};
	///Get the button used for the up command for the cannon
	SDL_Scancode GetCannonMoveDown(){return cannonMoveDown;};
	///Set the button that uses the up command for the cannon
	void SetCannonMoveLeft(SDL_Scancode currentKey){ cannonMoveLeft = currentKey;};
	///Get the button used for the up command for the cannon
	SDL_Scancode GetCannonMoveLeft(){return cannonMoveLeft;};
	///Set the button that uses the up command for the cannon
	void SetCannonMoveRight(SDL_Scancode currentKey){ cannonMoveRight = currentKey;};
	///Get the button used for the up command for the cannon
	SDL_Scancode GetCannonMoveRight(){return cannonMoveRight;};
	///Set the button that uses the up command for the helm
	void SetHelmMoveUp(SDL_Scancode currentKey){ helmMoveUp = currentKey;};
	///Get the button used for the up command for the helm
	SDL_Scancode GetHelmMoveUp(){return helmMoveUp;};
	///Set the button that uses the up command for the helm
	void SetHemlMoveDown(SDL_Scancode currentKey){ helmMoveDown = currentKey;};
	///Get the button used for the up command for the helm
	SDL_Scancode GetHelmMoveDown(){return helmMoveDown;};
	///Set the button that uses the up command for the helm
	void SetHelmMoveLeft(SDL_Scancode currentKey){ helmMoveLeft = currentKey;};
	///Get the button used for the up command for the helm
	SDL_Scancode GetHelmMoveLeft(){return helmMoveLeft;};
	///Set the button that uses the up command for the helm
	void SetHelmMoveRight(SDL_Scancode currentKey){ helmMoveRight = currentKey;};
	///Get the button used for the up command for the helm
	SDL_Scancode GetHelmMoveRight(){return helmMoveRight;};
	///Save players command buttons to a file
	void SaveCommands(); 
	SDL_Scancode SetCommands(int lineNo);
	void GetDeaultCommands();
};
#endif