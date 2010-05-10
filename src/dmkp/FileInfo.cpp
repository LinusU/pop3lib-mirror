/*
Copyright (C) 2009 Populous Mana Source Development Team

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

#include "FileReader.h"
#include "FileInfo.h"
#include "FileWriter.h"

namespace poplib
{

FileInfo::FileInfo ( const char *path )
{
    //*szFname = 0;

    FileReader reader = FileReader ( path );

    if ( reader.Error() )
    {
        nFsize = FILE_SIZE_NOT_EXISTS;
        isError = true;
    }
    else
    {
        nFsize = reader.FileSize();
        isError = false;
    }
}

bool FileInfo::Error() const
{
    return isError;
}

long long FileInfo::FileSize() const
{
    return nFsize;
}

FileInfo* FileInfo::OpenFile ( const char* path )
{
    if ( !path )
        return 0;

    return new FileInfo ( path );
}

} // namespace poplib
