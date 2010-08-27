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

#ifndef MARKER_H__
#define MARKER_H__

#include <iostream>

namespace poplib
{
/** Markers are stored in the header file. Each marker have x and y coordinate.
Markers are used by AI scripts. */
class Marker
{
public:
    char x, y;

    Marker(): x(0), y(0) { }

    Marker ( char xCoord, char yCoord ): x(xCoord), y(yCoord) { }

    bool isNull() const { return x == 0 && y == 0; }

    friend std::ostream& operator<< ( std::ostream& os, const Marker& obj )
    {
        os.write ( &obj.x, 1 );
        os.write ( &obj.y, 1 );

		return os;
    }

    friend std::istream& operator>> ( std::istream& is, Marker& obj )
    {
        is.read ( reinterpret_cast<char *> ( &obj.x ) , 1 );
        is.read ( reinterpret_cast<char *> ( &obj.y ) , 1 );

		return is;
    }
};

} // namespace poplib

#endif // MARKER_H__
