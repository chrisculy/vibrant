/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsapplication.cpp
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

#include "vlog.h"
#include "vstring.h"
#include "vwindowsapplication.h"
#include "vwindowsclient.h"
#include "vwindowsinput.h"
#include "vwindowsexception.h"
#include "vwindowsserver.h"

namespace Vibrant
{
    
    WindowsApplication::WindowsApplication ( Config* config, HINSTANCE hInstance ) :
        Application ( config )
    {
        this->hInstance = hInstance;
        // Get the class name and application title from the configuration.
        this->className = config->GetProperty ( "video_renderer_type" );
        this->title = config->GetProperty ( "application_title" );
        
        // Register the window class.
        if ( !RegisterWindowClass () )
        {
            throw WindowsException ( "Could not register window class.\n" );
        }
        
        try
        {
            // If this is a local application, create a server.
            if ( config->GetProperty ( "network_remote_server" ) == "false" )
            {
                this->serverIsRemote = false;
                this->server = new WindowsServer ( config );
            }
            else
            {
                this->serverIsRemote = true;
            }
            
            // Create the client.
            this->client = new WindowsClient ( config );
        }
        catch ( WindowsException e )
        {
            throw e;
        }
    }
    
    WindowsApplication::~WindowsApplication ()
    {
        // Unregister the window class.
        UnregisterClass ( this->className.CString (), this->hInstance );
        
        // Clean up the client and the server.
        if ( this->client != null )
        {
            delete this->client;
            this->client = null;
        }
        if ( this->server != null )
        {
            delete this->server;
            this->server = null;
        }
    }
    
    void WindowsApplication::Run ()
    {
        // Start the server thread running (if
        // the server needs to be started).
        if ( !this->serverIsRemote )
        {
            this->server->Create ();
        }

        // Start the client.
        client->Start ();
        
        // Enter main program loop (update everything until the client is done).
        while ( !client->IsDone () )
        {
            client->Update ();
        }

        // We are done, so stop the client.
        client->Stop ();
        
        // Exit the server thread.
        if ( this->serverIsRemote )
        {
            this->server->Exit ();
        }
    }
    
    bool WindowsApplication::RegisterWindowClass ()
    {
        // Create and clear the window class.
        WNDCLASSEX windowClass;
        ZeroMemory ( &windowClass, sizeof ( WNDCLASSEX ) );
        
        // Size of the window class object.
        windowClass.cbSize = sizeof(WNDCLASSEX);
        
        // Redraws the window for any movement.
        windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        
        // Sets the event handling function.
        windowClass.lpfnWndProc = (WNDPROC) ( WindowsInput::EventCallback );
        
        // Sets the instance.
        windowClass.hInstance = this->hInstance;
        
        // Class background brush color.
        windowClass.hbrBackground = (HBRUSH) ( COLOR_APPWORKSPACE );
        
        // Sets the cursor.
        windowClass.hCursor = LoadCursor ( null, IDC_ARROW );
        
        // Sets the application's class name.
        windowClass.lpszClassName = this->className.CString ();
        
        // Attempt to register the class.
        if ( RegisterClassEx ( &windowClass ) == 0 )
        {
            return false;
        }
        
        return true;
    }
    
    HINSTANCE WindowsApplication::GetHInstance ()
    {
        return this->hInstance;
    }
    
    String WindowsApplication::GetClassName ()
    {
        return this->className;
    }
    
    String WindowsApplication::GetTitle ()
    {
        return this->title;
    }

}

#endif
