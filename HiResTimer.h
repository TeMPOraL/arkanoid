#ifndef __HI_RES_TIMER_H__
#define __HI_RES_TIMER_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 12.04.2004
Last Revised:	12.04.2004

Implementation File: None

Notes:
	
*/

/*


*/

#include "Log.h"

namespace ARK
{	
	class CHiResTimer
	{
	private:
		
		LARGE_INTEGER ticksPerSecond;	//counter`s ticks per second
		LARGE_INTEGER startTime;	//current time
		LARGE_INTEGER lastTime;	//time from previous check

	public:
		CHiResTimer(){}	//default constructor
		
		inline bool Init();	//initialize the timer
		inline float GetElapsedSeconds();	//get delta time from last call
		
	};

	//code

	bool CHiResTimer::Init()
	{
		if(!QueryPerformanceFrequency(&ticksPerSecond))
		{
			//Hi Res Timer not avaible on this platform
			log.Error("CHiResTimer::Init() - High Resolution Timer not avaible on this platform");
			return false;	//Hi Res Timer not avaible on this platform
		}
		else
		{
			QueryPerformanceCounter(&startTime);
			lastTime = startTime;
			return true;
		}
	}

	float CHiResTimer::GetElapsedSeconds()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		
		float seconds = ( ( (float)currentTime.QuadPart - (float)lastTime.QuadPart ) / (float)ticksPerSecond.QuadPart );

		lastTime = currentTime;
		return seconds;

	}

} //end of namespace ARK

#endif //__HI_RES_TIMER_H__