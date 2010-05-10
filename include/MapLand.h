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

namespace poplib
{
/** Base class for the map land. It represents the mathematical matrix. Matrix element can be accessed using operator(). */
template<typename T>
class Matrix
{
public:
    /** Constructor.
    @param rows Width of the matrix.
    @param cols Height of the matrix. 
    */
    Matrix ( unsigned int rows, unsigned int cols );
    /** Copy constructor. */
    Matrix ( const Matrix<T>& map );
    Matrix<T>& operator= ( const Matrix<T>& map );
    virtual ~Matrix();
    /** Access to the matrix elements for read only purpose.
    @param row Row of the element.
    @param col Column of the element.
    */
    T operator() ( unsigned int row, unsigned int col ) const;
    /** Access to the matrix elements for write purpose.
    @param row Row of the element.
    @param col Column of the element.
    */
    T& operator() ( unsigned int row, unsigned int col );

private:
    T* mdata;
    unsigned int mrows, mcols;

    void copy ( const Matrix& map );
};
/** Populous map is a 128x128 square. */
class MapLand : public Matrix<unsigned int>
{
public:
	/** Constructor. */
    MapLand() : Matrix<unsigned int > ( mwidth, mheight ) {}
    /** Returns the width of the map. */
    int width() const { return mwidth; }
    /** Returns the height of the map. */
    int height() const { return mheight; }
    /** Saves map land to the stream. */
    friend std::ostream& operator<< ( std::ostream& os, const MapLand& obj );
    /** Loades map land from the stream. */
    friend std::istream& operator>> ( std::istream& is, MapLand& obj );

private:
    static const int mwidth = 128;
    static const int mheight = 128;
};

template<typename T>
Matrix<T>::Matrix ( unsigned int rows, unsigned int cols ): mrows(rows), mcols(cols)
{
    mdata = new T[rows * cols];
}

template<typename T>
void Matrix<T>::copy ( const Matrix<T>& map )
{
    mdata = new T[map.mrows * mcols];

    for ( int i = 0; i < map.mrows; ++i )
        for ( int j = 0; j < map.mcols; ++j )
            this->operator() ( i, j ) = map ( i, j );
}

template<typename T>
Matrix<T>::Matrix ( const Matrix<T>& map )
{
    copy ( map );
}

template<typename T>
Matrix<T>& Matrix<T>::operator= ( const Matrix<T>& map )
{
    if ( this == &map )
        return *this;

    delete[] mdata;
    copy ( map );

    return *this;
}

template<typename T>
Matrix<T>::~Matrix ()
{
    delete[] mdata;
}

template<typename T> inline
T Matrix<T>::operator() ( unsigned int row, unsigned int col ) const
{
    return mdata[row * mrows + col];
}

template<typename T> inline
T& Matrix<T>::operator() ( unsigned int row, unsigned int col )
{
    return mdata[row * mrows + col];
}

} // namespace poplib

#endif // _H_POPLIB_MAPLAND__
