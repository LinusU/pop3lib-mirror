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

#include "cPopMemory.h"

namespace poplib
{

#if defined(PLATFORM_WIN32)
void FixTexturesD3D ( cPopMemory* PopMemory )
{
    if ( ! ( PopMemory == 0 ) )
    {
        if ( PopMemory->isD3D == D3D )
        {
            PopMemory->WriteInt8 ( ( unsigned long ) OFFSETTextureFix, ( unsigned char ) VALUETextureFix );
        }
    }
}

void SetResolution ( cPopMemory* PopMemory, Size resolution )
{
    int Width = resolution.Width, Height = resolution.Height;

    if ( ( ! ( PopMemory == 0 ) ) && PopMemory->isD3D != ERR )
    {
        PopMemory->WriteInt8 ( 0x410F9A, 106 );
        PopMemory->WriteInt8 ( 0x410F9B, 32 );

        //push 32
        PopMemory->WriteInt8 ( 0x410F9A, 106 );
        PopMemory->WriteInt8 ( 0x410F9B, 32 );

        //push width
        PopMemory->WriteInt8 ( 0x410F9C, 104 );
        PopMemory->WriteInt8 ( 0x410F9D, ( byte ) ( Height & 0xFF ) );
        PopMemory->WriteInt8 ( 0x410F9E, ( byte ) ( ( Height & 0xFF00 ) / 256 ) );
        PopMemory->WriteInt8 ( 0x410F9F, 0 );
        PopMemory->WriteInt8 ( 0x410FA0, 0 );

        //push height
        PopMemory->WriteInt8 ( 0x410FA1, 104 );
        PopMemory->WriteInt8 ( 0x410FA2, ( byte ) ( Width & 0xFF ) );
        PopMemory->WriteInt8 ( 0x410FA3, ( byte ) ( ( Width & 0xFF00 ) / 256 ) );
        PopMemory->WriteInt8 ( 0x410FA4, 0 );
        PopMemory->WriteInt8 ( 0x410FA5, 0 );

        //push 32
        PopMemory->WriteInt8 ( 0x457D60, 106 );
        PopMemory->WriteInt8 ( 0x457D61, 32 );

        //push width
        PopMemory->WriteInt8 ( 0x457D62, 104 );
        PopMemory->WriteInt8 ( 0x457D63, ( byte ) ( Height & 0xFF ) );
        PopMemory->WriteInt8 ( 0x457D64, ( byte ) ( ( Height & 0xFF00 ) / 256 ) );
        PopMemory->WriteInt8 ( 0x457D65, 0 );
        PopMemory->WriteInt8 ( 0x457D66, 0 );

        //push height
        PopMemory->WriteInt8 ( 0x457D67, 104 );
        PopMemory->WriteInt8 ( 0x457D68, ( byte ) ( Width & 0xFF ) );
        PopMemory->WriteInt8 ( 0x457D69, ( byte ) ( ( Width & 0xFF00 ) / 256 ) );
        PopMemory->WriteInt8 ( 0x457D6A, 0 );
        PopMemory->WriteInt8 ( 0x457D6B, 0 );

        //Overwrite extra spare space with NOPs
        for ( unsigned long i = 0x410FA6; i < 0x410FC6; i++ )
        {
            PopMemory->WriteInt8 ( i, 144 );
        }
        for ( unsigned long i = 0x457D6C; i < 0x457D87; i++ )
        {
            PopMemory->WriteInt8 ( i, 144 );
        }
    }
}

cPopMemory::cPopMemory ()
{
    hPop = 0;

    HWND hwndPop;
    DWORD dwProcessID;
    HANDLE hPopulous;

    hwndPop = FindPopulousHWND ( &isD3D );

    if ( isD3D == IS_ERR )
    {
        return;
    }
    else
    {
        dwProcessID = GetProcessID ( hwndPop );

        if ( dwProcessID == _PROCESSERROR )
        {
            isD3D = IS_ERR;
            return;
        }
        else
        {
            hPopulous = AttachToProcess ( dwProcessID );

            if ( hPopulous )
            {
                hPop = hPopulous;
            }
        }
    }
}

cPopMemory::~cPopMemory ( )
{
    if ( hPop )
        CloseHandle ( hPop );
}

int cPopMemory::WriteInt8 ( unsigned long lAddress, char nValue )
{
    if ( isD3D == IS_ERR )
        return WRITE_ERROR_HANDLE_INVALID;
    else
    {
        DWORD dwBW;
        return WriteProcessMemory ( hPop, ( LPVOID ) lAddress, &nValue, sizeof ( nValue ), &dwBW );

    }
}
#endif

}  // namespace poplib
