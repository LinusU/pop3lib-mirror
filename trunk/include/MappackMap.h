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

#include "MapDat.h"
#include "MapHeader.h"

namespace poplib
{

class MappackMap : public MapDat, public MapHeader
{
public:
    MappackMap();

    friend std::ostream& operator<<(std::ostream& os, const MappackMap& obj) { return obj.toCompactForm(os); }
    friend std::istream& operator>>(std::istream& is, MappackMap& obj) { return obj.fromCompactForm(is); }

	protected:
    virtual std::ostream& toCompactForm ( std::ostream& os ) const;
    virtual std::istream& fromCompactForm ( std::istream& is );

private:
    void loadHeader ( const std::string& fileName );
    void saveHeader ( const std::string& fileName ) const;
    void loadMapDat ( const std::string& fileName );
    void saveMapDat ( const std::string& fileName ) const;

};

} // namespace poplib

#endif // _H_POPLIB_MAPPACKMAP__
