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

#ifndef _H_POPLIB_MAPPACKMAP__
#define _H_POPLIB_MAPPACKMAP__

#include <string>

#include "bits/mapBits.h"
#include "Map.h"

namespace poplib
{

class MappackMap : public Map
{
public:
    typedef _Teams Teams;

    // TODO add more things to MappackMap class
    MappackMap();
    explicit MappackMap(const std::string& fileName);
    MappackMap(const std::string& directory, const std::string& mapName);

    void saveExtended(const std::string& fileName) const;
    void loadExtended(const std::string& fileName);

    friend std::ostream& operator<<(std::ostream& os, const MappackMap& obj);
    friend std::istream& operator>>(std::istream& is, MappackMap& obj);

private:
    static const unsigned short magicNumber = 10611;
};

} // namespace poplib

#endif // _H_POPLIB_MAPPACKMAP__
