#ifndef __ARK_BRICK_H__
#define __ARK_BRICK_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 21.04.2004
Last Revised:	29.05.2004

Implementation File: Bricks.cpp

Notes:
	
*/

/*

  This file contains all brick classes

*/

namespace ARK
{
	//=============================================
	//base Brick class
	//=============================================
	class CBrick : public CActor
	{
	private:
	protected:
		int spriteHandle;	//sprite handle

		enum BRICK_ANIMATION_SEQUENCE
		{
			BAS_NONE = 0,
			BAS_INITIAL = BAS_NONE - 1,	//initial == default
			BAS_DYING = BAS_NONE - 2
		} currAnimationSequence;

		float frameTime;	//elapsed time of a single frame
		int curFrame;	//current frame

	public:

		DECLARE_SUPER(CActor);

		CBrick::CBrick();	//constructor
		CBrick::~CBrick(){}	//destructor

		void DefaultProperties();	//set everything to default

		void PostBeginPlay(CStringTable * dataStrings);	//called just after creating object, but during the game.
		void PreEndGame();	//called just before ending the game
		
		void Tick(float dT);
		void Draw();	//draw our actor

		bool TakeDamage(int damage);	//take damage
		bool ProcessCollision(CActor * other);	//process collision
		int EvaluatePointValue();	//evaluate value

		bool Destroy();	//destroy actor, with all animations & stuff
		bool Delete();	//delete actor, with all deinitializations & stuff

	};

	//=============================================
	//basic Brick class - CNormalBrick
	//=============================================
	class CNormalBrick : public CBrick
	{
	private:
	protected:
	public:

		DECLARE_SUPER(CBrick);

		CNormalBrick::CNormalBrick();	//constructor
		CNormalBrick::~CNormalBrick(){}	//destructor

		void DefaultProperties();	//set everything to default

		void PostBeginPlay(CStringTable * dataStrings);	//called just after creating object, but during the game.
		void PreEndGame();	//called just before ending the game
		
		void Tick(float dT);
		void Draw();	//draw our actor

		bool TakeDamage(int damage);	//take damage
		bool ProcessCollision(CActor * other);	//process collision
		int EvaluatePointValue();	//evaluate point value

		bool Destroy();	//destroy actor, with all animations & stuff
		bool Delete();	//delete actor, with all deinitializations & stuff

	};

	//=============================================
	//Hardened Brick
	//=============================================

	class CHardenedBrick : public CBrick
	{
	private:
	protected:
	public:

		DECLARE_SUPER(CBrick);

		CHardenedBrick::CHardenedBrick();	//constructor
		CHardenedBrick::~CHardenedBrick(){}	//destructor

		void DefaultProperties();	//set everything to default

		void PostBeginPlay(CStringTable * dataStrings);	//called just after creating object, but during the game.
		void PreEndGame();	//called just before ending the game
		
		void Tick(float dT);
		void Draw();	//draw our actor

		bool TakeDamage(int damage);	//take damage
		bool ProcessCollision(CActor * other);	//process collision
		int EvaluatePointValue();	//evaluate value

		bool Destroy();	//destroy actor, with all animations & stuff
		bool Delete();	//delete actor, with all deinitializations & stuff

	};

} //end of namespace ARK

#endif //__ARK_BRICK_H__