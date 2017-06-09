#ifndef __ARK_GAME_STATE_H__
#define __ARK_GAME_STATE_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 21.02.2004
Last Revised:	21.02.2004

Implementation File: None

Notes:
	
*/

/*


*/

namespace ARK
{
	class CGameState
	{
	public:
		CGameState(){}	//default constructor
		virtual ~CGameState(){}	//virtual destructor

		virtual bool Init()=0;	//Initialize Game State
		virtual void Update(float deltaT)=0;	//Update Game State
		virtual bool DeInit()=0;	//DeInitialize Game State

	};


} //end of namespace ARK

#endif //__GAME_STATE_H__