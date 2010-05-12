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

#include <bitset>
#include <list>

#include "bits/mapHeaderBits.h"
#include "Marker.h"

namespace poplib
{
/** Represents file mapName.hdr. Loads / saves map properties. */
class MapHeader
{
public:
    enum Spell {BLAST = 2, LIGHTNING, TORNADO, SWARM, INVISIBILITY, HYPNOTISE, FIRESTORM, GHOST_ARMY, ERODE,
                SWAMP, LANDBRIDGE, ANGEL_OF_DEATH, EARTHQUAKE, FLATTEN, VOLCANO, CONVERT, MAGICAL_SHIELD = 19
               };
    enum Building {HUT = 1, GUARD_TOWER = 3, TEMPLE, SPY_HUT, WARRIOR_HUT, FIREWARRIOR_HUT,
                   BOAT_HOUSE = 13, BALLOON_HUT = 15
                  };
    enum Property {NO_GUEST_SPELLS = 5, GOD_MODE, FOG_OF_WAR};
    enum Tribe {BLUE = 0, RED, YELLOW, GREEN};
    /** Bit mask enum. */
    typedef _Allies Allies;
    typedef std::list<Marker> markerList;
    /** Constructor. By default there is no allies, special properties are disabled, spells and buildings
    	*	are all enabled, all spells are charging at start.
    	*/
    MapHeader();
    /** Constructor. Loads the header properties from the file. */
    explicit MapHeader ( const std::string& fileName );
    /** Copy constructor. */
    MapHeader ( const MapHeader& mapHdr );
    MapHeader& operator= ( const MapHeader& mapHdr );
    virtual ~MapHeader();
    /** Loades map header details from the file.
    @param fileName Path to the file where header details are stored. File usualy has *.hdr extension.
    */
    void loadHeader ( const std::string& fileName );
    /** Saves map header details to the file.
    @param fileName Path to the file where header details should be stored. File should have *.hdr extension.
    */
    void saveHeader ( const std::string& fileName ) const;
    /** Saves map header details using compact form. Suitable for sending maps over the internet. */
    virtual std::ostream& toCompactForm ( std::ostream& os ) const;
    /** Loades map header details from compact form. */
    virtual std::istream& fromCompactForm ( std::istream& is );
    /** Returns true if spell is chargin at start. */
    bool isCharging ( Spell spell ) const { return mspellsNotCharging[spell] == 0; }
    /** Enables or disables spell charging at start. */
    void setCharging ( Spell spell, bool enabled ) { mspellsNotCharging[spell] = !enabled; }
    /** Enables or disables all spells charging at start. */
    void setAllCharging(bool charge);
    /** Sets allies for the tribe.
    @param ally Bitmask with allies.
    @remarks You can use | operator to provide more allies.
    */
    void setAlly ( Tribe tribe, Allies ally );
    /** Checks if tribe is allied with pointed tribes.
    @param ally Bitmask with allies.
    @remarks You can use | operator to provide more allies.
    */
    bool isAllied ( Tribe tribe, Allies ally );
    /** Reset allies, no tribes will be allied together. */
    void resetAllies();
    /** Sets maximum tribes amount available for this map.
    @param maxTribes Must be positive and smaller than 5.
    */
    void setMaxTribes(int maxTribes) { if(maxTribes > 0 && maxTribes < 5) mmaxTribes = maxTribes; }
    /** Returns maximum tribes amount available for this map. */
    int maxTribes() const { return mmaxTribes; }
    /** Enables / Disables spell on the map. */
    void setEnabled ( Spell spell, bool enabled ) { mspells.set(spell, enabled); }
    /** Enables / Disables building on the map. */
    void setEnabled ( Building building, bool enabled ) { mbuildings.set(building, enabled); }
    /** Enables / Disables property on the map. */
    void setEnabled ( Property property, bool enabled ) { mproperties.set(property, enabled); }
    /** Returns true if spell is enabled. */
    bool isEnabled ( Spell spell ) { return mspells.test(spell); }
    /** Returns true if building is enabled. */
    bool isEnabled ( Building building ) { return mbuildings.test(building); }
    /** Returns true if property is enabled. */
    bool isEnabled ( Property property ) { return  mproperties.test(property); }
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
    /** Returns list of the markers on the map. Map usualy contain 256 markers and their are used
    by AI scripts. */
    markerList* markers() { return mmarkers; }
    // TODO add methods, enums for landscape, tree style and markers

private:
    static const int TRIBES = 4; // max tribes

    std::bitset<24> mspells;
    std::bitset<16> mbuildings;
    std::bitset<24> mspellsNotCharging;
    std::bitset<8> mproperties;
    std::bitset<8> mallies[TRIBES];
    char maiScripts[TRIBES - 1];
    int mlandscape;
    int mtreeStyle;
    char mmaxTribes; 
    markerList* mmarkers;

    void copy ( const MapHeader& mapHdr );
    void defaultValues();
};

} // namespace poplib

#endif // _H_POPLIB_MAP_HEADER__
