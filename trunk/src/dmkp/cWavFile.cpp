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

#include "cWavFile.h"

namespace poplib
{

/*FIXME not crossplatform code
char* WAVGetFileName ( HWND hwndOwner, bool save )
{
    char filename[MAX_PATH + 1], strInitialDir[MAX_PATH + 1];
    *filename = 0;

    GetCurrentDirectoryA ( MAX_PATH, strInitialDir );


    if ( !save )
    {

        //Open
        OPENFILENAMEA openFName;
        SecureZeroMemory ( &openFName, sizeof ( openFName ) );

        openFName.lStructSize = sizeof ( openFName );
        openFName.lpstrDefExt = WAV_EXT;
        openFName.hwndOwner = hwndOwner;
        openFName.lpstrTitle = WAV_OTITLE;
        openFName.lpstrFile = filename;
        openFName.nMaxFile = sizeof ( filename );
        openFName.lpstrInitialDir = strInitialDir;
        openFName.lpstrFilter = WAV_FILTER;
        openFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if ( GetOpenFileName ( &openFName ) )
        {
            char* path = new char[MAX_PATH + 1];
            strcpy ( path, filename );
            return path;
        }

    }
    else
    {

        //Save
        OPENFILENAMEA openFName;
        SecureZeroMemory ( &openFName, sizeof ( openFName ) );

        openFName.lStructSize = sizeof ( openFName );
        openFName.lpstrDefExt = WAV_EXT;
        openFName.hwndOwner = hwndOwner;
        openFName.lpstrTitle = WAV_STITLE;
        openFName.lpstrFile = filename;
        openFName.nMaxFile = sizeof ( filename );
        openFName.lpstrInitialDir = strInitialDir;
        openFName.lpstrFilter = WAV_FILTER;
        openFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

        if ( GetSaveFileNameA ( &openFName ) )
        {
            char* path = new char[MAX_PATH + 1];
            strcpy ( path, filename );
            return path;
        }

    }

    return 0;
}

cWavFile::~cWavFile()
{
    if ( wfSoundData )
    {
        delete[] wfSoundData;
        wfSoundData = 0;
    }
};

cWavFile::cWavFile()
{
    DefaultConstructor();
};

//cWavFile::cWavFile(cPopSound* p)
//{
//	if(p)
//	{
//		RIFF = iRIFF; //RIFF
//		RIFFBlockSize = p->dataSize + 44;
//		RIFFBlockType = iRIFFType; //WAVE
//		DATABlockSize = p->dataSize;

//		wfSoundData = new unsigned char[p->dataSize];
//		memcpy(wfSoundData, p->soundData, p->dataSize);

//		wfBlockType = iWFBlockType;
//		wfBlockSize = iWFBlockSize;
//		wfFormatTag = iWFFormatTag;
//		wfChannels = p->channels;
//		wfSamplesPerSec = p->sampleRate;
//		wfBlockAlign = (wfChannels * p->bitsPerSample / 8);
//		wfAvgBytesPerSec = wfSamplesPerSec * wfBlockAlign;
//		wfBitsPerSample = p->bitsPerSample;
//	}
//	else
//		DefaultConstructor();
//};

int cWavFile::LoadWAV ( char* filename )
{
    if ( !filename )
    {
        return false;
    }

    if ( wfSoundData )
    {
        delete[]wfSoundData;
        wfSoundData = 0;
    }

    bool success = true;

    HANDLE hFile = CreateFileA ( filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBR = 0;

    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {
        success &= ReadFile ( hFile, &RIFF, sizeof ( RIFF ), &dwBR, 0 );

        if ( ! ( RIFF == iRIFF ) )
        {
            CloseHandle ( hFile );
            MessageBoxA ( 0, "Error, invalid WAV file: not of \"RIFF\" format", "Error", MB_OK | MB_ICONERROR );
            return false;
        }

        success &= ReadFile ( hFile, &RIFFBlockSize, sizeof ( RIFFBlockSize ), &dwBR, 0 );
        success &= ReadFile ( hFile, &RIFFBlockType, sizeof ( RIFFBlockType ), &dwBR, 0 );

        if ( ! ( RIFFBlockType == iRIFFType ) )
        {
            CloseHandle ( hFile );
            MessageBoxA ( 0, "Error, invalid RIFF Block type: not of type \"DATA\"", "Error", MB_OK | MB_ICONERROR );
            return false;
        }

        success &= ReadFile ( hFile, &wfBlockType, sizeof ( wfBlockType ), &dwBR, 0 );

        if ( ! ( wfBlockType == iWFBlockType ) )
        {
            CloseHandle ( hFile );
            MessageBoxA ( 0, "Error, invalid RIFF Format, block type not known!", "Error", MB_OK | MB_ICONERROR );
            return false;
        }

        success &= ReadFile ( hFile, &wfBlockSize, sizeof ( wfBlockSize ), &dwBR, 0 );
        success &= ReadFile ( hFile, &wfFormatTag, sizeof ( wfFormatTag ), &dwBR, 0 );

        if ( ! ( wfFormatTag == iWFFormatTag ) )
        {
            CloseHandle ( hFile );
            MessageBoxA ( 0,"Error, Audio format invalid.\nNeeds to be of type PCM (pulse-code modulation; non-compressed format)", "Error", MB_OK | MB_ICONERROR );
            return false;
        }

        success &= ReadFile ( hFile, &wfChannels, sizeof ( wfChannels ), &dwBR,0 );
        success &= ReadFile ( hFile, &wfSamplesPerSec, sizeof ( wfSamplesPerSec ), &dwBR,0 );
        success &= ReadFile ( hFile, &wfBlockAlign, sizeof ( wfBlockAlign ), &dwBR,0 );
        success &= ReadFile ( hFile, &wfAvgBytesPerSec, sizeof ( wfAvgBytesPerSec ), &dwBR,0 );
        success &= ReadFile ( hFile, &wfBitsPerSample, sizeof ( wfBitsPerSample ), &dwBR,0 );


        success &= ReadFile ( hFile, &DATABlockType, sizeof ( DATABlockType ), &dwBR,0 );

        if ( ! ( DATABlockType == iDataBlockType ) )
        {
            CloseHandle ( hFile );
            MessageBoxA ( 0, "Error, invalid datablock type!", "Error", MB_OK | MB_ICONERROR );
            return false;
        }

        success &= ReadFile ( hFile, &DATABlockSize, sizeof ( DATABlockSize ), &dwBR,0 );

        wfSoundData = new unsigned char[DATABlockSize];

        success &= ReadFile ( hFile, wfSoundData, DATABlockSize, &dwBR,0 );

        CloseHandle ( hFile );
        return success;
    }
    else
        return false;

    return false;
}

int cWavFile::SaveWAV ( char* filename )
{
    if ( !filename )
        return false;

    if ( !wfSoundData )
        return false;

    bool success = true;

    HANDLE hFile = CreateFileA ( filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBW = 0;

    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {
        success &= WriteFile ( hFile, &RIFF, sizeof ( RIFF ), &dwBW, 0 );
        success &= WriteFile ( hFile, &RIFFBlockSize, sizeof ( RIFFBlockSize ), &dwBW, 0 );
        success &= WriteFile ( hFile, &RIFFBlockType, sizeof ( RIFFBlockType ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfBlockType, sizeof ( wfBlockType ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfBlockSize, sizeof ( wfBlockSize ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfFormatTag, sizeof ( wfFormatTag ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfChannels, sizeof ( wfChannels ), &dwBW, 0 ); //http://www.funmansion.com/post/archive/index.php/t-69.html
        success &= WriteFile ( hFile, &wfSamplesPerSec, sizeof ( wfSamplesPerSec ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfAvgBytesPerSec, sizeof ( wfAvgBytesPerSec ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfBlockAlign, sizeof ( wfBlockAlign ), &dwBW, 0 );
        success &= WriteFile ( hFile, &wfBitsPerSample, sizeof ( wfBitsPerSample ), &dwBW, 0 );
        success &= WriteFile ( hFile, &DATABlockType, sizeof ( DATABlockType ), &dwBW, 0 );
        success &= WriteFile ( hFile, &DATABlockSize, sizeof ( DATABlockSize ), &dwBW, 0 );
        success &= WriteFile ( hFile, wfSoundData, DATABlockSize, &dwBW, 0 );

        CloseHandle ( hFile );
        return success;
    }
    else
    {
        return false;
    }
}

void cWavFile::DefaultConstructor()
{
    RIFF = iRIFF; //RIFF
    RIFFBlockSize = 44;
    RIFFBlockType = iRIFFType; //WAVE
    DATABlockType = iDataBlockType; //DATA
    DATABlockSize = 0;
    wfSoundData = NULL;
    wfBlockType = iWFBlockType; //FMT (Format)
    wfBlockSize = iWFBlockSize;
    wfFormatTag = iWFFormatTag;
    //wfChannels = p.Channels;
    //wfSamplesPerSec = p.SampleRate;
    //wfBlockAlign = (ushort)(wfChannels * p.BitRate / 8);
    //wfAvgBytesPerSec = wfSamplesPerSec * wfBlockAlign;
    //wfBitsPerSample = p.BitRate;
}
*/

} // namespace poplib
