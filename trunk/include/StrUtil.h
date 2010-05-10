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

#ifndef _H_STRUTIL__
#define _H_STRUTIL__

#include <string>
#include <list>
#include <sstream>

namespace poplib
{

class StrUtil
{
public:
    static std::string constrPatch ( const std::string& directory, const std::string& fileName );
    static std::list<std::string> split ( const std::string& str, char sep );

    template<class T>
    static std::string toString ( const T& t )
    {
        std::ostringstream stream;
        stream << t;
        return stream.str();
    }

    template<class T>
    static T fromString ( const std::string& s )
    {
        std::istringstream stream ( s );
        T t;
        stream >> t;
        return t;
    }
};

} // namespace poplib

#endif // _H_STRUTIL__
