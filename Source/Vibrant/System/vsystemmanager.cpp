/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsystemmanager.cpp
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

#include "vaudio.h"
#include "vcodemodule.h"
#include "vconfig.h"
#include "vinput.h"
#include "vlog.h"
#include "vrenderwindow.h"
#include "vsystem.h"
#include "vsystemmanager.h"
#include "vtime.h"
#include "vvideo.h"

// Include system dependent files.
#include VIBRANT_AUDIO_INCLUDE_FILE
#include VIBRANT_CODEMODULE_INCLUDE_FILE
#include VIBRANT_INPUT_INCLUDE_FILE
#include VIBRANT_TIME_INCLUDE_FILE

namespace Vibrant
{
    // Set initial uninitialized values.
    bool SystemManager::initialized = false;
    Config* SystemManager::config = null;
    AudioPtr SystemManager::audio = null;
    InputPtr SystemManager::input = null;
    Time* SystemManager::time = null;
    VideoPtr SystemManager::video = null;
    CodeModule* SystemManager::videoModule = null;
    
    void SystemManager::Start ( Config* config )
    {
        SystemManager::initialized = true;
        SystemManager::config = config;
    }
    
    void SystemManager::Shutdown ()
    {
        if ( SystemManager::initialized )
        {
            // Clean up all the active systems.
            // (Set smart pointers to null).
            if ( SystemManager::audio != null )
            {
                SystemManager::audio = null;
            }
            if ( SystemManager::input != null )
            {
                SystemManager::input = null;
            }
            if ( SystemManager::time != null )
            {
                delete SystemManager::time;
                SystemManager::time = null;
            }
            if ( SystemManager::video != null )
            {
                SystemManager::video = null;
            }
            if ( SystemManager::videoModule != null )
            {
                delete SystemManager::videoModule;
                SystemManager::videoModule = null;
            }
        }
    }
    
    Config* SystemManager::GetSystemConfig ()
    {
#if defined (DEBUG)
        if ( !SystemManager::initialized )
        {
            vlog << WARN << "SystemManager::GetSystemConfig - The system manager has not been initialized.";
            return;
        }
#endif
        
        return SystemManager::config;
    }
    
    Audio* SystemManager::GetAudioSystem ()
    {
#if defined (DEBUG)
        if ( !SystemManager::initialized )
        {
            vlog << WARN << "SystemManager::GetAudioSystem - The system manager has not been initialized.";
            return;
        }
#endif
        
        if ( SystemManager::audio == null )
        {
            SystemManager::audio = new VIBRANT_AUDIO ( SystemManager::config );
        }
        return SystemManager::audio;
    }
    
    Input* SystemManager::GetInputSystem ()
    {
#if defined (DEBUG)
        if ( !SystemManager::initialized )
        {
            vlog << WARN << "SystemManager::GetAudioSystem - The system manager has not been initialized.";
            return;
        }
#endif
        
        if ( SystemManager::input == null )
        {
            SystemManager::input = new VIBRANT_INPUT ( SystemManager::config );
        }
        return SystemManager::input;
    }
    
    Time* SystemManager::GetTimeSystem ()
    {
#if defined (DEBUG)
        if ( !SystemManager::initialized )
        {
            vlog << WARN << "SystemManager::GetAudioSystem - The system manager has not been initialized.";
            return;
        }
#endif
        
        if ( SystemManager::time == null )
        {
            SystemManager::time = new VIBRANT_TIME ( SystemManager::config );
        }
        return SystemManager::time;
    }
    
    Video* SystemManager::GetVideoSystem ()
    {
#if defined (DEBUG)
        if ( !SystemManager::initialized )
        {
            vlog << WARN << "SystemManager::GetAudioSystem - The system manager has not been initialized.";
            return;
        }
#endif
        
        if ( SystemManager::video == null )
        {
            // Load the appropriate video system implementation.
            SystemManager::videoModule = new VIBRANT_CODEMODULE ( "VOpenGL" );
            
            if ( videoModule->IsLoaded () )
            {
                GetVideoSystemFunction GetVideoSystem = (GetVideoSystemFunction) videoModule->GetFunction ( "GetVideoSystem" );
                if ( GetVideoSystem != null )
                {
                    SystemManager::video = GetVideoSystem ( config, new RenderWindow ( 0, 0, 800, 600 ) );
                    if ( SystemManager::video != null )
                    {
                        return SystemManager::video;
                    }
                }
            }
            
            // Notify the engine that the video system could not be loaded.
            throw NullPointerException ( "SystemManager::GetVideoSystem - Failed to dynamically load the video system." );
        }
        return SystemManager::video;
    }

}
