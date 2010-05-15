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

#include <fstream>

#include "MappackMap.h"

namespace poplib
{

MappackMap::MappackMap()
{

}

MappackMap::MappackMap(const std::string& filename)
{

}

MappackMap::MappackMap ( const std::string& directory, const std::string& mapName ) : Map(directory, mapName)
{

}

void MappackMap::saveExtended(const std::string& fileName) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        fout.write ( reinterpret_cast<const char *> ( &magicNumber ), 2 );
        fout << (*this);
    }
}

void MappackMap::loadExtended(const std::string& fileName)
{
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        unsigned int temp = 0;
        fin.read(reinterpret_cast<char *>(temp), 2);
        if (temp != magicNumber)
            return;

        fin >> (*this);
    }
}

std::ostream& operator<<(std::ostream& os, const MappackMap& obj)
{
    // TODO MappackMap class saving
    obj.saveHeaderCompactForm(os);
    obj.saveMapDatCompactForm(os);

    return os;
}

std::istream& operator>>(std::istream& is, MappackMap& obj)
{
    // TODO MappackMap class loading
    obj.loadHeaderCompactForm(is);
    obj.loadMapDatCompactForm(is);

    return is;
}

} // namespace poplib
