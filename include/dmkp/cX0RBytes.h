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

#ifndef _H_DMKP32_POPULOUS_CONSTANTS_FUNCTIONS
#define _H_DMKP32_POPULOUS_CONSTANTS_FUNCTIONS

namespace poplib
{

class cXORBytes
{

public:
    cXORBytes()
    {
        Key[0] = 223;
        Key[1] = 191;
        Key[2] = 127;
        Key[3] = 254;
        Key[4] = 253;
        Key[5] = 251;
        Key[6] = 247;
        Key[7] = 239;
    }

    void XORBytes ( unsigned char* bytes, int length )
    {
        int NumElements = length;

        if ( NumElements == 0 )
            return;

        for ( int i = 0; i < NumElements; i++ )
        {
            bytes[i] = bytes[i] ^ Key[i % 8];
        }
    }

private:
    unsigned char Key[8];
};

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_CONSTANTS_FUNCTIONS */
