/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinputmodifier.h
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

#ifndef VIBRANT_INPUTMODIFIER_H
#define VIBRANT_INPUTMODIFIER_H

#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates the different input modifiers
     * (which are then OR-ed together in a short integer).
     * 
     * <p>
     * Example usage:<br>
     * <pre>
     *  // modifierKeys is usually received from an input event.
     *  
     *  // Check if any shift key is pressed.
     *  if ( InputModifier::ModifiersPressed ( InputModifier::MOD_SHIFT_KEY ) )
     *  {
     *      ...
     *  }
     *  // Check if the left control key is pressed.
     *  if ( InputModifier::ModifiersPressed ( InputModifier::MOD_LEFT_CTRL ) )
     *  {
     *      ...
     *  }
     *  
     *  // ** Inside the input system ** //
     *  
     *  // The left shift key is pressed.
     *  InputModifier::SetModifiers ( InputModifier::MOD_LEFT_SHIFT, modifierKeys );
     *  // The right ctrl is no longer pressed.
     *  InputModifier::UnsetModifiers ( InputModifier::MOD_RIGHT_CTRL, modifierKeys );
     * </pre>
     * </p>
     * 
     * @author Chris Culy
     */
    struct VAPI InputModifier
    {
        public:
            /** @brief Used to indicate the left shift key is pressed. */
            static const unsigned short MOD_LEFT_SHIFT;

            /** @brief Used to indicate the right shift key is pressed. */
            static const unsigned short MOD_RIGHT_SHIFT;

            /** @brief A mask to test if any shift keys were pressed. */
            static const unsigned short MOD_SHIFT_KEY;

            /** @brief Used to indicate the left control key is pressed. */
            static const unsigned short MOD_LEFT_CTRL;

            /** @brief Used to indicate the right control key is pressed. */
            static const unsigned short MOD_RIGHT_CTRL;

            /** @brief A mask to test if any control keys were pressed. */
            static const unsigned short MOD_CTRL_KEY;

            /** @brief Used to indicate the left alt key is pressed. */
            static const unsigned short MOD_LEFT_ALT;

            /** @brief Used to indicate the right alt key is pressed. */
            static const unsigned short MOD_RIGHT_ALT;

            /** @brief A mask to test if any alt keys were pressed. */
            static const unsigned short MOD_ALT_KEY;

            /**
             * @brief Used to test if a modifier is pressed.
             * 
             * @param testModifiers The key modifiers to test for.
             * @param modifierKeys The actual pressed modifier keys.
             * @return <code>true</code> if the given modifier key was pressed;
             *      <code>false</code> otherwise.
             */
            static inline bool ModifiersPressed ( const unsigned short& testModifiers, const unsigned short& modifierKeys )
            {
                return ( ( modifierKeys & testModifiers ) != 0 );
            }
            
            /**
             * @brief Used to set the modifiers on a short
             * integer representing the pressed modifier keys.
             * 
             * @param newModifiers The newly pressed modifier keys.
             * @param modifierKeys The pressed modifier keys.
             */
            static inline void SetModifiers ( const unsigned short& newModifiers, unsigned short& modifierKeys )
            {
                modifierKeys |= newModifiers;
            }
            
            /**
             * @brief Used to unset the modifiers on a short
             * integer representing the pressed modifier keys.
             * 
             * @param oldModifiers The old pressed modifier keys (to be removed).
             * @param modifierKeys The pressed modifier keys.
             */
            static inline void UnsetModifiers ( const unsigned short& oldModifiers, unsigned short& modifierKeys )
            {
                modifierKeys &= ~oldModifiers;
            }
            
            /**
             * @brief Used to clear the modifiers on a short
             * integer representing the pressed modifier keys.
             * 
             * @param modifierKeys The pressed modifier keys.
             */
            static inline void ClearModifiers ( unsigned short& modifierKeys )
            {
                modifierKeys = 0;
            }
    };

}

#endif
