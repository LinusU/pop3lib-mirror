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

#include <sstream>

#include "Ip.h"
#include "StrUtil.h"

namespace poplib
{

Ip::Ip ( )
{
    setIp ( 0, 0, 0, 0 );
}

Ip::Ip ( int p1, int p2, int p3, int p4 )
{
    setIp ( p1,  p2,  p3,  p4 );
}

Ip::Ip ( const std::string& sip )
{
    setIp ( sip );
}

Ip::Ip ( const Ip& ip )
{
    msip = new std::string ( *ip.msip );
    mp1 = ip.mp1;
    mp2 = ip.mp2;
    mp3 = ip.mp3;
    mp4 = ip.mp4;
}

Ip& Ip::operator= ( const Ip& ip )
{
    *msip = *ip.msip;
    mp1 = ip.mp1;
    mp2 = ip.mp2;
    mp3 = ip.mp3;
    mp4 = ip.mp4;
	return *this;
}

void Ip::setIp ( int p1, int p2, int p3, int p4 )
{
    mp1 = p1;
    mp2 = p2;
    mp3 = p3;
    mp4 = p4;

    std::ostringstream stream;
    stream << mp1 << "." << mp2 << "." << mp3 << "." << mp4;
    *msip = stream.str();
}

void Ip::setIp ( const std::string& sip )
{
    *msip = sip;
    std::list<std::string> strList = StrUtil::split ( sip, '.' );
    if ( strList.size() != 4 )
    {
        mp1 = -1;
    }
    else
    {
        mp1 = StrUtil::fromString<int> ( strList.front() );
        strList.pop_front();
        mp2 = StrUtil::fromString<int> ( strList.front() );
        strList.pop_front();
        mp3 = StrUtil::fromString<int> ( strList.front() );
        strList.pop_front();
        mp4 = StrUtil::fromString<int> ( strList.front() );
    }
}

} // namespace poplib
