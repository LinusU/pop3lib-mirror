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

#ifndef _H_DMKP32_STRINGBUILDER_CLASS__
#define _H_DMKP32_STRINGBUILDER_CLASS__

namespace poplib {
	
	// TODO do we need classes like that ?
		class cStringBuilder
		{
		public:
			cStringBuilder();
			~cStringBuilder();

			bool Append(char* str1);
			int StrLength();
			char* ToString();
			
		private:
			char* string;
			int ArraySize();
			int Length;

		};

} // namespace poplib

#endif /* _H_DMKP32_STRINGBUILDER_CLASS__ */