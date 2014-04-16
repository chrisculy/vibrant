/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: winmain.cpp
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

#include "vanimationdemo.h"
#include "vconfig.h"
#include "vlog.h"
#include "testapplication.h"
#include "vwindowsapplication.h"
#include "vwindowsexception.h"

using namespace Vibrant;

static void logException ( Exception* e )
{
    Log vlog;
    vlog << ERR << e->GetMessage ();
}

int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    try
    {
        // Load the configuration.
        Config* config = new Config ();
        config->Load ();
        
        WindowsApplication* app = null;
        
        // Create the application and run it.
        //app = new WindowsApplication ( config, hInstance );
        app = new AnimationWindowsApplication ( config, hInstance );
        //app = new Osprey::TestApplication ( config, hInstance );
        
        app->Run ();
        
        // Application is done, so delete the application object.
        delete app;
        app = null;
        
        // Clean up the configuration.
        delete config;
        config = null;
    }
    catch ( WindowsException we )
    {
        logException ( &we );
    }
    catch ( NullPointerException npe )
    {
        logException ( &npe );
    }
    catch ( IllegalArgumentException iae )
    {
        logException ( &iae );
    }
    catch ( IllegalOperationException ioe )
    {
        logException ( &ioe );
    }
    catch ( IndexOutOfBoundsException ioobe )
    {
        logException ( &ioobe );
    }
    catch ( EmptyContainerException ece )
    {
        logException ( &ece );
    }
    catch ( NotSupportedOperationException nsoe )
    {
        logException ( &nsoe );
    }
    catch ( FileIOException fioe )
    {
        logException ( &fioe );
    }
    catch ( NetworkException ne )
    {
        logException ( &ne );
    }
    catch ( Exception e )
    {
        logException ( &e );
    }
    
    return 0;
}

#endif
