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

#include <string>
#include <iostream>
#include <fstream>

#include "MapHeader.h"

using poplib::MapHeader;

void testHeader(const MapHeader& h)
{
    std::cout << "\n\nAvailable spells:\n";
    if ( h.isEnabled ( MapHeader::BLAST ) )
        std::cout << "blast,";
    if ( h.isEnabled ( MapHeader::CONVERT ) )
        std::cout << " convert,";
    if ( h.isEnabled ( MapHeader::LIGHTNING ) )
        std::cout << " ligthning,";
    if ( h.isEnabled ( MapHeader::TORNADO ) )
        std::cout << " tornado,";
    if ( h.isEnabled ( MapHeader::EARTHQUAKE ) )
        std::cout << " earthquake,";
    if ( h.isEnabled ( MapHeader::ERODE ) )
        std::cout << " erode,";
    if ( h.isEnabled ( MapHeader::SWARM ) )
        std::cout << " swarm,";
    if ( h.isEnabled ( MapHeader::SWAMP ) )
        std::cout << " swamp,";
    if ( h.isEnabled ( MapHeader::GHOST_ARMY ) )
        std::cout << " ghost_army,";
    if ( h.isEnabled ( MapHeader::LANDBRIDGE ) )
        std::cout << " landbridge,";
    if ( h.isEnabled ( MapHeader::FLATTEN ) )
        std::cout << " flatten,";
    if ( h.isEnabled ( MapHeader::FIRESTORM ) )
        std::cout << " firestorm,";
    if ( h.isEnabled ( MapHeader::VOLCANO ) )
        std::cout << " volcano,";
    if ( h.isEnabled ( MapHeader::ANGEL_OF_DEATH ) )
        std::cout << " angel_of_death,";
    if ( h.isEnabled ( MapHeader::HYPNOTISE ) )
        std::cout << " hypnotise,";
    if ( h.isEnabled ( MapHeader::INVISIBILITY ) )
        std::cout << " invisibility,";
    if ( h.isEnabled ( MapHeader::MAGICAL_SHIELD ) )
        std::cout << " magical_shield,";

    std::cout << "\nChargable spells:\n";
    if ( h.isCharging(MapHeader::BLAST))
        std::cout << "blast,";
    if ( h.isCharging ( MapHeader::CONVERT ) )
        std::cout << " convert,";
    if ( h.isCharging ( MapHeader::LIGHTNING ) )
        std::cout << " ligthning,";
    if ( h.isCharging ( MapHeader::TORNADO ) )
        std::cout << " tornado,";
    if ( h.isCharging ( MapHeader::EARTHQUAKE ) )
        std::cout << " earthquake,";
    if ( h.isCharging ( MapHeader::ERODE ) )
        std::cout << " erode,";
    if ( h.isCharging ( MapHeader::SWARM ) )
        std::cout << " swarm,";
    if ( h.isCharging ( MapHeader::SWAMP ) )
        std::cout << " swamp,";
    if ( h.isCharging ( MapHeader::GHOST_ARMY ) )
        std::cout << " ghost_army,";
    if ( h.isCharging ( MapHeader::LANDBRIDGE ) )
        std::cout << " landbridge,";
    if ( h.isCharging ( MapHeader::FLATTEN ) )
        std::cout << " flatten,";
    if ( h.isCharging ( MapHeader::FIRESTORM ) )
        std::cout << " firestorm,";
    if ( h.isCharging ( MapHeader::VOLCANO ) )
        std::cout << " volcano,";
    if ( h.isCharging ( MapHeader::ANGEL_OF_DEATH ) )
        std::cout << " angel_of_death,";
    if ( h.isCharging ( MapHeader::HYPNOTISE ) )
        std::cout << " hypnotise,";
    if ( h.isCharging ( MapHeader::INVISIBILITY ) )
        std::cout << " invisibility,";
    if ( h.isCharging ( MapHeader::MAGICAL_SHIELD ) )
        std::cout << " magical_shield,";

    std::cout << "\n\navailable buildings:\n" ;
    if ( h.isEnabled ( MapHeader::HUT ) )
        std::cout << "hut,";
    if ( h.isEnabled ( MapHeader::GUARD_TOWER ) )
        std::cout << " guard_tower,";
    if ( h.isEnabled ( MapHeader::TEMPLE ) )
        std::cout << " temple,";
    if ( h.isEnabled ( MapHeader::SPY_HUT ) )
        std::cout << " spy_training_hut,";
    if ( h.isEnabled ( MapHeader::WARRIOR_HUT ) )
        std::cout << " warrior_training_hut,";
    if ( h.isEnabled ( MapHeader::FIREWARRIOR_HUT ) )
        std::cout << " firewarrior_hut,";
    if ( h.isEnabled ( MapHeader::BOAT_HOUSE ) )
        std::cout << " boat_house,";
    if ( h.isEnabled ( MapHeader::BALLOON_HUT ) )
        std::cout << " baloon_hut,";

    std::cout << "\n\nactivated properties: ";
    if ( h.isEnabled ( MapHeader::NO_GUEST_SPELLS ) )
        std::cout << " no_guest_spells,";
    if ( h.isEnabled ( MapHeader::FOG_OF_WAR ) )
        std::cout << " fog_of_war,";
    if ( h.isEnabled ( MapHeader::GOD_MODE ) )
        std::cout << " god_mode,";

    std::cout << "\n\nmax tribes: " << h.maxTribes();

    std::cout << "\n\nAllies:" << std::endl;
    std::cout << "BLUE -";
    if ( h.isAllied ( MapHeader::BLUE, poplib::ALLY_BLUE ) )
        std::cout << " blue,";
    if ( h.isAllied ( MapHeader::BLUE, poplib::ALLY_RED ) )
        std::cout << " red,";
    if ( h.isAllied ( MapHeader::BLUE, poplib::ALLY_YELLOW ) )
        std::cout << " yellow,";
    if ( h.isAllied ( MapHeader::BLUE, poplib::ALLY_GREEN ) )
        std::cout << " green,";

    std::cout << "\nRED -";
    if ( h.isAllied ( MapHeader::RED, poplib::ALLY_BLUE ) )
        std::cout << " blue,";
    if ( h.isAllied ( MapHeader::RED, poplib::ALLY_RED ) )
        std::cout << " red,";
    if ( h.isAllied ( MapHeader::RED, poplib::ALLY_YELLOW ) )
        std::cout << " yellow,";
    if ( h.isAllied ( MapHeader::RED, poplib::ALLY_GREEN ) )
        std::cout << " green,";

    std::cout << "\nYELLOW -";
    if ( h.isAllied ( MapHeader::YELLOW, poplib::ALLY_BLUE ) )
        std::cout << " blue,";
    if ( h.isAllied ( MapHeader::YELLOW, poplib::ALLY_RED ) )
        std::cout << " red,";
    if ( h.isAllied ( MapHeader::YELLOW, poplib::ALLY_YELLOW ) )
        std::cout << " yellow,";
    if ( h.isAllied ( MapHeader::YELLOW, poplib::ALLY_GREEN ) )
        std::cout << " green,";

    std::cout << "\nGREEN -";
    if ( h.isAllied ( MapHeader::GREEN, poplib::ALLY_BLUE ) )
        std::cout << " blue,";
    if ( h.isAllied ( MapHeader::GREEN, poplib::ALLY_RED ) )
        std::cout << " red,";
    if ( h.isAllied ( MapHeader::GREEN, poplib::ALLY_YELLOW ) )
        std::cout << " yellow,";
    if ( h.isAllied ( MapHeader::GREEN, poplib::ALLY_GREEN ) )
        std::cout << " green,";
    std::cout << std::endl;
}

int main ( int argc, const char* argv[] )
{
    MapHeader h ( "levl2131.hdr" );

    testHeader(h);

    std::cout << "\n\n=== COMPACT SAVE & LOAD TEST ===\n\n";

    std::ofstream fout;
    fout.open ( "temp_compact.hdr", std::ios_base::out );
    h.saveHeaderCompactForm(fout);
    fout.close();
    std::cout << "Compact header copy saved to the file: temp_compact.hdr\n\n";
    std::ifstream fin;
    fin.open("temp_compact.hdr", std::ios_base::in);
    h.loadHeaderCompactForm(fin);

    testHeader(h);

    return 0;
}
