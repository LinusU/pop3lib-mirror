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

#include "File.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "FileInfo.h"

namespace poplib
{

FileInfo* File::OpenInfo ( const char *path )
{
    return FileInfo::OpenFile ( path );//new cFileInfo(path);
}

FileReader* File::OpenRead ( const char* path )
{
    return FileReader::OpenFile ( path );//new cFileReader(path);
}

FileWriter* File::OpenWrite ( const char* path )
{
    return FileWriter::OpenFile ( path );//new cFileWriter(path);
}

} // namespace poplib
