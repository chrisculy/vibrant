/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vibrantconfig.cpp
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

#include "vconfig.h"

using namespace Vibrant;

int main ( int argc, char** argv )
{
    Config* config = new Config ();
    config->SetProperty ( "video_is_fullscreen", "false" );
    config->SetProperty ( "video_renderer_type", "OpenGL" );
    config->SetProperty ( "application_title", "Vibrant (Windows OpenGL)" );
    config->SetProperty ( "network_server_port", "1022" );
    config->SetProperty ( "network_remote_server", "false" );
    config->SetProperty ( "video_width", "800" );
    config->SetProperty ( "video_height", "600" );
    config->SetProperty ( "video_bits_per_pixel", "32" );
    config->SetProperty ( "video_flags", "3" );
    
    config->SetProperty ( "network_client_num_threads", "1" );
    config->SetProperty ( "video_thread", "1" );
    config->SetProperty ( "audio_thread", "1" );
    config->SetProperty ( "input_thread", "1" );
    
    config->SetProperty ( "network_client_frequency", "-1" );
    config->SetProperty ( "video_frequency", "70" );
    config->SetProperty ( "audio_frequency", "10" );
    config->SetProperty ( "input_frequency", "-1" );
    
    config->SetProperty ( "network_server_thread", "2" );
    config->SetProperty ( "network_server_num_threads", "1" );
    config->SetProperty ( "ai_thread", "2" );
    config->SetProperty ( "physics_thread", "2" );
    
    config->SetProperty ( "network_server_frequency", "-1" );
    config->SetProperty ( "ai_frequency", "-1" );
    config->SetProperty ( "physics_frequency", "-1" );
    
    config->Save ();
    //config->Print ();
    //config->Load ();
    //config->Print ();

    delete config;
    
    system ( "pause" );
    return 0;
}
