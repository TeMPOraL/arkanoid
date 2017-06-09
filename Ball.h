#ifndef __ARK_BALL_H__
#define __ARK_BALL_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 22.04.2004
Last Revised:	29.05.2004

Implementation File: Ball.cpp

Notes:
	
*/

/*



*/

namespace ARK
{
	const int MAX_BALL_PARTICLES = 256;	//maximum of ball praticles (per ball)
	//particle struct
	struct SBallParticle
	{
		Vector2 position;	//particle`s position
		float lifeTime;	//time alive
		union	//color
		{
			struct
			{
				float r;	//red
				float g;	//green
				float b;	//blue;
				float a;	//alpha
			};
			float color[4];	//array of R,G,B
		};
	};

	class CBall : public CActor
	{
	private:
	protected:

		int spriteHandle;	//handle to used image

		enum BALL_ANIMATION_SEQUENCE
		{
			BLAS_NONE = 0,			//[0 frames]
			BLAS_INITIAL = BLAS_NONE - 1,	//[x frames]	initial == default
			BLAS_BOUNCING = BLAS_NONE - 2	//[y frames]	when got hit
		} currAnimationSequence;

		float frameTime;	//elapsed time of a single frame
		int curFrame;	//current frame
		
		//particles
		SBallParticle particles[MAX_BALL_PARTICLES];	//particle array

	public:
		
		DECLARE_SUPER(CActor);

		CBall::CBall();	//constructor
		CBall::~CBall(){}	//destructor

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

#endif //__ARK_BALL_H__