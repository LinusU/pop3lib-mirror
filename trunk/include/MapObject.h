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

#ifndef _H_POPLIB_MAP_OBJECT__
#define _H_POPLIB_MAP_OBJECT__

#include "MapObjGeneric.h"

namespace poplib
{
class MapDat;

/** This template allows to create typesafety map objects. */
template <typename T>
class MapObject : public MapObjGeneric
{
public:
    /** Generic constructor. */
    MapObject(Type type, T model, Owner owner, int posx, int posy) :
            MapObjGeneric(type, model, owner, posx, posy) {}
    /** Constructor for building objects. */
    MapObject(ModelBuilding model, Owner owner, int posx, int posy, long angle) :
            MapObjGeneric(model, owner, posx, posy, angle) {}
    /** Constructor for scenery objects. */
    MapObject(ModelScenery model, Owner owner, int posx, int posy, int angle) :
            MapObjGeneric(model, owner, posx, posy, angle) {}
    /** Constructor for discovery objects. */
    MapObject(Owner owner, int posx, int posy, DiscoveryAvailabilityType discType) :
            MapObjGeneric(owner, posx, posy, discType) {}
    /** Constructor for trigger objects. */
    MapObject(Owner owner, int posx, int posy, TriggerType trigType) :
            MapObjGeneric(owner, posx, posy, trigType) {}
    /** Destructor. **/
    virtual ~MapObject() {}
    /** Returns the model of the object. */
    virtual T model() const
    {
        return static_cast<T>(mdata.model);
    }
    /** Sets model of the object. */
    void setModel(T model)
    {
        mdata.model = static_cast<T>(model);
    }

protected:
    /** Used to construct object from data structure while loading objects in the MapDat class. */
    MapObject(const MapObjData& data) : MapObjGeneric(data) {}
};

/** Represents a follower on the map. */
class MapObjFollower : public MapObject<MapObjGeneric::ModelFollower>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjFollower ( ModelFollower model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelFollower>( MapObjGeneric::FOLLOWER, model, owner, posx, posy )
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjFollower(const MapObjData& data) : MapObject<MapObjGeneric::ModelFollower>(data) {}
};


/** Represents a building on the map. */
class MapObjBuilding : public MapObject<MapObjGeneric::ModelBuilding>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    @param angle Angle of the building on the map.
    */
    MapObjBuilding ( ModelBuilding model, Owner owner, int posx = 0, int posy = 0, long angle = 0 ) :
            MapObject<MapObjGeneric::ModelBuilding>(model, owner, posx, posy, angle)
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjBuilding(const MapObjData& data) : MapObject<MapObjGeneric::ModelBuilding>(data) {}
};


/** Represents a creature on the map. */
class MapObjCreature : public MapObject<MapObjGeneric::ModelCreature>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjCreature ( ModelCreature model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelCreature>( MapObjGeneric::CREATURE, model, owner, posx, posy )
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjCreature(const MapObjData& data) : MapObject<MapObjGeneric::ModelCreature>(data) {}
};


/** Represents a vehicle on the map. */
class MapObjVehicle : public MapObject<MapObjGeneric::ModelVehicle>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjVehicle ( ModelVehicle model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelVehicle>( MapObjGeneric::VEHICLE, model, owner, posx, posy )
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjVehicle(const MapObjData& data) : MapObject<MapObjGeneric::ModelVehicle>(data) {}
};


/** Represents a scenery object on the map. */
class MapObjScenery : public MapObject<MapObjGeneric::ModelScenery>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    @param angle Angle of the building on the map.
    */
    MapObjScenery ( ModelScenery model, Owner owner, int posx = 0, int posy = 0, int angle = 0) :
            MapObject<MapObjGeneric::ModelScenery>(model, owner, posx, posy, angle)
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjScenery(const MapObjData& data) : MapObject<MapObjGeneric::ModelScenery>(data) {}
};


/** Represents a general object on the map. */
class MapObjGeneral : public MapObject<MapObjGeneric::ModelGeneral>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjGeneral ( ModelGeneral model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelGeneral>( MapObjGeneric::GENERAL, model, owner, posx, posy )
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjGeneral(const MapObjData& data) : MapObject<MapObjGeneric::ModelGeneral>(data) {}
};


/** Represents an effect on the map, including spell effect. */
class MapObjEffect : public MapObject<MapObjGeneric::ModelEffect>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjEffect ( ModelEffect model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelEffect>( MapObjGeneric::EFFECT, model, owner, posx, posy )
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjEffect(const MapObjData& data) : MapObject<MapObjGeneric::ModelEffect>(data) {}
};


/** Represents a shot effect, including firewarrior's shot. */
class MapObjShot : public MapObject<MapObjGeneric::ModelShot>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjShot ( ModelShot model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelShot>( MapObjGeneric::SHOT, model, owner, posx, posy )
    {

    }

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjShot(const MapObjData& data) : MapObject<MapObjGeneric::ModelShot>(data) {}
};


/** Represents a general shape on the map. */
class MapObjShape: public MapObject<MapObjGeneric::ModelShape>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjShape ( ModelShape model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelShape>( MapObjGeneric::SHAPE, model, owner, posx, posy ) {}

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjShape(const MapObjData& data) : MapObject<MapObjGeneric::ModelShape>(data) {}
};


/** Represents game's internal object on the map. */
class MapObjInternal : public MapObject<MapObjGeneric::ModelInternal>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjInternal ( ModelInternal model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelInternal>( MapObjGeneric::INTERNAL, model, owner, posx, posy ) {}

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjInternal(const MapObjData& data) : MapObject<MapObjGeneric::ModelInternal>(data) {}
};


/** Represents a spell object on the map. */
class MapObjSpell : public MapObject<MapObjGeneric::ModelSpell>
{
public:
    friend MapObjGeneric* MapObjGeneric::loadObject(std::istream& is);
    friend MapObjGeneric* MapObjGeneric::fromCompactForm(std::istream& is);
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjSpell ( ModelSpell model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<MapObjGeneric::ModelSpell>( MapObjGeneric::SPELL, model, owner, posx, posy ) {}

private:
    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjSpell(const MapObjData& data) : MapObject<MapObjGeneric::ModelSpell>(data) {}
};

} // namespace poplib

#endif // _H_POPLIB_MAP_OBJECT__
