#ifndef __ARK_GAME_STATE_MGR_H__
#define __ARK_GAME_STATE_MGR_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 23.03.2004
Last Revised:	23.03.2004

Implementation File: GameStateMgr.cpp

Notes:
	
*/

/*


*/
#include "GameState.h"

enum GAME_STATES
{
	GS_NONE = 0,
	GS_INTRO = GS_NONE - 1,
	GS_MAINMENU = GS_NONE - 2,
	GS_NORMAL_GAME = GS_NONE - 3,
	GS_TIMEATTACK_GAME = GS_NONE - 4,
	GS_SURVIVAL_GAME = GS_NONE -5,
	GS_GRAVITY_GAME = GS_NONE - 6,
	GS_CREDITS = GS_NONE - 7,
	GS_TEST = 255
};

namespace ARK
{
	class CGameStateMgr
	{
	private:
		GAME_STATES currentState;	//current state
		GAME_STATES newState;	//new state to be set

		CGameState * state;	//state object

		bool bShouldChangeState;	//should the Game State Manager change state?

		void ChangeState();	//do a state change

	public:
		CGameStateMgr():state(NULL), currentState(GS_NONE), newState(GS_NONE), bShouldChangeState(false){}
		~CGameStateMgr(){}

		bool Init();	//initialize
		bool Update(float deltaT);	//update
		bool DeInit();	//deinitialize

		bool SetState(GAME_STATES newState);
	};	//end of class CGameStateMgr
} //end of namespace ARK


#endif //_ARK_GAME_STATE_MGR_H_