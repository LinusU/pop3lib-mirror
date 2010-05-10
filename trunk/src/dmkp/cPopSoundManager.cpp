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

//#include <Windows.h>
//#include <MMSystem.h>

#include "cPopSoundManager.h"
#include "PopSound.h"
#include "cWavFile.h"

namespace poplib
{

/* FIXME not crossplatfrom code
void PlaySoundFile ( cWavFile* wav )
{
    if ( wav->SaveWAV ( "temp.wav" ) )
    {
        PlaySoundA ( "temp.wav", NULL, SND_FILENAME | SND_ASYNC );
    }
}

char* SDTGetFileName ( HWND hwndOwner, bool save )
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
        openFName.lpstrDefExt = SDT_EXT;
        openFName.hwndOwner = hwndOwner;
        openFName.lpstrTitle = SDT_OTITLE;
        openFName.lpstrFile = filename;
        openFName.nMaxFile = sizeof ( filename );
        openFName.lpstrInitialDir = strInitialDir;
        openFName.lpstrFilter = SDT_FILTER;
        openFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if ( GetOpenFileNameA ( &openFName ) )
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
        openFName.lpstrDefExt = SDT_EXT;
        openFName.hwndOwner = hwndOwner;
        openFName.lpstrTitle = SDT_STITLE;
        openFName.lpstrFile = filename;
        openFName.nMaxFile = sizeof ( filename );
        openFName.lpstrInitialDir = strInitialDir;
        openFName.lpstrFilter = SDT_FILTER;
        openFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

        if ( GetSaveFileNameA ( &openFName ) )
        {
            char* path = new char[MAX_PATH + 1];
            strcpy ( path, filename );
            return path;
        }

    }

    return 0;
}*/

/*
		char* HDRGetFileName(HWND hOwner, bool save)
		{
			//Filename is where the filename in the dialogue will be put
			//strInitialDir is the current directory
			char filename[MAX_PATH], strInitialDir[MAX_PATH];

			GetCurrentDirectory(sizeof(strInitialDir), strInitialDir);

			if(!save)
			{
				//Create structure for the dialogue to use
				OPENFILENAME openFName;
				SecureZeroMemory(&openFName, sizeof(OPENFILENAME));

				openFName.lStructSize = sizeof(openFName);
				openFName.lpstrDefExt = HDR_EXT;	//default extension
				openFName.hwndOwner = hOwner;		//owner window
				openFName.lpstrTitle = HDR_OTITLE;	//title
				openFName.lpstrFile = filename;		//pointer to the char array to store our filename
				openFName.nMaxFile = sizeof(filename);
				openFName.lpstrInitialDir = strInitialDir;
				openFName.lpstrFilter = HDR_FILTER;	//filter
				openFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;	//opening flags

				if(GetOpenFileName(&openFName))		//show dlg, get filename
				{
					char* path = new char[MAX_PATH];
					strcpy(path, filename);
					return path;				//return the filename
				}
			}
			else
			{
				OPENFILENAME saveFName;
				SecureZeroMemory(&saveFName, sizeof(OPENFILENAME));

				saveFName.lStructSize = sizeof(saveFName);
				saveFName.lpstrDefExt = HDR_EXT;
				saveFName.hwndOwner = hOwner;
				saveFName.lpstrTitle = HDR_STITLE;
				saveFName.lpstrFile = filename;
				saveFName.nMaxFile = sizeof(filename);
				saveFName.lpstrInitialDir = strInitialDir;
				saveFName.lpstrFilter = HDR_FILTER;
				saveFName.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

				if(GetSaveFileName(&saveFName))
				{
					char* path = new char[MAX_PATH];
					strcpy(path, filename);
					return path;				//return the filename
				}

			}



			return 0; //no action required
		}

		*/
/*

//This was created as a work around to the constructor inside the class that creates a new instance
//based on a wav class, I could not find a work around for it because it kept saying each other didn't exist.
//e.g. the cPopSound(cWavFile*) constructor kept insisting cWavFile wasn't defined!
cPopSound* cPopSoundFromWAV ( cWavFile* wav )
{
    if ( !wav )
        return 0;

    cPopSound* snd = new cPopSound;
    snd->dataSize = wav->DATABlockSize;
    snd->soundData = new unsigned char[wav->DATABlockSize];
    memcpy ( snd->soundData, wav->wfSoundData, wav->DATABlockSize );
    snd->headerSize = 44;
    snd->channels = wav->wfChannels;
    snd->sampleRate = wav->wfSamplesPerSec;
    snd->bitsPerSample = wav->wfBitsPerSample;
    snd->loopStart = 0;
    snd->loopEnd = 0;


    return snd;
}

//		cPopSound::cPopSound(cWavFile* wav)
//{
//	soundData = new unsigned char[wav->DATABlockSize];
//	memcpy(soundData, wav->wfSoundData, wav->DATABlockSize);
//	headerSize = 44;
//	channels = wav->wfChannels;
//	sampleRate = wav->wfSamplesPerSec;
//	bitsPerSample = wav->wfBitsPerSample;
//	loopStart = 0;
//	loopEnd = 0;
//};

cWavFile* cWavFileFromPOP ( cPopSound* p )
{
    cWavFile* snd;

    if ( p )
    {
        snd = new cWavFile;
        snd->RIFF = iRIFF; //RIFF
        snd->RIFFBlockSize = p->dataSize + p->headerSize;// 44;
        snd->RIFFBlockType = iRIFFType; //WAVE
        snd->DATABlockSize = p->dataSize;

        snd->wfSoundData = new unsigned char[p->dataSize];
        memcpy ( snd->wfSoundData, p->soundData, p->dataSize );

        snd->wfBlockType = iWFBlockType;
        snd->wfBlockSize = iWFBlockSize;
        snd->wfFormatTag = iWFFormatTag;
        snd->wfChannels = p->channels;
        snd->wfSamplesPerSec = p->sampleRate;
        snd->wfBlockAlign = ( snd->wfChannels * p->bitsPerSample / 8 );
        snd->wfAvgBytesPerSec = snd->wfSamplesPerSec * snd->wfBlockAlign;
        snd->wfBitsPerSample = p->bitsPerSample;
    }
    else
    {
        snd = new cWavFile;
    }

    return snd;
}


//		cWavFile::cWavFile(cPopSound* p)
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

unsigned int cPopSoundManager::GetNSounds()
{
    return ( unsigned int ) nSounds;
}

bool cPopSoundManager::ReplaceSound ( unsigned int index, cPopSound* pSnd )
{
    if ( index >= nSounds )
        return false;

    pSounds[index].Delete();

    pSounds[index].bitsPerSample = pSnd->bitsPerSample;
    pSounds[index].channels = pSnd->channels;
    pSounds[index].dataSize = pSnd->dataSize;
    pSounds[index].headerSize = pSnd->headerSize;
    pSounds[index].loopEnd = pSnd->loopEnd;
    pSounds[index].loopStart = pSnd->loopStart;
    pSounds[index].sampleRate = pSnd->sampleRate;

    pSounds[index].soundData = new unsigned char[pSnd->dataSize];
    memcpy ( pSounds[index].soundData, pSnd->soundData, pSnd->dataSize );

    memcpy ( pSounds[index].unknown, pSnd->unknown, sizeof ( pSnd->unknown ) );

    //memcpy(pSounds[index].title, pSnd->title, sizeof(pSnd->title));


    //   sound[index].HeaderSize = snd.HeaderSize;
    //sound[index].SampleRate = snd.SampleRate;
    //sound[index].BitRate = snd.BitRate;
    //sound[index].Channels = snd.Channels;
    //sound[index].SoundData = snd.SoundData;

    return true;
}

cPopSoundManager::cPopSoundManager()
{
    pSounds = 0;
    //SecureZeroMemory(currentFile, sizeof(currentFile));
}

cPopSoundManager::~cPopSoundManager()
{
    if ( pSounds )
        delete[] pSounds;
}

cPopSound* cPopSoundManager::GetSound ( unsigned int index )
{
    if ( index >= nSounds )
        return 0;
    else
    {
        return pSounds[index].Clone();
    }
}


bool cPopSoundManager::LoadFile ( char *filename )
{
    bool success = true;

    //Create handle to file
    HANDLE hFile = CreateFileA ( filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBR = 0;

    //Check the handle is good
    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {

        //Read in the number of sounds
        success &= ReadFile ( hFile, &nSounds, sizeof ( nSounds ), &dwBR, 0 );

        if ( nSounds )
        {
            LARGE_INTEGER li;
            li.QuadPart = nSounds * sizeof ( unsigned int );

            //skip the array of indices for the sounds (should not be needed by this programme)
            success &= SetFilePointerEx ( hFile, li, 0, FILE_CURRENT );

            //if pSounds is already allocated memory, clear it
            if ( pSounds )
                delete[]pSounds;

            //Allocate new memory
            pSounds = new cPopSound[nSounds];

            //Load file
            for ( int i = 0; i < nSounds; i++ )
            {
                success &= ReadFile ( hFile, &pSounds[i].headerSize, sizeof ( pSounds[i].headerSize ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].dataSize, sizeof ( pSounds[i].dataSize ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].title, sizeof ( pSounds[i].title ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].sampleRate, sizeof ( pSounds[i].sampleRate ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].bitsPerSample, sizeof ( pSounds[i].bitsPerSample ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].channels, sizeof ( pSounds[i].channels ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].unknown, sizeof ( pSounds[i].unknown ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].loopStart, sizeof ( pSounds[i].loopStart ), &dwBR, 0 );
                success &= ReadFile ( hFile, &pSounds[i].loopEnd, sizeof ( pSounds[i].loopEnd ), &dwBR, 0 );

                pSounds[i].soundData = new unsigned char[pSounds[i].dataSize];

                success &= ReadFile ( hFile, pSounds[i].soundData, pSounds[i].dataSize, &dwBR, 0 );

            }

            //for (int i = 0; i < numSounds; i++)
            //{
            //sound[i] = new cPopSound();
            //sound[i].HeaderSize = reader.ReadUInt32();
            //uint DataSize = reader.ReadUInt32(); //because "get" of that property returns the size of the sound data, which isn't even loaded yet!
            //sound[i].Title = new String((System.Text.ASCIIEncoding.ASCII.GetChars(reader.ReadBytes(16))));//System.Text.ASCIIEncoding.ASCII.GetChars(reader.ReadBytes(16));
            //sound[i].SampleRate = reader.ReadUInt16();
            //sound[i].BitRate = reader.ReadByte();
            //sound[i].Channels = reader.ReadByte();
            //sound[i].Unknown = reader.ReadBytes(4);
            //sound[i].LoopBegin = reader.ReadUInt32();
            //sound[i].LoopEnd = reader.ReadUInt32();
            //sound[i].SoundData = reader.ReadBytes(Convert.ToInt32(DataSize));
            //}
            CloseHandle ( hFile );
        }
        else
        {
            CloseHandle ( hFile );
            return false;
        }

        return success;
    }
    else
    {
        return false;
    }*/

    /*
    FileStream stream = new FileStream(fName, FileMode.Open, FileAccess.Read);
    BinaryReader reader = new BinaryReader(stream);

    //read the number of sounds in the file
    numSounds = reader.ReadInt32();


    int[] position = new int[numSounds];


    //read all positions of the sound files
    for (int i = 0; i < numSounds; i++)
    {
    position[i] = reader.ReadInt32();
    }

    Array.Resize(ref sound, numSounds);

    //and read the sound data

    for (int i = 0; i < numSounds; i++)
    {
    sound[i] = new cPopSound();
    sound[i].HeaderSize = reader.ReadUInt32();
    uint DataSize = reader.ReadUInt32(); //because "get" of that property returns the size of the sound data, which isn't even loaded yet!
    sound[i].Title = new String((System.Text.ASCIIEncoding.ASCII.GetChars(reader.ReadBytes(16))));//System.Text.ASCIIEncoding.ASCII.GetChars(reader.ReadBytes(16));
    sound[i].SampleRate = reader.ReadUInt16();
    sound[i].BitRate = reader.ReadByte();
    sound[i].Channels = reader.ReadByte();
    sound[i].Unknown = reader.ReadBytes(4);
    sound[i].LoopBegin = reader.ReadUInt32();
    sound[i].LoopEnd = reader.ReadUInt32();
    sound[i].SoundData = reader.ReadBytes(Convert.ToInt32(DataSize));
    }
    reader.Close();
    stream.Close();

    currentFile = fName;
    */
		
		/*
}


bool cPopSoundManager::SaveFile ( char* filename )
{
    if ( !filename )
        return false;

    HANDLE hFile = CreateFileA ( filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    DWORD dwBW = 0;
    bool success = true;

    if ( ! ( hFile == INVALID_HANDLE_VALUE ) )
    {

        //Write the number of sounds
        success &= WriteFile ( hFile, &nSounds, sizeof ( nSounds ), &dwBW, 0 );

        //Calculate the offset of the first sound
        unsigned int baseOffset = sizeof ( nSounds ) + ( sizeof ( int ) * nSounds );

        //Write it, then calculate the next and write that => loop
        for ( int i = 0; i < nSounds; i++ )
        {
            success &= WriteFile ( hFile, &baseOffset, sizeof ( baseOffset ), &dwBW, 0 );
            baseOffset += pSounds[i].GetByteSize();
        }

        //Write all the sound data
        for ( int i = 0; i < nSounds; i++ )
        {
            success &= WriteFile ( hFile, &pSounds[i].headerSize, sizeof ( pSounds[i].headerSize ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].dataSize, sizeof ( pSounds[i].dataSize ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].title, sizeof ( pSounds[i].title ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].sampleRate, sizeof ( pSounds[i].sampleRate ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].bitsPerSample, sizeof ( pSounds[i].bitsPerSample ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].channels, sizeof ( pSounds[i].channels ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].unknown, sizeof ( pSounds[i].unknown ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].loopStart, sizeof ( pSounds[i].loopStart ), &dwBW, 0 );
            success &= WriteFile ( hFile, &pSounds[i].loopEnd, sizeof ( pSounds[i].loopEnd ), &dwBW, 0 );
            success &= WriteFile ( hFile, pSounds[i].soundData, pSounds[i].dataSize, &dwBW, 0 );
        }

        CloseHandle ( hFile );
        return success;
    }
    else
        return false;
}
*/

} // namespace poplib
