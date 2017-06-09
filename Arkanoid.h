#ifndef __ARK_H__
#define __ARK_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 29.01.2004
Last Revised:	14.04.2004

Implementation File: None

Notes:
	
*/

/*
A header that contains all includes needed for program.
*/

//warning disables
#pragma warning (disable : 4035)	//disable warning about returning value in __asm block
#pragma warning (disable : 4786)	//disable warning about truncating names in debug mode

//defines
#define __ARK_FULL_DEBUG__	//full debugging mode
#define DECLARE_SUPER(superClass) typedef superClass Super	//super class - parent

//STL Includes
#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <list>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <cassert>
#include <sstream>
#include <cmath>
#include <ctime>

//OS Includes

#ifdef WIN32
#include <windows.h>
#include "resource.h"
#endif //WIN32

//Direct Input Includes
#include <dinput.h>

//GL Includes
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

//FMOD Includes
#include <fmod.h>
#include <fmod_errors.h>

//Arakanoid Includes

//   ..::Formats::..
#include "ArkGRP\\GRPFormat.h"
//   ..::Various::..
#include "Singleton.h"
#include "Log.h"
#include "Game.h"
#include "GameState.h"
#include "GameStateMgr.h"
#include "Window.h"
#include "Input.h"
#include "Audio.h"
#include "Math.h"
#include "Vector2.h"
#include "HiResTimer.h"
#include "PseudoRandomizer.h"
#include "ObjectManager.h"

#include "Sprite.h"
#include "SpriteMgr.h"

#include "StringTable.h"
#include "StringsSystem.h"
#include "StringsStat_txt.h"
#include "StringsData.h"

//   ..::Game Objects Related::..
#include "Actor.h"

#include "StaticText.h"
#include "Bricks.h"
#include "Paddle.h"
#include "Ball.h"

//   ..::Game States::..
#include "TestGameState.h"
#include "Intro.h"
#include "MainMenu.h"
#include "NormalGame.h"
#include "AllOtherGameStates.h"


#endif //__ARK_H__