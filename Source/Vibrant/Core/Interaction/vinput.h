/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinput.h
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

#ifndef VIBRANT_INPUT_H
#define VIBRANT_INPUT_H

#include "varray.h"
#include "vconfig.h"
#include "venginesystem.h"
#include "vevent.h"
#include "vinputsystem.h"
#include "vobject.h"
#include "vpointer.h"
#include "vstack.h"
#include "vsystem.h"
#include "vtimedupdater.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the input system.
     * 
     * @author Chris Culy
     * @see Config
     * @see EngineSystem
     * @see TimedUpdater
     */
    class VAPI Input : public EngineSystem, public TimedUpdater
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             * 
             * @param config The configuration to construct
             *      the input system from.
             */
            Input ( Config* config );

            /**
             * @brief Destructor.
             */
            virtual ~Input ();

            /**
             * @brief Starts the input system running.
             * 
             * <p>
             * Note: This is typically a late initialization that
             * does any still-needed initialization so that the input
             * system receives events from the operating system.
             * </p>
             * 
             * @see Updatable#Start()
             */
            virtual void Start ();

            /**
             * @brief The input system always runs as fast as possible,
             * so this function is overridden to always return true.
             * 
             * @return <code>true</code>.
             */
            virtual bool DoUpdate ();

            /**
             * @brief Retrieves whether the given key is pressed.
             * 
             * @param key The key to test.
             * @return <code>true</code> if the given key is
             *      pressed;<code>false</code> otherwise.
             */
            virtual bool KeyIsPressed ( const Key& key );

            /**
             * @brief Retrieves whether the given mouse button is pressed.
             * 
             * @param mouseButton The mouse button to test.
             * @return <code>true</code> if the given mouse button is
             *      pressed;<code>false</code> otherwise.
             */
            virtual bool MouseButtonIsPressed ( const MouseButton& mouseButton );

            /**
             * @brief Retrieves the modifier keys' state (a short integer
             * which holds which modifier keys are pressed).
             * 
             * @return The state of the modifier keys.
             */
            virtual unsigned short GetModifierKeys ();

            /**
             * @brief Adds the given modifier keys (when the keys are pressed).
             * 
             * @param modifierKeys The modifier keys to add.
             */
            virtual void AddModifiers ( unsigned short modifierKeys );

            /**
             * @brief Removes the given modifier keys (when the keys are released).
             * 
             * @param modifierKeys The modifier keys to remove.
             */
            virtual void RemoveModifiers ( unsigned short modifierKeys );

            /**
             * @brief Retrieves whether the given modifier keys are pressed.
             * 
             * @return <code>true</code> if the given modifier keys are
             *      pressed;<code>false</code> otherwise.
             */
            virtual bool ModifiersPressed ( unsigned short modifierKeys );

            //************************ General Interface ***********************//
            

            //****************************** Events ****************************//

            /** @brief The event that is fired when a key is pressed. */
            Event< Input, KeyEventParam > keyDown;

            /** @brief The event that is fired when a key is released. */
            Event< Input, KeyEventParam > keyUp;

            /** @brief The event that is fired when a mouse button is pressed. */
            Event< Input, MouseButtonEventParam > mouseButtonDown;

            /** @brief The event that is fired when a mouse button is released. */
            Event< Input, MouseButtonEventParam > mouseButtonUp;

            /** @brief The event that is fired when a mouse button is double clicked. */
            Event< Input, MouseButtonEventParam > mouseButtonDoubleClick;

            /** @brief The event that is fired when the mouse is moved. */
            Event< Input, MouseMoveEventParam > mouseMove;

            /** @brief The event that is fired when the mouse scroll wheel is moved. */
            Event< Input, MouseScrollEventParam > mouseScroll;

            //****************************** Events ****************************//

        protected:
            
            /** @brief Holds the state of the keys on the keyboard. */
            bool keys[ KEY_ENUM_END ];

            /** @brief Holds the state of the mouse buttons. */
            bool mouseButtons[ MOUSE_BUTTON_ENUM_END ];

            /** @brief Holds the state the modifier keys. */
            unsigned short modifierKeys;
    };
    
    typedef Pointer< Input > InputPtr;

}

#endif
