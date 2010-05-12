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
    /** Copy constructor */
    Map ( const Map& map );
    Map& operator= ( const Map& map );
    virtual ~Map();
    /** Loads map details from files.
    @param directory Directory, where map files are stored.
    @param mapName Name of files (without extension) where map is stored. Map files must follow convention:
    mapName.dat, mapName.hdr.
    */
    void load ( const std::string& directory, const std::string& mapName );
    /** Saves opened map files. */
    void save() const;
    /** Saves map details to files.
    @param directory Directory, where map files are stored.
    @param mapName Name of the files where map is stored. Map files follow convention:
    mapName.dat for land and mapName.hdr for header.
    */
    void save ( const std::string& directory, const std::string& mapName ) const;
    /** Returns path to the directory where map files are stored. */
    std::string mapDirectory() const { return mdirectory; }
    /** Returns file name (without extension) of loaded or saved maps. Map files follow convention: mapName.dat for land
    and mapName.hdr for header. */
    const std::string mapName() const { return mmapName; }
    
private:
    virtual std::ostream& toCompactForm ( std::ostream& os ) const;
    virtual std::istream& fromCompactForm ( std::istream& is );

private:
    static const std::string mapDatExt, mapHdrExt;
    std::string mdirectory, mmapName;
};

} // namespace poplib

#endif // _H_POPLIB_MAP__
