/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvector.cpp
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

#include "vreader.h"
#include "vsystem.h"
#include "vvector.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Vector::Vector ( float x, float y, float z )
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    Vector::Vector ( const Vector &vector )
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;
    }
    
    Vector::~Vector ()
    {
        /* stub function */
    }
    
    float Vector::GetX () const
    {
        return x;
    }
    
    float Vector::GetY () const
    {
        return y;
    }
    
    float Vector::GetZ () const
    {
        return z;
    }
    
    void Vector::SetX ( float x )
    {
        this->x = x;
    }
    
    void Vector::SetY ( float y )
    {
        this->y = y;
    }
    
    void Vector::SetZ ( float z )
    {
        this->z = z;
    }
    
    const int Vector::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Vector::Write ( Writer* writer ) const
    {
        writer->BeginObject ( "vector" );
        writer->WriteProperty ( "x", this->x );
        writer->WriteProperty ( "y", this->y );
        writer->WriteProperty ( "z", this->z );
        writer->EndObject ();
    }
    
    void Vector::Read ( Reader* reader )
    {
        reader->BeginObject ( "vector" );
        reader->ReadProperty ( "x", &this->x );
        reader->ReadProperty ( "y", &this->y );
        reader->ReadProperty ( "z", &this->z );
        reader->EndObject ();
    }
    
    const Vector& Vector::operator= ( const Vector &vector )
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;
        
        return *this;
    }
    
    const bool Vector::operator== ( const Vector &vector ) const
    {
        return ( ( x == vector.x ) && ( y == vector.y ) && ( z == vector.z ) );
    }
    
    const bool Vector::operator!= ( const Vector &vector ) const
    {
        return !( *this == vector );
    }
    
    const Vector Vector::operator+ ( const Vector &vector ) const
    {
        return Vector ( x + vector.x, y + vector.y, z + vector.z );
    }
    
    const Vector& Vector::operator+= ( const Vector &vector )
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        
        return *this;
    }
    
    const Vector Vector::operator- ( const Vector &vector ) const
    {
        return Vector ( x - vector.x, y - vector.y, z - vector.z );
    }
    
    const Vector Vector::operator- () const
    {
        return Vector ( -x, -y, -z );
    }
    
    const Vector& Vector::operator-= ( const Vector &vector )
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
        
        return *this;
    }
    
    const Vector& Vector::operator*= ( const float &scalar )
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        
        return *this;
    }
    
    const Vector& Vector::operator/= ( const float &scalar )
    {
        // Multiplication is faster, so just multiply by reciprocal.
        float recip = 1 / scalar;
        
        x *= recip;
        y *= recip;
        z *= recip;
        
        return *this;
    }
    
    const Vector Vector::operator* ( const float &scalar ) const
    {
        return Vector ( x * scalar, y * scalar, z * scalar );
    }
    
    const Vector Vector::operator/ ( const float &scalar ) const
    {
        float recip = 1 / scalar;
        return Vector ( x * recip, y * recip, z * recip );
    }
    
    const Vector Vector::CrossProduct ( const Vector &vector ) const
    {
        return Vector ( y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x );
    }
    
    const float Vector::DotProduct ( const Vector &vector ) const
    {
        return x * vector.x + y * vector.y + z * vector.z;
    }
    
    const float Vector::Length () const
    {
        return sqrt ( x * x + y * y + z * z );
    }
    
    const Vector Vector::UnitVector () const
    {
        return ( *this ) / Length ();
    }
    
    void Vector::Normalize ()
    {
        ( *this ) /= Length ();
    }
    
    const float inline Vector::Angle ( const Vector &normal ) const
    {
        return acos ( this->DotProduct ( normal ) );
    }
    
    const Vector inline Vector::Reflection ( const Vector &normal ) const
    {
        const Vector tmp = this->UnitVector ();
        return ( tmp - normal * 2.0 * ( tmp.DotProduct ( normal ) ) ) * ( this->Length () );
    }

}
