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

#ifndef _H_GLOBAL__
#define _H_GLOBAL__

namespace poplib
{

// platform detection
#if defined( __WIN32__ ) || defined( _WIN32 )
#	define PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#	define PLATFORM_APPLE
#else
#	define PLATFORM_LINUX
#endif

// platform dependend unit size declarations
typedef unsigned char UBYTE;
typedef signed char SBYTE;
typedef unsigned short UWORD;
typedef signed short SWORD;
typedef unsigned int UDWORD;
typedef signed int SDWORD;

} // namespace poplib

#endif // _H_GLOBAL__
