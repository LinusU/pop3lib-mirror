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

#ifndef _H_DMKP32_POPULOUS_OBJECT__
#define _H_DMKP32_POPULOUS_OBJECT__

#include "popObjectConstants.h"

namespace poplib
{
class cString;
class Colour;

enum Pop3Obj_TriggerTypes :
unsigned char
{
    T_typeStonehead = TRIGGER_STONEHEAD,
    T_typeTimed = TRIGGER_TIMED,
    T_typePlayerDeath = TRIGGER_PLAYER_DEATH,
    T_typeObelisk = TRIGGER_OBELISK,
    T_typeVaultofKnowledge = TRIGGER_VOK,
    T_typeGargoyle = TRIGGER_GARGOYLE
};

enum Pop3Obj_DiscoveryTypes :
unsigned char
{
    D_typeBuilding = DISCOVERY_BUILDING,
    D_typeSpell = DISCOVERY_SPELL,
    D_typeMana = DISCOVERY_MANA
};

enum Pop3Obj_ByteIndices :
unsigned int
{
    I_0=0, I_1=1, I_2=2, I_3=3,
    I_4=4, I_5=5, I_6=6, I_7=7,
    I_8=8, I_9=9, I_10=10, I_11=11,
    I_12=12, I_13=13, I_14=14, I_15=15,
    I_16=16, I_17=17, I_18=18, I_19=19,
    I_20=20, I_21=21, I_22=22, I_23=23,
    I_24=24, I_25=25, I_26=26, I_27=27,
    I_28=28, I_29=29, I_30=30, I_31=31,
    I_32=32, I_33=33, I_34=34, I_35=35,
    I_36=36, I_37=37, I_38=38, I_39=39,
    I_40=40, I_41=41, I_42=42, I_43=43,
    I_44=44, I_45=45, I_46=46, I_47=47,
    I_48=48, I_49=49, I_50=50, I_51=51,
    I_52=52, I_53=53, I_54=54
    //end

};

enum Pop3Object_T_IDX_INDICES :
unsigned char
{
    IDX_0 = 0, IDX_1 = 1, IDX_2 = 2, IDX_3 = 3, IDX_4 = 4, IDX_5 = 5, IDX_6 = 6, IDX_7 = 7, IDX_8 = 8, IDX_9 = 9 //end
};

class PopObject
{
public:
    unsigned char utype,
    ugroup,
    utribe,
    null1,
    ux,
    null2,
    uy,
    uangle;
    unsigned char uextra[47];

public:
    PopObject();
    PopObject ( PopObject& copyThis );
    PopObject* Clone() const;
    void ImportObject ( const PopObject* object );

    bool IsNormalObject() const;
    bool IsTrigger() const;
    bool IsDiscovery() const;
    bool IsDiscoveryMana() const;
    bool IsEffect() const;
    bool IsEffectLandBridge() const;
    bool IsEffectLightningBolt() const;

    bool IsShaman() const;
    bool IsWildman() const;

    cString szident() const;
    char* ident() const;

    unsigned char* exportObjAsByteArray() const;
    void Delete();
    bool isEmpty() const;

    Colour ARGBTribeColour() const;
    Colour ARGBTribeColourFlash() const;
    Colour ARGBForeColour() const;

    //int BGRATribeColour() const;
    //int BGRATribeColourFlash() const;
    //int BGRAForeColour() const;

    cString szTribeString() const;
    char* TribeString() const;


    unsigned char getByte ( const Pop3Obj_ByteIndices index ) const;
    void setByte ( const Pop3Obj_ByteIndices index, const unsigned char value );

    //T_ functions relate to trigger objects
    unsigned short T_getWorshipTime();
    void T_setWorshipTime ( const unsigned short value );
    unsigned char T_getNumOccurrences();
    void T_setNumOccurrences ( const unsigned char value );
    unsigned char T_getNumWorshippers();
    void T_setNumWorshippers ( const unsigned char value );
    unsigned char T_getCreatePlayerOwned(); //boolean: 1 / 0
    void T_setCreatePlayerOwned ( const bool value );
    unsigned char T_getStartInactive();
    void T_setStartInactive ( const unsigned char value );
    unsigned char T_getInactiveTime();
    void T_setInactiveTime ( const unsigned char value );
    unsigned char T_getCellRadius();
    void T_setCellRadius ( const unsigned char value );
    void T_setIDX ( const Pop3Object_T_IDX_INDICES index, const unsigned short word );
    unsigned short T_getIDX ( const Pop3Object_T_IDX_INDICES index );

    void T_organiseIDXs();
    unsigned int T_countIDXS();
    int T_getFreeIDX();


    Pop3Obj_TriggerTypes T_getType() const;
    void T_setType ( const Pop3Obj_TriggerTypes T_Type );


    //D_ functions relate to discovery objects
    Pop3Obj_DiscoveryTypes D_getDiscoveryType();
    void D_setDiscoveryType ( const Pop3Obj_DiscoveryTypes value );
    long long D_mana_getManaValue();
    void D_mana_setManaValue ( const long long value );
    unsigned char D_getAvailability();
    void D_setAvailability ( const unsigned char value );
    unsigned char D_getModel();
    void D_setModel ( const unsigned char value );


    //E_ functions relate to effect objects
    unsigned char E_lb_getX() const;
    void E_lb_setX ( const unsigned char x );
    unsigned char E_lb_getY() const;
    void E_lb_setY ( const unsigned char y );
    unsigned char E_light_getX() const;
    void E_light_setX ( const unsigned char x );
    unsigned char E_light_getY() const;
    void E_light_setY ( const unsigned char y );


    //Misc Functions
private:
    void ClearExtra();

public:
    void ChangeToNormalObject();
    void ChangeToDiscovery ( const Pop3Obj_DiscoveryTypes discovery_type );
    void ChangeToTrigger();

};

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_OBJECT__ */
