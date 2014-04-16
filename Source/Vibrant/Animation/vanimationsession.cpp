/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vanimationsession.cpp
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

#include "vanimationdata.h"
#include "vanimationsession.h"

namespace Vibrant
{
    
    AnimationSession::AnimationSession ()
    {
        // Set to default values.
        this->originalValue = null;
        this->resetValue = null;
    }
    
    AnimationSession::~AnimationSession ()
    {
        // Clean up values.
        if ( this->originalValue != null )
        {
            delete[] this->originalValue;
            this->originalValue = null;
        }
        if ( this->resetValue != null )
        {
            delete[] this->resetValue;
            this->resetValue = null;
        }
    }
    
    void AnimationSession::Register ( const AnimationData* animationData )
    {
        // If the animation data object is nonexistant, then just do nothing.
        if ( animationData == null )
        {
            return;
        }

        // Maybe actually do some sort of registration here later
        // but for now we just initialize the values if we need to.
        if ( this->originalValue == null )
        {
            this->originalValue = new float[ this->valueSize ];
        }
        if ( this->resetValue == null )
        {
            this->resetValue = new float[ this->valueSize ];
        }
    }

}
