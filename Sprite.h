#ifndef __ARK_SPRITE_H__
#define __ARK_SPRITE_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 16.04.2004
Last Revised:	19.04.2004

Implementation File: Sprite.cpp

Notes:
	
*/

/*

  Sprite is a texture with animation assigned to it. It consists of one image (one texture).
  [19.04.2004] I`ve just realized, that it should be named Texture, or Textured Quad, not sprire,
				as it doesn`t use fixed image size ...

*/

#include "Arkanoid.h"
#include "Vector2.h"

#define BMP_ID 0x4D42

namespace ARK
{
	class CSprite
	{
	private:
	protected:

		byte * imgBuffer;	//here we`ll store image data

		int width;	//image width
		int height;	//image height
		int bpp;	//image bits per pixel

		enum EImage_Type
		{
			IMAGE_TYPE_NONE = 0,
			IMAGE_TYPE_BMP,
			IMAGE_TYPE_TGA
		} imageType;	//image type

		std::string name;	//inage file name

		int horizontalFrames;	//horizontal frames
		int verticalFrames;	//vertical frames

		//those two are for optimising display
		float oneOverHFrames;	//1 / horizontalFrames
		float oneOverVFrames;	//1 / verticalFrames

		unsigned int glTextureID;	//OpenGL Texture ID

		bool LoadBMP(FILE * fIn, GRPData * grpHeader);	//load 24bit BMP image

	public:

		CSprite();	//constructor
		~CSprite();	//destructor

		bool Load(const char * fileName);	//load image
		bool DeInit();	//deinitialize image

		void Draw(int frame, Vector2 coords, Vector2 dimensions);	//prepare a frame for displaying ( 0 < == entire image)

		void SetFrameCount(int hFrames, int vFrames)
		{
			horizontalFrames = hFrames;	//horizontal frame count
			verticalFrames = vFrames;	//vertical frame count
			//for optimising
			oneOverHFrames = (1 / static_cast<float>(horizontalFrames));
			oneOverVFrames = (1 / static_cast<float>(verticalFrames));
		}

		int GetFrameCount()	//get frame count
		{
			return horizontalFrames * verticalFrames;	//return frame count
		}

		bool GetDimensions(Vector2 * vec)	//get sprite dimensions
		{
			*vec = Vector2(width, height);	//image dimensions
			return true;
		}

		std::string GetName()	//get sprite name
		{
			return name;
		}

	};

} //end of namespace ARK


#endif //__ARK_SPRITE_H__