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

#ifndef _H_POPLIB_MAP__
#define _H_POPLIB_MAP__

#include <string>

#include "MapDat.h"
#include "MapHeader.h"

namespace poplib
{
/** Maps in populous are combined with lvlname.dat file which contains map land and objects, 
and lvlname.hdr file which contains informations about allies, available spells and other
map properties. This class represents those two files and is recommended to manipulate maps. */
class Map : public MapDat, public MapHeader
{
public:
    /** Constructor. */
    Map();
    /** Constructor. Loads map details from files.
    @param directory Directory, where maps are stored.
    @param mapName Name of the files where map is stored. Map files must follow convention:
    mapName.dat, mapName.hdr.
    */
    Map ( const std::string& directory, const std::string& mapName );
    Map& operator= ( const Map& map );
    virtual ~Map();
    /** Loads map details from populous map files.
    @param directory Directory, where map files are stored.
    @param mapName Name of files (without extension) where map is stored. Map files must follow convention:
    mapName.dat, mapName.hdr.
    */
    void load ( const std::string& directory, const std::string& mapName );
    /** Saves map details to files using populous map format.
    @param directory Directory, where map files are stored.
    @param mapName Name of the files where map is stored. Map files follow convention:
    mapName.dat for land and mapName.hdr for header.
    */
    void save ( const std::string& directory, const std::string& mapName ) const;

protected:
    std::ostream& saveHeaderCompactForm ( std::ostream& os ) const { return MapHeader::saveHeaderCompactForm(os); }
    std::istream& loadHeaderCompactForm ( std::istream& is ) { return MapHeader::loadHeaderCompactForm(is); }
    std::ostream& saveMapDatCompactForm ( std::ostream& os ) const { return MapDat::saveMapDatCompactForm(os); }
    std::istream& loadMapDatCompactForm ( std::istream& is ) { return MapDat::loadMapDatCompactForm(is); }

private:
    static const std::string mapDatExt, mapHdrExt;
};

} // namespace poplib

#endif // _H_POPLIB_MAP__
