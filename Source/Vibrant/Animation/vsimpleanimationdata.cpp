/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsimpleanimationdata.cpp
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
#include "vmath.h"
#include "vmatrix.h"
#include "vquaternion.h"
#include "vsimpleanimationdata.h"

namespace Vibrant
{
    
    SimpleAnimationData::SimpleAnimationData ( Animatable* target, String targetAttribute, float* fromValue, float* toValue, float* byValue ) :
        AnimationData ( target, targetAttribute )
    {
        // Validate the from, to, and by values.
        if ( fromValue == null )
        {
            throw NullPointerException ( "SimpleAnimationData::SimpleAnimationData - The from value must be non-null." );
        }
        if ( toValue == null && byValue == null )
        {
            throw NullPointerException ( "SimpleAnimationData::SimpleAnimationData - The to or by value must be non-null." );
        }

        this->fromValue = fromValue;
        this->toValue = toValue;
        this->byValue = byValue;
        if ( this->targetAttribute != -1 )
        {
            this->finalValue = new float[ this->targetAttributeSize ];
        }
        else
        {
            this->finalValue = null;
        }
        
        this->animationType = ( toValue != null ) ? FROM_TO : FROM_BY;
    }
    
    SimpleAnimationData::~SimpleAnimationData ()
    {
        if ( this->finalValue != null )
        {
            delete[] this->finalValue;
            this->finalValue = null;
        }
    }
    
    SimpleAnimationType SimpleAnimationData::GetAnimationType ()
    {
        return this->animationType;
    }
    
    float* SimpleAnimationData::GetFromValue ()
    {
        return this->fromValue;
    }
    
    float* SimpleAnimationData::GetToValue ()
    {
        return this->toValue;
    }
    
    float* SimpleAnimationData::GetByValue ()
    {
        return this->byValue;
    }
    
    void SimpleAnimationData::SetAnimationType ( SimpleAnimationType animationType )
    {
        this->animationType = animationType;
    }
    
    void SimpleAnimationData::SetFromValue ( float* fromValue )
    {
        if ( fromValue == null )
        {
            throw NullPointerException ( "SimpleAnimationData::SetFromValue - The from value must be non-null." );
        }
        this->fromValue = fromValue;
    }
    
    void SimpleAnimationData::SetToValue ( float* toValue )
    {
        if ( toValue == null )
        {
            throw NullPointerException ( "SimpleAnimationData::SetToValue - The to value must be non-null." );
        }
        this->toValue = toValue;
    }
    
    void SimpleAnimationData::SetByValue ( float* byValue )
    {
        if ( byValue == null )
        {
            throw NullPointerException ( "SimpleAnimationData::SetByValue - The by value must be non-null." );
        }
        this->byValue = byValue;
    }
    
    void SimpleAnimationData::Update ( float percent, float blendWeight, bool additive )
    {
        // Make sure the animation target exists and the target attribute is supported.
        if ( this->target != null && this->targetAttribute != -1 && this->session != null )
        {
            this->target->GetTargetAttributeValue ( this->targetAttribute, this->animatedValue, this->targetAttributeSize );
            
            // Perform interpolation according to the attribute type being animated.
            switch ( this->targetAttributeType )
            {
                case QUATERNION:
                {
                    // Set the final value for the given animation type.
                    if ( this->animationType == FROM_TO )
                    {
                        for ( int i = 0; i < this->targetAttributeSize; i++ )
                        {
                            this->finalValue[ i ] = this->toValue[ i ];
                        }
                    }
                    else if ( this->animationType == FROM_BY )
                    {
                        // Create the 'from' and 'by' quaternions.
                        Quaternion fromQuaternion ( this->fromValue[ 0 ], this->fromValue[ 1 ], this->fromValue[ 2 ], this->fromValue[ 3 ] );
                        Quaternion byQuaternion ( this->byValue[ 0 ], this->byValue[ 1 ], this->byValue[ 2 ], this->byValue[ 3 ] );
                        
                        // Multiple the quaternions and extract the final values.
                        Quaternion animatedQuaternion = fromQuaternion * byQuaternion;
                        this->finalValue[ 0 ] = animatedQuaternion.GetX ();
                        this->finalValue[ 1 ] = animatedQuaternion.GetY ();
                        this->finalValue[ 2 ] = animatedQuaternion.GetZ ();
                        this->finalValue[ 3 ] = animatedQuaternion.GetW ();
                    }

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
                        case PACED:
                        {
                            if ( additive )
                            {
                                // Save the current quaternion.
                                Quaternion currentQuaternion ( this->animatedValue[ 0 ], this->animatedValue[ 1 ],
                                    this->animatedValue[ 2 ], this->animatedValue[ 3 ] );
                                
                                // Save the from and final quaternions.
                                Quaternion fromQuaternion ( this->fromValue[ 0 ], this->fromValue[ 1 ], this->fromValue[ 2 ],
                                    this->fromValue[ 3 ] );
                                Quaternion finalQuaternion ( this->finalValue[ 0 ], this->finalValue[ 1 ], this->finalValue[ 2 ],
                                    this->finalValue[ 3 ] );
                                
                                // Create a quaternion representing the final animated quaternion value (including additive composition).
                                Quaternion animatedQuaternion = currentQuaternion * ( Quaternion::Interpolate ( fromQuaternion,
                                    finalQuaternion, percent ) * blendWeight );
                                
                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            else
                            {
                                // Save the from and final quaternions.
                                Quaternion fromQuaternion ( this->fromValue[ 0 ], this->fromValue[ 1 ], this->fromValue[ 2 ],
                                    this->fromValue[ 3 ] );
                                Quaternion finalQuaternion ( this->finalValue[ 0 ], this->finalValue[ 1 ], this->finalValue[ 2 ],
                                    this->finalValue[ 3 ] );
                                
                                // Create a quaternion representing the final animated quaternion value.
                                Quaternion animatedQuaternion = ( Quaternion::Interpolate ( fromQuaternion, finalQuaternion, percent )
                                    * blendWeight );
                                
                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            break;
                        }
                        case DISCRETE:
                        {
                            if ( additive )
                            {
                                // Save the current quaternion.
                                Quaternion currentQuaternion ( this->animatedValue[ 0 ], this->animatedValue[ 1 ],
                                    this->animatedValue[ 2 ], this->animatedValue[ 3 ] );
                                
                                // Create a quaternion representing the animated quaternion value (includes the additive composition).
                                Quaternion animatedQuaternion;
                                if ( percent >= 0.5f )
                                {
                                    animatedQuaternion = currentQuaternion * ( Quaternion ( this->finalValue[ 0 ], this->finalValue[ 1 ],
                                        this->finalValue[ 2 ], this->finalValue[ 3 ] ) * blendWeight );
                                }
                                else
                                {
                                    animatedQuaternion = currentQuaternion * ( Quaternion ( this->fromValue[ 0 ], this->fromValue[ 1 ],
                                        this->fromValue[ 2 ], this->fromValue[ 3 ] ) * blendWeight );
                                }

                                this->animatedValue[ 0 ] = animatedQuaternion.GetX ();
                                this->animatedValue[ 1 ] = animatedQuaternion.GetY ();
                                this->animatedValue[ 2 ] = animatedQuaternion.GetZ ();
                                this->animatedValue[ 3 ] = animatedQuaternion.GetW ();
                            }
                            else
                            {
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = ( ( percent >= 0.5f ) ? this->finalValue[ i ] : this->fromValue[ i ] )
                                        * blendWeight;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                } // QUATERNION
                case MATRIX:
                {
                    // Set the final value for the given animation type.
                    if ( this->animationType == FROM_TO )
                    {
                        for ( int i = 0; i < this->targetAttributeSize; i++ )
                        {
                            this->finalValue[ i ] = this->toValue[ i ];
                        }
                    }
                    else if ( this->animationType == FROM_BY )
                    {
                        // Create the 'from' and 'by' matrices.
                        Matrix fromMatrix ( this->fromValue );
                        Matrix byMatrix ( this->byValue );
                        
                        // Multiple the matrices and extract the float array to get the final values.
                        ( fromMatrix * byMatrix ).CopyValues ( this->finalValue );
                    }

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
                        case PACED:
                        {
                            if ( additive )
                            {
                                // Save the current matrix.
                                Matrix currentMatrix ( this->animatedValue );
                                
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( 0.0f, 1.0f, this->fromValue[ i ], this->finalValue[ i ],
                                        percent ) * blendWeight;
                                }

                                // Create a matrix representing the animated matrix (that will be composed onto the current matrix).
                                Matrix animatedMatrix ( this->animatedValue );
                                ( currentMatrix * animatedMatrix ).CopyValues ( this->animatedValue );
                            }
                            else
                            {
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( 0.0f, 1.0f, this->fromValue[ i ], this->finalValue[ i ],
                                        percent ) * blendWeight;
                                }
                            }
                            break;
                        }
                        case DISCRETE:
                        {
                            if ( additive )
                            {
                                // Save the current matrix.
                                Matrix currentMatrix ( this->animatedValue );
                                
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = ( ( percent >= 0.5f ) ? this->finalValue[ i ] : this->fromValue[ i ] )
                                        * blendWeight;
                                }

                                // Create a matrix representing the animated matrix (that will be composed onto the current matrix).
                                Matrix animatedMatrix ( this->animatedValue );
                                ( currentMatrix * animatedMatrix ).CopyValues ( this->animatedValue );
                            }
                            else
                            {
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = ( ( percent >= 0.5f ) ? this->finalValue[ i ] : this->fromValue[ i ] )
                                        * blendWeight;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                } // MATRIX
                case SCALAR:
                {
                    // Set the final value for the given animation type.
                    if ( this->animationType == FROM_TO )
                    {
                        for ( int i = 0; i < this->targetAttributeSize; i++ )
                        {
                            this->finalValue[ i ] = this->toValue[ i ];
                        }
                    }
                    else if ( this->animationType == FROM_BY )
                    {
                        for ( int i = 0; i < this->targetAttributeSize; i++ )
                        {
                            this->finalValue[ i ] = this->fromValue[ i ] + this->byValue[ i ];
                        }
                    }

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
                        case PACED:
                        {
                            if ( additive )
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] += Math::Lerp ( 0.0f, 1.0f, this->fromValue[ i ], this->finalValue[ i ],
                                        percent ) * blendWeight;
                                }
                            }
                            else
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = Math::Lerp ( 0.0f, 1.0f, this->fromValue[ i ], this->finalValue[ i ],
                                        percent ) * blendWeight;
                                }
                            }
                            break;
                        }
                        case DISCRETE:
                        {
                            if ( additive )
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] += ( ( percent >= 0.5f ) ? this->finalValue[ i ] : this->fromValue[ i ] )
                                        * blendWeight;
                                }
                            }
                            else
                            {
                                // Interpolate all the values.
                                for ( int i = 0; i < this->targetAttributeSize; i++ )
                                {
                                    this->animatedValue[ i ] = ( ( percent >= 0.5f ) ? this->finalValue[ i ] : this->fromValue[ i ] )
                                        * blendWeight;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                } // SCALAR
                default:
                    break;
            }
            
            // Apply the animated value to the target.
            this->target->ApplyAnimatedValue ( this->animatedValue, this->targetAttributeSize, this->targetAttribute );
        }
    }

}
