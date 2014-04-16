/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsclient.cpp
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
#include "vwindowsaudio.h"
#include "vwindowsclient.h"
#include "vwindowsinput.h"
#include "vwindowstime.h"
#include "vwindowsvideo.h"

namespace Vibrant
{
    
    WindowsClient::WindowsClient ( Config* config ) :
        Client ( config )
    {
        this->done = false;
        this->paused = false;
        this->inHighPerformanceMode = true;
    }
    
    WindowsClient::~WindowsClient ()
    {
        /* stub function */
    }
    
    bool WindowsClient::IsInHighPerformanceMode ()
    {
        return this->inHighPerformanceMode;
    }
    
    void WindowsClient::SetInHighPerformanceMode ( bool inHighPerformanceMode )
    {
        this->inHighPerformanceMode = inHighPerformanceMode;
    }
    
    void WindowsClient::Update ()
    {
        if ( this->DoUpdate () )
        {
            WindowsVideo* video = dynamic_cast< WindowsVideo* > ( (Video*) this->video );
            
            // Get the messages from the OS and dispatch them.
            MSG message;
            if ( PeekMessage ( &message, video->GetWindowHandle (), 0, 0, PM_REMOVE ) != 0 )
            {
                // Check for a quit message.
                if ( message.message == WM_QUIT )
                {
                    this->SetDone ( true );
                }
                else
                {
                    DispatchMessage ( &message );
                }
                
                // Check if we should pause the app.
                if ( false )
                {
                    this->SetPaused ( true );
                }
            }
            else if ( this->IsPaused () )
            {
                WaitMessage ();
            }

            // Update the client systems.
            for ( int i = 0; i < systems->Size (); i++ )
            {
                ( *systems )[ i ]->Update ();
            }
            
            // If we want to not hog the CPU completely, sleep for a short time.
            if ( !this->inHighPerformanceMode )
            {
                Sleep ( 1 );
            }
        }
    }

}

#endif
