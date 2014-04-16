/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationmodes.h
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

#ifndef VIBRANT_ANIMATIONMODES_H
#define VIBRANT_ANIMATIONMODES_H

namespace Vibrant
{
    
    /**
     * @brief Represents the different behaviors an animation
     * can have when it ends (known as the animation's 'fill').
     */
    enum FillMode
    {
        FREEZE = 0,
        REMOVE = 1
    };
    
    /**
     * @brief Represents the different interpolation modes.
     */
    enum InterpolationMode
    {
        LINEAR = 0,
        DISCRETE = 1,
        PACED = 2,
        SPLINE = 3
    };
    
    /**
     * @brief Represents the different types of target attributes.
     */
    enum AnimatableAttributeType
    {
        SCALAR = 0,
        MATRIX = 1,
        QUATERNION = 2
    };
    
    /** @brief Represents an indefinite value. */
    const float ANIMATION_INDEFINITE = -1.0f;
    
    /** @brief Represents an 'none' (or 'undefined') animation value. */
    const float ANIMATION_NONE = -2.0f;

}

#endif
