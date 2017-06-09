#ifndef __ARK_WINDOW_H__
#define __ARK_WINDOW_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 11.02.2004
Last Revised:	11.02.2004

Implementation File: Window.cpp

Notes:
	
*/

/*
	Just a simle[?] Window class
*/

#include "Arkanoid.h"

namespace ARK
{
	class CWindow
	{
	protected:
		HWND hWnd;	//window`s handle
		HDC hDC;	//window`s Device Context
		HGLRC hRC;	//window`s Rendering Context
		WNDCLASS wndClass;	//window class

		DEVMODE dmScreenSettings;	//Device Mode

		int width;	//width
		int height;	//height
		int bpp;	//bits per pixel

		bool isFullScreen;	//full screen flag

		//bool InitWindowClass();	//fill up the window class
		//bool InitDeviceMode();	//initialize DevMode
		//bool InitPixelFormat();	//set up pixel format

	public:

		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);	//window procedure


		bool Init(int _width, int _height, int _bpp, bool fullscreen = false);
		bool DeInit();

		bool InitGL();
		void Resize(int newWidth, int newHeight);



		//accessors
		HWND GetHWND()	//get Window Handle
		{
			return hWnd;
		}

		HDC GetDC()
		{
			return hDC;
		}

		HGLRC GetGLRC()
		{
			return hRC;
		}
	};
} //end of namespace ARK

#endif //__ARK_WINDOW_H__