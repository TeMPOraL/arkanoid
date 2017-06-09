#ifndef __ARK_STRINGS_DATA_H__
#define __ARK_STRINGS_DATA_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 27.05.2004
Last Revised:	27.05.2004

Implementation File: None

Notes:
	
*/

/*
	This file contains #defines for strings in Arkanoid`s Data Files String TBL
*/

#define STRING_DATA_IMAGES_BEGIN 0	//beginning of image data

#define STRING_DATA_OFF_TS_LOGO   STRING_DATA_IMAGES_BEGIN + 0
#define STRING_DATA_OFF_ARKANOID_LOGO   STRING_DATA_IMAGES_BEGIN + 1

#define STRING_DATA_OFF_PADDLE_SPRITE    STRING_DATA_IMAGES_BEGIN + 2	//offset to paddle sprite
#define STRING_DATA_OFF_BALL_SPRITE    STRING_DATA_IMAGES_BEGIN + 3	//offset to ball sprite
#define STRING_DATA_OFF_POWERBALL_SPRITE    STRING_DATA_IMAGES_BEGIN + 4	//offset to powerball sprite
#define STRING_DATA_OFF_NORMAL_BRICK_SPRITE    STRING_DATA_IMAGES_BEGIN + 5	//offset to normal brick sprite
#define STRING_DATA_OFF_HARDENED_BRICK_SPRITE STRING_DATA_IMAGES_BEGIN + 6	//offset to hardened brick sprite
#define STRING_DATA_OFF_NEOSTEEL_BRICK_SPRITE STRING_DATA_IMAGES_BEGIN + 7	//offset to neosteel brick sprite
#define STRING_DATA_OFF_RUBBER_BRICK_SPRITE STRING_DATA_IMAGES_BEGIN + 8	//offset to rubber brick sprite
#define STRING_DATA_OFF_FONT_SPRITE STRING_DATA_IMAGES_BEGIN + 9	//offset to font sprite

#define STRING_DATA_SOUNDS_BEGIN 10 //beginning of sound data

#define STRING_DATA_OFF_MUSIC    STRING_DATA_SOUNDS_BEGIN + 0	//offset to music file
#define STRING_DATA_OFF_MENUSELECT_SOUND   STRING_DATA_SOUNDS_BEGIN + 1	//offset to menu select sound
#define STRING_DATA_OFF_MENUACKNOWLEDGE_SOUND   STRING_DATA_SOUNDS_BEGIN + 2	//offset to menu acknowledge sound
#define STRING_DATA_OFF_GAMEOVER_SOUND   STRING_DATA_SOUNDS_BEGIN + 3	//offset to gameover sound
#define STRING_DATA_OFF_VICTORY_SOUND   STRING_DATA_SOUNDS_BEGIN + 4	//offset to victory sound
#define STRING_DATA_OFF_DEFEAT_SOUND   STRING_DATA_SOUNDS_BEGIN + 5	//offset to defeat sound
#define STRING_DATA_OFF_PAUSE_SOUND   STRING_DATA_SOUNDS_BEGIN + 6	//offset to pause/unpause sound

#define STRING_DATA_OFF_BOUNCE_WALL_SOUUND   STRING_DATA_SOUNDS_BEGIN + 7	//offset to 'bounce off the wall' sound
#define STRING_DATA_OFF_BOUNCE_BRICK_SOUND   STRING_DATA_SOUNDS_BEGIN + 8	//offset to 'bounce off the brick' sound
#define STRING_DATA_OFF_DESTROY_SOUND   STRING_DATA_SOUNDS_BEGIN + 9	//offset to destroy sound


#endif //__ARK_STRINGS_DATA_H__