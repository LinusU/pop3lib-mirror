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

#include "MapDat.h"
#include "MapObject.h"
#include "MapObjDiscovery.h"
#include "MapObjTrigger.h"

int main ( int argc, const char* argv[] )
{
    std::string filePath ( "levl2131.dat" ); // map to load objects from
    poplib::MapDat mapDat(filePath);

    poplib::MapDat::objList* objects = mapDat.objects();
    poplib::MapDat::objList::const_iterator it;
    int i;
    for (it = objects->begin(), i = 1; it != objects->end(); ++it, ++i)
    {
        poplib::MapObjGeneric* obj = *it;
        std::cout << "\n " << i << ")   type: ";
        switch (obj->type())
        {
        case poplib::MapObjGeneric::FOLLOWER:
            std::cout << "FOLLOWER";
            std::cout << "; model: " << static_cast<poplib::MapObjFollower *>(obj)->model();
            break;
        case poplib::MapObjGeneric::BUILDING:
            std::cout << "BUILDING";
            std::cout << "; model: " << static_cast<poplib::MapObjBuilding *>(obj)->model();
            break;
        case poplib::MapObjGeneric::CREATURE:
            std::cout << "CREATURE";
            std::cout << "; model: " << static_cast<poplib::MapObjCreature *>(obj)->model();
            break;
        case poplib::MapObjGeneric::VEHICLE:
            std::cout << "VEHICLE";
            std::cout << "; model: " << static_cast<poplib::MapObjVehicle *>(obj)->model();
            break;
        case poplib::MapObjGeneric::SCENERY:
            std::cout << "SCENERY";
            std::cout << "; model: " << static_cast<poplib::MapObjScenery *>(obj)->model();
            break;
        case poplib::MapObjGeneric::GENERAL:
            std::cout << "GENERAL";
            std::cout << "; model: " << static_cast<poplib::MapObjGeneral *>(obj)->model();
            break;
        case poplib::MapObjGeneric::EFFECT:
            std::cout << "EFFECT";
            std::cout << "; model: " << static_cast<poplib::MapObjEffect *>(obj)->model();
            break;
        case poplib::MapObjGeneric::SHOT:
            std::cout << "SHOT";
            std::cout << "; model: " << static_cast<poplib::MapObjShot *>(obj)->model();
            break;
        case poplib::MapObjGeneric::SHAPE:
            std::cout << "SHAPE";
            std::cout << "; model: " << static_cast<poplib::MapObjShape *>(obj)->model();
            break;
        case poplib::MapObjGeneric::INTERNAL:
            std::cout << "INTERNAL";
            std::cout << "; model: " << static_cast<poplib::MapObjInternal *>(obj)->model();
            break;
        case poplib::MapObjGeneric::SPELL:
            std::cout << "SPELL";
            std::cout << "; model: " << static_cast<poplib::MapObjSpell *>(obj)->model();
            break;
        }

        std::cout << "; owner: ";
        switch (obj->owner())
        {
        case poplib::MapObjGeneric::BLUE:
            std::cout << "BLUE";
            break;
        case poplib::MapObjGeneric::RED:
            std::cout << "RED";
            break;
        case poplib::MapObjGeneric::YELLOW:
            std::cout << "YELLOW";
            break;
        case poplib::MapObjGeneric::GREEN:
            std::cout << "GREEN";
            break;
        case poplib::MapObjGeneric::NEUTRAL:
            std::cout << "NEUTRAL";
            break;
        default:
            std::cout << obj->owner();
        }
        std::cout << "; posx: " << static_cast<int>(obj->posx()) << ", posy: " << static_cast<int>(obj->posy());
    }

    std::cout << std::endl;

    return 0;
}
