/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vreader.cpp
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

#include "vreader.h"

namespace Vibrant
{
    
    Reader::Reader ( Stream* stream )
    {
        this->stream = stream;
    }
    
    Reader::~Reader ()
    {
        /* stub function */
    }

}
