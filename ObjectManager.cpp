/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 21.04.2004
Last Revised:	06.06.2004

This is an Implementation File:

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "ObjectManager.h"

namespace ARK
{
	//=============================================
	//LevelInfo
	//=============================================

	//=============================================
	//Function: Load()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 06.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: file name
	//Description:
	//	Loads level from file
	//=============================================
	bool CLevelInfo::Load(const char* fileName)
	{
		//help variables

		::strcpy(levelName, "[default]");

		char magic[4];	//magic number, 'A' 'R' 'K' 'L'
		unsigned int version;	//version
		unsigned int vcode;	//verification code; 0x0FF1C1A1;

		unsigned int offsetEOF;	//end of file offset
		int brickOverrides;	//brick override table entries

		log <<"CLevelInfo::Load() - Loading level from file \"" << fileName <<"\"\n";
		FILE * fIn = fopen(fileName,"rb");
		if(fIn == NULL)
		{
			log.Error("CLevelInfo::Load() - error loading level file.");
			return false;
		}

		//read header
		fread(magic, ( 4*sizeof(char) ), 1, fIn);
		if( !(magic[0] =='A' && magic[1] == 'R' && magic[2] == 'K' && magic[3] == 'L') )	//not a valid level
		{
			log <<"CLevelInfo::Load() - invalid level \"" << fileName <<"\"\n";
			return false;
		}

		fread(&version, sizeof(int), 1, fIn);	//read version
		fread(&vcode, sizeof(int), 1, fIn);	//read vcode
		fread(&offsetEOF, sizeof(int), 1, fIn);	//read offset to end of file

		fread(levelName, (64*sizeof(char)), 1, fIn);	//read level name
		fread(nextLevelName, (64*sizeof(char)), 1, fIn);	//read next level name

		fread(&initialBrickCount, sizeof(int), 1, fIn);	//read initial brick count

		if(initialBrickCount <= 0 || initialBrickCount >=256)	//something weird
		{
			log <<"CLevelInfo::Load() - very weird brick count of " << initialBrickCount <<" ; is this level valid? Stopping load process\n";
			return false;
		}

		CBrick * a_brick;	//just a brick
		int id,xpos, ypos;
		for(int i = 0; i < initialBrickCount ; ++i)
		{
			fread(&id, sizeof(int), 1 , fIn);
			a_brick = CreateBrickFromID(id);
			fread(&xpos,sizeof(int),1,fIn);
			fread(&ypos,sizeof(int),1,fIn);

			a_brick->DefaultProperties();
			a_brick->position = Vector2(xpos, ypos);

			liveBrickList.push_back(a_brick);
		}

		fread(&brickOverrides, sizeof(int), 1, fIn);	//read brick override table size
		
		if(brickOverrides < 0 || brickOverrides > 10)	//something weird happens
		{
			log <<"CLevelInfo::Load() - very weird brick override count of " << brickOverrides <<" ; is this level valid? Stopping load process\n";
			return false;
		}

		SBrickOverrideTable bot;	//just a temporary variable
		for(int j = 0; i < brickOverrides ; ++j)
		{
			fread(&bot, sizeof(SBrickOverrideTable), 1, fIn);
			brickOverrideTable.push_back(bot);
		}

		//data tbl. reading not finished!
		dataOverrideTable.LoadTable(fIn);

		fclose(fIn);
		return true;
	}

	//=============================================
	//Function: Unload()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 06.06.2004
	//
	//Returns: true on success; false on failure
	//Parameters: none
	//Description:
	//	Deinitializes all LevelInfo data.
	//=============================================
	bool CLevelInfo::Unload()
	{
		log <<"CLevelInfo::UnLoad() - Unloading level " << levelName <<"\n";
		//deinitialize lists

		for(std::vector<CBrick*>::iterator aliveItor = liveBrickList.begin() ; aliveItor != liveBrickList.end() ; )
		{
			(*aliveItor)->Release();
			liveBrickList.erase(aliveItor);
		}

		for(std::vector<CBrick*>::iterator deadItor = deadBrickList.begin() ; deadItor != deadBrickList.end() ; )
		{
			(*deadItor)->Release();
			deadBrickList.erase(deadItor);
		}
		return false;
	}

	//=============================================
	//Function: CreateBrickFromID()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 27.05.2004
	//
	//Returns: created brick
	//Parameters: brick type ID
	//Description:
	//	Factory method for creating bricks; if type invalid, returns Normal Brick
	//=============================================
	CBrick* CLevelInfo::CreateBrickFromID(int brickID)
	{
		switch(brickID)
		{
			case BRICK_TYPE_HARDENED:	//hardened brick
			{
				return new CHardenedBrick;
			}

			case BRICK_TYPE_NEOSTEEL:	//neosteel brick
			{
			}

			case BRICK_TYPE_RUBBER:	//rubber brick
			{
			}
			case BRICK_TYPE_NORMAL:	//Normal Brick
			{
				return new CNormalBrick;
			}
			default:	//any other
			{
				log <<"CLevelInfo::CreateBrickFromID() - Warning - unknown ID " << brickID <<" ; creating Normal Brick\n";
				return new CNormalBrick;	//create new Normal Brick
			}

		}
	}


	//=============================================
	//Object Manager
	//=============================================


	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 21.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CObjectManager::CObjectManager()
	{
		//some variable initializations
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 21.04.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//
	//=============================================
	CObjectManager::~CObjectManager()
	{

	}

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 08.07.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	initializes Object Manager
	//=============================================
	bool CObjectManager::Init(CGameRules _gameRules)
	{
		log <<"CObjectManager::Init() - initializing Object Manager\n";
		gameRules = _gameRules;

		level = new CLevelInfo;

		CStringTable * dataStrings = &(CGame::GetSingleton().dataStrings);

		gameplayMode = GPM_WAITING_UNTIL_USER_READY;

		gameModeDelay = 0.0f;
		
		lives = (gameRules.bTimeAttack)? 999 : 5;
		score = 0;

		if( ( gameRules.countdownType == CGameRules::CT_NONE ) || ( gameRules.countdownType == CGameRules::CT_FROMZERO ) )
		{
			timer = 0.0f;	//0 seconds
		}

		else
		{
			timer = 120.0f;	//2 mins
		}
		
		victorySound = CGame::GetSingleton().audioSystem.LoadSound("sfx\\game\\victory.wav");
		defeatSound = CGame::GetSingleton().audioSystem.LoadSound("sfx\\game\\defeat.wav");
		gameOverSound = CGame::GetSingleton().audioSystem.LoadSound("sfx\\game\\gameover.wav");
		ballBounceSound = CGame::GetSingleton().audioSystem.LoadSound("sfx\\game\\bounce.wav");
		ballDestroySound = CGame::GetSingleton().audioSystem.LoadSound("sfx\\game\\destroy.wav");
		pauseSound = CGame::GetSingleton().audioSystem.LoadSound("sfx\\game\\pause.wav");
		
		musicHandle = CGame::GetSingleton().audioSystem.LoadMusic("sfx\\game\\music1.mid");
		CGame::GetSingleton().audioSystem.PlayMusic(musicHandle);

		victoryMessage.DefaultProperties();
		victoryMessage.PostBeginPlay(dataStrings);
		victoryMessage.position =Vector2(400,300);	//center
		victoryMessage.SetText(CGame::GetSingleton().stat_txt.GetString(STAT_TXT_VICTORY_MESSAGE).c_str(), true, TEXTALIGN_CENTER, 25);

		defeatMessage.DefaultProperties();
		defeatMessage.PostBeginPlay(dataStrings);
		defeatMessage.position = Vector2(400,300);	//centered
		defeatMessage.SetText(CGame::GetSingleton().stat_txt.GetString(STAT_TXT_DEFEAT_MESSAGE).c_str(), true, TEXTALIGN_CENTER, 25);

		endGameMessage.DefaultProperties();
		endGameMessage.PostBeginPlay(dataStrings);
		endGameMessage.position = Vector2(400,300);
		endGameMessage.SetText(CGame::GetSingleton().stat_txt.GetString(STAT_TXT_ENDGAME_MESSAGE).c_str(), true, TEXTALIGN_CENTER, 25);

		waitUntilReadyMessage.DefaultProperties();
		waitUntilReadyMessage.PostBeginPlay(dataStrings);
		waitUntilReadyMessage.position = Vector2(400,300);
		waitUntilReadyMessage.SetText(CGame::GetSingleton().stat_txt.GetString(STAT_TXT_WAIT_UNTIL_READY_MESSAGE).c_str(), true, TEXTALIGN_CENTER, 20);

		pauseMessage.DefaultProperties();
		pauseMessage.PostBeginPlay(dataStrings);
		pauseMessage.position = Vector2(400,300);
		pauseMessage.SetText(CGame::GetSingleton().stat_txt.GetString(STAT_TXT_PAUSE_MESSAGE).c_str(), true, TEXTALIGN_CENTER, 30);

		livesText.DefaultProperties();
		livesText.PostBeginPlay(dataStrings);
		livesText.position = Vector2(800, 15);
		
		std::stringstream livesBuff;	//just a buffer
		livesBuff << lives;
		livesText.SetText((CGame::GetSingleton().stat_txt.GetString(STAT_TXT_LIVES_MASK) + livesBuff.str()).c_str(), true, TEXTALIGN_LEFT, 20);

		scoreText.DefaultProperties();
		scoreText.PostBeginPlay(dataStrings);
		scoreText.position = Vector2(10, 15);

		std::stringstream scoreBuff;	//just a buffer
		scoreBuff << score;
		scoreText.SetText((CGame::GetSingleton().stat_txt.GetString(STAT_TXT_SCORE_MASK) + scoreBuff.str()).c_str(), true, TEXTALIGN_RIGHT, 20);

		timerText.DefaultProperties();
		timerText.PostBeginPlay(dataStrings);
		timerText.position = Vector2(400,15);

		std::stringstream timerBuff;	//just a buffer
		timerBuff << static_cast<int>(timer);
		timerText.SetText((CGame::GetSingleton().stat_txt.GetString(STAT_TXT_TIMER_MASK) + timerBuff.str()).c_str(), true, TEXTALIGN_CENTER, 20);
		
		//create and initialize paddle
		paddle = new CPaddle;
		paddle->DefaultProperties();
		paddle->PostBeginPlay(dataStrings);

		paddle->position = Vector2(800/2, 570);	//set new paddle position to the bottom center of the screen
		
		actorList.push_back(paddle);

		//create and initialize initial ball (the first one)
		CBall * newBall = new CBall;
		newBall->DefaultProperties();
		newBall->PostBeginPlay(dataStrings);
		newBall->position = Vector2 (800/2, 600/2);
		newBall->velocity = Vector2(123,321);
		newBall->velocity.NormalizeFast();
		newBall->velocity *= 500;
		newBall->physicsMode = (gameRules.bUseGravity) ? CActor::PHYSICS_FALLING : CActor::PHYSICS_FLYING;

		ballList.push_back(newBall);
		newBall->AddRef();	//for Actor List
		actorList.push_back(newBall);

		//loading map
		LoadLevel("default.lev");

		//temporary code for "demo" purposes
		CBrick * a_brick;
		//higest row
		
		for(int i = 0 ; i < 800 / 50 ; i++)
		{
			a_brick = new CNormalBrick();
			a_brick->DefaultProperties();
			a_brick->PostBeginPlay(dataStrings);

			a_brick->position = Vector2( 25 + i * 50,100);
			actorList.push_back(a_brick);
			level->liveBrickList.push_back(a_brick);
		}

		//second row
		for( i = 0 ; i < 800 / 50 ; i++)
		{
			a_brick = new CNormalBrick();
			a_brick->DefaultProperties();
			a_brick->PostBeginPlay(dataStrings);

			a_brick->position = Vector2( 25 + i * 50, 75);

			actorList.push_back(a_brick);
			level->liveBrickList.push_back(a_brick);
		}

		for( i = 0 ; i < 800 / 50 ; i++)
		{
			a_brick = new CHardenedBrick();
			a_brick->DefaultProperties();
			a_brick->PostBeginPlay(dataStrings);

			a_brick->position = Vector2( 25 + i * 50, 50);

			actorList.push_back(a_brick);
			level->liveBrickList.push_back(a_brick);
		}

		for(i = 0 ; i < 800 / 50 ; i++)
		{
			if(i%3)
			{
				a_brick = new CNormalBrick();
			}
			else
			{
				a_brick = new CHardenedBrick();
			}
			//a_brick = ( i%3 )? (new CHardenedBrick()) : (new CNormalBrick());
			a_brick->DefaultProperties();
			a_brick->PostBeginPlay(dataStrings);

			a_brick->position = Vector2( 25 + i * 50,125);
			actorList.push_back(a_brick);
			level->liveBrickList.push_back(a_brick);
		}
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 22.04.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//
	//=============================================
	bool CObjectManager::DeInit()
	{
		log <<"CObjectManager::DeInit() - deinitializing Object Manager\n";

		CGame::GetSingleton().audioSystem.StopMusic(musicHandle);	//stop playing music
		//delete everything
		for(std::vector<CActor*>::iterator itor = actorList.begin() ; itor != actorList.end() ;)
		{
			(*itor)->PreEndGame();
			(*itor)->Delete();
			(*itor)->Release();
			
			actorList.erase(itor);
			
		}
	
		for(std::vector<CBall*>::iterator b_itor = ballList.begin(); b_itor != ballList.end() ;)
		{
			(*b_itor)->Release();
			ballList.erase(b_itor);
		}

		if(level)
		{
			level->Unload();
			delete level;
		}

		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 08.07.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//
	//=============================================
	void CObjectManager::Update(float dT)
	{
		ProcessGeneric(dT);

		//stuff below should be processed only, if playing game
		if(gameplayMode == GPM_PLAYING)
		{
			ProcessPaddle(dT);
			ProcessCollisions(dT);
			ProcessRules(dT);
		}
	}

	//=============================================
	//Function: Draw
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 29.05.2004
	//
	//Returns: nothing
	//Parameters: none
	//Description:
	//	Draws all objects
	//=============================================
	void CObjectManager::Draw()
	{
		//draw background

		//draw all actors
		CActor * drawActor;	//temporary pointer for drawing optimizations
		for(ActorListIterator itor = actorList.begin() ; itor != actorList.end() ; ++itor)
		{
			drawActor = (*itor);

			if( drawActor->bVisible == true )	//if object is visible
			{
				glColor4f(1.0f,1.0f,1.0f,0.99f);	//apply valid color [!!OPTIMISE!!]
				drawActor->Draw();	//draw
			}
		}

		livesText.Draw();	//draw lives text
		scoreText.Draw();	//draw score text
		
		if( gameRules.bShowTimer == true )	//are we allowed to draw timer?
		{
			timerText.Draw();	//yes? then draw it
		}

		//victory screen
		if( gameplayMode == GPM_VICTORY )
		{
			//show victory screen
			victoryMessage.Draw();
			return;
		}

		//defeat screen
		if( gameplayMode == GPM_DEFEAT )
		{
			//show defeat screen
			defeatMessage.Draw();
			return;
		}

		//end of game screen
		if( gameplayMode == GPM_GAMEOVER )
		{
			//show defeat screen
			endGameMessage.Draw();
			return;
		}

		//waiting for space
		if( gameplayMode == GPM_WAITING_UNTIL_USER_READY )
		{
			waitUntilReadyMessage.Draw();	//show message
			return;
		}
		
		//game paused
		if( gameplayMode == GPM_PAUSE )
		{
			pauseMessage.Draw();	//show pause message
		}
	}


	//=============================================
	//Function: ProcessGeneric()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 08.07.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//	Handles generic input and game states
	//=============================================
	void CObjectManager::ProcessGeneric(float dT)
	{
		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_ESCAPE))	//pressed esc.
		{
			CGame::GetSingleton().gameMgr.SetState(GS_MAINMENU);	//exit to menu
			return;
		}

		switch(gameplayMode)	//thx, Stanislaw Wawszczak; i followed Your idea and changed ifs to switches :D
		{
			case GPM_VICTORY:	//victory screen
			case GPM_DEFEAT:	//defeat screen
			case GPM_GAMEOVER:	//game over screen
			{
				return;	//do nothing
			}
			case GPM_WAITING_UNTIL_USER_READY:	//'press space to continue' screen
			{
				if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_SPACE))	//check for space
				{
					gameplayMode = GPM_PLAYING;	//play the game
					CGame::GetSingleton().audioSystem.PlaySound(pauseSound);
				}
				return;
			}
			case GPM_PAUSE:	//pause screen
			{
				if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_Q))	//pressed q?
				{
					gameplayMode = GPM_PLAYING;	//unpause
					CGame::GetSingleton().audioSystem.PlaySound(pauseSound);
				}
				return;
			}
		}

		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_P))	//p pressed
		{
			gameplayMode = GPM_PAUSE;	//pause the game
			CGame::GetSingleton().audioSystem.PlaySound(pauseSound);
			return;	//end update
		}

		//process physics
		CActor * phys_actor;	//temporary actor variable for optimizing physics tests
		for(ActorListIterator itor = actorList.begin() ; itor != actorList.end() ; )
		{
			phys_actor = (*itor);
			phys_actor->position += (phys_actor->velocity * dT);	//velocity
			
			//
			if(phys_actor->physicsMode == CActor::PHYSICS_FLYING || phys_actor->physicsMode == CActor::PHYSICS_FALLING)
			{
				phys_actor->velocity += (phys_actor->forces * phys_actor->mass * dT);	//acceleration

				if(phys_actor->physicsMode == CActor::PHYSICS_FALLING)	//falling mode?
				{
					(*itor)->velocity += Vector2(0,60) * g * dT;	//apply gravity 
				}
			}

			if(phys_actor->velocity.Lenght() > 800)	//apply speed limit of 800 pixels per second
			{
				phys_actor->velocity.Normalize();
				phys_actor->velocity *= 800;
			}


			phys_actor->Tick(dT);	//tick actor

			if(phys_actor->bDeleteMe == true)	//should we delete this object?
			{
				phys_actor->PreEndGame();	//signal End of Game
				phys_actor->Delete();	//deinitialize
				phys_actor->Release();	//release object
				actorList.erase(itor);	//erase object from list
			}
			else	//not deleting object
			{
				++itor;
			}
		}
	}

	//=============================================
	//Function: ProcessPaddle()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 06.06.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//	Handles paddle movement
	//=============================================
	void CObjectManager::ProcessPaddle(float dT)
	{
		//just a temporary lame movement with const speed
		paddle->velocity.Zero();	//set speed to 0

		//pressed left key
		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_LEFT))
		{
			paddle->velocity = Vector2(-700,0);	//velocity to the left
		}

		//pressed right key
		else if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_RIGHT))
		{
			paddle->velocity = Vector2(700,0);	//velocity to the right
		}

		
		if( (paddle->position.x + paddle->BBSize.x > 800) && paddle->velocity.x > 0)
		{
			paddle->position.x = 800 - paddle->BBSize.x;
		}

		if( (paddle->position.x - paddle->BBSize.x < 0) && paddle->velocity.x < 0)
		{
			paddle->position.x = 0 + paddle->BBSize.x;
		}

	}

	//=============================================
	//Function: ProcessCollisions
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 08.07.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//	Handles collision between balls, paddle, bricks, and pickups / powerups
	//=============================================
	void CObjectManager::ProcessCollisions(float dT)
	{
		CBall * ball;	//our iterated ball
		CBrick * brick;	//our iterated brick
		
		for(std::vector<CBall*>::iterator ball_itor = ballList.begin() ; ball_itor != ballList.end(); ++ball_itor)
		{
			ball = (*ball_itor);	//make ball pointer point to current ball to avoid iterator decrementation overhead

			//check collision with paddle
			if(RectangleCollision(ball->position , ball->BBSize, paddle->position, paddle->BBSize))
			{
				//collision occured
				ball->velocity.y = -ball->velocity.y;	//reverse vertical speed (i know it`s lame :( )
				ball->velocity *= paddle->damp;	//apply damping
				CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);	//play bounce-off sound
			}

			//check collision with top, left, and right walls
			//top wall
			if((ball->position.y - ball->BBSize.y) < 0 && (ball->velocity.y < 0))
			{
				ball->velocity.y = -ball->velocity.y;	//reverse vertical speed
				CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);	//play bounce-off sound
			}

			//left and right walls in one condition (it`s not quantum physics lesson, the ball won`t bounce off two opposite walls at the same time)
			if( ((ball->position.x - ball->BBSize.x) < 0 && (ball->velocity.x < 0)) || ((ball->position.x + ball->BBSize.x) > 800 && (ball->velocity.x > 0)) )
			{
				ball->velocity.x = -ball->velocity.x;	//reverse horizontal speed
				CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);	//play bounce-off sound
			}

			//bottom wall
			if((ball->position.y + ball->BBSize.y) > 600 && (ball->velocity.y >0))
			{
				// //TEMPORARY CODE
				ball->velocity.y = -ball->velocity.y;	//reverse vertical speed
				//CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);	//play bounce-off sound
				--lives;

				//update lives text
				std::stringstream lifeBuff;	//just a buffer
				lifeBuff << lives;
				livesText.SetText((CGame::GetSingleton().stat_txt.GetString(STAT_TXT_LIVES_MASK) + lifeBuff.str()).c_str(), true, TEXTALIGN_LEFT, 20);

				if( (gameRules.defeatConditions == CGameRules::DC_NOLIVES) && (lives <= 0) )
				{
					CGame::GetSingleton().audioSystem.PlaySound(defeatSound);
					gameplayMode = GPM_DEFEAT;
				}
			}

			//check collision with bricks
			for(std::vector<CBrick*>::iterator brick_itor = level->liveBrickList.begin() ; brick_itor != level->liveBrickList.end();)
			{
				brick = (*brick_itor);

				if(RectangleCollision(ball->position, ball->BBSize, brick->position, brick->BBSize))
				{

					ball->velocity.y = -ball->velocity.y;	//reverse vertical speed
					CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);	//play bounce-off sound

					if(brick->TakeDamage(16))	//destroyed
					{
						CGame::GetSingleton().audioSystem.PlaySound(ballDestroySound);	//play bounce-off sound
						//place explosion

						//move from alive brick list to dead brick list
						level->liveBrickList.erase(brick_itor);
						level->deadBrickList.push_back(brick);

					}
					else
					{
						++brick_itor;
						continue;
					}
				}
				else
				{
					++brick_itor;
				}

			}
		}

	}

	//=============================================
	//Function: ProcessRules()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 08.07.2004
	//
	//Returns: nothing
	//Parameters: Delta Time
	//Description:
	//	Handles victory / defeat conditions, and other game - rule stuff
	//=============================================
	void CObjectManager::ProcessRules(float dT)
	{
			
		//Victory Conditions

		//--no bricks remaining
		if( level->liveBrickList.empty() && gameRules.victoryConditions == CGameRules::VC_NOBRICKS )
		{
			CGame::GetSingleton().audioSystem.PlaySound(victorySound);
			gameplayMode = GPM_VICTORY;
		}
		

		//Time
		//--Count up
		
	}

	//=============================================
	//Function: LoadLevel()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 30.05.2004
	//
	//Returns: nothing
	//Parameters: Level Name
	//Description:
	//	
	//=============================================
	bool CObjectManager::LoadLevel(const char * nL)
	{
		level->Load(nL);
		return true;
	}
} //end of namespace ARK
