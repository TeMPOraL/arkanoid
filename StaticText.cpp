/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 15.04.2004
Last Revised: 29.05.2004

This is an Implementation File

Notes:
	
*/

/*

  This class represents a static text field

*/

#include "Arkanoid.h"
#include "Actor.h"
#include "StaticText.h"

namespace ARK
{

	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 15.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CStaticText::CStaticText()
	{

	}

	//=============================================
	//Function: DefaultProperties
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 20.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Sets all variables to default
	//=============================================
	void CStaticText::DefaultProperties()
	{
		Super::DefaultProperties();
		text = "(no text)";
		bColored = false;	//default = no colors
		textAligment = TEXTALIGN_CENTER;	//centered aligment
		textLenght = 9;
		coloredTextLenght = 9;
		charSize = 16;
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
	void CStaticText::PostBeginPlay(CStringTable * dataStrings)
	{

		Super::PostBeginPlay(dataStrings);

		if(dataStrings)
		{
			fontHandle = CGame::GetSingleton().spriteMgr.Load( CGame::GetSingleton().dataStrings.GetString(STRING_DATA_OFF_FONT_SPRITE).c_str() );
		}
		else
		{
			fontHandle = CGame::GetSingleton().spriteMgr.Load("font2.bmp");
		}
		CGame::GetSingleton().spriteMgr.SetFrameCount(fontHandle, 16, 16);
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
	void CStaticText::PreEndGame()
	{
		Super::PreEndGame();
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
	void CStaticText::Tick(float dT)
	{
		Super::Tick(dT);
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 05.05.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Draws actor
	//=============================================
	void CStaticText::Draw()
	{
		Vector2 drawBegin = position;	//where to start drawing
		switch(textAligment)
		{
			case TEXTALIGN_CENTER:	//centered text
			{
				drawBegin -= Vector2(coloredTextLenght * charSize * 0.5, 0);
				break;
			}
			
			case TEXTALIGN_LEFT:	//aligned to the left
			{
				drawBegin -= Vector2(coloredTextLenght * charSize, 0);
				break;
			}

			case TEXTALIGN_RIGHT:	//aligned to the right
			{
				drawBegin += Vector2(0, 0);
				break;
			}

			default:
			{
				break;
			}

		}
		if(bColored)	//colored text
		{
			glColor3f(0.68f,0.68f,0.86f);	//default color (light blue) 0xAEAEDD
			//color tags
			for(int i = 0 ; i < textLenght ; i++)
			{
				if( text.c_str()[i] == 0x02 )	//default light blue
				{
					glColor3f(0.68f,0.68f,0.86f);
					continue;
				}
				if( text.c_str()[i] == 0x03 )	//yellow 0xDDDD11
				{
					glColor3f(0.86f,0.86f,0.06f);
					continue;
				}
				if( text.c_str()[i] == 0x04 )	//white 0xFFFFFF
				{
					glColor3f(1.0f,1.0f,1.0f);
					continue;
				}
				if( text.c_str()[i] == 0x05 )	//grey
				{
					glColor3f(0.5f,0.5f,0.5f);
					continue;
				}
				if( text.c_str()[i] == 0x06 )	//red 0xFF0000
				{
					glColor3f(1.0f,0.0f,0.0f);
					continue;
				}
				if( text.c_str()[i] == 0x07 )	//light green 0x11FF11
				{
					glColor3f(0.06f,1.0f,0.06f);
					continue;
				}

				CGame::GetSingleton().spriteMgr.Draw(fontHandle, ((text.c_str())[i]-32) , drawBegin, Vector2(charSize,charSize));
				drawBegin += Vector2(charSize,0);

			}
		}
		else	//not colored text
		{
			for(int i = 0 ; i < textLenght ; ++i)
			{
				CGame::GetSingleton().spriteMgr.Draw(fontHandle, ((text.c_str())[i]-32) , drawBegin, Vector2(16,16));
				drawBegin += Vector2(16,0);
			}
		}
	//	glBegin(GL_QUADS);
	//	{
	//		glVertex2f(position.x - 100,position.y - 25);
	//		glVertex2f(position.x + 100,position.y - 25);
	//		glVertex2f(position.x + 100,position.y + 25);
	//		glVertex2f(position.x - 100,position.y + 25);
	//	}
	//	glEnd();
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
	bool CStaticText::ProcessCollision(CActor * other)
	{
		TakeDamage(100);
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
	bool CStaticText::TakeDamage(int damage)
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
	int CStaticText::EvaluatePointValue()
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
	bool CStaticText::Destroy()
	{
		return Super::Destroy();
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
	bool CStaticText::Delete()
	{
		return Super::Delete();
	}

	//=============================================
	//Function: SetText()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 24.04.2004
	//
	//Returns: nothing
	//Parameters: new text and properties (colored mark, aligment)
	//Description:
	//
	//=============================================
	void CStaticText::SetText(const char * txt, bool bIsColored, TEXTALIGN align, int letterSize)
	{
		text = txt;	//set text
		bColored = bIsColored;	//set color mark
		textAligment = align;	//set text aligment
		charSize = letterSize;

		//count text lenght
		textLenght = 0;
		coloredTextLenght = 0;

		for(int i = 0 ; i < text.size() ; i++)
		{
			if( ( * (text.c_str()) +i ) == '/0')	//if null
			{
				break;
			}
			++textLenght;	//increment text lenght
			
			//check for color tags
			if( (( * (text.c_str()) + i) != 0x1) || (( * (text.c_str()) + i) != 0x2) || (( * (text.c_str()) + i) != 0x3) || (( * (text.c_str()) + i) != 0x4) ||
				(( * (text.c_str()) + i) != 0x5) || (( * (text.c_str()) + i) != 0x6) || (( * (text.c_str()) + i) != 0x7))
			{
				++coloredTextLenght;
			}
		}

	}

	//=============================================
	//Function: GetText()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: currently used text
	//Parameters: none
	//Description:
	//
	//=============================================
	std::string CStaticText::GetText()
	{
		return text;	//get text
	}


} //end of namespace ARK