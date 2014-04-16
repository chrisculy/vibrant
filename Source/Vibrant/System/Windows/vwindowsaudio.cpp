/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsaudio.cpp
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vconfig.h"
#include "vlog.h"
#include "vwindowsaudio.h"

namespace Vibrant
{
    
    WindowsAudio::WindowsAudio ( Config* config ) :
        Audio ( config )
    {
        /* stub function */
    }
    
    WindowsAudio::~WindowsAudio ()
    {
        /* stub function */
    }

}

#endif
