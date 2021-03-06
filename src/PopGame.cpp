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

#include "Ip.h"
#include "PopGame.h"
#include "Mappack.h"

namespace poplib
{

PopGame::PopGame() : mdir("")
{

}

PopGame::PopGame ( const std::string& dir ) : mdir(dir)
{

}

PopGame::~PopGame()
{

}

#if defined(PLATFORM_WIN32)
bool PopGame::startMultiplayer ( const std::string& playerName, Ip localIp, Ip ExternIp )
{
    return false;
}
#endif

void PopGame::loadMappack(Mappack* mappack)
{
    // TODO loadMappack() method in PopGame class
}

void PopGame::restoreMaps()
{
    // TODO restoreMaps() method in PopGame class
}

} // namespace poplib
