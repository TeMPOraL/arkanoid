/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 19.04.2004
Last Revised: 05.05.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "MainMenu.h"



namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CMainMenu::CMainMenu()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CMainMenu::~CMainMenu()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.05.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Game State
	//=============================================
	bool CMainMenu::Init()
	{
		log << "CMainMenu::Init() - initializing Main Menu game state\n";
		//strings.Init("stat_txt.tbl");	//open string table file
		glDisable(GL_TEXTURE_2D);
		
		for(int i = 0; i < ARK_MAIN_MENU_OPTIONS ; ++i)
		{
			menuOptions[i].PostBeginPlay( &(CGame::GetSingleton().dataStrings) );	//initialize text fields
			menuOptions[i].SetText(CGame::GetSingleton().stat_txt.GetString(STAT_TXT_MAIN_MENU_STRING_OFFSET + i).c_str(), false, TEXTALIGN_CENTER, 20);	//set text
		}

		menuOptions[0].position = Vector2(200,300);
		menuOptions[1].position = Vector2(200,375);
		menuOptions[2].position = Vector2(600,300);
		menuOptions[3].position = Vector2(600,375);
		menuOptions[4].position = Vector2(400,450);
		menuOptions[5].position = Vector2(400,525);

		numOptions = ARK_MAIN_MENU_OPTIONS;
		selectedOption = 0;

		keyDownDelay = 0.0f;
		keyUpDelay = 0.0f;

		selectSound = CGame::GetSingleton().audioSystem.LoadSound(CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_MENUSELECT_SOUND).c_str());
		acknowledgeSound = CGame::GetSingleton().audioSystem.LoadSound(CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_MENUACKNOWLEDGE_SOUND).c_str());

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Game State
	//=============================================
	bool CMainMenu::DeInit()
	{
		log <<"CMainMenu::DeInit() - deinitializing Intro game state\n";
		for(int i = 0; i < numOptions ; ++i)
		{
			menuOptions[i].PreEndGame();
			menuOptions[i].Delete();
		}
		CGame::GetSingleton().spriteMgr.UnloadAll();	//unload all sprites
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CMainMenu::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen
		glLoadIdentity();
		glColor3f(1.0f,1.0f,1.0f);	//white

		glEnable(GL_TEXTURE_2D);

		keyUpDelay -=dT;
		keyDownDelay -=dT;

		if(keyDownDelay < 0)
		{
			keyDownDelay = 0;
		}

		if(keyUpDelay < 0)
		{
			keyUpDelay = 0;
		}


		for(int i = 0; i < selectedOption ; ++i)
		{
			menuOptions[i].Tick(dT);	//tick
			menuOptions[i].Draw();	//draw
		}
		glColor3f(1.0f,0.0f,0.0f);
		menuOptions[selectedOption].Tick(dT);	//tick selected
		menuOptions[selectedOption].Draw();	//draw selected

		glColor3f(1.0f,1.0f,1.0f);	//white

		for(int j = (selectedOption + 1) ; j <numOptions; ++j)
		{
			menuOptions[j].Tick(dT);	//tick rest
			menuOptions[j].Draw();	//draw rest
		}

		//input processing
		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_DOWN) && keyDownDelay == 0)
		{
			CGame::GetSingleton().audioSystem.PlaySound(selectSound);
			++selectedOption;	//increment currently selected option
			if(selectedOption >= numOptions)
			{
				selectedOption = 0;	//wrap to the beginning
			}
			//CGame::GetSingleton().inputSystem.GetKeyboard()->SetKeyState(DIK_DOWN);
			keyDownDelay += 0.125f;	//1/8 s.
		}

		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_UP) && keyUpDelay == 0)
		{
			--selectedOption;	//decrement currently selected option
			CGame::GetSingleton().audioSystem.PlaySound(selectSound);
			if(selectedOption < 0)
			{
				selectedOption = numOptions-1;	//wrap to the end
			}
			//CGame::GetSingleton().inputSystem.GetKeyboard()->SetKeyState(DIK_UP);
			keyUpDelay += 0.125f;	//1/8 s.
		}

		//selecting option when pressing Enter key
		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_RETURN))
		{
			CGame::GetSingleton().audioSystem.PlaySound(acknowledgeSound);
			switch (selectedOption)
			{
				case ARK_MAIN_MENU_OPTION_NEW_GAME_NORMAL:	//Normal Game
				{
					log <<"CMainMenu::Update() - user selected to enter Normal Game mode\n";
					CGame::GetSingleton().gameMgr.SetState(GS_NORMAL_GAME);
					break;
				}
				case ARK_MAIN_MENU_OPTION_NEW_GAME_TIME_ATTACK:	//Time Attack game
				{
					log <<"CMainMenu::Update() - user selected to enter Time Attack Game mode\n";
					CGame::GetSingleton().gameMgr.SetState(GS_TIMEATTACK_GAME);
					break;
				}
				case ARK_MAIN_MENU_OPTION_NEW_GAME_SURVIVAL:	//Survival game
				{
					log <<"CMainMenu::Update() - user selected to enter Time Attack Game mode\n";
					CGame::GetSingleton().gameMgr.SetState(GS_SURVIVAL_GAME);
					break;
				}
				case ARK_MAIN_MENU_OPTION_NEW_GAME_NORMAL_WITH_GRAVITY:	//Gravity Game
				{
					log <<"CMainMenu::Update() - user selected to enter Gravity Game mode\n";
					CGame::GetSingleton().gameMgr.SetState(GS_GRAVITY_GAME);
					break;
				}
				case ARK_MAIN_MENU_OPTION_QUIT:	//quit the game
				{
					log <<"CMainMenu::Update() - user selected Quit option in menu\n";
					CGame::GetSingleton().Quit();	//quit
					break;
				}
				default:
				{
					log <<"CMainMenu::Update() - user selected not yet implemented command\n";
					break;
				}
			}
		}


	}

} //end of namespace ARK