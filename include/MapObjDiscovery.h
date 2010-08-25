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

#ifndef _H_POPLIB_MAP_OBJ_DISCOVERY__
#define _H_POPLIB_MAP_OBJ_DISCOVERY__

#include "MapObject.h"

namespace poplib
{

class MapObjDiscovery : public MapObject<MapObjGeneric::ModelGeneral>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);

    MapObjDiscovery ( DiscoveryAvailabilityType discType, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelGeneral> (owner, posx, posy, discType) {}

    virtual ~MapObjDiscovery() {}

    DiscoveryAvailabilityType discoveryType() const
    {
        return static_cast<DiscoveryAvailabilityType>(mdata.discovery.discType);
    }
    void setDiscoveryType ( DiscoveryAvailabilityType discType )
    {
        mdata.discovery.discType = discType;
    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjDiscovery(const MapObjData& data) : MapObject<MapObjGeneric::ModelGeneral>(data) {}
};

} // namespace poplib

#endif // _H_POPLIB_MAP_OBJ_DISCOVERY__
