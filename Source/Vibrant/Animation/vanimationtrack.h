/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationtrack.h
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

#ifndef VIBRANT_ANIMATIONTRACK_H
#define VIBRANT_ANIMATIONTRACK_H

#include "vanimationdata.h"
#include "vanimationmodes.h"

namespace Vibrant
{
    
    /**
     * @brief Represents the changing of a single value over time.
     * 
     * @author Chris Culy
     */
    class VAPI AnimationTrack
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param animationData The animation data for the track.
             * @param duration The duration for the track.
             */
            AnimationTrack ( AnimationData* animationData = null, float duration = 0.0f );

            /**
             * @brief Destructor.
             */
            ~AnimationTrack ();

            /**
             * @brief Performs the accumulation of values for the animation track.
             */
            void AccumulateValue ();

            /**
             * @brief Clears the accumulated value.
             */
            void ClearAccumulatedValue ();

            /**
             * @brief Retrieves the animation data for the track.
             * 
             * @return The animation data.
             */
            AnimationData* GetAnimationData ();

            /**
             * @brief Retrieves the time offset until the track begins.
             * 
             * @return The begin offset.
             */
            float GetBeginOffset ();

            /**
             * @brief Retrieves the track's blending weight (for how much it affects its target).
             * 
             * @return The blending weight.
             */
            float GetBlendWeight ();

            /**
             * @brief Retrieves the track's duration (not counting repeats).
             * 
             * @return The duration.
             */
            float GetDuration ();

            /**
             * @brief Retrieves the track's fill mode (the effect when the track ends).
             * 
             * @return The fill mode.
             * @see FillMode
             */
            FillMode GetFillMode ();

            /**
             * @brief Retrieves the track's repeat count.
             * 
             * @return The repeat count.
             */
            float GetRepeatCount ();

            /**
             * @brief Retrieves the track's repeat duration.
             * 
             * @return The repeat duration.
             */
            float GetRepeatDuration ();

            /**
             * @brief Retrieves the track's speed (or speed factor).
             * 
             * @return The speed.
             */
            float GetSpeed ();

            /**
             * @brief Retrieves the track's speed effect on the track's duration
             * (i.e. If the speed is 2.0, then the effect on the duration is 0.5).
             * 
             * @return The speed effect.
             */
            float GetSpeedEffect ();

            /**
             * @brief Retrieves whether the track is accumulative on its target attribute or not.
             * 
             * @return <code>true</code> if the track is accumulative;
             *        <code>false</code> otherwise.
             */
            bool IsAccumulative ();

            /**
             * @brief Retrieves whether the track is additive on its target attribute or not.
             * 
             * @return <code>true</code> if the track is additive;
             *        <code>false</code> otherwise.
             */
            bool IsAdditive ();

            /**
             * @brief Sets the track's animation data.
             * 
             * @param animationData The animation data.
             */
            void SetAnimationData ( AnimationData* animationData );

            /**
             * @brief Sets the track's time offset before it begins.
             * 
             * TODO: We need to call back on the Animations that hold this AnimationTrack
             * so that they can recalculate the active duration and their duration.
             *
             * @param beginOffset The begin offset.
             */
            void SetBeginOffset ( float beginOffset );

            /**
             * @brief Sets the track's blend weight.
             * 
             * @param blendWeight The blend weight.
             * @throw IllegalArgumentException If <code>blendWeight &lt; 0</code>.
             */
            void SetBlendWeight ( float blendWeight );

            /**
             * @brief Sets the track's duration.
             * 
             * TODO: We need to call back on the Animations that hold this AnimationTrack
             * so that they can recalculate the active duration and their duration.
             * 
             * @param duration The duration.
             * @throw IllegalArgumentException If <code>duration &lt; 0</code>.
             */
            void SetDuration ( float duration );

            /**
             * @brief Sets the track's fill mode.
             * 
             * @param fillMode The fill mode.
             * @see FillMode
             */
            void SetFillMode ( FillMode fillMode );

            /**
             * @brief Sets the track's repeat count.
             * 
             * TODO: We need to call back on the Animations that hold this AnimationTrack
             * so that they can recalculate the active duration and their duration.
             * 
             * @param repeatCount The repeat count; must be greater than or equal to zero
             *      or {@link Vibrant#ANIMATION_INDEFINITE}.
             * @throw IllegalArgumentException If <code>repeatCount</code> is invalid.
             */
            void SetRepeatCount ( float repeatCount );

            /**
             * @brief Sets the track's repeat duration.
             * 
             * TODO: We need to call back on the Animations that hold this AnimationTrack
             * so that they can recalculate the active duration and their duration.
             * 
             * @param repeatDuration The repeat duration; must be greater than or equal
             *      to zero or {@link Vibrant#ANIMATION_NONE}.
             * @throw IllegalArgumentException If <code>repeatDuration</code> is invalid.
             */
            void SetRepeatDuration ( float repeatDuration );

            /**
             * @brief Sets the track's speed (or speed factor).
             * 
             * TODO: We need to call back on the Animations that hold this AnimationTrack
             * so that they can recalculate the active duration and their duration.
             * 
             * @param speed The speed.
             * @throw IllegalArgumentException If <code>speed &lt; 0</code>.
             */
            void SetSpeed ( float speed );

            /**
             * @brief Sets whether the track is accumulative on its target attribute or not.
             * 
             * @param accumulative Whether the track is accumulative or not.
             */
            void SetAccumulative ( bool accumulative );

            /**
             * @brief Sets whether the track is additive on its target attribute or not.
             * 
             * @param additive Whether the track is additive or not.
             */
            void SetAdditive ( bool additive );

            /**
             * @brief Updates the animation track for the given percentage through the track's duration.
             * 
             * @param percent The percentage through the animation track's duration.
             */
            void Update ( float percent );

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the data that is used to animate (from, to, and in between). */
            AnimationData* animationData;

            /** @brief Holds the time offset before the beginning occurs. */
            float beginOffset;

            /** @brief Holds the animation track's blend weight. */
            float blendWeight;

            /** @brief Holds the duration. */
            float duration;

            /** @brief Holds the animation track's fill mode. */
            FillMode fillMode;

            /** @brief Holds the number of times to repeat. */
            float repeatCount;

            /** @brief Holds the duration to repeat for (constrains the repeat count). */
            float repeatDuration;

            /** @brief Holds the speed or speed factor (defaults to 1.0).
             * <b>Note:</b> The speed factor is applied to all timing characteristics except the begin offset. */
            float speed;

            /** @brief Holds the speed effect (on the track's duration). */
            float speedEffect;

            /** @brief Holds whether the animation track is accumulative or not. */
            bool accumulative;

            /** @brief Holds whether the animation track is additive or not. */
            bool additive;
    };

}

// Include inline definitions.
#include "vanimationtrack.inl"

#endif
