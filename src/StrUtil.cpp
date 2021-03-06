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

#include "global.h"
#include "StrUtil.h"

namespace poplib
{

std::list<std::string> StrUtil::split ( const std::string& str, char sep )
{
    std::list<std::string> stringList;
    int pos = 0;
    for ( unsigned int i = 0; i < str.length(); ++i )
    {
        if ( str.at ( i ) == sep )
        {
            stringList.push_back ( str.substr ( pos, i - pos ) );
            pos = i;
        }
    }
    stringList.push_back ( str.substr ( pos, str.length() ) );

    return stringList;
}

} // namespace poplib
