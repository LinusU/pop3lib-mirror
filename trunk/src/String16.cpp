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
    UTF16 init = 0;
    mdata = stdStr16(&init);
}

String16::String16(UTF32* str)
{
    // TODO string16 constructing from UTF16
}

String16::String16(UTF16* str): mdata(str)
{

}

String16::String16(UTF8* str)
{
    // TODO string16 constructing from UTF8
}

std::ostream& operator<<(std::ostream& os, const String16& obj)
{
    os.write(reinterpret_cast<const char *>(obj.data16()), obj.dataSize());
}

std::istream& operator>>(std::istream& is, String16& obj)
{
    UTF16 c;
    while (true)
    {
        is.read(reinterpret_cast<char *>(&c), sizeof(UTF16));
        obj.mdata += c;
        if (c == 0)
            break;
    }
}

} // namespace poplib
