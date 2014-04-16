/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationdata.cpp
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

#include "vanimatable.h"
#include "vanimationdata.h"
#include "vstring.h"

namespace Vibrant
{
    void AnimationData::SetTarget ( Animatable* target, String attributeName )
    {
        // Set the default values.
        this->target = target;
        this->targetAttribute = -1;
        this->targetAttributeSize = 0;
        this->targetAttributeType = SCALAR;
        this->session = null;
        
        // Update the target attribute, target attribute size, and the animation session.
        if ( this->target != null )
        {
            this->targetAttribute = this->target->GetTargetAttribute ( attributeName );
            
            if ( this->targetAttribute != -1 )
            {
                this->targetAttributeSize = this->target->GetTargetAttributeSize ( this->targetAttribute );
                this->targetAttributeType = this->target->GetTargetAttributeType ( this->targetAttribute );
                this->session = this->target->GetAnimationSession ( this->targetAttribute );
                
                // Initialize the member variable to be used to calculate the current
                // animated value (cleaning up the old one if it exists).
                if ( this->animatedValue != null )
                {
                    delete[] animatedValue;
                    animatedValue = null;
                }
                this->animatedValue = new float[ this->targetAttributeSize ];
                
                // Register with the session.
                this->session->Register ( this );
                this->ResetAnimationSession ();
            }
        }
    }
}
