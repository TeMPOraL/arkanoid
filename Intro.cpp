/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 219.04.2004
Last Revised:	19.04.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "Intro.h"



namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CIntro::CIntro()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CIntro::~CIntro()
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
	bool CIntro::Init()
	{
		log << "CIntro::Init() - initializing Intro game state\n";
		
		//logoHandle = CGame::GetSingleton().spriteMgr.Load("biglogo.bmp");
		glClearColor(0.0f,0.0f,0.0f,0.0f);	//set clear color to black
		
		//TeMPOraL Software logo initialization
		TSLogoHandle = CGame::GetSingleton().spriteMgr.Load(CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_TS_LOGO).c_str());	//handle
		TSLogoDelay = 2.5;	//2.5 seconds
		
		//Arkanoid logo initialization
		ARKLogoHandle = CGame::GetSingleton().spriteMgr.Load(CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_ARKANOID_LOGO).c_str());
		ARKLogoDelay = 2.5;	//same 2.5 seconds
		delayBetweenLogos = 1;	//one second between

		accumulatedTime = 0;	//beginning == 0 seconds accumulated

		CGame::GetSingleton().timer.GetElapsedSeconds();	//just to reset timer because of a pause during loading intro

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
	bool CIntro::DeInit()
	{
		log <<"CIntro::DeInit() - deinitializing Intro game state\n";
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
	void CIntro::Update(float dT)
	{
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);	//clear the screen
		glLoadIdentity();
		glColor3f(1.0f,1.0f,1.0f);	//white

		accumulatedTime += dT;	//add time

		//if pressed either space or enter, skip logo presentation
		if( (CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_SPACE)) || (CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_RETURN)) )
		{
			log <<"CIntro::Update() - User requested to skip intro by pressing Space or Enter\n";
			CGame::GetSingleton().gameMgr.SetState(GS_MAINMENU);	//set to test state
			return;
		}

		if(accumulatedTime < TSLogoDelay)	//display TeMPOraL Software logo?
		{
			CGame::GetSingleton().spriteMgr.Draw(TSLogoHandle, -1, Vector2(400,300), Vector2(400,300));
			return;
		}
		if(accumulatedTime < (TSLogoDelay + delayBetweenLogos))	//pause - draw nothing
		{
			return;
		}
		if(accumulatedTime < (TSLogoDelay + delayBetweenLogos + ARKLogoDelay))	//display Arkanoid logo?
		{
			CGame::GetSingleton().spriteMgr.Draw(ARKLogoHandle, -1, Vector2(400,300), Vector2(800,600));
			return;
		}
		//end of logo showing
		CGame::GetSingleton().gameMgr.SetState(GS_MAINMENU);	//set to test state
		//glTranslatef(0.0f,0.0f,-3.0f);
	}

} //end of namespace ARK