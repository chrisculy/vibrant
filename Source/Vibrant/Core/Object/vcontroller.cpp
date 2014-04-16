/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vcontroller.cpp
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

#include "varray.h"
#include "vcontroller.h"
#include "vreader.h"
#include "vwriter.h"

namespace Vibrant
{
    
    Controller::~Controller ()
    {
        /* stub function */
    }
    
    Pointer< Object > Controller::GetObject ()
    {
        return this->obj;
    }
    
    bool Controller::Update ( long time )
    {
        /* stub function */
        return false;
    }
    
    const RTTI* Controller::GetType () const
    {
        return Controller::GetRTTI ();
    }
    
    RTTI* Controller::GetRTTI ()
    {
        static RTTI* type = null;
        if ( type == null )
        {
            Array< RTTI* > baseTypes;
            baseTypes.Push ( Object::GetRTTI () );
            type = new RTTI ( "Controller", baseTypes );
        }
        return type;
    }
    
    const int Controller::GetDiskSize () const
    {
        /* stub function */
        return 0;
    }
    
    void Controller::Write ( Writer* writer ) const
    {
        writer->BeginObject ( this->GetType ()->GetName () );
        
        // Write out the Object part of this object.
        writer->BeginBase ();
        Object::Write ( writer );
        writer->EndBase ();
        
        writer->EndObject ();
    }
    
    void Controller::Read ( Reader* reader )
    {
        reader->BeginObject ( this->GetType ()->GetName () );
        
        // Read in the Object part of this object.
        reader->BeginBase ();
        Object::Read ( reader );
        reader->EndBase ();
        
        reader->EndObject ();
    }
    
    Controller::Controller ()
    {
        /* stub function */
    }
    
    void Controller::SetObject ( Object* obj )
    {
        this->obj = obj;
    }
    
    double Controller::GetControllerTime ( double applicationTime ) const
    {
        /* stub function */
        return 0.0;
    }

}
