/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: venginethread.cpp
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

#include "venginethread.h"

namespace Vibrant
{
    
    EngineThread::EngineThread ( Array< EngineSystemPtr >* engineSystems )
    {
        this->engineSystems = engineSystems;
        // If there are no engine systems to update,
        // just end the thread right away.
        if ( this->engineSystems == null )
        {
            this->SetDone ( true );
        }
    }
    
    EngineThread::~EngineThread ()
    {
        /* stub function */
    }
    
    void EngineThread::Run ()
    {
        // Make sure the thread should run at all.
        if ( this->IsDone () )
        {
            return;
        }

        // Start all the engine systems.
        for ( int i = 0; i < engineSystems->Size (); i++ )
        {
            ( *engineSystems )[ i ]->Start ();
        }

        // Run until we are done.
        while ( !this->IsDone () )
        {
            // Update the engine systems.
            for ( int i = 0; i < engineSystems->Size (); i++ )
            {
                ( *engineSystems )[ i ]->Update ();
            }
        }
        
        // Stop all the engine systems (in reverse order).
        for ( int i = engineSystems->Size () - 1; i >= 0; i-- )
        {
            ( *engineSystems )[ i ]->Stop ();
        }
    }
    
    Array< EngineSystemPtr >* EngineThread::GetEngineSystems ()
    {
        return this->engineSystems;
    }

}
