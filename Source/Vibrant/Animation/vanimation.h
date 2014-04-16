/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimation.h
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

#ifndef VIBRANT_ANIMATION_H
#define VIBRANT_ANIMATION_H

#include "vanimationtrack.h"
#include "varray.h"

namespace Vibrant
{
    
    /**
     * @brief Represents an animation with a given set of animation
     * tracks that each change a value over time.
     * 
     * @author Chris Culy
     */
    class VAPI Animation
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param animationTracks The animation tracks for this animation.
             */
            Animation ( Array< AnimationTrack* >* animationTracks = null );

            /**
             * @brief Destructor.
             */
            virtual ~Animation ();

            /**
             * @brief Adds the given track to the animation at the given position.
             * 
             * @param animationTrack The animation track to add.
             * @param trackIndex The position to add the animation track at; if equal to -1 (default),
             *        the track is added at the end of the set of tracks.
             * @throw IndexOutOfBoundsException If <code>trackIndex</code> &lt; 0 or
             *      <code>index</code> &gt; GetAnimationTracks ()->Size ().
             */
            void AddTrack ( AnimationTrack* animationTrack, int trackIndex = -1 );

            /**
             * @brief Retrieves the duration for the entire animation.
             * 
             * @return The duration.
             */
            float GetDuration ();

            /**
             * @brief Retrieves the animation track at the given position.
             * 
             * @param trackIndex The index of the desired animation track.
             */
            AnimationTrack* GetAnimationTrack ( int trackIndex );

            /**
             * @brief Retrieves the set of animation tracks.
             * 
             * @return The animation tracks.
             */
            const Array< AnimationTrack* >* GetAnimationTracks ();

            /**
             * @brief Retrieves whether the animation is active or not.
             * 
             * @return <code>true</code> if the animation is active;
             *      <code>false</code> otherwise.
             */
            bool IsActive () const;

            /**
             * @brief Removes the given animation track.
             * 
             * @param animationTrack The track to remove.
             */
            void RemoveTrack ( AnimationTrack* animationTrack );

            /**
             * @brief Removes the animation track at the given position.
             * 
             * @param trackIndex The index of the animation track to remove.
             */
            void RemoveTrack ( int trackIndex );

            /**
             * @brief Plays the animation.
             */
            virtual void Play ();

            /**
             * @brief Stops the animation (and resets it to the beginning).
             */
            virtual void Stop ();

            /**
             * @brief Pauses the animation.
             * 
             * <b>Note:</b> If this is called multiple times, it will not
             * unpause the animation (it will just ensure the animation is in
             * a paused state); call Play to unpause or play the animation.
             */
            virtual void Pause ();

            /**
             * @brief Updates the animation for the given time.
             * 
             * @param time The current system time (in milliseconds).
             */
            virtual void Update ( long time );

            //************************ General Interface ***********************//

        private:
            
            /**
             * @brief Calculates the animation's duration from its animation tracks.
             */
            void CalculateDuration ();

            /**
             * @brief Calculates the active duration for a given animation track.
             * 
             * @param track The animation track.
             * @return The active duration of the given track.
             */
            static float CalculateActiveDuration ( AnimationTrack* track );

            /** @brief Holds the animation tracks for the animation. */
            Array< AnimationTrack* >* animationTracks;

            /** @brief Holds the active duration for the animation tracks. */
            Array< float >* activeDurations;

            /** @brief Holds whether each animation track is active or not. */
            Array< bool >* activeTracks;

            /** @brief Holds the current iteration of each animation track. */
            Array< int >* trackIterations;

            /** @brief Holds the animation's total duration (determined as the maximum duration of its animation tracks). */
            float duration;

            /** @brief Holds the current local animation time. */
            float currentTime;

            /** @brief Holds the animation's start time (system time in milliseconds). */
            long startTime;

            /** @brief Holds the last time an update occurred. */
            long lastUpdateTime;

            /** @brief Holds whether the animation is currently active or not. */
            bool isActive;

            /** @brief Holds whether the animation owns the animation tracks array. */
            bool ownsAnimationTracks;
    };

}

#endif
