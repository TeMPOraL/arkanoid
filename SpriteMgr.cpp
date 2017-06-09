/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 17.04.2004
Last Revised:	19.04.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "Sprite.h"
#include "SpriteMgr.h"

namespace ARK
{
	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 17.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Initializes Sprite Manager
	//=============================================
	bool CSpriteMgr::Init()
	{
		log <<"CSpriteMgr::Init() - initializing Sprite Manager\n";
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 17.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Sprite Manager and unloads all Sprites
	//=============================================
	bool CSpriteMgr::DeInit()
	{
		log <<"CSpriteMgr::DeInit() - deinitializing Sprite Manager\n";
		if(nSprites != 0 && nSprites > -1)	//some sprites remaining??
		{
			log << "CSpriteMgr::DeInit() - unloading remaining Sprites\n";
			for(int i = 0 ; i < nSprites ; i++)
			{
				table[i].DeInit();	//deinitialize image
			}
			nSprites = 0;	//all sprites unloaded
		}
		return true;
	}

	//=============================================
	//Function: UnloadAll()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 17.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Unloads all Sprites
	//=============================================
	void CSpriteMgr::UnloadAll()
	{
		if(nSprites != 0)	//some sprites remaining??
		{
			log << "CSpriteMgr::UnloadAll() - unloading all Sprites\n";
			for(int i = 0 ; i < nSprites ; i++)
			{
				table[i].DeInit();	//deinitialize image
			}
			nSprites = 0;	//all sprites unloaded
		}
	}

	//=============================================
	//Function: Load()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.06.2004
	//
	//Returns: Sprite handle, -1 on failure
	//Parameters: Sprite name
	//Description:
	//	Loads Sprite
	//=============================================
	int CSpriteMgr::Load(const char * fileName)
	{

		if( nSprites >= ARK_MAX_SPRITES )	//no place for new sprite
		{
			log.Error("CSpriteMgr::Load() - Sprite limit of %d exceeded while loading sprite %s", ARK_MAX_SPRITES, fileName);
			return -1;	//failure
		}

		//check if we already had loaded a sprite with given name
		for(int i = 0 ; i < nSprites; ++i)
		{
			if(table[i].GetName() == fileName)
			{
				if(CGame::GetSingleton().bDebugMode == true)
				{
					log <<"CSpriteMgr::Load() - requested sprite [" << fileName << "] already exists at position " << (i+1) <<")\n";
				}
				return i;	//return valid handle
			}
		}

		if( !table[nSprites].Load(fileName) )	//loading sprites
		{
			log.Error("CSpriteMgr::Load() - Failed to load sprite %s", fileName);
			//error handling
			return -1;
		}

		++nSprites;	//we`ve got a new sprite => increment sprite cout
		log <<"CSpriteMgr::Load() - loaded sprite [" << fileName <<"] at position " << nSprites <<")\n";
		return (nSprites - 1);
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: nothing
	//Parameters: sprite handle, frame number, coordinates, dimensions
	//Description:
	//	Draws sprite onto the screen
	//=============================================
	void CSpriteMgr::Draw(int sprite, int frame, Vector2 coords, Vector2 dimensions)
	{
		if(!((sprite >= nSprites) && (sprite < 0)))	//valid handle
		{
			table[sprite].Draw(frame, coords, dimensions);	//draw sprite
		}
	}

} //end of namespace ARK