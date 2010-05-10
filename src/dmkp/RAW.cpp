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

#include "RAW.h"

namespace poplib
{
/* FIXME not crossplatform code
bool RAW::LoadHDR ( char* filepath, cHeaderData* pHdr )
{
    if ( !pHdr || !filepath )
    {
        MessageBoxA ( 0, "Null Pointer exception.", "LoadHDR()", MB_OK | MB_ICONERROR | MB_TASKMODAL );
        return false;
    }

    //Attempt to load file
    HANDLE hFile = CreateFileA ( filepath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBytesRead = 0;

    LARGE_INTEGER p_int_FileSize;

    //If it could not be loaded....
    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {
        //Get file size of the file opened
        GetFileSizeEx ( hFile, &p_int_FileSize );
        //Check it is correct
        if ( p_int_FileSize.QuadPart != HDR_SIZE )
        {
            CloseHandle ( hFile );
            char text[80];
            sprintf ( text, "Invalid file size: %i\nFile should be size: %i", p_int_FileSize.QuadPart, HDR_SIZE );
            MessageBoxA ( 0, text, "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL );
            return false;
        }

        //Make a byte array of size 616
        unsigned char bytes[HDR_SIZE];

        //Read the file into the byte array ready to be processed.
        ReadFile ( hFile, bytes, sizeof ( bytes ), &dwBytesRead, 0 );
        if ( dwBytesRead != HDR_SIZE )
        {
            CloseHandle ( hFile );
            char text[80];
            sprintf ( text, "Problem reading file: could not read all %ibytes\n%i bytes read.", HDR_SIZE, dwBytesRead );
            MessageBoxA ( 0, text, "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL );
            return false;
        }


        CloseHandle ( hFile );

        SPELLS* spells = &pHdr->AvailableSpells;
        unsigned char curByte = bytes[0];
        spells->Hypnotise = curByte & BIT_0;
        spells->Invisibility = curByte & BIT_1;
        spells->Swarm = curByte & BIT_2;
        spells->Tornado = curByte & BIT_3;
        spells->Lightning = curByte & BIT_4;
        spells->Blast = curByte & BIT_5;

        //char text[50];
        //sprintf(text, "%i", spells->Blast);
        //MessageBox(0, text, "",MB_OK | MB_TASKMODAL);


        curByte = bytes[1];
        spells->Flatten = curByte & BIT_0;
        spells->Earthquake = curByte & BIT_1;
        spells->AngelOfDeath = curByte & BIT_2;
        spells->Landbridge = curByte & BIT_3;
        spells->Swamp = curByte & BIT_4;
        spells->Erode = curByte & BIT_5;
        spells->GhostArmy = curByte & BIT_6;
        spells->Firestorm = curByte & BIT_7;

        curByte = bytes[2];
        spells->MagicShield = curByte & BIT_4;
        spells->Convert = curByte & BIT_6;
        spells->Volcano = curByte & BIT_7;


        curByte = bytes[4];
        BUILDINGS* buildings = &pHdr->AvailableBuildings;
        buildings->WarriorHut = curByte & BIT_0;
        buildings->SpyHut = curByte & BIT_1;
        buildings->Temple = curByte & BIT_2;
        buildings->Tower = curByte & BIT_3;
        buildings->Hut = curByte & BIT_6;

        curByte = bytes[5];
        buildings->BalloonHut = curByte & BIT_0;
        buildings->BoatHut = curByte & BIT_2;
        buildings->FirewarriorHut = curByte & BIT_7;

        curByte = bytes[16];
        spells = &pHdr->SpellsNotCharging;
        spells->Hypnotise = curByte & BIT_0;
        spells->Invisibility = curByte & BIT_1;
        spells->Swarm = curByte & BIT_2;
        spells->Tornado = curByte & BIT_3;
        spells->Lightning = curByte & BIT_4;
        spells->Blast = curByte & BIT_5;

        curByte = bytes[17];
        spells->Flatten = curByte & BIT_0;
        spells->Earthquake = curByte & BIT_1;
        spells->AngelOfDeath = curByte & BIT_2;
        spells->Landbridge = curByte & BIT_3;
        spells->Swamp = curByte & BIT_4;
        spells->Erode = curByte & BIT_5;
        spells->GhostArmy = curByte & BIT_6;
        spells->Firestorm = curByte & BIT_7;

        curByte = bytes[18];
        spells->MagicShield = curByte & BIT_4;
        spells->Convert = curByte & BIT_6;
        spells->Volcano = curByte & BIT_7;


        //curByte = bytes[56];

        for ( int i = 0; i < 32; i++ )
        {
            pHdr->LevelName[i] = bytes[i + 56];
        }

        //byte 88 [base 0];
        pHdr->NumPlayers = bytes[88];
        pHdr->RedScript = bytes[89];
        pHdr->YellowScript = bytes[90];
        pHdr->GreenScript = bytes[91];

        curByte = bytes[92];
        ALLIANCES* allies = &pHdr->Allies;
        allies->BR = curByte & BIT_6;
        allies->BY = curByte & BIT_5;
        allies->BG = curByte & BIT_4;

        curByte = bytes[93];
        allies->RY = curByte & BIT_5;
        allies->RG = curByte & BIT_4;

        curByte = bytes[94];
        allies->YG = curByte & BIT_4;

        //byte 96
        pHdr->LandScape = bytes[96];
        pHdr->TreeStyle = ( ObjBank ) bytes[97];

        curByte = bytes[98];
        pHdr->LevelFlags.NoGuestSpells = curByte & BIT_5;
        pHdr->LevelFlags.God = curByte & BIT_6;
        pHdr->LevelFlags.Fog = curByte & BIT_7;

        //byte 100
        MARKER* mk = pHdr->Markers;
        for ( int i = 0; i < 256; i++ )
        {
            mk[i].x = bytes[i * 2 + 100];
            mk[i].y = bytes[i * 2 + 1 + 100];
        }

        return true;

    }
    else
    {
        //could not load, tell user.
        char error[MAX_PATH + 50];
        sprintf ( error, "File error: \"%s\".\nInvalid file handle value", filepath );
        MessageBoxA ( 0, error, "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL );
        return false;
    }
}


bool RAW::SaveHDR ( char* filepath, cHeaderData* pHdr )
{

    if ( !pHdr || !filepath )
    {
        MessageBoxA ( 0, "Null Pointer exception.", "SaveHDR()", MB_OK | MB_TASKMODAL );
        return false;
    }

    HANDLE hFile = CreateFileA ( filepath, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBW = 0;

    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {
        unsigned char bytes[HDR_SIZE];
        SecureZeroMemory ( bytes, sizeof ( bytes ) );

        //byteval = (val1 << 7) + (val2 << 6) + (val3 << 5) + (val4 << 4) + (val5 << 3) + (val6 << 2) + (val7 << 1) + val8
        //for when putting bits back, val1 - val8 must be 1 or 0

        SPELLS* spells = &pHdr->AvailableSpells;

        //byte 0 - spells1
        //bytes[0] = ( spells->Hypnotise << 7 ) +
                  // ( spells->Invisibility << 6 ) +
                  // ( spells->Swarm << 5 ) +
                  // ( spells->Tornado << 4 ) +
                  // ( spells->Lightning << 3 ) +
                  // ( spells->Blast << 2 ) +
                  // ( true << 1 ) + true;

        //(spells->Hypnotise ? BIT_0 : 0) + (spells->Invisibility ? BIT_1 : 0) +
        //(spells->Swarm ? BIT_2 : 0) + (spells->Tornado ? BIT_3 : 0) + (spells->Lightning ? BIT_4 : 0) +
        //(spells->Blast ? BIT_5 : 0) + BIT_6 + BIT_7; //alternative code, which can also be changed to | instead of +

        //byte 1 - spells2
        bytes[1] = ( spells->Flatten << 7 ) +
                   ( spells->Earthquake << 6 ) +
                   ( spells->AngelOfDeath << 5 ) +
                   ( spells->Landbridge << 4 ) +
                   ( spells->Swamp << 3 ) +
                   ( spells->Erode << 2 ) +
                   ( spells->GhostArmy << 1 ) +
                   ( spells->Firestorm );

        //(spells->Flatten ? BIT_0 : 0) + (spells->Earthquake ? BIT_1 : 0) + (spells->AngelOfDeath ? BIT_2 : 0) +
        //(spells->Landbridge ? BIT_3 : 0) + (spells->Swamp ? BIT_4 : 0) + (spells->Erode ? BIT_5 : 0) + (spells->GhostArmy ? BIT_6 : 0) +
        //(spells->Firestorm ? BIT_7 : 0);



        //byte 2 - spells3
        bytes[2] = ( true << 7 ) + ( true << 6 ) + ( true << 5 ) + ( true << 4 ) + ( spells->MagicShield << 3 ) +
                   ( true << 2 ) + ( spells->Convert << 1 ) + ( spells->Volcano );

        //BIT_0 + BIT_1 + BIT_2 + BIT_3 + (spells->MagicShield ? BIT_4 : 0) + BIT_5 +
        //(spells->Convert ? BIT_6 : 0) + (spells->Volcano ? BIT_7 : 0);




        //byte 4 - buildings1
        BUILDINGS* buildings = &pHdr->AvailableBuildings;
        bytes[4] = ( buildings->WarriorHut << 7 ) + ( buildings->SpyHut << 6 ) +
                   ( buildings->Temple << 5 ) + ( buildings->Tower << 4 ) +
                   ( true << 3 ) + ( true << 2 ) + ( buildings->Hut << 1 ) +	true;

        //(buildings->WarriorHut ? BIT_0 : 0) + (buildings->SpyHut ? BIT_1 : 0) + (buildings->Temple ? BIT_2 : 0) +
        //(buildings->Tower ? BIT_3 : 0) + BIT_4 + BIT_5 + (buildings->Hut ? BIT_6 : 0) + BIT_7;





        //byte 5 - buildings2
        bytes[5] = ( buildings->BalloonHut << 7 ) + ( true << 6 ) + ( buildings->BoatHut << 5 ) +
                   ( true << 4 ) + ( true << 3 ) + ( true << 2 ) + ( true << 1 ) + buildings->FirewarriorHut;

        //(buildings->BalloonHut ? BIT_0 : 0) + BIT_1 + (buildings->BoatHut ? BIT_2 : 0) + BIT_3 + BIT_4 + BIT_5 + BIT_6 +
        //(buildings->FirewarriorHut ? BIT_7 : 0);



        //byte 15, 16, 17 - spells not charging 1, 2, 3
        spells = &pHdr->SpellsNotCharging;
        bytes[16] = ( spells->Hypnotise << 7 ) +
                    ( spells->Invisibility << 6 ) +
                    ( spells->Swarm << 5 ) +
                    ( spells->Tornado << 4 ) +
                    ( spells->Lightning << 3 ) +
                    ( spells->Blast << 2 ) +
                    ( true << 1 ) + true;

        //(spells->Hypnotise ? BIT_0 : 0) + (spells->Invisibility ? BIT_1 : 0) +
        //(spells->Swarm ? BIT_2 : 0) + (spells->Tornado ? BIT_3 : 0) + (spells->Lightning ? BIT_4 : 0) +
        //(spells->Blast ? BIT_5 : 0) + BIT_6 + BIT_7;

        bytes[17] = ( spells->Flatten << 7 ) +
                    ( spells->Earthquake << 6 ) +
                    ( spells->AngelOfDeath << 5 ) +
                    ( spells->Landbridge << 4 ) +
                    ( spells->Swamp << 3 ) +
                    ( spells->Erode << 2 ) +
                    ( spells->GhostArmy << 1 ) +
                    ( spells->Firestorm );

        //(spells->Flatten ? BIT_0 : 0) + (spells->Earthquake ? BIT_1 : 0) + (spells->AngelOfDeath ? BIT_2 : 0) +
        //(spells->Landbridge ? BIT_3 : 0) + (spells->Swamp ? BIT_4 : 0) + (spells->Erode ? BIT_5 : 0) + (spells->GhostArmy ? BIT_6 : 0) +
        //(spells->Firestorm ? BIT_7 : 0);

        bytes[18] = ( true << 7 ) +
                    ( true << 6 ) +
                    ( true << 5 ) +
                    ( true << 4 ) +
                    ( spells->MagicShield << 3 ) +
                    ( true << 2 ) +
                    ( spells->Convert << 1 ) +
                    ( spells->Volcano );

        //BIT_0 + BIT_1 + BIT_2 + BIT_3 + (spells->MagicShield ? BIT_4 : 0) + BIT_5 +
        //(spells->Convert ? BIT_6 : 0) + (spells->Volcano ? BIT_7 : 0);

        //byte 55 to (55+32) - name
        for ( int i = 0; i < 32; i++ )
            bytes[i + 56] = pHdr->LevelName[i];
        //byte 88 - num players
        bytes[88] = pHdr->NumPlayers;
        //byte 89 - red script
        bytes[89] = pHdr->RedScript;
        //byte 90 - yellow script
        bytes[90] = pHdr->YellowScript;
        //byte 91 - green script
        bytes[91] = pHdr->GreenScript;
        //byte 92 to 95 - blue, red, yellow, green alliances
        ALLIANCES* allies = &pHdr->Allies;
        bytes[92] = BIT_7 + ( allies->BR ? BIT_6 : 0 ) + ( allies->BY ? BIT_5 : 0 ) + ( allies->BG ? BIT_4 : 0 );

        //(false << 7) + (false << 6) + (false << 5) + (false << 4) +
        //(allies->BG << 3) + (allies->BY << 2) + (allies->BR << 1) + true;

        bytes[93] = ( allies->BR ? BIT_7 : 0 ) + BIT_6 + ( allies->RY ? BIT_5 : 0 ) + ( allies->RG ? BIT_4 : 0 );

        //(false << 7) + (false << 6) + (false << 5) + (false << 4) +
        //(allies->RG << 3) + (allies->RY << 2) + (true << 1) + allies->BR;

        bytes[94] = ( allies->BY ? BIT_7 : 0 ) + ( allies->RY ? BIT_6 : 0 ) +  BIT_5 + ( allies->YG ? BIT_4 : 0 );

        //(false << 7) + (false << 6) + (false << 5) + (false << 4) +
        //(allies->YG << 3) + (true << 2) + (allies->RY << 1) + allies->BY;

        bytes[95] = ( allies->BG ? BIT_7 : 0 ) + ( allies->RG ? BIT_6 : 0 ) + ( allies->YG ? BIT_5 : 0 ) + BIT_4;

        //(false << 7) + (false << 6) + (false << 5) + (false << 4) +
        //(true << 3) + (allies->YG << 2) + (allies->RG << 1) + allies->BG;

        //byte 96
        bytes[96] = pHdr->LandScape;
        bytes[97] = pHdr->TreeStyle;

        bytes[98] = ( pHdr->LevelFlags.NoGuestSpells ? BIT_5 : 0 ) | ( pHdr->LevelFlags.God ? BIT_6 : 0 ) |	( pHdr->LevelFlags.Fog ? BIT_7 : 0 );

        //byte 100 to ((256*2)+100) - markers(x,y)
        for ( int i = 0; i < 256; i++ )
        {
            bytes[i * 2 + 100] = pHdr->Markers[i].x;
            bytes[i * 2 + 1 + 100] = pHdr->Markers[i].y;
        }

        WriteFile ( hFile, bytes, sizeof ( bytes ), &dwBW, 0 );
        CloseHandle ( hFile );

        if ( dwBW != HDR_SIZE )
        {
            char text[80];
            sprintf ( text, "Problem saving file: could not write all %ibytes\n%i bytes written.", HDR_SIZE, dwBW );
            MessageBoxA ( 0, text, "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL );
            return false;
        }

        return true;
    }
    else
    {
        //could not save, tell user.
        char error[MAX_PATH + 50];
        sprintf ( error, "File error: \"%s\".\nInvalid file handle value", filepath );
        MessageBoxA ( 0, error, "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL );
        return false;
    }
}

char* RAW::HDRGetFileName ( HWND hOwner, bool save )
{
    //Filename is where the filename in the dialogue will be put
    //strInitialDir is the current directory
    char filename[MAX_PATH + 1], strInitialDir[MAX_PATH + 1];
    *filename = 0;

    GetCurrentDirectory ( MAX_PATH, strInitialDir );

    if ( !save )
    {
        //Create structure for the dialogue to use
        OPENFILENAME openFName;
        SecureZeroMemory ( &openFName, sizeof ( openFName ) );

        openFName.lStructSize = sizeof ( openFName );
        openFName.lpstrDefExt = HDR_EXT;	//default extension
        openFName.hwndOwner = hOwner;		//owner window
        openFName.lpstrTitle = HDR_OTITLE;	//title
        openFName.lpstrFile = filename;		//pointer to the char array to store our filename
        openFName.nMaxFile = sizeof ( filename );
        openFName.lpstrInitialDir = strInitialDir;
        openFName.lpstrFilter = HDR_FILTER;	//filter
        openFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;	//opening flags

        if ( GetOpenFileName ( &openFName ) )		//show dlg, get filename
        {
            char* path = new char[MAX_PATH + 1];
            strcpy ( path, filename );
            return path;				//return the filename
        }
    }
    else
    {
        OPENFILENAME saveFName;
        SecureZeroMemory ( &saveFName, sizeof ( saveFName ) );

        saveFName.lStructSize = sizeof ( saveFName );
        saveFName.lpstrDefExt = HDR_EXT;
        saveFName.hwndOwner = hOwner;
        saveFName.lpstrTitle = HDR_STITLE;
        saveFName.lpstrFile = filename;
        saveFName.nMaxFile = sizeof ( filename );
        saveFName.lpstrInitialDir = strInitialDir;
        saveFName.lpstrFilter = HDR_FILTER;
        saveFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

        if ( GetSaveFileName ( &saveFName ) )
        {
            char* path = new char[MAX_PATH + 1];
            strcpy ( path, filename );
            return path;				//return the filename
        }

    }

    return 0; //no action required
}
*/

} // namespace poplib
