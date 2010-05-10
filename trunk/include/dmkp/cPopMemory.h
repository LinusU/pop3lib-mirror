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


#ifndef _H_DMKP32_POPULOUS_SOLO__
#define _H_DMKP32_POPULOUS_SOLO__

#include "memory.h"

#define WRITE_ERROR_HANDLE_INVALID -1
#define MEMOFF_TEXTUREFIX 0x05177BC
#define MEMVAL_TEXTUREFIX 63

namespace poplib
{
	
class cPopMemory;
struct Size;

void SetResolution ( cPopMemory* PopMemory, Size resolution );
void FixTexturesD3D ( cPopMemory* PopMemory );

enum Populous_MemoryOffsets
{
    OFFSETTextureFix = MEMOFF_TEXTUREFIX
};

enum Populous_MemoryValues
{
    VALUETextureFix = MEMVAL_TEXTUREFIX
};

enum Populous_States
{
    D3D = IS_D3D,
    SOFTWARE = IS_SOF,
    ERR = IS_ERR
};

struct Size
{
    int Width, Height;
};

#if defined(PLATFORM_WIN32)
class cPopMemory
{
public:

    //handle to populous
    HANDLE hPop;

    //state of populous : d3d mode, software mode or error
    int isD3D;

    cPopMemory ();
    ~cPopMemory ();

    int WriteInt8 ( unsigned long lAddress, char nValue );
};
#endif

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_SOLO__ */
