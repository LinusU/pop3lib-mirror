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

#include <cstring>

#include "MapObjTrigger.h"
#include "MapObjDiscovery.h"

namespace poplib
{

MapObjGeneric* MapObjGeneric::clone(const MapObjGeneric* obj)
{
    MapObjGeneric* objClone = 0;
    const MapObjGeneral* objGen;

    switch (obj->type())
    {
    case MapObjGeneric::FOLLOWER:
        objClone = new MapObjFollower(*static_cast<const MapObjFollower *>(obj));
        break;
    case MapObjGeneric::BUILDING:
        objClone = new MapObjBuilding(*static_cast<const MapObjBuilding *>(obj));
        break;
    case MapObjGeneric::CREATURE:
        objClone = new MapObjCreature(*static_cast<const MapObjCreature *>(obj));
        break;
    case MapObjGeneric::VEHICLE:
        objClone = new MapObjVehicle(*static_cast<const MapObjVehicle *>(obj));
        break;
    case MapObjGeneric::SCENERY:
        objClone = new MapObjScenery(*static_cast<const MapObjScenery *>(obj));
        break;
    case MapObjGeneric::GENERAL:
        objGen = static_cast<const MapObjGeneral *>(obj);
        if (objGen->model() == MapObjGeneric::TRIGGER)
            objClone = new MapObjTrigger(*static_cast<const MapObjTrigger *>(obj));
        else if (objGen->model() == MapObjGeneric::DISCOVERY)
            objClone = new MapObjDiscovery(*static_cast<const MapObjDiscovery *>(obj));
        else
            objClone = new MapObjGeneral(*objGen);
        break;
    case MapObjGeneric::EFFECT:
        objClone = new MapObjEffect(*static_cast<const MapObjEffect *>(obj));
        break;
    case MapObjGeneric::SHOT:
        objClone = new MapObjShot(*static_cast<const MapObjShot *>(obj));
        break;
    case MapObjGeneric::SHAPE:
        objClone = new MapObjShape(*static_cast<const MapObjShape *>(obj));
        break;
    case MapObjGeneric::INTERNAL:
        objClone = new MapObjInternal(*static_cast<const MapObjInternal *>(obj));
        break;
    case MapObjGeneric::SPELL:
        objClone = new MapObjSpell(*static_cast<const MapObjSpell *>(obj));
        break;
    }

    return objClone;
}

MapObjGeneric* MapObjGeneric::loadObject(std::istream& is)
{
    MapObjGeneric* obj = 0;
    MapObjGeneric::MapObjData objData;
    memset(&objData, 0, sizeof(objData));
    is.read(reinterpret_cast<char *>(&objData), sizeof(objData));
    switch (objData.type)
    {
    case MapObjGeneric::FOLLOWER:
        obj = new MapObjFollower(objData);
        break;
    case MapObjGeneric::BUILDING:
        obj = new MapObjBuilding(objData);
        break;
    case MapObjGeneric::CREATURE:
        obj = new MapObjCreature(objData);
        break;
    case MapObjGeneric::VEHICLE:
        obj = new MapObjVehicle(objData);
        break;
    case MapObjGeneric::SCENERY:
        obj = new MapObjScenery(objData);
        break;
    case MapObjGeneric::GENERAL:
        if (objData.model == MapObjGeneric::TRIGGER)
            obj = new MapObjTrigger(objData);
        else if (objData.model == MapObjGeneric::DISCOVERY)
            obj = new MapObjDiscovery(objData);
        else
            obj = new MapObjGeneral(objData);
        break;
    case MapObjGeneric::EFFECT:
        obj = new MapObjEffect(objData);
        break;
    case MapObjGeneric::SHOT:
        obj = new MapObjShot(objData);
        break;
    case MapObjGeneric::SHAPE:
        obj = new MapObjShape(objData);
        break;
    case MapObjGeneric::INTERNAL:
        obj = new MapObjInternal(objData);
        break;
    case MapObjGeneric::SPELL:
        obj = new MapObjSpell(objData);
        break;
    }

    return obj;
}
// TODO think about making objects smaller
std::ostream& MapObjGeneric::toCompactForm (const MapObjGeneric* obj, std::ostream& os)
{
    // used to store owner and object type
    UBYTE temp = 0;
    // store neutral as 4 instead of -1
    UBYTE owner = obj->mdata.owner == NEUTRAL ? 4 : obj->mdata.owner;
    // four low bits store owner
    temp |= (owner & 0x0F);
    // four high bits store object type
    temp |= ((obj->mdata.type & 0x0F) << 4);
    os.write(reinterpret_cast<char *>(&temp), 1);
    // store model
    os.write(reinterpret_cast<const char *>(&(obj->mdata.model)), 1);
    // store x and y positions
    os.write(reinterpret_cast<const char *>(&(obj->mdata.posx)), 1);
    os.write(reinterpret_cast<const char *>(&(obj->mdata.posy)), 1);
    // store eventual additional data
    if (obj->type() == BUILDING)
    {
        // angle of the building
        os.write(reinterpret_cast<const char *>(&(obj->mdata.building.angle)), 4);
    }
    else if (obj->type() == SCENERY)
    {
        // angle of the scenery
        os.write(reinterpret_cast<const char *>(&(obj->mdata.scenery.angle)), 2);
    }
    else if (obj->type() == GENERAL)
    {
        const MapObjGeneral* genObj = static_cast<const MapObjGeneral *>(obj);
        if (genObj->model() == TRIGGER)
        {
            // store trigType, cellRadius, randomValue, occurencesNumb, followersNumb
            os.write(reinterpret_cast<const char *>(&(obj->mdata.trigger.trigType)), 6);
            // find how many objects is connected to this trigger
            int i = 0;
            while (obj->mdata.trigger.objectId[i] && i < 10)
                ++i;
            // store information about connected objects
            os.write(reinterpret_cast<char *>(&i), 1);
            // store id of connected objectes
            for (int j = 0; j < i; ++j)
                os.write(reinterpret_cast<const char *>(&(obj->mdata.trigger.objectId[j])), 2);
            // store prayTime, startInactive, createPlayerOwned, inactiveTime
            os.write(reinterpret_cast<const char *>(&(obj->mdata.trigger.prayTime)), 6);
        }
        else if (genObj->model() == DISCOVERY)
        {
            // DiscoveryData
            os.write(reinterpret_cast<const char *>(&(obj->mdata.discovery)), 8);
        }
    }

    return os;
}

MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is)
{
    MapObjGeneric* obj = 0;
    MapObjGeneric::MapObjData objData;
    std::memset(&objData, 0, sizeof(objData));

    UBYTE temp = 0;
    is.read(reinterpret_cast<char *>(&temp), 1);
    // four low bits store owner
    objData.owner = temp & 0x0F;
    if (objData.owner == 4)
        objData.owner = NEUTRAL; // restore original neutral value instead of 4
    // four high bits store type
    objData.type = (temp & 0xF0) >> 4;
    // load model
    is.read(reinterpret_cast<char *>(&(objData.model)), 1);
    // load x and y positions
    is.read(reinterpret_cast<char *>(&(objData.posx)), 1);
    is.read(reinterpret_cast<char *>(&(objData.posy)), 1);
    // load eventual additional data
    switch (objData.type)
    {
    case MapObjGeneric::FOLLOWER:
        obj = new MapObjFollower(objData);
        break;
    case MapObjGeneric::BUILDING:
        // angle of the building
        is.read(reinterpret_cast<char *>(&(objData.building.angle)), 4);
        obj = new MapObjBuilding(objData);
        break;
    case MapObjGeneric::CREATURE:
        obj = new MapObjCreature(objData);
        break;
    case MapObjGeneric::VEHICLE:
        obj = new MapObjVehicle(objData);
        break;
    case MapObjGeneric::SCENERY:
        // angle of the scenery
        is.read(reinterpret_cast<char *>(&(objData.scenery.angle)), 2);
        obj = new MapObjScenery(objData);
        break;
    case MapObjGeneric::GENERAL:
        if (objData.model == TRIGGER)
        {
            // load trigType, cellRadius, randomValue, occurencesNumb, followersNumb
            is.read(reinterpret_cast<char *>(&(objData.trigger)), 6);
            int i = 0;
            // load information about connected objects
            is.read(reinterpret_cast<char *>(&i), 1);
            // load id of connected objectes
            for (int j = 0; j < i; ++j)
                is.read(reinterpret_cast<char *>(&(objData.trigger.objectId[j])), 2);
            // load prayTime, startInactive, createPlayerOwned, inactiveTime
            is.read(reinterpret_cast<char *>(&(objData.trigger.prayTime)), 6);

            obj = new MapObjTrigger(objData);
        }
        else if (objData.model == DISCOVERY)
        {
            // DiscoveryData
            is.read(reinterpret_cast<char *>(&(objData.discovery)), 8);
            obj = new MapObjDiscovery(objData);
        }
        else
        {
            obj = new MapObjGeneral(objData);
        }
        break;
    case MapObjGeneric::EFFECT:
        obj = new MapObjEffect(objData);
        break;
    case MapObjGeneric::SHOT:
        obj = new MapObjShot(objData);
        break;
    case MapObjGeneric::SHAPE:
        obj = new MapObjShape(objData);
        break;
    case MapObjGeneric::INTERNAL:
        obj = new MapObjInternal(objData);
        break;
    case MapObjGeneric::SPELL:
        obj = new MapObjSpell(objData);
        break;
    }

    return obj;
}

} // namespace poplib
