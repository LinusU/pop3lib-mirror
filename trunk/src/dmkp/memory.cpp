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

#include "memory.h"

namespace poplib {

#if defined(PLATFORM_WIN32)
HWND FindPopulousHWND ( int* isD3D )
{
    HWND hPop = FindWindow ( 0, "Populous, The Beginning" ); //D3D version has a comma

    if ( hPop )
    {
        *isD3D = IS_D3D;
        return hPop;
    }
    else
    {
        hPop = FindWindow ( 0, "Populous: The Beginning" ); //SOF version has a colon

        if ( hPop )
        {
            *isD3D = IS_SOF;
            return hPop;
        }
        else
        {
            *isD3D = IS_ERR;
            return 0;
        }
    }
}

DWORD GetProcessID ( HWND hWnd )
{
	DWORD dwProcId;

    if ( hWnd )
    {
        GetWindowThreadProcessId ( hWnd, &dwProcId );
    }
    else
        return _PROCESSERROR;

    return dwProcId;

}

HANDLE AttachToProcess ( DWORD dwProcessID )
{
    HANDLE hPop = OpenProcess ( PROCESS_ALL_ACCESS, false, dwProcessID );

    if ( hPop )
        return hPop;
    else
        return 0;
}
#endif

} // namespace poplib