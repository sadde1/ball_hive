# Microsoft Developer Studio Project File - Name="BallHive" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BallHive - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BallHive.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BallHive.mak" CFG="BallHive - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BallHive - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BallHive - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BallHive - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BallHive - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BallHive - Win32 Release"
# Name "BallHive - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutFgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Ball.cpp
# End Source File
# Begin Source File

SOURCE=.\BallHive.cpp
# End Source File
# Begin Source File

SOURCE=.\BallHive.rc
# End Source File
# Begin Source File

SOURCE=.\BallHiveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BallPool.cpp
# End Source File
# Begin Source File

SOURCE=.\Bfs.cpp
# End Source File
# Begin Source File

SOURCE=.\Board.cpp
# End Source File
# Begin Source File

SOURCE=.\Cell.cpp
# End Source File
# Begin Source File

SOURCE=.\ExitBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\GameOver.cpp
# End Source File
# Begin Source File

SOURCE=.\HiScore.cpp
# End Source File
# Begin Source File

SOURCE=.\HiveGame.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\OkBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\PauseBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\Score.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutBtn.h
# End Source File
# Begin Source File

SOURCE=.\AboutDialog.h
# End Source File
# Begin Source File

SOURCE=.\AboutFgr.h
# End Source File
# Begin Source File

SOURCE=.\Ball.h
# End Source File
# Begin Source File

SOURCE=.\BallHive.h
# End Source File
# Begin Source File

SOURCE=.\BallHiveDlg.h
# End Source File
# Begin Source File

SOURCE=.\BallPool.h
# End Source File
# Begin Source File

SOURCE=.\Bfs.h
# End Source File
# Begin Source File

SOURCE=.\Board.h
# End Source File
# Begin Source File

SOURCE=.\Cell.h
# End Source File
# Begin Source File

SOURCE=.\ExitBtn.h
# End Source File
# Begin Source File

SOURCE=.\GameOver.h
# End Source File
# Begin Source File

SOURCE=.\HiScore.h
# End Source File
# Begin Source File

SOURCE=.\HiveGame.h
# End Source File
# Begin Source File

SOURCE=.\LevelBtn.h
# End Source File
# Begin Source File

SOURCE=.\OkBtn.h
# End Source File
# Begin Source File

SOURCE=.\PauseBtn.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Score.h
# End Source File
# Begin Source File

SOURCE=.\ShowBtn.h
# End Source File
# Begin Source File

SOURCE=.\SoundPlayer.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\about.bmp
# End Source File
# Begin Source File

SOURCE=.\res\about_bgr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\about_fgr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BallHive.ico
# End Source File
# Begin Source File

SOURCE=.\res\BallHive.rc2
# End Source File
# Begin Source File

SOURCE=.\res\beginner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\beginnerselected.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\board.bmp
# End Source File
# Begin Source File

SOURCE=.\res\brownball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cell.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cell.gif
# End Source File
# Begin Source File

SOURCE=.\res\continue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\darkblueball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\digits.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\expert.bmp
# End Source File
# Begin Source File

SOURCE=.\res\expertselected.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flashball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GameOver.bmp
# End Source File
# Begin Source File

SOURCE=.\res\grayball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\greenball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lightblueball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\master.bmp
# End Source File
# Begin Source File

SOURCE=.\res\masterselected.bmp
# End Source File
# Begin Source File

SOURCE=.\res\new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\not_show.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\orangeball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pinkball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\redball.bmp
# End Source File
# Begin Source File

SOURCE=.\res\selectedcell.bmp
# End Source File
# Begin Source File

SOURCE=.\res\show.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\128.WAV
# End Source File
# Begin Source File

SOURCE=.\res\16.WAV
# End Source File
# Begin Source File

SOURCE=.\res\2.wav
# End Source File
# Begin Source File

SOURCE=.\res\256.WAV
# End Source File
# Begin Source File

SOURCE=.\res\32.wav
# End Source File
# Begin Source File

SOURCE=.\res\4.wav
# End Source File
# Begin Source File

SOURCE=.\res\64.WAV
# End Source File
# Begin Source File

SOURCE=.\res\8.wav
# End Source File
# Begin Source File

SOURCE=.\res\cell.WAV
# End Source File
# Begin Source File

SOURCE=.\res\Dead.WAV
# End Source File
# Begin Source File

SOURCE=.\res\Error.wav
# End Source File
# Begin Source File

SOURCE=.\res\Move.WAV
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
