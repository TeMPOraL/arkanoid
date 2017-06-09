#ifndef __ARK_SPRITE_MANAGER_H__
#define __ARK_SPRITE_MANAGER_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 17.04.2004
Last Revised:	27.05.2004

Implementation File: SpriteMgr.cpp

Notes:
	
*/

/*
	This class manages all sprites in the game.
	To load a sprite, call Load, giving it`s name. Function will return Sprite handle, or -1 if failed to load.
	To draw call Draw giving sprite handle, sprite frame, coords, and dimensions.
	All sprites will be deleted, when DeInit function is called, or manually - by using UnloadAll
	To get some information about sprites, call GetFrameCount and GetSpriteDimensions
*/

#include "Arkanoid.h"
#include "Sprite.h"
#include "Vector2.h"

#define ARK_MAX_SPRITES 256	//max sprites

namespace ARK
{

	class CSpriteMgr
	{
	protected:
		CSprite table[ARK_MAX_SPRITES];	//sprite table
		int nSprites;	//number of currently loaded sprites

	public:
		CSpriteMgr():nSprites(0){}	//constructor
		~CSpriteMgr(){}	//destructor

		bool Init();	//initialize Sprite Manager
		bool DeInit();	//deinitialize Sprite Manager
		int Load(const char * name);	//load a sprite
		void UnloadAll();	//unloads all sprites; use at Your own risk :D (means - when You`re shure that nothing `ll be refferencing to old sprites)

		void Draw(int sprite, int frame, Vector2 coords, Vector2 dimensions);	//draw sprite

		void SetFrameCount(int sprite, int hFrames, int vFrames)
		{
			if( (sprite < nSprites) && (sprite > -1) )
			{
				table[sprite].SetFrameCount(hFrames, vFrames);
				return;
			}
		}

		int GetFrameCount(int sprite)	//get sprite`s frame count
		{
			if( (sprite < nSprites) && (sprite > -1) )
			{
				return table[sprite].GetFrameCount();	//return frame count
			}
			else
			{
				return -1;
			}
		}
		bool GetSpriteDimensions(int sprite, Vector2 * dimensions)	//get sprite`s dimensions
		{
			if( (sprite < nSprites) && (sprite > -1) )
			{
				return table[sprite].GetDimensions(dimensions);	//returm sprite dimensions
			}
			else
			{
				return false;
			}
		}
	};


} //end of namespace ARK

#endif //__ARK_SPRITE_MANAGER_H__