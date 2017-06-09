/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 16.04.2004
Last Revised:	27.04.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "Sprite.h"

namespace ARK
{
	//=============================================
	//Function: Constructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 16.04.2004
	//
	//Returns: none [does constructors return anything ?? :P]
	//Parameters: none
	//Description:
	//
	//=============================================
	CSprite::CSprite()
	{
	}

	//=============================================
	//Function: Destructor
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 16.04.2004
	//
	//Returns: same as above
	//Parameters: none
	//Description:
	//
	//=============================================
	CSprite::~CSprite()
	{

	}

	//=============================================
	//Function: Load()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.06.2004
	//
	//Returns: true on success, false on failure
	//Parameters: file name
	//Description:
	//	Loads and initializes image
	//	THIS FUNCTION VERSION DOES NOT SUPPORT GRP FORMAT AS I`VE GOT MUCH PROBLEMS WITH IT :(
	//=============================================
	bool CSprite::Load(const char * fileName)
	{
		FILE * fIn;	//file pointer

		fIn = ::fopen(fileName, "rb");	//open file in read-binary mode

		log <<"CSprite::Load() - Loading image " << fileName <<"\n";
		
		if(fIn == NULL)	//failed to open file
		{
			log.Error("CSprite::Load() - failed to open file %s in read-binary mode", fileName);
			return false;
		}

		/*GRPData grpHeader;	//image file header

		::fread(&grpHeader, sizeof(grpHeader), 1, fIn);	//load GPR header

		//is this image a GRP?
		if( (grpHeader.magic[0] != 'A') && (grpHeader.magic[1] != 'G') && (grpHeader.magic[2] != 'R') &&(grpHeader.magic[3] != 'P'))
		{
			//no? :D
			log.Error("CSprite::Load() - file is not a valid GPR image");
			::fclose(fIn);
			return false;
		}

		horizontalFrames = grpHeader.numHorizontalFrames;	//horizontal ( < -- > ) frames
		verticalFrames = grpHeader.numVerticalFrames;	//vertical (up to down) frames

		if(CGame::GetSingleton().bDebugMode == true)	//log some debug data
		{
			log <<"CSprite::Load() - dumping image data\n";

			log << "Is a GRP\n";
			log << ((grpHeader.vcode == 0x0FF1C1A1)? "Official Image\n" : "Not Official Image\n" );
			log << "GRP Version " << (static_cast<float>(grpHeader.versionID) / 100) << "\n";
			log << "Original image name: " << grpHeader.origrinalFileName <<"\n";
			log << "Number of frames: horizontal: " << grpHeader.numHorizontalFrames <<"; vertical: " <<grpHeader.numVerticalFrames << "; total: " << (grpHeader.numHorizontalFrames + grpHeader.numVerticalFrames) <<"\n";
		}
		*/
		if(LoadBMP(fIn, NULL) == false)	//load as BMP image
		{
			log.Error("CSprite::Load() - error loading image as a BMP");
			::fclose(fIn);
			return false;
		}

		name = fileName;	//set image name

		log <<"CSprite::Load - Finished loading image\n";

		return true;
	}

	//=============================================
	//Function: LoadBMP()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 19.04.2004
	//
	//Returns: true on success, false on failure
	//Parameters: pointer to a FILE structure handling open file, GRP header
	//Description:
	//	Loads and initializes image as 24bit BMP
	//	THIS FUNCTION VERSION DOES NOT SUPPORT GRP FORMAT AS I`VE GOT MUCH PROBLEMS WITH IT :(
	//=============================================
	bool CSprite::LoadBMP(FILE * fIn, GRPData * grpHeader)
	{
	
		BITMAPFILEHEADER imgHeader;	//file header for .bmp file
		BITMAPINFOHEADER imgInfo;	//info header for .bmp

		//::fseek(fIn, grpHeader->offsetImageData ,SEEK_SET);	//goto beginnig of image data

		::fread(&imgHeader,sizeof(BITMAPFILEHEADER), 1, fIn);	//read bitmap file header

		if(imgHeader.bfType != BMP_ID) //is a valid BMP file
		{
			log.Error("CSprite::LoadBMP() - file is not a valid BMP image");
			::fclose(fIn);
			return false;
		}

		::fread(&imgInfo,sizeof(BITMAPINFOHEADER),1,fIn);	//read image info header

		//set reading pointer onto beginning of the image data
		//::fseek(fIn, grpHeader->offsetImageData ,SEEK_SET);	//goto beginnig of BMP header data
		::fseek(fIn,(imgHeader.bfOffBits /*+ sizeof(grpHeader)*/),SEEK_SET);	//jump to the beginning of BMP image data
		
		//set image properties
		width = imgInfo.biWidth;	//width
		height = imgInfo.biHeight;	//height
		bpp = imgInfo.biBitCount;	//bits per pixel

		log << "CSprite::LoadBMP() - Image widht: " << width <<" height: " << height <<" bpp: " << bpp <<"\n";

		imgBuffer = new byte[(width * height * (bpp/8))];	//create buffer for image data

		if(imgBuffer == NULL)	//failed to allocate memory
		{
			log.Error("CSprite::LoadBMP() - error allocating %d bytes of memory required for reading image", (bpp/8));
			::fclose(fIn);
			return false;
		}

		::fread(imgBuffer, 1, imgInfo.biSizeImage, fIn);	//read image data

		if(imgBuffer == NULL)	//failed to read image data
		{
			log.Error("CSprite::LoadBMP() - error reading image data\n");
		//	delete[] imgBuffer;	//free used memory
			::fclose(fIn);
		}

		//make texture
		if(CGame::GetSingleton().bDebugMode == true)
		{
			log <<"CSprite::LoadBMP() - Generating GL Texture handle\n";
		}

		glGenTextures(1, &glTextureID); //generate textures
		glBindTexture(GL_TEXTURE_2D, glTextureID);// bind

		if(CGame::GetSingleton().bDebugMode == true)
		{
			log <<"CSprite::LoadBMP() - Generated GL Texture handle = " << glTextureID <<"\n";
		}

		//texture wrapping
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//texture filters
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		if(CGame::GetSingleton().bDebugMode == true)
		{
			log <<"CSprite::LoadBMP() - Generating 2D Texture Image (glTexImage2d)\n";
		}

		//generate texture
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE ,imgBuffer);

		int mode = GL_RGB8;
		int mode2 = GL_BGR_EXT;
		if ((bpp/8)==4) mode = GL_RGBA8;
		if ((bpp/8)==4) mode2 = GL_BGRA_EXT;

		if(CGame::GetSingleton().bDebugMode == true)
		{
			log <<"CSprite::LoadBMP() - Building MipMaps\n";
		}

		gluBuild2DMipmaps(GL_TEXTURE_2D, mode, width, height, mode2, GL_UNSIGNED_BYTE, imgBuffer);
			
		::fclose(fIn);

		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 16.04.2004
	//
	//Returns: true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes sprite
	//============================================
	bool CSprite::DeInit()
	{
		if(imgBuffer != NULL)
		{
			delete[] imgBuffer;	//free memory
		}
		return true;
	}

	//=============================================
	//Function: Draw()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 27.05.2004
	//
	//Returns: nothing
	//Parameters: frame number, position of sprite`s middle, dimmensions of sprite
	//Description:
	//	Draws a frame [ frame number < 0 == entire image ]
	//=============================================
	void CSprite::Draw(int frame, Vector2 coords, Vector2 dimensions)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, glTextureID);	//bind texture
		
		glEnable(GL_BLEND);
		if(frame < 0)
		{
			//draw a quad
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f,0.0f);	glVertex2f((coords.x - (dimensions.x/2)), (coords.y + (dimensions.y/2)));
				glTexCoord2f(1.0f,0.0f);	glVertex2f((coords.x + (dimensions.x/2)), (coords.y + (dimensions.y/2)));
				glTexCoord2f(1.0f,1.0f);	glVertex2f((coords.x + (dimensions.x/2)), (coords.y - (dimensions.y/2)));
				glTexCoord2f(0.0f,1.0f);	glVertex2f((coords.x - (dimensions.x/2)), (coords.y - (dimensions.y/2)));
			}
			/*glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f,0.0f);	glVertex2f(100.0f,200.0f);
				glTexCoord2f(1.0f,0.0f);	glVertex2f(200.0f,200.0f);
				glTexCoord2f(1.0f,1.0f);	glVertex2f(200.0f,100.0f);
				glTexCoord2f(0.0f,1.0f);	glVertex2f(100.0f,100.0f);
			}
			*/
			glEnd();
		}
		else
		{
			//SOMEBODY HELP ME ?? !! ?? !! ?? !! ?? !! 
			//float cy = (int)(frame / horizontalFrames);
			//float cx = frame - cy * horizontalFrames ;

			float cx = static_cast<float>(frame%verticalFrames)/horizontalFrames;
			float cy = static_cast<float>(frame/horizontalFrames)/verticalFrames;

			//float cx = frame/horizontalFrames;
			//float cy = frame%verticalFrames;

			//cy /= verticalFrames;
			//cx /=horizontalFrames;

			//cy = 1-cy;
			//cx = 1-cx;

			//log <<cy <<" " << cx <<"\n";
			glBegin(GL_QUADS);
			{
		//		glTexCoord2f(cx,cy - oneOverVFrames);									glVertex2f((coords.x + (dimensions.x/2)), (coords.y - (dimensions.y/2)));
		//		glTexCoord2f(cx - oneOverHFrames, cy - oneOverVFrames);					glVertex2f((coords.x - (dimensions.x/2)), (coords.y - (dimensions.y/2)));
		//		glTexCoord2f(cx - oneOverHFrames, cy);	glVertex2f((coords.x - (dimensions.x/2)), (coords.y + (dimensions.y/2)));
		//		glTexCoord2f(cx, cy);					glVertex2f((coords.x + (dimensions.x/2)), (coords.y + (dimensions.y/2)));

				glTexCoord2f(cx, 1 - cy);						glVertex2f(coords.x - (dimensions.x/2), coords.y - (dimensions.y/2));
				glTexCoord2f(cx + oneOverHFrames, 1 - cy);		glVertex2f(coords.x + (dimensions.x/2), coords.y - (dimensions.y/2));
				glTexCoord2f(cx + oneOverHFrames, 1 - cy - oneOverVFrames);						glVertex2f(coords.x + (dimensions.x/2), coords.y + (dimensions.y/2));
				glTexCoord2f(cx, 1 - cy - oneOverVFrames);								glVertex2f(coords.x - (dimensions.x/2), coords.y + (dimensions.y/2));

				//glTexCoord2f(1.0f,1.0f);
				//glVertex2f(coords.x + (dimensions.x/2), coords.y - (dimensions.y/2));
				//glTexCoord2f(1.0f,1.0f);
				//glVertex2f((coords.x - (dimensions.x/2)), (coords.y - (dimensions.y/2)));
				//glTexCoord2f(1.0f,1.0f);
				//glVertex2f((coords.x - (dimensions.x/2)), (coords.y + (dimensions.y/2)));
				//glTexCoord2f(1.0f,1.0f);
				//glVertex2f((coords.x + (dimensions.x/2)), (coords.y + (dimensions.y/2)));
			}
			glEnd();
		}
	}

} //end of namespace ARK