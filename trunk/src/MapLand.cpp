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
            unsigned int temp = 0;
            is.read ( reinterpret_cast<char *> ( &temp ), 2 );
            mapLand ( i, j ) = temp;
        }
    }
    return is;
}

std::ostream& MapLand::toCompactForm ( std::ostream& os ) const
{
    // TODO write how actualy this compact form is saved
    unsigned short temp, temp2;

    unsigned int waterSize = 0;
    for ( int i = 0; i < width(); i++ )
        for ( int j = 0; j < height(); j++ )
            if ((*this)(i, j) == 0)
                waterSize++;

    bool skipWater = waterSize * 11 > 2048;

    os.write(reinterpret_cast<const char *>(&skipWater), 1);
    if (skipWater)
    {
        int landBitsSize = ( width() * height() )/ 8;
        std::bitset<8>* landBits = new std::bitset<8>[landBitsSize];
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
		delete[] landBits;
    }
    // save land
    char pos = 0;
    unsigned short mask;
    for ( int i = 0; i < width(); i++ )
    {
        for ( int j = 0; j < height(); j++ )
        {
            if (skipWater && (*this)(i, j) == 0)
                continue;

            unsigned int landPoint = (*this) ( i, j ) > 2047 ? 2047 : (*this) ( i, j );
            unsigned int tempPoint = landPoint;
            if (landPoint > 1023) // land higher than 1023 we mark as 0
                landPoint = 0;

            // save land high using 10 bits
            mask = 0x00FF >> pos; // cut lower bits
            temp = ((landPoint & mask) << pos ) | temp;
            os.write(reinterpret_cast<const char *>(&temp), 1);
            temp = 0;

            mask = 0xFFFF << 8 - pos; // cut higher bits
            temp = ((landPoint & mask) >> 8 - pos ) | temp;
            pos = pos + 2; // each iteration we left 10 - 8 = 2 bits to next iteration

            if (pos > 8)
            {
                mask = 0x00FF;
                temp2 = temp & mask;
                os.write(reinterpret_cast<const char *>(&temp2), 1);
                temp = temp >> 8;
                temp2 = 0;
                pos = pos - 8;
            }

            if (tempPoint > 1023) // save land higher than 1023 using 11 bits
            {
                landPoint = tempPoint;

                mask = 0x00FF >> pos; // cut lower bits
                temp = ((landPoint & mask) << pos ) | temp;
                os.write(reinterpret_cast<const char *>(&temp), 1);
                temp = 0;

                mask = 0xFFFF << 8 - pos; // cut higher bits
                temp = ((landPoint & mask) >> 8 - pos ) | temp;
                pos = pos + 3; // this time we left 11 - 8 - 3 bits to next iteration

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
    }
    if (pos > 0)
        os.write(reinterpret_cast<const char *>(&temp), 1);


    return os;
}

std::istream& MapLand::fromCompactForm ( std::istream& is )
{
    unsigned int temp = 0;
    bool skipWater = 0;
    int landBitsSize = ( width() * height() )/ 8;
    std::bitset<8>* landBits = new std::bitset<8>[landBitsSize];

    is.read(reinterpret_cast<char *>(&skipWater), 1);

    if (skipWater)
    {
        // load land bits
        for ( int i = 0; i < landBitsSize; ++i )
        {
            temp = 0;
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

            unsigned short readData = 0;
            char bits = 10;
            unsigned short mask;

            is.read(reinterpret_cast<char *>(&readData), 1);
            mask = 0x03FF >> pos;
            temp = ((readData & mask) << pos ) | temp;

            if (pos < 2) // we need to read one more byte
            {
                pos = 8 + pos;
                readData = 0;
                is.read(reinterpret_cast<char *>(&readData), 1);
                mask = 0x03FF >> pos;
                temp = ((readData & mask) << pos ) | temp;
            }

            if (temp == 0) // it's land higher than 1023, saved using 11 bits
            {
                bits = 10;
                temp = 0;
                mask = 0xFFFF << bits - pos;
                temp = ((readData & mask) >> bits - pos ) | temp;
                pos = pos - (bits - 8);

                readData = 0;
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
            }

            (*this)(i, j) = temp;

            if (temp <= 1023)
                bits = 10;
            else
                bits = 11;

            temp = 0;
            mask = 0xFFFF << bits - pos;
            temp = ((readData & mask) >> bits - pos ) | temp;
            pos = pos - (bits - 8);
        }
    }
	delete[] landBits;

    return is;
}

} // namespace poplib
