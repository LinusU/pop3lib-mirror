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

#include "cMapManager.h"
#include "cString.h"
#include "Colour.h"

namespace poplib
{

/* FIXME not crossplatform code
Colour MakeColour ( const unsigned short landHeight )
{
    if ( landHeight == 0 )
        return Colour ( 0,0,150 ); //water is blue
    else if ( landHeight > MAX_LAND_HEIGHT )
        return Colour ( 128,0,0 ); //invalid land is red

    unsigned char r = MAKECOLOUR_BASERED, g = MAKECOLOUR_BASEGREEN, b = MAKECOLOUR_BASEBLUE;

    g = ( landHeight * ( 255 - g ) / MAX_LAND_HEIGHT );

    return Colour ( r,g,b );
}

char* GetHDRFilenameFromMapName ( const char* src )
{
    if ( !src )
        return 0;
    else
    {
        //create copy
        char* newStr = new char[strlen ( src ) + 1];
        strcpy ( newStr, src ); //copy it over

        char* ext = PathFindExtensionA ( newStr ); //get pointer to the "." in the extension
        if ( !ext ) //if it is null, return (error)
        {
            delete[] newStr;
            return 0;
        }
        else
        {
            if ( strcmp ( ext, MAP_EXT ) != 0 ) //compare the extension to the constant
            {
                delete[] newStr;
                return 0;
            }
            else
            {
                strcpy ( newStr, HDR_EXT ); //copy over the new extension
                return newStr;
            }
        }
    }
}

void SetPopulousDirectory ( const char* szPath )
{
    if ( szPath )
    {
        int len = strlen ( szPath );
        if ( len > 0 && len < MAX_PATH + 1 )
        {
            strcpy ( szPopulousPath, szPath );
        }
    }
}

cString MAPGetFilenameSZ ( HWND hOwner, bool save )
{
    char* pChar = MAPGetFilename ( hOwner, save );

    if ( pChar )
    {
        cString string ( pChar );
        delete[]pChar;
        return string;
    }
    else
        return "";
}

char* MAPGetFilename ( HWND hOwner, bool save )
{
    //Filename is where the filename in the dialogue will be put
    //strInitialDir is the current directory
    char filename[MAX_PATH + 1];//, strInitialDir[MAX_PATH + 1];
    *filename = 0;

    //GetCurrentDirectory(MAX_PATH, strInitialDir);

    if ( !save )
    {
        //Create structure for the dialogue to use
        OPENFILENAME openFName;
        SecureZeroMemory ( &openFName, sizeof ( openFName ) );

        openFName.lStructSize = sizeof ( openFName );
        openFName.lpstrDefExt = MAP_EXT;	//default extension
        openFName.hwndOwner = hOwner;		//owner window
        openFName.lpstrTitle = MAP_OTITLE;	//title
        openFName.lpstrFile = filename;		//pointer to the char array to store our filename
        openFName.nMaxFile = sizeof ( filename );
        openFName.lpstrInitialDir = szPopulousPath;
        openFName.lpstrFilter = MAP_FILTER;	//filter
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
        saveFName.lpstrDefExt = MAP_EXT;
        saveFName.hwndOwner = hOwner;
        saveFName.lpstrTitle = MAP_STITLE;
        saveFName.lpstrFile = filename;
        saveFName.nMaxFile = sizeof ( filename );
        saveFName.lpstrInitialDir = szPopulousPath;
        saveFName.lpstrFilter = MAP_FILTER;
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

cMapManager::cMapManager ( bool bHeaderSupport )
{
    dOwner = 0;

    LandBuf = new unsigned short[128*128];
    HeaderSupport = bHeaderSupport;

    for ( int x = 0; x < MAP_WIDTH; x++ )
        for ( int y = 0; y < MAP_HEIGHT; y++ )
            LandBuf[x * 128 + y] = 0;

    *CurrentMap = 0;

    Object_CurrentSelected = OBJECT_NONE_SELECTED;
}

cMapManager::~cMapManager()
{
    if ( LandBuf ) delete[]LandBuf;
}

cMapManager* cMapManager::Clone()
{
    cMapManager* map = new cMapManager ( HeaderSupport );

    for ( int x = 0; x < MAP_WIDTH; x++ )
        for ( int y = 0; y < MAP_HEIGHT; y++ )
            map->LandBuf[x * 128 + y] = LandBuf[x* 128 + y];

    for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
    {
        map->Objects[i].ImportObject ( &Objects[i] );
    }

#ifndef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
    if ( HeaderSupport )
        map->Header.Import ( &Header );
#endif

    return map;
}

bool cMapManager::LoadMap ( const char* filepath )
{
    bool result = true;

    //Try to get a pointer to the file
    HANDLE hFile = CreateFileA ( filepath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
    LARGE_INTEGER liFileSize;
    DWORD dwBR = 0;

    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {
        GetFileSizeEx ( hFile, &liFileSize ); //get filesize

        if ( ! ( liFileSize.QuadPart == MAP_SIZE ) )
        {
            CloseHandle ( hFile );
            MessageBoxA ( 0, "Invalid file size!", "Error", MB_OK | MB_ICONERROR | MB_TASKMODAL );
            return false;
        }
        else
        {
            //for(int x = 0; x < MAP_WIDTH; x++)
            //{
            //	for(int y = 0; y < MAP_HEIGHT; y++)
            //	{
            //		result &= ReadFile(hFile, &LandBuf[x][y], sizeof(LandBuf[x][y]), &dwBR, 0);
            //	}
            //}

            result &= ReadFile ( hFile, LandBuf, ( 128*128 ) *2, &dwBR, 0 );

            result &= ReadFile ( hFile, &_void, sizeof ( _void ), &dwBR, 0 );

            for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
            {
                result &= ReadFile ( hFile, &Objects[i].utype, sizeof ( Objects[i].utype ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].ugroup, sizeof ( Objects[i].ugroup ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].utribe, sizeof ( Objects[i].utribe ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].null1, sizeof ( Objects[i].null1 ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].uy, sizeof ( Objects[i].uy ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].null2, sizeof ( Objects[i].null2 ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].ux, sizeof ( Objects[i].ux ), &dwBR, 0 );
                result &= ReadFile ( hFile, &Objects[i].uangle, sizeof ( Objects[i].uangle ), &dwBR, 0 );
                result &= ReadFile ( hFile, Objects[i].uextra, sizeof ( Objects[i].uextra ), &dwBR, 0 );

                if ( Objects[i].IsTrigger() ) // is it a trigger?
                {
                    Objects[i].T_organiseIDXs(); //shuffle idxs so they're all at the front, so the editor can read them(it stops reading the object idxs when it reaches a 0)
                }
            }

            result &= ReadFile ( hFile, _void2, sizeof ( _void2 ), &dwBR, 0 );

            CloseHandle ( hFile );

            Object_Sort(); //sort the objects

            //Copy the filename over
            strcpy ( CurrentMap, filepath );

#ifndef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
            if ( HeaderSupport )
            {
                //Now load the HDR if the above operations were successful
                if ( result )
                {
                    char* newPath = 0;

                    newPath = GetHDRFilenameFromMapName ( filepath );

                    if ( newPath )
                    {
                        if ( ! ( RAW::LoadHDR ( newPath, &Header ) ) )
                        {
                            cHeaderData hdr;
                            Header.Import ( &hdr );
                        }

                        delete[] newPath;
                    }
                    else
                        result &= false;
                    //result &= LoadHDR(
                }
            }
#endif

            Object_CurrentSelected = OBJECT_NONE_SELECTED;
            return result;
        }
    }
    else
        return false;


}

//		bool cMapManager::LoadMap(const char* filepath)
//		{
//
//			bool result = true;
//
//			cFileReader* reader = new cFileReader(filepath);
//
//			if(reader->FileSize() != MAP_SIZE)
//			{
//				reader->CloseFile();
//				delete reader;
//				return false;
//			}
//			else
//			{
//				for(int x = 0; x < MAP_WIDTH; x++)
//					for(int y = 0; y < MAP_HEIGHT; y++)
//						LandBuf[x][y] = reader->ReadUInt16();
//
//				reader->Seek(File_Seek::Seek_Begin, ((MAP_WIDTH * MAP_HEIGHT) *2) + POP_MAP_FILE_VOID1);
//
//				for(int i = 0; i < MAX_POP3_OBJECT; i++)
//				{
//					Objects[i].utype = reader->ReadUInt8();
//					Objects[i].ugroup = reader->ReadUInt8();
//					Objects[i].utribe = reader->ReadUInt8();
//					Objects[i].null1 = reader->ReadUInt8();
//					Objects[i].ux = reader->ReadUInt8();
//					Objects[i].null2 = reader->ReadUInt8();
//					Objects[i].uy = reader->ReadUInt8();
//					Objects[i].uangle = reader->ReadUInt8();
//
//					for(int z = 0; z < 47; z++)
//					{
//						Objects[i].uextra[z] = reader->ReadUInt8();
//					}
//
//					if(Objects[i].IsTrigger())
//					{
//						Objects[i].T_organiseIDXs();
//					}
//				}
//
//				Object_Sort(); //sort the objects
//
//				//Copy the filename over
//				strcpy(CurrentMap, filepath);
//
//
//#ifndef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
//				//Now load the HDR if the above operations were successful
//				if(result)
//				{
//					char* newPath = 0;
//
//					newPath = GetHDRFilenameFromMapName(filepath);
//
//					if(newPath)
//					{
//						if(!(LoadHDR(newPath, &Header)))
//						{
//							cHeaderData hdr;
//							Header.Import(&hdr);
//						}
//
//						delete[] newPath;
//					}
//					else
//						result &= false;
//					//result &= LoadHDR(
//				}
//#endif
//
//
//				reader->CloseFile();
//				delete reader;
//
//				return result;
//			}
//		}
//
bool cMapManager::NewMap()
{
    int res = MessageBoxA ( 0, "Do you wish to save first?", "Question", MB_YESNOCANCEL | MB_ICONQUESTION | MB_TASKMODAL );
    if ( res == IDYES )
    {
        bool success = Save ( true, 0 );

        if ( success )
        {
            ClearMap();
        }

        return success;
    }
    else if ( res == IDNO )
    {
        ClearMap();
        return true;
    }
    else
    {
        return false;
    }
}

void cMapManager::ClearMap()
{
    for ( unsigned int x = 0; x <  MAP_WIDTH; x++ )
    {
        for ( unsigned int y = 0; y < MAP_HEIGHT; y++ )
        {
            LandBuf[x * 128 + y] = 0;
        }
    }

    for ( unsigned int i = 0; i < MAX_POP3_OBJECT; i++ )
    {
        Objects[i].Delete();
    }

    //HDR
#ifndef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
    if ( HeaderSupport )
    {
        cHeaderData hdr;
        Header.Import ( &hdr );
    }
#endif
    //HDR


    //Clear current map name by putting the null at the beginning
    *CurrentMap = 0;
    Object_CurrentSelected = OBJECT_NONE_SELECTED;

    //if (OnNewMap != null)
    //    OnNewMap();
}

bool cMapManager::Save ( const bool saveAs, bool* bCancelled )
{
    if ( saveAs == false && ( ! ( *CurrentMap == 0 ) ) )
    {
        if ( bCancelled ) *bCancelled = false;
        return SaveMap ( CurrentMap );
    }
    else if ( ( saveAs == false && *CurrentMap == 0 ) || saveAs == true )
    {

        char* path = MAPGetFilename ( 0, true );

        if ( path )
        {
            bool res = true;
            res &= SaveMap ( path );

            delete[] path;
            if ( bCancelled ) *bCancelled = false;
            return res;
        }

        if ( bCancelled ) *bCancelled = true;
        return false;
    }

    if ( bCancelled ) *bCancelled = true;
    return false;
}

bool cMapManager::SaveMap ( const char* filepath )
{
    return SaveMap ( filepath, false );
}

bool cMapManager::SaveMapSilent ( const char* filepath )
{
    return SaveMap ( filepath, true );
}

bool cMapManager::SaveMap ( const char *filepath, const bool silent )
{
    bool result = true;


    //Try to get a pointer to the file
    HANDLE hFile = CreateFileA ( filepath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBR = 0;

    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {
        //for(int x = 0; x < MAP_WIDTH; x++)
        //{
        //	for(int y = 0; y < MAP_HEIGHT; y++)
        //	{
        //		result &= WriteFile(hFile, &LandBuf[x][y], sizeof(LandBuf[x][y]), &dwBR, 0);
        //	}
        //}

        result &= WriteFile ( hFile, LandBuf, ( 128*128 ) *2, &dwBR, 0 );

        result &= WriteFile ( hFile, &_void, sizeof ( _void ), &dwBR, 0 );

        Object_Sort(); //make sure to sort the objects

        for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
        {
            result &= WriteFile ( hFile, &Objects[i].utype, sizeof ( Objects[i].utype ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].ugroup, sizeof ( Objects[i].ugroup ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].utribe, sizeof ( Objects[i].utribe ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].null1, sizeof ( Objects[i].null1 ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].uy, sizeof ( Objects[i].uy ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].null2, sizeof ( Objects[i].null2 ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].ux, sizeof ( Objects[i].ux ), &dwBR, 0 );
            result &= WriteFile ( hFile, &Objects[i].uangle, sizeof ( Objects[i].uangle ), &dwBR, 0 );
            result &= WriteFile ( hFile, Objects[i].uextra, sizeof ( Objects[i].uextra ), &dwBR, 0 );
        }

        result &= WriteFile ( hFile, _void2, sizeof ( _void2 ), &dwBR, 0 );

        CloseHandle ( hFile );

        //Copy the filename over
        strcpy ( CurrentMap, filepath );

#ifndef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
        if ( HeaderSupport )
        {
            //Now save the HDR if the above operations were successful
            if ( result )
            {
                char* newPath = 0;

                newPath = GetHDRFilenameFromMapName ( filepath );

                if ( newPath )
                {
                    result &= RAW::SaveHDR ( newPath, &Header );

                    delete[] newPath;
                }
                else
                    result &= false;
                //result &= LoadHDR(
            }
        }
#endif
        return result;

    }
    else
        return false;
}


int cMapManager::Object_GetLastFree()
{
    if ( !Objects[MAX_POP3_OBJECT -1].isEmpty() )
        return -1;

    for ( int i = MAX_POP3_OBJECT -1; i >= 0; i-- )
    {
        if ( !Objects[i].isEmpty() )
        {
            return i + 1;
        }
    }
    return -1;
}

int cMapManager::Object_GetFirstFree()
{
    for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
    {
        if ( Objects[i].isEmpty() )
            return i;
    }

    return -1; //on error (no free objects)
}

unsigned int cMapManager::Object_Count()
{
    unsigned int count = 0;

    for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
    {
        if ( Objects[i].isEmpty() )
            break;
        else
            count += 1;
    }

    return count;
}

void cMapManager::Object_FixTriggers ( const unsigned int idx, const unsigned int newIdx )
{
    for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
    {
        if ( Objects[i].IsTrigger() )
        {
            for ( int j = 0; j < 10; j++ )
            {
                if ( Objects[i].T_getIDX ( Pop3Object_T_IDX_INDICES ( j ) ) == idx )
                {
                    Objects[i].T_setIDX ( Pop3Object_T_IDX_INDICES ( j ), newIdx );
                }
            }
        }

        if ( newIdx == 0 )
        {
            Objects[i].T_organiseIDXs();
        }
    }

}

int cMapManager::Object_GetLastObject()
{
    for ( int i = MAX_POP3_OBJECT - 1; i >= 0; i-- )
    {
        if ( Objects[i].isEmpty() == false )
            return i;
    }

    return 0;
}

void cMapManager::Object_Sort()
{
    MessageBoxA ( 0, "I am not happy with this function, please remember to rewrite it using bubble sort algorithm instead\nParticularly I am not happy with the IDX fixing.. shouldn't it be +1? I am unsure as to how this works now so I want to rewrite this sorting algorithm", "Object_Sort()", MB_OK | MB_TASKMODAL | MB_ICONERROR );
    int lastid;

    for ( int i = 0; i < MAX_POP3_OBJECT; i++ )
    {
        //Check if the object is empty/null
        if ( Objects[i].isEmpty() )
        {
            //Get the last (non-empty) object
            lastid = Object_GetLastObject();

            if ( lastid > i )
            {
                //Move last object to mid space and delete the last object
                Objects[i].ImportObject ( &Objects[lastid] );
                Objects[lastid].Delete();
                //Fix triggers
                Object_FixTriggers ( lastid, i );
            }
            else
                return; //must be at the end of the list, return
        }
    }

    int changes;
    bool changed = false;

    while ( true )
    {
        changes = 0;

        for ( int i = 0; i < MAX_POP3_OBJECT - 1; i++ )
        {
            if ( Objects[i].isEmpty() )
            {
                if ( !Objects[i + 1].isEmpty() )
                {
                    Objects[i].ImportObject ( &Objects[i + 1] );
                    Objects[i + 1].Delete();
                    Object_FixTriggers ( i + 2, i + 1 );
                    changes++;
                    changed = true;
                }
            }
        }

        if ( !changes )
            break;

    }

    /*
    unsigned short IDXs[10];
    for(int i = 0; i < 10; i++)
    IDXs[i] = T_getIDX(Pop3Object_T_IDX_INDICES(i));

    int changes;
    bool changed = false;
    while(true)
    {
    changes = 0;

    for(int i = 0; i < 9; i++)
    {
    if(IDXs[i] == 0)
    {
    if(IDXs[i + 1] > 0)
    {
    IDXs[i] = IDXs[i + 1];
    IDXs[i + 1] = 0;
    changes++;
    changed = true;
    }
    }
    }

    if(!changes)
    break;
    }

    if(changed)
    {
    for(int i = 0; i < 10; i++)
    {
    T_setIDX(Pop3Object_T_IDX_INDICES(i), IDXs[i]);
    }
    }
    */
		/*
}

bool cMapManager::Object_DeleteSelected()
{
    if ( Object_CurrentSelected > OBJECT_NONE_SELECTED && Object_CurrentSelected < MAX_POP3_OBJECT )
    {
        Objects[Object_CurrentSelected].Delete();			//clear object
        Object_FixTriggers ( Object_CurrentSelected + 1, 0 ); //clear any triggers linked to this object index, +1 is because IDXs start at 1



        //Shift all objects up by one place. Starting at the currently selected
        //Object_Sort();	//sort objects again using this if found that the following code doesn't work correctly!
        for ( int i = Object_CurrentSelected; i < MAX_POP3_OBJECT; i++ )
        {
            if ( i == MAX_POP3_OBJECT - 1 )
            {
                Objects[i].Delete();
                Object_FixTriggers ( i + 2, 0 );
                break;
            }

            Objects[i].ImportObject ( &Objects[i + 1] );
            Object_FixTriggers ( i + 2, i + 1 );
        }
        //-----------------------------------------------------------

        return true;
    }
    else
    {
        return false;
    }
}*/

/*
//Written by Ted Tycoon
Stats* cMapManager::LevelStats()
{
    Stats* statsLevelStatistics = new Stats();

    int islandcount, x, y, x1,
    y1, x127, y127, xx, yy,
    i, highestland,
    islands[17000][2],
    landchecked[128][128],
    xland[128][128],
    connectedland[9];

    long long landmass;

    bool sorted;

    for ( x = 0; x < 128; x++ )
    {
        for ( y = 0; y < 128; y++ )
        {
            xland[x][y] = LandBuf[x][y];
        }
    }

    for ( i = 0; i < 17000; i++ )
    {
        islands[i][ 0] = 0;
        islands[i][ 1] = 0;
    }

    islandcount = 0;
    highestland = 0;
    landmass = 0;

    for ( y = 0; y <= 127; y++ )
    {
        for ( x = 0; x <= 127; x++ )
        {
            if ( xland[x][ y] > 0 )
            {
                landmass += 1;
//first assume that each land tile is a separate island
                islandcount += 1;
                landchecked[x][ y] = islandcount;
            }
            else
            {
                landchecked[x][ y] = 0; //not land
            }
//keep highest land
            if ( xland[x][ y] > highestland ) highestland = xland[x][ y];
        }
    }


//now check each piece of land for connected land
    for ( y = 0; y <= 127; y++ )
    {
        y1 = ( y + 1 ) % 128;
        y127 = ( y + 127 ) % 128;
        for ( x = 0; x <= 127; x++ )
        {
            x1 = ( x + 1 ) % 128;
            x127 = ( x + 127 ) % 128;
            if ( xland[x][ y] > 0 )
            {
                connectedland[1] = landchecked[x1][ y];
                connectedland[2] = landchecked[x127][ y];
                connectedland[3] = landchecked[x][ y127];
                connectedland[4] = landchecked[x][ y1];
                connectedland[5] = landchecked[x127][ y127];
                connectedland[6] = landchecked[x127][ y1];
                connectedland[7] = landchecked[x1][ y127];
                connectedland[8] = landchecked[x1][ y1];
                if ( landchecked[x][ y] > 1 )
                    i = i;
                islandcount = landchecked[x][ y];

                for ( i = 1; i <= 8; i++ )
                {
                    if ( connectedland[i] != 0 )
                    {
                        if ( connectedland[i] < islandcount )
                            islandcount = connectedland[i]; //find the lowest islandcount
                    }
                }
//change all connected land to the lowest island count
                for ( yy = 0; yy <= 127; yy++ )
                {
                    for ( xx = 0; xx <= 127; xx++ )
                    {
                        if ( landchecked[xx][ yy] != 0 && landchecked[xx][ yy] != islandcount )
                        {
                            for ( i = 1; i <= 8; i++ )
                            {
                                if ( landchecked[xx][ yy] == connectedland[i] )
                                {
                                    landchecked[xx][ yy] = islandcount;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//now count the islands and their size
    islandcount = 0;

    for ( y = 0; y <= 127; y++ )
    {
        for ( x = 0; x <= 127; x++ )
        {
            if ( landchecked[x][ y] > 0 )
            {
                for ( i = 0; i <= islandcount; i++ ) //check whether we have found this island before
                {
                    if ( islands[i][ 0] == landchecked[x][ y] )
                    {
                        islands[i][ 1] += 1; //count the land squares for (this island
                        goto _islandfound;
                    }
                }
//must be a new island
                islandcount += 1;
                islands[islandcount][ 0] = landchecked[x][ y];
                islands[islandcount][ 1] += 1;
            _islandfound:
                x = x;		//to prevent error
            }
        }
    }

//bubble sort the islands by size
    do
    {
        sorted = true;
        for ( x = 2; x <= islandcount; x++ )
        {
            if ( islands[x][ 1] > islands[x - 1][ 1] )
            {
                sorted = false;
                islands[0][ 0] = islands[x][ 0];
                islands[x][ 0] = islands[x - 1][ 0];
                islands[x - 1][ 0] = islands[0][ 0];
                islands[0][ 1] = islands[x][ 1];
                islands[x][ 1] = islands[x - 1][ 1];
                islands[x - 1][ 1] = islands[0][ 1];
            }
        }
    }
    while ( !sorted );

    statsLevelStatistics->HighestLand = highestland;
    statsLevelStatistics->LandAmount = ( int ) ( landmass * 100 / 16000 ); //make a  CntI
    statsLevelStatistics->LargestIsland[0] = islands[1][ 1];
    statsLevelStatistics->LargestIsland[1] = islands[2][ 1];
    statsLevelStatistics->LargestIsland[2] = islands[3][ 1];
    statsLevelStatistics->LargestIsland[3] = islands[4][ 1];


//--------------------------------------------------------------
//-----------------------------Objects--------------------------
//--------------------------------------------------------------
    for ( i = 0; i < MAX_POP3_OBJECT; i++ )
    {
//Increment Objects
//You can add more to the structure like heads, buildings etc
//Increment tribe colour

        if ( !Objects[i].isEmpty() )
        {

            switch ( Objects[i].utribe )
            {
            case 0:
                statsLevelStatistics->BlueObjects += 1;
                break;
            case 1:
                statsLevelStatistics->RedObjects += 1;
                break;
            case 2:
                statsLevelStatistics->YellowObjects += 1;
                break;
            case 3:
                statsLevelStatistics->GreenObjects += 1;
                break;
            default:
                statsLevelStatistics->WildObjects += 1;
                break;
            }
        }
//Increment types
        switch ( Objects[i].ugroup )
        {
        case 1:
            if ( Objects[i].utype == 1 )
                statsLevelStatistics->Wildies += 1;      //Increment Wildies
            else
                statsLevelStatistics->Followers += 1;    //Increment Followers
            break;
        case 5:
            if ( Objects[i].utype > 0 && Objects[i].utype < 7 )
                statsLevelStatistics->Trees += 1;        //Increment Trees
            break;
        }
    }
    return statsLevelStatistics;
}*/

} // namespace poplib
