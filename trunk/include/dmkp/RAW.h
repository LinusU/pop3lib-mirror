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

#ifndef _H_DMKP32_POPULOUS_HDR_FUNCTIONS
#define _H_DMKP32_POPULOUS_HDR_FUNCTIONS

#include "global.h"

#define HDR_OTITLE "Open HDR file"
#define HDR_STITLE "Save HDR file"
#define HDR_FILTER "Populous HDR Files (*.hdr)\0*.hdr\0Populous HDR Files (levl20*.hdr)\0levl20*.hdr\0\0"
#define BIT_0 128
#define BIT_1 64
#define BIT_2 32
#define BIT_3 16
#define BIT_4 8
#define BIT_5 4
#define BIT_6 2
#define BIT_7 1

// #pragma comment(lib, "Comdlg32") //needed for dialog functions -get file name etc

namespace poplib {
	
	class HeaderData;
	/* FIXME not crossplatform code
		class RAW {
		public:
			static bool LoadHDR(char* filepath, cHeaderData* pHdr);
			static bool SaveHDR(char* filepath, cHeaderData* pHdr);
			static char* HDRGetFileName(HWND hOwner, bool save);
		};
*/

}; // namespace poplib

#endif /* _H_DMKP32_POPULOUS_HDR_FUNCTIONS */