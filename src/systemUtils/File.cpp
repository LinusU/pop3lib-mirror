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

#include <fstream>

#include "systemUtils/File.h"
#include "systemUtils/Dir.h"
#include "StrUtil.h"

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
    int i;
    for (i = filePath.size() - 1; i >= 0; --i)
    {
        if (filePath.at(i) == dirSep)
            break;
    }

    return filePath.substr(i + 1, filePath.size());
}

std::string File::fileName(const std::string& filePath)
{
    std::string withExt = fileNameWithExt(filePath);
    int pos = extPos(withExt);

    if (pos > 0)
        return withExt.substr(0, pos);
    else
        return withExt;
}

std::string File::fileExtension(const std::string& filePath)
{
    std::string withExt = fileNameWithExt(filePath);
    int pos = extPos(withExt);

    if (pos > 0)
        return withExt.substr(pos + 1, withExt.size() - pos);
    else
        return std::string("");
}

bool File::fileExists(const std::string& filePath)
{
    std::ifstream fin;
    fin.open(filePath.c_str(), std::ios::in);
    bool exists = fin.is_open();
    fin.close();

    return exists;
}

int File::extPos(const std::string& str)
{
    char c;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        c = str.at(i);
        if (c == '.')
        {
            if (i > 0 && i < str.size() - 1)
                return i;
            else
                return 0;
        }
    }
}

} // namespace poplib
