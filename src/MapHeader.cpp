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
#include <fstream>

#include "MapHeader.h"
#include <AbstractMapObj.h>

namespace poplib
{

void MapHeader::defaultValues()
{
    mmaxTribes = 3;
    // allies
    std::bitset<8> defaultAlly = std::bitset<8>();
    for ( int i = 0; i < TRIBES; ++i )
    {
        defaultAlly.set ( TRIBES - i - 1 );
        mallies[i] |= defaultAlly; // blue allied with blue, red with red etc.
        defaultAlly.reset();
    }
    // markers
    mmarkers = new MapHeader::markerList ();
}

MapHeader::MapHeader () : mproperties ( std::string ( "00001100" ) ),
        mbuildings ( std::string ( "1111111111111111" ) ), mspellsNotCharging ( std::string ( "111111111111111111111111" ) ),
        mspells(std::string ( "111111111111111111111111" ))
{
    defaultValues();
}

MapHeader::MapHeader ( const std::string& fileName ) : mproperties ( std::string ( "00001100" ) ),
        mbuildings ( std::string ( "1111111111111111" ) ), mspellsNotCharging ( std::string ( "111111111111111111111111" ) ),
        mspells(std::string ( "111111111111111111111111" ))
{
    defaultValues();
    loadHeader ( fileName );
}

void MapHeader::copy ( const MapHeader& mapHdr )
{
    mlandscape = mapHdr.mlandscape;
    mtreeStyle = mapHdr.mtreeStyle;
    mmaxTribes = mapHdr.mmaxTribes;

    mspells.reset();
    mspells |= mapHdr.mspells;
    mspellsNotCharging.reset();
    mspellsNotCharging |= mapHdr.mspellsNotCharging;
    mbuildings.reset();
    mbuildings |= mapHdr.mbuildings;
    mproperties.reset();
    mproperties |= mapHdr.mproperties;
    // allies
    for ( int i = 0; i < TRIBES; ++i )
    {
        mallies[i].reset();
        mallies[i] |= mapHdr.mallies[i];
    }
    // AI scripts
    for ( int i = 0; i < TRIBES - 1; ++i )
        maiScripts[i] = mapHdr.maiScripts[i];
    // markers
    *mmarkers = *mapHdr.mmarkers;
}

MapHeader::MapHeader ( const MapHeader& mapHdr )
{
    defaultValues();
    copy ( mapHdr );
}

MapHeader& MapHeader::operator= ( const MapHeader& mapHdr )
{
    if ( this == &mapHdr )
        return *this;

    copy ( mapHdr );

    return *this;
}

MapHeader::~MapHeader()
{
    delete mmarkers;
}

void MapHeader::loadHeader ( const std::string& fileName )
{
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        unsigned long temp = 0;
        // load enabled spells
        fin.read ( reinterpret_cast<char *> ( &temp ), 3 );
        mspells.reset();
        mspells |= std::bitset<24> ( temp ); // 0x0 - 0x2
        // load enabled buildings
        fin.seekg ( 1, std::ios_base::cur ); // skip 0x3
        temp = 0;
        fin.read ( reinterpret_cast<char *> ( &temp ), 2 );
        mbuildings.reset();
        mbuildings |= std::bitset<16> ( temp ); // 0x4 - 0x6
        // load chargable spells
        fin.seekg ( 0xf );
        temp = 0;
        fin.read ( reinterpret_cast<char *> ( &temp ), 3 ); // 0x15 - 0xa1
        mspellsNotCharging.reset();
        mspellsNotCharging |= std::bitset<24> ( temp );
        // load max tribes
        fin.seekg ( 0x58 );
        fin.read ( &mmaxTribes, 1 ); // 0x58
        // load AI scripts - they are numbers in hex for each tribe - Cpscr010.dat = 010 = 0A
        // scripts are in order for red, yellow and green
        fin.read ( &maiScripts[0], 1 ); // 0x59
        fin.read ( &maiScripts[1], 1 ); // 0x5a
        fin.read ( &maiScripts[2], 1 ); // 0x5b
        // load allies
        for ( int i = 0; i < TRIBES; ++i )
        {
            temp = 0;
            fin.read ( reinterpret_cast<char *> ( &temp ) , 1 ); // 0x5c - 0x5f
            mallies[i].reset();
            mallies[i] |= std::bitset<8> ( temp );
        }
        // load landscape
        fin.read ( reinterpret_cast<char *> ( &mlandscape ), 1 ); // 0x60
        // load tree style
        fin.read ( reinterpret_cast<char *> ( &mtreeStyle ), 1 ); // 0x61
        // load properties
        temp = 0;
        fin.read ( reinterpret_cast<char *> ( &temp ), 1 ); // 0x62
        mproperties.reset();
        mproperties |= std::bitset<8> ( temp );
        fin.seekg ( 1, std::ios_base::cur ); // skip 0x63
        // load markers
        mmarkers->clear();
        Marker m;
        for ( int i = 0; i < 256; ++i ) // markers start at 0x64
        {
            fin >> m; // 2 bytes for each marker
            mmarkers->push_back ( m );
        }
    }
    fin.close();
}

void MapHeader::saveHeader ( const std::string& fileName ) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        unsigned long temp;
        // save enabled spells
        temp = mspells.to_ulong();
        fout.write ( reinterpret_cast<const char *> ( &temp ), 3 ); // 0x0 - 0x2
        // save buildings
        temp = mbuildings.to_ulong();
        fout.seekp ( 1, std::ios_base::cur ); // skip 0x3
        fout.write ( reinterpret_cast<const char *> ( &temp ), 2 ); // 0x4 - 0x6
        // save chargable spells
        temp = mspellsNotCharging.to_ulong();
        fout.seekp ( 0xf );
        fout.write ( reinterpret_cast<const char *> ( &temp ), 3 ); // 0x15 - 0xa1
        // save max tribes
        fout.seekp ( 0x58 );
        fout.write ( &mmaxTribes, 1 ); // 0x58
        // save AI scripts - they are numbers in hex for each tribe - Cpscr010.dat = 010 = 0A
        // scripts are in order for red, yellow and green
        fout.write ( &maiScripts[0], 1 ); // 0x59
        fout.write ( &maiScripts[1], 1 ); // 0x5b
        fout.write ( &maiScripts[2], 1 ); // 0x5c
        // save allies
        for ( int i = 0; i < TRIBES; ++i )
        {
            temp = mallies[i].to_ulong(); // 0x5c - 0x5f
            fout.write ( reinterpret_cast<const char *> ( &temp ) , 1 );
        }
        // save landscape
        fout.write ( reinterpret_cast<const char *> ( &mlandscape ), 1 ); // 0x60
        // save tree style
        fout.write ( reinterpret_cast<const char *> ( &mtreeStyle ), 1 ); // 0x61
        // save properties
        temp = mproperties.to_ulong();
        fout.write ( reinterpret_cast<const char*> ( &temp ), 1 ); // 0x62
        // save markers
        fout.seekp ( 1, std::ios_base::cur ); // skip 0x63
        for ( markerList::iterator it = mmarkers->begin(); it != mmarkers->end(); ++it )
            fout << *it; // 2 bytes for each marker
        // header file has to have at least 616 bytes, fill with zeros if size under 616 bytes
        int zerosSize = 616 - fout.tellp();
        if (zerosSize > 0)
        {
            char* zeros = new char[zerosSize];
            fout.write ( zeros , zerosSize );
            delete[] zeros;
        }
    }
    fout.close();
}

std::ostream&  MapHeader::saveHeaderCompactForm ( std::ostream& os ) const
{
    unsigned long temp;
    // save enabled spells
    temp = mspells.to_ulong();
    os.write ( reinterpret_cast<const char *> ( &temp ), 3 );
    // save buildings
    temp = mbuildings.to_ulong();
    os.write ( reinterpret_cast<const char *> ( &temp ), 2 );
    // save chargable spells
    temp = mspellsNotCharging.to_ulong();
    os.write ( reinterpret_cast<const char *> ( &temp ), 3 );
    // save max tribes
    os.write ( &mmaxTribes, 1 );
    // save AI scripts - they are numbers in hex for each tribe - Cpscr010.dat = 010 = 0A
    // scripts are in order for red, yellow and green
    os.write ( &maiScripts[0], 1 );
    os.write ( &maiScripts[1], 1 );
    os.write ( &maiScripts[2], 1 );
    // save allies
    for ( int i = 0; i < TRIBES; ++i )
    {
        temp = mallies[i].to_ulong();
        os.write ( reinterpret_cast<const char *> ( &temp ) , 1 );
    }
    // save landscape
    os.write ( reinterpret_cast<const char *> ( &mlandscape ), 1 );
    // save tree style
    os.write ( reinterpret_cast<const char *> ( &mtreeStyle ), 1 );
    // save properties
    temp = mproperties.to_ulong();
    os.write ( reinterpret_cast<const char*> ( &temp ), 1 );
    // save markers
    temp = 0;
    os.seekp ( 1, std::ios_base::cur ); // make a place for a size, we don't know it yet
    for ( markerList::iterator it = mmarkers->begin(); it != mmarkers->end(); ++it )
    {
        if ((*it).isNull() == false)
        {
            os << *it; // 2 bytes for each marker
            temp++;
        }
    }
    int markersSize = temp * 2;
    os.seekp ( -(markersSize + 1), std::ios_base::cur ); // move back to save markers size
    os.write ( reinterpret_cast<const char*> ( &temp ), 1 );
    os.seekp(markersSize, std::ios_base::cur);// skip saved markers
    return os;
}

std::istream&  MapHeader::loadHeaderCompactForm ( std::istream& is )
{
    unsigned long temp = 0;
    // load enabled spells
    is.read ( reinterpret_cast<char *> ( &temp ), 3 );
    mspells.reset();
    mspells |= std::bitset<24> ( temp );
    // load enabled buildings
    temp = 0;
    is.read ( reinterpret_cast<char *> ( &temp ), 2 );
    mbuildings.reset();
    mbuildings |= std::bitset<16> ( temp );
    // load chargable spells
    temp = 0;
    is.read ( reinterpret_cast<char *> ( &temp ), 3 );
    mspellsNotCharging.reset();
    mspellsNotCharging |= std::bitset<24> ( temp );
    // load max tribes
    is.read ( &mmaxTribes, 1 );
    // load AI scripts - they are numbers in hex for each tribe - Cpscr010.dat = 010 = 0A
    // scripts are in order for red, yellow and green
    is.read ( &maiScripts[0], 1 );
    is.read ( &maiScripts[1], 1 );
    is.read ( &maiScripts[2], 1 );
    // load allies
    for ( int i = 0; i < TRIBES; ++i )
    {
        temp = 0;
        is.read ( reinterpret_cast<char *> ( &temp ) , 1 );
        mallies[i].reset();
        mallies[i] |= std::bitset<8> ( temp );
    }
    // load landscape
    is.read ( reinterpret_cast<char *> ( &mlandscape ), 1 );
    // load tree style
    is.read ( reinterpret_cast<char *> ( &mtreeStyle ), 1 );
    // load properties
    temp = 0;
    is.read ( reinterpret_cast<char *> ( &temp ), 1 );
    mproperties.reset();
    mproperties |= std::bitset<8> ( temp );
    // load markers
    mmarkers->clear();
    Marker m;
    temp = 0;
    is.read ( reinterpret_cast<char *> ( &temp ), 1 ); // read markes amount
    for ( unsigned int i = 0; i < temp; ++i )
    {
        is >> m; // 2 bytes for each marker
        mmarkers->push_back ( m );
    }

    return is;
}

void MapHeader::setAllCharging(bool charge)
{
    // TODO setAllCharging() method in MapHeader class
}

void MapHeader::setAlly ( MapHeader::Tribe tribe, MapHeader::Allies ally )
{
    std::bitset<8> bally ( static_cast<unsigned long> ( ally ) ); // bitmask representation of the allies
    mallies[tribe].reset();
    mallies[tribe] |= bally;
}

bool MapHeader::isAllied ( MapHeader::Tribe tribe, MapHeader::Allies ally )
{
    std::bitset<8> bitAlly ( static_cast<unsigned long> ( ally ) ); // bitmask representation of the allies
    std::bitset<8> temp ( mallies[tribe].to_ulong() ); // make copy of the original allies
    temp &= bitAlly;

    return temp.any();
}

void MapHeader::resetAllies()
{
    // TODO resetAllies() method in MapHeader class
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
