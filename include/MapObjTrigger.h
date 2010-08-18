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

#ifndef _H_POPLIB_MAP_OBJ_TRIGGER__
#define _H_POPLIB_MAP_OBJ_TRIGGER__

#include "MapObject.h"

namespace poplib
{

class MapObjTrigger : public MapObject<AbstractMapObj::ModelGeneral>
{
    // TODO add more things to triggers
    enum TriggerType {PROXIMITY = 0, // Stone Head or Totem Pole
                      TIMED, // Usually reoccurring automatic things
                      PLAYER_DEATH,
                      SHAMAN_PROXIMITY, // Obelisk
                      LIBRARY, // Vault of Knowledge
                      SHAMAN_AOD // Gargoyle
                     };

    MapObjTrigger(TriggerType trigType, Owner owner, int posx, int posy);
    virtual ~MapObjTrigger();

    TriggerType triggerType() const { return mtrigType; }
    void setTriggerType(TriggerType trigType) { mtrigType = trigType; }

protected:
    virtual std::ostream& saveObject ( std::ostream& os ) const;
    virtual std::istream& loadObject ( std::istream& is );

private:
    TriggerType mtrigType;
};

} // namespace poplib

#endif // _H_POPLIB_MAP_OBJ_TRIGGER__
