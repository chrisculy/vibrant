/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vdisplaystyle.cpp
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

#include "vdisplaystyle.h"

namespace Vibrant
{
    
    DisplayStyle::DisplayStyle ( bool is2D ) :
        is2D ( is2D )
    {
        /* stub function */
    }
    
    DisplayStyle::~DisplayStyle ()
    {
        /* stub function */
    }
    
    bool DisplayStyle::Is2D () const
    {
        return is2D;
    }

    void DisplayStyle::SetIs2D ( const bool is2D )
    {
        this->is2D = is2D;
    }
}
