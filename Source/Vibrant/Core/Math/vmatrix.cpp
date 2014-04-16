/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmatrix.cpp
 * 
 * 
 * --  Copyright (c) 2007-2008 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

// Include Precompiled Header.
#include "vprecompiled.h"

#include "varray.h"
#include "vexception.h"
#include "vlog.h"
#include "vmatrix.h"
#include "vreader.h"
#include "vsystem.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Matrix::Matrix ()
    {
        // Initialize to the identity matrix.
        for ( int col = 0; col < 4; col++ )
        {
            for ( int row = 0; row < 4; row++ )
            {
                if ( row == col )
                {
                    this->values[ col * 4 + row ] = 1.0f;
                }
                else
                {
                    this->values[ col * 4 + row ] = 0.0f;
                }
            }
        }
    }
    
    Matrix::Matrix ( float* val )
    {
#ifdef _MSC_VER
        memcpy_s ( this->values, 16 * sizeof ( float ), val, 16 * sizeof ( float ) );
#else
        memcpy ( this->values, val, 16 * sizeof(float) );
#endif
    }
    
    Matrix::Matrix ( Array< float >& val )
    {
        // Make sure the array is the right size.
        if ( val.Size () != 16 )
        {
            throw IllegalArgumentException ( "Matrix::Matrix - Initialization array is of an incorrect size." );
        }
        
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] = val[ i ];
        }
    }
    
    Matrix::Matrix ( Array< float >* val )
    {
        // Make sure the array is the right size.
        if ( val->Size () != 16 )
        {
            throw IllegalArgumentException ( "Matrix::Matrix - Initialization array is of an incorrect size." );
        }
        
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] = ( *val )[ i ];
        }
    }
    
    Matrix::~Matrix ()
    {
        /* stub function */
    }
    
    Matrix Matrix::GetIdentityMatrix ()
    {
        // Create a static identity matrix and initialize
        // it if it hasn't been initialized already.
        static Array< float > identityArray ( 16 );
        static Matrix identity ( identityArray );
        if ( identity.GetValues ()[ 0 ] != 1.0 )
        {
            for ( int r = 0; r < 4; r++ )
            {
                for ( int c = 0; c < 4; c++ )
                {
                    identity.SetValue ( r, c, ( r == c ) ? 1.0f : 0.0f );
                }
            }
        }
        
        // Note: we return a copy, not a reference
        // to the identity matrix so that it can be
        // changed by the user later on.
        return identity;
    }
    
    void Matrix::CopyValues ( float* values ) const
    {
#ifdef _MSC_VER
        memcpy_s ( values, 16 * sizeof ( float ), this->values, 16 * sizeof ( float ) );
#else
        memcpy ( values, this->values, 16 * sizeof(float) );
#endif
    }
    
    float Matrix::GetRotationX ()
    {
        return asinf ( this->values[ 9 ] );
    }
    
    float Matrix::GetRotationY ()
    {
        return asinf ( this->values[ 2 ] );
    }
    
    float Matrix::GetRotationZ ()
    {
        return asinf ( this->values[ 4 ] );
    }
    
    Matrix Matrix::GetTranspose ()
    {
        Matrix tmp;
        
        // First column.
        tmp.values[ 0 ] = this->values[ 0 ];
        tmp.values[ 1 ] = this->values[ 4 ];
        tmp.values[ 2 ] = this->values[ 8 ];
        tmp.values[ 3 ] = this->values[ 12 ];
        
        // Second column.
        tmp.values[ 4 ] = this->values[ 1 ];
        tmp.values[ 5 ] = this->values[ 5 ];
        tmp.values[ 6 ] = this->values[ 9 ];
        tmp.values[ 7 ] = this->values[ 13 ];
        
        // Third column.
        tmp.values[ 8 ] = this->values[ 2 ];
        tmp.values[ 9 ] = this->values[ 6 ];
        tmp.values[ 10 ] = this->values[ 10 ];
        tmp.values[ 11 ] = this->values[ 14 ];
        
        // Fourth column.
        tmp.values[ 12 ] = this->values[ 3 ];
        tmp.values[ 13 ] = this->values[ 7 ];
        tmp.values[ 14 ] = this->values[ 11 ];
        tmp.values[ 15 ] = this->values[ 15 ];
        
        return tmp;
    }
    
    float Matrix::GetValue ( int row, int col ) const
    {
        // Make sure the index is valid.
        if ( ( row < 0 ) || ( row > 3 ) || ( col < 0 ) || ( col > 3 ) )
        {
            throw IndexOutOfBoundsException ( "Matrix::GetValue - An index is out of bounds." );
        }

        int index = col * 4 + row;
        return this->values[ index ];
    }
    
    const float* Matrix::GetValues () const
    {
        return this->values;
    }
    
    void Matrix::SetValue ( int row, int col, float value )
    {
        // Make sure the index is valid.
        if ( ( row < 0 ) || ( row > 3 ) || ( col < 0 ) || ( col > 3 ) )
        {
            throw IndexOutOfBoundsException ( "Matrix::SetValue - An index is out of bounds." );
        }

        int index = col * 4 + row;
        this->values[ index ] = value;
    }
    
    const int Matrix::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Matrix::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "matrix" );
        writer->WriteProperty ( "values", this->values, 16 );
        writer->EndObject ();
    }
    
    void Matrix::Read ( Reader* reader )
    {
        reader->BeginObject ( "matrix" );
        reader->ReadProperty ( "values", this->values, 16 );
        reader->EndObject ();
    }
    
    const Matrix& Matrix::operator= ( Matrix x )
    {
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] = x.GetValues ()[ i ];
        }
        
        return *this;
    }
    
    Matrix Matrix::operator* ( float x )
    {
        Matrix tmp;
        for ( int i = 0; i < 16; i++ )
        {
            tmp.values[ i ] = this->values[ i ] * x;
        }
        
        return tmp;
    }
    
    Matrix Matrix::operator/ ( float x )
    {
        Matrix tmp;
        for ( int i = 0; i < 16; i++ )
        {
            tmp.values[ i ] = this->values[ i ] / x;
        }
        
        return tmp;
    }
    
    void Matrix::operator*= ( float x )
    {
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] *= x;
        }
    }
    
    void Matrix::operator/= ( float x )
    {
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] /= x;
        }
    }
    
    void Matrix::operator- ()
    {
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] *= -1.0f;
        }
    }
    
    Matrix Matrix::operator* ( const Matrix x ) const
    {
        Matrix tmp;
        int colIndex = 0;
        for ( int row = 0; row < 4; row++ )
        {
            for ( int col = 0; col < 4; col++ )
            {
                colIndex = 4 * col;
                tmp.values[ row + colIndex ] = this->values[ row ] * x.GetValues ()[ colIndex ] + this->values[ row + 4 ]
                    * x.GetValues ()[ colIndex + 1 ] + this->values[ row + 8 ] * x.GetValues ()[ colIndex + 2 ] + this->values[ row + 12 ]
                    * x.GetValues ()[ colIndex + 3 ];
            }
        }
        
        return tmp;
    }
    
    Matrix Matrix::operator+ ( const Matrix x ) const
    {
        Matrix tmp;
        for ( int i = 0; i < 16; i++ )
        {
            tmp.values[ i ] = this->values[ i ] + x.GetValues ()[ i ];
        }
        
        return tmp;
    }
    
    Matrix Matrix::operator- ( const Matrix x ) const
    {
        Matrix tmp;
        for ( int i = 0; i < 16; i++ )
        {
            tmp.values[ i ] = this->values[ i ] - x.GetValues ()[ i ];
        }
        
        return tmp;
    }
    
    void Matrix::operator*= ( const Matrix x )
    {
        Matrix tmp = *this;
        int colIndex = 0;
        for ( int row = 0; row < 4; row++ )
        {
            for ( int col = 0; col < 4; col++ )
            {
                colIndex = 4 * col;
                this->values[ row + colIndex ] = tmp.values[ row ] * x.GetValues ()[ colIndex ] + tmp.values[ row + 4 ]
                    * x.GetValues ()[ colIndex + 1 ] + tmp.values[ row + 8 ] * x.GetValues ()[ colIndex + 2 ] + tmp.values[ row + 12 ]
                    * x.GetValues ()[ colIndex + 3 ];
            }
        }
    }
    
    void Matrix::operator+= ( const Matrix x )
    {
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] += x.GetValues ()[ i ];
        }
    }
    
    void Matrix::operator-= ( const Matrix x )
    {
        for ( int i = 0; i < 16; i++ )
        {
            this->values[ i ] -= x.GetValues ()[ i ];
        }
    }
    
    Log& operator<< ( Log& log, const Matrix val )
    {
        for ( int i = 0; i < 16; i += 4 )
        {
            log << "\n[" << val.GetValues ()[ i ] << ',';
            log << val.GetValues ()[ i + 1 ] << ',';
            log << val.GetValues ()[ i + 2 ] << ',';
            log << val.GetValues ()[ i + 3 ] << "]\n";
        }
        return log;
    }

}
