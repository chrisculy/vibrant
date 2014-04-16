/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vnetworklayer.cpp
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

#include "vnetworklayer.h"
#include "vstring.h"

namespace Vibrant
{
    
    // Initialize static members.
    String NetworkLayer::errorMessage;
    int NetworkLayer::activeSocketCount = 0;

}
