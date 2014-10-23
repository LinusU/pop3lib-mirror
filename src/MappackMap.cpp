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
    
String16 MappackMap::statusStr(Status st)
{
    switch(st)
    {
        case ALPHA:
            return String16("ALPHA");
        case BETA:
            return String16("BETA");
        case STABLE:
            return String16("STABLE");
        case MATURE:
            return String16("MATURE");
        default:
            return String16("BAD_STATUS");
    }
}

MappackMap::MappackMap(): mpossTeams(std::string("11111111")), mdefTeams(std::string("11111111")),
    mstatus(ALPHA)
{

}

MappackMap::MappackMap(const std::string& filename):  mpossTeams(std::string("11111111")), mdefTeams(std::string("11111111")),
    mstatus(ALPHA)
{
    loadMappack(filename);
}

MappackMap::MappackMap ( const std::string& directory, const std::string& mapName ) :
        Map(directory, mapName), mpossTeams(std::string("11111111")),
        mdefTeams(std::string("11111111")), mstatus(ALPHA)
{

}

MappackMap::MappackMap ( const MappackMap& map ) : Map(), mpossTeams(static_cast<int>(map.mpossTeams.to_ulong())),
        mdefTeams(static_cast<int>(map.mdefTeams.to_ulong())), mname(map.mname), mdescr(map.mdescr), mstatus(map.mstatus)
{
    copyAuthors(map);
}

MappackMap& MappackMap::operator= ( const MappackMap& map )
{
    mpossTeams = map.mpossTeams;
    mdefTeams = map.mdefTeams;
    mname = map.mname;
    mdescr = map.mdescr;
    clearAuthors();
    copyAuthors(map);
	return *this;
}

MappackMap::~MappackMap()
{
    clearAuthors();
}

void MappackMap::saveMappack(const std::string& fileName) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        unsigned int temp = magicNumber;
        fout.write ( reinterpret_cast<const char *> ( &temp ), 2 );

        fout << (*this);
    }
    fout.close();
}

void MappackMap::loadMappack(const std::string& fileName)
{
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        unsigned int temp = 0;
        fin.read(reinterpret_cast<char *>(&temp), 2);
        if (temp != magicNumber)
            return;

        fin >> (*this);
    }
    fin.close();
}

void MappackMap::setPossibleTeams(poplib::MappackMap::Teams teams, bool enabled)
{
    std::bitset<8> bteams(static_cast<int>(teams)); // bitmask representation of teams
    if (enabled)
    {
        mpossTeams |= bteams;
    }
    else
    {
        bteams = bteams.flip();
        mpossTeams &= bteams;
    }
}

bool MappackMap::isPossibleTeam(Teams team) const
{
    return isSet(mpossTeams, team);
}

void MappackMap::setDefaultTeams(poplib::MappackMap::Teams teams, bool enabled)
{
    std::bitset<8> bteams(static_cast<int>(teams)); // bitmask representation of teams
    if (enabled)
    {
        mdefTeams |= bteams;
    }
    else
    {
        bteams = bteams.flip();
        mdefTeams &= bteams;
    }
}

bool MappackMap::isDefaultTeam(Teams team) const
{
    return isSet(mdefTeams, team);
}

String16 MappackMap::possibleTeams(const std::string& sep) const
{
    return teamsStr(mpossTeams, sep);
}

String16 MappackMap::defaultTeams(const std::string& sep) const
{
    return teamsStr(mdefTeams, sep);
}

void MappackMap::removeAuthor(const String16& author)
{
    std::list<String16 *>::iterator it;
    for (it = mauthors.begin(); it != mauthors.end(); ++it)
    {
        if (author == **it)
        {
            mauthors.erase(it);
            delete *it;
            return;
        }
    }
}

void MappackMap::setAuthors(const std::list<String16 *>& authors)
{
    clearAuthors();

    mauthors = authors;
}

std::ostream& operator<<(std::ostream& os, const MappackMap& obj)
{
    unsigned int temp = obj.mpossTeams.to_ulong();
    os.write(reinterpret_cast<char *>(&temp), 1);
    temp = obj.mdefTeams.to_ulong();
    os.write(reinterpret_cast<char *>(&temp), 1);
    os.write(reinterpret_cast<const char *>(&obj.mstatus), 1);

    os << obj.mname << obj.mdescr;

    temp = obj.mauthors.size();
    os.write(reinterpret_cast<char *>(&temp), 1);
    std::list<String16 *>::const_iterator it;
    for (it = obj.mauthors.begin(); it != obj.mauthors.end(); ++it)
        os << **it;

    obj.saveHeaderCompactForm(os);
    obj.saveMapDatCompactForm(os);

    return os;
}

std::istream& operator>>(std::istream& is, MappackMap& obj)
{
    obj.clearAuthors();

    unsigned int temp = 0;
    is.read(reinterpret_cast<char *>(&temp), 1);
    obj.mpossTeams = std::bitset<8>(static_cast<int>(temp));
    temp = 0;
    is.read(reinterpret_cast<char *>(&temp), 1);
    obj.mdefTeams = std::bitset<8>(static_cast<int>(temp));
    is.read(reinterpret_cast<char *>(&obj.mstatus), 1);

    is >> obj.mname >> obj.mdescr;

    temp = 0;
    is.read(reinterpret_cast<char *>(&temp), 1);
    for (unsigned int i = 0; i < temp; ++i)
    {
        String16* str = new String16();
        is >> *str;
        obj.mauthors.push_back(str);
    }

    obj.loadHeaderCompactForm(is);
    obj.loadMapDatCompactForm(is);

    return is;
}

void MappackMap::clearAuthors()
{
    std::list<String16 *>::iterator it;
    for (it = mauthors.begin(); it != mauthors.end(); ++it)
        delete *it;
}

void MappackMap::copyAuthors(const MappackMap& map)
{
    std::list<String16 *>::const_iterator it;
    for (it = map.mauthors.begin(); it != map.mauthors.end(); ++it)
        mauthors.push_back(new String16(**it));
}

bool MappackMap::isSet(std::bitset<8> team, Teams toTest) const
{
    std::bitset<8> bteam(static_cast<int>(toTest)); // bitmask representation of teams
    team &= bteam;
    return team.any();
}

String16 MappackMap::teamsStr(std::bitset<8> tms, const std::string& sep) const
{
    std::string tmsStr = "";
    if(isSet(tms, IVO))
    {
        appendSep(tmsStr, sep);
        tmsStr += "IVO";
    }
    
    if(isSet(tms, EVO))
    {
        appendSep(tmsStr, sep);
        tmsStr += "EVO";
    }
    
    if(isSet(tms, TVB))
    {
        appendSep(tmsStr, sep);
        tmsStr += "TVB";
    }
    
    if(isSet(tms, FFA))
    {
        appendSep(tmsStr, sep);
        tmsStr += "FFA";
    }
    
    if(isSet(tms, THREE_WAY))
    {
        appendSep(tmsStr, sep);
        tmsStr += "THREE_WAY";
    }
    
    if(isSet(tms, TWO_WAY))
    {
        appendSep(tmsStr, sep);
        tmsStr += "TWO_WAY";
    }
    
    return String16(tmsStr.c_str());
}

void MappackMap::appendSep(std::string& str, const std::string& sep) const
{
    str += (str.empty() ? "" : sep);
}

} // namespace poplib