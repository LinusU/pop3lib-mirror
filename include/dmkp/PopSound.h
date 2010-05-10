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


#ifndef _H_DMKP32_POPULOUS_CPOPSOUND__
#define _H_DMKP32_POPULOUS_CPOPSOUND__

typedef unsigned int uint;
typedef unsigned short uint16;

namespace poplib {

		class PopSound {
		public:
			uint headerSize;
			uint dataSize;
			char title[16];
			uint16 sampleRate;
			unsigned char bitsPerSample;
			unsigned char channels;
			uint loopStart;
			uint loopEnd;
			unsigned char unknown[4];
			unsigned char* soundData;

			PopSound();
			
			//cPopSound(cWavFile* wav);
			~PopSound();


			unsigned long GetByteSize();


			PopSound* Clone();
			void Delete();
		};

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_CPOPSOUND__ */