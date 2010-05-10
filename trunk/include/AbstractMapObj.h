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

#include <iostream>

#ifndef _H_POPLIB_ABSTRACT_MAP_OBJ__
#define _H_POPLIB_ABSTRACT_MAP_OBJ__

namespace poplib
{
/** Base class for all populous objects on the map. */
class AbstractMapObj
{
public:
    /**  Which tribe is the owner of the object. */
    enum Owner {BLUE = 1, RED, YELLOW, GREEN};
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
    /** Constructor.
    @param type Type of the object.
    @param owner What tribe is the owner of this object.
    @param posx X position of the object on the map.
    @param posy Y position of the object on the map.
    */
    AbstractMapObj ( Type type, Owner owner,int posx = 0, int posy = 0 ): mtype(type), mposx(posx), mposy(posy), mowner(owner)
    {

    }
    virtual ~AbstractMapObj() {}
    /** Returns type of the object */
    virtual Type type() const { return mtype; }
    /** Returns tribe who is the owner of the object. */
    Owner owner() const { return mowner; }
    /** Set new owner of the object.
    @param own New tribe who is the owner.
    */
    void setOwner(Owner own) { mowner = own; }
    /** Returns X position of the object on the map. */
    int positionx() const { return mposx; }
    /** Returns Y position of the object on the map. */
    int positiony() const { return mposy; }
    /** Set new position of the object on the map. */
    void setPosition ( int posX, int posY ) { mposx = posX; mposy = posY; }
    /** Used to load object from the file. This function uses virtual method std::ostream& saveObject ( std::ostream& os )
    	to provide different behavour for triggers, discoveries and scenery objects. */
    friend std::ostream& operator<<(std::ostream& os, const AbstractMapObj& obj) { return obj.saveObject(os); }
    /** Used to save object to the file. This function uses virtual method std::istream& loadObject ( std::istream& is )
    	to provide defferent behavour for triggers, discoveries and scenery objects. */
    friend std::istream& operator>>(std::istream& is, AbstractMapObj& obj) { return obj.loadObject(is); }

protected:
    /** Type can't be changed when object is already created. */
    void setType ( Type type ) { mtype = type; }
    /** Saves object binary to the stream.
    	@param os Stream used to save the object.*/
    virtual std::ostream& saveObject ( std::ostream& os ) const = 0;
    /** Loades binary object from the stream
    @param is Stream used to load the object. */
    virtual std::istream& loadObject ( std::istream& is ) = 0;

private:
    Type mtype;
    Owner mowner;
    int mposx, mposy;
};

} // namespace poplib

#endif // _H_POPLIB_ABSTRACT_MAP_OBJ__
