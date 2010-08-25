/*
Copyright (C) 2010 Populous Mana Source Development Team

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

#include <fstream>
#include <string>

#include "Mappack.h"
#include "StrUtil.h"
#include "systemUtils/File.h"

int main ( int argc, const char* argv[] )
{
    int i;
    std::list<poplib::MappackMap *> maps;
    std::list<poplib::MappackMap *>::iterator it;
    poplib::Mappack m;
    std::ofstream fout;
    std::string outTextLand = "map_";

    m.importFromDirectory ( "Asgard Worlds I" );
    //m.importFromDirectory ( "The Beginning" );
    maps = m.maps();
    for ( i = 0, it = maps.begin(); it != maps.end(); ++it, ++i )
    {
        UTF16 str[5]; str[0] = 'a'; str[1] = 'b'; str[2] = 'c'; str[3] = 'd'; str[4] = 0;
        (*it)->setMapName(str);
        (*it)->setDescription(str);
        (*it)->addAuthor(str);
        (*it)->addAuthor(str);
        (*it)->addAuthor(str);
    }

    UTF16 str[3];
    str[0] = 's'; str[1] = 's'; str[2] = 0;
    m.setName(str);
    m.setDescription(str);

    m.saveToFile("mappack.p3m");
    m.loadFromFile("mappack.p3m");

    maps = m.maps();
    for ( i = 0, it = maps.begin(); it != maps.end(); ++it, ++i )
    {
        poplib::MapLand* land = ( *it )->mapLand();

        std::string filename = outTextLand + poplib::StrUtil::toString<int> ( i );
        fout.open ( filename.c_str(), std::ios_base::out );
        // save land's height to the file
        for ( unsigned int i = 0; i < land->width(); ++i )
        {
            fout << "\n";
            for ( unsigned int j = 0; j < land->height(); ++j )
            {
                int landPoint = ( *land ) ( i, j );

                if ( landPoint > 1023 )
                    landPoint = 9;
                else if ( landPoint > 900 )
                    landPoint = 8;
                else if ( landPoint > 700 )
                    landPoint = 7;
                else if ( landPoint > 500 )
                    landPoint = 6;
                else if ( landPoint > 400 )
                    landPoint = 5;
                else if ( landPoint > 300 )
                    landPoint = 4;
                else if ( landPoint > 100 )
                    landPoint = 3;
                else if ( landPoint > 50 )
                    landPoint = 2;
                else
                    landPoint = 1;

                fout << landPoint << " ";
            }
        }

        fout.close();
    }

    return 0;
}
