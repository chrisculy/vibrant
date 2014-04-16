/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vserver.cpp
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

#include "vconvert.h"
#include "vserver.h"

namespace Vibrant
{
    
    Server::Server ( Config *config )
    {
        /* stub function */
        // Get the server port.
        StringToVal ( config->GetProperty ( "network_server_port" ), &this->port );
    }
    
    Server::~Server ()
    {
        /* stub function */
    }
    
    void Server::Start ()
    {
        /* stub function */
    }
    
    void Server::Stop ()
    {
        /* stub function */
    }
    
    void Server::Update ()
    {
        if ( this->DoUpdate () )
        {
            /*stub function*/
        }
    }
    
    void Server::Send ()
    {
        /*stub function*/
    }
    
    void Server::Receive ()
    {
        /*stub function*/
    }

}
