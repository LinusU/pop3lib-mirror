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

#include "PopSound.h"

namespace poplib
{

PopSound* PopSound::Clone()
{
    PopSound* snd = new PopSound;
    snd->bitsPerSample = bitsPerSample;
    snd->channels = channels;
    snd->dataSize = dataSize;

    memcpy ( snd->title, title, sizeof ( title ) );
    snd->sampleRate = sampleRate;
    snd->loopEnd = loopEnd;
    snd->loopStart = loopStart;

    memcpy ( snd->unknown, unknown, sizeof ( unknown ) );

    snd->soundData = new unsigned char[dataSize];
    memcpy ( snd->soundData, soundData, dataSize );

    return snd;
}

//This clears the object ready for being changed
//
void PopSound::Delete()
{
    if ( soundData )
    {
        delete[] soundData;
        soundData = 0;
    }

    headerSize = 40;
    dataSize = 0;
    //SecureZeroMemory(title, sizeof(title));
    sampleRate = 0;
    bitsPerSample = 0;
    channels = 0;
    loopStart = 0;
    loopEnd = 0;
    // FIXME platform dependand code
#if defined(PLATFORM_WIN32)
    SecureZeroMemory ( unknown, sizeof ( unknown ) );
#endif
}

unsigned long PopSound::GetByteSize()
{
    return sizeof ( headerSize ) + sizeof ( dataSize ) + sizeof ( title ) + sizeof ( sampleRate ) + sizeof ( bitsPerSample )
           + sizeof ( channels ) + sizeof ( loopStart ) + sizeof ( loopEnd ) + sizeof ( unknown ) + dataSize;
}

//cPopSound::cPopSound(cWavFile* wav)
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

PopSound::PopSound()
{
    headerSize = 40;
    soundData = NULL;
}

PopSound::~PopSound()
{
    if ( soundData )
        delete[] soundData;
}

} // namespace poplib
