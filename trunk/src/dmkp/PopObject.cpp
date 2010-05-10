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
#include <cstdio>

#include "PopObject.h"
#include "Colour.h"
#include "colourConstants.h"
#include "cString.h"

namespace poplib
{

PopObject::PopObject()
{
    for ( int i = 0; i < 55; i++ )
    {
        setByte ( Pop3Obj_ByteIndices ( i ), 0 );
    }
}

PopObject::PopObject ( PopObject& copyThis )
{
    for ( int i = 0; i < 55; i++ )
    {
        setByte ( Pop3Obj_ByteIndices ( i ), copyThis.getByte ( Pop3Obj_ByteIndices ( i ) ) );
    }
}

//Copy the object and return a pointer to the copy
PopObject* PopObject::Clone() const
{
    PopObject* obj = new PopObject;

    unsigned char* bytes = this->exportObjAsByteArray();


    for ( int i = 0; i < 55; i++ )
        obj->setByte ( ( Pop3Obj_ByteIndices ) i, bytes[i] );

    delete[] bytes;

    return obj;
}

void PopObject::ImportObject ( const PopObject* object )
{
    for ( int i = 0; i < 55; i++ )
    {
        this->setByte ( Pop3Obj_ByteIndices ( i ), object->getByte ( Pop3Obj_ByteIndices ( i ) ) );
    }

    /* //It may be faster to set these directly then memcpy() the uextra buffer.
    unsigned char utype,
    ugroup,
    utribe,
    null1,
    ux,
    null2,
    uy,
    uangle;
    unsigned char uextra[47];
    */
}

//Check it is not a trigger, discovery or effect land bridge.
bool PopObject::IsNormalObject() const
{
    return !IsTrigger() && !IsDiscovery() && !IsEffectLandBridge();
}

//Check if the object is a trigger
bool PopObject::IsTrigger() const
{
    return utype == 6 && ugroup == 6;
}

//Check if the object is a discovery
bool PopObject::IsDiscovery() const
{
    return utype == 2 && ugroup == 6;
}

bool PopObject::IsDiscoveryMana() const
{
    return IsDiscovery() && uangle == ( unsigned char ) ( D_typeMana );
}

//Check if the object is an effect
bool PopObject::IsEffect() const
{
    return ugroup == 7;
}

//Check if the object is an effect : landbridge
bool PopObject::IsEffectLandBridge() const
{
    return IsEffect() && utype == 24;
}

//Check if the object is an effect : lightning bolt
bool PopObject::IsEffectLightningBolt() const
{
    return IsEffect() && utype == 17;
}

bool PopObject::IsShaman() const
{
    return utype == 7 && ugroup == 1;
}

bool PopObject::IsWildman() const
{
    return utype == 1 && ugroup == 1;
}

//Set the IDX at the specified index to the specified value
void PopObject::T_setIDX ( const Pop3Object_T_IDX_INDICES index, const unsigned short word )
{
    if ( ( index > 9 ) )
        return;
    else
    {

        unsigned char buf[2];
        unsigned char* numRef = buf;
        * ( ( unsigned short* ) numRef ) = word;

        setByte ( ( Pop3Obj_ByteIndices ) ( 13 + ( index * 2 ) ), buf[0] );
        setByte ( ( Pop3Obj_ByteIndices ) ( 14 + ( index * 2 ) ), buf[1] );

        /*
        public static unsafe byte[] GetBytes(short value)
        {
        byte[] buffer = new byte[2];
        fixed (byte* numRef = buffer)
        {
        *((short*) numRef) = value;
        }
        return buffer;
        }
        */

    }
}

//Get the IDX at the specified index
unsigned short PopObject::T_getIDX ( const Pop3Object_T_IDX_INDICES index )
{
    if ( index > 9 )
        return 0;
    else
    {

        unsigned char buf[2];
        buf[0] = getByte ( ( Pop3Obj_ByteIndices ) ( 13 + ( index * 2 ) ) );
        buf[1] = getByte ( ( Pop3Obj_ByteIndices ) ( 14 + ( index * 2 ) ) );

        return * ( ( unsigned short* ) ( buf ) );

    }
    //unsigned short *s = (unsigned short *)(&uextra[position]);


}

//Return a string describing the object - e.g.: 0606 would return "Trigger", 0101 would return "Wildman"
char* PopObject::ident() const
{
    //MessageBox(0, "I need implementing!", "cPop3Object::ident()", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    //return 0;

    unsigned char group = ugroup;
    unsigned char type = utype;

    char* str = 0;

    if ( group == N_GROUPS_Models_Values[0] )
    {
        for ( int i = 0; i < sizeof ( N_PERSONS_Models_Values ); i++ )
        {
            if ( type == N_PERSONS_Models_Values[i] )
            {
                str = new char[strlen ( N_PERSONS_Models[i] ) + 1];
                strcpy ( str, N_PERSONS_Models[i] );
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[1] )
    {
        for ( int i = 0; i < sizeof ( N_BUILDINGS_Models_Values ); i++ )
        {
            if ( type == N_BUILDINGS_Models_Values[i] )
            {
                str = new char[strlen ( N_BUILDINGS_Models[i] ) + 1];
                strcpy ( str, N_BUILDINGS_Models[i] );
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[2] )
    {
        if ( type == 1 )
        {
            str = new char[strlen ( N_CREATURE_Models[0] ) + 1];
            strcpy ( str, N_CREATURE_Models[0] );
            return str;
        }
    }
    else if ( group == N_GROUPS_Models_Values[3] )
    {
        for ( int i = 0; i < sizeof ( N_VEHICLES_Models_Values ); i++ )
        {
            if ( type == N_VEHICLES_Models_Values[i] )
            {
                str = new char[strlen ( N_VEHICLES_Models[i] ) + 1];
                strcpy ( str, N_VEHICLES_Models[i] );
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[4] )
    {
        for ( int i = 0; i < sizeof ( N_SCENERY_Models_Values ); i++ )
        {
            if ( type == N_SCENERY_Models_Values[i] )
            {
                str = new char[strlen ( N_SCENERY_Models[i] ) + 1];
                strcpy ( str, N_SCENERY_Models[i] );
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[5] )
    {
        for ( int i = 0; i < sizeof ( N_GENERAL_Models_Values ); i++ )
        {
            if ( type == N_GENERAL_Models_Values[i] )
            {
                str = new char[strlen ( N_GENERAL_Models[i] ) + 1];
                strcpy ( str, N_GENERAL_Models[i] );
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[6] )
    {
        for ( int i = 0; i < sizeof ( N_EFFECT_Models_Values ); i++ )
        {
            if ( type == N_EFFECT_Models_Values[i] )
            {
                str = new char[strlen ( N_EFFECT_Models[i] ) + 1 + 20]; // + 20 to ensure "E: " fits in ;)
                *str = 0;
                strcat ( str, "E:" );
                strcat ( str,  N_EFFECT_Models[i] );
                return /*"E:" +*/ str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[7] )
    {
        for ( int i = 0; i < sizeof ( N_VEHICLES_Models_Values ); i++ )
        {
            if ( type == N_SPELLS_Models_Values[i] )
            {
                str = new char[strlen ( N_SPELLS_Models[i] ) + 1];
                strcpy ( str, N_SPELLS_Models[i] );
                return str;
            }
        }
    }

    char text[100];
    sprintf ( text, "%s (0x%.2x 0x%.2x)", SZ_UNKNOWN, ugroup, utype );

    str = new char[strlen ( text ) + 1];
    strcpy ( str, text );
    return str;
}

cString PopObject::szident() const
{
    //MessageBox(0, "I need implementing!", "cPop3Object::ident()", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    //return 0;

    unsigned char group = ugroup;
    unsigned char type = utype;

    cString str;

    if ( group == N_GROUPS_Models_Values[0] )
    {
        for ( int i = 0; i < sizeof ( N_PERSONS_Models_Values ); i++ )
        {
            if ( type == N_PERSONS_Models_Values[i] )
            {
                str = N_PERSONS_Models[i];
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[1] )
    {
        for ( int i = 0; i < sizeof ( N_BUILDINGS_Models_Values ); i++ )
        {
            if ( type == N_BUILDINGS_Models_Values[i] )
            {
                str = N_BUILDINGS_Models[i];
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[2] )
    {
        if ( type == 1 )
        {
            str = N_CREATURE_Models[0];
            return str;
        }
    }
    else if ( group == N_GROUPS_Models_Values[3] )
    {
        for ( int i = 0; i < sizeof ( N_VEHICLES_Models_Values ); i++ )
        {
            if ( type == N_VEHICLES_Models_Values[i] )
            {
                str = N_VEHICLES_Models[i];
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[4] )
    {
        for ( int i = 0; i < sizeof ( N_SCENERY_Models_Values ); i++ )
        {
            if ( type == N_SCENERY_Models_Values[i] )
            {
                str = N_SCENERY_Models[i];
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[5] )
    {
        for ( int i = 0; i < sizeof ( N_GENERAL_Models_Values ); i++ )
        {
            if ( type == N_GENERAL_Models_Values[i] )
            {
                str = N_GENERAL_Models[i];
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[6] )
    {
        for ( int i = 0; i < sizeof ( N_EFFECT_Models_Values ); i++ )
        {
            if ( type == N_EFFECT_Models_Values[i] )
            {
                str = cString ( "E: " ) + N_EFFECT_Models[i];
                return str;
            }
        }
    }
    else if ( group == N_GROUPS_Models_Values[7] )
    {
        for ( int i = 0; i < sizeof ( N_VEHICLES_Models_Values ); i++ )
        {
            if ( type == N_SPELLS_Models_Values[i] )
            {
                str = N_SPELLS_Models[i];
                return str;
            }
        }
    }

    char text[100];
    sprintf ( text, "%s (0x%.2x 0x%.2x)", SZ_UNKNOWN, ugroup, utype );

    str = text;
    return str;
}

//Copy the object to a byte array and return the pointer to it
unsigned char* PopObject::exportObjAsByteArray() const
{
    unsigned char* bytes = new unsigned char[55];

    for ( int i = 0; i < 55; i++ )
    {
        bytes[i] = getByte ( Pop3Obj_ByteIndices ( i ) );
    }


    return bytes;
}

//Clear the object and replace with 0s
void PopObject::Delete()
{
    for ( int i = 0; i < 55; i++ )
        setByte ( Pop3Obj_ByteIndices ( i ), 0 );
}

//Check if the object is empty - usually if the group is 0 it is empty.. otherwise it is an error
bool PopObject::isEmpty() const
{
    return ! ( ugroup > 0 );
}

//Return an integer representing the colour of the object
Colour PopObject::ARGBTribeColour() const
{
    if ( ugroup == 2 )
    {
        switch ( utribe )
        {
        case ( TRIBE_BLUE ) : //blue
        {
            return Colour ( 128, 0, 0, 128 );
            break;
        }
        case ( TRIBE_RED ) : //red
        {
            return Colour ( 128, 255, 0, 0 );
            break;
        }
        case ( TRIBE_YELLOW ) : //yellow
        {
            return Colour ( 128, 255, 255, 0 );
            break;
        }
        case ( TRIBE_GREEN ) : //green
        {
            return Colour ( 128, 0, 255, 0 );
            break;
        }
        default:
        {
            return Colour ( 128, 255, 255, 255 );
            break;
        }
        }
    }
    else
    {
        switch ( utribe )
        {
        case ( TRIBE_BLUE ) : //blue
        {
            return Navy;//RGB(0, 0, 255);
            break;
        }
        case ( TRIBE_RED ) : //red
        {
            return RED;//RGB(255, 0, 0);
            break;
        }
        case ( TRIBE_YELLOW ) : //yellow
        {
            return YELLOW;//RGB(255, 255, 0);
            break;
        }
        case ( TRIBE_GREEN ) : //green
        {
            return GreenYellow;
            break;
        }
        case ( TRIBE_WILD ) : //wild
        {
            return WHITE;//RGB(255, 255, 255);
            break;
        }
        case ( TRIBE_NEUTRAL ) : //neutral
        {
            return MEDIUM_GREY;//RGB(128, 128, 128);
            break;
        }
        default:
        {
            return WHITE;//RGB(255, 255, 255);
            break;
        }
        }
    }

}

//Return an integer representing the colour of the object in the editor's flash phase (if any)
Colour PopObject::ARGBTribeColourFlash() const
{
    switch ( utribe )
    {
    case ( TRIBE_BLUE ) : //blue
    {
        return LIGHT_BLUE;
        break;
    }
    case ( TRIBE_RED ) : //red
    {
        return LIGHT_SALMON;//RGB(255, 160, 122); //Colour.LightSalmon
        break;
    }
    case ( TRIBE_YELLOW ) : //yellow
    {
        return LIGHT_YELLOW;//RGB(255, 255, 224); //Colour.LightYellow
        break;
    }
    case ( TRIBE_GREEN ) : //green
    {
        return LIGHT_GREEN;//RGB(144, 238, 144); //Colour.LightGreen
        break;
    }
    default:
    {
        return LIGHT_GREY;//RGB(190, 190, 190); //Colour.Gray
        break;
    }
    }
}

//Return an integer for the forecolour of the object in any listboxes (the text will stand out using these colours on their tribe colour bg)
Colour PopObject::ARGBForeColour() const
{
    if ( utribe == TRIBE_YELLOW )      //yellow
        return BLACK;//RGB(0,0,0); //(black colour)
    else if ( utribe == TRIBE_NEUTRAL ) //neutral
        return WHITE;//RGB(255,255,255);//(white colour)
    else if ( utribe == TRIBE_WILD ) //wild
        return BLACK;//RGB(0,0,0); //(black colour)
    else if ( utribe == TRIBE_BLUE || utribe == TRIBE_RED || utribe == TRIBE_GREEN ) //blue, red, green
        return WHITE;//RGB(255,255,255);//(white colour)
    else
        return PINK;//RGB(255, 192, 203); //Unknown\error (pink colour)
}

////-------------------------------------------------------------------------------------------------------
////Return an integer representing the colour of the object
//int cPop3Object::BGRATribeColour() const
//{
//	if(ugroup == 2)
//	{
//		switch(utribe)
//		{
//		case(TRIBE_BLUE): //blue
//			{
//				return 0xFF000080L; //ARGB(128, 0, 0, 255);
//				break;
//			}
//		case(TRIBE_RED): //red
//			{
//				return 0x0000FF80L; //ARGB(128, 255, 0, 0);
//				break;
//			}
//		case(TRIBE_YELLOW): //yellow
//			{
//				return 0x00FFFF80L;//ARGB(128, 255, 255, 0);
//				break;
//			}
//		case(TRIBE_GREEN): //green
//			{
//				return 0x00FF0080L;//ARGB(128, 0, 255, 0);
//				break;
//			}
//		default:
//			{
//				return 0xFFFFFF80L;//ARGB(128, 255, 255, 255);
//				break;
//			}
//		}
//	}
//	else
//	{
//		switch(utribe)
//		{
//		case(TRIBE_BLUE): //blue
//			{
//				return 0xFF0000FF;//RGB(0, 0, 255);
//				break;
//			}
//		case(TRIBE_RED): //red
//			{
//				return 0x0000FFFF;//RGB(255, 0, 0);
//				break;
//			}
//		case(TRIBE_YELLOW): //yellow
//			{
//				return 0x00FFFFFF;//RGB(255, 255, 0);
//				break;
//			}
//		case(TRIBE_GREEN): //green
//			{
//				return 0x00FF00FF;//RGB(0, 255, 0);
//				break;
//			}
//		case(TRIBE_WILD): //wild
//			{
//				return 0xFFFFFFFF;//RGB(255, 255, 255);
//				break;
//			}
//		case(TRIBE_NEUTRAL): //neutral
//			{
//				return 0x808080FF;//RGB(128, 128, 128);
//				break;
//			}
//		default:
//			{
//				return 0xFFFFFFFF;//RGB(255, 255, 255);
//				break;
//			}
//		}
//	}

//}

////Return an integer representing the colour of the object in the editor's flash phase (if any)
//int cPop3Object::BGRATribeColourFlash() const
//{
//	switch(utribe)
//	{
//	case(TRIBE_BLUE): //blue
//		{
//			return 0xE6D8ADFF;//RGB(173,216,230); //Colour.LightBlue
//			break;
//		}
//	case(TRIBE_RED): //red
//		{
//			return 0x7AA0FFFF;//RGB(255, 160, 122); //Colour.LightSalmon
//			break;
//		}
//	case(TRIBE_YELLOW): //yellow
//		{
//			return 0xE0FFFFFF;//RGB(255, 255, 224); //Colour.LightYellow
//			break;
//		}
//	case(TRIBE_GREEN): //green
//		{
//			return 0x90EE90FF;//RGB(144, 238, 144); //Colour.LightGreen
//			break;
//		}
//	default:
//		{
//			return 0xBEBEBEFF;//RGB(190, 190, 190); //Colour.Gray
//			break;
//		}
//	}
//}

////Return an integer for the forecolour of the object in any listboxes (the text will stand out using these colours on their tribe colour bg)
//int cPop3Object::BGRAForeColour() const
//{
//	if (utribe == TRIBE_YELLOW)        //yellow
//		return 0x000000FF;//RGB(0,0,0); //(black colour)
//	else if (utribe == TRIBE_NEUTRAL) //neutral
//		return 0xFFFFFFFF;//RGB(255,255,255);//(white colour)
//	else if (utribe == TRIBE_WILD) //wild
//		return 0x000000FF;//RGB(0,0,0); //(black colour)
//	else if (utribe == TRIBE_BLUE || utribe == TRIBE_RED || utribe == TRIBE_GREEN)//blue, red, green
//		return 0xFFFFFFFF;//RGB(255,255,255);//(white colour)
//	else
//		return 0xCBC0FFFF;//RGB(255, 192, 203); //Unknown\error (pink colour)
//}

////-------------------------------------------------------------------------------------------------------

//Return a string with the name of the tribe
cString PopObject::szTribeString() const
{
    if ( utribe == TRIBE_BLUE )
    {
        return SZ_BLUE;
    }

    if ( utribe == TRIBE_RED )
    {
        return SZ_RED;
    }

    if ( utribe == TRIBE_YELLOW )
    {
        return SZ_YELLOW;
    }

    if ( utribe == TRIBE_GREEN )
    {
        return SZ_GREEN;
    }

    if ( utribe == TRIBE_WILD )
    {
        return SZ_WILD;
    }

    if ( utribe == TRIBE_NEUTRAL )
    {
        return SZ_NEUTRAL;
    }

    return SZ_UNKNOWN;

}


//Return a string with the name of the tribe
char* PopObject::TribeString() const
{
    char* str;

    if ( utribe == TRIBE_BLUE )
    {
        str = new char[strlen ( SZ_BLUE ) + 1];
        strcpy ( str, SZ_BLUE );
        return str;
    }

    if ( utribe == TRIBE_RED )
    {
        str = new char[strlen ( SZ_RED ) + 1];
        strcpy ( str, SZ_RED );
        return str;
    }

    if ( utribe == TRIBE_YELLOW )
    {
        str = new char[strlen ( SZ_YELLOW ) + 1];
        strcpy ( str, SZ_YELLOW );
        return str;
    }

    if ( utribe == TRIBE_GREEN )
    {
        str = new char[strlen ( SZ_GREEN ) + 1];
        strcpy ( str, SZ_GREEN );
        return str;
    }

    if ( utribe == TRIBE_WILD )
    {
        str = new char[strlen ( SZ_WILD ) + 1];
        strcpy ( str, SZ_WILD );
        return str;
    }

    if ( utribe == TRIBE_NEUTRAL )
    {
        str = new char[strlen ( SZ_NEUTRAL ) + 1];
        strcpy ( str, SZ_NEUTRAL );
        return str;
    }

    str = new char[strlen ( SZ_UNKNOWN ) + 1];
    strcpy ( str, SZ_UNKNOWN );
    return str;

}

//Get the byte in the object at the specified index
unsigned char PopObject::getByte ( const Pop3Obj_ByteIndices index ) const
{
    if ( index == 0 )
    {
        return utype;
    }

    if ( index == 1 )
    {
        return ugroup;
    }

    if ( index == 2 )
    {
        return utribe;
    }

    if ( index == 3 )
    {
        return null1;
    }

    if ( index == 4 )
    {
        return ux;
    }

    if ( index == 5 )
    {
        return null2;
    }

    if ( index == 6 )
    {
        return uy;
    }

    if ( index == 7 )
    {
        return uangle;
    }

    if ( index >= 8 )
    {
        return uextra[index - 8];
    }

    return 0;
}

//Set the byte of the object at the specified index
void PopObject::setByte ( const Pop3Obj_ByteIndices index, const unsigned char val )
{
    if ( index == 0 )
    {
        utype = val;
        return;
    }

    if ( index == 1 )
    {
        ugroup = val;
        return;
    }

    if ( index == 2 )
    {
        utribe = val;
        return;
    }

    if ( index == 3 )
    {
        null1 = val;
        return;
    }

    if ( index == 4 )
    {
        ux = val;
        return;
    }

    if ( index == 5 )
    {
        null2 = val;
        return;
    }

    if ( index == 6 )
    {
        uy = val;
        return;
    }

    if ( index == 7 )
    {
        uangle = val;
        return;
    }

    if ( index >= 8 )
    {
        uextra[index - 8] = val;
        return;
    }


}

//-------------------------------------------------//
//Triggers
//-------------------------------------------------//

//Return the worship time of the trigger
unsigned short PopObject::T_getWorshipTime()
{
    unsigned char buf[2];
    buf[0] = getByte ( ( Pop3Obj_ByteIndices ) 33 );
    buf[1] = getByte ( ( Pop3Obj_ByteIndices ) 34 );

    return * ( ( unsigned short* ) ( buf ) );
}

//Set the worship time of the trigger
void PopObject::T_setWorshipTime ( const unsigned short value )
{
    unsigned char buf[2];
    unsigned short* pBuf = ( unsigned short* ) ( buf );
    *pBuf = value;

    setByte ( ( Pop3Obj_ByteIndices ) 33, buf[0] );
    setByte ( ( Pop3Obj_ByteIndices ) 34, buf[1] );
}

//Get the number of times it can be worshipped/triggered
unsigned char PopObject::T_getNumOccurrences()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 10 );
}

//Set the number of times it can be worshipped/triggered
void PopObject::T_setNumOccurrences ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 10, value );
}

unsigned char PopObject::T_getNumWorshippers()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 11 );
}

void PopObject::T_setNumWorshippers ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 11, value );
}

unsigned char PopObject::T_getCreatePlayerOwned()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 36 );
}

void PopObject::T_setCreatePlayerOwned ( const bool value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 36,value );
}

unsigned char PopObject::T_getStartInactive()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 35 );
}

void PopObject::T_setStartInactive ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 35, value );
}

unsigned char PopObject::T_getInactiveTime()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 37 );
}

void PopObject::T_setInactiveTime ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 37, value );
}

unsigned char PopObject::T_getCellRadius()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 8 );
}

void PopObject::T_setCellRadius ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 8, value );
}

//Put all the IDXs that are valid to the front, invalid IDXs are 0. IDXs are therefore, 1-based indices. Object 0 being IDX equivalant of 1.
void PopObject::T_organiseIDXs()
{
    unsigned short IDXs[10];
    for ( int i = 0; i < 10; i++ )
        IDXs[i] = T_getIDX ( Pop3Object_T_IDX_INDICES ( i ) );

    int changes;
    bool changed = false;
    while ( true )
    {
        changes = 0;

        for ( int i = 0; i < 9; i++ )
        {
            if ( IDXs[i] == 0 )
            {
                if ( IDXs[i + 1] > 0 )
                {
                    IDXs[i] = IDXs[i + 1];
                    IDXs[i + 1] = 0;
                    changes++;
                    changed = true;
                }
            }
        }

        if ( !changes )
            break;
    }

    if ( changed )
    {
        for ( int i = 0; i < 10; i++ )
        {
            T_setIDX ( Pop3Object_T_IDX_INDICES ( i ), IDXs[i] );
        }
    }

}

unsigned int PopObject::T_countIDXS()
{
    T_organiseIDXs(); //make sure they're in order.
    int count = 0;
    for ( int i = 0; i < 10; i++ )
    {
        if ( T_getIDX ( ( Pop3Object_T_IDX_INDICES ) i ) > 0 )
        {
            count += 1;
        }
    }

    return count;
}

int PopObject::T_getFreeIDX()
{
    T_organiseIDXs();
    for ( int i = 0; i < 10; i++ )
    {
        if ( T_getIDX ( Pop3Object_T_IDX_INDICES ( i ) ) == 0 )
        {
            return i;
        }
    }

    return -1;
}

Pop3Obj_TriggerTypes PopObject::T_getType() const
{
    return Pop3Obj_TriggerTypes ( uangle );
}

void PopObject::T_setType ( const Pop3Obj_TriggerTypes T_Type )
{
    uangle = ( unsigned char ) ( T_Type );
}

//-------------------------------------------------//
//Discoveries
//-------------------------------------------------//

Pop3Obj_DiscoveryTypes PopObject::D_getDiscoveryType()
{
    return Pop3Obj_DiscoveryTypes ( uangle );
}

void PopObject::D_setDiscoveryType ( const Pop3Obj_DiscoveryTypes value )
{
    uangle = ( unsigned char ) ( value );
}

long long PopObject::D_mana_getManaValue()
{
    unsigned char buf[8];
    buf[0] = getByte ( ( Pop3Obj_ByteIndices ) 11 );
    buf[1] = getByte ( ( Pop3Obj_ByteIndices ) 12 );
    buf[2] = getByte ( ( Pop3Obj_ByteIndices ) 13 );
    buf[3] = getByte ( ( Pop3Obj_ByteIndices ) 14 );
    buf[4] = getByte ( ( Pop3Obj_ByteIndices ) 15 );
    buf[5] = getByte ( ( Pop3Obj_ByteIndices ) 16 );
    buf[6] = getByte ( ( Pop3Obj_ByteIndices ) 17 );
    buf[7] = getByte ( ( Pop3Obj_ByteIndices ) 18 );

    return * ( ( long long* ) ( buf ) );
}

void PopObject::D_mana_setManaValue ( const long long value )
{
    unsigned char int64[8];
    * ( ( long long* ) int64 ) = value;

    setByte ( ( Pop3Obj_ByteIndices ) 11, int64[0] );
    setByte ( ( Pop3Obj_ByteIndices ) 12, int64[1] );
    setByte ( ( Pop3Obj_ByteIndices ) 13, int64[2] );
    setByte ( ( Pop3Obj_ByteIndices ) 14, int64[3] );
    setByte ( ( Pop3Obj_ByteIndices ) 15, int64[4] );
    setByte ( ( Pop3Obj_ByteIndices ) 16, int64[5] );
    setByte ( ( Pop3Obj_ByteIndices ) 17, int64[6] );
    setByte ( ( Pop3Obj_ByteIndices ) 18, int64[7] );

}

unsigned char PopObject::D_getAvailability()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 9 );
}

void PopObject::D_setAvailability ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 9, value );
}

unsigned char PopObject::D_getModel()
{
    return getByte ( ( Pop3Obj_ByteIndices ) 8 );
}

void PopObject::D_setModel ( const unsigned char value )
{
    setByte ( ( Pop3Obj_ByteIndices ) 8, value );
}

void PopObject::ClearExtra()
{
    for ( int i = 0; i < sizeof ( uextra ); i++ )
    {
        uextra[i] = 0;
    }
}

void PopObject::ChangeToNormalObject()
{
    ClearExtra();
}

void PopObject::ChangeToDiscovery ( Pop3Obj_DiscoveryTypes discovery_type )
{
    ClearExtra();

    switch ( discovery_type )
    {
    case ( D_typeBuilding ) :
    {
        setByte ( ( Pop3Obj_ByteIndices ) 7, 2 );
        setByte ( ( Pop3Obj_ByteIndices ) 8, 1 );
        setByte ( ( Pop3Obj_ByteIndices ) 9, 1 );
        setByte ( ( Pop3Obj_ByteIndices ) 10, 1 );
        break;
    }
    case ( D_typeMana ) :
    {
        setByte ( ( Pop3Obj_ByteIndices ) 7, 6 );
        setByte ( ( Pop3Obj_ByteIndices ) 8, 1 );
        setByte ( ( Pop3Obj_ByteIndices ) 9, 1 );
        setByte ( ( Pop3Obj_ByteIndices ) 10, 1 );
        break;
    }
    case ( D_typeSpell ) :
    {
        setByte ( ( Pop3Obj_ByteIndices ) 7, 11 );
        setByte ( ( Pop3Obj_ByteIndices ) 8, 1 );
        setByte ( ( Pop3Obj_ByteIndices ) 9, 1 );
        setByte ( ( Pop3Obj_ByteIndices ) 10, 1 );
        break;
    }
    }
}

void PopObject::ChangeToTrigger()
{
    ClearExtra();

    setByte ( ( Pop3Obj_ByteIndices ) 7, 3 );
    setByte ( ( Pop3Obj_ByteIndices ) 8, 1 );
    setByte ( ( Pop3Obj_ByteIndices ) 10, 1 );
    setByte ( ( Pop3Obj_ByteIndices ) 11, 1 );
    T_setWorshipTime ( 32 );
    setByte ( ( Pop3Obj_ByteIndices ) 37, 1 );
}

unsigned char PopObject::E_lb_getX() const
{
    return getByte ( ( Pop3Obj_ByteIndices ) 8 );
}

void PopObject::E_lb_setX ( const unsigned char x )
{
    setByte ( ( Pop3Obj_ByteIndices ) 8, x );
}

unsigned char PopObject::E_lb_getY() const
{
    return getByte ( ( Pop3Obj_ByteIndices ) 12 );
}

void PopObject::E_lb_setY ( const unsigned char y )
{
    setByte ( ( Pop3Obj_ByteIndices ) 12, y );
}

unsigned char PopObject::E_light_getX() const
{
    return E_lb_getX();
}

void PopObject::E_light_setX ( const unsigned char x )
{
    E_lb_setX ( x );
}

unsigned char PopObject::E_light_getY() const
{
    return E_lb_getY();
}

void PopObject::E_light_setY ( const unsigned char y )
{
    E_lb_setY ( y );
}

} // namespace poplib
