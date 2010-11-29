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

#ifndef _H_POPLIB_MAPDAT__
#define _H_POPLIB_MAPDAT__

#include <list>

#include "MapLand.h"

namespace poplib
{
class MapObjGeneric;

/** Represents file mapName.dat. Loads / saves map land and objects on the map. */
class MapDat
{
public:
   typedef std::list<MapObjGeneric *> objList;
    /** Constructor. */
    MapDat();
    /** Constructor. Loades map land and objects from the file.  */
    explicit MapDat ( const std::string& fileName );
    /** Copy constructor. */
    MapDat ( const MapDat& map );
    MapDat& operator= ( const MapDat& map );
    virtual ~MapDat();
    /** Loads map land and objects from the file.
    @param fileName Path to the file where map details are stored. It usualy has *.dat extension.
    */
    void loadMapDat ( const std::string& fileName );
    /** Saves map land and objects to the file.
    @param fileName Path to the file where map details should be stored. It should have *.dat extension.
    */
    void saveMapDat ( const std::string& fileName ) const;
    /** Saves map dat details using compact form. Suitable for sending maps over the internet. */
    std::ostream& saveMapDatCompactForm ( std::ostream& os ) const;
    /** Loades map header details from compact form. */
    std::istream& loadMapDatCompactForm ( std::istream& is );
    /** Returns the land heights. */
    MapLand* mapLand() const
    {
        return mland;
    }
    /** Sets the land heights for the map.  */
    void setMapLand ( MapLand* land );
    /** Returns list of the objects on the map. */
    objList* objects() const
    {
        return mobjects;
    }
    /** Sets new list of the objects on the map.  */
    void setObjects ( objList* objects );

private:
    objList* mobjects;
    MapLand* mland;

    void copy(const MapDat& map);
    std::istream& loadObjects(std::istream& is);
    void cleanObjects();
};

} // namespace poplib

#endif // _H_POPLIB_MAPDAT__
