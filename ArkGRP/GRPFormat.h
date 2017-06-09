#ifndef __ARK_GRP_H__
#define __ARK_GRP_H__

namespace ARK
{
	class GRPData
	{
	public:
		unsigned char magic[4];	//identification number, should be 'A' 'G' 'R' 'P'
		unsigned int versionID;	//version info
		unsigned int vcode;	//verification code used to differ original and user-made graphics
		char origrinalFileName[64];	//name of the original file
		unsigned int numHorizontalFrames;	//number of horizontal frames
		unsigned int numVerticalFrames;	//number of vertical frames
		int offsetImageData;	//offset to image data (bytes from beginning of the file)
		int offsetEOImageData;	//offset to the end of image data (bytes from beginning of the end)
	};
} //end of namespace ARK

#endif //__ARK_GRP_H__