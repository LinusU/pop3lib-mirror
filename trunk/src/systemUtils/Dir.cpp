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

#if defined(PLATFORM_WIN32)

#elif defined(PLATFORM_LINUX)
//#include <sys/types.h>
#include <dirent.h>
#endif

#include <dirent.h> // FIXME remove me
#include "systemUtils/Dir.h"

namespace poplib
{

std::list<std::string> Dir::listFiles(const std::string& dir)
{
    std::list<std::string> files;

#if defined(PLATFORM_WIN32)

#elif defined(PLATFORM_LINUX)
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) != NULL) {
        while ((dirp = readdir(dp)) != NULL) {
            if (dirp->d_type == 8) // it's regular file
                files.push_back(std::string(dirp->d_name));
        }
        closedir(dp);
    }
#endif

    return files;
}

} // namespace poplib
