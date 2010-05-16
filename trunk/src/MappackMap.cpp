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
    loadExtended(filename);
}

MappackMap::MappackMap ( const std::string& directory, const std::string& mapName ) :
        Map(directory, mapName)
{

}

MappackMap::~MappackMap()
{
    clearAuthors();
}

void MappackMap::saveExtended(const std::string& fileName) const
{
    std::ofstream fout;
    fout.open ( fileName.c_str(), std::ios_base::out | std::ios_base::binary );
    if ( fout.is_open() )
    {
        fout << (*this);
    }
}

void MappackMap::loadExtended(const std::string& fileName)
{
    std::ifstream fin;
    fin.open ( fileName.c_str(), std::ios_base::in | std::ios_base::binary );
    if ( fin.is_open() )
    {
        fin >> (*this);
    }
}

void MappackMap::setPossibleTeams(Teams teams)
{
    std::bitset<8> bteams(static_cast<unsigned long>(teams)); // bitmask representation of teams
    mpossTeams.reset();
    mpossTeams |= bteams;
}

bool MappackMap::isPossibleTeam(Teams team) const
{
    std::bitset<8> bteam(static_cast<unsigned long>(team)); // bitmask representation of teams
    std::bitset<8> temp = mpossTeams; // make copy of the original teams
    temp &= bteam;
    return temp.any();
}

void MappackMap::setDefaultTeams(Teams teams)
{
    std::bitset<8> bteams(static_cast<unsigned long>(teams)); // bitmask representation of teams
    mdefTeams.reset();
    mdefTeams |= bteams;
}

bool MappackMap::isDefaultTeam(Teams team) const
{
    std::bitset<8> teams(static_cast<unsigned long>(team)); // bitmask representation of teams
    std::bitset<8> temp = mdefTeams; // make copy of the original teams
    temp &= teams;
    return temp.any();
}

void MappackMap::removeAuthor(const String16& author)
{
    std::list<String16 *>::iterator it;
    for (it = mauthors.begin(); it != mauthors.end(); ++it)
    {
        if (author == **it)
        {
            mauthors.erase(it);
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
    os.write ( reinterpret_cast<const char *> ( &obj.magicNumber ), 2 );

    unsigned int temp = obj.mpossTeams.to_ulong();
    os.write(reinterpret_cast<char *>(&temp), 1);
    temp = obj.mdefTeams.to_ulong();
    os.write(reinterpret_cast<char *>(&temp), 1);

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
    is.read(reinterpret_cast<char *>(&temp), 2);
    if (temp != obj.magicNumber)
        return is;

    is.read(reinterpret_cast<char *>(&temp), 1);
    obj.mpossTeams = std::bitset<8>(temp);
    is.read(reinterpret_cast<char *>(&temp), 1);
    obj.mdefTeams = std::bitset<8>(temp);

    is >> obj.mname >> obj.mdescr;

    is.read(reinterpret_cast<char *>(&temp), 1);
    for (int i = 0; i < temp; ++i)
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

} // namespace poplib
