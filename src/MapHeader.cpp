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

#include <cstring>
#include <fstream>

#include "MapHeader.h"

namespace poplib
{

MapHeader::MapHeader ()
{
    memset(&mdata, 0, sizeof(mdata));
    resetAllies();
}

MapHeader::MapHeader ( const std::string& fileName )
{
    loadHeader ( fileName );
}

MapHeader::~MapHeader()
{

}

void MapHeader::loadHeader ( const std::string& fileName )
{
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        memset(&mdata, 0, sizeof(mdata));
        fin.read(reinterpret_cast<char *>(&mdata), sizeof(mdata));
    }
    fin.close();
}

void MapHeader::saveHeader ( const std::string& fileName ) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        fout.write(reinterpret_cast<const char *>(&mdata), sizeof(mdata));
    }
    fout.close();
}

std::ostream&  MapHeader::saveHeaderCompactForm ( std::ostream& os ) const
{
    // save enabled spells and buildings
    os.write ( reinterpret_cast<const char *> ( &mdata ), sizeof(mdata.spellsAvailable) + sizeof(mdata.buildingsAvailable) );
    // save spells which are not charging at the beginning of the game
    os.write ( reinterpret_cast<const char *> ( &mdata.spellsNotCharging ), sizeof(mdata.spellsNotCharging) );
    // save max tribes
    os.write ( reinterpret_cast<const char *> (&mdata.maxTribes), sizeof(mdata.maxTribes) );
    // save landscape and tree style
    os.write ( reinterpret_cast<const char *> (&mdata.landscape), sizeof(mdata.landscape) + sizeof(mdata.treeStyle) );

    return os;
}

std::istream&  MapHeader::loadHeaderCompactForm ( std::istream& is )
{
    memset(&mdata, 0, sizeof(mdata));
    resetAllies();
    // load enabled spells and buildings
    is.read( reinterpret_cast<char *> ( &mdata ), sizeof(mdata.spellsAvailable) + sizeof(mdata.buildingsAvailable) );
    // load spells which are not charging at the beginning of the game
    is.read( reinterpret_cast<char *> ( &mdata.spellsNotCharging ), sizeof(mdata.spellsNotCharging) );
    // load max tribes
    is.read ( reinterpret_cast<char *> (&mdata.maxTribes), sizeof(mdata.maxTribes) );
    // load landscape and tree style
    is.read ( reinterpret_cast<char *> (&mdata.landscape), sizeof(mdata.landscape) + sizeof(mdata.treeStyle) );

    return is;
}

void MapHeader::setAllCharging(bool charge)
{
    if(charge)
      mdata.spellsNotCharging = 0;
    else
      mdata.spellsNotCharging = 0xffffffff;
}

void MapHeader::resetAllies()
{
    for ( int i = 0; i < MapHeader::NUMB_OF_TRIBES; ++i )
        mdata.allies[i] = (mdata.allies[i] & 0) | (0x00000001 << i); // blue allied with blue, red with red etc.
}

void MapHeader::setEnabledAllSpells(bool enabled)
{
    // TODO setEnabledAllSpells() method in MapHeader class
}

void MapHeader::setEnabledAllBuildings(bool enabled)
{
    // TODO setEnabledAllBuildings() method in MapHeader class
}

void MapHeader::setEnabledAllProperties(bool enabled)
{
    // TODO setEnabledAllProperties() method in MapHeader class
}

void MapHeader::setStandardSpells()
{
    // TODO setStandardSpells() method in MapHeader class
}

void MapHeader::setStandardBuildings()
{
    // TODO setStandardBuildings() method in MapHeader class
}

} // namespace poplib
