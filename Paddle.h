#ifndef __ARK_PADDLE_H__
#define __ARK_PADDLE_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 22.04.2004
Last Revised:	29.05.2004

Implementation File: Paddle.cpp

Notes:
	
*/

/*



*/

namespace ARK
{

	class CPaddle : public CActor
	{
	private:
	protected:

		int spriteHandle;	//handle to used image

		enum PADDLE_ANIMATION_SEQUENCE
		{
			PAS_NONE = 0,			//[0 frames]
			PAS_INITIAL = PAS_NONE - 1,	//[x frames]	initial == default
			PAS_BOUNCING = PAS_NONE - 2	//[y frames]	when got hit
		} currAnimationSequence;

		float frameTime;	//elapsed time of a single frame
		int curFrame;	//current frame
	public:
		
		DECLARE_SUPER(CActor);

		CPaddle::CPaddle();	//constructor
		CPaddle::~CPaddle(){}	//destructor

		void DefaultProperties();	//set everything to default

		void PostBeginPlay(CStringTable * dataStrings);	//called just after creating object, but during the game.
		void PreEndGame();	//called just before ending the game
		
		void Tick(float dT);
		void Draw();	//draw our actor

		bool TakeDamage(int damage);	//take damage
		bool ProcessCollision(CActor * other);	//process collision

		bool Destroy();	//destroy actor, with all animations & stuff
		bool Delete();	//delete actor, with all deinitializations & stuff

	};


} //end of namespace ARK

#endif //__ARK_PADDLE_H__