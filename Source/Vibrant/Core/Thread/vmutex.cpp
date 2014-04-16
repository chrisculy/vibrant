/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmutex.cpp
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

#include "vmutex.h"
#include "vsystem.h"

#include VIBRANT_MUTEX_INCLUDE_FILE

namespace Vibrant
{
    
    Mutex::Mutex ()
    {
        /* stub function */
    }
    
    Mutex::~Mutex ()
    {
        /* stub function */
    }
    
    Mutex* Mutex::GetNewMutex ()
    {
        return (Mutex*) ( new VIBRANT_MUTEX () );
    }

}
