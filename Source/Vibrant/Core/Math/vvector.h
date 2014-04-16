/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvector.h
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

#ifndef VIBRANT_VECTOR_H
#define VIBRANT_VECTOR_H

#include "vreader.h"
#include "vserializable.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates a vector in 3D space.
     * 
     * @author Chris Culy
     */
    class VAPI Vector : public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param x The vector's x coordinate.
             * @param y The vector's y coordinate.
             * @param z The vector's z coordinate.
             */
            Vector ( float x = 0.0, float y = 0.0, float z = 0.0 );

            /**
             * @brief Copy constructor.
             * 
             * @param vector The vector to copy into this vector.
             */
            Vector ( const Vector &vector );

            /**
             * @brief Destructor.
             */
            virtual ~Vector ();

            /**
             * @brief Retrieves the x value.
             * 
             * @return The x value.
             */
            float GetX () const;

            /**
             * @brief Retrieves the y value.
             * 
             * @return The y value.
             */
            float GetY () const;

            /**
             * @brief Retrieves the z value.
             * 
             * @return The z value.
             */
            float GetZ () const;

            /**
             * @brief Sets the x value.
             * 
             * @param x The x value.
             */
            void SetX ( float x );

            /**
             * @brief Sets the y value.
             * 
             * @param y The y value.
             */
            void SetY ( float y );

            /**
             * @brief Sets the z value.
             * 
             * @param z The z value.
             */
            void SetZ ( float z );

            //************************ General Interface ***********************//
            

            //************************ Streaming system ************************//

            /**
             * @see Serializable#GetDiskSize()
             */
            const int GetDiskSize () const;

            /**
             * @see Serializable#Write(Writer*)
             */
            void Write ( Writer* writer ) const;

            /**
             * @see Serializable#Read(Reader*)
             */
            void Read ( Reader* reader );

            //************************ Streaming system ************************//
            

            //********************* Mathematical Operators *********************//

            /**
             * @brief Assignment operator.
             * 
             * @param vector The vector to assign to this vector.
             * @return The result of the assignment
             *      (this vector after assignment).
             */
            const Vector& operator= ( const Vector &vector );

            /**
             * @brief Equality operator.
             * 
             * @param vector The vector to test against
             *      this vector for equality.
             * @return <code>true</code> if the two vectors are
             *      equal; <code>false</code> otherwise.
             */
            const bool operator== ( const Vector &vector ) const;

            /**
             * @brief Inequality operator.
             * 
             * @param vector The vector to test against
             *      this vector for inequality.
             * @return <code>true</code> if the two vectors are
             *      not equal; <code>false</code> otherwise.
             */
            const bool operator!= ( const Vector &vector ) const;

            /**
             * @brief Addition operator.
             * 
             * @param vector The vector to add to this vector.
             * @return The sum of the vectors.
             */
            const Vector operator+ ( const Vector &vector ) const;

            /**
             * @brief Addition-equals operator.
             * 
             * @param vector The vector to add to this vector.
             * @returns The result of the addition and assignment
             *      (this vector after the sum has been stored in it).
             */
            const Vector& operator+= ( const Vector &vector );

            /**
             * @brief Subtraction operator.
             * 
             * @param vector The vector to subtract from this vector.
             * @return The difference between the two vectors.
             */
            const Vector operator- ( const Vector &vector ) const;

            /**
             * @brief Negation operator.
             * 
             * @returns The negative of this vector.
             */
            const Vector operator- () const;

            /**
             * @brief Subtraction-equals operator.
             * 
             * @param vector The vector to subtract from this vector.
             * @return The result of the subtraction and assignment
             *      (this vector after the difference has been stored in it).
             */
            const Vector& operator-= ( const Vector &vector );

            /**
             * @brief Scalar multiplication-equals operator.
             * 
             * @param scalar The scalar to multiply this vector by.
             * @returns The result of scalar multiplication and assignment
             *      (this vector after the scalar product has been stored in it).
             */
            const Vector& operator*= ( const float &scalar );

            /**
             * @brief Scalar division-equals operator.
             * 
             * @param scalar The scalar to divide this vector by.
             * @return The result of scalar division and assignment
             *      (this vector after the scalar quotient has been stored in it).
             */
            const Vector& operator/= ( const float &scalar );

            /**
             * @brief Scalar multiplication operator.
             * 
             * @param scalar The scalar to multiply this vector by.
             * @return The scalar product of the given scalar and this vector.
             */
            const Vector operator* ( const float &scalar ) const;

            /**
             * @brief Scalar division operator.
             * 
             * @param scalar The scalar to divide this vector by.
             * @return The scalar quotient of the given scalar and this vector.
             */
            const Vector operator/ ( const float &scalar ) const;

            /**
             * @brief Calculates the cross product of this
             * vector with the specified vector.
             * 
             * @param vector The vector to calculate the cross product with.
             * @return The cross product of this vector with the specified vector.
             */
            const Vector CrossProduct ( const Vector &vector ) const;

            /**
             * @brief Calculates the dot product of this
             * vector with the specified vector.
             * 
             * @param vector The vector to calculate the dot product with.
             * @return The dot product of this vector with the specified vector.
             */
            const float DotProduct ( const Vector &vector ) const;

            /**
             * @brief Calculates the length of the vector.
             * 
             * @return The length of the vector.
             */
            const float Length () const;

            /**
             * @brief Calculates the vector's unit vector.
             * 
             * @return The vector's unit vector.
             */
            const Vector UnitVector () const;

            /**
             * @brief Normalizes the vector.
             */
            void Normalize ();

            /**
             * @brief Calculates the angle between this vector
             * and another vector (i.e. a normal vector).
             * 
             * @param normal The vector to calculate the angle to.
             * @returns The angle between this vector and the given vector.
             */
            inline const float Angle ( const Vector &normal ) const;

            /**
             * @brief Calculates the reflection of this vector
             * through another vector (i.e. a normal vector).
             * 
             * @param normal The vector to reflect through.
             * @returns The reflection of this vector through the given vector.
             */
            inline const Vector Reflection ( const Vector &normal ) const;

            //********************* Mathematical Operators *********************//

        protected:
            
            /** @brief Holds the x coordinate. */
            float x;

            /** @brief Holds the y coordinate. */
            float y;

            /** @brief Holds the z coordinate. */
            float z;
    };

}

#endif
