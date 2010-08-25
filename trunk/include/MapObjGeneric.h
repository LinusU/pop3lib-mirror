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

#ifndef _H_POPLIB_GENERIC_MAP_OBJ__
#define _H_POPLIB_GENERIC_MAP_OBJ__

#include <iostream>
#include <cstring>
#include <list>

#include "global.h"

namespace poplib
{
/** Base class for all populous objects on the map. */
class MapObjGeneric
{
public:
    /**  Which tribe is the owner of the object. */
    enum Owner {NEUTRAL = -1, BLUE = 0, RED, YELLOW, GREEN};
    /** Special objects like discoveries or triggers have GENERAL type.*/
    enum Type {FOLLOWER = 1, BUILDING, CREATURE, VEHICLE, SCENERY, GENERAL, EFFECT, SHOT, SHAPE, INTERNAL, SPELL};

    enum ModelFollower {WILDMAN = 1, BRAVE, WARRIOR, PREACHER, SPY, FIREWARRIOR, SHAMAN, ANGEL_OF_DEATH_MODEL};
    /** RECONVERSION, WALL_PIECE, GATE and CURR_OE_SLOT are unused in the maps. */
    enum ModelBuilding {SMALL_HUT = 1, MEDIUM_HUT, LARGE_HUT, GUARD_TOWER, TEMPLE, SPY_TRAINING_HUT, WARRIOR_TRAINING_HUT, FIREWARRIOR_TRAINING_HUT,
                        RECONVERSION /* unused */, WALL_PIECE /* unused */, GATE /* unused */, CURR_OE_SLOT /* unused */, BOAT_HOUSE, BOAT_HOUSE_2,
                        BALLOON_HUT, BALLOON_HUT_2, GUARD_POST, VAULT_OF_KNOWLEADGE, PRISON
                       };
    /** All models are visible as an EAGLE. */
    enum ModelCreature {BEAR = 1, BUFFALO, WOLF, EAGLE, RABBIT, BEAVER, FISH};

    enum ModelVehicle {BOAT = 1, BOAT_2, BALLOON, BALLOON_2};

    enum ModelScenery {TREE_1, TREE_2, TREE_3, TREE_4, TREE_5, TREE_6, PLANT_1, PLANT_2, STONE_HEAD, FIRE, WOOD_PILE, REINCARNATION_SITE_PILLAR,
                       ROCK, PORTAL, ISLAND, BRIDGE, DORMANT_TREE, TOP_LVL_SCENERY, SUB_LVL_SCENERY
                      };

    enum ModelGeneral {LIGHT = 1, DISCOVERY, DEBUG_STATIC, DEBUG_FLYING, DEBUG_FLAG, TRIGGER, VEHICLE_CONSTRUCTION, MAPWHO_THING, BUILDING_ADD_ON,
                       DISCOVERY_MARKER
                      };
    /** LANDBRIDGE_EFFECT requires additional parameters. */
    enum ModelEffect {SIMPLE_BLAST = 1, SPRITE_CIRCLES, SMOKE, LIGHTNING_ELEM, BURN_CELL_OBSTACLES, FLATTEN_LAND, MOVE_RS_PILLAR, PREPARE_RS_LAND,
                      SPHERE_EXPLODE, FIREBALL, FIRECLOUD, GHOST_ARMY_EFFECT, INVISIBILITY_EFFECT, EXPLODE_BLDG_PARTIAL, VOLCANO_EFFECT, HYPNOTISM, LIGHTNING_BOLT,
                      SWAMP_EFFECT, FIRESTORM_EFFECT, EROSION, LANDBRIDGE_EFFECT /* requires additional parameters */, WRATH_OF_GOD, EARTHQUAKE_EFFECT, FLY_THINGUMMY,
                      SPHERE_EXPLODE_AND_FIRE, BIG_FIRE, LIGHTNING_EFFECT, FLATTEN_EFFECT, GENERAL_EFFECT, SHAPE_SPARKLE, LAVA_FLOW, VOLCANO_EXPLOSIONS, PURIFY_LAND,
                      UNPURIFY_LAND, EXPLOSION_1, EXPLOSION_2, LAVA_SQUARE, WW_ELEMENT, RAISE_LAND, LOWER_LAND, HILL, VALLEY, PLACE_TREE, RISE, DIP,
                      REIN_ROCK_DEBRIS, CLEAN_MAPWHO, PLACE_SHAMAN, PLACE_WILD, BLDG_SMOKE, MUCH_SIMPLER_BLAST, TRUMBLING_BRANCH, CONVERSION_FLASH,
                      HYPNOSIS_FLASH, SPARKLE, SMALL_SPARKLE, EXPLOSION_3, ROCK_EXPLOSION, LAVA_GLOOP, SPLASH_6, SMOKE_CLOUD, SMOKE_CLOUD_CONSTANT,
                      FIREBALL_2, GROUND_SHOCKWAVE, ORBITER, BIG_SPARKLE, METEOR, CONEVRT_WILD, BLDG_SMOKE_2_FULL, BLDG_SMOKE_2_PARTIAL,
                      BLDG_DAMAGED_SMOKE, DELETE_RS_PILLAR, SPELL_BLAST, FIRESTORM_SMOKE, PLAYER_DEAD, REVEAL_FOG_AREA, SHIELD, BOAT_HUT_REPAIR,
                      REEDY_GRASS, SWAMP_MIST, ARMAGEDDON_EFFECT, BLOODLUST_EFFECT, TELEPORT_EFFECT, ATLANTIS_SET, ATLANTIS_INVOKE, STATUE_TO_AOD, FILL_ONE_SHOT, FIRE_ROLL_ELEM
                     };

    enum ModelShot {STANDARD = 1, STANDARD_2, STANDARD_3, FIREBALL_SHOT, LIGHTNING_SHOT, FIREWARRIOR_SHOT, VOLCANO_FIREBALL_1, VOLCANO_FIREBALL_2};

    enum ModelShape {GENERAL_SHAPE = 1};

    enum ModelInternal {FORMATION = 1, BEACON, THING_INFO_DISPLAY, SOUL_CONVERT, SOUL_MAN, PREACHER_ATTRACT, OBJECT_FACE, FIGHT, PRE_FIGHT,
                        GUARD_CONTROL, BRIDGE_CONTROL, SOUL_CONVERT_2, DT_BEACON, PLAYER_RAISE, PLAYER_LOWER, GUARD_POST_DISPLAY, PLAYER_SMOOTH,
                        WOOD_DISTRIBUTE, SINKING_BUILDING
                       };

    enum ModelSpell {BURN = 1, BLAST, LIGHTNING, TORNADO, SWARM, INVISIBILITY, HYPNOTISE, FIRESTORM, GHOST_ARMY, ERODE, SWAMP, LANDBRIDGE,
                     ANGEL_OF_DEATH_SPELL, EARTHQUAKE, FLATTEN, VOLCANO, CONVERT, ARMAGEDDON, MAGICAL_SHIELD, BLOODLUST, TELEPORT
                    };

    // TODO add more things to discoveries
    enum DiscoveryAvailabilityType {NOT_AVAILABLE = 0, PERMAMENT /* Needed for Vault of Knowledge */, LEVEL, ONCE, DISCOVERY_AV_TYPE};

    // TODO add more things to triggers
    enum TriggerType {PROXIMITY = 0, // Stone Head or Totem Pole
                      TIMED, // Usually reoccurring automatic things
                      PLAYER_DEATH,
                      SHAMAN_PROXIMITY, // Obelisk
                      LIBRARY, // Vault of Knowledge
                      SHAMAN_AOD // Gargoyle
                     };

    virtual ~MapObjGeneric() {}
    /** Returns type of the object */
    virtual Type type() const
    {
        return static_cast<Type>(mdata.type);
    }
    /** Returns tribe who is the owner of the object. */
    Owner owner() const
    {
        return static_cast<Owner>(mdata.owner);
    }
    /** Set new owner of the object.
    @param own Which tribe is the new owner of an object.
    */
    void setOwner(Owner owner)
    {
        mdata.owner = static_cast<Owner>(owner);
    }
    /** Returns X position of the object on the map. */
    char posx() const
    {
        return mdata.posx;
    }
    /** Returns Y position of the object on the map. */
    char posy() const
    {
        return mdata.posy;
    }
    /** Set new position of the object on the map. */
    void setPosition ( short posX, short posY ) {
        mdata.posx = posX;
        mdata.posy = posY;
    }
    /** Saves object to the stream. */
    static std::ostream& saveObject(const MapObjGeneric* obj, std::ostream& os)
    {
        os.write(reinterpret_cast<const char *>(&(obj->mdata)), 55);
        return os;
    }
    /** Returns copy of the object. */
    static MapObjGeneric* clone(const MapObjGeneric* obj);
    /** Loads object from the stream. */
    static MapObjGeneric* loadObject(std::istream& is);
    /** Saves object details using compact form. Suitable for sending data over the internet. */
    static std::ostream& toCompactForm (const MapObjGeneric* obj, std::ostream& os);
    /** Loades object details from compact form. */
    static MapObjGeneric* fromCompactForm(std::istream& is);

protected:
    typedef struct _BuildingData
    {
        SDWORD angle;
    } BuildingData;


    typedef struct _SceneryData
    {
        UBYTE gap[3];
        SWORD angle;
    } SceneryData;


    typedef struct _DiscoveryData
    {
        UBYTE discType,
        discModel,
        availabilityType,
        triggerType;
        SDWORD manaAmount;
    } DiscoveryData;


    typedef struct _TriggerData
    {
        UBYTE trigType,
        cellRadius,
        randomValue;
        SBYTE occurencesNumb;
        UWORD followersNumb, // how many followers may pray it
        objectId[10]; // id = position of the object in the file
        UWORD prayTime; // in game turns, 1 sec = 12 game turns
        UBYTE startInactive,
        createPlayerOwned;
        SWORD inactiveTime;
    } TriggerData;

    typedef struct _MapObjData
    {
        UBYTE model,
        type;
        SBYTE owner;
        SWORD posx,
        posy;
        union
        {
            BuildingData building;
            SceneryData scenery;
            DiscoveryData discovery;
            TriggerData trigger;
            UBYTE gap[48]; // each object must have exactly 55 bytes
        };

        // default constructor
        _MapObjData() :
                model(BALLOON), type(VEHICLE), owner(NEUTRAL), posx(0), posy(0) {
            std::memset(gap, 0, sizeof(gap));
        }
        // generic constructor
        _MapObjData(Type _type, UBYTE _model, Owner _owner, int _posx, int _posy) :
                model(_model), type(_type), owner(_owner), posx(_posx), posy(_posy) {
            std::memset(gap, 0, sizeof(gap));
        }
        // constructor for building objects
        _MapObjData (ModelBuilding _model, Owner _owner, int _posx, int _posy, long _angle) :
                model(_model), type(BUILDING), owner(_owner), posx(_posx), posy(_posy) {
            std::memset(gap, 0, sizeof(gap));
            building.angle = _angle;
        }
        // constructor for scenery objects
        _MapObjData (ModelScenery _model, Owner _owner, int _posx, int _posy, int _angle) :
                model(_model), type(SCENERY), owner(_owner), posx(_posx), posy(_posy) {
            std::memset(gap, 0, sizeof(gap));
            scenery.angle = _angle;
        }
        // constructor for discovery objects
        _MapObjData (Owner _owner, int _posx, int _posy, DiscoveryAvailabilityType discType) :
                model(DISCOVERY), type(GENERAL), owner(_owner), posx(_posx), posy(_posy) {
            std::memset(gap, 0, sizeof(gap));
            discovery.discType = discType;
        }
        // constructor for trigger objects
        _MapObjData(Owner _owner, int _posx, int _posy, TriggerType _trigType) :
                model(TRIGGER), type(GENERAL), owner(_owner), posx(_posx), posy(_posy) {
            std::memset(gap, 0, sizeof(gap));
            trigger.trigType = _trigType;
        }
    } MapObjData;

    // Used to construct object from data structure while loading objects in the MapDat class.
    MapObjGeneric(const MapObjData& data) : mdata(data) {}
    // Default constructor.
    MapObjGeneric() {}
    // Generic constructor.
    MapObjGeneric(Type type, UBYTE model, Owner owner, int posx, int posy) :
            mdata(type, model, owner, posx, posy) {}
    // Constructor for building objects.
    MapObjGeneric(ModelBuilding model, Owner owner, int posx, int posy, long angle) :
            mdata(model, owner, posx, posy, angle) {}
    // Constructor for scenery objects.
    MapObjGeneric(ModelScenery model, Owner owner, int posx, int posy, int angle) :
            mdata(model, owner, posx, posy, angle) {}
    // Constructor for discovery objects.
    MapObjGeneric(Owner owner, int posx, int posy, DiscoveryAvailabilityType discType) :
            mdata(owner, posx, posy, discType) {}
    // Constructor for trigger objects.
    MapObjGeneric(Owner owner, int posx, int posy, TriggerType trigType) :
            mdata(owner, posx, posy, trigType) {}

    MapObjData mdata;
};

} // namespace poplib

#endif // _H_POPLIB_GENERIC_MAP_OBJ__
