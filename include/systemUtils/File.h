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

#ifndef _H_POPLIB_FILE__
#define _H_POPLIB_FILE__

#include <string>

#include "global.h"

namespace poplib
{
extern const char dirSep;

/** Operations on file names. */
class File
{
public:
    static std::string path(const std::string& directory, const std::string& fileName);
    static std::string fileNameWithExt(const std::string& filePath);
    static std::string fileName(const std::string& filePath);
    static std::string fileExtension(const std::string& filePath);
    static bool fileExists(const std::string& filePath);

private:
    static int extPos(const std::string& str);
};

} // namespace poplib

#endif // _H_POPLIB_FILE__
