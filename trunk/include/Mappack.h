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

#ifndef _H_POPLIB_MAPPACK__
#define _H_POPLIB_MAPPACK__

#include <string>
#include <list>

#include "MappackMap.h"

namespace poplib
{

class Mappack
{
public:
    Mappack();
    explicit Mappack(const std::string& fileName);
    /** Copy constructor. */
    Mappack ( const Mappack& mappack );
    Mappack& operator= ( const Mappack& mappack );
    virtual ~Mappack();

    void loadFromFile(const std::string& fileName);
    void loadFromDirectory(const std::string& dir);
    void saveToFile(const std::string& fileName) const;

    void addMap(MappackMap* map) { mmaps.push_back(map); }
    void removeMap(MappackMap* map);
    std::list<MappackMap *> maps() const { return mmaps; }

    String16 name() const { return mname; }
    void setName(const String16& name) { mname = name; }
    String16 description() const { return mdesc; }
    void setDescription(const String16& desc) { mdesc = desc; }

private:
    std::list<MappackMap *> mmaps;
    String16 mname;
    String16 mdesc;

    static const unsigned int magicNumber = 10499;

    void cleanMaps();
    void copyMaps(const Mappack& mappack);

    // TODO mappack text informations should be stored as UTF-8
};

} // namespace poplib

#endif // _H_POPLIB_MAPPACK__
