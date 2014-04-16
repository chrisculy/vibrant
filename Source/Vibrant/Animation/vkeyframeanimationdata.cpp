/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vkeyframeanimationdata.cpp
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

// Include Precompiled Header.
#include "vprecompiled.h"

#include "vanimatable.h"
#include "vanimationmodes.h"
#include "vkeyframeanimationdata.h"
#include "vmath.h"
#include "vmatrix.h"
#include "vquaternion.h"

namespace Vibrant
{
    
    KeyframeAnimationData::KeyframeAnimationData ( Animatable* target, String targetAttribute, Array< float* >* keyValues,
        Array< float >* keyTimes, int keyCount ) :
        AnimationData ( target, targetAttribute )
    {
        this->currentKeyframe = 0;
        
        // Create the key values and key times.
        this->keyValues = new Array< float* > ( keyCount );
        this->keyTimes = new Array< float > ( keyCount );
        
        if ( keyValues != null )
        {
            *this->keyValues = *keyValues;
        }
        
        if ( keyTimes != null )
        {
            *this->keyTimes = *keyTimes;
        }
    }
    
    KeyframeAnimationData::~KeyframeAnimationData ()
    {
        if ( this->keyValues != null )
        {
            delete this->keyValues;
            this->keyValues = null;
        }
        if ( this->keyTimes != null )
        {
            delete this->keyTimes;
            this->keyTimes = null;
        }
    }
    
    void KeyframeAnimationData::AddKey ( float* keyValue, float keyTime, int keyIndex )
    {
        // Validate the key value.
        if ( keyValue == null )
        {
            throw NullPointerException ( "KeyframeAnimationData::AddKey - The key value must be non-null." );
        }
        this->keyValues->Insert ( keyValue, keyIndex );
        this->keyTimes->Insert ( keyTime, keyIndex );
    }
    
    const int KeyframeAnimationData::GetKeyCount ()
    {
        if ( this->keyValues != null )
        {
            return this->keyValues->Size ();
        }
        return 0;
    }
    
    Array< float* >* KeyframeAnimationData::GetKeyValues ()
    {
        return this->keyValues;
    }
    
    Array< float >* KeyframeAnimationData::GetKeyTimes ()
    {
        return this->keyTimes;
    }
    
    void KeyframeAnimationData::SetKeyValues ( Array< float* >* keyValues )
    {
        this->keyValues = keyValues;
    }
    
    void KeyframeAnimationData::SetKeyTimes ( Array< float >* keyTimes )
    {
        this->keyTimes = keyTimes;
    }
    
    void KeyframeAnimationData::Update ( float percent, float blendWeight, bool additive )
    {
        // Make sure the animation target exists, the target attribute is supported,
        // and that we have key values and key times.
        if ( this->target != null && this->targetAttribute != -1 && this->keyValues != null && this->keyTimes != null )
        {
            this->target->GetTargetAttributeValue ( this->targetAttribute, this->animatedValue, this->targetAttributeSize );
            
            // Perform interpolation according to the attribute type being animated.
            switch ( this->targetAttributeType )
            {
                case QUATERNION:
                {
                    // Interpolate using the set interpolation mode.
                    switch ( this->mode )
                    {
                        case SPLINE:
                        {
                            // Calculate the altered percent using spline interpolation.
                            if ( this->keyPoints != null )
                            {
                                percent = Math::Clamp ( Math::EvaluateCubicHermiteSpline1D ( this->keyPoints, percent ), 0.0f, 1.0f );
                            }
                            
                            // Let the execution fall through to linear (this is how we do spline-we just
                            // alter the percent and then evaluate the rest as a normal linear interpolation).
                        }
                        case LINEAR:
                        {
                            // Update the current keyframe.
                            this->UpdateCurrentKeyframe ( percent );
                            
                            // Calculate the percent between the key frames.
                            float percentBetweenKeyFrames = ( percent - this->keyTimes->At ( this->currentKeyframe ) )
                                / ( this->keyTimes->At ( this->currentKeyframe + 1 ) - this->keyTimes->At ( this->currentKeyframe ) );
                            if ( additive )
                            {
                                // Save the current quaternion.
                                Quaternion currentQuaternion ( this->animatedValue[ 0 ], this->animatedValue[ 1 ],
                                    this->animatedValue[ 2 ], this->animatedValue[ 3 ] );
                                
                                // Save the from and final quaternions.
                                Quaternion fromQuaternion ( this->keyValues->At ( this->currentKeyframe )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe )[ 1 ], this->keyValues->At ( this->currentKeyframe )[ 2 ], this->keyValues->At (
                                    this->currentKeyframe )[ 3 ] );
                                Quaternion finalQuaternion ( this->keyValues->At ( this->currentKeyframe + 1 )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe + 1 )[ 1 ], this->keyValues->At ( this->currentKeyframe + 1 )[ 2 ],
                                    this->keyValues->At ( this->currentKeyframe + 1 )[ 3 ] );
                                
                                // Create a quaternion representing the final animated quaternion value (including additive composition).
                                Quaternion animatedQuaternion = currentQuaternion * ( Quaternion::Interpolate ( fromQuaternion,
                                    finalQuaternion, percentBetweenKeyFrames ) * blendWeight );
                                
                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            else
                            {
                                // Save the from and final quaternions.
                                Quaternion fromQuaternion ( this->keyValues->At ( this->currentKeyframe )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe )[ 1 ], this->keyValues->At ( this->currentKeyframe )[ 2 ], this->keyValues->At (
                                    this->currentKeyframe )[ 3 ] );
                                Quaternion finalQuaternion ( this->keyValues->At ( this->currentKeyframe + 1 )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe + 1 )[ 1 ], this->keyValues->At ( this->currentKeyframe + 1 )[ 2 ],
                                    this->keyValues->At ( this->currentKeyframe + 1 )[ 3 ] );
                                
                                // Create a quaternion representing the final animated quaternion value.
                                Quaternion animatedQuaternion = ( Quaternion::Interpolate ( fromQuaternion, finalQuaternion,
                                    percentBetweenKeyFrames ) * blendWeight );
                                
                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            break;
                        }
                        case DISCRETE:
                        {
                            // Update the current keyframe.
                            this->UpdateCurrentKeyframe ( percent );
                            
                            // Calculate the percent between the key frames.
                            float percentBetweenKeyFrames = ( percent - this->keyTimes->At ( this->currentKeyframe ) )
                                / ( this->keyTimes->At ( this->currentKeyframe + 1 ) - this->keyTimes->At ( this->currentKeyframe ) );
                            if ( percentBetweenKeyFrames < 0.5f )
                            {
                                if ( additive )
                                {
                                    // Save the current quaternion.
                                    Quaternion currentQuaternion ( this->animatedValue[ 0 ], this->animatedValue[ 1 ],
                                        this->animatedValue[ 2 ], this->animatedValue[ 3 ] );
                                    
                                    // Create a quaternion representing the animated quaternion value (includes the additive composition).
                                    Quaternion animatedQuaternion = currentQuaternion * ( Quaternion ( this->keyValues->At (
                                        this->currentKeyframe )[ 0 ], this->keyValues->At ( this->currentKeyframe )[ 1 ],
                                        this->keyValues->At ( this->currentKeyframe )[ 2 ],
                                        this->keyValues->At ( this->currentKeyframe )[ 3 ] ) * blendWeight );
                                    
                                    this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                    this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                    this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                    this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                                }
                                else
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] = ( this->keyValues->At ( this->currentKeyframe )[ i ] ) * blendWeight;
                                    }
                                }
                            }
                            else
                            {
                                if ( additive )
                                {
                                    // Save the current quaternion.
                                    Quaternion currentQuaternion ( this->animatedValue[ 0 ], this->animatedValue[ 1 ],
                                        this->animatedValue[ 2 ], this->animatedValue[ 3 ] );
                                    
                                    // Create a quaternion representing the animated quaternion value (includes the additive composition).
                                    Quaternion animatedQuaternion = currentQuaternion * ( Quaternion ( this->keyValues->At (
                                        this->currentKeyframe + 1 )[ 0 ], this->keyValues->At ( this->currentKeyframe + 1 )[ 1 ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ 2 ], this->keyValues->At ( this->currentKeyframe
                                            + 1 )[ 3 ] ) * blendWeight );
                                    
                                    this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                    this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                    this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                    this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                                }
                                else
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] = ( this->keyValues->At ( this->currentKeyframe + 1 )[ i ] ) * blendWeight;
                                    }
                                }
                            }
                            break;
                        }
                        case PACED:
                        {
                            // Update the current keyframe using the special paced function.
                            this->UpdateCurrentKeyframePaced ( percent );
                            
                            // Calculate the previous and next key times.
                            float keyCountReciprocal = 1.0f / ( (float) this->GetKeyCount () - 1 );
                            float prevKeyTime = ( (float) this->currentKeyframe ) * keyCountReciprocal;
                            float nextKeyTime = ( (float) this->currentKeyframe + 1.0f ) * keyCountReciprocal;
                            
                            // Calculate the percent between the key frames.
                            float percentBetweenKeyFrames = ( percent - prevKeyTime ) / ( nextKeyTime - prevKeyTime );
                            if ( additive )
                            {
                                // Save the current quaternion.
                                Quaternion currentQuaternion ( this->animatedValue[ 0 ], this->animatedValue[ 1 ],
                                    this->animatedValue[ 2 ], this->animatedValue[ 3 ] );
                                
                                // Save the from and final quaternions.
                                Quaternion fromQuaternion ( this->keyValues->At ( this->currentKeyframe )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe )[ 1 ], this->keyValues->At ( this->currentKeyframe )[ 2 ], this->keyValues->At (
                                    this->currentKeyframe )[ 3 ] );
                                Quaternion finalQuaternion ( this->keyValues->At ( this->currentKeyframe + 1 )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe + 1 )[ 1 ], this->keyValues->At ( this->currentKeyframe + 1 )[ 2 ],
                                    this->keyValues->At ( this->currentKeyframe + 1 )[ 3 ] );
                                
                                // Create a quaternion representing the final animated quaternion value (including additive composition).
                                Quaternion animatedQuaternion = currentQuaternion * ( Quaternion::Interpolate ( fromQuaternion,
                                    finalQuaternion, percentBetweenKeyFrames ) * blendWeight );
                                
                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            else
                            {
                                // Save the from and final quaternions.
                                Quaternion fromQuaternion ( this->keyValues->At ( this->currentKeyframe )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe )[ 1 ], this->keyValues->At ( this->currentKeyframe )[ 2 ], this->keyValues->At (
                                    this->currentKeyframe )[ 3 ] );
                                Quaternion finalQuaternion ( this->keyValues->At ( this->currentKeyframe + 1 )[ 0 ], this->keyValues->At (
                                    this->currentKeyframe + 1 )[ 1 ], this->keyValues->At ( this->currentKeyframe + 1 )[ 2 ],
                                    this->keyValues->At ( this->currentKeyframe + 1 )[ 3 ] );
                                
                                // Create a quaternion representing the final animated quaternion value.
                                Quaternion animatedQuaternion = ( Quaternion::Interpolate ( fromQuaternion, finalQuaternion,
                                    percentBetweenKeyFrames ) * blendWeight );
                                
                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case MATRIX:
                {
                    // Interpolate using the set interpolation mode.
                    switch ( this->mode )
                    {
                        case SPLINE:
                        {
                            // Calculate the altered percent using spline interpolation.
                            if ( this->keyPoints != null )
                            {
                                percent = Math::Clamp ( Math::EvaluateCubicHermiteSpline1D ( this->keyPoints, percent ), 0.0f, 1.0f );
                            }
                            
                            // Let the execution fall through to linear (this is how we do spline-we just
                            // alter the percent and then evaluate the rest as a normal linear interpolation).
                        }
                        case LINEAR:
                        {
                            // Update the current keyframe.
                            this->UpdateCurrentKeyframe ( percent );
                            
                            if ( additive )
                            {
                                // Save the current matrix.
                                Matrix currentMatrix ( this->animatedValue );
                                
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }

                                // Create a matrix representing the animated matrix (that will be composed onto the current matrix).
                                Matrix animatedMatrix ( this->animatedValue );
                                ( currentMatrix * animatedMatrix ).CopyValues ( this->animatedValue );
                            }
                            else
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }
                            }
                            break;
                        }
                        case DISCRETE:
                        {
                            // Update the current keyframe.
                            this->UpdateCurrentKeyframe ( percent );
                            
                            float percentBetweenKeyFrames = ( percent - this->keyTimes->At ( this->currentKeyframe ) )
                                / ( this->keyTimes->At ( this->currentKeyframe + 1 ) - this->keyTimes->At ( this->currentKeyframe ) );
                            if ( percentBetweenKeyFrames < 0.5f )
                            {
                                if ( additive )
                                {
                                    // Create matrices for the current value and the animated value.
                                    Matrix currentMatrix ( this->animatedValue );
                                    Matrix animatedMatrix = ( Matrix ( this->keyValues->At ( this->currentKeyframe ) ) ) * blendWeight;
                                    
                                    // Multiply the matrices to get the final animated value.
                                    ( currentMatrix * animatedMatrix ).CopyValues ( this->animatedValue );
                                }
                                else
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] = ( this->keyValues->At ( this->currentKeyframe )[ i ] ) * blendWeight;
                                    }
                                }
                            }
                            else
                            {
                                if ( additive )
                                {
                                    // Create matrices for the current value and the animated value.
                                    Matrix currentMatrix ( this->animatedValue );
                                    Matrix animatedMatrix = ( Matrix ( this->keyValues->At ( this->currentKeyframe + 1 ) ) ) * blendWeight;
                                    
                                    // Multiply the matrices to get the final animated value.
                                    ( currentMatrix * animatedMatrix ).CopyValues ( this->animatedValue );
                                }
                                else
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] = ( this->keyValues->At ( this->currentKeyframe + 1 )[ i ] ) * blendWeight;
                                    }
                                }
                            }
                            break;
                        }
                        case PACED:
                        {
                            // Update the current keyframe using the special paced function.
                            this->UpdateCurrentKeyframePaced ( percent );
                            
                            if ( additive )
                            {
                                // Save the current matrix.
                                Matrix currentMatrix ( this->animatedValue );
                                
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }

                                // Create a matrix representing the animated matrix (that will be composed onto the current matrix).
                                Matrix animatedMatrix ( this->animatedValue );
                                ( currentMatrix * animatedMatrix ).CopyValues ( this->animatedValue );
                            }
                            else
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case SCALAR:
                {
                    // Interpolate using the set interpolation mode.
                    switch ( this->mode )
                    {
                        case SPLINE:
                        {
                            // Calculate the altered percent using spline interpolation.
                            if ( this->keyPoints != null )
                            {
                                percent = Math::Clamp ( Math::EvaluateCubicHermiteSpline1D ( this->keyPoints, percent ), 0.0f, 1.0f );
                            }
                            
                            // Let the execution fall through to linear (this is how we do spline-we just
                            // alter the percent and then evaluate the rest as a normal linear interpolation).
                        }
                        case LINEAR:
                        {
                            // Update the current keyframe.
                            this->UpdateCurrentKeyframe ( percent );
                            
                            if ( additive )
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] += Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }
                            }
                            else
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }
                            }
                            break;
                        }
                        case DISCRETE:
                        {
                            // Update the current keyframe.
                            this->UpdateCurrentKeyframe ( percent );
                            
                            float percentBetweenKeyFrames = ( percent - this->keyTimes->At ( this->currentKeyframe ) )
                                / ( this->keyTimes->At ( this->currentKeyframe + 1 ) - this->keyTimes->At ( this->currentKeyframe ) );
                            if ( percentBetweenKeyFrames < 0.5f )
                            {
                                if ( additive )
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] += ( this->keyValues->At ( this->currentKeyframe )[ i ] ) * blendWeight;
                                    }
                                }
                                else
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] = ( this->keyValues->At ( this->currentKeyframe )[ i ] ) * blendWeight;
                                    }
                                }
                            }
                            else
                            {
                                if ( additive )
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] += ( this->keyValues->At ( this->currentKeyframe + 1 )[ i ] )
                                            * blendWeight;
                                    }
                                }
                                else
                                {
                                    // Interpolate all the values.
                                    for ( int i = 0; i < this->targetAttributeSize; i++ )
                                    {
                                        this->animatedValue[ i ] = ( this->keyValues->At ( this->currentKeyframe + 1 )[ i ] ) * blendWeight;
                                    }
                                }
                            }
                            break;
                        }
                        case PACED:
                        {
                            // Update the current keyframe using the special paced function.
                            this->UpdateCurrentKeyframePaced ( percent );
                            
                            if ( additive )
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] += Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }
                            }
                            else
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( this->keyTimes->At ( this->currentKeyframe ),
                                        this->keyTimes->At ( this->currentKeyframe + 1 ),
                                        this->keyValues->At ( this->currentKeyframe )[ i ],
                                        this->keyValues->At ( this->currentKeyframe + 1 )[ i ], percent ) * blendWeight;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
            
            // Apply the animated value to the target.
            this->target->ApplyAnimatedValue ( this->animatedValue, this->targetAttributeSize, this->targetAttribute );
        }
    }
    
    void KeyframeAnimationData::UpdateCurrentKeyframe ( float percent )
    {
        // Find the current key frame starting with the old current key frame.
        if ( this->currentKeyframe + 2 < this->GetKeyCount () && this->keyTimes->At ( this->currentKeyframe + 1 ) < percent )
        {
            while ( this->currentKeyframe + 2 < this->GetKeyCount () )
            {
                this->currentKeyframe++;
                if ( this->keyTimes->At ( this->currentKeyframe + 1 ) >= percent )
                {
                    break;
                }
            }
        }
        else if ( this->currentKeyframe > 0 && this->keyTimes->At ( this->currentKeyframe ) > percent )
        {
            while ( currentKeyframe > 0 )
            {
                this->currentKeyframe--;
                if ( this->keyTimes->At ( this->currentKeyframe ) < percent )
                {
                    break;
                }
            }
        }
    }
    
    void KeyframeAnimationData::UpdateCurrentKeyframePaced ( float percent )
    {
        // Calculate the reciprocal of the key frame count - 1 (used to calculate the previous and next key times).
        float keyCountReciprocal = 1.0f / ( (float) this->GetKeyCount () - 1 );
        
        // Calculate the previous key time.
        float prevKeyTime = ( (float) this->currentKeyframe ) * keyCountReciprocal;
        
        // Calculate the next key time lazily (i.e. not here-see 'else if' clause below).
        float nextKeyTime = ( (float) this->currentKeyframe + 1.0f ) * keyCountReciprocal;
        
        if ( this->currentKeyframe + 2 < this->GetKeyCount () && nextKeyTime < percent )
        {
            while ( this->currentKeyframe + 2 < this->GetKeyCount () )
            {
                this->currentKeyframe++;
                
                // Calculate the new next key time (we don't care about the previous key time).
                nextKeyTime = ( (float) this->currentKeyframe + 1.0f ) * keyCountReciprocal;
                
                if ( nextKeyTime >= percent )
                {
                    break;
                }
            }
        }
        else if ( this->currentKeyframe > 0 && prevKeyTime > percent )
        {
            while ( currentKeyframe > 0 )
            {
                this->currentKeyframe--;
                
                // Calculate the new previous key time (we don't care about the next key time).
                prevKeyTime = ( (float) this->currentKeyframe ) * keyCountReciprocal;
                
                if ( prevKeyTime <= percent )
                {
                    break;
                }
            }
        }
    }

}
