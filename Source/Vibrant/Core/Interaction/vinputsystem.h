/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinputsystem.h
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

#ifndef VIBRANT_INPUTSYSTEM_H
#define VIBRANT_INPUTSYSTEM_H

#include "vinputmodifier.h"
#include "vstring.h"

namespace Vibrant
{
    /**
     * @brief Encapsulates the keys
     * on the keyboard.
     * 
     * @author Chris Culy
     */
    enum Key
    {
        KEY_ENUM_START = 0,
        KEY_A = KEY_ENUM_START,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_BACK_QUOTE,
        KEY_TILDE,
        KEY_1,
        KEY_EXCLAMATION_MARK,
        KEY_2,
        KEY_AT_SYMBOL,
        KEY_3,
        KEY_NUMBER_SIGN,
        KEY_4,
        KEY_DOLLAR_SIGN,
        KEY_5,
        KEY_PERCENT,
        KEY_6,
        KEY_CARET,
        KEY_7,
        KEY_AMPERSAND,
        KEY_8,
        KEY_ASTERISK,
        KEY_9,
        KEY_LEFT_PARENTHESIS,
        KEY_0,
        KEY_RIGHT_PARENTHESIS,
        KEY_SUBTRACT,
        KEY_UNDERSCORE,
        KEY_EQUALS,
        KEY_ADD,
        KEY_BACKSPACE,
        KEY_TAB,
        KEY_LEFT_BRACKET,
        KEY_LEFT_CURLY_BRACE,
        KEY_RIGHT_BRACKET,
        KEY_RIGHT_CURLY_BRACE,
        KEY_BACKSLASH,
        KEY_PIPE,
        KEY_CAPS_LOCK,
        KEY_SEMICOLON,
        KEY_COLON,
        KEY_SINGLE_QUOTE,
        KEY_DOUBLE_QUOTE,
        KEY_ENTER,
        KEY_COMMA,
        KEY_LEFT_ANGLE_BRACKET,
        KEY_PERIOD,
        KEY_RIGHT_ANGLE_BRACKET,
        KEY_FORWARD_SLASH,
        KEY_QUESTION_MARK,
        KEY_ESCAPE,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        KEY_PRINT_SCREEN,
        KEY_SCROLL_LOCK,
        KEY_PAUSE,
        KEY_INSERT,
        KEY_HOME,
        KEY_PAGE_UP,
        KEY_DELETE,
        KEY_END,
        KEY_PAGE_DOWN,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_SPACE,
        NUM_NUM_LOCK,
        NUM_DIVIDE,
        NUM_MULTIPLY,
        NUM_SUBTRACT,
        NUM_ADD,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        NUM_0,
        NUM_PERIOD,
        KEY_ENUM_END = NUM_PERIOD
    };
    
    /**
     * @brief Encapsulates the different mouse buttons.
     * 
     * @author Chris Culy
     */
    enum MouseButton
    {
        MOUSE_BUTTON_ENUM_START = 0,
        MOUSE_LEFT = MOUSE_BUTTON_ENUM_START,
        MOUSE_MIDDLE,
        MOUSE_RIGHT,
        MOUSE_BUTTON_ENUM_END = MOUSE_RIGHT
    };
    
    /**
     * @brief Encapsulates the parameter data for key events.
     * 
     * @author Chris Culy
     */
    struct VAPI KeyEventParam
    {
            KeyEventParam ()
            {
                this->key = KEY_ENUM_START;
                InputModifier::ClearModifiers ( this->modifierKeys );
            }
            
            Key key;
            unsigned short modifierKeys;
    };
    
    /**
     * @brief Encapsulates the parameter data for mouse button events.
     * 
     * @author Chris Culy
     */
    struct VAPI MouseButtonEventParam
    {
            MouseButtonEventParam ()
            {
                this->button = MOUSE_BUTTON_ENUM_START;
                InputModifier::ClearModifiers ( this->modifierKeys );
            }
            
            MouseButton button;
            unsigned short modifierKeys;
    };
    
    /**
     * @brief Encapsulates the parameter data for mouse move events.
     * 
     * @author Chris Culy
     */
    struct VAPI MouseMoveEventParam
    {
            MouseMoveEventParam ()
            {
                this->x = 0;
                this->y = 0;
                InputModifier::ClearModifiers ( this->modifierKeys );
            }
            
            int x;
            int y;
            unsigned short modifierKeys;
    };
    
    /**
     * @brief Encapsulates the parameter data for mouse scroll events.
     * 
     * @author Chris Culy
     */
    struct VAPI MouseScrollEventParam
    {
            MouseScrollEventParam ()
            {
                this->y = 0;
                InputModifier::ClearModifiers ( this->modifierKeys );
            }
            
            unsigned short y;
            unsigned short modifierKeys;
    };
    
    /**
     * @brief Retrieves the human readable (and printable) string that
     * corresponds to the given key with the given modifier keys pressed.
     * 
     * @param key The key.
     * @param shiftIsPressed Whether or not shift is pressed.
     * @return The corresponding string.
     */
    VAPI String KeyToString ( const Key& key, bool shiftIsPressed );
    
    /**
     * @brief Retrieves the key that corresponds to the given character.
     * 
     * @param character The character.
     * @param shiftIsPressed Whether or not shift is pressed.
     * @return The corresponding key.
     */
    VAPI Key GetKey ( const vchar character, bool shiftIsPressed );
    
    /**
     * @brief Retrieves a human readable string of all the pressed modifier keys.
     * 
     * @param modifierKeys The pressed modifier keys.
     */
    VAPI String GetModifierKeys ( const unsigned short& modifierKeys );
}

#endif
