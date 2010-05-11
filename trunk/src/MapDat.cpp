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

#include <string>
#include <iostream>
#include <fstream>

#include "MapDat.h"
#include "MapLand.h"

namespace poplib
{

MapDat::MapDat()
{
    mland = new MapLand();
    mobjects = new objList();
}

MapDat::MapDat ( const std::string& fileName )
{
    mland = new MapLand();
    mobjects = new objList();
    loadMapDat ( fileName );
}

void MapDat::copy ( const MapDat& map )
{
    mland = new MapLand ( *map.mland );
    // assign memory for objects and copy them
    mobjects = new objList();
    objList::iterator it;
    for ( it = map.mobjects->begin(); it != map.mobjects->end(); ++it )
        mobjects->push_back ( *it );
}

MapDat::MapDat ( const MapDat& map )
{
    copy ( map );
}

MapDat& MapDat::operator= ( const MapDat& map )
{
    if ( this == &map )
        return *this;

    delete mland;
    cleanObjects();
    copy ( map );

    return *this;
}

MapDat::~MapDat()
{
    cleanObjects();
    delete mobjects;
    delete mland;
}

void MapDat::loadMapDat ( const std::string& fileName )
{
    cleanObjects();

    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        fin >> ( *mland );
        // TODO loading objects from the file
    }
}

void MapDat::saveMapDat ( const std::string& fileName ) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        fout << ( *mland );
        // TODO saving objects to the file
        // fill with zeros if size under 192 137 bytes
        unsigned int temp = 0;
        while ( fout.tellp() < 192137 )
            fout.write ( reinterpret_cast<const char *> ( &temp ), 1 );
    }
}

std::ostream& MapDat::toCompactForm ( std::ostream& os ) const
{
    // TODO toCompactForm() method in MapDat class
    mland->toCompactForm(os);
    // save objects size
    unsigned int temp = mobjects->size();
    os.write(reinterpret_cast<const char *>(temp), 2);
    // save objects
    objList::iterator it;
    for ( it = mobjects->begin(); it != mobjects->end(); ++it )
        ; // TODO save objects to compact form

    return os;
}

std::istream& MapDat::fromCompactForm ( std::istream& is )
{
    // TODO fromCompactForm() method in MapDat class
    cleanObjects();

    mland->fromCompactForm(is);
    // load objects size
    unsigned int temp = 0;
    is.read(reinterpret_cast<char *>(temp), 2);
    // load objects
    objList::iterator it;
    for ( it = mobjects->begin(); it != mobjects->end(); ++it )
        ; // TODO load objects from compact form

    return is;
}

void MapDat::setMapLand ( MapLand* land )
{
    delete mland;
    mland = land;
}

void MapDat::setObjects ( MapDat::objList* objects )
{
    cleanObjects();
    delete mobjects;

    mobjects = objects;
}

void MapDat::cleanObjects()
{
    // clean already loaded objects
    objList::iterator it;
    for ( it = mobjects->begin(); it != mobjects->end(); ++it )
        delete *it;
}

} // namespace poplib
