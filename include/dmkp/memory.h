/*
Copyright (C) 2009 Populous Mana Source Development Team

This file is part of poplib.

poplib is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

poplib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with poplib. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _H_MEMORYFUNCS___
#define _H_MEMORYFUNCS___

#include "global.h"

#if defined(PLATFORM_WIN32)
#	include <windows.h>
#endif

#define IS_D3D 1
#define IS_SOF 0
#define IS_ERR -1

#define _PROCESSERROR 0

#define SZ_1280X1024 "1280x1024"
#define SZ_1024X768 "1024x768"
#define SZ_800X600 "800x600"
#define SZ_640X480 "640x480"

#define EXE_D3D "d3dpoptb.exe"
#define EXE_SOF "poptb.exe"

#pragma comment(lib, "user32") //needed for the process functions

//extern HANDLE hPopProcess;
//extern DWORD dwProcID;
//extern HWND hwndPop;

//HWND hWnd = FindWindow(0, "Populous, The Beginning");
//only works for d3d, software uses colon instead of comma


//GetWindowThreadProcessId(hWnd, &procID);

//hPopProcess = OpenProcess(PROCESS_ALL_ACCESS, false, procID);


//WriteProcessMemory(hProcess, (LPVOID)(offset), &value, sizeof(value), NULL);

//fix texture:
//0x05177BC = 63

/*
Ted says (21:07):
window handle = find window with name "Populous......
process id = get process id using window handle
process handle = get process handle using process id
Ted says (21:07):
thats basically what you are doing to get process handle


char value = 63;
WriteProcessMemory(hProcess, (LPVOID)(0x05177BC), &value, sizeof(value), NULL);





Uncheat:
If LCase$(ExeFile2) = "d3dpoptb.exe" Then
WriteProcessMemory pHandle, &H89C662, ByVal "", 2, 2
Else
WriteProcessMemory pHandle, &H884BFA, ByVal "", 2, 2
End If
Cheated = True
' Close the Process Handle
CloseHandle pHandle



*/

namespace poplib
{

#if defined(PLATFORM_WIN32)
HWND FindPopulousHWND ( int* isD3D );
DWORD GetProcessID ( HWND hWnd );
HANDLE AttachToProcess ( DWORD dwProcessID );
#endif

};

#endif /* _H_MEMORYFUNCS___ */
