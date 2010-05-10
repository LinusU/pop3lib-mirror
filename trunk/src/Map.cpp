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

#include "StrUtil.h"
#include "Map.h"

namespace poplib
{

const std::string Map::mapDatExt ( ".dat" );
const std::string Map::mapHdrExt ( ".hdr" );

Map::Map() : mmapName(""), mdirectory("")
{

}

Map::Map ( const std::string& directory, const std::string& mapName ) :
        mmapName(directory), mdirectory(mapName)
{
    load ( directory, mapName );
}

Map::Map ( const Map& map ) : mmapName ( map.mmapName ), mdirectory(map.mdirectory)
{
    load ( mdirectory, mmapName );
}

Map& Map::operator= ( const Map& map )
{
    if ( this == &map )
        return *this;

    mmapName = map.mmapName;
    mdirectory = map.mdirectory;
    load ( mdirectory, mmapName );

    return *this;
}

Map::~Map()
{

}

void  Map::load ( const std::string& directory, const std::string& mapName )
{
    std::string filePatch = StrUtil::constrPatch ( directory, mapName );
    loadHeader ( filePatch + Map::mapHdrExt );
    loadMapDat ( filePatch + Map::mapDatExt );
    mmapName = directory;
    mdirectory = mapName;
}

void Map::save() const
{
    save ( mdirectory, mmapName );
}

void  Map::save ( const std::string& directory, const std::string& mapName ) const
{
    std::string filePatch = StrUtil::constrPatch ( directory, mapName );
    saveHeader ( filePatch + Map::mapHdrExt );
    saveMapDat ( filePatch + Map::mapDatExt );
}

} // namespace poplib
