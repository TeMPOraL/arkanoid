/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 23.03.2004
Last Revised:	23.03.2004

This is an Implementation File:

Notes:
	
*/

/*

  CGameStateMgr class

*/

#include "Arkanoid.h"
#include "GameStateMgr.h"

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
	//	Initializes Game State Manager
	//=============================================
	bool CGameStateMgr::Init()
	{
		log << "CGameStateMgr::Init() - Initializing Game State Manager\n";
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
	//	Deinitializes Game State Manager
	//=============================================
	bool CGameStateMgr::DeInit()
	{
		if(state != NULL)
		{
			state->DeInit();	//disable state
			delete state;	//delete state
			state = NULL;	//set pointer to nothing
		}
		log << "CGameStateMgr::DeInit() - Deinitializing Game State Manager\n";
		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 23.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: Delta Time
	//Description:
	//	Updates active state
	//=============================================
	bool CGameStateMgr::Update(float deltaT)
	{
		if(bShouldChangeState)	//if need to change states
		{
			ChangeState();	//change state
			bShouldChangeState = false;	//zero flag
		}
		if(state == NULL)	//if no state active
		{
			return true;
		}
		
		state->Update(deltaT);	//update state
		return true;	//return
	}

	//=============================================
	//Function: SetState()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 23.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: new state ID
	//Description:
	//
	//=============================================
	bool CGameStateMgr::SetState(GAME_STATES newState)
	{
		this->newState = newState;	//set new state
		bShouldChangeState = true;	//mark request of state change
		return true;
	}


	//=============================================
	//Function: ChangeState()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 21.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Changes game state
	//=============================================
	void CGameStateMgr::ChangeState()
	{
		if(currentState == newState)	//if the new state is the same as the old one
		{
			//reinitialize
			state->DeInit();
			state->Init();
			return;
		}
		if(state != NULL)
		{
			state->DeInit();	//deinitialize state
			delete state;	//delete old state
		}

		switch(newState)	//select new state
		{
			case GS_TEST:	//just a test state
			{
				state = new CTestGameState();
				break;
			}
			case GS_INTRO:	//intro mode
			{
				state  = new CIntro();	//new intro state
				break;
			}
			case GS_MAINMENU:
			{
				state = new CMainMenu();	//main menu
				break;
			}
			case GS_NORMAL_GAME:
			{
				state = new CNormalGame();	//normal game
				break;
			}
			case GS_TIMEATTACK_GAME:
			{
				state = new CTimeAttackGame();	//time attack game
				break;
			}
			case GS_SURVIVAL_GAME:
			{
				state = new CSurvivalGame();	//survival game
				break;
			}
			case GS_GRAVITY_GAME:
			{
				state = new CGravityGame();	//gravity game
				break;
			}
			case GS_CREDITS:
			{
				state = new CCredits();	//credits & thanks
				break;
			}
			//GS_NULL and unhandled states
			case GS_NONE:
			default:
			{
				state = NULL;
				break;
			}
		}
		if(state!=NULL)	//if state != GS_NULL
		{
			state->Init();	//initialize state
		}
		currentState = newState;	//set current state
		newState = GS_NONE;	//set new state to none
		return;
	}

} //end of namespace ARK