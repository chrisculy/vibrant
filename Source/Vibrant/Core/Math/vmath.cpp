/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmath.cpp
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

namespace Vibrant
{
    
    // Initialize static members.
    const float PI = 3.14159265f;
    const float Math::EPSILON = 0.0001f;
    const float Math::DEGREES_TO_RADIANS = 0.0174532925f;
    const float Math::RADIANS_TO_DEGREES = 57.2957795f;
    
    float Math::FractionalPart ( float value )
    {
        if ( value < 0.0f )
        {
            value *= -1.0f;
        }

        while ( value >= 1.0f )
        {
            value -= 1.0f;
        }
        return value;
    }
    
    float Math::EvaluateCubicHermiteSpline1D ( float* points, float t )
    {
        // Calculate the coefficients.
        float t2 = t * t;
        float t3 = t2 * t;
        float h0 = ( 2 * t3 ) - ( 3 * t2 ) + 1;
        float h1 = t3 - ( 2 * t2 ) + t;
        float h2 = ( -2 * t3 ) + ( 3 * t2 );
        float h3 = t3 - t2;
        
        // Calculate the value.
        return h0 * points[ 0 ] + h1 * points[ 1 ] + h2 * points[ 3 ] + h3 * points[ 2 ];
    }
    
    float* Math::EvaluateCubicHermiteSpline2D ( float* points, float t )
    {
        // Calculate the coefficients.
        float t2 = t * t;
        float t3 = t2 * t;
        float h0 = ( 2 * t3 ) - ( 3 * t2 ) + 1;
        float h1 = t3 - ( 2 * t2 ) + t;
        float h2 = ( -2 * t3 ) + ( 3 * t2 );
        float h3 = t3 - t2;
        
        // Calculate the value (x and y).
        float* values = new float[ 2 ];
        values[ 0 ] = h0 * points[ 0 ] + h1 * points[ 2 ] + h2 * points[ 6 ] + h3 * points[ 4 ];
        values[ 1 ] = h0 * points[ 1 ] + h1 * points[ 3 ] + h2 * points[ 7 ] + h3 * points[ 5 ];
        
        return values;
    }
    
    float Math::Clamp ( float value, float low, float high )
    {
        if ( value < low )
        {
            return low;
        }
        else if ( value > high )
        {
            return high;
        }
        else
        {
            return value;
        }
    }
    
    bool Math::ApproximatelyEqual ( float firstValue, float secondValue, float epsilon )
    {
        if ( firstValue > secondValue )
        {
            return ( firstValue - secondValue < epsilon );
        }
        else
        {
            return ( secondValue - firstValue < epsilon );
        }
    }
    
    int Math::Round ( float value )
    {
        return (int) ( value + 0.5f );
    }
    
    float Math::Lerp ( float prevKeyTime, float nextKeyTime, float prevKeyValue, float nextKeyValue, float percent )
    {
        return ( ( percent - prevKeyTime ) / ( nextKeyTime - prevKeyTime ) * ( nextKeyValue - prevKeyValue ) ) + prevKeyValue;
    }
    
    float Math::ToRadians ( const float degrees )
    {
        return degrees * Math::DEGREES_TO_RADIANS;
    }
    
    float Math::ToDegrees ( const float radians )
    {
        return radians * Math::RADIANS_TO_DEGREES;
    }
    
    float Math::ToMilliseconds ( const float seconds )
    {
        return seconds * 1000.0f;
    }
    
    float Math::ToSeconds ( const float milliseconds )
    {
        return milliseconds * 0.001f;
    }

}
