
#ifndef __ARK_MAIN_MENU_H__
#define __ARK_MAIN_MENU_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 15.04.2004
Last Revised:	15.04.2004

Implementation File: MainMenu.cpp

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "TestGameState.h"
#include "StaticText.h"

#define ARK_MAIN_MENU_OPTIONS 6

const int ARK_MAIN_MENU_OPTION_NEW_GAME_NORMAL = 0;
const int ARK_MAIN_MENU_OPTION_NEW_GAME_TIME_ATTACK = 1;
const int ARK_MAIN_MENU_OPTION_NEW_GAME_SURVIVAL = 2;
const int ARK_MAIN_MENU_OPTION_NEW_GAME_NORMAL_WITH_GRAVITY = 3;
const int ARK_MAIN_MENU_OPTION_CREDITS = 4;
const int ARK_MAIN_MENU_OPTION_QUIT = 5;

namespace ARK
{
	class CMainMenu : public CGameState
	{
	private:
		
		CStaticText menuOptions[ARK_MAIN_MENU_OPTIONS];	//menu options table
		int numOptions;
		int selectedOption;

		int selectSound;	//sound played when selecting
		int acknowledgeSound;	//sound played when acknowledged an option

		//
		float keyDownDelay;
		float keyUpDelay;
	public:
		CMainMenu();	//constructor
		~CMainMenu();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};
}

#endif //__ARK_MAIN_MENU_H__