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
#include "systemUtils/File.h"

namespace poplib
{

Mappack::Mappack()
{

}

Mappack::Mappack ( const std::string& fileName )
{
    loadFromFile ( fileName );
}

Mappack::Mappack ( const Mappack& mappack )
{
    copyMaps(mappack);
}

Mappack& Mappack::operator= ( const Mappack& mappack )
{
    cleanMaps();
    copyMaps(mappack);
}

Mappack::~Mappack()
{
    cleanMaps();
}

void Mappack::loadFromFile ( const std::string& fileName )
{
    mmaps.clear();
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        unsigned int temp = 0;
        fin.read ( reinterpret_cast<char *> ( &temp ), 2 );
        if ( temp != magicNumber )
            return;

        temp = 0;
        MappackMap* m;
        fin.read ( reinterpret_cast<char *> ( &temp ), 1 );
        for ( int i = 0; i < temp; ++i )
        {
            m = new MappackMap();
            fin >> *m;
            mmaps.push_back ( m );
        }
    }
    fin.close();
}

void Mappack::loadFromDirectory ( const std::string& dir )
{
    mmaps.clear();

    std::list<std::string> files = Dir::listFiles ( dir );
    MappackMap* m;
    std::list<std::string>::iterator it;
    std::string t;
    for ( it = files.begin(); it != files.end(); ++it )
    {
        t = File::fileExtension ( *it );
        if ( File::fileExtension ( *it ) == "dat" )
        {
            m = new MappackMap ( dir, File::fileName ( *it ) );
            mmaps.push_back ( m );
        }
    }
}

void Mappack::saveToFile ( const std::string& fileName ) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        unsigned int temp = magicNumber;
        fout.write ( reinterpret_cast<const char *> ( &temp ), 2 );
        temp = mmaps.size();
        fout.write ( reinterpret_cast<const char *> ( &temp ), 1 );
        std::list<MappackMap *>::const_iterator it;
        for ( it = mmaps.begin(); it != mmaps.end(); ++it )
            fout << ( **it );
    }
    fout.close();
}

void Mappack::removeMap(MappackMap* map)
{
    std::list<MappackMap *>::iterator it;
    for ( it = mmaps.begin(); it != mmaps.end(); ++it )
    {
        if (map == *it)
        {
            mmaps.erase(it);
            delete *it;
            return;
        }
    }

}

void Mappack::cleanMaps()
{
    std::list<MappackMap *>::const_iterator it;
    for ( it = mmaps.begin(); it != mmaps.end(); ++it )
        delete *it;
}

void Mappack::copyMaps(const Mappack& mappack)
{
    std::list<MappackMap *>::const_iterator it;
    for ( it = mappack.mmaps.begin(); it != mappack.mmaps.end(); ++it )
        mmaps.push_back(new MappackMap(**it));
}

} // namespace poplib
