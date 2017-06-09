#ifndef __ARK_AUDIO_H__
#define __ARK_AUDIO_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 29.01.2004
Last Revised:	11.05.2004

Implementation File: Audio.cpp

Notes:
	
*/

/*
	Header for Audio subsystem
*/

#include "Arkanoid.h"

namespace ARK
{
	const int ARK_MAX_SOUNDS = 16;	//max sound samples
	const int ARK_MAX_MUSICS = 4;	//max music samples
	struct CSound
	{
		std::string name;	//sound`s name
		FSOUND_SAMPLE * soundHandle;	//FMOD sound handle
	};

	struct CMusic
	{
		std::string name;	//music`s name
		FMUSIC_MODULE * musicHandle;
	};
	class CAudio
	{
	protected:
		CSound sounds[ARK_MAX_SOUNDS];	//sound table
		CMusic musics[ARK_MAX_MUSICS];	//music table. Got no idea why I`ve done it this way :D

		int nSounds;	//number of loaded samples
		int nMusics;	//number of loaded music samples

	public:
		CAudio(){}
		~CAudio(){}
		bool Init();	//initialize Audio Subsystem
		bool DeInit();	//deinitialize Audio Subsystem

		int LoadSound(const char * name);	//load a sound
		void PlaySound(int soundID);	//play a soung

		int LoadMusic(const char * name);	//load a music
		void PlayMusic(int musicID);	//play music
		void StopMusic(int musicID);	//stop music

	};

} //end of namespace ARK


#endif //__ARK_AUDIO_H__