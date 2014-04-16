/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationsession.h
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

#ifndef VIBRANT_ANIMATIONSESSION_H
#define VIBRANT_ANIMATIONSESSION_H

#include "vanimationdata.h"

namespace Vibrant
{
    // Forward declare the AnimationData class to prevent include header looping.
    //class AnimationData;

    /**
     * @brief Encapsulates the data needed for animating an attribute of an animatable object.
     * 
     * @see Animatable
     * @author Chris Culy
     */
    struct VAPI AnimationSession
    {
            /**
             * @brief Constructor.
             */
            AnimationSession ();

            /**
             * @brief Destructor.
             */
            ~AnimationSession ();

            /**
             * @brief Registers an AnimationData object with the animation session.
             * 
             * @param animationData The animation data object to register.
             */
            void Register ( const AnimationData* animationData );

            /** @brief Holds the session's original value. */
            float* originalValue;

            /** @brief Holds the session's reset value (the value to reset to each update). */
            float* resetValue;

            /** @brief Holds the size of the session values. */
            short valueSize;
            
    };

}

// Include the AnimationData header now (this should not cause include header looping).
//#include "vanimationdata.h"

#endif
