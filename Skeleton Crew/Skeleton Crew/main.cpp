#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "SDL.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <ctime>
#include "SDL_ttf.h"
#include "SDL_timer.h"
#include <vector>
#include "SceneManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include <chrono>
#include <winsock2.h>
#include <windows.h>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")

//Screen dimension constants 
//The window we'll be rendering to 
SDL_Window* window = nullptr; 
//Event handler 
SDL_Event eHandler;
//The window renderer 
SDL_Renderer* renderer = nullptr; 
//Current displayed texture 
SDL_Rect stretchRect; 

//Starts up SDL and creates window 
bool init(); 
//Loads media 
bool loadMedia(); 
//Frees media and shuts down SDL 
void close();
SDL_Texture* loadTexture( std::string path );

using namespace std;
using namespace std::chrono;



bool init() 
{ 
	//Initialization flag 
	bool success = true; 
	int screenWidth=1280;
	int screenHeight=720;
	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = screenWidth; 
	stretchRect.h = screenHeight;


	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else 
	{  
		if(SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else 
		{  
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
			{
				printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				SoundManager::getManager()->sound = false;
			}

			//Set texture filtering to linear
			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			{
				printf( "Warning: Linear texture filtering not enabled!" );
			}
			window = SDL_CreateWindow( "Skeleton Pirates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN ); 
			if( window == nullptr )
			{
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 
				success = false; 
			} 
			else 
			{ 
				//Create renderer for window 
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
				if( renderer == nullptr ) 
				{ 
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
					success = false;
				} 
				else 
				{ 
					//Initialize renderer color 
					SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
					//Initialize PNG loading 
					int imgFlags = IMG_INIT_PNG; 
					if( !( IMG_Init( imgFlags ) & imgFlags  ) ) 
					{ 
						string a = IMG_GetError();
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
						success = false; 
					} 
				} 
			}
			//intialise truetype font for writing purposes
			if(TTF_Init() == -1)
			{
				return false;
			}
		}
	} 
	return success; 
}



SDL_Texture* loadTexture( std::string path ) 
{ 
	//The final texture 
	SDL_Texture* newTexture = nullptr; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else 
	{
		//Create texture from surface pixels 
		//newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		if( newTexture == nullptr ) 
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return newTexture; 
}





void close() 
{ 
	//Free loaded image 
	//Destroy window 
	SDL_DestroyRenderer( renderer ); 
	SDL_DestroyWindow( window ); 
	window = nullptr; 
	renderer = nullptr; 
	//Quit SDL subsystems 
	IMG_Quit(); 
	SDL_Quit();

}

void get_Website(string word)
{
    string base_URL = "http://twitter.com/home?status=";
    string search_URL = "dummy";
    search_URL = base_URL + word;

    cout << "Searching for: \"" << word << "\"\n";

	ShellExecuteA(0, "open", search_URL.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}


int main( int argc, char* args[] ) 
{ 
	bool QUIT = false;
	if( !init() )
	{ 
		printf( "Failed to initialize!\n" ); 
	} 
	else 
	{
		//milliseconds start = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
		std::clock_t mClock;
		int min = 1000;
		mClock = std::clock();
		//Load media 
		if( !loadMedia() )	
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			srand (time(0));
			bool run = true;
			while(run)
			{

				//if(((std::clock()-mClock)/(double)CLOCKS_PER_SEC) >= 1.0/480.0)
				//milliseconds num =  duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch())-start;
				std::clock_t num = std::clock()-mClock;
				//float time = num.count()/1000.0f;
				float time = num/1000.0f;

				if(time >= 1.0f/60.0f)
				{
					//start = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
					mClock = std::clock();
					KeyManager::getManager()->Update(eHandler);


					SceneManager::getManager()->update(time);
					SceneManager::getManager()->draw(renderer);
					if(KeyManager::getManager()->keyPressed(SDL_SCANCODE_ESCAPE)||KeyManager::getManager()->quit())
					{
						SceneManager::getManager()->saveGame();
						run=false;
					}
				}
			}
		}
	}
	delete AnimationManager::getManager();
	delete CameraManager::getManager();
	delete CollisionManager::getManager();
	delete GUIManager::getManager();
	delete KeyManager::getManager();
	delete ObjectManager::getManager();
	delete SceneManager::getManager();
	delete SoundManager::getManager();
	delete TextureManager::getManager();

	close();
	_CrtDumpMemoryLeaks();

	return 0;
}



bool loadMedia() 
{ 
	//Loading success flag 
	bool success = true; 
	//*
	//backgrounds
	TextureManager::getManager()->background1 = new Texture(renderer,"images/backgrounds/water1.png");
	TextureManager::getManager()->background2 = new Texture(renderer,"images/backgrounds/water2.png");
	TextureManager::getManager()->background3 = new Texture(renderer,"images/backgrounds/water3.png");
	

	//boat stuff
	TextureManager::getManager()->cannonBall = new Texture(renderer,"images/boats/cannon-ball.png");
	TextureManager::getManager()->grapple = new Texture(renderer,"images/boats/Grapple.png");
	TextureManager::getManager()->canon = new Texture(renderer,"images/boats/canon.png");
	TextureManager::getManager()->muzzleFlash = new Texture(renderer,"images/boats/canonFlash.png");
	TextureManager::getManager()->canonTop = new Texture(renderer,"images/boats/canonTop.png");
	TextureManager::getManager()->arrow = new Texture(renderer,"images/boats/CROSSHAIR128X64.png");
	TextureManager::getManager()->helm = new Texture(renderer,"images/boats/helm2.png");
	TextureManager::getManager()->pirateMast = new Texture(renderer,"images/boats/Sail1.png");
	TextureManager::getManager()->pirateCrowNest = new Texture(renderer,"images/boats/Sail2.png");
	TextureManager::getManager()->ship = new Texture(renderer,"images/boats/SHIPMR2.png");
	TextureManager::getManager()->navyMast = new Texture(renderer,"images/boats/Navy-Sails1.png");
	TextureManager::getManager()->navyCrowNest = new Texture(renderer,"images/boats/Navy-Sails2.png");


	//boss boats
	TextureManager::getManager()->dreadRobertsBoat = new Texture(renderer,"images/bossBoats/DreadRobMR2.png");
	TextureManager::getManager()->dreadRobertsHelm = new Texture(renderer,"images/bossBoats/helm1mr2.png");
	TextureManager::getManager()->dreadRobertsCrowNest = new Texture(renderer,"images/bossBoats/Dreadsail2MR2.png");
	TextureManager::getManager()->dreadRobertsMast = new Texture(renderer,"images/bossBoats/Dreadsail1MR2.png");
	TextureManager::getManager()->daveyMast = new Texture(renderer,"images/bossBoats/DEATHSHIPSAIL2.png");
	TextureManager::getManager()->daveyHelm = new Texture(renderer,"images/bossBoats/bossship_helm_50x35.png");
	TextureManager::getManager()->daveySails = new Texture(renderer,"images/bossBoats/DEATHSHIPSAIL1.png");
	TextureManager::getManager()->alienShip = new Texture(renderer,"images/bossBoats/spaceship_180x180.png");
	TextureManager::getManager()->deathMast = new Texture(renderer,"images/bossBoats/bossship_Bsail_45x405.png");
	TextureManager::getManager()->deathSails = new Texture(renderer,"images/bossBoats/bossship_Fsail_25x275.png");
	TextureManager::getManager()->deathShip = new Texture(renderer,"images/bossBoats/bossship_630x240.png");
	TextureManager::getManager()->fisherboat = new Texture(renderer, "images/boats/fishingboat.png");
	TextureManager::getManager()->neptunesWhale = new Texture(renderer, "images/bossBoats/kingneptuneswhale.png");


	//bosses
	TextureManager::getManager()->krakenTentacle1 = new Texture(renderer,"images/bosses/kraken/tentacles6_50x42.png");
	TextureManager::getManager()->krakenTentacle2 = new Texture(renderer,"images/bosses/kraken/tentacles7_20x50.png");
	TextureManager::getManager()->krakenTentacle3 = new Texture(renderer,"images/bosses/kraken/tentacles8_20x50.png");
	TextureManager::getManager()->krakenTentacle4 = new Texture(renderer,"images/bosses/kraken/tentacles9_20x50.png");
	TextureManager::getManager()->krakenTentacle5 = new Texture(renderer,"images/bosses/kraken/tentacles10_20x50.png");
	TextureManager::getManager()->krakenTentacle6 = new Texture(renderer,"images/bosses/kraken/tentacles11_20x50.png");
	TextureManager::getManager()->alien = new Texture(renderer,"images/bosses/alien_32x32.png");
	TextureManager::getManager()->death = new Texture(renderer,"images/bosses/Death.png");
	TextureManager::getManager()->dreadRoberts = new Texture(renderer,"images/bosses/dread-pirate-roberto.png");
	TextureManager::getManager()->kingNeptune = new Texture(renderer,"images/bosses/kingneptune_32x32.png");
	TextureManager::getManager()->davyJones = new Texture(renderer,"images/bosses/Davy-Jones.png");
	TextureManager::getManager()->mobyDick = new Texture(renderer,"images/bosses/mobydick_520x180.png");

	//boss units
	TextureManager::getManager()->ghostPirate = new Texture(renderer,"images/bossUnits/ghost-sailor.png");


	//hats
	TextureManager::getManager()->navyRank1 = new Texture(renderer,"images/hats/navy/hat1.png");
	TextureManager::getManager()->navyRank2 = new Texture(renderer,"images/hats/navy/hat2.png");
	TextureManager::getManager()->navyRank3 = new Texture(renderer,"images/hats/navy/hat3.png");
	TextureManager::getManager()->navyRank4 = new Texture(renderer,"images/hats/navy/hat4.png");
	TextureManager::getManager()->navyRank5 = new Texture(renderer,"images/hats/navy/hat5.png");
	TextureManager::getManager()->navyRank6 = new Texture(renderer,"images/hats/navy/hat6.png");

	//pirate hats
	TextureManager::getManager()->pirateRank1 = new Texture(renderer,"images/hats/pirate/hat1.png");
	TextureManager::getManager()->pirateRank2 = new Texture(renderer,"images/hats/pirate/hat2.png");
	TextureManager::getManager()->pirateRank3 = new Texture(renderer,"images/hats/pirate/hat3.png");
	TextureManager::getManager()->pirateRank4 = new Texture(renderer,"images/hats/pirate/hat4.png");
	TextureManager::getManager()->pirateRank5 = new Texture(renderer,"images/hats/pirate/hat5.png");
	TextureManager::getManager()->pirateRank6 = new Texture(renderer,"images/hats/pirate/hat6.png");
	
	
	//islands
	TextureManager::getManager()->bankIsland = new Texture(renderer,"images/islands/bank.png","images/islands/bank.txt");
	TextureManager::getManager()->emptyIsland = new Texture(renderer,"images/islands/emptyIsland.png","images/islands/emptyIsland.txt");
	TextureManager::getManager()->pirateCove = new Texture(renderer,"images/islands/shipyard.png","images/islands/shipyard.txt");
	TextureManager::getManager()->villageIsland = new Texture(renderer,"images/islands/village.png","images/islands/village.txt");
	TextureManager::getManager()->villageIslandTwo = new Texture(renderer,"images/islands/village2.png","images/islands/village2.txt");
	TextureManager::getManager()->rockyIsland = new Texture(renderer,"images/islands/rocky.png","images/islands/rocky.txt");
	TextureManager::getManager()->volcano = new Texture(renderer,"images/islands/volcano.png","images/islands/volcano.txt");


	//misc
	TextureManager::getManager()->goldChestClosed = new Texture(renderer,"images/misc/chest-closed.png");
	TextureManager::getManager()->goldChestOpen = new Texture(renderer,"images/misc/chest-open.png");
	TextureManager::getManager()->circle = new Texture(renderer,"images/misc/circle.png");
	TextureManager::getManager()->fogEffect = new Texture(renderer,"images/misc/FOG-EFFECT.png");
	TextureManager::getManager()->goldCoin = new Texture(renderer,"images/misc/GOLD.png");
	TextureManager::getManager()->sword = new Texture(renderer,"images/misc/sword.png");
	TextureManager::getManager()->tree = new Texture(renderer,"images/misc/tree.png");
	TextureManager::getManager()->blank = new Texture(renderer,"images/misc/empty.png");


	//sea creatures
	TextureManager::getManager()->hydraSmall = new Texture(renderer,"images/seaCreatures/hydra.png");
	TextureManager::getManager()->hydraLarge = new Texture(renderer,"images/seaCreatures/hydraDad.png");
	TextureManager::getManager()->jellyfish = new Texture(renderer,"images/seaCreatures/jellyfish.png");
	TextureManager::getManager()->octopusSmall = new Texture(renderer,"images/seaCreatures/octopus.png");
	TextureManager::getManager()->octopusLarge = new Texture(renderer,"images/seaCreatures/octopusLarge.png");
	TextureManager::getManager()->squid = new Texture(renderer,"images/seaCreatures/squid.png");
	TextureManager::getManager()->whale = new Texture(renderer,"images/seaCreatures/whale.png");
	TextureManager::getManager()->whaleBottom = new Texture(renderer,"images/seaCreatures/whaleBottom.png");
	TextureManager::getManager()->serpent = new Texture(renderer,"images/seaCreatures/serpent.png");
	TextureManager::getManager()->turtle = new Texture(renderer,"images/seaCreatures/turtle.png");


	//units
	TextureManager::getManager()->pirate = new Texture(renderer,"images/units/PirateMR2.png");
	TextureManager::getManager()->skeletonPirate = new Texture(renderer,"images/units/SkeletonMk2.png");
	TextureManager::getManager()->villager = new Texture(renderer,"images/units/VillagerMr2.png");
	TextureManager::getManager()->navy = new Texture(renderer,"images/units/navysailor.png");

	//HUD elements
	TextureManager::getManager()->ship_indicator1 = new Texture(renderer,"images/GUI/HUD_ship_indicator.png");
	TextureManager::getManager()->ship_indicator2 = new Texture(renderer,"images/GUI/HUD_ship_indicator2.png");
	TextureManager::getManager()->unit_indicator = new Texture(renderer,"images/GUI/HUD_unit_indicator.png");
	TextureManager::getManager()->minimap = new Texture(renderer,"images/GUI/minimap.png");
	TextureManager::getManager()->gold_indicator = new Texture(renderer,"images/GUI/HUD_gold_indicator.png");
	TextureManager::getManager()->notoriety1 = new Texture(renderer,"images/GUI/skull.png");
	TextureManager::getManager()->notoriety2 = new Texture(renderer,"images/GUI/skull1.png");
	TextureManager::getManager()->notoriety3 = new Texture(renderer,"images/GUI/skull2.png");
	TextureManager::getManager()->notoriety4 = new Texture(renderer,"images/GUI/skull3.png");
	TextureManager::getManager()->unitCommandIcon = new Texture(renderer,"images/GUI/Hud_unit_indicator.png");
	TextureManager::getManager()->hatIcon = new Texture(renderer,"images/hats/pirate/hat1.png");
	TextureManager::getManager()->blankBackground = new Texture(renderer,"images/GUI/blank.png");
	TextureManager::getManager()->shipMenuBottom  = new Texture(renderer,"images/GUI/bottom.png");
	TextureManager::getManager()->shipMenuBack  = new Texture(renderer,"images/GUI/section.png");
	TextureManager::getManager()->upArrow  = new Texture(renderer,"images/GUI/up_arrow.png");
	TextureManager::getManager()->downArrow  = new Texture(renderer,"images/GUI/down_arrow.png");
	TextureManager::getManager()->boardCommand  = new Texture(renderer,"images/GUI/board.png");
	TextureManager::getManager()->abandonCommand  = new Texture(renderer,"images/GUI/abandon.png");
	TextureManager::getManager()->lootCommand  = new Texture(renderer,"images/GUI/loot.png");
	TextureManager::getManager()->mapShipTexture  = new Texture(renderer,"images/GUI/ship.png");
	TextureManager::getManager()->mapIslandTexture  = new Texture(renderer,"images/GUI/island.png");
	TextureManager::getManager()->bankTexture = new Texture(renderer, "images/GUI/DeathsBankGUI.png");
	TextureManager::getManager()->deposit = new Texture(renderer, "images/GUI/deposit.png");
	TextureManager::getManager()->withdraw = new Texture(renderer, "images/GUI/Withdraw.png");
	TextureManager::getManager()->bankAmount = new Texture(renderer, "images/GUI/bankAmount.png");
	TextureManager::getManager()->minusDBbtn = new Texture(renderer, "images/GUI/minus_buttonDB.png");
	TextureManager::getManager()->plusDBbtn = new Texture(renderer, "images/GUI/plus_buttonDB.png");

	//Shop Images
	TextureManager::getManager()->buyShipBack = new Texture(renderer,"images/GUI/screen_buy_ship.png");
	TextureManager::getManager()->buyShipBackTop = new Texture(renderer,"images/GUI/screen_buy_ship_top.png");
	TextureManager::getManager()->shipLvl1 = new Texture(renderer,"images/GUI/Buy_Ships/ShipLvl1.png");
	TextureManager::getManager()->shipLvl2 = new Texture(renderer,"images/GUI/Buy_Ships/ShipLvl2.png");
	TextureManager::getManager()->shipLvl3 = new Texture(renderer,"images/GUI/Buy_Ships/ShipLvl3.png");
	TextureManager::getManager()->buyBtn = new Texture(renderer,"images/GUI/BUY_BUTTON.png");
	TextureManager::getManager()->upgradeUnitBack = new Texture(renderer,"images/GUI/screen_unit_upgrades.png");
	TextureManager::getManager()->upgradeShipBack = new Texture(renderer,"images/GUI/screen_ship_upgrades.png");
	TextureManager::getManager()->leftArrow  = new Texture(renderer,"images/GUI/left_arrow.png");
	TextureManager::getManager()->rightArrow  = new Texture(renderer,"images/GUI/right_arrow.png");
	TextureManager::getManager()->plusBtn  = new Texture(renderer,"images/GUI/plus_button.png");

	//menu 
	TextureManager::getManager()->menu_screen =  new Texture(renderer,"images/menu/main-menu-background.png");
	TextureManager::getManager()->deatBackground =  new Texture(renderer,"images/menu/Death-screen.png");
	TextureManager::getManager()->optionMenu =  new Texture(renderer,"images/menu/options_bg.png");
	TextureManager::getManager()->playBtn =  new Texture(renderer,"images/menu/playMoff.png");
	TextureManager::getManager()->playBtn2 =  new Texture(renderer,"images/menu/playMon.png");
	TextureManager::getManager()->quitBtn =  new Texture(renderer,"images/menu/QuitMoff.png");
	TextureManager::getManager()->quitBtn2 =  new Texture(renderer,"images/menu/QuitMon.png");
	TextureManager::getManager()->replayBtn =  new Texture(renderer,"images/menu/RestartMoff.png");
	TextureManager::getManager()->replayBtn2 =  new Texture(renderer,"images/menu/RestartMon.png");
	TextureManager::getManager()->backBtn =  new Texture(renderer,"images/menu/BackMoff.png");
	TextureManager::getManager()->backBtn2 =  new Texture(renderer,"images/menu/BackMon.png");
	TextureManager::getManager()->optionsBtn =  new Texture(renderer,"images/menu/OptionsMoff.png");
	TextureManager::getManager()->optionsBtn2 =  new Texture(renderer,"images/menu/OptionsMon.png");
	TextureManager::getManager()->upBtn =  new Texture(renderer,"images/menu/btnUp.png");
	TextureManager::getManager()->downBtn =  new Texture(renderer,"images/menu/btnDown.png");
	TextureManager::getManager()->leftBtn =  new Texture(renderer,"images/menu/btnLeft.png");
	TextureManager::getManager()->rightBtn =  new Texture(renderer,"images/menu/btnRight.png");
	TextureManager::getManager()->grappleBtn =  new Texture(renderer,"images/menu/btnGrapple.png");
	TextureManager::getManager()->assignBtn =  new Texture(renderer,"images/menu/btnAssign.png");
	TextureManager::getManager()->defaultBtn =  new Texture(renderer,"images/menu/btnDefault.png");
	TextureManager::getManager()->cannonUpBtn =  new Texture(renderer,"images/menu/cannonUpBtn.png");
	TextureManager::getManager()->cannonDownBtn =  new Texture(renderer,"images/menu/cannonDownBtn.png");
	TextureManager::getManager()->cannonLeftBtn =  new Texture(renderer,"images/menu/cannonLeftBtn.png");
	TextureManager::getManager()->cannonRightBtn =  new Texture(renderer,"images/menu/cannonRight.png");
	TextureManager::getManager()->helmUpBtn =  new Texture(renderer,"images/menu/helmUpBtn.png");
	TextureManager::getManager()->helmDownBtn =  new Texture(renderer,"images/menu/helmDown.png");
	TextureManager::getManager()->helmLeftBtn =  new Texture(renderer,"images/menu/helmLeftBtn.png");
	TextureManager::getManager()->helmRightBtn =  new Texture(renderer,"images/menu/helmRightBtn.png");
	TextureManager::getManager()->loadBtn =  new Texture(renderer,"images/menu/LoadGameMoff.png");
	TextureManager::getManager()->loadBtn2 =  new Texture(renderer,"images/menu/LoadGameMon.png");

	//font
	TextureManager::getManager()->font = TTF_OpenFont("images/fonts/BOOTERFZ.ttf", 36);
	TextureManager::getManager()->fontInner = TTF_OpenFont("images/fonts/BOOTERFZ.ttf", 30);
	TextureManager::getManager()->fontText = TTF_OpenFont("images/fonts/BOOTERFZ.ttf", 18);

//	SoundManager::getManager()->shipSound
	//Sounds
	SoundManager::getManager()->loadSound();
	//*/
	string name;
	//ifstream file("images/fonts/names.txt");
	ifstream file("images/fonts/classNames.txt");
	//Crew::nameOptions[150];
	if(file.is_open())
	{
		/*for(int i = 0; i<150; i++)
		{
			getline(file,name);
			Crew::nameOptions.push_back(name);
		}*/
		while(getline(file,name))
		{
			Crew::nameOptions.push_back(name);
		}
	}
	return success; 
}