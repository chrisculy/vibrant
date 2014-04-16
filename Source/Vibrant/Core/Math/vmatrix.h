/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmatrix.h
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

#ifndef VIBRANT_MATRIX_H
#define VIBRANT_MATRIX_H

#include "varray.h"
#include "vlog.h"
#include "vreader.h"
#include "vserializable.h"
#include "vwriter.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the functionality of a 4x4 matrix.
     * 
     * The matrix is stored in a flat columnwise floating point array (below is shown
     * the how the matrix elements are stored in the array and then the array indices
     * for the matrix elements):
     * 
     * <pre>
     * [ m00 m10 m20 m30 m01 m11 m21 m31 m02 m12 m22 m32 m03 m13 m23 m33 ]
     * 
     * [ 0  4   8  12 ]
     * [ 1  5   9  13 ]
     * [ 2  6  10  14 ]
     * [ 3  7  11  15 ]
     * </pre>
     * 
     * <p>
     * Provides all basic matrix operations.
     * <b>Note that not all matrix operations have been coded yet.
     * (inversion, inner and dot products, etc)</b>
     * </p>
     *
     * @author Chris Culy
     */
    class VAPI Matrix : public Serializable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Matrix ();

            /**
             * @brief Constructor.
             * 
             * <b>Note:</b> This is an unsafe constructor-it is assumed that the given array
             * has a size of 16 (and is non-null), so use with caution.
             * 
             * @param val The 4x4 matrix stored in a flat floating point array in column major order.
             */
            Matrix ( float* val );

            /**
             * @brief Constructor.
             * 
             * @param val The 4x4 matrix stored in a flat floating point array. 
             * @throws IllegalArgumentException if val is not an array of 16 elements.
             */
            Matrix ( Array< float >& val );

            /**
             * @see Matrix#Matrix(Array<float>&)
             */
            Matrix ( Array< float >* val );

            /**
             * @brief Destructor.
             */
            virtual ~Matrix ();

            /**
             * @brief Returns the 4x4 identity matrix.
             * 
             * @return The 4x4 identity matrix.
             */
            static Matrix GetIdentityMatrix ();

            /**
             * @brief Copies the matrix's values into the given array.
             * 
             * Note: Behavior is undefined if the given array has a size less than 16.
             * 
             * @param values A floating-point array of size 16 to store the matrix values in.
             */
            void CopyValues ( float* values ) const;

            /**
             * @brief Retrieves the rotation about the X axis.
             * 
             * @return The rotation about the X axis.
             */
            float GetRotationX ();

            /**
             * @brief Retrieves the rotation about the Y axis.
             * 
             * @return The rotation about the Y axis.
             */
            float GetRotationY ();

            /**
             * @brief Retrieves the rotation about the Z axis.
             * 
             * @return The rotation about the Z axis.
             */
            float GetRotationZ ();

            /**
             * @brief Retrieves the transpose of the matrix.
             * 
             * @return The transpose of the matrix.
             */
            Matrix GetTranspose ();

            /**
             * @brief Retrieves the specified element in the matrix.
             * 
             * @param row The row of the element; must be from 0-3.
             * @param col The col of the element; must be from 0-3.
             * @throws IndexOutOfBoundsException If row or col
             *      are outside the valid range of 0-3.
             */
            float GetValue ( int row, int col ) const;

            /**
             * @brief Retrieves the matrix's value array.
             * 
             * @return The matrix's value array.
             */
            const float* GetValues () const;

            /**
             * @brief Sets the specified element in the matrix.
             * 
             * @param row The row of the element to be set;
             *      must be from 0-3.
             * @param col The col of the element to be set;
             *      must be from 0-3.
             * @param value The value to set the element to.
             * @throws IndexOutOfBoundsException If row or col
             *      are outside the valid range of 0-3.
             */
            void SetValue ( int row, int col, float value );

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
            

            //******************* Matrix - Scalar Operations ******************//

            /**
             * @brief Assigns the matrix to another matrix.
             * 
             * @param x The matrix to assign to (copy into) this one.
             */
            const Matrix& operator= ( Matrix x );

            /**
             * @brief Multiplies the matrix by a scalar.
             * 
             * @param x The scalar value to multiply the matrix by.
             * @return The result of multiplying the matrix and the scalar.
             */
            Matrix operator* ( float x );

            /**
             * @brief Divides the matrix by a scalar.
             * 
             * @param x The scalar value to divide the matrix by.
             * @returns The result of dividing the matrix by the scalar.
             */
            Matrix operator/ ( float x );

            /**
             * @brief Multiplies the matrix by a scalar and assigns
             * the result to the matrix.
             * 
             * @param x The scalar to multiply by.
             */
            void operator*= ( float x );

            /**
             * @brief Divides the matrix by a scalar and assigns
             * the result to the matrix.
             * 
             * @param x The scalar to divide by.
             */
            void operator/= ( float x );

            /**
             * @brief Negates the matrix (multiplies by -1).
             */
            void operator- ();

            //******************* Matrix - Scalar Operations ******************//
            

            //************************ Matrix Operations ***********************//

            /**
             * @brief Performs matrix multiplication.
             * 
             * @param x The matrix to multiply by.
             * @return The result of multiplying the two matrices.
             */
            Matrix operator* ( const Matrix x ) const;

            /**
             * @brief Performs matrix addition.
             * 
             * @param x The matrix to add.
             * @return The result of adding the two matrices.
             */
            Matrix operator+ ( const Matrix x ) const;

            /**
             * @brief Performs matrix subtraction.
             * 
             * @param x The matrix to subtract.
             * @return The result of subtracting the provided matrix from the first matrix.
             */
            Matrix operator- ( const Matrix x ) const;

            /**
             * @brief Performs matrix multiplication and assigns the result to the matrix.
             * 
             * @param x The matrix to multiply by.
             */
            void operator*= ( const Matrix x );

            /**
             * @brief Performs matrix addition and assigns the result to the matrix.
             * 
             * @param x The matrix to add.
             */
            void operator+= ( const Matrix x );

            /**
             * @brief Performs matrix subtraction and assigns the result to the matrix.
             * 
             * @param x The matrix to subtract.
             */
            void operator-= ( const Matrix x );

            //************************ Matrix Operations ***********************//

        private:
            
            /** @brief The 4x4 matrix stored in a flat float precision floating point array. */
            float values[ 16 ];
    };

    /**
     * @brief Writes a matrix to the log file.
     * 
     * @param log The log to write the matrix to.
     * @param val The matrix to write to the log file.
     * @return A reference to the logger.
     */
    Log& operator<< ( Log& log, const Matrix val );

}

#endif
