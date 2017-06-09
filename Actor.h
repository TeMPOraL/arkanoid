#ifndef __ARK_ACTOR_H__
#define __ARK_ACTOR_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 15.04.2004
Last Revised:	29.05.2004

Implementation File: Actor.cpp [?]

Notes:
	
*/

/*

  Actor is a base class for all game world objects.

*/

#include "Arkanoid.h"

namespace ARK
{
	class CActor
	{
	private:
	protected:

		int refCount;	//Reference Count
	public:
		//physics
		Vector2 position;	//Actor`s position
		Vector2 velocity;	//Actor`s velocity
		Vector2 forces;	//Sum of all forces; F = ma => a = F/m <--- acceleration

		float mass;	//mass of the actor
		float damp;	//multipled with speed of another object when colliding. damp < 1 means slower movement; > 1 - faster

		bool bCollide;	//true = can collide; false = cannot
		bool bVisible;	//true = visible; false = not

		enum ePhysics
		{
			PHYSICS_NONE = 0,	//no bounces, etc. - stays still or does what is supposed to do
			PHYSICS_FLYING,	//no gravity, just bouncing around
			PHYSICS_FALLING	//bouncing around, but with gravity factor
		} physicsMode;

		Vector2 BBSize;	//dimmensions of a Bounding Box; used for almost everything ;D

		//general
		int health;	//hp; 0 == destroyed
		bool bDeleteMe;	//delete this object in the next game loop

		//general functions
		CActor();	//constructor
		virtual ~CActor(){};	//virtual destructor

		virtual void DefaultProperties();	//set everything to default

		virtual void PostBeginPlay(CStringTable * dataStrings);	//called just after creating object, but during the game.
		virtual void PreEndGame();	//called just before ending the game
		//heheheh, there`s no update ! :) everything is done by game state :D
		virtual void Tick(float dT);	//only tick serving for something like update, but it`s not the same
		virtual void Draw();	//draw our actor

		virtual bool TakeDamage(int damage);	//take damage
		virtual bool ProcessCollision(CActor * other);	//process collision

		virtual int EvaluatePointValue();	//evaluate point value of an actor

		virtual bool Destroy();	//destroy actor, with all animations & stuff
		virtual bool Delete();	//delete actor, with all deinitializations & stuff

		void AddRef()
		{
			++refCount;
		}

		void Release()
		{
			if( (--refCount) <= 0)
			{
				delete this;	//remove object
			}
		}
	};

}

#endif //__ARK_ACTOR_H__