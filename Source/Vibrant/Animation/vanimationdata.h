/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationdata.h
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

#ifndef VIBRANT_ANIMATIONDATA_H
#define VIBRANT_ANIMATIONDATA_H

#include "vanimatable.h"
#include "vanimationmodes.h"
#include "varray.h"

namespace Vibrant
{
    
    /**
     * @brief Holds all information related to the actual data that
     * is used to animate the target attribute.
     * 
     * @author Chris Culy
     */
    class VAPI AnimationData
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param target The target for the animation data.
             * @param attributeName The target attribute's name.
             */
            AnimationData ( Animatable* target, String attributeName );

            /**
             * @brief Destructor.
             */
            virtual ~AnimationData ();

            /**
             * @brief Retrieves the animation data's associated animation session.
             * 
             * @return The animation session.
             */
            AnimationSession* GetAnimationSession () const;

            /**
             * @brief Retrieves the animation data's interpolation mode.
             * 
             * @return The interpolation mode.
             */
            InterpolationMode GetInterpolationMode () const;

            /**
             * @brief Retrieves the animation data's key points (the first and second
             * control points in a flat array).
             * 
             * @return The key points.
             */
            float* GetKeyPoints () const;

            /**
             * @brief Retrieves the animation data's target object.
             * 
             * @return The target object.
             */
            Animatable* GetTarget () const;

            /**
             * @brief Retrieves the target attribute.
             * 
             * @return The target attribute.
             */
            int GetTargetAttribute () const;

            /**
             * @brief Retrieves the target attribute size.
             * 
             * @return The target attribute size.
             */
            short GetTargetAttributeSize () const;

            /**
             * @brief Resets the animated value to the animation session's reset value
             * (which is usually the original or accumulated value).
             */
            void ResetAnimatedValue ();

            /**
             * @brief Resets the animation session.
             */
            void ResetAnimationSession ();

            /**
             * @brief Resets the target's value to the animation session's original value.
             */
            void ResetTargetValue ();

            /**
             * @brief Sets the animation data's target object and target attribute.
             * 
             * @param target The target object.
             * @param attributeName The target attribute's name.
             */
            void SetTarget ( Animatable* target, String attributeName );

            /**
             * @brief Sets the interpolation mode.
             * 
             * @param mode The interpolation mode.
             */
            void SetInterpolationMode ( InterpolationMode mode );

            /**
             * @brief Sets the animation data's key points which are used to modify
             * the time value for animation data using spline interpolation.
             * 
             * <b>Note:</b> This is equivalent to having four key points (the start point, the first control
             * tangent, the second control tangent, and the end point) where the start and end points
             * are defaulted to 0.0 and 1.0 respectively. This ensures the animation cannot animate to
             * before the start of the animation data or past the end of the animation data.
             * 
             * @param firstControlTangent The first control tangent.
             * @param secondControlTangent The second control tangent.
             */
            void SetKeyPoints ( float firstControlTangent, float secondControlTangent );

            /**
             * @brief Updates the animation data.
             * 
             * @param percent The percentage through the animation.
             * @param blendWeight How much the animated value should be applied (this value is clamped to[0.0-1.0]).
             * @param additive Whether the animation is additive or not.
             */
            virtual void Update ( float percent, float blendWeight = 1.0f, bool additive = false ) = 0;

            //************************ General Interface ***********************//

        protected:
            
            /** @brief Holds the target attribute (depends on the target's type). */
            int targetAttribute;

            /** @brief Holds the size (in bytes) of the animated attribute. */
            short targetAttributeSize;

            /** @brief Holds the type of the animated attribute. */
            AnimatableAttributeType targetAttributeType;

            /** @brief Holds the target object to be animated. */
            Animatable* target;

            /** @brief Holds the interpolation mode. */
            InterpolationMode mode;

            /** @brief Holds the key points used for spline interpolation. */
            float* keyPoints;

            /** @brief Holds the animation data's animation session. */
            AnimationSession* session;

            /** @brief Holds the animation data's currently calculated animated value. */
            float* animatedValue;
    };

}

// Include inline definitions.
#include "vanimationdata.inl"

#endif
