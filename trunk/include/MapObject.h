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

#include "AbstractMapObj.h"

namespace poplib
{
/** This template allows to create typesafety map objects. */
template <typename T>
class MapObject : public AbstractMapObj
{
public:
    /** Constructor.
    @param type Type of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObject ( Type type, T model, Owner owner, int posx = 0, int posy = 0 );
    /** Returns the model of the object. */
    virtual T model() const { return mmodel; }
    /** Sets a model for the object. */
    virtual void setModel ( T model ) { mmodel = model; }

protected:
    /** Saves model, type, owner and position of the object to the stream. */
    virtual std::ostream& saveObject ( std::ostream& os ) const;
    /** Loades model, type, owner and position of the object from the stream. */
    virtual std::istream& loadObject ( std::istream& is );

private:
    T mmodel;
};

template <typename T>
MapObject<T>::MapObject ( Type type, T model, Owner owner, int posx , int posy ) :
        AbstractMapObj ( type, owner, posx, posy ), mmodel(model)
{

}

template<typename T>
std::ostream& MapObject<T>::saveObject ( std::ostream& os ) const
{
    T model = mmodel;
    Type typ = type();
    Owner own = owner();
    int posx = positionx();
    int posy = positiony();

    os.write ( reinterpret_cast<char *> ( &model ), 1 );
    os.write ( reinterpret_cast<char *> ( &typ ), 1 );
    os.write ( reinterpret_cast<char *> ( &own ), 1 );
    os.write ( reinterpret_cast<char *> ( &posx ), 2 );
    os.write ( reinterpret_cast<char *> ( &posy ), 2 );

    return os;
}

template<typename T>
std::istream& MapObject<T>::loadObject ( std::istream& is )
{
    unsigned int model;
    int posx, posy;
    Type type;
    Owner owner;

    is.read ( reinterpret_cast<char *> ( &model ), 1 );
    is.read ( reinterpret_cast<char *> ( &type ), 1 );
    is.read ( reinterpret_cast<char *> ( &owner ), 1 );
    is.read ( reinterpret_cast<char *> ( &posx ), 2 );
    is.read ( reinterpret_cast<char *> ( &posy ), 2 );

    setModel ( static_cast<T> ( model ) );
    setType ( type );
    setOwner ( owner );
    setPosition ( posx, posy );

    return is;
}
/** Represents a follower on the map. */
class MapObjFollower : public MapObject<AbstractMapObj::ModelFollower>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjFollower ( ModelFollower model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelFollower> ( AbstractMapObj::FOLLOWER, model, owner, posx, posy )
    {

    }
};
/** Represents a building on the map. */
class MapObjBuilding : public MapObject<AbstractMapObj::ModelBuilding>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    @param angle Angle of the building on the map.
    */
    MapObjBuilding ( ModelBuilding model, Owner owner, int posx = 0, int posy = 0, long angle = 0 ) :
            MapObject<AbstractMapObj::ModelBuilding> ( AbstractMapObj::BUILDING, model, owner, posx, posy ), mangle(angle)
    {

    }

protected:
    /** Saves object's properties and angle. */
    virtual std::ostream& saveObject ( std::ostream& os ) const
    {
        MapObject<AbstractMapObj::ModelBuilding>::saveObject ( os );
        os.write ( reinterpret_cast<const char *> ( &mangle ), sizeof ( mangle ) );
    }
    /** Loades object's properties and angle. */
    virtual std::istream& loadObject ( std::istream& is )
    {
        MapObject<AbstractMapObj::ModelBuilding>::loadObject ( is );
        is.read ( reinterpret_cast<char *> ( &mangle ), sizeof ( mangle ) );
    }

private:
    long mangle;
};
/** Represents a creature on the map. */
class MapObjCreature : public MapObject<AbstractMapObj::ModelCreature>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjCreature ( ModelCreature model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelCreature> ( AbstractMapObj::CREATURE, model, owner, posx, posy )
    {

    }
};
/** Represents a vehicle on the map. */
class MapObjVehicle : public MapObject<AbstractMapObj::ModelVehicle>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjVehicle ( ModelVehicle model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelVehicle> ( AbstractMapObj::VEHICLE, model, owner, posx, posy )
    {

    }
};
/** Represents a scenery object on the map. */
class MapObjScenery : public MapObject<AbstractMapObj::ModelScenery>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    @param angle Angle of the building on the map.
    */
    MapObjScenery ( ModelScenery model, Owner owner, int posx = 0, int posy = 0, long angle = 0) :
            MapObject<AbstractMapObj::ModelScenery> ( AbstractMapObj::SCENERY, model, owner, posx, posy ), mangle(angle)
    {

    }

protected:
    /** Saves object's properties and angle. */
    virtual std::ostream& saveObject ( std::ostream& os ) const
    {
        MapObject<AbstractMapObj::ModelScenery>::saveObject ( os );
        os.seekp ( 2, std::ios_base::cur );
        os.write ( reinterpret_cast<const char *> ( &mangle ), sizeof ( mangle ) );
    }
    /** Loades object's properties and angle. */
    virtual std::istream& loadObject ( std::istream& is )
    {
        MapObject<AbstractMapObj::ModelScenery>::loadObject ( is );
        is.seekg ( 2, std::ios_base::cur );
        is.read ( reinterpret_cast<char *> ( &mangle ), sizeof ( mangle ) );
    }

private:
    long mangle;
};
/** Represents a general object on the map. */
class MapObjGeneral : public MapObject<AbstractMapObj::ModelGeneral>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjGeneral ( ModelGeneral model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelGeneral> ( AbstractMapObj::GENERAL, model, owner, posx, posy )
    {

    }
};
/** Represents an effect on the map, including spell effect. */
class MapObjEffect : public MapObject<AbstractMapObj::ModelEffect>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjEffect ( ModelEffect model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelEffect> ( AbstractMapObj::EFFECT, model, owner, posx, posy )
    {

    }
};
/** Represents a shot effect, including firewarrior's shot. */
class MapObjShot : public MapObject<AbstractMapObj::ModelShot>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjShot ( ModelShot model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelShot> ( AbstractMapObj::SHOT, model, owner, posx, posy )
    {

    }
};
/** Represents a general shape on the map. */
class MapObjShape: public MapObject<AbstractMapObj::ModelShape>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjShape ( ModelShape model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelShape> ( AbstractMapObj::SHAPE, model, owner, posx, posy )
    {

    }
};
/** Represents game's internal object on the map. */
class MapObjInternal : public MapObject<AbstractMapObj::ModelInternal>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjInternal ( ModelInternal model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelInternal> ( AbstractMapObj::INTERNAL, model, owner, posx, posy )
    {

    }
};
/** Represents a spell object on the map. */
class MapObjSpell : public MapObject<AbstractMapObj::ModelSpell>
{
public:
    /** Constructor.
    @param model Model of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    MapObjSpell ( ModelSpell model, Owner owner, int posx = 0, int posy = 0 ) :
            MapObject<AbstractMapObj::ModelSpell> ( AbstractMapObj::SPELL, model, owner, posx, posy )
    {

    }
};

} // namespace poplib

#endif // _H_POPLIB_MAP_OBJECT__
