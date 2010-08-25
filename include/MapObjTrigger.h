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

#ifndef _H_POPLIB_MAP_OBJ_TRIGGER__
#define _H_POPLIB_MAP_OBJ_TRIGGER__

#include "MapObject.h"

namespace poplib
{

class MapObjTrigger : public MapObject<MapObjGeneric::ModelGeneral>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);

    MapObjTrigger(TriggerType trigType, Owner owner, int posx, int posy):
            MapObject<MapObjGeneric::ModelGeneral>(owner, posx, posy, trigType) {}

    virtual ~MapObjTrigger() {}

    TriggerType triggerType() const
    {
        return static_cast<TriggerType>(mdata.trigger.trigType);
    }
    void setTriggerType(TriggerType trigType)
    {
        mdata.trigger.trigType = trigType;
    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjTrigger(const MapObjData& data) : MapObject<MapObjGeneric::ModelGeneral>(data) {}
};

} // namespace poplib

#endif // _H_POPLIB_MAP_OBJ_TRIGGER__
