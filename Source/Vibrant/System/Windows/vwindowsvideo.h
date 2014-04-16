/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsvideo.h
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

#ifndef VIBRANT_WINDOWSVIDEO_H
#define VIBRANT_WINDOWSVIDEO_H

#include "vconfig.h"
#include "vmutex.h"
#include "vrenderwindow.h"
#include "vstring.h"
#include "vvideo.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the video system for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsVideo : public Video
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            WindowsVideo ( Config* config, RenderWindow* renderWindow = null );

            /**
             * @brief Destructor.
             */
            virtual ~WindowsVideo ();

            /**
             * @brief Starts the video system (essentially does all
             * late initialization like initialization of
             * the renderer and the render context).
             * 
             * @see Video#Start ()
             */
            virtual void Start ();

            /**
             * @see Video#Update()
             */
            virtual void Update ();

            /**
             * @see Video#GoFullscreen()
             */
            virtual bool GoFullscreen ( int width, int height, int bpp );

            /**
             * @brief Gets whether the video system is running
             * in a separate thread (from the input system) or not.
             * 
             * @returns Whether the video system is running
             *      in a separate thread or not.
             */
            bool IsInSeparateThread ();

            /**
             * @brief Retrieves the window handle.
             * 
             * @return The window handle.
             */
            HWND GetWindowHandle ();

            /**
             * @brief Retrieves the wait mutex for the video system.
             * 
             * @return The wait mutex.
             */
            Mutex* GetWaitMutex ();

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @brief Helper function that does all
             * late initialization of the video system.
             * 
             * @see WindowsVideo#Start ()
             */
            virtual void StartVideo () = 0;

            //************************ General Interface ***********************//

        protected:
            
            /** @brief Holds the mutex used to wait on the video system. */
            Mutex* waitMutex;

            /** @brief Holds the pixel format descriptor. */
            PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

            /** @brief Holds the window style. */
            DWORD windowStyle;

            /** @brief Holds the extended window style. */
            DWORD windowExtendedStyle;

            /** @brief The application's window handle. */
            HWND windowHandle;

            /** @brief The application's device context. */
            HDC deviceContext;

            /** @brief The application's render context. */
            HGLRC renderContext;

            /** @brief The application's width. */
            int width;

            /** @brief The application's height. */
            int height;

            /** @brief The application's bit depth. */
            int bpp;

            /** @brief Whether the video system is running in a
             * separate thread from the input thread. */
            bool inSeparateThread;
    };

}

#endif

#endif
