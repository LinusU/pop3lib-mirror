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

#ifndef _H_DMKP32_POPULOUS_SOUND_EDITOR__
#define _H_DMKP32_POPULOUS_SOUND_EDITOR__

#define SDT_EXT ".sdt"
#define SDT_OTITLE "Open Populous SDT file"
#define SDT_FILTER "Populous Sound File (*.sdt)\0*.sdt\0\0"
#define SDT_STITLE "Save Populous SDT file"

#pragma comment(lib, "winmm.lib")

namespace poplib
{

/* FIXME not crossplatform code
class cPopSound;
class cWavFile;

	cPopSound* cPopSoundFromWAV(cWavFile* wav);
	cWavFile* cWavFileFromPOP(cPopSound* p);
	char* SDTGetFileName(HWND hwndOwner, bool save);
	void PlaySoundFile(cWavFile* wav);

	class cPopSoundManager {
	private:
		int nSounds;
		cPopSound* pSounds;
		//char currentFile[MAX_PATH + 1];


	public:
		cPopSoundManager();
		~cPopSoundManager();

		bool SaveFile(char* filename);
		cPopSound* GetSound(unsigned int index);
		bool ReplaceSound(unsigned int index, cPopSound* pSnd);
		bool LoadFile(char* filename);

		unsigned int GetNSounds();
	};
*/

} // namespace poplib

#endif /* _H_DMKP32_POPULOUS_SOUND_EDITOR__ */
