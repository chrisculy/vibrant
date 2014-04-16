/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vquaternion.cpp
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

#include "vmath.h"
#include "vmatrix.h"
#include "vquaternion.h"
#include "vvector.h"

namespace Vibrant
{
    
    Quaternion::Quaternion ( float x, float y, float z, float w )
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    
    Quaternion::~Quaternion ()
    {
        /* stub function */
    }
    
    float Quaternion::GetAngleOfRotation () const
    {
        return 2 * acosf ( this->w );
    }
    
    Vector Quaternion::GetAxisOfRotation () const
    {
        float scale = sqrtf ( this->x * this->x + this->y * this->y + this->z * this->z );
        if ( scale == 0.0f )
        {
            // Undefined result.
            return Vector ();
        }
        else
        {
            float scaleReciprocal = 1.0f / scale;
            return Vector ( this->x * scaleReciprocal, this->y * scaleReciprocal, this->z * scaleReciprocal );
        }
    }
    
    float Quaternion::DotProduct ( const Quaternion& quaternion ) const
    {
        return this->x * quaternion.x + this->y * quaternion.y + this->z * quaternion.z + this->w * quaternion.w;
    }
    
    float Quaternion::GetLength ()
    {
        return sqrtf ( this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w );
    }
    
    Matrix Quaternion::GetMatrix () const
    {
        // Calculate constants that we need.
        float w2 = this->w * this->w;
        float x2 = this->x * this->x;
        float y2 = this->y * this->y;
        float z2 = this->z * this->z;
        
        float twoXY = 2 * this->x * this->y;
        float twoXZ = 2 * this->x * this->z;
        float twoWX = 2 * this->w * this->x;
        float twoWY = 2 * this->w * this->y;
        float twoWZ = 2 * this->w * this->z;
        float twoYZ = 2 * this->y * this->z;
        
        // Construct the matrix values.
        float values[ 16 ];
        
        // First column.
        values[ 0 ] = w2 + x2 - y2 - z2;
        values[ 1 ] = twoXY + twoWZ;
        values[ 2 ] = twoXZ - twoWY;
        values[ 3 ] = 0.0f;
        
        // Second column.
        values[ 4 ] = twoXY - twoWZ;
        values[ 5 ] = w2 - x2 + y2 - z2;
        values[ 6 ] = twoYZ + twoWX;
        values[ 7 ] = 0.0f;
        
        // Third column.
        values[ 8 ] = twoXZ + twoWY;
        values[ 9 ] = twoYZ - twoWX;
        values[ 10 ] = w2 - x2 - y2 + z2;
        values[ 11 ] = 0.0f;
        
        // Fourth column.
        values[ 12 ] = 0.0f;
        values[ 13 ] = 0.0f;
        values[ 14 ] = 0.0f;
        values[ 15 ] = 1.0f;
        
        return Matrix ( values );
    }
    
    Quaternion Quaternion::GetUnitQuaternion ()
    {
        return ( *this ) / this->GetLength ();
    }
    
    void Quaternion::Normalize ()
    {
        ( *this ) /= this->GetLength ();
    }
    
    float Quaternion::GetX () const
    {
        return this->x;
    }
    
    float Quaternion::GetY () const
    {
        return this->y;
    }
    
    float Quaternion::GetZ () const
    {
        return this->z;
    }
    
    float Quaternion::GetW () const
    {
        return this->w;
    }
    
    void Quaternion::SetX ( float x )
    {
        this->x = x;
    }
    
    void Quaternion::SetY ( float y )
    {
        this->y = y;
    }
    
    void Quaternion::SetZ ( float z )
    {
        this->z = z;
    }
    
    void Quaternion::SetW ( float w )
    {
        this->w = w;
    }
    
    const Quaternion& Quaternion::operator= ( const Quaternion quaternion )
    {
        this->x = quaternion.x;
        this->y = quaternion.y;
        this->z = quaternion.z;
        this->w = quaternion.w;
        
        return *this;
    }
    
    bool Quaternion::operator== ( const Quaternion& quaternion ) const
    {
        return this->x == quaternion.x && this->y == quaternion.y && this->z == quaternion.z && this->w == quaternion.w;
    }
    
    bool Quaternion::operator!= ( const Quaternion& quaternion ) const
    {
        return !( *this == quaternion );
    }
    
    Quaternion Quaternion::CreateFromAxisAngle ( Vector& axis, float angle )
    {
        // Make sure the axis is normalized.
        axis.Normalize ();
        
        Quaternion tmp;
        float halfTheta = Math::ToRadians ( angle ) * 0.5f;
        float sinHalfTheta = sinf ( halfTheta );
        
        // Calculate the quaternion values.
        tmp.x = axis.GetX () * sinHalfTheta;
        tmp.y = axis.GetY () * sinHalfTheta;
        tmp.z = axis.GetZ () * sinHalfTheta;
        tmp.w = cosf ( halfTheta );
        
        return tmp;
    }
    
    Quaternion Quaternion::CreateFromAxisAngle ( float x, float y, float z, float angle )
    {
        Vector axis ( x, y, z );
        return Quaternion::CreateFromAxisAngle ( axis, angle );
    }
    
    Quaternion Quaternion::CreateFromMatrix ( const Matrix& matrix )
    {
        Quaternion tmp;
        
        float diagonalX = matrix.GetValue ( 0, 0 );
        float diagonalY = matrix.GetValue ( 1, 1 );
        float diagonalZ = matrix.GetValue ( 2, 2 );
        float diagonalW = matrix.GetValue ( 3, 3 );
        
        float trace = diagonalX + diagonalY + diagonalZ + diagonalW;
        if ( trace >= 0.0f )
        {
            float s = 2.0f * sqrtf ( trace );
            float sReciprocal = 1.0f / s;
            tmp.x = ( matrix.GetValue ( 2, 1 ) - matrix.GetValue ( 1, 2 ) ) * sReciprocal;
            tmp.y = ( matrix.GetValue ( 0, 2 ) - matrix.GetValue ( 2, 0 ) ) * sReciprocal;
            tmp.z = ( matrix.GetValue ( 1, 0 ) - matrix.GetValue ( 0, 1 ) ) * sReciprocal;
            tmp.w = s * 0.25f;
        }
        else
        {
            // The diagonal X is the greatest component.
            if ( diagonalX > diagonalY && diagonalX > diagonalZ )
            {
                // Calculate the quaternion values.
                float s = 2.0f * sqrtf ( matrix.GetValue ( 0, 0 ) - matrix.GetValue ( 1, 1 ) - matrix.GetValue ( 2, 2 ) + 1.0f );
                float sReciprocal = 1.0f / s;
                tmp.x = s * 0.25f;
                tmp.y = ( matrix.GetValue ( 0, 1 ) + matrix.GetValue ( 1, 0 ) ) * sReciprocal;
                tmp.z = ( matrix.GetValue ( 0, 2 ) + matrix.GetValue ( 2, 0 ) ) * sReciprocal;
                tmp.w = ( matrix.GetValue ( 1, 2 ) - matrix.GetValue ( 2, 1 ) ) * sReciprocal;
            }
            // The diagonal Y is the greatest component.
            else if ( diagonalY > diagonalZ )
            {
                // Calculate the quaternion values.
                float s = 2.0f * sqrtf ( matrix.GetValue ( 1, 1 ) - matrix.GetValue ( 0, 0 ) - matrix.GetValue ( 2, 2 ) + 1.0f );
                float sReciprocal = 1.0f / s;
                tmp.x = ( matrix.GetValue ( 0, 1 ) + matrix.GetValue ( 1, 0 ) ) * sReciprocal;
                tmp.y = s * 0.25f;
                tmp.z = ( matrix.GetValue ( 1, 2 ) + matrix.GetValue ( 2, 1 ) ) * sReciprocal;
                tmp.w = ( matrix.GetValue ( 0, 2 ) - matrix.GetValue ( 2, 0 ) ) * sReciprocal;
            }
            // The diagonal Z is the greatest component.
            else
            {
                // Calculate the quaternion values.
                float s = 2.0f * sqrtf ( matrix.GetValue ( 2, 2 ) - matrix.GetValue ( 0, 0 ) - matrix.GetValue ( 1, 1 ) + 1.0f );
                float sReciprocal = 1.0f / s;
                tmp.x = ( matrix.GetValue ( 0, 2 ) + matrix.GetValue ( 2, 0 ) ) * sReciprocal;
                tmp.y = ( matrix.GetValue ( 1, 2 ) + matrix.GetValue ( 2, 1 ) ) * sReciprocal;
                tmp.z = s * 0.25f;
                tmp.w = ( matrix.GetValue ( 0, 1 ) - matrix.GetValue ( 1, 0 ) ) * sReciprocal;
            }
        }
        
        return tmp;
    }
    
    Quaternion Quaternion::Interpolate ( Quaternion prevQuaternion, Quaternion nextQuaternion, float percent, bool useShortestPath,
        float epsilon )
    {
        // Get the angle between the two quaternions.
        float angle = prevQuaternion.DotProduct ( nextQuaternion );
        
        // If we are using the shortest path, then check if
        // the angle is less than zero and negate the first quaternion and the angle.
        if ( useShortestPath && angle < 0.0f )
        {
            prevQuaternion *= -1.0f;
            angle *= -1.0f;
        }
        
        // If the angle is small, just use linear interpolation.
        if ( angle > ( 1.0f - epsilon ) )
        {
            return ( prevQuaternion + ( nextQuaternion - prevQuaternion ) * percent );
        }
        // Use spherical linear interpolation.
        else
        {
            float theta = acosf ( Math::Clamp ( angle, -1.0f, 1.0f ) );
            return ( ( sinf ( ( 1 - percent ) * theta ) * prevQuaternion ) + ( sinf ( percent * theta ) * nextQuaternion ) )
                / sinf ( theta );
        }
    }
    
    Quaternion Quaternion::operator- () const
    {
        return Quaternion ( -this->x, -this->y, -this->z, -this->w );
    }
    
    Quaternion Quaternion::operator+ ( const Quaternion& quaternion ) const
    {
        return Quaternion ( this->x + quaternion.x, this->y + quaternion.y, this->z + quaternion.z, this->w + quaternion.w );
    }
    
    Quaternion Quaternion::operator- ( const Quaternion& quaternion ) const
    {
        return Quaternion ( this->x - quaternion.x, this->y - quaternion.y, this->z - quaternion.z, this->w - quaternion.w );
    }
    
    Quaternion Quaternion::operator* ( const Quaternion& quaternion ) const
    {
        return Quaternion ( this->w * quaternion.x + this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y, this->w
            * quaternion.y + this->y * quaternion.w + this->z * quaternion.x - this->x * quaternion.z, this->w * quaternion.z + this->z
            * quaternion.w + this->x * quaternion.y - this->y * quaternion.x, this->w * quaternion.w - this->x * quaternion.x - this->y
            * quaternion.y - this->z * quaternion.z );
    }
    
    void Quaternion::operator+= ( const Quaternion& quaternion )
    {
        this->x += quaternion.x;
        this->y += quaternion.y;
        this->z += quaternion.z;
        this->w += quaternion.w;
    }
    
    void Quaternion::operator-= ( const Quaternion& quaternion )
    {
        this->x -= quaternion.x;
        this->y -= quaternion.y;
        this->z -= quaternion.z;
        this->w -= quaternion.w;
    }
    
    void Quaternion::operator*= ( const Quaternion& quaternion )
    {
        ( *this ) = ( *this ) * quaternion;
    }
    
    Quaternion Quaternion::operator* ( float scalar ) const
    {
        return Quaternion ( this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar );
    }
    
    Quaternion Quaternion::operator/ ( float scalar ) const
    {
        float reciprocal = 1.0f / scalar;
        return Quaternion ( this->x * reciprocal, this->y * reciprocal, this->z * reciprocal, this->w * reciprocal );
    }
    
    void Quaternion::operator*= ( float scalar )
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        this->w *= scalar;
    }
    
    void Quaternion::operator/= ( float scalar )
    {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        this->w /= scalar;
    }

}
