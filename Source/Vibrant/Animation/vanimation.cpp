/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimation.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "vanimation.h"
#include "vanimationtrack.h"
#include "varray.h"
#include "vmath.h"
#include "vsystemmanager.h"
#include "vtime.h"

namespace Vibrant
{
    
    Animation::Animation ( Array< AnimationTrack* >* animationTracks )
    {
        // Set the animation tracks, creating them if they are null.
        if ( animationTracks == null )
        {
            this->animationTracks = new Array< AnimationTrack* > ();
            this->activeDurations = new Array< float > ();
            this->activeTracks = new Array< bool > ();
            this->trackIterations = new Array< int > ();
            this->ownsAnimationTracks = true;
        }
        else
        {
            this->animationTracks = animationTracks;
            this->activeDurations = new Array< float > ( this->animationTracks->Size () );
            this->activeTracks = new Array< bool > ( this->animationTracks->Size () );
            this->trackIterations = new Array< int > ( this->animationTracks->Size () );
            this->ownsAnimationTracks = false;
            
            // Fill the active durations and active tracks arrays (and set the
            // current iterations for the tracks to 0).
            for ( int i = 0; i < this->animationTracks->Size (); i++ )
            {
                this->activeDurations->At ( i ) = Animation::CalculateActiveDuration ( this->animationTracks->At ( i ) );
                this->activeTracks->At ( i ) = false;
                this->trackIterations->At ( i ) = 0;
            }
        }

        this->currentTime = 0.0f;
        this->isActive = false;
        this->startTime = -1;
        this->lastUpdateTime = -1;
        
        this->CalculateDuration ();
    }
    
    Animation::~Animation ()
    {
        // Clean up the animation tracks array if the animation owns
        // the animation tracks and they still exist.
        if ( this->ownsAnimationTracks )
        {
            if ( this->animationTracks != null )
            {
                delete this->animationTracks;
                this->animationTracks = null;
            }
        }

        // Clean up the active durations and active tracks arrays.
        if ( this->activeDurations != null )
        {
            delete this->activeDurations;
            this->activeDurations = null;
        }
        if ( this->activeTracks != null )
        {
            delete this->activeTracks;
            this->activeTracks = null;
        }
    }
    
    void Animation::AddTrack ( AnimationTrack* animationTrack, int trackIndex )
    {
        // If the track index is -1, then add the given track at the end (default).
        if ( trackIndex < 0 )
        {
            this->animationTracks->Push ( animationTrack );
            this->activeDurations->Push ( Animation::CalculateActiveDuration ( animationTrack ) );
            this->activeTracks->Push ( false );
            this->trackIterations->Push ( 0 );
        }
        else
        {
            this->animationTracks->Insert ( animationTrack, trackIndex );
            this->activeDurations->Insert ( Animation::CalculateActiveDuration ( animationTrack ), trackIndex );
            this->activeTracks->Insert ( false, trackIndex );
            this->trackIterations->Insert ( 0, trackIndex );
        }
        
        // Recalculate the duration.
        this->CalculateDuration ();
    }
    
    float Animation::GetDuration ()
    {
        return this->duration;
    }
    
    AnimationTrack* Animation::GetAnimationTrack ( int trackIndex )
    {
        return this->animationTracks->At ( trackIndex );
    }
    
    const Array< AnimationTrack* >* Animation::GetAnimationTracks ()
    {
        return this->animationTracks;
    }
    
    bool Animation::IsActive () const
    {
        return this->isActive;
    }
    
    void Animation::RemoveTrack ( AnimationTrack* animationTrack )
    {
        int index = -1;
        
        // Find the animation track to be removed.
        for ( int i = 0; i < this->animationTracks->Size (); i++ )
        {
            if ( this->animationTracks->At ( i ) == animationTrack )
            {
                index = i;
                break;
            }
        }
        
        // If the animation track was found, remove it.
        if ( index >= 0 )
        {
            this->RemoveTrack ( index );
        }
    }
    
    void Animation::RemoveTrack ( int trackIndex )
    {
        this->animationTracks->Remove ( trackIndex );
        this->activeDurations->Remove ( trackIndex );
        this->activeTracks->Remove ( trackIndex );
        this->trackIterations->Remove ( trackIndex );
        
        // Recalculate the duration.
        this->CalculateDuration ();
    }
    
    void Animation::Play ()
    {
        this->isActive = true;
        
        // Update the start time based on how far through the animation we are.
        this->startTime = SystemManager::GetTimeSystem ()->GetTime () - (long) ( Math::ToMilliseconds ( this->currentTime ) );
        
        // Reset all animation sessions if we are playing from the very beginning.
        if ( this->currentTime == 0.0f )
        {
            for ( int i = 0; i < this->animationTracks->Size (); i++ )
            {
                AnimationData* animationData = this->animationTracks->At ( i )->GetAnimationData ();
                if ( animationData != null )
                {
                    animationData->ResetAnimationSession ();
                }
            }
        }
    }
    
    void Animation::Stop ()
    {
        // Set the animation back to the beginning.
        this->currentTime = 0.0f;
        for ( int i = 0; i < this->animationTracks->Size (); i++ )
        {
            AnimationData* animationData = this->animationTracks->At ( i )->GetAnimationData ();
            if ( animationData != null )
            {
                animationData->ResetTargetValue ();
            }

            // Update the track's active status.
            this->activeTracks->At ( i ) = false;
            
            // Update the track's current iteration.
            this->trackIterations->At ( i ) = 0;
        }
        
        // The animation is now inactive.
        this->isActive = false;
    }
    
    void Animation::Pause ()
    {
        this->isActive = false;
    }
    
    void Animation::Update ( long time )
    {
        if ( this->isActive )
        {
            // Go through the tracks and reset all attributes to their original values.
            AnimationData* animationData = null;
            AnimationTrack* track = null;
            for ( int i = 0; i < this->animationTracks->Size (); i++ )
            {
                track = this->animationTracks->At ( i );
                
                animationData = track->GetAnimationData ();
                
                // If the animation data exists and was active, then reset the value before it is animated below.
                if ( animationData != null && this->activeTracks->At ( i ) )
                {
                    // If the track is accumulative, we need to perform accumulation before we reset
                    // the animated value so that the animated value that we reset to is the correct accumulated value.
                    // (We only perform accumulation if the time is not outside the active duration.)
                    if ( track->IsAccumulative () && this->currentTime <= this->activeDurations->At ( i ) )
                    {
                        float totalTrackPercent = 0.0f;
                        if ( track->GetDuration () * track->GetSpeedEffect () != 0 )
                        {
                            totalTrackPercent = ( this->currentTime - track->GetBeginOffset () ) / ( track->GetDuration ()
                                * track->GetSpeedEffect () );
                        }

                        int currentIteration = (int) totalTrackPercent;
                        bool newIteration = false;
                        if ( this->trackIterations->At ( i ) < currentIteration )
                        {
                            newIteration = true;
                            this->trackIterations->At ( i ) = currentIteration;
                        }
                        
                        if ( newIteration && this->trackIterations->At ( i ) != 0 )
                        {
                            track->AccumulateValue ();
                        }
                    }
                    animationData->ResetAnimatedValue ();
                }
            }

            // Calculate the current local time.
            this->currentTime = Math::ToSeconds ( (float) ( time - startTime ) );
            
            float percent = 0.0f;
            bool trackIsActive = false;
            
            // Go through the tracks and update them.
            for ( int i = 0; i < this->animationTracks->Size (); i++ )
            {
                track = this->animationTracks->At ( i );
                
                // Get whether the track is active or not.
                trackIsActive = ( this->currentTime >= track->GetBeginOffset () && this->currentTime <= this->activeDurations->At ( i ) )
                    || ( this->activeDurations->At ( i ) == ANIMATION_INDEFINITE );
                
                // If the current animation track is active, update it.
                if ( trackIsActive )
                {
                    // Calculate the percentage through the track, taking into account the begin offset, the track's duration
                    // and the track's speed. The total track percent represents the complete percent through the track's duration
                    // including repeats while the percent variable holds the local percent through the duration.
                    // (i.e. if the animation is 4.5 times through the animation track, then the total track percent would be
                    // 4.5 while the local percent would be 0.5).
                    float totalTrackPercent = 0.0f;
                    if ( track->GetDuration () * track->GetSpeedEffect () != 0 )
                    {
                        totalTrackPercent = ( this->currentTime - track->GetBeginOffset () ) / ( track->GetDuration ()
                            * track->GetSpeedEffect () );
                    }
                    percent = Math::FractionalPart ( totalTrackPercent );
                    percent = Math::Clamp ( percent, 0.0f, 1.0f );
                    
                    // For the special case where the currentTime is at the
                    // end of the track's duration, forcibly set it to 1.0.
                    if ( this->currentTime > track->GetBeginOffset () && Math::ApproximatelyEqual ( percent, 0.0f, 0.000001f ) )
                    {
                        percent = 1.0f;
                    }
                    track->Update ( percent );
                    
                    // If the track used to be inactive and should now be active, then update its active status.
                    if ( !this->activeTracks->At ( i ) && trackIsActive )
                    {
                        this->activeTracks->At ( i ) = true;
                    }
                }
                // If the track used to be active and now is not, then we are at the end of
                // the animation track. Thus, we resolve the fill for the track and clear the accumulated values.
                else if ( this->activeTracks->At ( i ) && !trackIsActive )
                {
                    // Resolve the fill.
                    if ( track->GetFillMode () == REMOVE )
                    {
                        animationData = track->GetAnimationData ();
                        if ( animationData != null )
                        {
                            animationData->ResetAnimatedValue ();
                        }
                    }
                    else if ( track->GetFillMode () == FREEZE )
                    {
                        // Calculate the percentage through the track using the repeat count, duration, and repeat duration.
                        float repeatDuration = track->GetRepeatDuration ();
                        float simpleDuration = track->GetRepeatCount () * track->GetDuration ();
                        
                        // The repeat duration constrains the repeat count.
                        if ( repeatDuration < simpleDuration && repeatDuration != ANIMATION_NONE )
                        {
                            percent = ( track->GetDuration () == 0.0f ) ? 0.0f : Math::FractionalPart ( repeatDuration
                                / track->GetDuration () );
                        }
                        else
                        {
                            percent = ( track->GetDuration () == 0.0f ) ? 0.0f : Math::FractionalPart ( simpleDuration
                                / track->GetDuration () );
                        }

                        // If the percent is zero, then we conclude that we have just finished the track
                        // (and thus we should evaluate and freeze at percent = 1.0).
                        if ( Math::ApproximatelyEqual ( percent, 0.0f ) )
                        {
                            percent = 1.0f;
                        }
                        track->Update ( percent );
                        
                        // Save the frozen value as the new reset value until the
                        // animation is started from the beginning again.
                        animationData = track->GetAnimationData ();
                        if ( animationData != null && animationData->GetTarget () != null )
                        {
                            AnimationSession* session = animationData->GetAnimationSession ();
                            if ( session != null )
                            {
                                animationData->GetTarget ()->GetTargetAttributeValue ( animationData->GetTargetAttribute (),
                                    session->resetValue, session->valueSize );
                            }
                        }
                    }

                    // Clear accumulation values since the track is finished.
                    if ( track->IsAccumulative () )
                    {
                        track->ClearAccumulatedValue ();
                    }
                    
                    // Update the track's active status.
                    this->activeTracks->At ( i ) = false;
                }
            }
            
            // Check if the duration is positive or indefinite (normal case).
            if ( this->duration > 0.0f || this->duration == ANIMATION_INDEFINITE )
            {
                float totalPercent = ( this->currentTime / this->duration );
                totalPercent = Math::Clamp ( totalPercent, 0.0f, 1.0f );
                
                // If we are at the end of the animation, then set it as inactive and reset the current time.
                if ( Math::ApproximatelyEqual ( totalPercent, 1.0f ) )
                {
                    // Go through the active tracks and resolve the fill and perform accumulation for them.
                    for ( int i = 0; i < this->animationTracks->Size (); i++ )
                    {
                        track = this->animationTracks->At ( i );
                        
                        if ( this->activeTracks->At ( i ) )
                        {
                            // Resolve the fill.
                            if ( track->GetFillMode () == REMOVE )
                            {
                                animationData = track->GetAnimationData ();
                                if ( animationData != null )
                                {
                                    animationData->ResetAnimatedValue ();
                                }
                            }
                            // Note that we do not re-evaluate here at the current percent for
                            // fill mode equal to freeze because the track is still active
                            // and thus was just evaluated above.
                            else
                            {
                                // Save the frozen value as the new reset value until the
                                // animation is started from the beginning again.
                                animationData = track->GetAnimationData ();
                                if ( animationData != null && animationData->GetTarget () != null )
                                {
                                    AnimationSession* session = animationData->GetAnimationSession ();
                                    if ( session != null )
                                    {
                                        animationData->GetTarget ()->GetTargetAttributeValue ( animationData->GetTargetAttribute (),
                                            session->resetValue, session->valueSize );
                                    }
                                }
                            }

                            // Clear accumulation values since the track is finished.
                            if ( track->IsAccumulative () )
                            {
                                track->ClearAccumulatedValue ();
                            }
                            
                            // Update the track's active status.
                            this->activeTracks->At ( i ) = false;
                        }
                    }

                    // Mark the animation as inactive and reset the current time.
                    this->isActive = false;
                    this->currentTime = 0.0f;
                }
            }
            else
            {
                // The duration is zero, so we are done.
                this->isActive = false;
            }
        }
    }
    
    void Animation::CalculateDuration ()
    {
        // Reset the duration and recalculate it.
        this->duration = 0.0f;
        
        // Go through the tracks and find the greatest active duration.
        for ( int i = 0; i < this->animationTracks->Size (); i++ )
        {
            // Check if the animation track's duration is indefinite.
            if ( this->activeDurations->At ( i ) == ANIMATION_INDEFINITE )
            {
                this->duration = ANIMATION_INDEFINITE;
                return;
            }
            
            // Check if the animation track's duration is longer than 
            // the currently calculated duration.
            if ( this->activeDurations->At ( i ) > this->duration )
            {
                this->duration = this->activeDurations->At ( i );
            }
        }
    }
    
    float Animation::CalculateActiveDuration ( AnimationTrack* track )
    {
        if ( track != null )
        {
            float duration = track->GetDuration ();
            float repeatCount = track->GetRepeatCount ();
            float repeatDuration = track->GetRepeatDuration ();
            float beginOffset = track->GetBeginOffset ();
            float speedEffect = track->GetSpeedEffect ();
            
            // Check if the animation track repeats indefinitely.
            if ( repeatCount == ANIMATION_INDEFINITE )
            {
                return ANIMATION_INDEFINITE;
            }
            // Check if the simple duration (the duration times the repeat count)
            // is less than or equal to the repeat duration or if the repeat
            // duration is not specified (it is set to -1f by default).
            else if ( ( ( duration * repeatCount ) <= repeatDuration ) || repeatDuration == ANIMATION_NONE )
            {
                return beginOffset + ( speedEffect * ( duration * repeatCount ) );
            }
            else
            {
                return beginOffset + ( speedEffect * repeatDuration );
            }
        }
        else
        {
            return 0.0f;
        }
    }

}
