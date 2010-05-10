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

#include "FileWriter.h"
#include "cString.h"

namespace poplib
{

bool FileWriter::Error() const
{
    if ( pFile )
    {
        return ferror ( pFile );
    }
    else
        return true;
}

void FileWriter::CloseFile()
{
    if ( pFile )
    {
        fclose ( pFile );
        pFile = 0;
    }
}

void FileWriter::WriteUInt16 ( const unsigned short ushort )
{
    if ( pFile )
    {
        unsigned char buf[2];
        * ( ( unsigned short* ) ( buf ) ) = ushort;

        fwrite ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteUInt32 ( const unsigned int uint )
{
    if ( pFile )
    {
        unsigned char buf[4];
        * ( ( unsigned int* ) ( buf ) ) = uint;

        fwrite ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteUInt64 ( const unsigned long long ulng )
{
    if ( pFile )
    {
        unsigned char buf[8];
        * ( ( unsigned long long* ) ( buf ) ) = ulng;

        fwrite ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteUInt8 ( const unsigned char byte )
{
    if ( pFile )
    {
        unsigned char buf = byte;

        fwrite ( &buf, sizeof ( buf ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteInt16 ( const signed short shrt )
{
    if ( pFile )
    {
        unsigned char buf[2];
        * ( ( signed short* ) ( buf ) ) = shrt;

        fwrite ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteInt32 ( const signed int int_32 )
{
    if ( pFile )
    {
        unsigned char buf[4];
        * ( ( signed int* ) ( buf ) ) = int_32;

        fwrite ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteInt64 ( const signed long long lng )
{
    if ( pFile )
    {
        unsigned char buf[8];
        * ( ( signed long long* ) ( buf ) ) = lng;

        fwrite ( buf, sizeof ( buf[0] ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteInt8 ( const signed char sbyte )
{
    if ( pFile )
    {
        signed char buf = sbyte;

        fwrite ( &buf, sizeof ( buf ), sizeof ( buf ), pFile );
    }
}

void FileWriter::WriteANSIString ( const cString& cstrString )
{
    if ( pFile )
    {
        char buf = 0;
        if ( cstrString.GetBufferLength() < 1 )
        {
            fwrite ( &buf, 1, 1, pFile ); //just write the null, if someone reads from a file and the string was empty when written, it will mess up
        }
        else
        {

            for ( int i = 0; i < cstrString.GetBufferLength(); i++ )
            {
                fwrite ( cstrString.Const_BufferPtr() + i, 1, 1, pFile );
            }
        }
    }
}

void FileWriter::Seek ( const File_Seek seek_where_from, const signed long amount )
{
    if ( pFile )
    {
        fseek ( pFile, amount, seek_where_from );
    }
}

long FileWriter::Position() const
{
    if ( pFile )
    {
        return ftell ( pFile );
    }

    return FILE_SIZE_NOT_EXISTS; //the constant to indicate a file does not exist/there is an error
}

FileWriter::FileWriter ( const char* path )
{
    pFile = 0;
    if ( path )
    {
        pFile = fopen ( path, FILE_OPEN_WRITBIN/*"wb"*/ );
    }
}

FileWriter::FileWriter()
{
    CloseFile();
}

FileWriter* FileWriter::OpenFile ( const char* path )
{
    if ( !path )
        return 0;

    return new FileWriter ( path );
}

} // namespace poplib
