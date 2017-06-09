#ifndef __ARK_ALL_OTHER_GAME_STATES_H__
#define __ARK_ALL_OTHER_GAME_STATES_H__
/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 25.04.2004
Last Revised:	25.04.2004

Implementation File: AllOtherGameStates.cpp

Notes:
	
*/

/*

*/

#include "Arkanoid.h"

#include "StaticText.h"

namespace ARK
{

	class CTimeAttackGame : public CGameState
	{
	private:
	
	public:
		CTimeAttackGame();	//constructor
		~CTimeAttackGame();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};

	class CSurvivalGame : public CGameState
	{
	private:
	
	public:
		CSurvivalGame();	//constructor
		~CSurvivalGame();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};

	class CGravityGame : public CGameState
	{
	private:
	
	public:
		CGravityGame();	//constructor
		~CGravityGame();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};

	class CCredits : public CGameState
	{
	private:
	
	public:
		CCredits();	//constructor
		~CCredits();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};


} //end of namespace ARK


#endif //__ARK_ALL_OTHER_GAME_STATES_H__