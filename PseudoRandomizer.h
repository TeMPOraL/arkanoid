#ifndef __ARK_PSEUDO_RANDOMIZER_H__
#define __ARK_PSEUDO_RANDOMIZER_H__


/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 14.04.2004
Last Revised:	14.04.2004

Implementation File:

Notes:
	
*/

/*

	Pseudo-random numer generator

*/
#include "Arkanoid.h"

namespace ARK
{
	class CPseudoRandomizer
	{
	protected:
		long seed;	//seed
		long gen1;	//value 1
		long gen2;	//value 2
	public:
		CPseudoRandomizer();
		~CPseudoRandomizer();
		void Init(long _gen2 = 3719);
		long Rand(long maxValue);	//return number from 0 to maxValue
		float FRand();	//return float [0...1]

	};

} //end of namespace ARK


#endif //__ARK_PSEUDO_RANDOMIZER_H__