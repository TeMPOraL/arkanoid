/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 25.04.2004
Last Revised:	25.04.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "AllOtherGameStates.h"

namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CTimeAttackGame::CTimeAttackGame()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CTimeAttackGame::~CTimeAttackGame()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Game State
	//=============================================
	bool CTimeAttackGame::Init()
	{
		log << "CTimeAttackGame::Init() - initializing Time Attack Game state\n";
		
		CGameRules gameRules;	//game rules

		gameRules.bUseGravity = false;
		gameRules.bNoPowerups = false;
		gameRules.bNoNextLevel = false;
		gameRules.bRespawnBricks = false;
		gameRules.bShowTimer = true;
		gameRules.bTimeAttack = true;
		gameRules.countdownType = CGameRules::CT_FROMZERO;
		gameRules.defeatConditions = CGameRules::DC_NOLIVES;
		gameRules.victoryConditions = CGameRules::VC_NOBRICKS;
		CGame::GetSingleton().objectManager.Init( gameRules );
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Game State
	//=============================================
	bool CTimeAttackGame::DeInit()
	{
		log <<"CTimeAttackGame::DeInit() - deinitializing Time Attack Game state\n";
		CGame::GetSingleton().spriteMgr.UnloadAll();	//unload all sprites
		CGame::GetSingleton().objectManager.DeInit();
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CTimeAttackGame::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen and the depth buffer
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);

		CGame::GetSingleton().objectManager.Update(dT);
		CGame::GetSingleton().objectManager.Draw();

	}


	//=============================================

	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CSurvivalGame::CSurvivalGame()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CSurvivalGame::~CSurvivalGame()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Game State
	//=============================================
	bool CSurvivalGame::Init()
	{
		log << "CSurvivalGame::Init() - initializing Survival Game state\n";

		CGameRules gameRules;	//game rules

		gameRules.bUseGravity = false;
		gameRules.bNoPowerups = false;
		gameRules.bNoNextLevel = false;
		gameRules.bRespawnBricks = true;
		gameRules.bShowTimer = true;
		gameRules.bTimeAttack = false;
		gameRules.countdownType = CGameRules::CT_NONE;
		gameRules.defeatConditions = CGameRules::DC_LOSTBALL;
		gameRules.victoryConditions = CGameRules::VC_NOBRICKS;
		CGame::GetSingleton().objectManager.Init( gameRules );
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Game State
	//=============================================
	bool CSurvivalGame::DeInit()
	{
		log <<"CSurvivalGame::DeInit() - deinitializing Survival Game state\n";
		CGame::GetSingleton().spriteMgr.UnloadAll();	//unload all sprites
		CGame::GetSingleton().objectManager.DeInit();
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CSurvivalGame::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen and the depth buffer
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);

		CGame::GetSingleton().objectManager.Update(dT);
		CGame::GetSingleton().objectManager.Draw();

	}

	//=============================================

	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CGravityGame::CGravityGame()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CGravityGame::~CGravityGame()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Game State
	//=============================================
	bool CGravityGame::Init()
	{
		log << "CGravityGame::Init() - initializing Test game state\n";

		CGameRules gameRules;	//game rules

		gameRules.bUseGravity = true;
		gameRules.bNoPowerups = false;
		gameRules.bNoNextLevel = false;
		gameRules.bRespawnBricks = false;
		gameRules.bShowTimer = false;
		gameRules.bTimeAttack = false;
		gameRules.countdownType = CGameRules::CT_NONE;
		gameRules.defeatConditions = CGameRules::DC_NOLIVES;
		gameRules.victoryConditions = CGameRules::VC_NOBRICKS;
		CGame::GetSingleton().objectManager.Init( gameRules );

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Game State
	//=============================================
	bool CGravityGame::DeInit()
	{
		log <<"CGravityGame::DeInit() - deinitializing Test game state\n";
		CGame::GetSingleton().spriteMgr.UnloadAll();	//unload all sprites
		CGame::GetSingleton().objectManager.DeInit();
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CGravityGame::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen and the depth buffer
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);

		CGame::GetSingleton().objectManager.Update(dT);
		CGame::GetSingleton().objectManager.Draw();

	}


	
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CCredits::CCredits()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CCredits::~CCredits()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Game State
	//=============================================
	bool CCredits::Init()
	{
		log << "CCredits::Init() - initializing Test game state\n";
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Game State
	//=============================================
	bool CCredits::DeInit()
	{
		log <<"CCredits::DeInit() - deinitializing Test game state\n";
		CGame::GetSingleton().spriteMgr.UnloadAll();	//unload all sprites
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 25.04.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CCredits::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen and the depth buffer
		glLoadIdentity();
		//glTranslatef(0.0f,0.0f,-3.0f);
	}
	

} //end of namespace ARK