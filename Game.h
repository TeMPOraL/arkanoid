#ifndef __ARK_GAME_H__
#define __ARK_GAME_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 29.01.2004
Last Revised:	26.05.2004

Implementation File: Game.cpp

Notes:
	
*/

/*

  CGame class:

  Main game class, controlls all subsystems - input, sound, game manager (logic),
  file access controll. A singleton.

*/
#include "Arkanoid.h"
#include "GameStateMgr.h"
#include "Singleton.h"
#include "StringTable.h"
#include "Window.h"
#include "Input.h"
#include "Audio.h"
#include "HiResTimer.h"
#include "PseudoRandomizer.h"
#include "SpriteMgr.h"
#include "ObjectManager.h"

namespace ARK
{
	class CGame : public CSingleton<CGame>
	{
	private:
		HINSTANCE appInstance;	//application instance
		
		bool bShouldQuit;	//should the program quit?
	public:
		std::string runParams;	//command line parameters

		CStringTable systemStrings;	//main string table
		CStringTable stat_txt;	//game text string table
		CStringTable dataStrings;	//string table with data file names

		CWindow gameWindow;	//main game window
		CGameStateMgr gameMgr;	//game state manager
		CInput inputSystem;	//input system
		CAudio audioSystem;	//audio system
		CSpriteMgr spriteMgr;	//sprite manager
		CHiResTimer timer;	//High Resolution Timer
		CPseudoRandomizer randomizer;	//Pseudo-Random Number Generator
		CObjectManager objectManager;	//Object Manager

		bool bDebugMode;	//run in debug mode
	
		
		CGame():appInstance(0), bShouldQuit(false), bDebugMode(false){}	//empty constructor
		~CGame(){}	//empty destructor

		bool Init(HINSTANCE _appInstance, LPSTR params);	//initialization
		bool DeInit();	//deinitialization
		bool Execute();	//execution

		void Quit()
		{
			bShouldQuit = true;
		}

	};

} //end of namespace ARK


#endif //__ARK_GAME_H__