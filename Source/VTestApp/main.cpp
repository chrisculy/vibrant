/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: main.cpp
 * 
 * 
 * --  Copyright (c) 2007-2009 Alterr.  --
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

#ifdef SYSTEM_GENERIC

#include "vapplication.h"
#include "vconfig.h"
#include "vgfloaderdemo.h"
#include "vinputdemo.h"

int main ( int argc, char** argv )
{
    // Load the configuration.
    Config* config = new Config ();
    config->Load ();

    // Create the application and run it.
    //Application app ( config );
    //app.Run ();

    // *** VGFLoader demo. *** //
    return VGFLoaderDemo ();
    // *** VGFLoader demo. *** //

    // *** Input demo. *** //
    //return VInputDemo ();
    // *** Input demo. *** //

    return 0;
}

#endif
