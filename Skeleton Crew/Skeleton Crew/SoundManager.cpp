#include "SoundManager.h"

SoundManager* SoundManager::me;

SoundManager* SoundManager::getManager()
{
	
	if(!me)
	{
		Mix_AllocateChannels(99999);
		me=new SoundManager();
	}
	return me;
}

SoundManager::SoundManager(void)
{
	sound = true;
}


SoundManager::~SoundManager(void)
{
	 //Free the sound effects
    Mix_FreeChunk( shipSound);
	Mix_FreeChunk( CannonFireSound);
	Mix_FreeChunk( GrappleFireSound);
	Mix_FreeChunk( CannonBallImpact);
	Mix_FreeChunk( coin);
	Mix_FreeChunk( deathCry);
	Mix_FreeChunk( whaleSound);
	Mix_FreeChunk( turtleSound);
	Mix_FreeChunk(jellySound);
	Mix_FreeChunk( hydraSound);
	Mix_FreeChunk( hydraDadSound);
	Mix_FreeChunk(scream1);
	Mix_FreeChunk( scream2);
	Mix_FreeChunk(pirateSound1);
	Mix_FreeChunk(pirateSound2);
	Mix_FreeChunk( pirateSound3);
	Mix_FreeChunk( pirateSound4);
	Mix_FreeChunk( pirateSound5);


	//Free the music
	/*Mix_FreeMusic( menuMusic);
	Mix_FreeMusic(deathFightMusic);
	Mix_FreeMusic( backgroundMusic);
	*/

	//Close the SDL mixer
	Mix_CloseAudio();
	
}


/*
--------------------
Load the required Sound files
--------------------
*/
bool SoundManager::loadSound(){
	 //Loading success flag
    bool success = true;

	if(sound)
	{
		 //Load music
		backgroundMusic = Mix_LoadMUS( "sounds/Crusade.ogg" );
		if( backgroundMusic == nullptr )
		{
			printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
			sound=false;
		}
	}

	if(sound)
	{
		 //Load music
		menuMusic = Mix_LoadMUS( "sounds/mainMenu.ogg" );
		if( menuMusic == nullptr )
		{
			printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
			sound=false;
		}
	}

	if(sound)
	{
		//Load sound effects
		shipSound = Mix_LoadWAV( "sounds/Boat-Select.ogg" );
		if(  shipSound == nullptr )
		{
			printf( "Failed to load boat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
			sound=false;
		}
	}

	coin = Mix_LoadWAV("sounds/moneyGain.ogg");
	if(  coin == NULL )
	{
		printf( "Failed to load money sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	CannonFireSound = Mix_LoadWAV("sounds/cannon.ogg");
	if( CannonFireSound == NULL )
	{
		printf( "Failed to load cannon sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	GrappleFireSound = Mix_LoadWAV("sounds/rope.ogg");
	if( GrappleFireSound == NULL )
	{
		printf( "Failed to load rope sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	CannonBallImpact = Mix_LoadWAV("sounds/explosion.ogg");
	if( CannonBallImpact == NULL )
	{
		printf( "Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//voices
	pirateSound1 = Mix_LoadWAV("sounds/Grunt1.ogg");
	if( pirateSound1 == NULL )
	{
		printf( "Failed to load grunt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	pirateSound2 = Mix_LoadWAV("sounds/Grunt2.ogg");
	if( pirateSound2 == NULL )
	{
		printf( "Failed to load grunt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	pirateSound3 = Mix_LoadWAV("sounds/Grunt3.ogg");
	if( pirateSound3 == NULL )
	{
		printf( "Failed to load grunt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	pirateSound4 = Mix_LoadWAV("sounds/Grunt4.ogg");
	if( pirateSound4 == NULL )
	{
		printf( "Failed to load grunt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	pirateSound5 = Mix_LoadWAV("sounds/Grunt5.ogg");
	if( pirateSound5 == NULL )
	{
		printf( "Failed to load grunt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//For when a unit dies
	deathCry = Mix_LoadWAV("sounds/dyingSound.ogg");
	if( deathCry == NULL )
	{
		printf( "Failed to load dying sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Sea Creature sounds
	whaleSound = Mix_LoadWAV("sounds/whaleYawn.ogg");
	if( whaleSound == NULL )
	{
		printf( "Failed to load whale sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	turtleSound = Mix_LoadWAV("sounds/turtle.ogg");
	if( turtleSound == NULL )
	{
		printf( "Failed to load turtle sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	jellySound = Mix_LoadWAV("sounds/JellyBoing.ogg");
	if( jellySound == NULL )
	{
		printf( "Failed to load jellyfish sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	hydraSound = Mix_LoadWAV("sounds/hydra.ogg");
	if( hydraSound == NULL )
	{
		printf( "Failed to load hydra sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	hydraDadSound = Mix_LoadWAV("sounds/hydraDad.ogg");
	if( hydraDadSound == NULL )
	{
		printf( "Failed to load hydra Dad sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Villager screams
	scream1 = Mix_LoadWAV("sounds/scream1.ogg");
	if( scream1 == NULL )
	{
		printf( "Failed to load scream1 sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	scream2 = Mix_LoadWAV("sounds/scream2.ogg");
	if( scream2 == NULL )
	{
		printf( "Failed to load scream2 sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Add in other sounds here
	

	return success;
}
/*
--------------------
Starts a sound effect playing on first free channel
--------------------
*/
void SoundManager::startSound(Mix_Chunk* soundEffect, Vector2f soundPosition)
{
	//if the sound is in range of the player
	if (camraPos.x - soundPosition.x >= -640 &&
			camraPos.x - soundPosition.x <= 640 && 
			camraPos.y - soundPosition.y >= -360 && 
			camraPos.y - soundPosition.y <= 360)
 	{
 		
 				Mix_VolumeChunk(soundEffect, MIX_MAX_VOLUME);
				Mix_PlayChannel( -1, soundEffect, 0 );
	}
	else if(camraPos.x - soundPosition.x > -3840 &&
			camraPos.x - soundPosition.x < 5120 && 
			camraPos.y - soundPosition.y > -2160 && 
			camraPos.y -soundPosition.y < 2880)
 	{
 			
 				Mix_VolumeChunk(soundEffect, MIX_MAX_VOLUME/15);
 				Mix_PlayChannel( -1, soundEffect, 0 );
 			
 	}
}

/*
--------------------
Starts playing music 
--------------------
*/
void SoundManager::startMusic(Mix_Music* music)
{
	  //If there is no music playing
	if(sound)
	{
		if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_PlayMusic( music, -1 );
		}
	}
}

/*
--------------------
Stops playing music 
--------------------
*/
void SoundManager::stopMusic()
{
	if(sound)
	{
		//Stop the music
		 Mix_HaltMusic();
	}
}

/*
--------------------
Pauses if music is playing, if music is paused it resumes it
--------------------
*/
void SoundManager::pauseResumeMusic()
{
	//If the music is paused
	if(sound)
	{
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}

void SoundManager::update(Vector2f camraPosition){
	camraPos = camraPosition;
}