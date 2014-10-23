/*
Copyright (C) 2010 Populous Mana Source Development Team

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

#include <fstream>

#include "String16.h"

namespace poplib
{

String16::String16()
{
    mdata = new UTF16[2];
    mdata[0] = 0; mdata[1] = 0;
    msize = 2;
}

String16::String16(const char * str)
{
    int len = strlen(str);
    msize = (len + 1)*sizeof(UTF16);
    mdata = new UTF16[len + 1];
    
    // deep copy of the data
    for(int i = 0; i < len; ++i)
    {
        mdata[i] = str[i];
    }
    
    // null termination character
    mdata[len] = 0;
}

String16::String16(const UTF32* str)
{
    // TODO string16 constructing from UTF32
}

String16::String16(const UTF16* str)
{
    int i = 0;
    UTF16 c;
    while (true)
    {
        c = str[i];
        if (c == 0)
        {
            msize = (i + 1)*sizeof(UTF16);
            mdata = new UTF16[i + 1];
            std::memcpy(mdata, str, msize);
            break;
        }
        ++i;
    }
}

String16::String16(const UTF8* str)
{
    // TODO string16 constructing from UTF8
}

String16::String16(const String16& str): msize(str.msize)
{
    mdata = new UTF16[msize/sizeof(UTF16)];
    std::memcpy(mdata, str.mdata, msize);
}

String16& String16::operator=(const String16& str)
{
    delete[] mdata;

    msize = str.msize;
    mdata = new UTF16[msize/sizeof(UTF16)];
    std::memcpy(mdata, str.mdata, msize);
	return *this;
}

String16::~String16()
{
    delete[] mdata;
}

std::ostream& operator<<(std::ostream& os, const String16& obj)
{
    os.write(reinterpret_cast<const char *>(obj.data16()), obj.dataSize());

    return os;
}

std::istream& operator>>(std::istream& is, String16& obj)
{
    // TODO storing string16 data using utf-8 encoding - it's usualy shorter
    delete[] obj.mdata;

    int pos = static_cast<int>(is.tellg());
    obj.msize = 0;
    UTF16 c;
    while (true)
    {
        c = 0;
        is.read(reinterpret_cast<char *>(&c), sizeof(UTF16));
        ++obj.msize;
        if (c == 0)
            break;
    }

    obj.msize = obj.msize * sizeof(UTF16);
    obj.mdata = new UTF16 [obj.msize/sizeof(UTF16)];
    is.seekg(pos);
    is.read(reinterpret_cast<char *>(obj.mdata), obj.msize);

    return is;
}

} // namespace poplib
