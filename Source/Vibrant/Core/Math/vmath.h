/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmath.h
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

#ifndef VIBRANT_MATH_H
#define VIBRANT_MATH_H

namespace Vibrant
{
    
    /**
     * @brief Provides general mathematical functions.
     * 
     * @author Chris Culy
     */
    class Math
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Returns the absolute value of the fractional part of the given value.
             * 
             * @param value The value to retrieve the fractional part of.
             * @return The absolute value of the fractional part of the given value.
             */
            static float FractionalPart ( float value );

            /**
             * @brief Evaluates a one-dimensional cubic Hermite spline for the given 't.'
             * 
             * See http://en.wikipedia.org/wiki/Cubic_Hermite_spline for more information.
             * 
             * @param points The points for the spline (must contain 4 floats in the form:
             *      start point, first control tangent, second control tangent, last control point).
             * @param t The t parameter for the cubic Hermite spline function.
             * @return The evaluated value.
             */
            static float EvaluateCubicHermiteSpline1D ( float* points, float t );

            /**
             * @brief Evaluates a cubic Hermite curve for the given 't.'
             * 
             * See http://en.wikipedia.org/wiki/Cubic_Hermite_spline for more information.
             * 
             * @param points The points for the spline (must contain 8 floats in the form:
             *      start points (x, y), first control tangents (x, y), second control
             *      tangents (x, y), last points (x, y)).
             * @param t The t parameter for the cubic Hermite spline function.
             * @return An array of two floats in the form[ x, y ] for the evaluated point
             *      (Note: the user is responsible for destroying this array).
             */
            static float* EvaluateCubicHermiteSpline2D ( float* points, float t );

            /**
             * @brief Clamps the given value between the given range.
             * 
             * @param value The value to clamp.
             * @param low The lowest valid value.
             * @param high The highest valid value.
             * @return The clamped value.
             */
            static float Clamp ( float value, float low, float high );

            /**
             * @brief Retrieves whether the first value is approximately equal to the second value
             * (within the range of the given epsilon from the second value).
             * 
             * @param firstValue The first value to compare.
             * @param secondValue The second value to compare.
             * @param epsilon The margin of error.
             * @return <code>true</code> if the two values are within the given epsilon
             *      from each other; <code>false</code> otherwise.
             */
            static bool ApproximatelyEqual ( float firstValue, float secondValue, float epsilon = Math::EPSILON );

            /**
             * @brief Rounds the given floating point value.
             * 
             * @param value The value to round.
             * @return The rounded value as an integer.
             */
            static int Round ( float value );

            /**
             * @brief Performs linear interpolation of the given values.
             * 
             * @param prevKeyTime The previous key time.
             * @param nextKeyTime The next key time.
             * @param prevKeyValue The previous key value.
             * @param nextKeyValue The next key value.
             * @param percent The percentage between the two keys that the value should be evaluated at.
             * @return The interpolated value.
             */
            static float Lerp ( float prevKeyTime, float nextKeyTime, float prevKeyValue, float nextKeyValue, float percent );

            /**
             * @brief Converts the given value from degrees to radians.
             * 
             * @param degrees The value in degrees.
             * @return The value in radians.
             */
            static float ToRadians ( const float degrees );

            /**
             * @brief Converts the given value from radians to degrees.
             * 
             * @param radians The value in radians.
             * @return The value in degrees.
             */
            static float ToDegrees ( const float radians );

            /**
             * @brief Converts the given value from seconds to milliseconds.
             * 
             * @param seconds The value in seconds.
             * @return The value in milliseconds.
             */
            static float ToMilliseconds ( const float seconds );

            /**
             * @brief Converts the given value from milliseconds to seconds.
             * 
             * @param milliseconds The value in milliseconds.
             * @return The value in seconds.
             */
            static float ToSeconds ( const float milliseconds );

            /** Holds the pi constant. */
            static const float PI;

            //************************ General Interface ***********************//

        private:
            
            /** @brief Represents the default error margin for calculations. */
            static const float EPSILON;

            /** @brief Holds the conversion ratio from degrees to radians. */
            static const float DEGREES_TO_RADIANS;

            /** @brief Holds the conversion ratio from radians to degrees. */
            static const float RADIANS_TO_DEGREES;
    };

}

#endif
