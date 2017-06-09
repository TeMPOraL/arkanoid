#ifndef __ARK_INPUT_H__
#define __ARK_INPUT_H__

/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 26.03.2004
Last Revised:	11.04.2004

Implementation File: Input.cpp

Notes:
	
	  TODO: Vector2d class for mouse position
*/

/*
	Header for Input subsystem. Contains CInput, CMouse and CKeyboard classes.
*/


namespace ARK
{
	//=============================================
	//Class CKeyboard - represents Keyboard
	//=============================================
	class CKeyboard
	{
	private:
		IDirectInputDevice8 * pDIDev;	//Direct Input Device
		char keys[256];	//key states
	public:
		CKeyboard(){}	//constructor
		~CKeyboard(){}	//destructor

		bool Init(IDirectInput8 *pDI, HWND windowHandle);	//initailze device
		bool DeInit();	//deinitailze device

		bool Update();	//update device

		bool Acquire();	//acquire device
		bool UnAcquire();	//unacquire device

		//keyboard operations
		bool GetKeyState(int key)	//get state of single key
		{
			return (*(keys + key)) ? true : false; //keys[key] ? true : false
		}

		void SetKeyState(int key)	//set state of single key
		{
			*(keys + key) = false;
		}

		bool KeyUp(int key)	//is key up?
		{
			return ((*(keys + key)) & 0x80) ? false : true;	//(keys[key] & 0x80) ? false : true
		}

		bool KeyDown(int key)	//is key down?
		{
			return !KeyUp(key);
		}

		void Clear()
		{
			memset(keys, 0, 256 * sizeof(bool));	//set keyboard data to zero
		}
	};

	//=============================================
	//Class CMouse - represents Mouse
	//=============================================
	class CMouse
	{
	private:
		IDirectInputDevice8 * pDIDev;	//Direct Input Device
		DIMOUSESTATE mouseState;	//Mouse State
	public:

		bool Init(IDirectInput8 *pDI, HWND windowHandle, bool bExclusive);	//initailze device
		bool DeInit();	//deinitailze device

		bool Update();	//update device

		bool Acquire();	//acquire device
		bool UnAcquire();	//unacquire device

		//mouse operations
		bool ButtonDown(int button)	//is button pressed?
		{
			return (*(mouseState.rgbButtons + button) & 0x80 ) ? true : false ;
		}

		bool ButtonUp(int button)	//is button depressed?
		{
			return !ButtonDown(button);
		}

		int GetWheelMovement()
		{
			return mouseState.lZ;
		}

		CMouse(){}	//constructor
		~CMouse(){}	//destructor
	};

	//=============================================
	//Class CInput - Input subsystem
	//=============================================
	class CInput
	{
	private:
		IDirectInput8 * pDirectInput;	//Direct Input 8 Interface Pointer
		CKeyboard * keyboard;	//keyboard
		CMouse * mouse;	//mouse
	public:
		bool Init(HWND windowHandle, HINSTANCE appInstance, bool bExclusive);	//initialize
		bool DeInit();	//deinitialize

		bool Update();	//update input device state

		bool AcquireAll();	//acquire all devices
		bool UnAcquireAll();	//unacquire all devices
		
		//input device operations

		CKeyboard * GetKeyboard()	//keyboard accessor
		{
			return keyboard;
		}

		CMouse * GetMouse()	//mouse accessor
		{
			return mouse;
		}
	};

} //end of namespace ARK

#endif //__ARK_INPUT_H__
