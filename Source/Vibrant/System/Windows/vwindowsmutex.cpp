/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsmutex.cpp
 * 
 * 
 * --  Copyright (c) 2007-2008 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision: 130 $
 * $Author: Chris $
 * $Date: 2008-01-16 22:31:42 -0500 (Wed, 16 Jan 2008) $
 */

// Include Precompiled Header.
#include "vprecompiled.h"

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#ifdef _DEBUG
#include "vlog.h"
#endif

#include "vconvert.h"
#include "vwindowsmutex.h"

namespace Vibrant
{
    
    WindowsMutex::WindowsMutex ()
    {
        this->handle = null;
        this->name = WindowsMutex::GetNextName ();
    }
    
    WindowsMutex::~WindowsMutex ()
    {
        /* stub function */
    }
    
    void WindowsMutex::Wait ()
    {
        // Wait on the mutex if it is valid and locked.
        if ( this->handle != null )
        {
            WaitForSingleObject ( this->handle, INFINITE );
        }
        // If the mutex is not valid and we are
        // in debug mode, vlog a warning.
        else
        {
#ifdef _DEBUG
            //vlog << WARN << "Attempting to wait on an invalid mutex.\n";
#endif
        }
    }
    
    void WindowsMutex::Lock ()
    {
        this->handle = CreateMutex ( null, true, this->name.CString () );
    }
    
    void WindowsMutex::Unlock ()
    {
        ReleaseMutex ( this->handle );
        this->handle = null;
    }
    
    String WindowsMutex::GetNextName ()
    {
        static unsigned long uid = 0;
        static String nextName;
        
        // Use the uid as the mutex name.
        ValToString ( uid, &nextName );
        
        // This will eventually wrap around, but we don't care.
        uid++;
        return nextName;
    }

}

#endif
