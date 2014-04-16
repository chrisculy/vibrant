/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vvideo.cpp
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
#include "vconvert.h"
#include "vrenderwindow.h"
#include "vscenemanager.h"
#include "vvideo.h"

namespace Vibrant
{
    
    Video::Video ( Config* config, RenderWindow* renderWindow )
    {
        this->renderer = null;
        this->renderWindow = renderWindow;
        
        // Create the scene manager from the given render window.
        this->sceneManager = new SceneManager ( renderWindow );
        
        /** Sample implementation. **/

        //        // Load the video configuration.
        //        int width = 0;
        //        int height = 0;
        //        int bitsPerPixel = 0;
        //        StringToVal ( config->GetProperty ( "video_width" ), width );
        //        StringToVal ( config->GetProperty ( "video_height" ), height );
        //        StringToVal ( config->GetProperty ( "video_bits_per_pixel" ), bitsPerPixel );
        //        
        //        // Create the renderer and set the main render window.
        //        this->renderer = new GLRenderer ( width, height, bitsPerPixel );
        //        if ( renderWindow == null )
        //        {
        //        this->renderWindow = new RenderWindow ();
        //        }
        //        
        //        // Create the scene manager from the given render window.
        //        this->sceneManager = new SceneManager ( renderWindow );
    }
    
    Video::~Video ()
    {
        /* stub function */
    }
    
    void Video::SetIsFullscreen ( bool isFullscreen )
    {
        if ( this->isFullscreen != isFullscreen )
        {
            videoModeIsDirty = true;
            this->isFullscreen = isFullscreen;
        }
    }
    
    bool Video::IsFullscreen ()
    {
        return this->isFullscreen;
    }
    
    RenderWindow* Video::GetMainRenderWindow ()
    {
        return this->renderWindow;
    }

}
