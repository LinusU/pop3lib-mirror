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

#ifndef _H_POPLIB_MAP_STRING16__
#define _H_POPLIB_MAP_STRING16__

#include <string>
#include <iostream>
#include <cstring>

#include "UTFConversion.h"

namespace poplib
{

class String16
{
public:
    String16();
    /** Constructs object from a block of the data, encoded using start ANSI string representation. Makes a deep copy of data. */
    String16(const char * str);
    /** Not implemented yet. */
    String16(const UTF32* str);
    /** Constructs object from a block of the data, encoded with UTF-16 and terminated by null character. Makes a deep copy of data. */
    String16(const UTF16* str);
    /** Not implemented yet. */
    String16(const UTF8* str);
    String16(const String16& str);
    String16& operator=(const String16& str);
    virtual ~String16();

    /** Not implemented yet. */
    const UTF8* data8() const { return 0; } // TODO returning UTF8 data
    /** Returns null-terminated sequence of internal data. */
    const UTF16* data16() const { return mdata; }
     /** Not implemented yet. */
    const UTF32* data32() const { return 0; } // TODO returning UTF32 data
    /** Returns how many bytes is used by a string with null termination. */
    unsigned int dataSize() const { return msize; }
    bool operator==(const String16& str) const { return str.msize == msize && std::memcmp(str.mdata, mdata, msize); }

    friend std::ostream& operator<<(std::ostream& os, const String16& obj);
    friend std::istream& operator>>(std::istream& is, String16& obj);

private:
    typedef std::basic_string<UTF16> stdStr16;

    UTF16* mdata;
    unsigned int msize;
};

} // namespace poplib

#endif // _H_POPLIB_MAP_STRING16__
