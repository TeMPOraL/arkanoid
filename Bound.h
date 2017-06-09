#ifndef __ARK_BOUND_H__
#define __ARK_BOUND_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 18.04.2004
Last Revised:	18.04.2004

Implementation File: Bound.cpp

Notes:
	
*/

/*

  CBound - class representing a boundary, from whitch the ball bounces.

*/

namespace ARK
{
	class CBound : public CActor
	{
	private:
	protected:
	public:

		DECLARE_SUPER(CActor);

		CBound::CBound();	//constructor
		CBound::~CBound(){}	//destructor

		void DefaultProperties();	//set everything to default

		void PostBeginPlay();	//called just after creating object, but during the game.
		void PreEndGame();	//called just before ending the game
		
		void Tick(float dT);
		void Draw();	//draw our actor

		bool TakeDamage(int damage);	//take damage
		bool ProcessCollision(CActor * other);	//process collision

		bool Destroy();	//destroy actor, with all animations & stuff
		bool Delete();	//delete actor, with all deinitializations & stuff

	};

} //end of namespace ARK

#endif //__ARK_BOUND_H__