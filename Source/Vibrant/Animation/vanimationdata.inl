/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationdata.inl
 * 
 * 
 * --  Copyright (c) 2007-2009 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision$
 * $Author$
 * $Date$
 */

#include "vanimatable.h"
#include "vanimationmodes.h"
#include "vanimationsession.h"

namespace Vibrant
{
    
    inline AnimationData::AnimationData ( Animatable* target, String attributeName )
    {
        // Initialize to default values.
        this->mode = LINEAR;
        this->animatedValue = null;
        
        this->keyPoints = new float[ 4 ];
        this->keyPoints[ 0 ] = 0.0f;
        this->keyPoints[ 1 ] = 1.0f;
        this->keyPoints[ 2 ] = 1.0f;
        this->keyPoints[ 3 ] = 1.0f;
        
        // Set the target and initialize all related values.
        this->SetTarget ( target, attributeName );
    }
    
    inline AnimationData::~AnimationData ()
    {
        this->target = null;
        this->session = null;
        if ( this->animatedValue != null )
        {
            delete[] this->animatedValue;
            this->animatedValue = null;
        }
        if ( this->keyPoints != null )
        {
            delete[] this->keyPoints;
            this->keyPoints = null;
        }
    }
    
    inline AnimationSession* AnimationData::GetAnimationSession () const
    {
        return this->session;
    }
    
    inline InterpolationMode AnimationData::GetInterpolationMode () const
    {
        return this->mode;
    }
    
    inline float* AnimationData::GetKeyPoints () const
    {
        return &( this->keyPoints[ 1 ] );
    }
    
    inline Animatable* AnimationData::GetTarget () const
    {
        return this->target;
    }
    
    inline int AnimationData::GetTargetAttribute () const
    {
        return this->targetAttribute;
    }
    
    inline short AnimationData::GetTargetAttributeSize () const
    {
        return this->targetAttributeSize;
    }
    
    inline void AnimationData::ResetAnimatedValue ()
    {
        if ( this->targetAttribute != -1 && this->session != null && this->session->resetValue != null )
        {
            this->target->ApplyAnimatedValue ( this->session->resetValue, this->session->valueSize, this->targetAttribute );
        }
    }
    
    inline void AnimationData::ResetAnimationSession ()
    {
        if ( this->target != null && this->targetAttribute != -1 )
        {
            if ( this->session != null && this->session->originalValue != null && this->session->resetValue != null )
            {
                // Set the animation session's values.
                this->target->GetTargetAttributeValue ( this->targetAttribute, this->session->originalValue, this->session->valueSize );
                this->target->GetTargetAttributeValue ( this->targetAttribute, this->session->resetValue, this->session->valueSize );
            }
        }
    }
    
    inline void AnimationData::ResetTargetValue ()
    {
        if ( this->targetAttribute != -1 && this->session != null && this->session->originalValue != null )
        {
            this->target->ApplyAnimatedValue ( this->session->originalValue, this->session->valueSize, this->targetAttribute );
        }
    }
    
    inline void AnimationData::SetInterpolationMode ( InterpolationMode mode )
    {
        this->mode = mode;
    }
    
    inline void AnimationData::SetKeyPoints ( float firstControlTangent, float secondControlTangent )
    {
        this->keyPoints[ 1 ] = firstControlTangent;
        this->keyPoints[ 2 ] = secondControlTangent;
    }

}
