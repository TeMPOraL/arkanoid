/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 22.04.2004
Last Revised: 29.05.2004

This is an Implementation File;

Notes:
	
*/

/*


*/

#include "Arkanoid.h"
#include "Paddle.h"

namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CPaddle::CPaddle()
	{

	}

	//=============================================
	//Function: DefaultProperties
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 24.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Sets all variables to default
	//=============================================
	void CPaddle::DefaultProperties()
	{
		Super::DefaultProperties();
		physicsMode = PHYSICS_FLYING;
		BBSize = Vector2(75,15);
		spriteHandle = -1;
		currAnimationSequence = PAS_NONE;
		frameTime = 0;
		curFrame = 1;
		damp = 1.5f;
	}

	//=============================================
	//Function: PostBeginPlay()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 29.05.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	void CPaddle::PostBeginPlay(CStringTable * dataStrings)
	{
		if(dataStrings)
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load( CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_PADDLE_SPRITE).c_str() );
		}
		else
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load("gfx\\paddle.bmp");
		}
		CGame::GetSingleton().spriteMgr.SetFrameCount(spriteHandle, 1, 1);
		Super::PostBeginPlay(dataStrings);
	}

	//=============================================
	//Function: PreEndPlay()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	void CPaddle::PreEndGame()
	{
		Super::PreEndGame();
	}

	//=============================================
	//Function: Tick()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: Time elapsed between this and last game cycle
	//Description:
	//	Preforms some time-connected actions
	//=============================================
	void CPaddle::Tick(float dT)
	{
		Super::Tick(dT);
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Draws actor
	//=============================================
	void CPaddle::Draw()
	{
		CGame::GetSingleton().spriteMgr.Draw(spriteHandle, curFrame, position, BBSize);
	}

	//=============================================
	//Function: ProcessCollisions()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 18.04.2004
	//
	//Returns: true if approved, false if discarded
	//Parameters: other actor involved in collision
	//Description:
	//	Collision Processing
	//=============================================
	bool CPaddle::ProcessCollision(CActor * other)
	{
		return true;
	}

	//=============================================
	//Function: TakeDamage()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.05.2004
	//
	//Returns: true if destroyed; false otherwise
	//Parameters: damage amount
	//Description:
	//
	//=============================================
	bool CPaddle::TakeDamage(int damage)
	{
		return Super::TakeDamage(damage);
	}

	//=============================================
	//Function: Destroy()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 18.04.2004
	//
	//Returns: true if approved, false if discarded
	//Parameters: none
	//Description:
	//
	//=============================================
	bool CPaddle::Destroy()
	{
		return Super::Destroy();
	}

	//=============================================
	//Function: Delete()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 18.04.2004
	//
	//Returns: true if approved, false if discarded
	//Parameters: none
	//Description:
	//
	//=============================================
	bool CPaddle::Delete()
	{
		return Super::Delete();
	}

} //end of namespace ARK