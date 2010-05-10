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

#ifndef _H_DMKP32_COLOUR_CLASS__
#define _H_DMKP32_COLOUR_CLASS__

#define BYTES_PER_PIXEL 4 //How many bytes represent a colour. ALWAYS 4!

typedef unsigned long COLORREF, DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;

//#define ARGB(a,r,g,b)          ((COLORREF)((((BYTE)(a)|((WORD)((BYTE)(r))<<8))|(((DWORD)(BYTE)(g))<<16)) | (((DWORD)(BYTE)(b)) <<24)))
//#define RGBX(r, g, b)			RGB(r,g,b)
#define ARGB(a, r, g, b)		RGB(r, g, b)

namespace poplib
{

class Colour
{
public:
    Colour();
    Colour ( const Colour& copy );
    Colour ( const unsigned long ARGBcolour );
    Colour ( const unsigned char R, const unsigned char G, const unsigned char B );
    Colour ( const unsigned char A, const unsigned char R, const unsigned char G, const unsigned char B );
    //unsigned long ToARGB();
    //unsigned long ToARGB() const;

    unsigned char A() const;
    unsigned char R() const;
    unsigned char G() const;
    unsigned char B() const;
    static Colour Blend ( const unsigned char R, const unsigned char G, const unsigned char B, const Colour* withARGBColour );
    const static int nBytesPerPixel = BYTES_PER_PIXEL;

    Colour& operator= ( const Colour& colour );

private:
    unsigned char _A, _R, _G, _B;
};

} // namespace util

#endif /* _H_DMKP32_COLOUR_CLASS__ */
