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

protected:
    unsigned int mrows, mcols;

private:
    T* mdata;

    void copy ( const Matrix& map );
};
/** Populous map is a 128x128 square. */
class MapLand : public Matrix<unsigned int>
{
public:
    /** Constructor. */
    MapLand() : Matrix<unsigned int > ( 128, 128 ) {}
    /** Returns the width of the map. */
    unsigned int width() const { return mcols; }
    /** Returns the height of the map. */
    unsigned int height() const { return mrows; }
    /** Saves map land to the stream. */
    friend std::ostream& operator<< ( std::ostream& os, const MapLand& obj );
    /** Loades map land from the stream. */
    friend std::istream& operator>> ( std::istream& is, MapLand& obj );
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
    mdata = new T[mcols * map.mrows];

    for ( int i = 0; i < map.mcols; ++i )
        for ( int j = 0; j < map.mrows; ++j )
            this->operator() ( i, j ) = map ( i, j );// TODO use memcopy to copy mapland
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

    delete[] mdata;
    copy ( map );
    mcols = map.mcols;
    mrows = map.mrows;

    return *this;
}

template<typename T>
Matrix<T>::~Matrix ()
{
    delete[] mdata;
}

template<typename T>
T Matrix<T>::operator() ( unsigned int col, unsigned int row ) const
{
    return mdata[row * mcols + col];
}

template<typename T>
T& Matrix<T>::operator() ( unsigned int col, unsigned int row )
{
    return mdata[row * mcols + col];
}

} // namespace poplib

#endif // _H_POPLIB_MAPLAND__
