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

#include "cStringBuilder.h"
#include <cstring>

namespace poplib
{

cStringBuilder::cStringBuilder()
{
    string = new char[1];
    string[0] = '\0';
    Length = 1;
}

cStringBuilder::~cStringBuilder()
{
    if ( !string == 0 )
    {
        delete[] string;
        string = 0;
    }
}

bool cStringBuilder::Append ( char *str1 )
{
    //if this is the first time a string is added or it has not been initialised with a string already....
    if ( !string )
    {
        string = new char[1];
        string[0] = '\0';
    }

    //get the length of the new string
    int len = strlen ( str1 );

    //get the current length of the array storing the string
    int arraySize = ArraySize(); //this includes the null at the end, so the length of the string to
    //add to this (str1) doesn't include the null in the counting but doesn't matter because
    //the null in the original string is overwritten with the first char in the string
    //to copy to it (str1)

    //create a temporary char array with the size of the two lengths added together
    char* temp = new char[len + arraySize];
    //copy to temp, the string stored in the original string
    strcpy ( temp, string );
    //add the string from the new string to the temp string
    strcat ( temp, str1 );
    //clear the original string
    delete[] string;
    Length = strlen ( temp ) + 1;
    //change the address
    string = temp;

    return true;

}

int cStringBuilder::ArraySize()
{
    if ( string )
    {
        return StrLength() + 1; //could try strlen(string) + 1
    }
    else
        return 0;
}

int cStringBuilder::StrLength()
{
    if ( string )
    {
        return strlen ( string );
    }
    else
        return 0;
}

char* cStringBuilder::ToString()
{
    if ( string )
    {
        char* temp = new char[ArraySize() ];
        strcpy ( temp, string );
        return temp;
    }
    else
        return 0;
}

} // namespace poplib
