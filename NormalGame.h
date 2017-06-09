#ifndef __ARK_NORMAL_GAME_H__
#define __ARK_NORMAL_GAME_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 21.04.2004
Last Revised:	21.04.2004

Implementation File: NormalGame.cpp

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "TestGameState.h"
#include "StaticText.h"

namespace ARK
{
	class CNormalGame: public CGameState
	{
	private:
	
	public:
		CNormalGame();	//constructor
		~CNormalGame();	//destructor

		bool Init();	//initialize
		void Update(float dT);	//update
		bool DeInit();	//deinitialize

	};

} //end of namespace ARK

#endif //__ARK_NORMAL_GAME_H__