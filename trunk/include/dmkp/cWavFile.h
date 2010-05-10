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


#ifndef _H_DMKP32_POPULOUS_CWAVFILE__
#define _H_DMKP32_POPULOUS_CWAVFILE__

#include "global.h"

typedef unsigned int uint;
typedef unsigned short uint16;

//Ideal Values / the defaults
#define iRIFF 0x46464952
#define iRIFFType 0x45564157
#define iDataBlockType 0x61746164
#define iWFBlockType 0x20746D66
#define iWFBlockSize 16
#define iWFFormatTag 1

#define WAV_EXT ".sdt"
#define WAV_OTITLE "Open WAV file"
#define WAV_FILTER "WAV File (*.wav)\0*.wav\0\0"
#define WAV_STITLE "Save WAV file"

namespace poplib
{

/* FIXME not crossplatform code
char* WAVGetFileName ( HWND hwndOwner, bool save );

class cWavFile
{
public:
    int RIFF;
    uint RIFFBlockSize;
    uint RIFFBlockType;
    uint wfBlockType;
    uint wfBlockSize;
    uint16 wfFormatTag;
    uint16 wfChannels;
    uint wfSamplesPerSec;
    uint16 wfBlockAlign;
    uint wfAvgBytesPerSec;
    uint16 wfBitsPerSample;
    uint DATABlockType;
    uint DATABlockSize;
    unsigned char* wfSoundData;

    //some formulae:
    //wfBlockAlign = ((wfChannels * localSound.bitsPerSample) / 8);
    //wfAvgBytesPerSec = wfSamplesPerSec * wfBlockAlign;
    ~cWavFile();
    cWavFile();
    //cWavFile(cPopSound* p);
    int LoadWAV ( char* filename );
    int SaveWAV ( char* filename );

private:
    void DefaultConstructor();
};
*/

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_CWAVFILE__ */
