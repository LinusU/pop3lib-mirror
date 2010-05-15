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

#include "systemUtils/File.h"

namespace poplib
{

std::string File::path(const std::string& directory, const std::string& fileName)
{
    std::string filePath = directory;
    char lastChar = directory.at ( directory.length() - 1 );
    if ( lastChar != '/' && lastChar != '\\' )
    {
#if defined(PLATFORM_WIN32)
        filePath += dirSep;
#elif defined(PLATFORM_LINUX)
        filePath += dirSep;
#endif
    }

    return filePath + fileName;
}

std::string File::fileNameWithExt(const std::string& filePath)
{
    std::string withExt("");
    char c = filePath.at(filePath.size() - 1);
    for (int i = filePath.size() - 1; i >= 0 && c != dirSep; --i)
        withExt += c;

    return withExt;
}

std::string File::fileName(const std::string& filePath)
{
    std::string withExt = fileNameWithExt(filePath);

    std::string fileName("");
    char c = withExt.at(withExt.size() - 1);
    for (int i = withExt.size() - 1; i >= 0 && c != dirSep && c != '.'; --i)
        fileName += c;

    return fileName;
}

std::string File::fileExtension(const std::string& filePath)
{
    std::string name = fileNameWithExt(filePath);

    std::string ext("");
    char c = name.at(name.size() - 1);
    bool hasExt = false;
    for (int i = name.size() - 1; i >= 0 && !(hasExt = c == '.'); --i)
        ext += c;

    if (hasExt)
        return ext;
    else
        return std::string("");
}

} // namespace poplib
