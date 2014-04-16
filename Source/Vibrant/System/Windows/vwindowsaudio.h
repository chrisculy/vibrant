/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsaudio.h
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#ifndef VIBRANT_WINDOWSAUDIO_H
#define VIBRANT_WINDOWSAUDIO_H

#include "vaudio.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the audio system for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsAudio : public Audio
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration the audio
             *      system uses to construct itself.
             */
            WindowsAudio ( Config* config );

            /**
             * @brief Destructor.
             */
            ~WindowsAudio ();

            /**
             * @see WindowsThread#Run()
             */
            void Run ();
            
            //************************ General Interface ***********************//
    };

}

#endif

#endif
