# Microsoft Developer Studio Project File - Name="Arkanoid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Arkanoid - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Arkanoid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Arkanoid.mak" CFG="Arkanoid - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Arkanoid - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Arkanoid - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Arkanoid - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dinput8.lib dxguid.lib fmodvc.lib OpenGL32.lib GLU32.lib GLAux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Arkanoid - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Gr /W3 /GX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dinput8.lib dxguid.lib fmodvc.lib OpenGL32.lib GLU32.lib GLAux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Arkanoid - Win32 Release"
# Name "Arkanoid - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\resources.rc
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# End Group
# Begin Group "Game Stuff"

# PROP Default_Filter ""
# Begin Group "Game Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Audio.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\GameStateMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectManager.cpp

!IF  "$(CFG)" == "Arkanoid - Win32 Release"

!ELSEIF  "$(CFG)" == "Arkanoid - Win32 Debug"

# SUBTRACT CPP /Z<none>

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PseudoRandomizer.cpp
# End Source File
# Begin Source File

SOURCE=.\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\SpriteMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\StringTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Window.cpp
# End Source File
# End Group
# Begin Group "Game Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Audio.h
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\GameState.h
# End Source File
# Begin Source File

SOURCE=.\GameStateMgr.h
# End Source File
# Begin Source File

SOURCE=.\ArkGRP\GRPFormat.h
# End Source File
# Begin Source File

SOURCE=.\HiResTimer.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\Math.h
# End Source File
# Begin Source File

SOURCE=.\ObjectManager.h
# End Source File
# Begin Source File

SOURCE=.\PseudoRandomizer.h
# End Source File
# Begin Source File

SOURCE=.\Singleton.h
# End Source File
# Begin Source File

SOURCE=.\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\SpriteMgr.h
# End Source File
# Begin Source File

SOURCE=.\StringTable.h
# End Source File
# Begin Source File

SOURCE=.\Vector2.h
# End Source File
# Begin Source File

SOURCE=.\Window.h
# End Source File
# End Group
# Begin Group "String ID`s"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StringsData.h
# End Source File
# Begin Source File

SOURCE=.\StringsStat_txt.h
# End Source File
# Begin Source File

SOURCE=.\StringsSystem.h
# End Source File
# End Group
# Begin Group "Game States"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AllOtherGameStates.cpp
# End Source File
# Begin Source File

SOURCE=.\AllOtherGameStates.h
# End Source File
# Begin Source File

SOURCE=.\Intro.cpp
# End Source File
# Begin Source File

SOURCE=.\Intro.h
# End Source File
# Begin Source File

SOURCE=.\MainMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMenu.h
# End Source File
# Begin Source File

SOURCE=.\NormalGame.cpp
# End Source File
# Begin Source File

SOURCE=.\NormalGame.h
# End Source File
# Begin Source File

SOURCE=.\TestGameState.cpp
# End Source File
# Begin Source File

SOURCE=.\TestGameState.h
# End Source File
# End Group
# Begin Group "Game Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Actor.cpp
# End Source File
# Begin Source File

SOURCE=.\Actor.h
# End Source File
# Begin Source File

SOURCE=.\Ball.cpp
# End Source File
# Begin Source File

SOURCE=.\Ball.h
# End Source File
# Begin Source File

SOURCE=.\Bricks.cpp
# End Source File
# Begin Source File

SOURCE=.\Bricks.h
# End Source File
# Begin Source File

SOURCE=.\Paddle.cpp
# End Source File
# Begin Source File

SOURCE=.\Paddle.h
# End Source File
# Begin Source File

SOURCE=.\StaticText.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticText.h
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\Arkanoid.h
# End Source File
# Begin Source File

SOURCE=.\changes.txt
# End Source File
# Begin Source File

SOURCE=.\credits.txt
# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\specialny_readme.txt
# End Source File
# Begin Source File

SOURCE=.\tech.txt
# End Source File
# End Target
# End Project
