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
#include "cString.h"

namespace poplib
{

bool FileReader::Exists() const
{
    return FileSize() > FILE_SIZE_NOT_EXISTS;
}

bool FileReader::Error() const
{
    if ( pFile )
    {
        return ferror ( pFile );
    }
    else
        return true;
}

long long FileReader::CalculateFileSize()
{
    if ( pFile )
    {
        //long pos = ftell(pFile);
        long size = 0;
        fseek ( pFile, 0, Seek_End );
        size = ftell ( pFile );
        fseek ( pFile, 0/*pos*/, Seek_Begin );
        return size;
    }
    else
        return FILE_SIZE_NOT_EXISTS;
}

long long FileReader::FileSize() const
{
    return nSize;
}

bool FileReader::EndOfStream() const
{
    //return feof(pFile);
    //feof didn't return true unless something tried to read after the last char in the file had been read already
    return Position() == FileSize();
}

FileReader* FileReader::OpenFile ( const char* path )
{
    if ( !path )
        return 0;

    return new FileReader ( path );
}//Create a new file reader class with a file open, returns null when it cannot open the file.

void FileReader::CloseFile()
{
    if ( pFile )
    {
        fclose ( pFile );
        pFile = 0;
        nSize = 0;
    }
}


unsigned short FileReader::ReadUInt16()
{
    if ( !pFile )
        return 0;


    unsigned char buf[2];

    fread ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );

    return * ( ( unsigned short* ) buf );
}

unsigned int FileReader::ReadUInt32()
{
    if ( !pFile )
        return 0;


    unsigned char buf[4];

    fread ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );

    return * ( ( unsigned int* ) buf );
}

unsigned long long FileReader::ReadUInt64()
{
    if ( !pFile )
        return 0;


    unsigned char buf[8];

    fread ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );

    return * ( ( unsigned long long* ) buf );
}


unsigned char FileReader::ReadUInt8()
{
    if ( !pFile )
        return 0;

    unsigned char buf;
    fread ( &buf, sizeof ( buf ), sizeof ( buf ), pFile );

    return buf;
}


signed short FileReader::ReadInt16()
{
    if ( !pFile )
        return 0;

    unsigned char buf[2];
    fread ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );

    return * ( ( signed short* ) buf );
}

signed int FileReader::ReadInt32()
{
    if ( !pFile )
        return 0;

    unsigned char buf[4];

    fread ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    return * ( ( signed int* ) buf );
}

signed long long FileReader::ReadInt64()
{
    if ( !pFile )
        return 0;

    unsigned char buf[8];
    fread ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );

    return * ( ( signed long long* ) buf );
}

signed char FileReader::ReadInt8()
{
    if ( !pFile )
        return 0;

    signed char buf = 0;
    fread ( &buf, sizeof ( buf ), sizeof ( buf ), pFile );

    return buf;
}

void FileReader::Seek ( const File_Seek seek_where_from, const signed long amount )
{
    if ( pFile )
    {
        fseek ( pFile, amount, seek_where_from );
    }
}

cString FileReader::ReadANSIString()
{
    if ( !pFile ) return "";

    if ( EndOfStream() ) return "";
    else
    {
        cString retVal = "";
        char buf = 0;

        while ( true )
        {
            int read = fread ( &buf, sizeof ( buf ), 1, pFile );

            if ( read )
            {
                if ( buf == 0 )
                {
                    return retVal;
                }
                else
                {
                    retVal = retVal + buf;
                }
            }
            else
            {
                return retVal;
            }
        }
    }
}

long FileReader::Position() const
{
    if ( pFile )
    {
        return ftell ( pFile );
    }

    return FILE_SIZE_NOT_EXISTS; //the constant to indicate a file does not exist
}
FileReader::FileReader ( const char *path )
{
    pFile = 0;
    nSize = FILE_SIZE_NOT_EXISTS;
    if ( path )
    {
        pFile = fopen ( path, FILE_OPEN_READBIN/*"rb"*/ );

        if ( pFile )
        {
            nSize = CalculateFileSize();
        }
    }
}

FileReader::~FileReader()
{
    if ( pFile )
    {
        fclose ( pFile );
        pFile = 0;
    }
}

} // namespace poplib
