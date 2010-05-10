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

#ifndef _H_DMKP32_POPULOUS_MAP_MANAGER__
#define _H_DMKP32_POPULOUS_MAP_MANAGER__

// FIXME not crossplatform code, max length of the file path
#define MAX_PATH 255

#define MAP_OTITLE "Open Map file"
#define MAP_STITLE "Save Map file"
#define MAP_FILTER "Populous Map Files (levl2*.dat)\0levl2*.dat\0Populous Map Files (*.dat)\0*.dat\0\0"
//#define MAP_FILTER "Populous Map Files (*.dat)\0*.dat\0Populous Map Files (levl20*.dat)\0levl20*.dat\0\0"

#define OBJECT_NONE_SELECTED -1

#define MAKECOLOUR_BASEGREEN 20
#define MAKECOLOUR_BASERED 20
#define MAKECOLOUR_BASEBLUE 0

//do this to remove the HDR handling stuff from this class
//#define DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR

#ifdef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
#pragma message "DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR defined, ignoring Populous HDR file related members and functions"
#endif

#define REG_PATH_POPULOUS "SOFTWARE\\Bullfrog Productions Ltd\\Populous: The Beginning"
#define REG_VALNAME_POPULOUS_INSTALLPATH "InstallPath"

#define MAX_LAND_HEIGHT 1024
#define MAX_POP3_OBJECT 2000
#define MAP_WIDTH 128
#define MAP_HEIGHT MAP_WIDTH

#define POP_MAP_FILE_VOID1 49219	//The void between the end of the land array and the beginning of the objects array
#define POP_MAP_FILE_VOID2 150		//The remaining space in the file after the objects array

#define HDR_EXT ".hdr"
#define MAP_EXT ".dat"
#define HDR_SIZE 616
#define SCRIPT_SIZE 12552
#define MAP_SIZE 192137

namespace poplib
{


class cString;
class HeaderData;
class PopObject;
class Colour;

/*
FIXME not crossplatform code
Colour makeColour ( const unsigned short landHeight );
char* getHDRFilenameFromMapName ( const char *src );

//used for open file dialog etc when map loading, is wrapped by a .net function taking a dmkp::Text::cString^ argument
char szPopulousPath[MAX_PATH + 1] = "C:\\Program Files\\Bullfrog\\Populous";

void SetPopulousDirectory ( const char* szPath );


cString MAPGetFilenameSZ ( HWND hOwner, bool save );
char* MAPGetFilename ( HWND hOwner, bool save );

class cMapManager
{
public:

    //HWND hwndOwner;

    unsigned short* LandBuf;

    unsigned char _void[POP_MAP_FILE_VOID1];

    PopObject Objects[MAX_POP3_OBJECT];

    unsigned char _void2[POP_MAP_FILE_VOID2];

#ifndef DMKP_POPULOUS_LIB_MAPMANAGER_NOHDR
    HeaderData Header;
#endif
    bool HeaderSupport; //if true, class will use header functions
    //if false, class will ignore header functions.

    char CurrentMap[MAX_PATH + 1];

    //ctor
    cMapManager ( bool );
    ~cMapManager();
    cMapManager* Clone();

    bool LoadMap ( const char* filepath );
    bool NewMap();
    bool Save ( const bool saveAs, bool* bCancelled );
    bool SaveMapSilent ( const char* filepath );

    int Object_GetLastObject();
    int Object_GetLastFree();
    int Object_GetFirstFree();
    int Object_CurrentSelected;
    unsigned int Object_Count();
    void Object_FixTriggers ( const unsigned int idx, const unsigned int newIdx );
    void Object_Sort();
    bool Object_DeleteSelected();
    //Stats* LevelStats(); //written by Ted Tycoon

    unsigned short LandTile ( int x, int y )
    {
        return LandBuf[ ( x * 128 ) + y];
    }
    void LandTile ( int x, int y, unsigned short l )
    {
        LandBuf[ ( x * 128 ) + y] = l;
    }


private:
    bool SaveMap ( const char* filepath, const bool silent );
    bool SaveMap ( const char* filepath );
    void ClearMap();

    //events (maybe) needed:

    //public delegate void LoadCompleteEvent();
    //public event LoadCompleteEvent OnLoadComplete;

    //public delegate void LoadFailedEvent();
    //public event LoadFailedEvent OnLoadFail;

    //public delegate void SaveCancelledEvent();
    //public event SaveCancelledEvent OnSaveCancelled;

    //public delegate void SaveSucceededEvent();
    //public event SaveCancelledEvent OnSaveComplete;

    //public delegate void NewMapEvent();
    //public event NewMapEvent OnNewMap;
};
*/

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_MAP_MANAGER__ */
