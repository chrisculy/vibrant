/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vclient.cpp
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

#include "varray.h"
#include "vaudio.h"
#include "vclient.h"
#include "vconfig.h"
#include "vconvert.h"
#include "venginethread.h"
#include "vexception.h"
#include "vinput.h"
#include "vlog.h"
#include "vrenderwindow.h"
#include "vstring.h"
#include "vsystem.h"
#include "vsystemmanager.h"
#include "vtime.h"
#include "vupdatable.h"
#include "vvideo.h"

namespace Vibrant
{
    
    Client::Client ( Config* config )
    {
        // Get a reference to the main client-side systems (this ensures all of these systems are initialized).
        this->audio = SystemManager::GetAudioSystem ();
        this->input = SystemManager::GetInputSystem ();
        this->time = SystemManager::GetTimeSystem ();
        
        try
        {
            this->video = SystemManager::GetVideoSystem ();
        }
        catch ( NullPointerException e )
        {
#if DEBUG
            vlog << ERR << "Could not load the video system from the dynamic shared library.\n";
#endif
            // TODO: Document this exception.
            throw e;
        }

        // Set up the various client systems for updates.
        int threadCount = 1;
        StringToVal ( config->GetProperty ( "network_client_num_threads" ), &threadCount );
        if ( threadCount < 1 )
        {
            // TODO: Document this exception.
            throw IllegalArgumentException ( "Client::Client - Cannot run in less than one thread." );
        }
        Array< Array< EngineSystem* > > threadedSystems ( threadCount );
        this->threads = new Array< EngineThread* > ( threadCount - 1 );
        
        // Add the client's systems to the proper array.
        // The below variable is used as the thread
        // number for each system.
        int threadNumber = 1;
        
        // Audio.
        StringToVal ( config->GetProperty ( "audio_thread" ), &threadNumber );
        if ( threadNumber > threadCount )
        {
            // TODO: Document this exception.
            throw IllegalArgumentException ( "Client::Client - The audio system's thread number is too large." );
        }
        threadedSystems[ threadNumber - 1 ].Push ( this->audio );
        
        // Video. (Note: I am adding the video before the input specifically
        // because it has to be this way to work in Windows-this may need
        // to be changed later on for other operating systems/reasons).
        StringToVal ( config->GetProperty ( "video_thread" ), &threadNumber );
        if ( threadNumber > threadCount )
        {
            // TODO: Document this exception.
            throw IllegalArgumentException ( "Client::Client - The video system's thread number is too large." );
        }
        threadedSystems[ threadNumber - 1 ].Push ( this->video );
        
        // Input.
        StringToVal ( config->GetProperty ( "input_thread" ), &threadNumber );
        if ( threadNumber > threadCount )
        {
            // TODO: Document this exception.
            throw IllegalArgumentException ( "Client::Client - The input system's thread number is too large." );
        }
        threadedSystems[ threadNumber - 1 ].Push ( this->input );
        
        // Go through the threads and set them up.
        int size = 0;
        EngineSystemPtr* engineSystems = null;
        for ( int i = 0; i < threadCount; i++ )
        {
            size = threadedSystems[ i ].Size ();
            if ( size > 0 )
            {
                // Copy all the updatables into a normal array.
                engineSystems = new EngineSystemPtr[ size ];
                for ( int j = 0; j < size; j++ )
                {
                    engineSystems[ j ] = threadedSystems[ i ][ j ];
                }
                
                // Create all the separate threads with their given systems to update.
                if ( i > 0 )
                {
                    ( *this->threads )[ i - 1 ] = new EngineThread ( new Array< EngineSystemPtr > ( size, engineSystems ) );
                }
                // Create the array of systems the main thread should update.
                else
                {
                    this->systems = new Array< EngineSystemPtr > ( size, engineSystems );
                }
            }
        }

        // Set the frequency on each system.
        int systemFrequency = -1;
        StringToVal ( config->GetProperty ( "network_client_frequency" ), &systemFrequency );
        this->SetFrequency ( systemFrequency );
        StringToVal ( config->GetProperty ( "audio_frequency" ), &systemFrequency );
        this->audio->SetFrequency ( systemFrequency );
        StringToVal ( config->GetProperty ( "input_frequency" ), &systemFrequency );
        this->input->SetFrequency ( systemFrequency );
        StringToVal ( config->GetProperty ( "video_frequency" ), &systemFrequency );
        this->video->SetFrequency ( systemFrequency );
    }
    
    Client::~Client ()
    {
        // Clean up the main thread systems.
        delete this->systems;
        this->systems = null;
        
        // Clean up the client threads.
        for ( int i = 0; i < this->threads->Size (); i++ )
        {
            // For each thread, delete the thread's engine systems.
            delete ( *this->threads )[ 0 ]->GetEngineSystems ();
        }
        delete this->threads;
        this->threads = null;
        
        // Set smart pointers to null to release the reference.
        this->audio = null;
        this->input = null;
        this->video = null;
        
        // Ensure we don't get a dangling pointer.
        this->time = null;
    }
    
    void Client::Start ()
    {
        // Create the client's threads.
        for ( int i = 0; i < this->threads->Size (); i++ )
        {
            ( *this->threads )[ i ]->Create ();
        }
        
        // Start the main thread systems.
        for ( int i = 0; i < this->systems->Size (); i++ )
        {
            ( *this->systems )[ i ]->Start ();
        }
    }
    
    void Client::Stop ()
    {
        // Stop the main thread systems.
        for ( int i = 0; i < this->systems->Size (); i++ )
        {
            ( *this->systems )[ i ]->Stop ();
        }
        
        // Exit all the client threads.
        for ( int i = 0; i < this->threads->Size (); i++ )
        {
            ( *this->threads )[ i ]->Exit ();
        }
    }
    
    void Client::Update ()
    {
        /* stub function */
    }
    
    void Client::Connect ( String server )
    {
        /*stub function*/
    }
    
    void Client::Send ()
    {
        /*stub function*/
    }
    
    void Client::Receive ()
    {
        /*stub function*/
    }
    
    bool Client::IsPaused ()
    {
        return this->paused;
    }
    
    void Client::SetPaused ( bool paused )
    {
        this->paused = paused;
    }
    
    bool Client::IsDone ()
    {
        return this->done;
    }
    
    void Client::SetDone ( bool done )
    {
        this->done = done;
    }

}
