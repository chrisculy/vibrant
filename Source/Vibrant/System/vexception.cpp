/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vexception.cpp
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

#include "vexception.h"

namespace Vibrant
{
    
    Exception::Exception ( String message )
    {
        this->message = message;
    }
    
    String Exception::GetMessage ()
    {
        return this->message;
    }

}
