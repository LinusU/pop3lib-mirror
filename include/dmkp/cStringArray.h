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

#ifndef _H_CSTRINGARRAY__
#define _H_CSTRINGARRAY__

namespace poplib
{

class cString;

// TODO do we need classes like that?
class cString_Array
{
public:
    cString_Array();
    cString_Array ( const cString_Array& copyThis );
    ~cString_Array();

    unsigned int	GetArrayLength() const;

    void Add ( cString& str );
    int Find ( cString& str ) const;
    cString Join() const; //join together into just a cString
    cString Join ( const cString& medium ) const; //join together, with this in between

    cString& operator[] ( const unsigned int index );
    const cString&	operator[] ( const unsigned int index ) const;
    cString_Array&	operator= ( const cString_Array& arr );

private:
    void DefaultConstructor();

    cString* pArray;
    void ResizeArray ( const unsigned int nExtraSpacesRequired );
    unsigned int	nArrayLength;
};

} // namespace poplib

#endif /* _H_CSTRINGARRAY__ */
