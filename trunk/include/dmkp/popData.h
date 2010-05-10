/*
Copyright (C) 2009 Populous Mana Source Development Team

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

#ifndef _H_DMKP32_POPULOUS_STRUCTS__
#define _H_DMKP32_POPULOUS_STRUCTS__

namespace poplib
{

struct SPELLS
{
    bool Blast, Lightning, Tornado, Swarm, Invisibility,
    Hypnotise, Firestorm, GhostArmy, Erode, Swamp,
    Landbridge, AngelOfDeath, Earthquake, Flatten,
    Volcano, Convert, Armageddon, MagicShield, Bloodlust,
    Teleport;
};

struct BUILDINGS
{
    bool Hut, Tower, Temple, SpyHut, WarriorHut,
    FirewarriorHut, BoatHut, BalloonHut;
};

struct ALLIANCES
{
    bool BR, BY, BG, RY, RG, YG;
};

struct FLAGS
{
    bool God, Fog, NoGuestSpells;
};

enum ObjBank
{
    Style1 = 00, Style2 = 02, Style3 = 03, Style4 = 04, Style5 = 05, Style6 = 06, Style7 = 07,
};

struct MARKER
{
    unsigned char x, y;
};

//NB: The members of this class are not in order of how they appear in the file, use the LoadHDR function in HDR_Functions.h to load
//a HDR file
class popData
{

public:
    unsigned char LevelName[32];
    SPELLS AvailableSpells;
    BUILDINGS AvailableBuildings;
    SPELLS SpellsNotCharging;
    unsigned char NumPlayers,
    RedScript,
    YellowScript,
    GreenScript;

    ALLIANCES Allies;
    unsigned char LandScape;
    ObjBank TreeStyle;
    FLAGS LevelFlags;
    MARKER Markers[256];


    void Import ( popData* pHdr );
};

}; // namespace poplib

#endif /* _H_DMKP32_POPULOUS_STRUCTS__ */
