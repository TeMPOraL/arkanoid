#ifndef __ARK_INTRO_H__
#define __ARK_INTRO_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 19.04.2004
Last Revised:	19.04.2004

Implementation File: Intro.cpp

Notes:
	
*/

/*
	Intro game state - just a state showing TeMPOraL Software and Arkanoid logo.
*/

#include "Arkanoid.h"
#include "GameState.h"

namespace ARK
{
	class CIntro : public CGameState
	{
	private:
		int TSLogoHandle;	//TeMPOraL Software logo handle
		int ARKLogoHandle;	//Arkanoid logo handle

		float TSLogoDelay;	//time for displaying TeMPOraL Software logo
		float ARKLogoDelay;	//time for displaying Arkanoid logo
		float delayBetweenLogos;	//delay between TeMPOraL Software and Arkanoid logos

		float accumulatedTime;	//accumulated time duration of showing logo

	public:
		CIntro();	//constructor
		~CIntro();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize
	};
} //end of namespace ARK

#endif //__ARK_INTRO_H__