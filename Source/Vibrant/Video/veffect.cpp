/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: veffect.cpp
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

#include "veffect.h"
#include "vreader.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Effect::Effect ()
    {
        /* stub function */
    }
    
    Effect::~Effect ()
    {
        /* stub function */
    }
    
    const RTTI* Effect::GetType () const
    {
        return Effect::GetRTTI ();
    }
    
    RTTI* Effect::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            type = new RTTI ( "Effect", baseTypes );
        }
        return type;
    }
    
    const int Effect::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Effect::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        
        // Write the Object part of this object.
        writer->BeginBase ();
        Object::Write ( writer );
        writer->EndBase ();
        writer->EndObject ();
    }
    
    void Effect::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        
        // Read the Object part of this object.
        reader->BeginBase ();
        Object::Read ( reader );
        reader->EndBase ();
        reader->EndObject ();
    }

}
