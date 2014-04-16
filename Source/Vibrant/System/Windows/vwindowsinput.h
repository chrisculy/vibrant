/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsinput.h
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

#ifndef VIBRANT_WINDOWSINPUT_H
#define VIBRANT_WINDOWSINPUT_H

#include "vinput.h"
#include "vmutex.h"

namespace Vibrant
{
    
    /**
     * @brief Implements the input system for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsInput : public Input
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration that the
             *      input system uses to construct itself.
             */
            WindowsInput ( Config* config );

            /**
             * @brief Destructor.
             */
            ~WindowsInput ();

            /**
             * @brief Starts the input system running.
             * 
             * <p>
             * Note: The video system must finish initializing
             * before the input system starts running because
             * the input system needs the application's window
             * handle that is initialized in the construction
             * of the video system.
             * </p>
             */
            void Start ();

            /**
             * @brief Retrieves the wait mutex for the video system.
             * 
             * @return The wait mutex.
             */
            Mutex* GetWaitMutex ();

            /**
             * @brief The callback function for Windows events.
             * 
             * @see Windows Documentation
             */
            static LRESULT CALLBACK EventCallback ( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam );

            /** @brief Represents the key down state. */
            static const unsigned short KEY_STATE_DOWN = 0x1000;

            /** @brief Represents a trigger key (ie. Caps Lock) in the 'ON' state. */
            static const unsigned short KEY_STATE_TRIGGER = 0x0001;

            //************************ General Interface ***********************//

        private:
            
            /**
             * @brief Updates the state inside the
             * input system for modifier keys.
             * 
             * @param leftVirtualKey The Windows virtual key code for
             *      the left version of the modifier key.
             * @param rightVirtualKey The Windows virtual key code for
             *      the right version of the modifier key.
             * @param leftInputModifier The input modifier bit value for
             *      the left version of the modifier key (ie. InputModifier::MOD_LEFT_SHIFT).
             * @param rightInputModifier The input modifier bit value for
             *      the right version of the modifier key (ie. InputModifier::MOD_RIGHTT_SHIFT).
             */
            void UpdateModifierKey ( short leftVirtualKey, short rightVirtualKey, short leftInputModifier, short rightInputModifier );

            /**
             * @brief Fires a key down event.
             * 
             * @param wParam Holds the key to fire the event for.
             * @return <code>true</code> if the event was handled;
             *      <code>false</code> otherwise.
             */
            bool FireKeyDown ( WPARAM wParam );

            /**
             * @brief Fires a key up event.
             * 
             * @param wParam Holds the key to fire the event for.
             * @return <code>true</code> if the event was handled;
             *      <code>false</code> otherwise.
             */
            bool FireKeyUp ( WPARAM wParam );

            /**
             * @brief Fires a mouse button down event.
             * 
             * @param mouseButton The mouse button to fire the event for.
             * @return <code>true</code> if the event was handled;
             *      <code>false</code> otherwise.
             */
            bool FireMouseButtonDown ( MouseButton mouseButton );

            /**
             * @brief Fires a mouse button up event.
             * 
             * @param mouseButton The mouse button to fire the event for.
             * @return <code>true</code> if the event was handled;
             *      <code>false</code> otherwise.
             */
            bool FireMouseButtonUp ( MouseButton mouseButton );

            /**
             * @brief Fires a mouse button double click event.
             * 
             * @param mouseButton The mouse button to fire the event for.
             * @return <code>true</code> if the event was handled;
             *      <code>false</code> otherwise.
             */
            bool FireMouseButtonDoubleClick ( MouseButton mouseButton );

            /** @brief Holds the mutex used to wait on the input system. */
            Mutex* waitMutex;
    };

}

#endif

#endif
