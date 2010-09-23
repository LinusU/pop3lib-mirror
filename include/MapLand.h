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

#ifndef _H_POPLIB_MAPLAND__
#define _H_POPLIB_MAPLAND__

#include <iostream>
#include <cstring>

#include "global.h"

namespace poplib
{
/** Base class for the map land. It represents the mathematical matrix. Matrix element can be accessed using operator(). */
template<typename T>
class Matrix
{
public:
    /** Constructor.
    @param cols Width of the matrix.
    @param rows Height of the matrix.
    */
    Matrix ( unsigned int cols, unsigned int rows );
    /** Copy constructor. */
    Matrix ( const Matrix<T>& map );
    Matrix<T>& operator= ( const Matrix<T>& map );
    virtual ~Matrix();
    /** Access to the matrix elements for read only purpose.
    @param col Column of the element.
    @param row Row of the element.
    */
    T operator() ( unsigned int col, unsigned int row ) const;
    /** Access to the matrix elements for write purpose.
    @param col Column of the element.
    @param row Row of the element.
    */
    T& operator() ( unsigned int col, unsigned int row );
    /** Saves data to the stream. */
    template<typename S>
    friend std::ostream& operator<<( std::ostream& os, const Matrix<S>& obj );
    /** Loades data from the stream. */
    template<typename S>
    friend std::istream& operator>>( std::istream& is, Matrix<S>& obj );

protected:
    unsigned int mrows, mcols;

private:
    T* mdata;

    void copy ( const Matrix& map );
};

/** Populous map is a 128x128 square. */
class MapLand : public Matrix<SWORD>
{
public:
    /** Constructor. */
    MapLand() : Matrix<SWORD> ( 128, 128 ) {}
    /** Returns the width of the map. */
    unsigned int width() const {
        return mcols;
    }
    /** Returns the height of the map. */
    unsigned int height() const {
        return mrows;
    }
    /** Saves map land details using compact form. Suitable for sending maps over the internet. */
    std::ostream& toCompactForm ( std::ostream& os ) const;
    /** Loades map header details from compact form. */
    std::istream& fromCompactForm ( std::istream& is );
};

template<typename T>
Matrix<T>::Matrix ( unsigned int cols, unsigned int rows ): mcols(cols), mrows(rows)
{
    mdata = new T[cols * rows];
}

template<typename T>
void Matrix<T>::copy ( const Matrix<T>& map )
{
    mdata = new T[mcols * mrows];
    std::memcpy(reinterpret_cast<char *>(mdata), map.mdata, mrows*mcols*sizeof(T));
}

template<typename T>
Matrix<T>::Matrix ( const Matrix<T>& map ): mcols(map.mcols), mrows(map.mrows)
{
    copy ( map );
}

template<typename T>
Matrix<T>& Matrix<T>::operator= ( const Matrix<T>& map )
{
    if ( this == &map )
        return *this;

    mcols = map.mcols;
    mrows = map.mrows;
    delete[] mdata;
    copy ( map );

    return *this;
}

template<typename T>
Matrix<T>::~Matrix ()
{
    delete[] mdata;
}

template<typename T>
T Matrix<T>::operator() ( unsigned int row, unsigned int col ) const
{
    return mdata[col*mrows + row];
}

template<typename T>
T& Matrix<T>::operator() ( unsigned int row, unsigned int col )
{
     return mdata[col*mrows + row];
}

template<typename T>
std::ostream& operator<< ( std::ostream& os, const Matrix<T>& m )
{
    os.write(reinterpret_cast<const char *>(m.mdata), m.mrows*m.mcols*sizeof(T));
    return os;
}

template<typename T>
std::istream& operator>> ( std::istream& is, Matrix<T>& m )
{
    is.read(reinterpret_cast<char *>(m.mdata), m.mrows*m.mcols*sizeof(T));
    return is;
}

} // namespace poplib

#endif // _H_POPLIB_MAPLAND__
