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

#ifndef _H_POPLIB_MAP_HEADER__
#define _H_POPLIB_MAP_HEADER__

#include <iostream>

#include "global.h"
#include "bits/mapBits.h"

namespace poplib
{
/** Represents file mapName.hdr. Loads / saves map properties. */
class MapHeader
{
public:
    enum Spell {BLAST = 2, LIGHTNING, TORNADO, SWARM, INVISIBILITY, HYPNOTISE, FIRESTORM, GHOST_ARMY, ERODE,
                SWAMP, LANDBRIDGE, ANGEL_OF_DEATH, EARTHQUAKE, FLATTEN, VOLCANO, CONVERT, MAGICAL_SHIELD = 19, NUMB_OF_SPELLS = 20 };
    enum Building {HUT = 1, GUARD_TOWER = 3, TEMPLE, SPY_HUT, WARRIOR_HUT, FIREWARRIOR_HUT,
                   BOAT_HOUSE = 13, BALLOON_HUT = 15, NUMB_OF_BUILDINGS = 16};
    enum Property {FOG_OF_WAR = 0, GOD_MODE, FORCE_640_x_480, FORGE_WORLD, NO_GUEST_SPELLS = 4, NO_OF_PROPERTIES = 5 };
    enum Tribe {BLUE = 0, RED, YELLOW, GREEN, NUMB_OF_TRIBES = 4};

#pragma pack(push, 1) /* set alignment to 1 byte boundary */
    typedef struct _Marker
    {
        SBYTE x, y;
    } Marker;
#pragma pack(pop) /* restore original alignment from stack */

    /** Bit mask enum. */
    typedef _Allies Allies;
    /** Constructor. By default there is no allies, special properties are disabled, spells and buildings
    * are all enabled, all spells are charging at start.
    */
    MapHeader();
    /** Constructor. Loads the header properties from the file. */
    explicit MapHeader ( const std::string& fileName );
    virtual ~MapHeader();
    /** Loades map header details from the file.
    @param fileName Path to the file where header details are stored. File usualy has *.hdr extension.
    */
    void loadHeader ( const std::string& fileName );
    /** Saves map header details to the file.
    @param fileName Path to the file where header details should be stored. File should have *.hdr extension.
    */
    void saveHeader ( const std::string& fileName ) const;
    /** Saves map header details using compact form optimised for being small. It's designed for multiplayer maps 
    thus it doesn't store some informations about single player mode. */
    virtual std::ostream& saveHeaderCompactForm ( std::ostream& os ) const;
    /** Loades map header details using compact form optimised for being small. It's designed for multiplayer maps 
    thus it doesn't store some informations about single player mode. */
    virtual std::istream& loadHeaderCompactForm ( std::istream& is );
    /** Returns true if spell is chargin at start. */
    bool isCharging ( Spell spell ) const { return (mdata.spellsNotCharging & (0x00000001 << spell)) == 0; }
    /** Enables or disables spell charging at start. */
    void setCharging ( Spell spell, bool enabled ) 
    {
        if (enabled)
            mdata.spellsNotCharging |= (0x00000001 << spell);
        else
            mdata.spellsNotCharging &= ((0x00000001 << spell) ^ 0xffffffff);
    }
    /** Enables or disables all spells charging at start. */
    void setAllCharging(bool charge);
    /** Sets allies for the tribe.
    @param ally Bitmask with allies.
    @remarks You can use | operator to provide more allies.
    */
    void setAlly ( Tribe tribe, Allies ally ) { mdata.allies[tribe] = (mdata.allies[tribe] & 0) | ally; }
    /** Checks if tribe is allied with pointed tribes.
    @param ally Bitmask with allies.
    @remarks You can use | operator to provide more allies.
    */
    bool isAllied ( Tribe tribe, Allies ally ) const { return (mdata.allies[tribe] & ally) > 0; }
    /** Reset allies, no tribes will be allied together. */
    void resetAllies();
    /** Sets maximum tribes amount available for this map.
    @param maxTribes Must be positive, bigger than 1 and smaller than 5.
    */
    void setMaxTribes(int maxTribes) { if(maxTribes > 1 && maxTribes < 5) mdata.maxTribes = maxTribes - 1; }
    /** Returns maximum tribes amount available for this map. */
    int maxTribes() const { return mdata.maxTribes + 1; }
    /** Enables / Disables spell on the map. */
    void setEnabled ( Spell spell, bool enabled ) 
    {
        if (enabled)
            mdata.spellsAvailable |= (0x00000001 << spell);
        else
            mdata.spellsAvailable &= ((0x00000001 << spell) ^ 0xffffffff);
    }
    /** Enables / Disables building on the map. */
    void setEnabled ( Building building, bool enabled ) 
    { 
        if (enabled)
            mdata.buildingsAvailable |= (0x00000001 << building);
        else
            mdata.buildingsAvailable &= ((0x00000001 << building) ^ 0xffffffff);
    }
    /** Enables / Disables property on the map. */
    void setEnabled ( Property property, bool enabled ) 
    { 
        if (enabled)
            mdata.properties |= (0x00000001 << property);
        else
            mdata.properties &= ((0x00000001 << property) ^ 0xffffffff);
    }
    /** Returns true if spell is enabled. */
    bool isEnabled ( Spell spell ) const { return (mdata.spellsAvailable & (0x00000001 << spell)) > 0; }
    /** Returns true if building is enabled. */
    bool isEnabled ( Building building ) const { return (mdata.buildingsAvailable & (0x00000001 << building)) > 0; }
    /** Returns true if property is enabled. */
    bool isEnabled ( Property property ) const { return (mdata.properties & (0x00000001 << property)) > 0; }
    /** Enables / Disables all spells. */
    void setEnabledAllSpells(bool enabled);
    /** Enables / Disables all buildings. */
    void setEnabledAllBuildings(bool enabled);
    /** Enables / Disables all properties. */
    void setEnabledAllProperties(bool enabled);
    /** Restrictions common for multiplayer games. Enabled spells: blast, convert, lightning, tornado, swarm,
    *	ghost army, landbridge, flatten, earthquake, erode, firestorm, volcano.
    */
    void setStandardSpells();
    /** Restrictions common for multiplayer games. Enabled buildings: hut, guard tower, warrior hut, firewarrior hut. */
    void setStandardBuildings();
    /** Returns list of the markers on the map. Map always contains exactly 256 markers and their are used
    by AI scripts. */
    Marker* markers() { return mdata.markers; }
    // TODO add more methods

private:

#pragma pack(push, 1) /* set alignment to 1 byte boundary */
    typedef struct _HeaderData
    {
        UDWORD spellsAvailable;
        UDWORD buildingsAvailable;
        UDWORD buildingsAvailableLevel; // TODO what's this?
        UDWORD buildingsAvailableOnce; // buildings which can be build once
        UDWORD spellsNotCharging; // spells which are not charging at the beginning of the game
        UBYTE spellsAvailableOnce[32]; // spells which can be used once
        UWORD vehicles; // types of vehicles available to the player, TODO how to use it?
        UBYTE disableTrainingMana; // TODO what's this?
        UBYTE flags; //unused
        char levelName[32];
        UBYTE maxTribes; // how many tribes are on the map, 0 - one tribe, 1 - two tribes ...
        UBYTE AIscriptIndex[3]; // indexes are in order for red, yellow and green
        UBYTE allies[4]; // teams in single player mode
        UBYTE landscape; // grass, snow etc.
        UBYTE treeStyle; // type of trees
        UBYTE properties; // available in single player mode
        UBYTE padding[1];
        Marker markers[256]; // markers are points (x, y) used in the AI scripts
        SBYTE startCameraX, startCameraY; // (x, y) position of the camera at the beginning of the game
        UWORD startCameraAngle;
    } HeaderData;
#pragma pack(pop) /* restore original alignment from stack */

    HeaderData mdata;
};

} // namespace poplib

#endif // _H_POPLIB_MAP_HEADER__
