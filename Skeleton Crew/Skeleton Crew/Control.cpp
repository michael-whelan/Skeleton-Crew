#include "Control.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>

Control* Control::me;

Control* Control::getManager()
{
	if(!me)
	{
		me=new Control();
	}
	return me;
	
}


Control::Control(void)
{
	moveUpKey = SetCommands(0);
	moveDownKey = SetCommands(1);
	moveLeftKey = SetCommands(2);
	moveRightKey = SetCommands(3);
	grapppleKey = SetCommands(4); 
	assignKey = SetCommands(5);
	cannonMoveUp = SetCommands(6);
	cannonMoveDown = SetCommands(7);
	cannonMoveLeft = SetCommands(8);
	cannonMoveRight = SetCommands(9);
	helmMoveUp = SetCommands(10);
	helmMoveDown = SetCommands(11);
	helmMoveLeft = SetCommands(12);
	helmMoveRight = SetCommands(13);
}

Control::~Control()
{

}

void Control::SaveCommands()
{
	ofstream myfile ("commands.txt");
	if (myfile.is_open())
	{
		myfile<<(int) GetMoveUpCommand()<<endl;
		myfile<<(int) GetMoveDownCommand()<<endl;
		myfile<<(int) GetMoveLeftCommand()<<endl;
		myfile<<(int) GetMoveRightCommand()<<endl;
		myfile<<(int) GetGrappleCommand()<<endl;
		myfile<<(int) GetAssignCommand()<<endl;
		myfile<<(int) GetCannonMoveUp()<<endl;
		myfile<<(int) GetCannonMoveDown()<<endl;
		myfile<<(int) GetCannonMoveLeft()<<endl;
		myfile<<(int) GetCannonMoveRight()<<endl;
		myfile<<(int) GetHelmMoveUp()<<endl;
		myfile<<(int) GetHelmMoveDown()<<endl;
		myfile<<(int) GetHelmMoveLeft()<<endl;
		myfile<<(int) GetHelmMoveRight()<<endl;
		myfile.close();
	}
	else cout << "Unable to open file";
}

SDL_Scancode Control::SetCommands(int lineNum)
{
  string line;
  ifstream myfile ("commands.txt");
  int keyCode = 0; 
  SDL_Scancode command;
  if (myfile.is_open())
  {
	   for (int lineno = 0; getline (myfile,line) && lineno < 14; lineno++)
	   {
			if (lineno == lineNum)
			{
				keyCode = atoi(line.c_str());
				return command = (SDL_Scancode)keyCode;
			}
	   }
	myfile.close();
	
  }

  else cout << "Unable to open file"; 
}

void Control::GetDeaultCommands()
{
	ifstream listOfCommandsfile("commandsDefault.txt");
    ofstream destinationfile("commands.txt");
	string line;

	if (destinationfile.is_open())
	{
		for(int i = 0; i < 15; i++)
		{
			std::getline(listOfCommandsfile, line);
			destinationfile << line << '\n'; 
		}
	 destinationfile.close();
  }

	moveUpKey = SetCommands(0);
	moveDownKey = SetCommands(1);
	moveLeftKey = SetCommands(2);
	moveRightKey = SetCommands(3);
	grapppleKey = SetCommands(4); 
	assignKey = SetCommands(5);
	cannonMoveUp = SetCommands(6);
	cannonMoveDown = SetCommands(7);
	cannonMoveLeft = SetCommands(8);
	cannonMoveRight = SetCommands(9);
	helmMoveUp = SetCommands(10);
	helmMoveDown = SetCommands(11);
	helmMoveLeft = SetCommands(12);
	helmMoveRight = SetCommands(13);
}