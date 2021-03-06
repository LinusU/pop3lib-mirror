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

#include <string>
#include <iostream>
#include <fstream>

#include "MapDat.h"

int main ( int argc, const char* argv[] )
{
    using poplib::MapDat;
    using poplib::MapLand;

    std::string filePath ( "levl2131.dat" ); // map to load
    std::string outTextLand ( "mapLand.txt" ); // file to store map land in text form
    std::string compactFile("temp_compact.dat");
    std::string tempMapFileName("temp.dat");
    std::ofstream fout;
    std::ifstream fin;

    MapDat m1, m2, m3;
    m1.loadMapDat( filePath ); // load map details
    m2 = m1; // test copy operator
    fout.open ( compactFile.c_str(), std::ios_base::out );
    m2.saveMapDatCompactForm(fout); // store in compact form
    fout.close();
    std::cout << "Loaded map has been saved in compact form to the file: " << compactFile << std::endl;

    fin.open ( compactFile.c_str(), std::ios_base::in );
    m3.loadMapDatCompactForm(fin); // load from compact form
    fin.close();
    fout.open ( outTextLand.c_str(), std::ios_base::out );

    MapLand* land = m3.mapLand();

    // save land's height to the file
    for ( unsigned int i = 0; i < land->width(); ++i )
    {
        fout << "\n";
        for ( unsigned int j = 0; j < land->height(); ++j )
        {
            int landPoint = ( *land ) ( i, j );

            if ( landPoint > 1000 )
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

    std::cout << "Compact map '" << compactFile << "' loaded succesful and land saved to the file '" << outTextLand << "'" <<std::endl;
    m2.saveMapDat(tempMapFileName);
    std::cout << "Copy of the map has been saved to the file '" << tempMapFileName <<"'\n";

    return 0;
}
