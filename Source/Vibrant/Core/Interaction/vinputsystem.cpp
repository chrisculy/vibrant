/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinputsystem.cpp
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

#include "vinputmodifier.h"
#include "vinputsystem.h"
#include "vsystem.h"

namespace Vibrant
{
    
    String KeyToString ( const Key& key, bool shiftIsPressed )
    {
        switch ( key )
        {
            case KEY_A:
                return ( shiftIsPressed ) ? "A" : "a";
            case KEY_B:
                return ( shiftIsPressed ) ? "B" : "b";
            case KEY_C:
                return ( shiftIsPressed ) ? "C" : "c";
            case KEY_D:
                return ( shiftIsPressed ) ? "D" : "d";
            case KEY_E:
                return ( shiftIsPressed ) ? "E" : "e";
            case KEY_F:
                return ( shiftIsPressed ) ? "F" : "f";
            case KEY_G:
                return ( shiftIsPressed ) ? "G" : "g";
            case KEY_H:
                return ( shiftIsPressed ) ? "H" : "h";
            case KEY_I:
                return ( shiftIsPressed ) ? "I" : "i";
            case KEY_J:
                return ( shiftIsPressed ) ? "J" : "j";
            case KEY_K:
                return ( shiftIsPressed ) ? "K" : "k";
            case KEY_L:
                return ( shiftIsPressed ) ? "L" : "l";
            case KEY_M:
                return ( shiftIsPressed ) ? "M" : "m";
            case KEY_N:
                return ( shiftIsPressed ) ? "N" : "n";
            case KEY_O:
                return ( shiftIsPressed ) ? "O" : "o";
            case KEY_P:
                return ( shiftIsPressed ) ? "P" : "p";
            case KEY_Q:
                return ( shiftIsPressed ) ? "Q" : "q";
            case KEY_R:
                return ( shiftIsPressed ) ? "R" : "r";
            case KEY_S:
                return ( shiftIsPressed ) ? "S" : "s";
            case KEY_T:
                return ( shiftIsPressed ) ? "T" : "t";
            case KEY_U:
                return ( shiftIsPressed ) ? "U" : "u";
            case KEY_V:
                return ( shiftIsPressed ) ? "V" : "v";
            case KEY_W:
                return ( shiftIsPressed ) ? "W" : "w";
            case KEY_X:
                return ( shiftIsPressed ) ? "X" : "x";
            case KEY_Y:
                return ( shiftIsPressed ) ? "Y" : "y";
            case KEY_Z:
                return ( shiftIsPressed ) ? "Z" : "z";
            case KEY_BACK_QUOTE:
                return "`";
            case KEY_TILDE:
                return "~";
            case KEY_1:
                return "1";
            case KEY_EXCLAMATION_MARK:
                return "!";
            case KEY_2:
                return "2";
            case KEY_AT_SYMBOL:
                return "@";
            case KEY_3:
                return "3";
            case KEY_NUMBER_SIGN:
                return "#";
            case KEY_4:
                return "4";
            case KEY_DOLLAR_SIGN:
                return "$";
            case KEY_5:
                return "5";
            case KEY_PERCENT:
                return "%";
            case KEY_6:
                return "6";
            case KEY_CARET:
                return "^";
            case KEY_7:
                return "7";
            case KEY_AMPERSAND:
                return "&";
            case KEY_8:
                return "8";
            case KEY_ASTERISK:
                return "*";
            case KEY_9:
                return "9";
            case KEY_LEFT_PARENTHESIS:
                return "(";
            case KEY_0:
                return "0";
            case KEY_RIGHT_PARENTHESIS:
                return ")";
            case KEY_SUBTRACT:
                return "-";
            case KEY_UNDERSCORE:
                return "_";
            case KEY_EQUALS:
                return "=";
            case KEY_ADD:
                return "+";
            case KEY_BACKSPACE:
                return "<backspace>";
            case KEY_TAB:
                return "<tab>";
            case KEY_LEFT_BRACKET:
                return "[";
            case KEY_LEFT_CURLY_BRACE:
                return "{";
            case KEY_RIGHT_BRACKET:
                return "]";
            case KEY_RIGHT_CURLY_BRACE:
                return "}";
            case KEY_BACKSLASH:
                return "\\";
            case KEY_PIPE:
                return "|";
            case KEY_CAPS_LOCK:
                return "<caps lock>";
            case KEY_SEMICOLON:
                return ";";
            case KEY_COLON:
                return ":";
            case KEY_SINGLE_QUOTE:
                return "\'";
            case KEY_DOUBLE_QUOTE:
                return "\"";
            case KEY_ENTER:
                return "<enter>";
            case KEY_COMMA:
                return ",";
            case KEY_LEFT_ANGLE_BRACKET:
                return "<";
            case KEY_PERIOD:
                return ".";
            case KEY_RIGHT_ANGLE_BRACKET:
                return ">";
            case KEY_FORWARD_SLASH:
                return "/";
            case KEY_QUESTION_MARK:
                return "?";
            case KEY_ESCAPE:
                return "<escape>";
            case KEY_F1:
                return "<F1>";
            case KEY_F2:
                return "<F2>";
            case KEY_F3:
                return "<F3>";
            case KEY_F4:
                return "<F4>";
            case KEY_F5:
                return "<F5>";
            case KEY_F6:
                return "<F6>";
            case KEY_F7:
                return "<F7>";
            case KEY_F8:
                return "<F8>";
            case KEY_F9:
                return "<F9>";
            case KEY_F10:
                return "<F10>";
            case KEY_F11:
                return "<F11>";
            case KEY_F12:
                return "<F12>";
            case KEY_PRINT_SCREEN:
                return "<print screen>";
            case KEY_SCROLL_LOCK:
                return "<scroll lock>";
            case KEY_PAUSE:
                return "<pause break>";
            case KEY_INSERT:
                return "<insert>";
            case KEY_HOME:
                return "<home>";
            case KEY_PAGE_UP:
                return "<page up>";
            case KEY_DELETE:
                return "<delete>";
            case KEY_END:
                return "<end>";
            case KEY_PAGE_DOWN:
                return "<page down>";
            case KEY_UP:
                return "<up>";
            case KEY_DOWN:
                return "<down>";
            case KEY_LEFT:
                return "<left>";
            case KEY_RIGHT:
                return "<right>";
            case KEY_SPACE:
                return "<space>";
            case NUM_NUM_LOCK:
                return "<numpad: num lock>";
            case NUM_DIVIDE:
                return "<numpad: />";
            case NUM_MULTIPLY:
                return "<numpad: *>";
            case NUM_SUBTRACT:
                return "<numpad: ->";
            case NUM_ADD:
                return "<numpad: +>";
            case NUM_1:
                return "<numpad: 1>";
            case NUM_2:
                return "<numpad: 2>";
            case NUM_3:
                return "<numpad: 3>";
            case NUM_4:
                return "<numpad: 4>";
            case NUM_5:
                return "<numpad: 5>";
            case NUM_6:
                return "<numpad: 6>";
            case NUM_7:
                return "<numpad: 7>";
            case NUM_8:
                return "<numpad: 8>";
            case NUM_9:
                return "<numpad: 9>";
            case NUM_0:
                return "<numpad: 0>";
            case NUM_PERIOD:
                return "<numpad: .>";
            default:
                return "Unknown key.";
        }
    }
    
#ifdef SYSTEM_WINDOWS
    Key GetKey ( const vchar character, bool shiftIsPressed )
    {
        unsigned int virtualKey = ( (unsigned int) character & 0xFF );
        switch ( virtualKey )
        {
            case 'A':
                return KEY_A;
            case 'B':
                return KEY_B;
            case 'C':
                return KEY_C;
            case 'D':
                return KEY_D;
            case 'E':
                return KEY_E;
            case 'F':
                return KEY_F;
            case 'G':
                return KEY_G;
            case 'H':
                return KEY_H;
            case 'I':
                return KEY_I;
            case 'J':
                return KEY_J;
            case 'K':
                return KEY_K;
            case 'L':
                return KEY_L;
            case 'M':
                return KEY_M;
            case 'N':
                return KEY_N;
            case 'O':
                return KEY_O;
            case 'P':
                return KEY_P;
            case 'Q':
                return KEY_Q;
            case 'R':
                return KEY_R;
            case 'S':
                return KEY_S;
            case 'T':
                return KEY_T;
            case 'U':
                return KEY_U;
            case 'V':
                return KEY_V;
            case 'W':
                return KEY_W;
            case 'X':
                return KEY_X;
            case 'Y':
                return KEY_Y;
            case 'Z':
                return KEY_Z;
                // '`' && '~'
            case VK_OEM_3:
                return ( shiftIsPressed ) ? KEY_TILDE : KEY_BACK_QUOTE;
            case '1':
                return ( shiftIsPressed ) ? KEY_EXCLAMATION_MARK : KEY_1;
            case '2':
                return ( shiftIsPressed ) ? KEY_AT_SYMBOL : KEY_2;
            case '3':
                return ( shiftIsPressed ) ? KEY_NUMBER_SIGN : KEY_3;
            case '4':
                return ( shiftIsPressed ) ? KEY_DOLLAR_SIGN : KEY_4;
            case '5':
                return ( shiftIsPressed ) ? KEY_PERCENT : KEY_5;
            case '6':
                return ( shiftIsPressed ) ? KEY_CARET : KEY_6;
            case '7':
                return ( shiftIsPressed ) ? KEY_AMPERSAND : KEY_7;
            case '8':
                return ( shiftIsPressed ) ? KEY_ASTERISK : KEY_8;
            case '9':
                return ( shiftIsPressed ) ? KEY_LEFT_PARENTHESIS : KEY_9;
            case '0':
                return ( shiftIsPressed ) ? KEY_RIGHT_PARENTHESIS : KEY_0;
                // '-' && '_'
            case VK_OEM_MINUS:
                return ( shiftIsPressed ) ? KEY_UNDERSCORE : KEY_SUBTRACT;
                // '=' && '+'
            case VK_OEM_PLUS:
                return ( shiftIsPressed ) ? KEY_ADD : KEY_EQUALS;
            case VK_BACK:
                return KEY_BACKSPACE;
            case VK_TAB:
                return KEY_TAB;
                // '[' && '{'
            case VK_OEM_4:
                return ( shiftIsPressed ) ? KEY_LEFT_CURLY_BRACE : KEY_LEFT_BRACKET;
                // ']' && '}'
            case VK_OEM_6:
                return ( shiftIsPressed ) ? KEY_RIGHT_CURLY_BRACE : KEY_RIGHT_BRACKET;
                // '\' && '|'
            case VK_OEM_5:
                return ( shiftIsPressed ) ? KEY_PIPE : KEY_BACKSLASH;
            case VK_CAPITAL:
                return KEY_CAPS_LOCK;
                // ';' && ':'
            case VK_OEM_1:
                return ( shiftIsPressed ) ? KEY_COLON : KEY_SEMICOLON;
                // ''' && '"'
            case VK_OEM_7:
                return ( shiftIsPressed ) ? KEY_DOUBLE_QUOTE : KEY_SINGLE_QUOTE;
            case VK_RETURN:
                return KEY_ENTER;
                // ',' && '<'
            case VK_OEM_COMMA:
                return ( shiftIsPressed ) ? KEY_LEFT_ANGLE_BRACKET : KEY_COMMA;
                // '.' && '>'
            case VK_OEM_PERIOD:
                return ( shiftIsPressed ) ? KEY_RIGHT_ANGLE_BRACKET : KEY_PERIOD;
                // '/' && '?'
            case VK_OEM_2:
                return ( shiftIsPressed ) ? KEY_QUESTION_MARK : KEY_FORWARD_SLASH;
            case VK_ESCAPE:
                return KEY_ESCAPE;
            case VK_F1:
                return KEY_F1;
            case VK_F2:
                return KEY_F2;
            case VK_F3:
                return KEY_F3;
            case VK_F4:
                return KEY_F4;
            case VK_F5:
                return KEY_F5;
            case VK_F6:
                return KEY_F6;
            case VK_F7:
                return KEY_F7;
            case VK_F8:
                return KEY_F8;
            case VK_F9:
                return KEY_F9;
            case VK_F10:
                return KEY_F10;
            case VK_F11:
                return KEY_F11;
            case VK_F12:
                return KEY_F12;
            case VK_SNAPSHOT:
                return KEY_PRINT_SCREEN;
            case VK_SCROLL:
                return KEY_SCROLL_LOCK;
            case VK_PAUSE:
                return KEY_PAUSE;
            case VK_INSERT:
                return KEY_INSERT;
            case VK_HOME:
                return KEY_HOME;
            case VK_PRIOR:
                return KEY_PAGE_UP;
            case VK_DELETE:
                return KEY_DELETE;
            case VK_END:
                return KEY_END;
            case VK_NEXT:
                return KEY_PAGE_DOWN;
            case VK_UP:
                return KEY_UP;
            case VK_DOWN:
                return KEY_DOWN;
            case VK_LEFT:
                return KEY_LEFT;
            case VK_RIGHT:
                return KEY_RIGHT;
            case VK_SPACE:
                return KEY_SPACE;
            case VK_NUMLOCK:
                return NUM_NUM_LOCK;
            case VK_DIVIDE:
                return NUM_DIVIDE;
            case VK_MULTIPLY:
                return NUM_MULTIPLY;
            case VK_SUBTRACT:
                return NUM_SUBTRACT;
            case VK_ADD:
                return NUM_ADD;
            case VK_NUMPAD1:
                return NUM_1;
            case VK_NUMPAD2:
                return NUM_2;
            case VK_NUMPAD3:
                return NUM_3;
            case VK_NUMPAD4:
                return NUM_4;
            case VK_NUMPAD5:
                return NUM_5;
            case VK_NUMPAD6:
                return NUM_6;
            case VK_NUMPAD7:
                return NUM_7;
            case VK_NUMPAD8:
                return NUM_8;
            case VK_NUMPAD9:
                return NUM_9;
            case VK_NUMPAD0:
                return NUM_0;
            case VK_DECIMAL:
                return NUM_PERIOD;
            default:
                return KEY_ENUM_START;
        }
    }
#else
    Key getKey ( const vchar character, bool shiftIsPressed )
    {
        return KEY_A;
    }
#endif
    
    String GetModifierKeys ( const unsigned short& modifierKeys )
    {
        String result;
        
        // Left Shift.
        if ( InputModifier::ModifiersPressed ( InputModifier::MOD_LEFT_SHIFT, modifierKeys ) )
        {
            if ( !result.IsEmpty () )
            {
                result += " ";
            }
            result += "<left shift>";
        }

        // Right Shift.
        if ( InputModifier::ModifiersPressed ( InputModifier::MOD_RIGHT_SHIFT, modifierKeys ) )
        {
            if ( !result.IsEmpty () )
            {
                result += " ";
            }
            result += "<right shift>";
        }

        // Left Ctrl.
        if ( InputModifier::ModifiersPressed ( InputModifier::MOD_LEFT_CTRL, modifierKeys ) )
        {
            if ( !result.IsEmpty () )
            {
                result += " ";
            }
            result += "<left ctrl>";
        }

        // Right Ctrl.
        if ( InputModifier::ModifiersPressed ( InputModifier::MOD_RIGHT_CTRL, modifierKeys ) )
        {
            if ( !result.IsEmpty () )
            {
                result += " ";
            }
            result += "<right ctrl>";
        }

        // Left Alt.
        if ( InputModifier::ModifiersPressed ( InputModifier::MOD_LEFT_ALT, modifierKeys ) )
        {
            if ( !result.IsEmpty () )
            {
                result += " ";
            }
            result += "<left alt>";
        }

        // Right Alt.
        if ( InputModifier::ModifiersPressed ( InputModifier::MOD_RIGHT_ALT, modifierKeys ) )
        {
            if ( !result.IsEmpty () )
            {
                result += " ";
            }
            result += "<right alt>";
        }
        
        return result;
    }

}
