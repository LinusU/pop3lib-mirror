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


#ifndef _H_DMKP32_POPULOUS_OBJECT_CONSTANTS_HEADER__
#define _H_DMKP32_POPULOUS_OBJECT_CONSTANTS_HEADER__

//#define SZ_RED "Red"
//#define SZ_BLUE "Blue"
//#define SZ_YELLOW "Yellow"
//#define SZ_GREEN "Green"
#define SZ_RED "Dakini"
#define SZ_BLUE "Ikani"
#define SZ_YELLOW "Chumara"
#define SZ_GREEN "Matak"
#define SZ_WILD "Wild"
#define SZ_NEUTRAL "Neutral"
#define TRIBE_BLUE 0
#define TRIBE_RED 1
#define TRIBE_YELLOW 2
#define TRIBE_GREEN 3
#define TRIBE_WILD 0xFF
#define TRIBE_NEUTRAL 0xAA

#define SZ_UNKNOWN "Unknown"

//Indices of the arrays
#define DISCOVERY_BUILDING_INDEX 0
#define DISCOVERY_SPELL_INDEX 2
#define DISCOVERY_MANA_INDEX 1

//Value of the discoveries array.
#define DISCOVERY_BUILDING 2
#define DISCOVERY_SPELL 11
#define DISCOVERY_MANA 6

//Number of elements of the arrays.
#define NUM_D_AVAILABILITIES 3
#define NUM_D_TYPES 3
#define NUM_D_BUILDINGS_MODELS 10
#define NUM_D_SPELLS_MODELS 20
#define NUM_N_GROUPS_MODELS 8
#define NUM_N_PERSONS_MODELS 8
#define NUM_N_BUILDINGS_MODELS 12
#define NUM_N_CREATURE_MODELS 1
#define NUM_N_VEHICLES_MODELS 4
#define NUM_N_SCENERY_MODELS 19
#define NUM_N_GENERAL_MODELS 4
#define NUM_N_EFFECT_MODELS 93
#define NUM_N_SPELLS_MODELS 20
#define NUM_N_TEAMS 6

#define NUM_T_TYPES 6

//Values of the elements of the groups array.
#define GROUP_PERSONS 1
#define GROUP_BUILDINGS 2
#define GROUP_CREATURE 3
#define GROUP_VEHICLE 4
#define GROUP_SCENERY 5
#define GROUP_GENERAL 6
#define GROUP_EFFECT 7
#define GROUP_SPELL 11

//Indices of the elements of the arrays.
#define GROUP_PERSONS_INDEX 0
#define GROUP_BUILDINGS_INDEX 1
#define GROUP_CREATURE_INDEX 2
#define GROUP_VEHICLE_INDEX 3
#define GROUP_SCENERY_INDEX 4
#define GROUP_GENERAL_INDEX 5
#define GROUP_EFFECT_INDEX 6
#define GROUP_SPELL_INDEX 7

//Indices of the elements of the arrays.
#define TRIBE_BLUE_INDEX 0
#define TRIBE_RED_INDEX 1
#define TRIBE_YELLOW_INDEX 2
#define TRIBE_GREEN_INDEX 3
#define TRIBE_WILD_INDEX 4
#define TRIBE_NEUTRAL_INDEX 5

//Values of the trigger types array, also the indices of the values :P
#define TRIGGER_STONEHEAD 0
#define TRIGGER_TIMED 1
#define TRIGGER_PLAYER_DEATH 2
#define TRIGGER_OBELISK 3
#define TRIGGER_VOK 4
#define TRIGGER_GARGOYLE 5

#define MAX_TRIGGER_LINKS 10

namespace poplib
{

const char* T_Types[NUM_T_TYPES] = { "Stonehead", "Timed", "Unknown", "Obelisk", "Vault of Knowledge", "Gargoyle" };
const unsigned char T_Types_Values[NUM_T_TYPES] = { TRIGGER_STONEHEAD, TRIGGER_TIMED, TRIGGER_PLAYER_DEATH, TRIGGER_OBELISK, TRIGGER_VOK, TRIGGER_GARGOYLE};

const char* D_Availabilities[NUM_D_AVAILABILITIES] = { "Permanent:V.O.K/Obelisk", "Level:Unknown", "One-Shot:Stonehead" };
const unsigned char D_Availabilities_Values[NUM_D_AVAILABILITIES] = { 1, 2, 3 };

const char* D_Types[NUM_D_TYPES] = { "Building", "Mana", "Spell" };
const unsigned char D_Types_Values[NUM_D_TYPES] = { DISCOVERY_BUILDING, DISCOVERY_MANA, DISCOVERY_SPELL};

const char* D_Buildings_Models[NUM_D_BUILDINGS_MODELS] = { "Small Hut", "Medium Hut", "Large Hut", "Guard Tower", "Temple", "Spy Training Hut", "Warrior Training Hut", "Firewarrior Training Hut", "Boat Hut", "Balloon Hut" };
const unsigned char D_Buildings_Models_Values[NUM_D_BUILDINGS_MODELS] = { 1, 2, 3, 4, 5, 6, 7, 8, 13, 15 };
const char* D_Spells_Models[NUM_D_SPELLS_MODELS] = { "Blast", "Lightning", "Tornado", "Swarm", "Invisibility", "Hypnotise", "Firestorm", "Ghost Army", "Erode", "Swamp", "Landbridge", "Angel of Death", "Earthquake", "Flatten", "Volcano", "Convert", "Armageddon", "Magical Shield", "Bloodlust", "Teleport" };
const unsigned char D_Spells_Models_Values[NUM_D_SPELLS_MODELS] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };

const unsigned char D_Mana_Model_Value = 5;

const char* N_GROUPS_Models[NUM_N_GROUPS_MODELS] = { "Followers", "Buildings", "Creature", "Vehicle", "Scenery", "General", "Effect", "Spell" };
const unsigned char N_GROUPS_Models_Values[NUM_N_GROUPS_MODELS] = { GROUP_PERSONS, GROUP_BUILDINGS, GROUP_CREATURE, GROUP_VEHICLE, GROUP_SCENERY, GROUP_GENERAL, GROUP_EFFECT, GROUP_SPELL };

const char* N_PERSONS_Models[NUM_N_PERSONS_MODELS] = { "Wildman", "Brave", "Warrior", "Preacher", "Spy", "Firewarrior", "Shaman", "Angel of Death" };
const unsigned char N_PERSONS_Models_Values[NUM_N_PERSONS_MODELS] = { 1, 2, 3, 4, 5, 6, 7, 8 };
const char* N_BUILDINGS_Models[NUM_N_BUILDINGS_MODELS] = { "Small Hut", "Medium Hut", "Large Hut", "Guard Tower", "Temple", "Spy Training Hut", "Warrior Training Hut", "Firewarrior Training Hut", "Boat Hut", "Balloon Hut", "Vault of Knowledge", "Prison" };
const unsigned char N_BUILDINGS_Models_Values[NUM_N_BUILDINGS_MODELS] = { 1, 2, 3, 4, 5, 6, 7, 8, 13, 15, 18, 19 };
const char* N_CREATURE_Models[NUM_N_CREATURE_MODELS] = { "Eagle" };
const unsigned char N_CREATURE_Models_Values[NUM_N_CREATURE_MODELS] = { 1 };
const char* N_VEHICLES_Models[NUM_N_VEHICLES_MODELS] = { "Boat 1", "Boat 2", "Balloon 1", "Balloon 2" };
const unsigned char N_VEHICLES_Models_Values[NUM_N_VEHICLES_MODELS] = { 1, 2, 3, 4 };
const char* N_SCENERY_Models[NUM_N_SCENERY_MODELS] = { "Tree 1", "Tree 2", "Tree 3", "Tree 4", "Tree 5", "Tree 6", "Plant 1", "Plant 2", "Stonehead", "Fire", "Wood-Pile", "RS Site Pillar", "Rock", "Portal", "Island", "Bridge", "Dormant Tree", "Top Level Scenery", "Sub Level Scenery" };
const unsigned char N_SCENERY_Models_Values[NUM_N_SCENERY_MODELS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
const char* N_GENERAL_Models[NUM_N_GENERAL_MODELS] = { "Discovery", "Trigger", "Building-Addon", "Light" };
const unsigned char N_GENERAL_Models_Values[NUM_N_GENERAL_MODELS] = { 2, 6, 9, 1 };

const char* N_EFFECT_Models[NUM_N_EFFECT_MODELS] = {"Simple Blast", "Sprite Circles", "Smoke", "Lightning Elem", "Burn Cell Obstacles", "Flatten Land", "Move RS Pillar", "Prepare RS Land", "Sphere Explode", "Fireball", "Firecloud", "Ghost Army", "Invisibility", "Explode Bldg Partial", "Volcano", "Hypnotism", "Lightning Bolt", "Swamp", "Angel Of Death", "Tornado","Swarm", "Firestorm", "Erosion", "Landbridge", "Wrath of God", "Earthquake", "Fly Thingummy", "Sphere Explode and Fire", "Big Fire", "Lightning", "Flatten", "General", "Shape Sparkle", "Lava Flow", "Volcano Explosions", "Purify Land", "Unpurify Land",
        "Explosion 1", "Explosion 2", "Lava Square", "WW Element", "Lightning Strand", "WW Dust", "Raise Land", "Lower Land", "Hill", "Valley", "Place Tree", "Rise", "Dip", "Rain Rock Debris", "Clear Mapwho", "Place Shaman", "Place Wild", "Bldg Smoke", "Much Simpler Blast" , "Tumbling Branch", "Conversion Flash", "Hypnosis Flash", "Sparkle", "Small Sparkle", "Explosion 3", "Rock Explosion", "Lava Gloop", "Splash 6", "Smoke Cloud", "Smoke Cloud Constant", "Fireball 2","Ground Shockwave", "Orbiter", "Big Sparkle", "Meteor", "Convert Wild", "Bldg Smoke 2 Full",
        "Bldg Smoke 2 Partial", "Bldg Damaged Smoke", "Delete RS Pillars", "Spell Blast", "Firestorm Smoke", "Player Dead", "Reveal Fog Area", "Shield", "Boat Hut Repair", "Reedy Grass", "Swamp Mist", "Armageddon", "Bloodlust", "Teleport", "Atlantis Set", "Atlantis Invoke", "Statue To Aod", "Fill One Shot","Fire Roll Elem"
                                                   };
const unsigned char N_EFFECT_Models_Values[NUM_N_EFFECT_MODELS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93 };

const char* N_SPELLS_Models[NUM_N_SPELLS_MODELS] = { "Blast", "Lightning", "Tornado", "Swarm", "Invisibility", "Hypnotise", "Firestorm", "Ghost Army", "Erode", "Swamp", "Landbridge", "Angel of Death", "Earthquake", "Flatten", "Volcano", "Convert", "Armageddon", "Magical Shield", "Bloodlust", "Teleport" };
const unsigned char N_SPELLS_Models_Values[NUM_N_SPELLS_MODELS] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };


const char* N_TEAMS[NUM_N_TEAMS] = { SZ_BLUE, SZ_RED, SZ_YELLOW, SZ_GREEN, SZ_WILD, SZ_NEUTRAL };
const unsigned char N_TEAMS_VALUES[NUM_N_TEAMS] = { TRIBE_BLUE, TRIBE_RED, TRIBE_YELLOW, TRIBE_GREEN, TRIBE_WILD, TRIBE_NEUTRAL };

}; // namespace poplib

#endif /* _H_DMKP32_POPULOUS_OBJECT_CONSTANTS_HEADER__ */
