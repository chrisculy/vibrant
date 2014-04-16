/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vsystemmanager.h
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

#ifndef VIBRANT_SYSTEMMANAGER_H
#define VIBRANT_SYSTEMMANAGER_H

#include "vaudio.h"
#include "vcodemodule.h"
#include "vconfig.h"
#include "vinput.h"
#include "vsystem.h"
#include "vtime.h"
#include "vvideo.h"

namespace Vibrant
{
    /**
     * @brief Manages the global systems for the Vibrant engine.
     * 
     * @see Audio
     * @see Input
     * @see Time
     * @see Video
     */
    class VAPI SystemManager
    {
        public:
            
            /**
             * @brief Starts the system manager.
             * 
             * Note: This function must be called before the system manager is used.
             * 
             * @param config The engine configuration.
             */
            static void Start ( Config* config );

            /**
             * @brief Shuts down the system manager.
             * 
             * Note: This function must be called when the system manager is done being used.
             */
            static void Shutdown ();
            
            /**
             * @brief Retrieves the system's configuration.
             * 
             * @return The system configuration.
             */
            static Config* SystemManager::GetSystemConfig ();

            /**
             * @brief Retrieves the engine's audio system.
             * 
             * @return The audio system.
             */
            static Audio* GetAudioSystem ();

            /**
             * @brief Retrieves the engine's input system.
             * 
             * @return The input system.
             */
            static Input* GetInputSystem ();

            /**
             * @brief Retrieves the engine's time system.
             * 
             * @return The time system.
             */
            static Time* GetTimeSystem ();

            /**
             * @brief Retrieves the engine's video system.
             * 
             * @return The video system.
             * @throws NullPointerException If the video system fails to load.
             */
            static Video* GetVideoSystem ();

        private:
            
            /**
             * @brief Constructor made private to disallow creation.
             */
            SystemManager ();

            /** @brief Holds whether the system manager is initialized or not. */
            static bool initialized;

            /** @brief Holds the engine configuration (used to construct the engine systems). */
            static Config* config;

            /** @brief Holds the audio system. */
            static AudioPtr audio;

            /** @brief Holds the input system. */
            static InputPtr input;

            /** @brief Holds the time system. */
            static Time* time;

            /** @brief Holds the video system. */
            static VideoPtr video;

            /** @brief Holds the code module that the video system dynamically loads from. */
            static CodeModule* videoModule;
    };
}

#endif
