/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimatable.h
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

#ifndef VIBRANT_ANIMATABLE_H
#define VIBRANT_ANIMATABLE_H

#include "vanimationmodes.h"
#include "vstring.h"

namespace Vibrant
{
    // Forward declare the AnimationSession struct to prevent include header looping.
    struct AnimationSession;
    
    /**
     * @brief Provides an interface for objects that can be animated.
     * 
     * @author Chris Culy
     */
    class Animatable
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Applies the given animated value.
             * 
             * The <code>animatedValueSize</code> parameter allows for target attributes to be animated using
             * values of different sizes (i.e. for animating the target attribute of translation (in 3D space),
             * one could apply the minimally required 3 values of translation in the X, Y, and Z directions or
             * a full 4 x 4 transformation matrix).
             * 
             * <b>Note:</b> The implementation of this must copy the values
             * from <code>animatedValue</code> and ensure that there are no
             * pointers set to <code>animatedValue</code> as this pointer is
             * not guaranteed to be valid after the function call ends.
             * 
             * @param animatedValue The animated value.
             * @param animatedValueSize The size of the animated value.
             * @param targetAttribute The target attribute to apply the value to.
             */
            virtual void ApplyAnimatedValue ( float* animatedValue, short animatedValueSize, int targetAttribute ) = 0;

            /**
             * @brief Retrieves the animation session for the given target attribute.
             * 
             * <b>Note:</b> The animation session object that is returned should
             * have its <code>valueSize</code> member variable initialized to the correct value.
             * 
             * @param targetAttribute The target attribute.
             * @return The animation session.
             */
            virtual AnimationSession* GetAnimationSession ( int targetAttribute ) = 0;

            /**
             * @brief Retrieves the integer constant representing
             * the given attribute if the attribute is supported.
             * 
             * @param attributeName The name of attribute.
             * @return The integer constant representing the attribute
             *        or -1 if the attribute is not supported.
             */
            virtual int GetTargetAttribute ( String attributeName ) = 0;

            /**
             * @brief Retrieves the size of one instance of
             * the given attribute if the attribute is supported.
             * 
             * @param targetAttribute The target attribute.
             * @return The size of one instance of the given attribute
             *      or -1 if the attribute is not supported (must be greater
             *      than zero for supported attributes or behavior is undefined).
             */
            virtual int GetTargetAttributeSize ( int targetAttribute ) = 0;

            /**
             * @brief Retrieves the type of the given animatable target attribute if the attribute is supported.
             * 
             * @param targetAttribute The target attribute.
             * @return The type of the given attribute.
             * @throws IllegalArgumentException If the given targetAttribute is not supported.
             */
            virtual AnimatableAttributeType GetTargetAttributeType ( int targetAttribute ) = 0;

            /**
             * @brief Retrieves the current value for the given target attribute.
             * 
             * @param targetAttribute The target attribute to retrieve the value of.
             * @param value The variable where the current value for the given target attribute will be stored.
             *      Note that if the target attribute is not supported, <code>value</code> is not modified.
             * @param valueSize The size of the <code>value</code> parameter (allows for support for different sizes-
             *      see {@link ApplyAnimatedValue(float*, short, int) ApplyAnimatedValue} for more information).
             */
            virtual void GetTargetAttributeValue ( int targetAttribute, float* value, short valueSize ) = 0;

            /**
             * @brief Retrieves whether the given attribute is supported.
             * 
             * @param attributeName The name of attribute.
             * @return <code>true</code> if the attribute is supported;
             *        <code>false</code> otherwise.
             */
            virtual bool IsSupported ( String attributeName )
            {
                return ( this->GetTargetAttribute ( attributeName ) != -1 );
            }
            
            //************************ General Interface ***********************//
    };

}

#endif
