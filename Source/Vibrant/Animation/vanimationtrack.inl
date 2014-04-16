/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationtrack.inl
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

#include "vanimationdata.h"
#include "vanimationmodes.h"

namespace Vibrant
{
    
    inline AnimationTrack::AnimationTrack ( AnimationData* animationData, float duration )
    {
        this->animationData = animationData;
        this->duration = duration;
        
        // Set default values.
        this->accumulative = false;
        this->additive = false;
        this->beginOffset = 0.0f;
        this->blendWeight = 1.0f;
        this->fillMode = REMOVE;
        this->repeatCount = 1.0f;
        this->repeatDuration = ANIMATION_NONE;
        this->speed = 1.0f;
        this->speedEffect = 1.0f;
    }
    
    inline AnimationTrack::~AnimationTrack ()
    {
        this->animationData = null;
    }
    
    inline void AnimationTrack::AccumulateValue ()
    {
        if ( this->animationData != null && this->animationData->GetAnimationSession () != null && this->animationData->GetTarget ()
            != null )
        {
            int targetAttributeSize = this->animationData->GetTargetAttributeSize ();
            Animatable* target = this->animationData->GetTarget ();
            AnimationSession* session = this->animationData->GetAnimationSession ();
            
            // Accumulate the values according the target attribute type.
            if ( session->resetValue != null )
            {
                // In order to calculate the accumulated value, we just evaluate the animation data
                // at full blend weight in additive mode at the very end of the local duration. This way
                // we can encapsulate the code that deals with interpolation of different target attribute
                // types within the AnimationData classes.
                // 
                // (Note: this also actually applies the accumulation to the target right away
                // which we don't want to do until the next iteration through, so we store the
                // previous animated values and then reset them after calculating the accumulated values).

                // Store the actual current values so that we can reset them after evaluating the accumulated values.
                float* currentValue = new float[ targetAttributeSize ];
                target->GetTargetAttributeValue ( this->animationData->GetTargetAttribute (), currentValue, targetAttributeSize );
                
                // Calculate the accumulated value and store it in the animation session's reset value.
                this->animationData->ResetAnimatedValue ();
                this->animationData->Update ( 1.0f, 1.0f, true );
                target->GetTargetAttributeValue ( this->animationData->GetTargetAttribute (), session->resetValue, session->valueSize );
                
                // Reset the actual current values.
                this->animationData->GetTarget ()->ApplyAnimatedValue ( currentValue, targetAttributeSize,
                    this->animationData->GetTargetAttribute () );
                delete[] currentValue;
                currentValue = null;
            }
        }
    }
    
    inline void AnimationTrack::ClearAccumulatedValue ()
    {
        // Reset the animation session's reset values to the original values.
        if ( this->animationData != null && this->animationData->GetAnimationSession () != null )
        {
            AnimationSession* session = this->animationData->GetAnimationSession ();
            int targetAttributeSize = this->animationData->GetTargetAttributeSize ();
            
#ifdef _MSC_VER
            memcpy_s ( session->resetValue, targetAttributeSize * sizeof ( float ), session->originalValue, targetAttributeSize * sizeof ( float ) );
#else
            memcpy ( session->resetValue, session->originalValue, targetAttributeSize * sizeof(float) );
#endif
        }
    }
    
    inline AnimationData* AnimationTrack::GetAnimationData ()
    {
        return this->animationData;
    }
    
    inline float AnimationTrack::GetBeginOffset ()
    {
        return this->beginOffset;
    }
    
    inline float AnimationTrack::GetBlendWeight ()
    {
        return this->blendWeight;
    }
    
    inline float AnimationTrack::GetDuration ()
    {
        return this->duration;
    }
    
    inline FillMode AnimationTrack::GetFillMode ()
    {
        return this->fillMode;
    }
    
    inline float AnimationTrack::GetRepeatCount ()
    {
        return this->repeatCount;
    }
    
    inline float AnimationTrack::GetRepeatDuration ()
    {
        return this->repeatDuration;
    }
    
    inline float AnimationTrack::GetSpeed ()
    {
        return this->speed;
    }
    
    inline float AnimationTrack::GetSpeedEffect ()
    {
        return this->speedEffect;
    }
    
    inline bool AnimationTrack::IsAccumulative ()
    {
        return this->accumulative;
    }
    
    inline bool AnimationTrack::IsAdditive ()
    {
        return this->additive;
    }
    
    inline void AnimationTrack::SetAnimationData ( AnimationData* animationData )
    {
        this->animationData = animationData;
    }
    
    inline void AnimationTrack::SetBeginOffset ( float beginOffset )
    {
        this->beginOffset = beginOffset;
    }
    
    inline void AnimationTrack::SetBlendWeight ( float blendWeight )
    {
        if ( blendWeight < 0.0f )
        {
            throw IllegalArgumentException ( "AnimationTrack::SetBlendWeight - Blend weight must be >= 0." );
        }
        
        this->blendWeight = blendWeight;
    }
    
    inline void AnimationTrack::SetDuration ( float duration )
    {
        if ( duration < 0.0f )
        {
            throw IllegalArgumentException ( "AnimationTrack::SetDuration - Duration must be >= 0." );
        }
        
        this->duration = duration;
    }
    
    inline void AnimationTrack::SetFillMode ( FillMode fillMode )
    {
        this->fillMode = fillMode;
    }
    
    inline void AnimationTrack::SetRepeatCount ( float repeatCount )
    {
        if ( repeatCount < 0.0f && repeatCount != ANIMATION_INDEFINITE )
        {
            throw IllegalArgumentException ( "AnimationTrack::SetRepeatCount - Repeat count must be >= 0 or ANIMATION_INDEFINITE." );
        }
        
        this->repeatCount = repeatCount;
    }
    
    inline void AnimationTrack::SetRepeatDuration ( float repeatDuration )
    {
        if ( repeatDuration < 0.0f && repeatDuration != ANIMATION_NONE )
        {
            throw IllegalArgumentException ( "AnimationTrack::SetRepeatDuration - Repeat duration must be >= 0 or ANIMATION_NONE." );
        }
        
        this->repeatDuration = repeatDuration;
    }
    
    inline void AnimationTrack::SetSpeed ( float speed )
    {
        if ( speed < 0.0f )
        {
            throw IllegalArgumentException ( "AnimationTrack::SetSpeed - Speed must be >= 0." );
        }

        this->speed = speed;
        this->speedEffect = ( this->speed == 0.0f ) ? 0.0f : 1.0f / this->speed;
    }
    
    inline void AnimationTrack::SetAccumulative ( bool accumulative )
    {
        this->accumulative = accumulative;
    }
    
    inline void AnimationTrack::SetAdditive ( bool additive )
    {
        this->additive = additive;
    }
    
    inline void AnimationTrack::Update ( float percent )
    {
        this->animationData->Update ( percent, this->blendWeight, this->additive );
    }

}
