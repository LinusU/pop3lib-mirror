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

#include "MapObjTrigger.h"

namespace poplib
{

MapObjTrigger::MapObjTrigger ( TriggerType trigType, Owner owner, int posx, int posy ) :
        MapObjGeneral ( AbstractMapObj::TRIGGER, owner, posx, posy ), mtrigType(trigType)
{

}

std::ostream& MapObjTrigger::saveObject ( std::ostream& os ) const
{
    MapObject<ModelGeneral>::saveObject ( os );
    // TODO saving map object trigger

	return os;
}

std::istream& MapObjTrigger::loadObject ( std::istream& is )
{
    MapObject<ModelGeneral>::loadObject ( is );
    // TODO loading map object trigger

	return is;
}

} // namespace poplib
