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

#include "cString.h"
#include <cstring>

namespace poplib
{

void cString::DefaultConstructor()
{
    pBuffer = 0;
    nBufferLength = 0;
    nStringLength = 0;
}

cString::cString()
{
    DefaultConstructor();
}

cString::cString ( const char *szCharArray )
{
    if ( !szCharArray )
    {
        DefaultConstructor();
    }
    else
    {
        int len = strlen ( szCharArray ) + 1;
        pBuffer = new char[len];

        if ( pBuffer )
        {
            strcpy ( pBuffer, szCharArray );
            nBufferLength = len;
            nStringLength = len - 1;
        }
        else
        {
            DefaultConstructor();
        }
    }
}

cString::cString ( const char *szCharArray, const int nStrLen )
{
    pBuffer = new char[nStrLen + 1];
    if ( pBuffer )
    {
        for ( int i = 0; i < nStrLen; i++ )
        {
            pBuffer[i] = szCharArray[i];
        }
        pBuffer[nStrLen] = 0; //null terminate it

        nBufferLength = nStrLen + 1;
        nStringLength = nStrLen;
    }
    else
    {
        DefaultConstructor();
    }
}

cString::cString ( const char Character, const int nCharCount )
{
    pBuffer = new char[nCharCount + 1];

    if ( pBuffer )
    {
        for ( int i = 0; i < nCharCount; i++ ) pBuffer[i] = Character;
        pBuffer[nCharCount] = 0; //null terminated

        nBufferLength = nCharCount + 1;
        nStringLength = nCharCount;
    }
    else
    {
        DefaultConstructor();
    }
}

cString::cString ( const cString *cstrTemplate )
{
    if ( cstrTemplate )
    {
        if ( cstrTemplate->GetBufferLength() < 1 )
        {
            DefaultConstructor();
        }
        else
        {
            pBuffer = cstrTemplate->GetBufferCopy();

            if ( pBuffer )
            {
                nBufferLength = cstrTemplate->GetBufferLength();
                nStringLength = cstrTemplate->GetStringLength();
            }
            else
            {
                DefaultConstructor();
            }

        }
    }
    else
    {
        DefaultConstructor();
    }
}

/*Copy Constructor*/ cString::cString ( const cString& copyThis )
{
    DefaultConstructor();

    this->pBuffer = copyThis.GetBufferCopy();
    this->nBufferLength = copyThis.GetBufferLength();
    this->nStringLength = copyThis.GetStringLength();
}

cString::~cString()
{
    if ( pBuffer )
    {
        delete[]pBuffer;
        pBuffer = 0;
    }

}


char& cString::operator[] ( unsigned int nIndex )
{
    assert ( nIndex < nStringLength );

    return pBuffer[nIndex];

}

const char& cString::operator[] ( unsigned int nIndex ) const
{
    assert ( nIndex < nStringLength );

    return pBuffer[nIndex];
}

cString	cString::operator+ ( const cString* str ) const
{
    //cString sz = cString(this);
    //sz.Append(str);
    return Join ( this, str );
}

cString	cString::operator+ ( const cString& str ) const
{
    return Join ( this, &str );
}

cString	cString::operator+ ( const char c ) const
{
    return Join ( this, &cString ( c, 1 ) );
}

cString cString::operator + ( const char* sz ) const
{
    return Join ( this, &cString ( sz ) );
}

bool cString::operator== ( const cString* str ) const
{
    return Compare ( this, str );
}

bool cString::operator== ( const cString& str ) const
{
    return Compare ( this, &str );
}

bool cString::operator!= ( const cString* str ) const
{
    return !Compare ( this, str );
}

bool cString::operator!= ( const cString& str ) const
{
    return !Compare ( this, &str );
}

cString& cString::operator = ( const cString &str )
{
    if ( this == &str ) return *this; //check for self assignment first

    if ( pBuffer ) delete[]pBuffer;
    DefaultConstructor();

    pBuffer = str.GetBufferCopy();
    nStringLength = str.GetStringLength();
    nBufferLength = str.GetBufferLength();

    return *this;
}



/*static function*/ cString cString::EmptyString()
{
    return "";
}


char cString::Char ( unsigned int nIndex ) const
{
    if ( nIndex < nBufferLength )
        return pBuffer[nIndex];
    else
        return 0;
}


/*static function*/cString* cString::cStrCat ( const cString* dest, const cString* src )
{
    cString* returnThis = new cString ( dest );

    if ( returnThis )
    {
        returnThis->Append ( src );
        return returnThis;
    }
    else
    {
        return 0;
    }
}

/*static function*/cString cString::Join ( const cString *dest, const cString *src )
{
    cString str ( dest );
    str.Append ( src );
    return str;
}


/*static function*/bool cString::Compare ( const cString* strA, const cString* strB )
{
    if ( !strA || !strB ) return false;

    if ( strA == strB ) return true; //check if they are pointing to the same instance first.

    if ( strA->GetStringLength() != strB->GetStringLength() ) //if the lengths are different, then it is not the same
        return false;
    else
    {
        //Iterate through, until it encounters a char that is not the same in both strings
        for ( int i = 0; i < strA->GetBufferLength(); i++ )
        {
            if ( strA->Char ( i ) != strB->Char ( i ) )
                return false;
        }

        //didn't find any differences, exit with true
        return true;
    }
}

bool cString::CompareTo ( const cString* strA ) const
{
    return Compare ( this, strA );
}

bool cString::CompareTo ( const cString& strA ) const
{
    return Compare ( this, &strA );
}


void cString::Append ( const cString* cstrString )
{
    if ( cstrString && this )
    {
        unsigned int len = this->GetStringLength() + cstrString->GetStringLength() + 1; //new buffer length
        char* newBuf = new char[len];

        if ( newBuf )
        {
            for ( int i = 0; i < this->GetStringLength(); i++ )
            {
                newBuf[i] = this->pBuffer[i];
            }

            for ( int i = this->GetStringLength(); i < this->GetStringLength() + cstrString->GetStringLength(); i++ )
            {
                //newBuf[i] = cstrString[i - this->GetStringLength()]; //doesn't work? wtf ASK ABOUT THIS
                newBuf[i] = cstrString->Char ( i - this->GetStringLength() );
            }

            newBuf[len - 1] = 0; //len -1  because "len" is the size of the buffer

            if ( pBuffer ) delete[]pBuffer;
            pBuffer = newBuf;
            nBufferLength = len;
            nStringLength = len - 1;
        }
    }
}

void cString::Append ( const cString& cstrString )
{
    Append ( &cstrString );
}

void cString::Append ( const char* szCharArray )
{
    this->Append ( &cString ( szCharArray ) );
}

void cString::Append ( const char* szCharArray, const int nStrLen )
{
    this->Append ( &cString ( szCharArray, nStrLen ) );
}


cString cString::Insert ( const cString* str, const unsigned int start ) const
{
    if ( !str ) return *this; //check for null ptr

    //without this line, it still has this same behaviour, however I believe it is probably faster to simply check this first and
    //add the strings together than get the substrings first and then add them together
    if ( start == 0 ) return *str + *this;
    else if ( start > nStringLength - 1 ) return *this + *str;

    cString strA = SubString ( 0, start );
    cString strB = *str;
    cString strC = SubString ( start );

    return strA + strB + strC;
}

cString cString::Insert ( const cString& str, const unsigned int start ) const
{
    return Insert ( &str, start );
}

unsigned int cString::GetBufferLength() const
{
    return nBufferLength;
}

unsigned int cString::GetStringLength() const
{
    return nStringLength;
}

char* cString::GetBufferCopy() const
{
    char* returnVal = new char[nBufferLength];
    if ( returnVal )
    {
        //strcpy(returnVal, pBuffer);
        //returnVal[nStringLength] = 0; //why is this necessary? strcpy should have done this for me but didn't.

        for ( int i = 0; i < nBufferLength; i++ )
        {
            returnVal[i] = pBuffer[i];
        }

        return returnVal;
    }

    return 0;
}


void cString::Clear()
{
    if ( pBuffer )
    {
        delete[] pBuffer;
        pBuffer = 0;
    }

    DefaultConstructor();

    *this = EmptyString();
}

const char* cString::Const_BufferPtr() const
{
    return pBuffer;
}

cString cString::SubString ( const unsigned int start ) const
{
    return SubString ( start, nStringLength );
}

cString cString::SubString ( const unsigned int start, const unsigned int length ) const
{
    if ( start > nStringLength -1 )
    {
        return EmptyString();
    }
    else
    {
        unsigned int begin = start, len = length;

        if ( start + length > nStringLength-1 )
        {
            len = nStringLength - begin;
        }

        char* sz = new char[len + 1];
        if ( sz )
        {
            for ( int i = 0; i < len; i++ )
            {
                sz[i] = pBuffer[i + start];
            }

            sz[len] = 0; //null terminator it :D

            cString str = sz;

            delete[]sz;
            return str;
        }
        else
        {
            return EmptyString();
        }
    }
}

cString cString::Remove ( const unsigned int start, const unsigned int length ) const //returns this string with the number of chars removed from the specified start index
{
    //can make a "TrimRight" and "TrimLeft" function using this function!!

    if ( start >= this->nStringLength )
        return *this;
    else
    {
        //0 to start is string A
        //length + start to end is string B

        if ( start == 0 )
        {
            return SubString ( start + length );
        }
        else
        {
            return Join ( &SubString ( 0, start ), &SubString ( start + length ) );
        }

        return "";
    }
}

cString cString::TrimLeft ( const unsigned int start ) const
{
    return SubString ( start );
}

cString cString::TrimRight ( const unsigned int start ) const
{
    return SubString ( 0, start + 1 );
}


bool cString::StartsWith ( const cString* str ) const
{
    if ( !str ) return false; //null ptr

    if ( this->nStringLength < str->GetStringLength() ) return false; //if the string isn't even as long as the one wanting to ask if it is at the beginning, then it's not there :p

    cString temp = this->SubString ( 0, str->GetStringLength() );
    return temp == str;

    //for some reason it won't let me use temp by itself when on the rhs, has to be a pointer 0.o even though the operator can take a reference!
}

bool cString::StartsWith ( const cString& str ) const
{
    return StartsWith ( &str );
}

bool cString::EndsWith ( const cString* str ) const
{
    if ( !str ) return false; //null ptr

    if ( this->nStringLength < str->GetStringLength() ) return false;

    //int start = this->GetStringLength() - str->GetStringLength();

    cString temp = this->SubString ( this->GetStringLength() - str->GetStringLength() );

    return ( temp == str );
}

bool cString::EndsWith ( const cString& str ) const
{
    return EndsWith ( &str );
}

bool cString::Contains ( const cString* str ) const
{
    if ( !str ) return false; //null ptr

    if ( str->GetStringLength() > this->GetStringLength() )
        return false; //can't possibly be in it if it is longer than it
    else
    {
        char* buf = this->GetBufferCopy();
        char* substr = str->GetBufferCopy();

        if ( buf && substr )
        {
            char* addr = strstr ( buf, substr );
            delete[] buf;
            delete[] substr;
            return addr != 0;
        }
        else
        {
            if ( buf ) delete[]buf;
            if ( substr ) delete[]substr;
            return false;
        }
    }
    //strstr(
}

bool cString::Contains ( const cString& str ) const
{
    return Contains ( &str );
}

int cString::IndexOf ( const cString* str ) const
{
    return IndexOf ( str, 0 );
    //if(!str) return -1; //null ptr exception

    //char* copy = str->GetBufferCopy();

    //if(copy)
    //{
    //	char* index = strstr(this->pBuffer, copy); //strstr returns a pointer to the location of a string within a string
    //	delete[]copy;
    //	int position = (int)(index - pBuffer);
    //	return position < 0 ? -1 : position;
    //}

    //return -1;
}

int cString::IndexOf ( const cString& str ) const
{
    return IndexOf ( &str );
}


int cString::IndexOf ( const cString* str, const unsigned int start ) const
{
    if ( !str ) return -1; //null ptr exception

    if ( start > nStringLength - 1 ) return -1;

    char* copy = str->GetBufferCopy();

    if ( copy )
    {
        char* index = strstr ( ( this->pBuffer + start ), copy ); //strstr returns a pointer to the location of a string within a string
        delete[]copy;
        int position = ( int ) ( index - pBuffer );
        return position < 0 ? -1 : position;
    }

    return -1;
}

int cString::IndexOf ( const cString& str, const unsigned int start ) const
{
    return IndexOf ( &str, start );
}

int cString::LastIndexOfChar ( const char* str ) const
{
    if ( !str ) return -1; //null ptr exception

    char* index = ( strrchr ( pBuffer, *str ) ); //strrchr returns the last index of a character, strchr returns the first index of

    int position = ( int ) ( index - pBuffer );
    return position < 0 ? -1 : position;

    return -1;
}

int cString::LastIndexOfChar ( const char& str ) const
{
    return LastIndexOfChar ( &str );
}

int cString::IndexOfChar ( const char* str ) const
{
    if ( !str ) return -1; //null ptr exception

    char* index = ( strchr ( pBuffer, *str ) ); //strchr returns the first index of,strrchr returns the last index of a character

    int position = ( int ) ( index - pBuffer );
    return position < 0 ? -1 : position;

    return -1;
}

int cString::IndexOfChar ( const char& str ) const
{
    return IndexOfChar ( &str );
}

cString cString::ReplaceOnce ( const cString* ThisStr, const cString* withThatStr ) const
{
    if ( ! ( ThisStr && withThatStr ) ) return *this;
    if ( *ThisStr == cString::EmptyString() ) return *this; //without this, if you did ReplaceOnce("", "ssasds") it added it onto the beginning

    char* szParent = GetBufferCopy();
    char* szThis = ThisStr->GetBufferCopy();
    char* szThat = withThatStr->GetBufferCopy();

    //copy all the buffers

    if ( szParent && szThat && szThis ) //check they are not null pointers
    {
        char* index = strstr ( szParent, szThis );
        if ( index ) //get the index of the first occurance of szThis
        {
            if ( ThisStr->GetStringLength() == withThatStr->GetStringLength() ) //no resizing needed because it is the same length as the replace
            {
                strncpy ( index, szThat, withThatStr->GetStringLength() ); //this is pointing to the szParent buffer, so

                cString returnVal = szParent; //we can just copy it

                if ( szThis ) delete[]szThis;
                if ( szThat ) delete[]szThat;
                if ( szParent ) delete[]szParent;

                return returnVal;
            }
            else
            {
                //we use szParent and the index together here because those are the two things we were just working with
                //and we do not want to change *this instance... but return a copy with the changes implemented

                cString strA = SubString ( 0, ( int ) ( index - szParent ) );
                cString strB = withThatStr;
                cString strC = SubString ( ( int ) ( index - szParent ) + ThisStr->GetStringLength() );

                cString returnVal = strA + strB + strC;


                if ( szThis ) delete[]szThis;
                if ( szThat ) delete[]szThat;
                if ( szParent ) delete[]szParent;

                return returnVal;
            }
        }
        else //if not found, return this instance unchanged
        {
            if ( szThis ) delete[]szThis;
            if ( szThat ) delete[]szThat;
            if ( szParent ) delete[]szParent;

            return *this;
        }
    }
    else //if some are, check which ones aren't and delete
    {
        if ( szThis ) delete[]szThis;
        if ( szThat ) delete[]szThat;
        if ( szParent ) delete[]szParent;

        return *this; //return this instance, unchanged
    }
}

cString cString::ReplaceOnce ( const cString& This, const cString& withThat ) const
{
    return ReplaceOnce ( &This, &withThat );
}

cString cString::ReplaceOnce ( const cString* This, const cString& withThat ) const
{
    return ReplaceOnce ( This, &withThat );
}

cString cString::ReplaceOnce ( const cString& This, const cString* withThat ) const
{
    return ReplaceOnce ( &This, withThat );
}

//cString cString::ReplaceAll(const cString* ThisStr, const cString* withThatStr) const
//{
//	if(!(ThisStr && withThatStr)) return *this;

//	if(ThisStr->GetStringLength() == 0 || *ThisStr == EmptyString()) return *this; //prevent infinite loop

//	cString copy = *this;

//	if(!(copy.Contains(ThisStr))) return *this;
//	else
//	{
//		while(copy.Contains(ThisStr))
//		{
//			copy = copy.ReplaceOnce(ThisStr, withThatStr);
//		}

//		return copy;
//	}
//}

//cString cString::ReplaceAll(const cString* This, const cString& withThat) const
//{
//	return ReplaceAll(This, &withThat);
//}

//cString cString::ReplaceAll(const cString& This, const cString* withThat) const
//{
//	return ReplaceAll(&This, withThat);
//}

//cString cString::ReplaceAll(const cString& This, const cString& withThat) const
//{
//	return ReplaceAll(&This, &withThat);
//}

cString cString::ToLower() const
{
    char* buf = this->GetBufferCopy();

    if ( buf )
    {
        for ( int i = 0; i < this->GetBufferLength(); i++ )
        {
            buf[i] = CharToLower ( buf[i] );
        }

        cString str = buf;

        delete[]buf;

        return str;
    }
    else
    {
        return *this;
    }
}

cString cString::ToUpper() const
{
    char* buf = this->GetBufferCopy();

    if ( buf )
    {
        for ( int i = 0; i < this->GetBufferLength(); i++ )
        {
            buf[i] = CharToUpper ( buf[i] );
        }

        cString str = buf;

        delete[]buf;

        return str;
    }
    else
    {
        return *this;
    }
}

cString cString::InvertCase() const
{
    char* buf = this->GetBufferCopy();

    if ( buf )
    {
        for ( int i = 0; i < this->GetBufferLength(); i++ )
        {
            if ( IsLowerCase ( buf[i] ) )
            {
                buf[i] = CharToUpper ( buf[i] );
            }
            else
            {
                buf[i] = CharToLower ( buf[i] );
            }
        }

        cString str = buf;
        delete[]buf;
        return str;
    }
    else
    {
        return *this;
    }
}

/*static function*/ char cString::CharToLower ( const char c )
{
    if ( ( int ) ( c ) < 91 && ( int ) ( c ) > 64 )
    {
        return ( char ) ( ( int ) ( c ) + 32 );
    }
    else
    {
        return c;
    }
}

/*static function*/ char cString::CharToUpper ( const char c )
{
    if ( ( int ) ( c ) < 123 && ( int ) ( c ) > 96 )
    {
        return ( char ) ( ( int ) ( c ) - 32 );
    }
    else
    {
        return c;
    }
}

/*static function*/ bool cString::IsLowerCase ( const char c )
{
    //#if _DEBUG
    //			bool test = (((int)(c) < 123) && ((int)(c) > 96));
    //#endif
    return ( ( ( int ) ( c ) < 123 ) && ( ( int ) ( c ) > 96 ) );
}

/*static function*/ bool cString::IsUpperCase ( const char c )
{
    //#if _DEBUG
    //			bool test = (((int)(c) < 91) && ((int)(c) > 64));
    //#endif
    return ( ( ( int ) ( c ) < 91 ) && ( ( int ) ( c ) > 64 ) );
}




/*static function*/ bool cString::IsDigit ( const char c )
{
    //#if _DEBUG
    //			bool test = (((int)(c) > 47) && ((int)(c) < 58));
    //#endif
    return ( ( ( int ) ( c ) > 47 ) && ( ( int ) ( c ) < 58 ) );
}

/*static function*/ bool cString::IsAlpha ( const char c )
{
    return IsLowerCase ( c ) || IsUpperCase ( c );
}
/*static function*/ bool cString::IsAlNum ( const char c )
{
    return IsAlpha ( c ) || cString::IsDigit ( c );
}

/*static function*/ bool cString::IsNumber ( const cString* str )
{
    if ( !str ) return false;

    for ( int i = 0; i < str->GetStringLength(); i++ )
    {
        if ( !IsDigit ( ( *str ) [i] ) )
            return false;
    }

    return true;
}

/*static function*/ bool cString::IsNumber ( const cString& str )
{
    return IsNumber ( &str );
}

/*static function*/ bool cString::IsAlNum ( const cString* str )
{
    if ( !str ) return false;

    for ( int i = 0; i < str->GetStringLength(); i++ )
    {
        if ( IsDigit ( ( *str ) [i] ) || IsAlpha ( ( *str ) [i] ) )
            continue;
        else
            return false;
    }

    return true;
}

/*static function*/ bool cString::IsAlNum ( const cString& str )
{
    return IsAlNum ( &str );
}

bool cString::IsAlNum() const
{
    return IsAlNum ( this );
}

bool cString::IsNumber() const
{
    return IsNumber ( this );
}

} // namespace poplib
