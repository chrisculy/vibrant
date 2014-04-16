/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtransform.h
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

#ifndef VIBRANT_TRANSFORM_H
#define VIBRANT_TRANSFORM_H

#include "vmatrix.h"
#include "vquaternion.h"
#include "vvector.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates 3D transforms.
     * 
     * @author Chris Culy
     */
    class VAPI Transform
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            Transform ();

            /**
             * @brief Constructor.
             * 
             * @param scale The scale component of the transformation.
             * @param rotation The rotation component of the transformation.
             * @param translation The translation component of the transformation.
             */
            Transform ( const Vector& scale, const Quaternion& rotation, const Vector& translation );

            /**
             * @brief Destructor.
             */
            ~Transform ();

            /**
             * @brief Retrieves the transform's underlying matrix.
             * 
             * @return The transform's matrix.
             */
            const Matrix& GetMatrix () const;

            /**
             * @brief Retrieves the transformation's scale.
             * 
             * @return The transformation's scale.
             */
            const Vector& GetScale () const;

            /**
             * @brief Retrieves the transformation's scale along the X axis.
             * 
             * @return The scale along the X axis.
             */
            float GetScaleX () const;

            /**
             * @brief Retrieves the transformation's scale along the Y axis.
             * 
             * @return The scale along the Y axis.
             */
            float GetScaleY () const;

            /**
             * @brief Retrieves the transformation's scale along the Z axis.
             * 
             * @return The scale along the Z axis.
             */
            float GetScaleZ () const;

            /**
             * @brief Retrieves the transformation's rotation.
             * 
             * @return The transformation's rotation.
             */
            const Quaternion& GetRotation () const;

            /**
             * @brief Retrieves the x component of the transform's rotation quaternion.
             * 
             * @return The x component of the transform's rotation quaternion.
             */
            float GetRotationX () const;

            /**
             * @brief Retrieves the y component of the transform's rotation quaternion.
             * 
             * @return The y component of the transform's rotation quaternion.
             */
            float GetRotationY () const;

            /**
             * @brief Retrieves the z component of the transform's rotation quaternion.
             * 
             * @return The z component of the transform's rotation quaternion.
             */
            float GetRotationZ () const;

            /**
             * @brief Retrieves the w component of the transform's rotation quaternion.
             * 
             * @return The w component of the transform's rotation quaternion.
             */
            float GetRotationW () const;

            /**
             * @brief Retrieves the transformation's translation.
             * 
             * @return The transformation's translation.
             */
            const Vector& GetTranslation () const;

            /**
             * @brief Retrieves the transformation's translation along the X axis.
             * 
             * @return The translation along the X axis.
             */
            float GetTranslationX () const;

            /**
             * @brief Retrieves the transformation's translation along the Y axis.
             * 
             * @return The translation along the Y axis.
             */
            float GetTranslationY () const;

            /**
             * @brief Retrieves the transformation's translation along the Z axis.
             * 
             * @return The translation along the Z axis.
             */
            float GetTranslationZ () const;

            /**
             * @brief Sets the transform's underlying matrix.
             * 
             * <b>Note:</b> This overrides the transform's separate scale, rotation,
             * and translation components until one of these are set (at which point
             * this matrix that was just set is ignored).
             * 
             * @param matrix The transform's matrix.
             */
            void SetMatrix ( Matrix& matrix );

            /**
             * @brief Sets the scale for the transform.
             * 
             * @param scale The scale as a vector.
             */
            void SetScale ( Vector& scale );

            /**
             * @brief Sets the scale for the transform.
             * 
             * @param sx The amount to scale in the x direction.
             * @param sy The amount to scale in the y direction.
             * @param sz The amount to scale in the z direction.
             */
            void SetScale ( float sx, float sy, float sz );

            /**
             * @brief Sets the rotation quaternion for the transform.
             * 
             * @param rotation The rotation quaternion.
             */
            void SetRotation ( Quaternion& rotation );

            /**
             * @brief Sets the rotation quaternion for the transform.
             * 
             * @param x The x component of the rotation quaternion.
             * @param y The y component of the rotation quaternion.
             * @param z The z component of the rotation quaternion.
             * @param w The w component of the rotation quaternion.
             */
            void SetRotation ( float x, float y, float z, float w );

            /**
             * @brief Sets the translation for the transform.
             * 
             * @param translation The translation as a vector.
             */
            void SetTranslation ( Vector& translation );

            /**
             * @brief Sets the translation for the transform.
             * 
             * @param tx The amount to translate in the x direction.
             * @param ty The amount to translate in the y direction.
             * @param tz The amount to translate in the z direction.
             */
            void SetTranslation ( float tx, float ty, float tz );

            /**
             * @brief Scales the current tranformation.
             * 
             * @param scale The amount to scale by.
             */
            void Scale ( Vector& scale );

            /**
             * @brief Scales the current transformation along the X axis.
             * 
             * @param sx The amount to scale along the X axis by.
             */
            void ScaleX ( float sx );

            /**
             * @brief Scales the current transformation along the Y axis.
             * 
             * @param sy The amount to scale along the Y axis by.
             */
            void ScaleY ( float sy );

            /**
             * @brief Scales the current transformation along the Z axis.
             * 
             * @param sz The amount to scale along the Z axis by.
             */
            void ScaleZ ( float sz );

            /**
             * @brief Rotates the current transformation.
             * 
             * @param rotate The amount to rotate by.
             */
            void Rotate ( Quaternion& rotate );

            /**
             * @brief Translates the current transformation.
             * 
             * @param translate The amount to translate by.
             */
            void Translate ( Vector& translate );

            /**
             * @brief Translates the current transformation along the X axis.
             * 
             * @param tx The amount to translate along the X axis by.
             */
            void TranslateX ( float tx );

            /**
             * @brief Translates the current transformation along the Y axis.
             * 
             * @param ty The amount to translate along the Y axis by.
             */
            void TranslateY ( float ty );

            /**
             * @brief Translates the current transformation along the Z axis.
             * 
             * @param tz The amount to translate along the Z axis by.
             */
            void TranslateZ ( float tz );

            /**
             * @brief Multiplies this transform by the given transform.
             * 
             * @param transform The transform to multiply with this transform.
             * @return The product of this transform and the specified transform as a matrix.
             */
            Matrix operator* ( const Transform& transform );

            /**
             * @brief Assignment operator.
             * 
             * @param transform The transform to assign to this transform.
             * @return The end result of the assignment (this transform after the assignment).
             */
            Transform& operator= ( const Transform& transform );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds whether the transform's matrix is dirty. */
            mutable bool matrixIsCurrent;

            /** @brief Holds the scale vector for the transform. */
            Vector* scale;

            /** @brief Holds the translation vector for the transform. */
            Vector* translation;

            /** @brief Holds the quaternion that represents the rotation of the transform. */
            Quaternion* rotation;

            /** @brief Holds the matrix that represents the transform. */
            Matrix* matrix;
    };

}

#endif
