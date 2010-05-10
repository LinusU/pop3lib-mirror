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

#ifndef _H_DMKP32_CSTRING_CLASS__
#define _H_DMKP32_CSTRING_CLASS__

#include <cassert>
#include <iostream>

namespace poplib
{

	// TODO Do we need classes like that ?
class cString
{
public:
    cString();
    cString ( const char* szCharArray ); //uses strlen to get the length of the string
    cString ( const char* szCharArray, const int nStrLen ); //uses nStrLen + 1 for the buffer length, and nStrLen to copy the chars
    cString ( const char Character, const int nCharCount ); //creates a string filled with that character at nCharCount length, buffer is + 1 to that length
    cString ( const cString* cstrTemplate ); //creates a new string and initialises it to the value of the string argument
    //Copy constructor
    cString ( const cString& copyThis );

    ~cString();

    // Subscript operator
    char& operator[] ( unsigned int nIndex );
    const char& operator[] ( unsigned int nIndex ) const;

    cString operator+ ( const cString* str ) const;
    cString operator+ ( const cString& str ) const;

    cString operator+ ( const char c ) const;
    cString	operator+ ( const char* sz ) const;

    bool operator== ( const cString* str ) const;
    bool operator== ( const cString& str ) const;
    bool operator!= ( const cString* str ) const;
    bool operator!= ( const cString& str ) const;

    cString& operator= ( const cString& str );

    static cString	EmptyString();

    char Char ( unsigned int nIndex ) const;

    static cString* cStrCat ( const cString* dest, const cString* src );
    static cString Join ( const cString *dest, const cString *src );

    static bool Compare ( const cString* strA, const cString* strB );
    bool CompareTo ( const cString* strA ) const;
    bool CompareTo ( const cString& strA ) const;

    void Append ( const cString* cstrString );
    void Append ( const cString& cstrString );
    void Append ( const char* szCharArray );
    void Append ( const char* szCharArray, const int nStrLen );

    cString Insert ( const cString* str, const unsigned int start ) const;
    cString Insert ( const cString& str, const unsigned int start ) const;

    unsigned int GetBufferLength() const;
    unsigned int GetStringLength() const;

    const char* Const_BufferPtr() const;

    void Clear(); //empties the string

    cString Remove ( const unsigned int start, const unsigned int length ) const; //returns this string with the number of chars removed from the specified start index
    cString SubString ( const unsigned int start ) const;
    cString SubString ( const unsigned int start, const unsigned int length ) const;

    cString TrimLeft ( const unsigned int start ) const;
    cString TrimRight ( const unsigned int start ) const;

    cString ReplaceOnce ( const cString* ThisStr, const cString* withThatStr ) const;
    cString ReplaceOnce ( const cString& This, const cString& withThat ) const;
    cString ReplaceOnce ( const cString* This, const cString& withThat ) const;
    cString ReplaceOnce ( const cString& This, const cString* withThat ) const;
    //cString ReplaceAll(const cString* ThisStr, const cString* withThatStr) const;
    //cString ReplaceAll(const cString* This, const cString& withThat) const;
    //cString ReplaceAll(const cString& This, const cString* withThat) const;
    //cString ReplaceAll(const cString& This, const cString& withThat) const;

    bool EndsWith ( const cString& ) const;
    bool StartsWith ( const cString& ) const;
    bool EndsWith ( const cString* ) const;
    bool StartsWith ( const cString* ) const;

    bool Contains ( const cString* ) const;
    bool Contains ( const cString& ) const;

    int IndexOf ( const cString* ) const;
    int IndexOf ( const cString& ) const;
    int IndexOf ( const cString* str, const unsigned int start ) const;
    int IndexOf ( const cString& str, const unsigned int start ) const;

    int LastIndexOfChar ( const char* ) const;
    int LastIndexOfChar ( const char& ) const;
    int IndexOfChar ( const char* ) const;
    int IndexOfChar ( const char& ) const;

    cString ToUpper() const;
    cString ToLower() const;
    cString InvertCase() const;

    // mode #chan +b #popmm x?????_*!*@* //--this was shown on popre

    //it is supposed to be:
    //mode #chan +b *!*@*
    //and
    //mode #chan +e x?????_*!*@*
    //http://www.youtube.com/watch?v=56I1m__fnBY&eurl=http://icanhascheezburger.com/page/1/&feature=player_embedded

    static char CharToLower ( const char c );
    static char CharToUpper ( const char c );
    static bool IsUpperCase ( const char c );
    static bool IsLowerCase ( const char c );
    static bool IsDigit ( const char c );
    static bool IsAlpha ( const char c );
    static bool IsAlNum ( const char c ); //(A - Z) (a - z) (0 - 9)
    static bool IsNumber ( const cString* str );
    static bool IsNumber ( const cString& str ); //returns if the sole contents of the string are just numbers (0 - 9)
    static bool IsAlNum ( const cString* str );
    static bool IsAlNum ( const cString& str );

    bool IsAlNum() const;
    bool IsNumber() const;

private:
    void DefaultConstructor();
    char* GetBufferCopy() const;
    char* pBuffer;
    unsigned int nBufferLength;
    unsigned int nStringLength;
};

//More ideas:
//Split ? - this will require a new class xD cStringArray.

} // namespace poplib

#endif /* _H_DMKP32_CSTRING_CLASS__ */
