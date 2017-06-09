#ifndef __ARK_STATIC_TEXT_H__
#define __ARK_STATIC_TEXT_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 15.04.2004
Last Revised:	29.05.2004

Implementation File: StaticText.cpp

Notes:
	
*/

/*

  This class represents a static text field

*/

#include "Arkanoid.h"
#include "Actor.h"

enum TEXTALIGN
{
	TEXTALIGN_NONE = 0,	//as-is :D
	TEXTALIGN_LEFT,	//to the left
	TEXTALIGN_RIGHT,	//to the right
	TEXTALIGN_CENTER	//to the center
};

namespace ARK
{
	class CStaticText : public CActor
	{
	private:
	protected:

		int fontHandle;	//handle for a font used to display text
		//text aligment
		TEXTALIGN textAligment;
		bool bColored;	//if true, then game`ll check text for color tags

		//thoese two variables are for speeding up text drawing by precounting text lenght
		int textLenght;	//lenght of uncolored text
		int coloredTextLenght;	//lenght of colored text

		int charSize;	//single character size
	public:

		DECLARE_SUPER(CActor);
		
		std::string text;	//text to display

		CStaticText();	//constructor
		~CStaticText(){}	//destructor

		void DefaultProperties();	//set everything to default

		void PostBeginPlay(CStringTable * dataStrings);	//called just after creating object, but during the game.
		void PreEndGame();	//called just before ending the game

		void Tick(float dT);	//tick
		void Draw();	//draw our actor
		
		bool TakeDamage(int damage);	//take damage
		bool ProcessCollision(CActor * other);	//process collision
		int EvaluatePointValue();	//evaluate value

		bool Destroy();	//destroy actor, with all animations & stuff
		bool Delete();	//delete actor, with all deinitializations & stuff

		void SetText(const char * txt, bool bIsColored, TEXTALIGN align, int letterSize);	//set new text
		std::string GetText();	//get text

	};

} //end of namespace ARK

#endif //__ARK_STATIC_TEXT_H__