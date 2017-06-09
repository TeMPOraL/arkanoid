
		if( CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_ESCAPE) )
		{
			CGame::GetSingleton().gameMgr.SetState(GS_MAINMENU);
		}

		//pause the game
		if(CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_P))	//p pressed
			{
				gameplayMode = GPM_PAUSE;	//pause the game
				CGame::GetSingleton().audioSystem.PlaySound(pauseSound);
				return;	//end update
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


		//update physics
		for(ActorListIterator itor = actorList.begin() ; itor != actorList.end() ;)
		{
			//physics
			(*itor)->position += ((*itor)->velocity * dT);	//move objects
			
			if((*itor)->velocity.Lenght() > 800)	//speed limit of 800 pixel/second
			{
				(*itor)->velocity.NormalizeFast();	//normalize speed vector
				(*itor)->velocity *= 800;	//set speed to 800 px/s
			}
			
			//flying or falling physics model
			if( (*itor)->physicsMode == CActor::PHYSICS_FLYING || (*itor)->physicsMode == CActor::PHYSICS_FALLING )
			{
				(*itor)->velocity += ((*itor)->forces * (*itor)->mass * dT);	//apply forces
				
				if( (*itor)->physicsMode == CActor::PHYSICS_FALLING )	//falling?
				{
					(*itor)->velocity += Vector2(0,60) * g * dT;	//apply gravity
				}

			}
			
			(*itor)->Tick(dT);	//tick

			//deleting
			if( (*itor)->bDeleteMe == true )	//delete object
			{
				(*itor)->PreEndGame();	//
				(*itor)->Delete();	//deinitialize
				(*itor)->Release();	//delete object
				actorList.erase(itor);	//erase from list
				
			}
			else	//not deleting
			{
				++itor;	//increment iterator
			}
		}
		//paddle movement

		if(paddle->velocity.x > 700)	//velocity limit
		{
			paddle->velocity.x = 700;
		}

		if(paddle->velocity.x < -700)	//velocity limit
		{
			paddle->velocity.x = -700;
		}

		//collision with left wall
		if(paddle && (paddle->position.x - paddle->BBSize.x/2 < -5) )
		{
			paddle->position.x = 0 + (paddle->BBSize.x/2);	//correct position a bit
			paddle->velocity.Zero();	//set velocity to 0
			paddle->forces.Zero();	//set forces to 0
		}
		//collision with right wall
		if(paddle && (paddle->position.x + paddle->BBSize.x/2 > 805) )
		{
			paddle->position.x = 800 - (paddle->BBSize.x/2);	//correct position
			paddle->velocity.Zero();	//zero velocity
			paddle->forces.Zero();	//zero forces
		}

		if(paddle->velocity.x > 0)	//friction :D
		{
			paddle->forces = Vector2(-2048,0);	//apply force of -2048... Newtons?? How do You call kilograms * Pixels / second squared??? :D
		}
		else if(paddle->velocity.x < 0)	//friction
		{
			paddle->forces = Vector2(2048,0);	//2048 kg*px/s^2
		}

		//input
		if( CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_LEFT) )	//left arrow
		{
			paddle->forces = Vector2(-3072, 0);	//push to the left
		}

		if( CGame::GetSingleton().inputSystem.GetKeyboard()->KeyDown(DIK_RIGHT) )
		{
			paddle->forces = Vector2(3072, 0);	//push to the right
		}

		//process collisions
		//  ->balls
		for(std::vector<CBall*>::iterator b_itor = ballList.begin(); b_itor != ballList.end() ; ++b_itor)
		{
			//left wall
			if( ( (*b_itor)->position.x - (*b_itor)->BBSize.x/2 < 0 ) && (*b_itor)->velocity.x < 0 )
			{
				//reverse horizontal speed
				(*b_itor)->velocity.x = -(*b_itor)->velocity.x ;
				CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);
			}

			//right
			if( ( (*b_itor)->position.x + (*b_itor)->BBSize.x/2 > 800 ) && (*b_itor)->velocity.x > 0 )
			{
				//reverse horizontal speed
				(*b_itor)->velocity.x = -(*b_itor)->velocity.x ;

				CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);
			}

			//top
			if( ( (*b_itor)->position.y - (*b_itor)->BBSize.y/2 < 0 ) && (*b_itor)->velocity.y < 0 )
			{
				//reverse horizontal speed
				(*b_itor)->velocity.y = -(*b_itor)->velocity.y ;

				CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);
			}

			//bottom == out of the map == lost ball
			if( ( (*b_itor)->position.y + (*b_itor)->BBSize.y/2 > 600 ) && (*b_itor)->velocity.y > 0 )
			{
				//reverse horizontal speed
				//(*b_itor)->velocity.y = -(*b_itor)->velocity.y ;

				//reset paddle position
				paddle->position = Vector2(400,550);	//paddle position
				paddle->velocity.Zero();	//zero velocity
				paddle->forces.Zero();	//zero forces

				//!! WHAT ABOUT MULTIPLE BALLS? !!
				(*b_itor)->position = Vector2(400,300);	//middle of the screen
				(*b_itor)->velocity = Vector2(CGame::GetSingleton().randomizer.FRand() /3, 1.0f);	//random velocity
				(*b_itor)->velocity.NormalizeFast();	//normalize velocity vector
				(*b_itor)->velocity *= 250;	//set velocity to 250 px/s
				
				--lives;	//lost a life

				//update lives display
				std::stringstream livesBuff;	//just a buffer
				livesBuff << lives;
				livesText.SetText((stat_txt.GetString(STAT_TXT_LIVES_MASK) + livesBuff.str()).c_str(), true, TEXTALIGN_LEFT, 20);

				gameplayMode = GPM_WAITING_UNTIL_USER_READY;	//just a pause

				//defeat conditions
				if( ( gameRules.defeatConditions == CGameRules::DC_NOLIVES || gameRules.defeatConditions == CGameRules::DC_LOSTBALL ) &&lives <= 0 )	//no lives
				{
					gameplayMode = GPM_DEFEAT;	//defeat
					CGame::GetSingleton().audioSystem.PlaySound(defeatSound);

				}
				
			}

			if(RectangleCollision( (*b_itor)->position, (*b_itor)->BBSize, paddle->position, paddle->BBSize) )
			{
				if((*b_itor)->velocity.y >0)	//if flying down the screen
				{
					//collides
					(*b_itor)->velocity.y = - (*b_itor)->velocity.y;	//reverse vertical velocity
					(*b_itor)->velocity *= paddle->damp;	//apply damping
					(*b_itor)->velocity += (paddle->velocity/15);	//apply paddle`s velocity to ball movement
					
					CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);
				}
			}

			for(std::vector<CBrick*>::iterator br_itor = brickList.begin() ; br_itor != brickList.end() ;++br_itor)
			{
			/*	if( (((*b_itor)->position.x + (*b_itor)->BBSize.x/2) > ((*br_itor)->position.x - (*br_itor)->BBSize.x/2) )&&
					( ( (*b_itor)->position.x - (*b_itor)->BBSize.x/2) < ((*br_itor)->position.x + (*br_itor)->BBSize.x/2) ) )
				{
					if( ( ( (*b_itor)->position.y + (*b_itor)->BBSize.y/2) > ((*br_itor)->position.y - (*br_itor)->BBSize.y/2) ) &&
						( ( (*b_itor)->position.y - (*b_itor)->BBSize.y/2) < ((*br_itor)->position.y + (*br_itor)->BBSize.y/2) ) )
					{*/
				if( (*br_itor)->bCollide )
				{
					if(RectangleCollision( (*b_itor)->position, (*b_itor)->BBSize, (*br_itor)->position, (*br_itor)->BBSize) )	
					{
					//collides
						if( (*b_itor)->velocity.y < 0 )	//flying upwards
						{
							(*b_itor)->velocity.y = - (*b_itor)->velocity.y;	//reverse vertical velocity
							(*b_itor)->velocity *= (*br_itor)->damp;	//apply damping
						}

						if((*br_itor)->TakeDamage(16))	//take damage
						{
							//is dead?
							score += (*br_itor)->EvaluatePointValue();	//add points
			//				brickList.erase(br_itor);	//erase from list
							(*br_itor)->bVisible = false;
							(*br_itor)->bCollide = false;
							CGame::GetSingleton().audioSystem.PlaySound(ballDestroySound);
						}

						else	//sitll alive?
						{
							CGame::GetSingleton().audioSystem.PlaySound(ballBounceSound);
							score += (*br_itor)->EvaluatePointValue();	//add points
						}
						
						//update score display
						std::stringstream scoreBuff;	//just a buffer
						scoreBuff << score;
						scoreText.SetText((stat_txt.GetString(STAT_TXT_SCORE_MASK) + scoreBuff.str()).c_str(), true, TEXTALIGN_RIGHT, 20);
						return;	//stop doing everything

					}
					
				}
					/*

					}


				}*/
				//++br_itor;	//increment brick iterator
			}
		}
