/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 21.04.2004
Last Revised:	21.04.2004

This is an Implementation File;

Notes:
	
*/

/*

*/


#include "Arkanoid.h"
#include "GameState.h"
#include "NormalGame.h"
#include "ObjectManager.h"


namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 21.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CNormalGame::CNormalGame()
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
	CNormalGame::~CNormalGame()
	{
	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Game State
	//=============================================
	bool CNormalGame::Init()
	{
		log << "CNormalGame::Init() - initializing Normal Game state\n";

		CGameRules gameRules;	//game rules

		gameRules.bUseGravity = false;
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
	//Last Revised: 19.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Game State
	//=============================================
	bool CNormalGame::DeInit()
	{
		log <<"CNormalGame::DeInit() - deinitializing Normal Game state\n";
		CGame::GetSingleton().objectManager.DeInit();
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
	void CNormalGame::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen
		glLoadIdentity();
		glColor3f(1.0f,1.0f,1.0f);	//white

		glEnable(GL_TEXTURE_2D);

		CGame::GetSingleton().objectManager.Update(dT);
		CGame::GetSingleton().objectManager.Draw();

	}
} //end of namespace ARK
