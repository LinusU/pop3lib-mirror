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

#include "Colour.h"

namespace poplib
{

Colour::Colour()
{
    _A = 255;
    _R = 0;
    _G = 0;
    _B = 0;
}

Colour::Colour ( const Colour& copy )
{
    _A = copy._A;
    _R = copy._R;
    _G = copy._G;
    _B = copy._B;
}

Colour::Colour ( const unsigned long ARGBcolour )
{
    unsigned char buf[4];
    * ( ( int* ) buf ) = ARGBcolour;

    _A = buf[0];
    _R = buf[1];
    _G = buf[2];
    _B = buf[3];
}

Colour::Colour ( const unsigned char R, const unsigned char G, const unsigned char B )
{
    _A = 255;
    _R = R;
    _G = G;
    _B = B;
}

Colour::Colour ( const unsigned char A, const unsigned char R, const unsigned char G, const unsigned char B )
{
    _A = A;
    _R = R;
    _G = G;
    _B = B;
}

//unsigned long cColour::ToARGB()
//{
//	return RGB(_A,_R,_G,_B);
//}

//unsigned long cColour::ToARGB() const
//{
//	return RGB(_A,_R,_G,_B);
//}

unsigned char Colour::A() const
{
    return _A;
}

unsigned char Colour::R() const
{
    return _R;
}

unsigned char Colour::G() const
{
    return _G;
}

unsigned char Colour::B() const
{
    return _B;
}

Colour Colour::Blend ( const unsigned char R, const unsigned char G, const unsigned char B, const Colour *withARGBColour )
{
    //draw with transparency/blend the two pixels
    int oldBlue = withARGBColour->B();
    int oldGreen = withARGBColour->G();
    int oldRed = withARGBColour->R();
    double alpha = ( double ) ( withARGBColour->A() ) / ( double ) ( 256 );

    unsigned char newBlue = ( unsigned char ) ( ( double ) B * alpha + ( double ) oldBlue * ( double ) ( 1 - alpha ) );
    unsigned char newRed = ( unsigned char ) ( ( double ) R * alpha + ( double ) oldRed * ( double ) ( 1 - alpha ) );
    unsigned char newGreen = ( unsigned char ) ( ( double ) G * alpha + ( double ) oldGreen * ( double ) ( 1 - alpha ) );

    return Colour ( 255, newRed,newGreen,newBlue );
}


Colour& Colour::operator= ( const Colour& colour )
{
    _A = colour._A;
    _R = colour._R;
    _G = colour._G;
    _B = colour._B;

    return *this;
}

} // namespace util