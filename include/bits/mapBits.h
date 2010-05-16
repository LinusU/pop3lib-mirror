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

#ifndef _H_POPLIB_MAP_HEADERBITS__
#define _H_POPLIB_MAP_HEADERBITS__

namespace poplib
{

enum _Allies {ALLY_BLUE = 1, ALLY_RED = 1 << 1, ALLY_YELLOW = 1 << 2, ALLY_GREEN = 1 << 3};
inline _Allies operator| ( _Allies ally1, _Allies ally2 )
{ return _Allies ( static_cast<int> ( ally1 ) | static_cast<int> ( ally2 ) ); }

enum _Teams {IVO = 1, EVO = 1 << 1, TVB = 1 << 2, FFA = 1 << 3, THREE_WAY = 1 << 4, TWO_WAY = 1 << 5};
inline _Teams operator| ( _Teams teams1, _Teams teams2 )
{ return _Teams ( static_cast<int> ( teams1 ) | static_cast<int> ( teams2 ) ); }

} // namespace poplib

#endif // _H_POPLIB_MAP_HEADERBITS__
