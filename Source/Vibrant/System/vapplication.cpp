/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vapplication.cpp
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

#include "vapplication.h"
#include "vclient.h"
#include "vconfig.h"
#include "vconvert.h"
#include "vserver.h"
#include "vsystem.h"
#include "vsystemmanager.h"

#include VIBRANT_TIME_INCLUDE_FILE

namespace Vibrant
{
    
    Application::Application ( Config* config )
    {
        // Start the system manager.
        SystemManager::Start ( config );
        
        /** Sample implementation. **/

        //        client = new WindowsClient ( config );
        //        // If this is a local application,
        //        // create a server as well.
        //        if ( config->GetProperty ( "network_remote_server" ) == "false" )
        //        {
        //            server = new WindowsServer ( config );
        //        }
    }
    
    Application::~Application ()
    {
        // Shut down the system manager.
        SystemManager::Shutdown ();
        
        /** Sample implementation. **/

        //        if ( client != null )
        //        {
        //            delete client;
        //            client = null;
        //        }
        //        if ( server != null )
        //        {
        //            delete server;
        //            server = null;
        //        }
    }
    
    void Application::Run ()
    {
        /** Sample implementation. **/

        //        // Start the client.
        //        client->Start ();
        //        
        //        // Enter main program loop (update everything until the client is done).
        //        while ( !client->IsDone () )
        //        {
        //            client->Update ();
        //        }
        //        
        //        // We are done, so stop the client.
        //        client->Stop ();
    }
    
    Client* Application::GetClient ()
    {
        return this->client;
    }
    
    Server* Application::GetServer ()
    {
        return this->server;
    }

}
