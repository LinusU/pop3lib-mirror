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
    unsigned int temp;
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
                landBits[(i * width() + j) / 8].set((i * width() + j) % 8 + 1, isWater);
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
    for ( int i = 0; i < width(); i++ )
    {
        for ( int j = 0; j < height(); j++ )
        {
            if (skipWater && (*this)(i, j) == 0)
                continue;
								// TODO saving land using 10 bits
						//temp = 
        }
    }

    return os;
}

std::istream& MapLand::fromCompactForm ( std::istream& is )
{
    for ( int i = 0; i < width(); i++ )
    {
        for ( int j = 0; j < height(); j++ )
        {

        }
    }

    return is;
}

} // namespace poplib
