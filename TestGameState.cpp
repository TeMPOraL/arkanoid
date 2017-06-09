/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 23.03.2004
Last Revised:	19.04.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "TestGameState.h"

namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 23.03.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CTestGameState::CTestGameState()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 23.03.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CTestGameState::~CTestGameState()
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
	bool CTestGameState::Init()
	{
		log << "CTestGameState::Init() - initializing Test game state\n";
		//no more needs for testing Pseudo Randomizer - it works correct, or at least I think so
		//(I hope that I won`t have to submit previous sentence on GameAI.com in section "Famous Last Words" :) )
		//log << "->" << CGame::GetSingleton().randomizer.Rand(128) <<"\n" << CGame::GetSingleton().randomizer.FRand() << "\n";

		logoHandle = CGame::GetSingleton().spriteMgr.Load("font2.bmp");
		CGame::GetSingleton().spriteMgr.SetFrameCount(logoHandle, 16, 16);
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
	bool CTestGameState::DeInit()
	{
		log <<"CTestGameState::DeInit() - deinitializing Test game state\n";
		CGame::GetSingleton().spriteMgr.UnloadAll();	//unload all sprites
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
	void CTestGameState::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen and the depth buffer
		glLoadIdentity();
		//glTranslatef(0.0f,0.0f,-3.0f);

		if(CGame::GetSingleton().inputSystem.GetKeyboard()->GetKeyState(DIK_Q) == true)
		{
			CGame::GetSingleton().Quit();
		}

		glDisable(GL_TEXTURE_2D);
		if((CGame::GetSingleton().inputSystem.GetKeyboard()->GetKeyState(DIK_Z) == true))
		{
			glBegin(GL_TRIANGLES);
			{
				//glColor3f(0.0f,1.0f,1.0f);
				glColor3f(CGame::GetSingleton().randomizer.FRand(),CGame::GetSingleton().randomizer.FRand(),CGame::GetSingleton().randomizer.FRand());
				glVertex2f(200.0f,0.0f);
				
				glColor3f(CGame::GetSingleton().randomizer.FRand(),CGame::GetSingleton().randomizer.FRand(),CGame::GetSingleton().randomizer.FRand());
				glVertex2f(0.0f,200.0f);

				glColor3f(CGame::GetSingleton().randomizer.FRand(),CGame::GetSingleton().randomizer.FRand(),CGame::GetSingleton().randomizer.FRand());
				glVertex2f(200.0f,200.0f);
			}
			glEnd();
		}
		else
		{

			glBegin(GL_TRIANGLES);
			{
				glColor3f(1.0f,0.0f,0.0f);
				glVertex3f(1.0f,0.0f,0.0f);
				
				glColor3f(0.0f,1.0f,0.0f);
				glVertex3f(0.0f,1.0f,0.0f);

				glColor3f(0.0f,0.0f,1.0f);
				glVertex3f(1.0f,1.0f,0.0f);
			}
			glEnd();
		}
		glEnable(GL_TEXTURE_2D);

		glColor4f(0.0f,1.0f,1.0f,0.75f);	//a bit of transparency

		CGame::GetSingleton().spriteMgr.Draw(logoHandle, 'Q' - 31, Vector2(400,300), Vector2(400,300));
		
	}

} //end of namespace ARK