#include "GUIManager.h"

GUIManager* GUIManager::me;

GUIManager* GUIManager::getManager()
{
	if(!me)
	{
		me=new GUIManager();
	}
	return me;
}

GUIManager::GUIManager(void)
{
	uiElements = new vector<HUDElement*>();
	uiElements->push_back( new ShipIndicator(1216,64));
	notorietyIndicator = new NotorietyIndicator(64,500);
	minimap = new Minimap(128,646);
	uiElements->push_back( new HatMenu(32,32));
	uiElements->push_back(new UnitCommandIndicator(1216,650));
	goldIndicator = new GoldIndicator(640,64);
	shopScreen = new Shop(640,380);
	bankScreen= new BankGUI(640,320);
}


GUIManager::~GUIManager(void)
{
	vector<HUDElement*>::iterator hudIter = uiElements->begin();
	for(;hudIter!=uiElements->end();)
	{
		delete *hudIter;
		hudIter = uiElements->erase(hudIter);
	}
	delete uiElements;
	delete shipIndicator;
	delete notorietyIndicator;
	delete minimap;
	delete goldIndicator;
	delete commandIndicator;
	delete shopScreen;
	delete bankScreen;
}

void GUIManager::createGUI()
{
}

void GUIManager::update(float timeElapsed)
{
	if(KeyManager::getManager()->mousePressed(KeyManager::mouseButtons::left))
	{
		Vector2f mousePos = KeyManager::getManager()->mousePosition();
		/*
		= hatMenu->getPos();
		if(sqrt((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y))<hatMenu->getRadius())
			hatMenu->menu();

		//click ship menu
		MenuPos = shipIndicator->getIconPos();
		if(sqrt((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y))<shipIndicator->getIconRadius())
			shipIndicator->menu();

		//click command menu
		MenuPos = commandIndicator->getIconPos();
		if(sqrt((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y))<commandIndicator->getIconRadius())
			commandIndicator->menu();

		//check if player is clicking commands if command menu is open
		if(commandIndicator->isOpen())
		{
			//check board command
			MenuPos = commandIndicator->getBoardIconPos();
			if(sqrt((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y))<commandIndicator->getIconRadius())
			{

			}

			//check abandon command
			MenuPos = commandIndicator->getAbandonIconPos();
			if(sqrt((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y))<commandIndicator->getIconRadius())
			{

			}

			//check loot command
			MenuPos = commandIndicator->getLootIconPos();
			if(sqrt((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y))<commandIndicator->getIconRadius())
			{

			}
		}
		/*
		if(shopScreen)
		{
			if(shopScreen->getAlive())
			{
				shopScreen->update(timeElapsed,mousePos.x,mousePos.y);
			}
		}*/
		if(shopScreen->getAlive())
		{
			shopScreen->update(timeElapsed,mousePos.x,mousePos.y,((Station*)ObjectManager::getManager()->selected->getStation()), ((HatMenu*)uiElements->at(1)));
		}
		if(bankScreen->getMenu())
		{
			bankScreen->update(timeElapsed);
		}
	}
	//click hat menu
	Vector2f MenuPos;
	vector<HUDElement*>::iterator hudIter = uiElements->begin();
	for(;hudIter!=uiElements->end();hudIter++)
	{
		if(KeyManager::getManager()->mousePressed(KeyManager::mouseButtons::left))
		{
			Vector2f mousePos = KeyManager::getManager()->mousePosition();
			MenuPos = (*hudIter)->getPos();
			if((MenuPos.x - mousePos.x)*(MenuPos.x - mousePos.x) + (MenuPos.y - mousePos.y)*(MenuPos.y - mousePos.y)<((*hudIter)->getSize().x/2)*((*hudIter)->getSize().x/2))
			{
				(*hudIter)->menu();
			}
		}
		(*hudIter)->update(timeElapsed);
	}
	//hatMenu->update(timeElapsed);
	//shipIndicator->update(timeElapsed);
	//commandIndicator->update(timeElapsed);

	
}

void GUIManager::draw(SDL_Renderer* renderer, Vector2f offset)
{
	//shipIndicator->draw(renderer);
	notorietyIndicator->draw(renderer);
	minimap->draw(renderer);
	//hatMenu->draw(renderer);
	goldIndicator->draw(renderer);
	//commandIndicator->draw(renderer);
	vector<HUDElement*>::iterator hudIter = uiElements->begin();
	for(;hudIter!=uiElements->end();hudIter++)
	{
		(*hudIter)->draw(renderer);
	}

	if(ObjectManager::getManager()->selected)
	{
		minimap->drawStations(renderer,ObjectManager::getManager()->stations,ObjectManager::getManager()->selected->getPos());
	}

	if(shopScreen->getAlive())
	{
		shopScreen->draw(renderer);
	}
	if(bankScreen->getMenu())
	{
		bankScreen->draw(renderer);
	}
}