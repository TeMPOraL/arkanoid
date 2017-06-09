#ifndef __ARK_TEST_GAME_STATE_H__
#define __ARK_TEST_GAME_STATE_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 23.03.2004
Last Revised:	15.04.2004

Implementation File: TestGameState.cpp

Notes:
	
*/

/*

*/

#include "Arkanoid.h"

namespace ARK
{
	class CTestGameState : public CGameState
	{
	private:
		int logoHandle;	//logo sprite handle
	public:
		CTestGameState();	//constructor
		~CTestGameState();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};
}

#endif //__ARK_TEST_GAME_STATE_H__