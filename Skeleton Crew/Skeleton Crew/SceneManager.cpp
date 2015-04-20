#include "SceneManager.h"

SceneManager* SceneManager::me;
SceneManager* SceneManager::getManager()
{
	if(!me)
	{
		me= new SceneManager();
	}
	return me;
}


SceneManager::SceneManager(void)
{
	loadedGame = false;
	Loadedstations=new vector<Station*>(0);
	LoadedCrew=new vector<Crew*>(0);
	LoadedUnit=new vector<EnemyCrew*>(0);
	menu = new Menu();
	game = new Game();
}


SceneManager::~SceneManager(void)
{
	delete menu;
	delete game;
}


void SceneManager::saveGame()
{
	ofstream file;
	file.open("save.txt");
	
	if(file.is_open())
	{
		file<< game->getGold()<<endl;
		file<< ObjectManager::getManager()->hatsTotal->at(0)<<',';
		file<< ObjectManager::getManager()->hatsTotal->at(1)<<',';
		file<< ObjectManager::getManager()->hatsTotal->at(2)<<',';
		file<< ObjectManager::getManager()->hatsTotal->at(3)<<',';
		file<< ObjectManager::getManager()->hatsTotal->at(4)<<',';
		file<< ObjectManager::getManager()->hatsTotal->at(5)<<endl;
		for(int i = 0; i <ObjectManager::getManager()->stations->size(); i++)
		{
			file<< ObjectManager::getManager()->stations->at(i)->getEntity()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getLvl()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getPos().x<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getPos().y<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getGold()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getHealthMultiply()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getReloadMultiply()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getCrowsMultiply()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getSpeedMultiply()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getTurningMultiply()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getDmgMultiply()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getAssignedCrew()->size()<<',';
			file<< ObjectManager::getManager()->stations->at(i)->getAssignedUnits()->size()<<endl;
		}
		file.close();
	}						
}
void SceneManager::loadGame()
{
	//if(menu->getLoadBtn()){
		hatsTotal = new vector<int>(0);
		ifstream file("save.txt");
		string b = "";
		int i =0;
		int i2 = 0;
		float f = 0;
		vector<string> list;
		int iter=0;
		string tokenEnt,tokenLvl,tokenX,tokenY,tokenG,tokenH,tokenCan,tokenCrows,tokenSail,tokenRud,tokenCanB,
			tokenH0,tokenH1,tokenH2,tokenH3,tokenH4,tokenH5,tokenCrew,tokenUnits;
		if(file.is_open())
		{
			while(getline(file,b))
			{
				//getline(file,
				//int temp;
				//istringstream buffer(b);
				//buffer>>temp;
				list.push_back(b);
				//buffer>>list.at(iter);
				//iter++;
				if(iter >0){
					string s = list.at(iter);
					tokenEnt = s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenLvl = s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenX =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenY =  s.substr(0,s.find(','));
					s.erase(0,s.find(',')+1);
					tokenG =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenH = s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenCan =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenCrows =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenSail =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenRud =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenCanB =  s.substr(0,s.find(','));
					s.erase(0,s.find(",")+1);
					tokenCrew =  s.substr(0,s.find(','));
					s.erase(0,s.find(',')+1);
					tokenUnits =  s.substr(0,s.find(','));
					s.erase(0,s.find(',')+1);
					istringstream bufferX(tokenX);
					istringstream bufferY(tokenY);
					bufferX>>i;
					bufferY>>i2;
					istringstream bufferLvl(tokenLvl);
					bufferLvl>>f;
					if(atoi(tokenEnt.c_str()) &Entity::entityType::bank)
					{
						Loadedstations->push_back( ObjectFactory::SpawnStation(i,i2,Entity::entityType::bank,1));
					}
					else if(atoi(tokenEnt.c_str()) &Entity::entityType::shipyard)
					{
						Loadedstations->push_back( ObjectFactory::SpawnStation(i,i2,Entity::entityType::shipyard,1));
					}
					else if(atoi(tokenEnt.c_str()) &Entity::entityType::ship)
					{
						Loadedstations->push_back( ObjectFactory::SpawnStation(i,i2,Entity::entityType::ship,f));
					}
					else if(atoi(tokenEnt.c_str()) &Entity::entityType::seacreatures)
					{
						Loadedstations->push_back( ObjectFactory::SpawnStation(i,i2,Entity::entityType::seacreatures,1));
					}
					else// if(atoi(tokenEnt.c_str()) &Entity::entityType::island)
					{
						Loadedstations->push_back( ObjectFactory::SpawnStation(i,i2,Entity::entityType::island,1));
					}
					for(int temp =0; temp < atoi(tokenCrew.c_str()); temp++ )
					{
						Crew* myMainMan = new Crew(Loadedstations->at(iter-1)->getPos().x,Loadedstations->at(iter-1)->getPos().y,Loadedstations->at(iter-1),Unit::states::noneState);
						Loadedstations->at(iter-1)->getAssignedCrew()->push_back(myMainMan);
						LoadedCrew->push_back(myMainMan);
					}
					for(int temp =0; temp < atoi(tokenUnits.c_str()); temp++ )
					{
						EnemyCrew* myMainMan = new EnemyCrew(Loadedstations->at(iter-1)->getPos().x,Loadedstations->at(iter-1)->getPos().y,selectUnitType(),Loadedstations->at(iter-1));
						Loadedstations->at(iter-1)->getAssignedUnits()->push_back(myMainMan);
						LoadedUnit->push_back(myMainMan);
					}
					istringstream buffer1(tokenG);
					buffer1>>i;
					Loadedstations->at(iter-1)->setGold(i);//
					istringstream buffer2(tokenH);
					buffer2>>f;
					Loadedstations->at(iter-1)->setHealthMultiply(f);//
					istringstream buffer3(tokenCan);
					buffer3>>f;
					Loadedstations->at(iter-1)->setReloadMultiply(f);//
					istringstream buffer4(tokenCrows);
					buffer4>>f;
					Loadedstations->at(iter-1)->setCrowsMultiply(f);//
					istringstream buffer5(tokenSail);
					buffer5>>f;
					Loadedstations->at(iter-1)->setSpeedMultiply(f);//
					istringstream buffer6(tokenRud);
					buffer6>>f;
					Loadedstations->at(iter-1)->setTurningMultiply(f);//
					istringstream buffer7(tokenCanB);
					buffer7>>f;
					Loadedstations->at(iter-1)->setDmgMultiply(f);//
				}
				iter++;
			}
			///0=bank; 1 = 
			//i = list.at(0);
			istringstream buffer( list.at(0));
			buffer >>i;
	
			game->loadGame(i);
			string st = list.at(1);

			tokenH0 =  st.substr(0,st.find(','));
			st.erase(0,st.find(",")+1);
			tokenH1 =  st.substr(0,st.find(','));
			st.erase(0,st.find(",")+1);
			tokenH2 =  st.substr(0,st.find(','));
			st.erase(0,st.find(",")+1);
			tokenH3 =  st.substr(0,st.find(','));
			st.erase(0,st.find(",")+1);
			tokenH4 =  st.substr(0,st.find(','));
			st.erase(0,st.find(",")+1);
			tokenH5 =  st.substr(0,st.find(','));
			st.erase(0,st.find(",")+1);
		

			//ObjectManager::getManager()->hatsTotal->clear();
			istringstream bufferH0(tokenH0);
			bufferH0>>i;
			hatsTotal->push_back(i);
			istringstream bufferH1(tokenH1);
			bufferH1>>i;
			hatsTotal->push_back(i);
			istringstream bufferH2(tokenH2);
			bufferH2>>i;
			hatsTotal->push_back(i);
			istringstream bufferH3(tokenH3);
			bufferH3>>i;
			hatsTotal->push_back(i);
			istringstream bufferH4(tokenH4);
			bufferH4>>i;
			hatsTotal->push_back(i);
			istringstream bufferH5(tokenH5);
			bufferH5>>i;
			hatsTotal->push_back(i);

			menu->setLoadMsg("Load Successful");
			menu->successLoad=true;
			loadedGame = true;
		}
		else 
		{
			menu->setLoadMsg("No Save File Found");
			menu->successLoad=false;
			loadedGame = false;
		}
		//menu->setLoadBtn(false);
	//}
}

Entity::entityType SceneManager::selectUnitType()
{
	int unitT = rand() %((int)2) -0;

	if(unitT == 1)
	{
		return Entity::entityType::navy;
	}
	return Entity::entityType::pirate;


}

void SceneManager::update(float timeElapsed)
{
	if(menu->getLoadBtn())
	{
		menu->setLoadedGame(false);
		loadGame();
		menu->setLoadBtn(false);
	}
	if(menu->gameState == menu->state::inGame)
	{
		if(loadedGame)
		{
			ObjectManager::getManager()->stations->clear();
			ObjectManager::getManager()->stations->insert(ObjectManager::getManager()->stations->end(),Loadedstations->begin(),Loadedstations->end());
			ObjectManager::getManager()->crew->clear();
			ObjectManager::getManager()->crew->insert(ObjectManager::getManager()->crew->end(),LoadedCrew->begin(),LoadedCrew->end());
			ObjectManager::getManager()->selected = ObjectManager::getManager()->crew->at(0);

			ObjectManager::getManager()->units->clear();
			ObjectManager::getManager()->units->insert(ObjectManager::getManager()->units->end(),LoadedUnit->begin(),LoadedUnit->end());

			((HatMenu*)GUIManager::getManager()->getHatMenu())->setSM(hatsTotal->at(0));
			((HatMenu*)GUIManager::getManager()->getHatMenu())->setPO(hatsTotal->at(1));
			((HatMenu*)GUIManager::getManager()->getHatMenu())->setCPO(hatsTotal->at(2));
			((HatMenu*)GUIManager::getManager()->getHatMenu())->setLtn(hatsTotal->at(3));
			((HatMenu*)GUIManager::getManager()->getHatMenu())->setCpt(hatsTotal->at(4));
			((HatMenu*)GUIManager::getManager()->getHatMenu())->setAdm(hatsTotal->at(5));
			
			loadedGame=false;
		}
		game->update(timeElapsed);
		if(ObjectManager::getManager()->crew->size() < 1)
		{
			menu->gameState = menu->state::deathScreen;
		}
	}
	else
	{
		menu->update(timeElapsed);
	}
}

void SceneManager::draw(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
	if(menu->gameState == menu->state::inGame)
	{
		game->draw(renderer);
	}
	else
	{
		menu->draw(renderer);
	}
	SDL_RenderPresent(renderer);
}