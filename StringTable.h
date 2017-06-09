#ifndef __ARK_STRING_TABLE_H__
#define __ARK_STRING_TABLE_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 02.02.2004
Last Revised:	27.05.2004

Implementation File: StringTables.cpp

Notes:
	
*/

/*
	Header for String Table Object
*/

namespace ARK
{
	class CStringTable
	{
	protected:
		std::string * table;	//table of strings
		unsigned int numEntries;	//number of string entries

	public:
		CStringTable();	//constructor
		~CStringTable();//destructor

		bool Init(const char * fN);	//initialize from file
		bool Init(const char * stringTableData, unsigned int bufferSize);	//initialize from file

		bool LoadTable(FILE * fIn);	//load table from file, giving file handle ptr.

		bool DeInit();	//deinitialize

		bool Load(const char * fN);	//load from file

		std::string GetString(unsigned int pos);	//get string
		unsigned int GetEntriesCount()	//get number of string entries
		{
			return numEntries;
		}

		bool EntryExists(unsigned int entry)
		{
			return ( (entry < numEntries) ? true : false );
		}


	};

} //end of namespace ARK


#endif //__ARK_STRING_TABLE_H__