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

#ifndef _H_DMKP32_IO_CFILEWRITER_CLASS__
#define _H_DMKP32_IO_CFILEWRITER_CLASS__

#include "File.h"

namespace poplib
{

class cString;

class FileWriter
{
private:
    std::FILE* pFile;

public:
    bool Error() const;

    void CloseFile();

    void WriteUInt16 ( const unsigned short ushort );
    void WriteUInt32 ( const unsigned int uint );
    void WriteUInt64 ( const unsigned long long ulng );
    void WriteUInt8 ( const unsigned char byte );

    void WriteInt16 ( const signed short shrt );
    void WriteInt32 ( const signed int int_32 );
    void WriteInt64 ( const signed long long lng );
    void WriteInt8 ( const signed char sbyte );

    void WriteANSIString ( const cString& cstrString );

    void Seek ( const File_Seek seek_where_from, const signed long amount );
    long Position() const;

    FileWriter ( const char* path );
		FileWriter();
    ~FileWriter();

public:
    static FileWriter* OpenFile ( const char* path );
};

} // namespace poplib

#endif /* _H_DMKP32_IO_CFILEWRITER_CLASS__ */
