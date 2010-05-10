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

#include "MapObjDiscovery.h"

namespace poplib
{

MapObjDiscovery::MapObjDiscovery ( DiscoveryAvailabilityType discType, Owner owner, int posx, int posy) :
        MapObjGeneral ( AbstractMapObj::DISCOVERY, owner, posx, posy ), mdiscType(discType)
{

}

std::ostream& MapObjDiscovery::saveObject ( std::ostream& os ) const
{
    MapObject<ModelGeneral>::saveObject ( os );
    // TODO saving map object discovery

	return os;
}

std::istream& MapObjDiscovery::loadObject ( std::istream& is )
{
    MapObject<ModelGeneral>::loadObject ( is );
    // TODO loading map object discovery

	return is;
}

} // namespace poplib
