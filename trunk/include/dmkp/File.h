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

#ifndef _H_DMKP32_IO_CFILE_CLASS
#define _H_DMKP32_IO_CFILE_CLASS

#define FILE_SIZE_NOT_EXISTS -1 //This is my own constant used to determine if a file exists or not, the cFileReaderClass will set the filesize variable to this when it was unable to open the file.
#define FILE_OPEN_READBIN "rb" //open file for binary reading
#define FILE_OPEN_WRITBIN "wb" //open file for binary writing

#include <cstdio>

namespace poplib
{

class FileReader;
class FileWriter;
class FileInfo;

enum File_Seek
{
    Seek_Begin = SEEK_SET,
    Seek_End = SEEK_END,
    Seek_Current = SEEK_CUR
};

class File
{
public:
    static FileReader* OpenRead ( const char* path );
    static FileWriter* OpenWrite ( const char* path );
    static FileInfo* OpenInfo ( const char* path );
};

} // namespace poplib

#endif /* _H_DMKP32_IO_CFILE_CLASS */
