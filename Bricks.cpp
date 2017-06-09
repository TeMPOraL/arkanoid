/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 22.04.2004
Last Revised: 29.05.2004

This is an Implementation File;

Notes:
	
*/

/*

  This file contains all brick classes implementation

*/

#include "Arkanoid.h"
#include "Bricks.h"

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
	CBrick::CBrick()
	{

	}

	//=============================================
	//Function: DefaultProperties
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Sets all variables to default
	//=============================================
	void CBrick::DefaultProperties()
	{
		Super::DefaultProperties();
		BBSize = Vector2(50,20);
	//	spriteHandle = -1;
		currAnimationSequence = BAS_NONE;
		frameTime = 0;
		curFrame = 0;
	}

	//=============================================
	//Function: PostBeginPlay()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	void CBrick::PostBeginPlay(CStringTable * dataStrings)
	{
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
	void CBrick::PreEndGame()
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
	void CBrick::Tick(float dT)
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
	void CBrick::Draw()
	{
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
	bool CBrick::ProcessCollision(CActor * other)
	{
		return true;
	}

	//=============================================
	//Function: TakeDamage()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 18.04.2004
	//
	//Last Revised: 05.05.2004
	//Parameters: damage amount
	//Description:
	//
	//=============================================
	bool CBrick::TakeDamage(int damage)
	{
		return Super::TakeDamage(damage);
	}

	//=============================================
	//Function: EvaluatePointValue()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 24.04.2004
	//
	//Returns: point value
	//Parameters: none
	//Description:
	//
	//============================================
	int CBrick::EvaluatePointValue()
	{
		return 1;
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
	bool CBrick::Destroy()
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
	bool CBrick::Delete()
	{
		return Super::Delete();
	}

	//=============================================
	//CNormalBrick
	//=============================================

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
	CNormalBrick::CNormalBrick()
	{
	}

	//=============================================
	//Function: DefaultProperties
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.05.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Sets all variables to default
	//=============================================
	void CNormalBrick::DefaultProperties()
	{
		Super::DefaultProperties();
		health = 5;
	}

	//=============================================
	//Function: PostBeginPlay()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	void CNormalBrick::PostBeginPlay(CStringTable * dataStrings)
	{
		Super::PostBeginPlay(dataStrings);
		//load gfx
		if(dataStrings)
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load( CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_NORMAL_BRICK_SPRITE).c_str() );
		}
		else
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load("gfx\\normal_brick.bmp");
		}
		CGame::GetSingleton().spriteMgr.SetFrameCount(spriteHandle, 1, 1);
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
	void CNormalBrick::PreEndGame()
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
	void CNormalBrick::Tick(float dT)
	{
		Super::Tick(dT);
		//frame changes
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
	void CNormalBrick::Draw()
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
	bool CNormalBrick::ProcessCollision(CActor * other)
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
	bool CNormalBrick::TakeDamage(int damage)
	{
		return Super::TakeDamage(damage);
	}

	//=============================================
	//Function: EvaluatePointValue()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 24.04.2004
	//
	//Returns: point value
	//Parameters: none
	//Description:
	//
	//============================================
	int CNormalBrick::EvaluatePointValue()
	{
		return 50;
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
	bool CNormalBrick::Destroy()
	{
		bDeleteMe = true;
		return true;
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
	bool CNormalBrick::Delete()
	{
		return Super::Delete();
	}


	//=============================================
	//CHardenedBrick
	//=============================================

	
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
	CHardenedBrick::CHardenedBrick()
	{
	}

	//=============================================
	//Function: DefaultProperties
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Sets all variables to default
	//=============================================
	void CHardenedBrick::DefaultProperties()
	{
		Super::DefaultProperties();

		health = 36;
	}

	//=============================================
	//Function: PostBeginPlay()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	void CHardenedBrick::PostBeginPlay(CStringTable * dataStrings)
	{
		Super::PostBeginPlay(dataStrings);

		if(dataStrings)
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load( CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_HARDENED_BRICK_SPRITE).c_str() );
		}
		else
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load("gfx\\hardened_brick.bmp");
		}
		CGame::GetSingleton().spriteMgr.SetFrameCount(spriteHandle, 1, 1);
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
	void CHardenedBrick::PreEndGame()
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
	void CHardenedBrick::Tick(float dT)
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
	void CHardenedBrick::Draw()
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
	bool CHardenedBrick::ProcessCollision(CActor * other)
	{
		return true;
	}

	//=============================================
	//Function: TakeDamage()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 18.04.2004
	//
	//Last Revised: 05.05.2004
	//Parameters: damage amount
	//Description:
	//
	//=============================================
	bool CHardenedBrick::TakeDamage(int damage)
	{
		return Super::TakeDamage(damage);
	}

	//=============================================
	//Function: EvaluatePointValue()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 24.04.2004
	//
	//Returns: point value
	//Parameters: none
	//Description:
	//
	//============================================
	int CHardenedBrick::EvaluatePointValue()
	{
		return (health > 0) ? 25 : 75;
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
	bool CHardenedBrick::Destroy()
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
	bool CHardenedBrick::Delete()
	{
		return Super::Delete();
	}


} //end of namespace ARK