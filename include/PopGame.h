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

#ifndef _H_POPLIB_POPGAME__
#define _H_POPLIB_POPGAME__

#include <string>

#include "global.h"

namespace poplib
{
class Ip;
class Mappack;

class PopGame
{
public:
    enum ResultState { FINISHED_SUCCESSFUL, RESYNC, CRASHED, UNKNOWN };

    PopGame();
    explicit PopGame ( const std::string& gameDirectory );
    virtual ~PopGame();
#if defined(PLATFORM_WIN32)
    // TODO multiplayer game starting using win api, function should return process handler
    bool startMultiplayer ( const std::string& playerName, Ip localIp, Ip ExternIp = Ip() );
#endif
    void loadMappack(Mappack* mappack);
    void restoreMaps();
    std::string directory() const { return mdir; }
    void setDirectory( const std::string& dir ) { mdir = dir; }

private:
    std::string mdir;
    ResultState mstate;
};

} // namespace poplib

#endif // _H_POPLIB_POPGAME__
