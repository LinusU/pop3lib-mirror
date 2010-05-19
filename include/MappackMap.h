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

#ifndef _H_POPLIB_MAPPACKMAP__
#define _H_POPLIB_MAPPACKMAP__

#include <string>
#include <bitset>
#include <list>

#include "String16.h"
#include "bits/mapBits.h"
#include "Map.h"

namespace poplib
{

class MappackMap : public Map
{
public:
    typedef _Teams Teams;
    enum Status {ALPHA = 0, BETA, STABLE, MATURE};

    MappackMap();
    explicit MappackMap(const std::string& fileName);
    MappackMap(const std::string& directory, const std::string& mapName);
    /** Copy constructor. */
    MappackMap ( const MappackMap& map );
    MappackMap& operator= ( const MappackMap& map );
    virtual ~MappackMap();

    void saveExtended(const std::string& fileName) const;
    void loadExtended(const std::string& fileName);

    void setPossibleTeams(Teams teams, bool enabled);
    bool isPossibleTeam(Teams team) const;
    void setDefaultTeams(Teams teams, bool enabled);
    bool isDefaultTeam(Teams team) const;

    void setMapName(const String16& name) { mname =  name; }
    String16 mapName() const { return mname; }
    void setDescription(const String16& descr) { mdescr = descr; }
    String16 description() const { return mdescr; }
    void addAuthor(const String16& author) { mauthors.push_back(new String16(author)); }
    void removeAuthor(const String16& author);
    void setAuthors(const std::list<String16 *>& authors);
    std::list<String16 *> authors() const { return mauthors; }
    void setStatus(Status status) { mstatus = status; }
    Status status() const { return mstatus; }

    friend std::ostream& operator<<(std::ostream& os, const MappackMap& obj);
    friend std::istream& operator>>(std::istream& is, MappackMap& obj);

private:
    std::bitset<8> mpossTeams;
    std::bitset<8> mdefTeams;
    String16 mname;
    String16 mdescr;
    std::list<String16 *> mauthors;
    Status mstatus;

    static const unsigned short magicNumber = 10611;

    void clearAuthors();
    void copyAuthors(const MappackMap& map);
};

} // namespace poplib

#endif // _H_POPLIB_MAPPACKMAP__
