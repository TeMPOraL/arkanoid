/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 27.04.2004
Last Revised: 29.05.2004

This is an Implementation File

Notes:
	
*/

/*

  Actor is a base class for all game world objects.

*/

#include "Arkanoid.h"
#include "Actor.h"

namespace ARK
{

	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 27.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CActor::CActor()
	{
		refCount = 1;
	}

	//=============================================
	//Function: DefaultProperties()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Sets all variables to default
	//=============================================
	void CActor::DefaultProperties()
	{
		bDeleteMe = false;
		bCollide = true;	//collisions
		bVisible = true;	//visible
		
		position.Zero();
		velocity.Zero();
		forces.Zero();

		mass = 1.0f;	//one Kg
		damp = 1.0f;	//damping

		physicsMode = PHYSICS_NONE;	//still object
		BBSize = Vector2(1,1);

		health = 100;
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
	void CActor::PostBeginPlay(CStringTable * dataStrings)
	{
	}

	//=============================================
	//Function: PreEndPlay()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	void CActor::PreEndGame()
	{
	}

	//=============================================
	//Function: Tick()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 18.04.2004
	//
	//Returns: nothing
	//Parameters: Time elapsed between this and last game cycle
	//Description:
	//	Preforms some time-connected actions
	//=============================================
	void CActor::Tick(float dT)
	{
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Draws actor
	//=============================================
	void CActor::Draw()
	{
	}

	//=============================================
	//Function: ProcessCollisions()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: true if approved, false if discarded
	//Parameters: other actor involved in collision
	//Description:
	//	Collision Processing
	//=============================================
	bool CActor::ProcessCollision(CActor * other)
	{
		TakeDamage(10);
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
	bool CActor::TakeDamage(int damage)
	{
		health -= damage;	//take damage
		if(health <= 0)	//no health
		{
			Destroy();	//destroy object
			return true;
		}
		//return true;
		return false;
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
	int CActor::EvaluatePointValue()
	{
		return 0;
	}

	//=============================================
	//Function: Destroy()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: true if approved, false if discarded
	//Parameters: none
	//Description:
	//
	//=============================================
	bool CActor::Destroy()
	{
		Delete();
		return true;
	}

	//=============================================
	//Function: Delete()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: true if approved, false if discarded
	//Parameters: none
	//Description:
	//
	//=============================================
	bool CActor::Delete()
	{
		bDeleteMe = true;	//mark as ready to delete
		return true;
	}


} //end of namespace ARK