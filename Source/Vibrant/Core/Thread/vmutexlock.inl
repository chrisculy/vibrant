/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vmutexlock.inl
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

#include "vmutex.h"

namespace Vibrant
{
    
    inline MutexLock::MutexLock ( const Mutex* mutex )
    {
        this->mutex = const_cast< Mutex* > ( mutex );
        this->mutex->Lock ();
    }
    
    inline MutexLock::~MutexLock ()
    {
        this->mutex->Unlock ();
    }

}
