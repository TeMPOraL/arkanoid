/*
Arkanoid`s GRP Converter utility. It`s a console program that converts
normal images to Arkanoid`s GRP animations. See Tech.txt from Arkanoid for
more deails.

  By Jacek "TeMPOraL" Zlydach [temporal@poczta.fm]
  
  Visit TeMPOraS Software for more games and programs.
  www.temporal-software.prv.pl
*/

#include <iostream>
#include <stdio.h>
#include "GRPFormat.h"

#define VERSION 3
#define MAX_ALLOWED_IMAGE_SIZE 1024 * 1024 * 8 //8 MB

void ProcessCommand(int argc, char *args[]);
void Compile(const char * fileName, const char * outputFileName, int hFrames, int vFrames);
void Decompile(const char * fileName, const char * outputFileName);
void Dump(const char * fileName);

int main(int argc, char * argv[], char * env[])
{

	std::cout <<"\n\nArkanoid`s GRP Conventer Utility v 0.03 Debug compiled at 12.04.2004\n";
	std::cout <<"By Jacek \"TeMPOraL\" Zlydach [temporal@poczta.fm]\n";
	std::cout <<"Visit TeMPOraL Software for more games and programs.\n";
	std::cout <<"www.temporal-software.prv.pl\n";
	
	if(argc <=1)
	{
		std::cout <<"\nUsage: ArkGRP <command> [params]\n";
		std::cout <<"Use help command for list of avaible commands and their details\n";
		return 0;
	}
	else
	{
		//std::cout <<"\nCommands handling not yet implemented!\n";
		ProcessCommand(argc, argv);
		return 0;
	}

	return 0;
}

void ProcessCommand(int argc, char *args[])
{
	if(argc > 1)
	{
		//HELP COMMAND
		if(::stricmp(args[1], "help") == 0)
		{
			//generic help
			if(argc <3)
			{
				std::cout <<"\nHELP:\nAvaible Commands:\n";
				std::cout <<"\nhelp [command] - if specified, displays detailed help about command. Else, displays text You are now reading\n";
				std::cout <<"\ncompile <input file> <output file> <number of horizontal frames> <number of vertical frames> - compiles image to GRP\n";
				std::cout <<"\ndecompile <input file> [output file] - decompiles image from GRP\n";
				std::cout <<"\ndump <input file>  - displays info about specified GRP\n";
			}
			else
			{
				//help info
				if(::stricmp(args[2], "help") == 0)
				{
					std::cout <<"\nHELP - Displaying 'help' command info:\n";
					std::cout <<"\nUsage: help [command]\n";
					std::cout <<"If command specified, displays detailed informations about it. Else, displays command list\n";
				}
				
				//compile info
				if(::stricmp(args[2], "compile") == 0)
				{
					std::cout <<"\nHELP - Displaying 'compile' command info\n";
					std::cout <<"\nUsage: compile <input file> <output file> <number of horizontal frames> <number of vertical frames>\n";
					std::cout <<"Compiles input image to output GRP.\n";
				}

				//decompile info
				if(::stricmp(args[2], "decompile") == 0)
				{
					std::cout <<"\nHELP - Displaying 'decompile' command info\n";
					std::cout <<"\nUsage: decompile <input file> [output file]\n";
					std::cout <<"Decompiles image from GRP to it`s original format. If the output file name is not specified, image will be saved with filename stored in GRP data. If it is also not possible, the image will be saved as OutputImage.unk\n";
				}

				//dump info
				if(::stricmp(args[2], "dump") == 0)
				{
					std::cout <<"\nHELP - Displaying 'dump' command info\n";
					std::cout <<"\nUsage: dump <input file>\n";
					std::cout <<"Analyzes target GRP and displays info about it\n";
				}
			}
		}

		//COMPILE COMMAND
		if(::stricmp(args[1], "compile") == 0)
		{
			if(argc <= 5)
			{
				std::cout <<"\nInsufficient arguments\n";
				return;
			}

			Compile(args[2], args[3], ::atoi(args[4]), ::atoi(args[5]));
			return;
		}

		//DECOMPILE COMMAND
		if(::stricmp(args[1], "decompile") == 0)
		{
			if(argc <= 2)
			{
				std::cout <<"\nInsufficient arguments\n";
				return;
			}

			if(argc == 3)
			{
				std::cout <<"\nOutput file name nor specified, defaulting to OutputImage.unk\n";
				Decompile(args[2], "OutputImage.unk");
				return;
			}

			Decompile(args[2], args[3]);
			return;
		}

		if(::stricmp(args[1], "dump") == 0)
		{
			if(argc <= 2)
			{
				std::cout <<"\nInsufficient arguments\n";
				return;
			}

			Dump(args[2]);
			return;
		}
	
	}
	return;

}

void Compile(const char * fileName, const char * outputFileName, int hFrames, int vFrames)
{
	FILE *fIn, *fOut;	//file handles
	
	fIn = ::fopen(fileName,"rb");	//input file
	fOut = ::fopen(outputFileName, "wb");	//output file

	//checking
	if(fIn == NULL)
	{
		std::cout <<"\nFATAL: Unable to open input file " << fileName <<"! Please make sure if the file exists!\n";
		return;
	}

	if(fOut == NULL)
	{
		std::cout <<"\nFATAL: Unable to open output file " << outputFileName <<"!\n";
		return;
	}

	ARK::GRPData grpHeader;	//data header
	grpHeader.magic[0] = 'A';
	grpHeader.magic[1] = 'G';
	grpHeader.magic[2] = 'R';
	grpHeader.magic[3] = 'P';

	grpHeader.versionID = VERSION;

	grpHeader.vcode = 0x0FF1C1A1;	// == "official" :D

	::strncpy(grpHeader.origrinalFileName,fileName,64);

	grpHeader.numHorizontalFrames = hFrames;
	grpHeader.numVerticalFrames = vFrames;
	grpHeader.offsetImageData = sizeof(ARK::GRPData);

	char * imgBuffer = new char[MAX_ALLOWED_IMAGE_SIZE];

	if(imgBuffer == NULL)
	{
		std::cout << "\nError compiling file " << fileName << " - unable to allocate " << (MAX_ALLOWED_IMAGE_SIZE / 1024) << " kB block in memory";
		return;
	}

	int imgSize = fread(imgBuffer, MAX_ALLOWED_IMAGE_SIZE, 1 ,fIn);

	std::cout << "\nSize of input image: " << (imgSize/1024) <<" kB";

	grpHeader.offsetEOImageData = (sizeof(ARK::GRPData) + imgSize);

	::fwrite(&grpHeader,1, sizeof(grpHeader),fOut);
	::fwrite(imgBuffer, 1, imgSize, fOut);

	::fclose(fIn);
	::fclose(fOut);
	delete[] imgBuffer;

	std::cout << "\nCompilation completed; generated GRP image " << outputFileName << " from image " << fileName <<"\n";
	
	return;
}

void Decompile(const char * fileName, const char *outputFileName)
{
	FILE *fIn, *fOut;	//file handles
	
	fIn = ::fopen(fileName,"rb");	//input file
	fOut = ::fopen(outputFileName, "wb");	//output file

	//checking
	if(fIn == NULL)
	{
		std::cout <<"\nFATAL: Unable to open input file " << fileName <<"! Please make sure if the file exists!\n";
		return;
	}

	if(fOut == NULL)
	{
		std::cout <<"\nFATAL: Unable to open output file " << outputFileName <<"!\n";
		return;
	}

	ARK::GRPData grpHeader;	//data header
	
	::fread(&grpHeader, sizeof(ARK::GRPData), 1, fIn);

	if((grpHeader.magic[0] != 'A') || (grpHeader.magic[1] != 'G') || (grpHeader.magic[2] != 'R') || (grpHeader.magic[3] != 'P'))
	{
		std::cout <<"\nInvalid magic number; file is probably not a GRP.";
		return;
	}

	if(grpHeader.versionID != VERSION)
	{
		std::cout <<"\nWarning: file version differs from the supported one. May not decompile correctly";
	}

	char * imgBuffer = new char[(grpHeader.offsetEOImageData  - grpHeader.offsetImageData)];

	::fread(imgBuffer, (grpHeader.offsetEOImageData  - grpHeader.offsetImageData), 1, fIn);

	::fwrite(imgBuffer, 1, (grpHeader.offsetEOImageData  - grpHeader.offsetImageData), fOut);

	std::cout <<"\nDecompilation completed; decompiled " << fileName << " to " << outputFileName <<"\n";
	delete[] imgBuffer;

	return;
}

void Dump(const char * fileName)
{
	FILE * fIn;
	ARK::GRPData grpHeader;

	fIn = ::fopen(fileName,"rb");	//input file
	
	//checking
	if(fIn == NULL)
	{
		std::cout <<"\nFATAL: Unable to open input file " << fileName <<"! Please make sure if the file exists!\n";
		return;
	}

	::fread(&grpHeader, sizeof(ARK::GRPData), 1 ,fIn);

	if((grpHeader.magic[0] != 'A') || (grpHeader.magic[1] != 'G') || (grpHeader.magic[2] != 'R') || (grpHeader.magic[3] != 'P'))
	{
		std::cout <<"\nInvalid magic number; file is probably not a GRP.";
		return;
	}

	std::cout <<"\nFile version: " << (static_cast<float>(grpHeader.versionID) / 100) ;
	if(grpHeader.vcode == 0x0FF1C1A1)
	{
		std::cout << "\nOfficial GRP Image";
	}
	else
	{
		std::cout << "\nNot official GRP Image";
	}
	
	std::cout <<"\nOriginal image name: " << grpHeader.origrinalFileName ;
	std::cout <<"\nNumber of horizontal frames: " << grpHeader.numHorizontalFrames ;
	std::cout <<"\nNumber of vertical frames: " << grpHeader.numVerticalFrames ;

	std::cout <<"\nImage data size: " << (grpHeader.offsetEOImageData - grpHeader.offsetImageData) ;
	return ;
}