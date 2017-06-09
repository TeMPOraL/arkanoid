/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 29.01.2004
Last Revised:	11.05.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "Audio.h"
#include "StringsSystem.h"

namespace ARK
{
	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 23.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Audio System
	//=============================================
	bool CAudio::Init()
	{
		log << "CAudio::Init() - Initializing FMOD Audio\n";

		if (FSOUND_GetVersion() < FMOD_VERSION)	//check FMOD version
		{
			log.Error("CAudio::Init() - Invalid FMOD Version. You should be using FMOD %.02f\n", FMOD_VERSION);
			MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_INVALID_FMOD_VERSION)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			return false;
		}

		if (!FSOUND_Init(32000, 64, 0))
		{
			log.Error("CAudio::Init() - Failed to initialize FMOD Sound System");
			MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_FAILED_INITIALIZING_FSOUND)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			return false;
		}

		
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 23.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Audio System
	//=============================================
	bool CAudio::DeInit()
	{
		log << "CAudio::DeInit() - Deinitializing FMOD Audio\n";
		FSOUND_Close();
		return true;
	}

	//=============================================
	//Function: LoadSound()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.05.2004
	//
	//Returns: int - loaded sound ID
	//Parameters: name of sound to load
	//Description:
	//	Loads sound file and returns it`s ID
	//=============================================
	int CAudio::LoadSound(const char * name)
	{
		if(nSounds >= ARK_MAX_SOUNDS)	//check if not exceeded sound limit
		{
			log <<"CAudio::LoadSound() - Warning, exceeded sound limit of " << ARK_MAX_SOUNDS << "\n";
			return -1;
		}

		for(int i = 0; i < nSounds ; ++i)	//check if we have a sound already loaded
		{
			if(sounds[i].name == name)	//found the same sound
			{
				if(CGame::GetSingleton().bDebugMode == true)	//in debug mode
				{
					log <<"CAudio::LoadSound() - Sample already exists at position " << i << "\n";
				}
				return i;	//return sound handle
			}
		}
		sounds[nSounds].name = name;	//copy name
		sounds[nSounds].soundHandle = FSOUND_Sample_Load(FSOUND_FREE, name, FSOUND_NORMAL, 0, 0);	//load a sound
		
		if(sounds[nSounds].soundHandle == NULL)	//failed to load sound
		{
			log.Error("CAudio::LoadSound() - Error loading sound [%s]", name);
			return -1;
		}
		log <<"CAudio::LoadSound() - loaded sound [" << name <<"] at position " << nSounds <<"\n";
		++nSounds;	//increment sound count
		return (nSounds-1);
	}

	//=============================================
	//Function: PlaySound()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.05.2004
	//
	//Returns: nothing
	//Parameters: sound ID
	//Description:
	//	Plays sound with given ID
	//=============================================
	void CAudio::PlaySound(int soundID)
	{
		if(soundID < 0 || soundID >= nSounds)	//invalid handles
		{
			log.Error("CAudio::PlaySound() - Error playing sound. Invalid handle");
			return;
		}
		FSOUND_PlaySound(FSOUND_FREE, sounds[soundID].soundHandle);	//play sound
	}

	//=============================================
	//Function: LoadMusic()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.05.2004
	//
	//Returns: int - loaded music ID
	//Parameters: music file name
	//Description:
	//	Loads sound with given name
	//=============================================
	int CAudio::LoadMusic(const char * name)
	{
		if(nMusics >= ARK_MAX_MUSICS)	//check music limit
		{
			log <<"CAudio::LoadMusic() - Warning, exceeded music limit of " << ARK_MAX_MUSICS << "\n";
			return -1;
		}

		//check if we have this music loaded
		for(int i = 0; i < nMusics ; ++i)
		{
			if(musics[i].name == name)	//found the same music
			{
				if(CGame::GetSingleton().bDebugMode == true)	//in debug mode
				{
					log <<"CAudio::LoadMusic() - Song already exists at position " << i << "\n";
				}
				return i;	//return music handle
			}
		}

		musics[nMusics].name = name;	//copy name
		musics[nMusics].musicHandle = FMUSIC_LoadSong(name);	//load music
		
		if(musics[nMusics].musicHandle == NULL)	//failed to load sound
		{
			log.Error("CAudio::LoadMusic() - Error loading music [%s]", name);
			return -1;
		}
		log <<"CAudio::LoadMusic() - loaded music [" << name <<"] at position " << nMusics <<"\n";
		++nMusics;	//increment music count
		return (nMusics-1);

	}

	//=============================================
	//Function: PlayMusic()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.05.2004
	//
	//Returns: nothing
	//Parameters: music ID
	//Description:
	//	Plays music
	//=============================================
	void CAudio::PlayMusic(int musicID)
	{
		if(musicID < 0 || musicID >= nMusics)	//invalid handles
		{
			log.Error("CAudio::PlayMusic() - Error playing Music. Invalid handle");
			return;
		}
		FMUSIC_PlaySong(musics[musicID].musicHandle);	//play music
	}

	//=============================================
	//Function: StopMusic()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.05.2004
	//
	//Returns: nothing
	//Parameters: music ID
	//Description:
	//	Stops music
	//=============================================
	void CAudio::StopMusic(int musicID)
	{
		if(musicID < 0 || musicID >= nMusics)	//invalid handles
		{
			log.Error("CAudio::StopMusic() - Error stopping Music. Invalid handle");
			return;
		}
		FMUSIC_StopSong(musics[musicID].musicHandle);	//play music
	}
}