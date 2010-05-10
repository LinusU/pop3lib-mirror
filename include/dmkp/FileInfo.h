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

#ifndef _H_DMKP32_IO_CFILEINFO_CLASS
#define _H_DMKP32_IO_CFILEINFO_CLASS

namespace poplib
{
//Perhaps add a function to transfer the file handle to a reader or writer
//FileInfo::OpenRead?

class FileInfo
{
public:
    bool Error() const;
    long long FileSize() const;

    FileInfo ( const char* path );
private:
    bool isError;
    long long nFsize;
    //char szFname[MAX_PATH];

public:
    static FileInfo* OpenFile ( const char* path );
};

} // namespace poplib

#endif /* _H_DMKP32_IO_CFILEINFO_CLASS */
