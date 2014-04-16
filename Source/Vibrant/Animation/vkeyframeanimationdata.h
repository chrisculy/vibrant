/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vkeyframeanimationdata.h
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

#ifndef VIBRANT_KEYFRAMEANIMATIONDATA_H
#define VIBRANT_KEYFRAMEANIMATIONDATA_H

#include "vanimationdata.h"
#include "varray.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Represents the data for an animation
     * that uses key values and key times.
     * 
     * @author Chris Culy
     */
    class VAPI KeyframeAnimationData : public AnimationData
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param target The target for the animation data.
             * @param targetAttribute The target attribute's name.
             * @param keyValues The key values for the animation data.
             * @param keyTimes The key times for the animation data.
             * @param keyCount The number of keys (key values and times).
             */
            KeyframeAnimationData ( Animatable* target, String targetAttribute, Array< float* >* keyValues = null,
                Array< float >* keyTimes = null, int keyCount = 0 );

            /**
             * @brief Destructor.
             */
            ~KeyframeAnimationData ();

            /**
             * @brief Adds a keyframe with the given value and time at the given index.
             * 
             * @param keyValue The key frame's key value.
             * @param keyTime The key frame's key time.
             * @param keyIndex The index to add the key at.
             * @throw NullPointerException If <code>keyValue</code> is <code>null</code>.
             * @throw IndexOutOfBoundsException If <code>keyIndex</code> &lt; 0 or
             *      <code>index</code> &gt; GetKeyCount ().
             */
            void AddKey ( float* keyValue, float keyTime, int keyIndex );

            /**
             * @brief Retrieves the number of key frames.
             * 
             * @return The number of key frames.
             */
            const int GetKeyCount ();

            /**
             * @brief Retrieves the animation data's key values.
             * 
             * @return The key values.
             */
            Array< float* >* GetKeyValues ();

            /**
             * @brief Retrieves the animation data's key times.
             * 
             * @return The key times.
             */
            Array< float >* GetKeyTimes ();

            /**
             * @brief Sets the animation data's key values.
             * 
             * @param keyValues The key values.
             */
            void SetKeyValues ( Array< float* >* keyValues );

            /**
             * @brief Sets the animation data's key times.
             * 
             * @param keyTimes The key times.
             */
            void SetKeyTimes ( Array< float >* keyTimes );

            /**
             * @brief Updates the animation data for the given percentage through the animation.
             * 
             * @param percent The percentage through the animation.
             * @param blendWeight How much the animated value should be applied (this value is clamped to[0.0-1.0]).
             * @param additive Whether the animation is additive or not.
             */
            void Update ( float percent, float blendWeight = 1.0f, bool additive = false );

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Updates the current keyframe given the percentage through the animation.
             * 
             * @param percent The percentage through the animation.
             */
            void UpdateCurrentKeyframe ( float percent );

            /**
             * @brief Updates the current keyframe given the percentage through the animation (for paced animations).
             * 
             * @param percent The percentage through the animation.
             */
            void UpdateCurrentKeyframePaced ( float percent );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the key values. */
            Array< float* >* keyValues;

            /** @brief Holds the key times. */
            Array< float >* keyTimes;

            /** @brief Holds the current key frame (ranges from 0 to the number of keys minus 2). */
            int currentKeyframe;

            /** @brief Holds whether the animation data object owns the key values. */
            bool ownsKeyValues;

            /** @brief Holds whether the animation data object owns the key times. */
            bool ownsKeyTimes;
    };

}

#endif
