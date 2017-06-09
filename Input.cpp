/*
Project:	Arkanoid

Programmer:	Jacek "TeMPOraL" Zlydach	[temporal@poczta.fm]

Created: 26.03.2004
Last Revised:	13.04.2004

This is an Implementation File

Notes:
	
*/

/*

*/

#include "Arkanoid.h"
#include "Input.h"

namespace ARK
{

	//=============================================
	//CKeyboard class Implementation
	//=============================================

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 26.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: Direct Input Interface, HWND
	//Description:
	//	Initializes Keyboard
	//=============================================
	bool CKeyboard::Init(IDirectInput8 *pDI, HWND windowHandle)
	{
		log <<"CKeyboard::Init() - Initializing Keyboard\n";

		if( FAILED(pDI->CreateDevice(GUID_SysKeyboardEm, &pDIDev, NULL)) )	//create device
		{
			log.Error("CKeyboard::Init() - Error creating device");
			//error handling
			return false;
		}
		
		if( FAILED(pDIDev->SetDataFormat(&c_dfDIKeyboard)) ) //set device format (c_dfDIKeyboard is a Direct Input global variable)
		{
			log.Error("CKeyboard::Init() - Error setting keyboard data format");
			//error handling
			return false;
		}

		//set cooperative level
		if( FAILED(pDIDev->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) )
		{
			log.Error("CKeyboard::Init() - Failed to set cooperative level");
			//error handling
			return false;
		}

		if( FAILED(pDIDev->Acquire()) )
		{
			log.Error("CKeyboard::Init() - Failed to acquire device");
			//error handling
			return false;
		}
		Clear();

		log <<"CKeyboard::Init() - Keyboard initialized successfuly\n";
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 26.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Denitializes Keyboard
	//=============================================
	bool CKeyboard::DeInit()
	{
		log <<"CKeyboard::DeInit() - Deinitializing Keyboard\n";
		if(pDIDev)
		{
			pDIDev->Unacquire();	//unacquire keyboard
			pDIDev->Release();	//release device
		}
		return true;
		log <<"CKeyboard::DeInit() - Keyboard deinitialized successfuly\n";
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Updates Keyboard
	//=============================================
	bool CKeyboard::Update()
	{
		HRESULT hr;
		hr = pDIDev->GetDeviceState(sizeof(keys), (LPVOID)keys/*static_cast<void*>(keys)*/);

		if( FAILED(hr) )
		{
			log <<"!!!Input error code - " << hr <<"\n";
			if(hr == DIERR_INPUTLOST)
			{
				log.Error("DIERR_INPUTLOST");
			}
			log.Error("CKeyboard::Update() - Error getting device state, attempting to acquire and try again.");
			if( FAILED(pDIDev->Acquire()) )
			{
				log.Error("CKeyboard::Update() - Error acquiring device; giving up");
				return false;
			}
			if( FAILED(pDIDev->GetDeviceState(sizeof(keys), static_cast<void*>(keys))) )
			{
				log.Error("CKeyboard::Update() - Error getting device state, giving up");
				return false;
			}
		}
		return true;
	}
	//=============================================
	//Function: Acquire()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 26.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Acquires keyboard
	//=============================================
	bool CKeyboard::Acquire()
	{
		Clear();
		return ( !FAILED( pDIDev->Acquire() ) );
	}

	//=============================================
	//Function: UnAcquire()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 26.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Unacquires keyboard
	//=============================================
	bool CKeyboard::UnAcquire()
	{
		Clear();
		return ( !FAILED( pDIDev->Unacquire() ) );
	}

	//=============================================
	//CMouse class Implementation
	//=============================================

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: Direct Input Device, HWND, bool - exclusive mode
	//Description:
	//	Initializes Mouse
	//=============================================
	bool CMouse::Init(IDirectInput8 * pDI, HWND windowHandle, bool bExclusive)
	{
		log <<"CMouse::Init() - Initializing Mouse\n";

		HRESULT hr = pDI->CreateDevice(GUID_SysMouse, &pDIDev, NULL) ;
		if( FAILED( hr ) )	//create device
		{
			log.Error("CMouse::Init() - Error creating device");
			log << hr <<"\n";

			log << DIERR_OUTOFMEMORY << " " << DIERR_OLDDIRECTINPUTVERSION << " " << DIERR_GENERIC << " " << DIERR_HANDLEEXISTS << " " << DIERR_MAPFILEFAIL << " " << DIERR_DEVICEFULL << "\n";

			//error handling
			return false;
		}

		if( FAILED(pDIDev->SetDataFormat(&c_dfDIMouse)) )	//set device format (c_dfDIMouse is a Direct Input global variable)
		{
			log.Error("CMouse::Init() - Error setting data format");
			//error handling
			return false;
		}

		//temporary variable
		DWORD flags = (bExclusive) ? (DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY) : (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		//setting cooperative level
		if( FAILED(pDIDev->SetCooperativeLevel(windowHandle, flags)) )
		{
			log.Error("CMouse::Init() - Failed to set cooperative level (%s mode)", bExclusive ? "exclusive" : "nonexclusive");
			//error handling
			return false;
		}

		//acquiring device
		if( FAILED(pDIDev->Acquire()) )
		{
			log.Error("CMouse::Init() - Failed to acquire device");
			//error handling
			return false;
		}

		//get device state
		if( FAILED(pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)) )
		{
			log.Error("CMouse::Init() - Failed to get device state");
			//error handling
			return false;
		}
		
		log <<"CMouse::Init() - Mouse initialized successfuly\n";
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 28.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: None
	//Description:
	//	Deinitializes Mouse
	//=============================================
	bool CMouse::DeInit()
	{
		if(pDIDev)
		{
			pDIDev->Unacquire();
			pDIDev->Release();
		}

		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 28.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: None
	//Description:
	//	Updates Mouse
	//=============================================
	bool CMouse::Update()
	{
		if( FAILED(pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)) )
		{
			log.Error("CMouse::Update() - Error getting device state, attempting to acquire and try again");
			//error handling
			if( !Acquire() )
			{
				log.Error("CMouse::Update() - Error acquiring device; giving up");
				//error handling
				return false;
			}
			if( FAILED(pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)) )
			{
				log.Error("CMouse::Update() - Error getting device state, giving up");
				//error handling
				return false;
			}
		}
		return true;
	}

	//=============================================
	//Function: Acquire()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 28.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: None
	//Description:
	//	Acquires Mouse
	//=============================================
	bool CMouse::Acquire()
	{
		return !( FAILED( pDIDev->Acquire() ) );
	}

	//=============================================
	//Function: UnAcquire()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 28.03.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: None
	//Description:
	//	Unacquires Mouse
	//=============================================
	bool CMouse::UnAcquire()
	{
		return !( FAILED( pDIDev->Unacquire() ) );
	}

	//=============================================
	//CInput class Implementation
	//=============================================

	//=============================================
	//Function: Init()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: HWND, HINSTANCE, bool - exclusive mode
	//Description:
	//	Initializes Input System
	//=============================================
	bool CInput::Init(HWND windowHandle, HINSTANCE appInstance, bool bExclusive)
	{
		if( FAILED(DirectInput8Create(appInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDirectInput, NULL)) )
		{
			log.Error("CInput::Init() - Error creating Direct Input 8 Interface");

			MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_CREATING_DI8_INTERFACE)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			//error handling
			return false;
		}
		
		keyboard = new CKeyboard;
		if(keyboard == NULL)
		{
			log.Error("CInput::Init() - Error creating keyboard object");

			MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_INITIALIZING_KEYBOARD)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			//error handling
			return false;
		}
		if( !(keyboard->Init(pDirectInput,windowHandle)) )
		{
			log.Error("CInput::Init() - Error initializing keyboard");

			MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_INITIALIZING_KEYBOARD)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			//error handling
			return false;
		}

		mouse = NULL;
		mouse = new CMouse;
		if(mouse = NULL)
		{
			log.Error("CInput::Init() - Error creating mouse object");
			
			MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_INITIALIZING_MOUSE)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);
			
			//error handling
			return false;
		}
	//	if( !(mouse->Init(pDirectInput, windowHandle, bExclusive)) )
	//	{
	//		log.Error("CInput::Init() - Error initializing mouse");

	//		MessageBox(NULL,(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_ERROR_INITIALIZING_MOUSE)).c_str(),(CGame::GetSingleton().systemStrings.GetString(STRING_SYS_GAMENAME)).c_str(),MB_OK|MB_ICONSTOP);

			//error handling
	//		return false;
	//	}
		return true;
	}

	//=============================================
	//Function: DeInit()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters: none
	//Description:
	//	Deinitializes Input System
	//=============================================
	bool CInput::DeInit()
	{
		UnAcquireAll();
		if(keyboard != NULL)
		{
			keyboard->DeInit();
			delete keyboard;
			keyboard = NULL;
		}
		
	//	if(mouse != NULL)
	//	{
	//		mouse->DeInit();
	//		delete mouse;
	//		mouse = NULL;
	//	}

		if( FAILED(pDirectInput->Release()) )
		{
			log.Error("CInput::DeInit() - Error releasing Direct Input 8 Interface");
			//error handling
			return false;
		}

		return true;
	}

	//=============================================
	//Function: Update()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters:
	//Description:
	//	Updates Input
	//=============================================
	bool CInput::Update()
	{
		if(keyboard != NULL)
		{
			keyboard->Update();
		}

	//	if(mouse != NULL)
	//	{
		//	mouse->Update();
	//	}

		return true;
	}

	//=============================================
	//Function: AcquireAll()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters:
	//Description:
	//	Acquires all Input Devices
	//=============================================
	bool CInput::AcquireAll()
	{
		if(keyboard != NULL)
		{
			keyboard->Acquire();
		}

	//	if(mouse != NULL)
	//	{
	//		mouse->Acquire();
	//	}

		return true;
	}

	//=============================================
	//Function: UnAcquireAll()
	//
	//Programmer: Jacek "TeMPOraL" Zlydach
	//Last Revised: 11.04.2004
	//
	//Returns: bool - true on success, false on failure
	//Parameters:
	//Description:
	//	Unacquires all used Input Devices
	//=============================================
	bool CInput::UnAcquireAll()
	{
		if(keyboard != NULL)
		{
			keyboard->UnAcquire();
		}

	//	if(mouse != NULL)
	//	{
	//		mouse->UnAcquire();
	//	}
		return true;
	}


} //end of namespace ARK
