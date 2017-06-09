#ifndef __ARK_MATH_H__
#define __ARK_MATH_H__
/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 14.04.2004
Last Revised:	14.04.2004

Implementation File: None

Notes:

*/

/*
	Just few math & physics functions and constants
*/

#include "Arkanoid.h"

#pragma warning (disable : 4035)	//disable warning about returning value in __asm block

namespace ARK
{
	const float EPSILON = 0.00001f;				//minimum values for floats

	const float PI =3.141592653589793238462f;	//PI
	const float Sqrt2 = 1.414213562419339f;		//Square Root of 2

	//physics constants
	const float g = 9.81f;	//gravitational acceleration

	//=================================================
	inline float absf(float value)
	{
		*(long*)&value &= 0x7fffffff;	//clear bit 37
		return value;
	}


	// ..:: Powers and roots :..
	inline float sqrtf(float r)
	{	//fast square root
		__asm{
			fld r
			fsqrt
		}
	}


	inline float RSqrt(float number)
	{
		//this function is 'borrowed' from Mirko-Teran Ravnikar
		//thanks once again!
		float half_number = number *.5f;
		long i = * (long*)&number;
		i = (0x5f3759df - (i >>1));
		number = * (float * )&i;
		return number * ( 1.5f - half_number *number *number) ;
	}
} //end of namespace ARK
#endif //__ARK_MATH_H__