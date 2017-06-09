/*
Project Arkanoid.

  Just a simple old-school game.

  By Jacek "TeMPOraL" Zlydach.

*/

#include <windows.h>
#include "Arkanoid.h"

//================================================
//WinMain - application`s entry point
//=================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	new ARK::CGame();	//new game

	ARK::CGame::GetSingleton().Init(hInstance, lpCmdLine);

	ARK::CGame::GetSingleton().Execute();

	ARK::CGame::GetSingleton().DeInit();
	delete ARK::CGame::GetSingletonPtr();

	return 0;	//no error
}