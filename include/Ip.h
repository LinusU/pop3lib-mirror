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

#ifndef _H_POPLIB_IP__
#define _H_POPLIB_IP__

#include <string>

namespace poplib
{

class Ip
{
public:
    Ip();
    Ip ( int p1, int p2, int p3, int p4 );
    Ip ( const std::string& sip );
    Ip ( const Ip& ip );
    Ip& operator= ( const Ip& ip );

    void setIp ( int p1, int p2, int p3, int p4 );
    void setIp ( const std::string& sip );

    std::string str() const { return *msip; }
    bool isValid() const
    {
        return mp1 > -1 && mp1 < 256 && mp2 > -1 && mp2 < 256 && mp3 > -1 && mp3 < 256 && mp4 > -1 && mp4 < 256;
    }

private:
    std::string* msip;
    int mp1, mp2, mp3, mp4;
};

} // namespace poplib

#endif // _H_POPLIB_IP__
