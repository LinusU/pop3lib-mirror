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

#ifndef _H_POPLIB_DIR__
#define _H_POPLIB_DIR__

#include <list>
#include <string>

#include "global.h"

namespace poplib
{

#if defined(PLATFORM_WIN32)
/** Directories separator. */
const char dirSep = '\\';
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
/** Directories separator. */
const char dirSep = '/';
#endif

/** Basic directories functionality. */
class Dir
{
public:
    /** Lists files in the pointed directory, ignores subdirectories. */
    static std::list<std::string> listFiles(const std::string& dir);
};

} // namespace poplib

#endif // _H_POPLIB_DIR__
