/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsimpleanimationdata.h
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

#ifndef VIBRANT_SIMPLEANIMATIONDATA_H
#define VIBRANT_SIMPLEANIMATIONDATA_H

#include "vanimatable.h"
#include "vanimationdata.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Represents the different types of simple animations.
     */
    enum SimpleAnimationType
    {
        FROM_TO = 0,
        FROM_BY = 1
    };
    
    /**
     * @brief Represents the animation data for a simple animation
     * that either animates in one of two ways: (1) <b>from</b> one value
     * <b>to</b> another value, or (2) <b>from</b> one value <b>by</b> another value.
     * 
     * <b>Note:</b> If all three of 'from,' 'to,' and 'by,' are specified (by using
     * SetFromValue, SetToValue, SetByValue), then the from-to animation type is used
     * and the by value is ignored.
     * 
     * @author Chris Culy
     */
    class VAPI SimpleAnimationData : public AnimationData
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param target The target for the animation data.
             * @param targetAttribute The target attribute's name.
             * @param fromValue The value to animate from.
             * @param toValue The value to animate to.
             * @param byValue The value to animate by.
             * @throw NullPointerException If <code>fromValue</code> is <code>null</code>.
             * @throw NullPointerException If both <code>toValue</code> and <code>byValue</code> are <code>null</code>.
             */
            SimpleAnimationData ( Animatable* target, String targetAttribute, float* fromValue, float* toValue, float* byValue );

            /**
             * @brief Destructor.
             */
            ~SimpleAnimationData ();

            /**
             * @brief Retrieves the simple animation type.
             * 
             * @return The animation type.
             */
            SimpleAnimationType GetAnimationType ();

            /**
             * @brief Retrieves the value to animate from.
             * 
             * @return The value to animate from.
             */
            float* GetFromValue ();

            /**
             * @brief Retrieves the value to animate to.
             * 
             * @return The value to animate to.
             */
            float* GetToValue ();

            /**
             * @brief Retrieves the value to animate by.
             * 
             * @return The value to animate by.
             */
            float* GetByValue ();

            /**
             * @brief Sets the simple animation type.
             * 
             * @param animationType The animation type.
             */
            void SetAnimationType ( SimpleAnimationType animationType );

            /**
             * @brief Sets the value to animate from.
             * 
             * @param fromValue The value to animate from.
             * @throw NullPointerException If <code>byValue</code> is <code>null</code>.
             */
            void SetFromValue ( float* fromValue );

            /**
             * @brief Sets the value to animate to.
             * 
             * @param toValue The value to animate to.
             * @throw NullPointerException If <code>byValue</code> is <code>null</code>.
             */
            void SetToValue ( float* toValue );

            /**
             * @brief Sets the value to animate by.
             * 
             * @param byValue The value to animate by.
             * @throw NullPointerException If <code>byValue</code> is <code>null</code>.
             */
            void SetByValue ( float* byValue );

            /**
             * @brief Updates the animation data for the given percentage through the animation.
             * 
             * @param percent The percentage through the animation.
             * @param blendWeight How much the animated value should be applied (this value is clamped to[0.0-1.0]).
             * @param additive Whether the animation is additive or not.
             */
            void Update ( float percent, float blendWeight = 1.0f, bool additive = false );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the from value (animating from x). */
            float* fromValue;

            /** @brief Holds the to value (animating to x). */
            float* toValue;

            /** @brief Holds the by value (animating by x). */
            float* byValue;

            /** @brief Holds the final value to animate to (used in the update function). */
            float* finalValue;

            /** @brief Holds the simple animation type. */
            SimpleAnimationType animationType;
    };

}

#endif
