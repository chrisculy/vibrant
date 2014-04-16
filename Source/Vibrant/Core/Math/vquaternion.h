/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vquaternion.h
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

#ifndef VIBRANT_QUATERNION_H
#define VIBRANT_QUATERNION_H

#include "vmatrix.h"
#include "vvector.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the functionality of a quaternion in 3D space.
     * 
     * @author Chris Culy
     */
    class VAPI Quaternion
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param x The x component.
             * @param y The y component.
             * @param z The z component.
             * @param w The w component.
             */
            Quaternion ( float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f );

            /**
             * @brief Destructor.
             */
            ~Quaternion ();

            /**
             * @brief Retrieves the angle of rotation (in radians).
             * 
             * @return The angle of rotation.
             */
            float GetAngleOfRotation () const;

            /**
             * @brief Retrieves the axis of rotation.
             * 
             * <b>Note:</b> If the <code>scale</code> ( <code>scale = sqrt (x*x + y*y + z*z)</code> )
             * is zero, the result is undefined.
             * 
             * @return The axis of rotation.
             */
            Vector GetAxisOfRotation () const;

            /**
             * @brief Retrieves the dot product of this quaternion and the given quaternion.
             * 
             * @param quaternion The quaternion to compute the dot product with.
             * @return The dot product of the two quaternions.
             */
            float DotProduct ( const Quaternion& quaternion ) const;

            /**
             * @brief Retrieves the length (or magnitude) of the quaternion.
             * 
             * @return The length of the quaternion.
             */
            float GetLength ();

            /**
             * @brief Retrieves the matrix representation of the quaternion.
             * 
             * @return The matrix representation of the quaternion.
             */
            Matrix GetMatrix () const;

            /**
             * @brief Retrieves the quaternion in unit (normalized) form.
             * 
             * @return The unit quaternion.
             */
            Quaternion GetUnitQuaternion ();

            /**
             * @brief Normalizes the quaternion.
             */
            void Normalize ();

            /**
             * @brief Retrieves the x component.
             * 
             * @return The x component.
             */
            float GetX () const;

            /**
             * @brief Retrieves the y component.
             * 
             * @return The y component.
             */
            float GetY () const;

            /**
             * @brief Retrieves the z component.
             * 
             * @return The z component.
             */
            float GetZ () const;

            /**
             * @brief Retrieves the w component.
             * 
             * @return The w component.
             */
            float GetW () const;

            /**
             * @brief Sets the x component.
             * 
             * @param x The x component.
             */
            void SetX ( float x );

            /**
             * @brief Sets the y component.
             * 
             * @param y The y component.
             */
            void SetY ( float y );

            /**
             * @brief Sets the z component.
             * 
             * @param z The z component.
             */
            void SetZ ( float z );

            /**
             * @brief Sets the w component.
             * 
             * @param w The w component.
             */
            void SetW ( float w );

            /**
             * @brief Assigns the given quaternion to this quaternion
             * 
             * @param quaternion The quaternion to assign to this quaternion.
             * @return This quaternion after the assignment has been performed.
             */
            const Quaternion& operator= ( const Quaternion quaternion );

            /**
             * @brief Tests equality between this quaternion and the given quaternion.
             * 
             * @param quaternion The quaternion to test equality with.
             * @return <code>true</code> if the quaternions are equal; <code>false</code> otherwise.
             */
            bool operator== ( const Quaternion& quaternion ) const;

            /**
             * @brief Tests inequality between this quaternion and the given quaternion.
             * 
             * @param quaternion The quaternion to test inequality with.
             * @return <code>true</code> if the quaternions are not equal; <code>false</code> otherwise.
             */
            bool operator!= ( const Quaternion& quaternion ) const;

            /**
             * @brief Creates a Quaternion from the given axis angle.
             * 
             * @param axis The axis to rotate about.
             * @param angle The angle of rotation (in degrees).
             */
            static Quaternion CreateFromAxisAngle ( Vector& axis, float angle );

            /**
             * @brief Creates a Quaternion from the given axis angle.
             * 
             * @param x The x component of the axis to rotate about.
             * @param y The y component of the axis to rotate about.
             * @param z The z component of the axis to rotate about.
             * @param angle The angle of rotation (in degrees).
             */
            static Quaternion CreateFromAxisAngle ( float x, float y, float z, float angle );

            /**
             * @brief Creates a Quaternion from the given matrix.
             * 
             * @param matrix The matrix to construct the quaternion from.
             */
            static Quaternion CreateFromMatrix ( const Matrix& matrix );

            /**
             * @brief Interpolates between the two given unit quaternions
             * (note that it is assumed the quaternions are normalized).
             * 
             * @param prevQuaternion The previous quaternion value.
             * @param nextQuaternion The next quaternion value.
             * @param percent The percent in between the two values.
             * @param useShortestPath Whether the interpolation should use the shortest path or not.
             * @param epsilon The epsilon for using linear interpolation instead of spherical linear interpolation.
             * @return The interpolated quaternion value.
             */
            static Quaternion Interpolate ( Quaternion prevQuaternion, Quaternion nextQuaternion, float percent, bool useShortestPath =
                false, float epsilon = 0.05f );

            //************************ General Interface ***********************//
            

            //********************* Mathematical Operators *********************//

            /**
             * @brief Performs quaternion negation.
             * 
             * @return The negative of this quaternion.
             */
            Quaternion operator- () const;

            /**
             * @brief Performs quaternion addition.
             * 
             * @param quaternion The quaternion to add.
             * @return The sum of the two quaternions.
             */
            Quaternion operator+ ( const Quaternion& quaternion ) const;

            /**
             * @brief Performs quaternion subtraction.
             * 
             * @param quaternion The quaternion to subtract.
             * @return The difference of the two quaternions.
             */
            Quaternion operator- ( const Quaternion& quaternion ) const;

            /**
             * @brief Performs quaternion multiplication.
             * 
             * @param quaternion The quaternion to multiply by.
             * @return The result of multiplying the two quaternions.
             */
            Quaternion operator* ( const Quaternion& quaternion ) const;

            /**
             * @brief Performs quaternion addition and assigns the result to this quaternion.
             * 
             * @param quaternion The quaternion to add.
             */
            void operator+= ( const Quaternion& quaternion );

            /**
             * @brief Performs quaternion subtraction and assigns the result to this quaternion.
             * 
             * @param quaternion The quaternion to subtract.
             */
            void operator-= ( const Quaternion& quaternion );

            /**
             * @brief Performs quaternion multiplication and assigns the result to this quaternion.
             * 
             * @param quaternion The quaternion to multiply by.
             */
            void operator*= ( const Quaternion& quaternion );

            /**
             * @brief Performs scalar-quaternion multiplication.
             * 
             * @param scalar The scalar to multiply by.
             * @return The product of the quaternion and the scalar.
             */
            Quaternion operator* ( float scalar ) const;

            /**
             * @brief Performs scalar-quaternion division.
             * 
             * @param scalar The scalar to divide by.
             * @return The quotient of the quaternion and scalar.
             */
            Quaternion operator/ ( float scalar ) const;

            /**
             * @brief Performs scalar-quaternion multiplication and assigns the result to this quaternion.
             * 
             * @param scalar The scalar to multiply by.
             */
            void operator*= ( float scalar );

            /**
             * @brief Performs scalar-quaternion division and assigns the result to this quaternion.
             * 
             * @param scalar The scalar to divide by.
             */
            void operator/= ( float scalar );

            //********************* Mathematical Operators *********************//

        private:
            
            /** @brief Holds the x component. */
            float x;

            /** @brief Holds the y component. */
            float y;

            /** @brief Holds the z component. */
            float z;

            /** @brief Holds the w component. */
            float w;
    };
    
    /**
     * @brief Pre-multiplies the quaternion by the given scalar.
     * 
     * @param scalar The scalar to multiply by.
     * @param quaternion The quaternion to multiply.
     * @return The product of the quaternion and the scalar.
     */
    inline const Quaternion operator* ( const float scalar, const Quaternion& quaternion )
    {
        return quaternion * scalar;
    }

}

#endif
