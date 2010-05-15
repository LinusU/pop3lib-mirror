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

#include "Mappack.h"
#include "systemUtils/Dir.h"

namespace poplib
{

Mappack::Mappack()
{

}

Mappack::Mappack(const std::string& fileName)
{
    loadFromFile(fileName);
}

void Mappack::loadFromFile(const std::string& fileName)
{
    mmaps.clear();
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        unsigned int temp = 0;
        fin.read(reinterpret_cast<char *>(temp), 2);
        if (temp != magicNumber)
            return;

        temp = 0;
        MappackMap m;
        fin.read(reinterpret_cast<char *>(temp), 4);
        for (int i = 0; i < temp; ++i)
        {
            fin >> m;
            mmaps.push_back(m);
        }
    }
}

void Mappack::loadFromDirectory(const std::string& dir)
{
    mmaps.clear();

    std::list<std::string> files = Dir::listFiles(dir);
    MappackMap m;
    std::list<std::string>::iterator it;
    for (it = files.begin(); it != files.end(); ++it)
    {
        m = MappackMap(dir, *it);
        mmaps.push_back(m);
    }
}

void Mappack::saveToFile(const std::string& fileName) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        fout.write ( reinterpret_cast<const char *> ( &magicNumber ), 2);
        unsigned int temp = mmaps.size();
        fout.write ( reinterpret_cast<const char *> ( &temp ), 4 );
        std::list<MappackMap>::const_iterator it;
        for (it = mmaps.begin(); it != mmaps.end(); ++it)
            fout << (*it);
    }
}

} // namespace poplib
