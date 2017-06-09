#ifndef __ARK_OBJECT_MANAGER_H__
#define __ARK_OBJECT_MANAGER_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 21.04.2004
Last Revised:	08.07.2004

Implementation File: ObjectManager.h

Notes:
	
*/

/*

  Contains also CGameRules ans CLevelInfo classes - i added them here to avoid making another *.h/*.cpp

*/

#include "Arkanoid.h"
#include "Actor.h"
#include "StaticText.h"
#include "Bricks.h"
#include "Paddle.h"
#include "Ball.h"

namespace ARK
{
	enum E_BRICK_TYPES
	{
		BRICK_TYPE_NORMAL = 1,	//normal brick
		BRICK_TYPE_HARDENED = 2,	//hardened brick
		BRICK_TYPE_NEOSTEEL = 3,	//neosteel brick
		BRICK_TYPE_RUBBER = 4	//rubber brick
	};
	class CLevelInfo
	{
	public:
		char levelName[64];	//name of this level
		char nextLevelName[64];	//FILE name of next level
		int initialBrickCount;	//initial brick count

		struct SBrickOverrideTable	//internal structure holding overrides for brick data
		{
			int brickType;	//type of overriden brick
			int brickHealth;	//new health
			int brickScore;	//new score
		};

		std::vector<SBrickOverrideTable> brickOverrideTable;	//brick override table

		CStringTable dataOverrideTable;	//for overridind data.tbl

		std::vector<CBrick*> liveBrickList;	//list of alive bricks
		std::vector<CBrick*> deadBrickList;	//list of dead bricks
		CSprite backgroundImage;	//background image

		//functions

		bool Load(const char* fileName);	//load from file
		bool Unload();	//deinitialize

		CBrick* CreateBrickFromID(int brickID);	//factory method for bricks

	};
	class CGameRules
	{
	public:
		//various booleans
		bool bUseGravity;	//use gravity?

		//countdown type
		enum COUNTDOWN_TYPE
		{
			CT_NONE = 0,
			CT_TOZERO = CT_NONE + 1,
			CT_FROMZERO = CT_NONE + 2

		} countdownType;

		enum VICTORY_CONDITIONS
		{
			VC_NONE = 0,
			VC_NOBRICKS = VC_NONE + 1,	//no bricks remaining
			VC_TIMEOUT = VC_NONE +1
		} victoryConditions;

		enum DEFEAT_CONDITIONS
		{
			DC_NONE = 0,
			DC_NOLIVES = DC_NONE + 1,
			DC_TIMEOUT = DC_NONE + 2,
			DC_LOSTBALL = DC_NONE + 3
		} defeatConditions;

		bool bShowTimer;	//show count down timer
		bool bNoPowerups;	//no powerups
		bool bTimeAttack;	//powerups == time stops
		bool bRespawnBricks;	//respawn bricks

		bool bNoNextLevel;	//no next level

	};

	class CObjectManager
	{
	private:
	protected:
		//typedefs
		typedef std::vector<CActor*> ActorList;
		typedef std::vector<CActor*>::iterator ActorListIterator;

		//enums
		enum GAMEPLAY_MODE
		{
			GPM_PLAYING = 0,
			GPM_VICTORY = GPM_PLAYING -1,
			GPM_DEFEAT = GPM_PLAYING - 2,
			GPM_GAMEOVER = GPM_PLAYING - 3,
			GPM_WAITING_UNTIL_USER_READY = GPM_PLAYING - 4,
			GPM_PAUSE = GPM_PLAYING - 5
		} gameplayMode;

		//vars
		ActorList actorList;	//list of all game actors

		CLevelInfo* level;	//a level

		//bricklist moved to CLevelInfo class

		//std::vector<CBrick*> brickList;	//list of all bricks
		std::vector<CBall*> ballList;	//list of all balls
		//std::list<CPowerup*> powerupList;	//list of all powerups

		CPaddle * paddle;

		//sounds
		int victorySound;	//victory sound
		int defeatSound;	//defeat sound
		int gameOverSound;	//game over sound
		int ballBounceSound;	//ball bounce sound
		int ballDestroySound;	//ball destroying sound
		int pauseSound;	//game pause sound
		
		int musicHandle;	//music handle

		CGameRules gameRules;	//game rules

		int nStartingBricks;	//number of starting bricks

		int score;	//player`s score
		int lives;	//player`s lives
		float timer;	//countdown timer

		float gameModeDelay;	//game mode pause

		//CStringTable stat_txt;	//string table

		CStaticText timerText;	//timer text
		CStaticText scoreText;	//score text
		CStaticText livesText;	//lives text
		CStaticText victoryMessage;	//victory message
		CStaticText defeatMessage;	//defeat message
		CStaticText endGameMessage;	//end - game message
		CStaticText pauseMessage;	//pause - game message
		CStaticText waitUntilReadyMessage;	//wait until ready message

		//utility functions
		inline bool RectangleCollision(Vector2 & position1, Vector2 & bb1, Vector2 & position2, Vector2 & bb2);
		/*int GetBrickCount()
		{
			int count = 0;	//brick count
			//for each brick...
			for(std::vector<CBrick*>::iterator br_itor = brickList.begin() ; br_itor != brickList.end() ; ++br_itor)
			{
				//if visible
				if( ( (*br_itor)->bVisible) )
				{
					++count;	//increment count
				}
			}
			return count;
		}*/
	public:

		CObjectManager();	//constructor
		~CObjectManager();	//destructor
		bool Init(CGameRules _gameRules);	//initialize object manager
		bool DeInit();	//deinitialize object manager

		bool LoadLevel(const char* newLevel);	//load a level

		void Update(float dT);	//update all objects
		void Draw();	//draw everything

		//helper functions
		void ProcessGeneric(float dT);	//general stuff
		void ProcessPaddle(float dT);	//process paddle - related stuff
		void ProcessCollisions(float dT);	//process ball to anything collisions
		void ProcessRules(float dT);	//process game rules
	};


	//=============================================
	//Function: RectangleCollision()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 17.05.2004
	//
	//Returns: true if collide; false otherwise
	//Parameters: 2 Bounding Rectangles (position & size)*2
	//Description:
	//	Checks collision between two given Bounding Rectangles,
	//	described as their center, and size
	//=============================================
	inline bool CObjectManager::RectangleCollision(Vector2& position1, Vector2 & bb1, Vector2 & position2, Vector2 & bb2)
	{
		
		if( ( (position1.x + bb1.x/2) > (position2.x - bb2.x/2) )&& ( ( position1.x - bb1.x/2) < (position2.x + bb2.x/2) ) )
		{
			if( ( ( position1.y + bb1.y/2) > (position2.y - bb2.y/2) ) && ( ( position1.y - bb1.y/2) < (position2.y + bb2.y/2) ) )
			{
				return true;	//COLLIDING!
			}
		}
		return false;	//NOT COLLIDING!
	}


} //end of namespace ARK

#endif //__ARK_OBJECT_MANAGER_H__