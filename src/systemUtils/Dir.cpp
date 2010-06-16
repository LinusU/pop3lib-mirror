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

#include "global.h"

#if defined(PLATFORM_WIN32)
#	include <windows.h>
#	include <tchar.h>
#	include <stdio.h>
#	include <strsafe.h>
#elif defined(PLATFORM_LINUX)
#	include <dirent.h>
#endif

#include "systemUtils/Dir.h"

namespace poplib
{

std::list<std::string> Dir::listFiles(const std::string& dir)
{
    std::list<std::string> files;

#if defined(PLATFORM_WIN32)
    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    HANDLE hFind = INVALID_HANDLE_VALUE;

    // Prepare string for use with FindFile functions.  First, copy the
    // string to a buffer, then append '\*' to the directory name.
    StringCchCopy(szDir, MAX_PATH, dir.c_str());
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    // Find the first file in the directory.
    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
        return files;

    do
    {
        files.push_back(std::string(ffd.cFileName));
    }
    while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);
#elif defined(PLATFORM_LINUX)
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) != NULL) {
        while ((dirp = readdir(dp)) != NULL) {
            files.push_back(std::string(dirp->d_name));
        }
        closedir(dp);
    }
#endif

    return files;
}

} // namespace poplib
