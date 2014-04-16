/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwriter.cpp
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

#include "vwriter.h"

namespace Vibrant
{
    
    Writer::Writer ( Stream* stream )
    {
        this->stream = stream;
    }
    
    Writer::~Writer ()
    {
        /* stub function */
    }
    
    void Writer::Write ()
    {
        this->stream->Flush ();
    }

}
