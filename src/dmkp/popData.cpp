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

#include <cstring>

#include "popData.h"

namespace poplib
{
	
void popData::Import ( popData* pHdr )
{
    //Make a copy of the header and store it inside here

    memcpy ( LevelName, pHdr->LevelName, sizeof ( LevelName ) );
    memcpy ( &AvailableSpells, &pHdr->AvailableSpells, sizeof ( SPELLS ) );
    memcpy ( &AvailableBuildings, &pHdr->AvailableBuildings, sizeof ( BUILDINGS ) );
    memcpy ( &SpellsNotCharging, &pHdr->SpellsNotCharging, sizeof ( SPELLS ) );
    NumPlayers = pHdr->NumPlayers;
    RedScript = pHdr->RedScript;
    YellowScript = pHdr->YellowScript;
    GreenScript = pHdr->GreenScript;
    memcpy ( &Allies, &pHdr->Allies, sizeof ( ALLIANCES ) );
    LandScape = pHdr->LandScape;
    TreeStyle = pHdr->TreeStyle;
    memcpy ( &LevelFlags, &pHdr->LevelFlags, sizeof ( FLAGS ) );

    for ( int i = 0; i < 256; i++ )
    {
        Markers[i] = pHdr->Markers[i];
    }
}

} // namespace poplib