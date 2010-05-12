/*
Copyright (C) 2010 Populous Mana Source Development Team

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

#include <bitset>

#include "MapLand.h"

namespace poplib
{

std::ostream& operator<< ( std::ostream& os, const MapLand& mapLand )
{
    // Populous map is a square with 128x128,
    // 128 (width) * 128 (height) * 2 (WORD) = 32 768 bytes,
    // every WORD is one height of one point of map
    for ( int i = 0; i < mapLand.width(); i++ )
    {
        for ( int j = 0; j < mapLand.height(); j++ )
        {
            unsigned int temp = mapLand ( i, j );
            os.write ( reinterpret_cast<char *> ( &temp ), 2 );
        }
    }
    return os;
}

std::istream& operator>> ( std::istream& is, MapLand& mapLand )
{
    // Populous map is a square with 128x128,
    // 128 (width) * 128 (height) * 2 (WORD) = 32 768 bytes,
    // every WORD is one height of one point of map
    for ( int i = 0; i < mapLand.width(); i++ )
    {
        for ( int j = 0; j < mapLand.height(); j++ )
        {
            unsigned int temp;
            is.read ( reinterpret_cast<char *> ( &temp ), 2 );
            mapLand ( i, j ) = temp;
        }
    }
    return is;
}

std::ostream& MapLand::toCompactForm ( std::ostream& os ) const
{
    // TODO write how actualy this compact form is saved
    short temp, temp2;

    unsigned int waterSize = 0;
    for ( int i = 0; i < width(); i++ )
        for ( int j = 0; j < height(); j++ )
            if ((*this)(i, j) == 0)
                waterSize++;

    bool skipWater = waterSize * 2 > ( width() * height() ) / 8;

    os.write(reinterpret_cast<const char *>(&skipWater), 1);
    if (skipWater)
    {
        int landBitsSize = ( width() * height() )/ 8 + 1;
        std::bitset<8> landBits[landBitsSize];
        for ( int i = 0; i < width(); i++ )
        {
            for ( int j = 0; j < height(); j++ )
            {
                bool isWater = (*this)(i, j) == 0;
                landBits[(i * width() + j) / 8].set((i * width() + j) % 8, isWater);
            }
        }
        // save land bits
        for ( int i = 0; i < landBitsSize; ++i )
        {
            temp = landBits[i].to_ulong();
            os.write(reinterpret_cast<const char *>(&temp), 1);
        }
    }
    // save land
    char pos = 0;
    temp = 0;
    temp2 = 0;
    for ( int i = 0; i < width(); i++ )
    {
        for ( int j = 0; j < height(); j++ )
        {
            if (skipWater && (*this)(i, j) == 0)
                continue;

            int landPoint = (*this) ( i, j ) > 2047 ? 2047 : (*this) ( i, j );

            short mask = 0x00FF >> pos; // cut lower bits
            temp = ((landPoint & mask) << pos ) | temp;
            os.write(reinterpret_cast<const char *>(&temp), 1);
            temp = 0;

            mask = 0xFFFF << 8 - pos; // cut higher bits
            temp = ((landPoint & mask) >> 8 - pos ) | temp;
            pos = pos + 3;
            if (pos > 8)
            {
                mask = 0x00FF;
                temp2 = temp & mask;
                os.write(reinterpret_cast<const char *>(&temp2), 1);
                temp = temp >> 8;
                temp2 = 0;
                pos = pos - 8;
            }
        }
    }

    return os;
}

std::istream& MapLand::fromCompactForm ( std::istream& is )
{
    unsigned int temp;
    bool skipWater;
    int landBitsSize = ( width() * height() )/ 8 + 1;
    std::bitset<8> landBits[landBitsSize];

    is.read(reinterpret_cast<char *>(&skipWater), 1);

    if (skipWater)
    {
        // load land bits
        for ( int i = 0; i < landBitsSize; ++i )
        {
            is.read(reinterpret_cast<char *>(&temp), 1);
            landBits[i] = std::bitset<8>(temp);
        }
    }
    // load land
    char pos = 0;
    temp = 0;
    for ( int i = 0; i < width(); i++ )
    {
        for ( int j = 0; j < height(); j++ )
        {
            if (skipWater)
            {
                bool isWater = landBits[(i * width() + j) / 8].test((i * width() + j) % 8 );
                if (isWater)
                {
                    (*this)(i, j) = 0;
                    continue;
                }

            }

            short readData = 0;
            short mask;

            is.read(reinterpret_cast<char *>(&readData), 1);
            mask = 0x07FF >> pos;
            temp = ((readData & mask) << pos ) | temp;
            if (pos < 3) // we need to read one more byte
            {
                pos = 8 + pos;
                readData = 0;
                is.read(reinterpret_cast<char *>(&readData), 1);
                mask = 0x07FF >> pos;
                temp = ((readData & mask) << pos ) | temp;
            }
            (*this)(i, j) = temp;

            temp = 0;
            mask = 0xFFFF << 11 - pos;
            temp = ((readData & mask) >> 11 - pos ) | temp;
            pos = pos - 3;
        }
    }

    return is;
}

} // namespace poplib
