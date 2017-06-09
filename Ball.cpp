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
#include "Ball.h"

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
	CBall::CBall()
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
	void CBall::DefaultProperties()
	{
		Super::DefaultProperties();
		BBSize = Vector2(15,15);
		//spriteHandle = -1;
		currAnimationSequence = BLAS_NONE;
		frameTime = 0;
		curFrame = 0;
		mass = 1000;
	
		for(int i = 0; i < MAX_BALL_PARTICLES ; ++i)
		{
			particles[i].lifeTime = CGame::GetSingleton().randomizer.FRand();
			particles[i].r = CGame::GetSingleton().randomizer.FRand();
			particles[i].g = CGame::GetSingleton().randomizer.FRand();
			particles[i].b = CGame::GetSingleton().randomizer.FRand();
		}
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
	void CBall::PostBeginPlay(CStringTable * dataStrings)
	{
		if(dataStrings)
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load( CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_BALL_SPRITE).c_str() );
		}
		else
		{
			spriteHandle = CGame::GetSingleton().spriteMgr.Load("gfx\\ball.bmp");
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
	void CBall::PreEndGame()
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
	void CBall::Tick(float dT)
	{
		Super::Tick(dT);

		//update particles
		for(int i = 0; i < MAX_BALL_PARTICLES ; ++i)
		{
			particles[i].r -= (dT * 0.5);	//update red
			particles[i].g -= (dT * 0.5);	//update green
			particles[i].b -= (dT * 0.5);	//update blue
			particles[i].lifeTime += dT;	//add elapsed time

			if( particles[i].lifeTime > 3.0f )	//spawn as new particle
			{
				//update position

				particles[i].position = position + Vector2((CGame::GetSingleton().randomizer.FRand() * 5) - 5, (CGame::GetSingleton().randomizer.FRand() * 5) - 5);

				particles[i].r = CGame::GetSingleton().randomizer.FRand()+0.5f;
				particles[i].g = CGame::GetSingleton().randomizer.FRand()+0.5f;
				particles[i].b = CGame::GetSingleton().randomizer.FRand()+0.5f;

				particles[i].lifeTime = 0.0f + CGame::GetSingleton().randomizer.FRand();
			}
		}

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
	void CBall::Draw()
	{
		CGame::GetSingleton().spriteMgr.Draw(spriteHandle, curFrame, position, BBSize);
		glDisable(GL_TEXTURE_2D);

		glBegin(GL_POINTS);
		{
			for(int i = 0; i < MAX_BALL_PARTICLES ; ++i)
			{
				glColor3f(particles[i].r, particles[i].g, particles[i].b);
				glVertex2f(particles[i].position.x, particles[i].position.y);
			}
		}
		glEnd();
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
	bool CBall::ProcessCollision(CActor * other)
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
	bool CBall::TakeDamage(int damage)
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
	int CBall::EvaluatePointValue()
	{
		return 0;
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
	bool CBall::Destroy()
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
	bool CBall::Delete()
	{
		memset(particles, 0 ,sizeof(particles));
		return Super::Delete();
	}

} //end of namespace ARK