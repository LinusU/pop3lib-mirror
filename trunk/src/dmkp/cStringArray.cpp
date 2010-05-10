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

#include "cStringArray.h"
#include "cString.h"

namespace poplib
{

void cString_Array::DefaultConstructor()
{
    pArray = 0;
    nArrayLength = 0;
}

void cString_Array::ResizeArray ( const unsigned int nExtraSpacesRequired )
{
    if ( nExtraSpacesRequired < 1 ) return;

    if ( pArray )
    {
        cString* copyOfArray = new cString[nArrayLength + nExtraSpacesRequired];
        for ( int i = 0; i < nArrayLength; i++ )
        {
            copyOfArray[i] = pArray[i];
        }

        delete[]pArray;
        pArray = copyOfArray;
        nArrayLength = nArrayLength + nExtraSpacesRequired;
    }
    else
    {
        pArray = new cString[nExtraSpacesRequired];
        nArrayLength = nExtraSpacesRequired;
    }
}

cString_Array::cString_Array()
{
    DefaultConstructor();
}

cString_Array::cString_Array ( const cString_Array& copyThis )
{
    DefaultConstructor();

    this->pArray = new cString[copyThis.GetArrayLength() ];

    for ( int i = 0; i < copyThis.GetArrayLength(); i++ )
    {
        //this->pArray[i] = new cString();
        ( this->pArray[i] ) = copyThis[i];
    }

    this->nArrayLength = copyThis.GetArrayLength();
}

cString_Array::~cString_Array()
{
    if ( pArray )
    {
        delete[]pArray;
    }

    pArray = 0;
    nArrayLength = 0;
}

unsigned int cString_Array::GetArrayLength() const
{
    return nArrayLength;
}

void cString_Array::Add ( cString& str )
{
    ResizeArray ( 1 );
    pArray[nArrayLength-1] = str;
}

int	cString_Array::Find ( cString& str ) const
{
    for ( int i = 0; i < nArrayLength; i++ ) if ( str == pArray[i] ) return i;

    return -1; //not present
}

cString	cString_Array::Join() const//join together into just a cString
{
    return Join ( "" );
}

cString cString_Array::Join ( const cString& medium ) const //join together, with this in between
{
    if ( nArrayLength < 1 ) return "";
    cString str = "";
    for ( int i = 0; i < nArrayLength; i++ )
    {
        if ( medium.GetStringLength() == 0 )
        {
            str = str + pArray[i];
        }
        else
        {
            str = str + pArray[i];

            if ( i < nArrayLength - 1 )
                str = str + medium;
        }
    }

    return str;
}

cString& cString_Array::operator [] ( const unsigned int index )
{
    assert ( index < nArrayLength );

    return ( pArray[index] );
}

const cString& cString_Array::operator [] ( const unsigned int index ) const
{
    assert ( index < nArrayLength );

    return ( pArray[index] );
}

cString_Array& cString_Array::operator= ( const cString_Array& arr )
{
    if ( pArray ) delete[]pArray;
    DefaultConstructor();

    this->pArray = new cString[arr.GetArrayLength() ];
    if ( pArray )
    {
        for ( int i = 0; i < arr.GetArrayLength(); i++ )
        {
            this->pArray[i] = arr[i];
        }
        this->nArrayLength = arr.GetArrayLength();

    }
    else
    {
        this->nArrayLength = 0;
        this->pArray = 0;
    }

    return *this;
}

}
