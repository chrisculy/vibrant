/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vpointable.cpp
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

#include "vpointable.h"
#include "vsystem.h"

#ifdef _DEBUG
#include "vlog.h"
#endif

namespace Vibrant
{
    
    Pointable::Pointable ()
    {
        referenceCount = 0;
    }
    
    Pointable::~Pointable ()
    {
        // If the number of references is not zero,
        // and we are in debug mode, vlog an error.
#ifdef _DEBUG
        if ( referenceCount != 0 )
        {
            //vlog << ERR << "An object was destroyed with " << referenceCount << " active references.\n";
        }
#endif
    }
    
    void Pointable::AddReference ()
    {
        referenceCount++;
    }
    
    void Pointable::RemoveReference ()
    {
        referenceCount--;
    }
    
    int Pointable::ReferenceCount () const
    {
        return referenceCount;
    }

}
