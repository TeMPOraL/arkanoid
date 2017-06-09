/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 29.01.2004
Last Revised:	26.05.2004

This is an Implementation File:

Notes:
	
*/


/*
  CGame class:

  Main game class, controlls all subsystems - input, sound, game manager (logic),
  file access controll. A singleton.

*/

#include "Arkanoid.h"
#include "Game.h"

namespace ARK
{

	//=============================================
	//Function: Init
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 26.05.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes main game class
	//=============================================
	bool CGame::Init(HINSTANCE _appInstance, LPSTR params)
	{
		log.Open("log.Arkanoid.txt");
		log <<"CGame::Init() - Initializing Game\n-> Application`s Instance Handle (HINSTANCE): " <<_appInstance <<"\n";
		log <<"-> Command line parameters:\n" << params <<"\n";
		appInstance = _appInstance;
		runParams = params;

		//checking command-line params
		bool bRunFullScreen = true;	//run in windowed mode
		//-w - run windowed
		if(runParams.find_first_of("-w") == 0)
		{
			log <<"-w Param approved; running in windowed mode..\n";
			bRunFullScreen = false;
		}

		//-d - run in debug mode
		if(runParams.find_first_of("-d")== 0)
		{
			log <<"-d Param approved; running in Debug mode..\n";
			bDebugMode = true;
		}

		log <<"-> Loading System String Table\n";

		systemStrings.Init("system_txt.tbl");	//load strings

		log <<"-> Loading Game Text String Table\n";

		stat_txt.Init("stat_txt.tbl");	//load strings

		log <<"-> Loading Data Files String Table\n";

		dataStrings.Init("data.tbl");

		log <<"-> Initializing Game Window\n";
		//initialize Window
		if(!gameWindow.Init(800,600,16,bRunFullScreen))
		{
			Quit();
		}

		log <<"-> Initializing High Resolution Timer\n";
		//initialize High Resolution Timer
		if(!timer.Init())
		{
			log.Error("CGame::Init() - High Resolution Timer not avaible on this platform");
			MessageBox(NULL,(systemStrings.GetString(STRING_SYS_ERROR_HI_RES_TIMER_NOT_AVAIBLE)).c_str(),(systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);
			Quit();
		}

		//initialize PseudoRandomizer
		log <<"-> Initializing Pseudo-Random Number Generator\n";
		randomizer.Init();

		log <<"-> Initializing Input\n";
		//initialize Input System
		if(!inputSystem.Init(gameWindow.GetHWND(), appInstance, true))
		{
		//	Quit();
		}

		log <<"-> Initializing Audio\n";
		//initialize Audio System
		if(!audioSystem.Init())
		{
			Quit();
		}
		
		log <<"-> Initializing Game State Manager\n";
		//initialize Game State Manager
		if(!gameMgr.Init())
		{
			Quit();
		}

		log <<"-> Initializing Sprite Manager\n";
		if(!spriteMgr.Init())
		{
			Quit();
		}
		log <<"\t\t..::End of Game Initialization::..\n";
		return true;
	}

	//=============================================
	//Function: DeInit
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 26.05.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	DeInitializes main game class
	//=============================================
	bool CGame::DeInit()
	{
		log <<"CGame::DeInit() - Deinitializing Game\n";

		log <<"-> Unloading Data Files String Table\n";
		dataStrings.DeInit();
		
		log <<"-> Unloading Game Text String Table\n";
		stat_txt.DeInit();

		log <<"-> Unloading System String Table\n";
		systemStrings.DeInit();
		
		log <<"-> Deinitializing Sprite Manager\n";
		spriteMgr.DeInit();

		log <<"-> Deinitializing Game State Manager\n";
		//deinitialize Game State Manager
		gameMgr.DeInit();
		
		log <<"-> Deinitializing Input\n";
		//deinitialize Input System
		inputSystem.DeInit();

		log <<"-> Deinitializing Audio\n";
		//deinitialize Audio System
		audioSystem.DeInit();
		
		log <<"->Deinitializing Game Window\n";
		//deinit window
		gameWindow.DeInit();

		return true;
	}

	//=============================================
	//Function: Execute
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.03.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Executes the game
	//=============================================
	bool CGame::Execute()
	{
		log <<"CGame::Execute() - Game started\n";
		MSG msg;
		gameMgr.SetState(GS_INTRO);
		
		while(true)
		{
			if (PeekMessage(&msg,/*gameWindow.GetHWND()*/NULL,0,0,PM_REMOVE))
			{
			
				if (msg.message==WM_QUIT)
				{
					log <<"WM_QUIT Message recieved\n";
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			
			}
			else			
			{
				if (bShouldQuit)
				{
					log<<"Breaking main loop (bShouldQuit == true)!\n";
					break;
				}
				else
				{
					inputSystem.Update();	//update input
					gameMgr.Update(timer.GetElapsedSeconds());	//update game
					SwapBuffers(gameWindow.GetDC());	//swap GL buffers
				}
			}
		}

		log <<"\t\t..::End of Game Execution::..\n";
		return true;
	}

} //end of namespace ARK