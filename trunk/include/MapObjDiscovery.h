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

class MapObjDiscovery : public MapObject<AbstractMapObj::ModelGeneral>
{
public:
	// TODO add more things to discoveries
    enum DiscoveryAvailabilityType {NOT_AVAILABLE = 0, PERMAMENT /* Needed for Vault of Knowledge */, LEVEL, ONCE, DISCOVERY_AV_TYPE};

    MapObjDiscovery ( DiscoveryAvailabilityType discType, Owner owner, int posx = 0, int posy = 0 ) ;
    virtual ~MapObjDiscovery();

    DiscoveryAvailabilityType discoveryType() const { return mdiscType; }
    void setDiscoveryType ( DiscoveryAvailabilityType discType ) { mdiscType = discType; }

protected:
    virtual std::ostream& saveObject ( std::ostream& os ) const;
    virtual std::istream& loadObject ( std::istream& is );

private:
    DiscoveryAvailabilityType mdiscType;
};

} // namespace poplib

#endif // _H_POPLIB_MAP_OBJ_DISCOVERY__
