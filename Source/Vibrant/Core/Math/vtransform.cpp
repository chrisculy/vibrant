/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vtransform.cpp
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

#include "vmatrix.h"
#include "vquaternion.h"
#include "vtransform.h"
#include "vvector.h"

namespace Vibrant
{
    
    Transform::Transform ()
    {
        this->matrix = new Matrix ();
        *this->matrix = Matrix::GetIdentityMatrix ();
        
        this->scale = new Vector ( 1.0f, 1.0f, 1.0f );
        this->rotation = new Quaternion ();
        this->translation = new Vector ();
        
        this->matrixIsCurrent = true;
    }
    
    Transform::Transform ( const Vector& scale, const Quaternion& rotation, const Vector& translation )
    {
        this->matrix = new Matrix ();
        *this->scale = scale;
        *this->rotation = rotation;
        *this->translation = translation;
        this->matrixIsCurrent = false;
    }
    
    Transform::~Transform ()
    {
        if ( this->matrix != null )
        {
            delete this->matrix;
            this->matrix = null;
        }
        if ( this->scale != null )
        {
            delete this->scale;
            this->scale = null;
        }
        if ( this->translation != null )
        {
            delete this->translation;
            this->translation = null;
        }
        if ( this->rotation != null )
        {
            delete this->rotation;
            this->rotation = null;
        }
    }
    
    const Matrix& Transform::GetMatrix () const
    {
        // If the matrix is not current, then compose it (TRS) and update it.
        if ( !this->matrixIsCurrent )
        {
            Matrix scaleMatrix;
            scaleMatrix.SetValue ( 0, 0, this->scale->GetX () );
            scaleMatrix.SetValue ( 1, 1, this->scale->GetY () );
            scaleMatrix.SetValue ( 2, 2, this->scale->GetZ () );
            
            Matrix translationMatrix;
            translationMatrix.SetValue ( 0, 3, this->translation->GetX () );
            translationMatrix.SetValue ( 1, 3, this->translation->GetY () );
            translationMatrix.SetValue ( 2, 3, this->translation->GetZ () );
            
            *this->matrix = ( translationMatrix * this->rotation->GetMatrix () ) * scaleMatrix;
            this->matrixIsCurrent = true;
        }
        return *( this->matrix );
    }
    
    const Vector& Transform::GetScale () const
    {
        return *( this->scale );
    }
    
    float Transform::GetScaleX () const
    {
        return this->scale->GetX ();
    }
    
    float Transform::GetScaleY () const
    {
        return this->scale->GetY ();
    }
    
    float Transform::GetScaleZ () const
    {
        return this->scale->GetZ ();
    }
    
    const Quaternion& Transform::GetRotation () const
    {
        return *( this->rotation );
    }
    
    float Transform::GetRotationX () const
    {
        return this->rotation->GetX ();
    }
    
    float Transform::GetRotationY () const
    {
        return this->rotation->GetY ();
    }
    
    float Transform::GetRotationZ () const
    {
        return this->rotation->GetZ ();
    }
    
    float Transform::GetRotationW () const
    {
        return this->rotation->GetW ();
    }
    
    const Vector& Transform::GetTranslation () const
    {
        return *( this->translation );
    }
    
    float Transform::GetTranslationX () const
    {
        return this->translation->GetX ();
    }
    
    float Transform::GetTranslationY () const
    {
        return this->translation->GetY ();
    }
    
    float Transform::GetTranslationZ () const
    {
        return this->translation->GetZ ();
    }
    
    void Transform::SetMatrix ( Matrix& matrix )
    {
        *this->matrix = matrix;
        this->matrixIsCurrent = true;
    }
    
    void Transform::SetScale ( Vector& scale )
    {
        *this->scale = scale;
        this->matrixIsCurrent = false;
    }
    
    void Transform::SetScale ( float sx, float sy, float sz )
    {
        Vector scale ( sx, sy, sz );
        this->SetScale ( scale );
    }
    
    void Transform::SetRotation ( Quaternion& rotation )
    {
        *this->rotation = rotation;
        this->matrixIsCurrent = false;
    }
    
    void Transform::SetRotation ( float x, float y, float z, float w )
    {
        Quaternion rotation ( x, y, z, w );
        this->SetRotation ( rotation );
    }
    
    void Transform::SetTranslation ( Vector& translation )
    {
        *this->translation = translation;
        this->matrixIsCurrent = false;
    }
    
    void Transform::SetTranslation ( float tx, float ty, float tz )
    {
        Vector translation ( tx, ty, tz );
        this->SetTranslation ( translation );
    }
    
    void Transform::Scale ( Vector& scale )
    {
        this->scale->SetX ( this->scale->GetX () * scale.GetX () );
        this->scale->SetY ( this->scale->GetY () * scale.GetY () );
        this->scale->SetZ ( this->scale->GetZ () * scale.GetZ () );
    }
    
    void Transform::ScaleX ( float sx )
    {
        this->scale->SetX ( this->scale->GetX () * sx );
    }
    
    void Transform::ScaleY ( float sy )
    {
        this->scale->SetY ( this->scale->GetY () * sy );
    }
    
    void Transform::ScaleZ ( float sz )
    {
        this->scale->SetZ ( this->scale->GetZ () * sz );
    }
    
    void Transform::Rotate ( Quaternion& rotate )
    {
        Quaternion rotation = this->GetRotation () * rotate;
        this->SetRotation ( rotation );
    }
    
    void Transform::Translate ( Vector& translate )
    {
        this->translation->SetX ( this->translation->GetX () + translate.GetX () );
        this->translation->SetY ( this->translation->GetY () + translate.GetY () );
        this->translation->SetZ ( this->translation->GetZ () + translate.GetZ () );
    }
    
    void Transform::TranslateX ( float tx )
    {
        this->translation->SetX ( this->translation->GetX () + tx );
    }
    
    void Transform::TranslateY ( float ty )
    {
        this->translation->SetY ( this->translation->GetY () + ty );
    }
    
    void Transform::TranslateZ ( float tz )
    {
        this->translation->SetZ ( this->translation->GetZ () + tz );
    }
    
    Matrix Transform::operator* ( const Transform& transform )
    {
        return this->GetMatrix () * transform.GetMatrix ();
    }
    
    Transform& Transform::operator= ( const Transform& transform )
    {
        *this->scale = *transform.scale;
        *this->translation = *transform.translation;
        *this->rotation = *transform.rotation;
        this->matrixIsCurrent = false;
        return *this;
    }

}
