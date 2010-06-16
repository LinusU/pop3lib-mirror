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

#include "systemUtils/File.h"
#include "Map.h"

namespace poplib
{

const std::string Map::mapDatExt ( ".dat" );
const std::string Map::mapHdrExt ( ".hdr" );

Map::Map()
{

}

Map::Map ( const std::string& directory, const std::string& mapName )
{
    loadMap ( directory, mapName );
}

Map::~Map()
{

}

void  Map::loadMap ( const std::string& directory, const std::string& mapName )
{
    std::string filePath = File::path ( directory, mapName );
    if (File::fileExists(filePath + Map::mapHdrExt))
        loadHeader ( filePath + Map::mapHdrExt );

    loadMapDat ( filePath + Map::mapDatExt );
}

void  Map::saveMap ( const std::string& directory, const std::string& mapName ) const
{
    std::string filePath = File::path ( directory, mapName );
    saveHeader ( filePath + Map::mapHdrExt );
    saveMapDat ( filePath + Map::mapDatExt );
}

} // namespace poplib
