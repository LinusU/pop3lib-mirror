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

#ifndef _H_DMKP32_IO_CFILEREADER_CLASS____
#define _H_DMKP32_IO_CFILEREADER_CLASS____

#include "File.h"

namespace poplib
{

class cString;

class FileReader
{
private:
    std::FILE* pFile;
    long long nSize;
    long long CalculateFileSize(); //calculate filesize initially when opening a file

public:
    bool Exists() const;
    bool Error() const;
    long long FileSize() const;
    bool EndOfStream() const;
    //bool OpenFile(const char* path); //replaced with static version
    void CloseFile();

    unsigned short ReadUInt16();
    unsigned int ReadUInt32();
    unsigned long long ReadUInt64();
    unsigned char ReadUInt8();

    signed short ReadInt16();
    signed int ReadInt32();
    signed long long ReadInt64();
    signed char ReadInt8();

    cString ReadANSIString();

    void Seek ( const File_Seek seek_where_from, const signed long amount );
    long Position() const;

    FileReader ( const char* path );
    ~FileReader();

public:
    static FileReader* OpenFile ( const char* path );

};

} // namespace poplib

#endif /* _H_DMKP32_IO_CFILEREADER_CLASS____ */


//bool cFileReader::OpenFile(const char* path)
//{
//	if(path)
//	{

//		if(pFile)
//			CloseFile();

//		pFile = fopen(path, "rb");

//		if(pFile)
//		{
//			nSize = CalculateFileSize();
//			return true;
//		}

//	}
//	return false;
//}
