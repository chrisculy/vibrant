/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsinput.cpp
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

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#include "vconfig.h"
#include "vinputmodifier.h"
#include "vinputsystem.h"
#include "vlog.h"
#include "vmutex.h"
#include "vmutexlock.h"
#include "vsystemmanager.h"
#include "vwindowsaudio.h"
#include "vwindowsclient.h"
#include "vwindowsinput.h"
#include "vwindowsvideo.h"

namespace Vibrant
{
    
    LRESULT CALLBACK WindowsInput::EventCallback ( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
    {
        WindowsInput* input = (WindowsInput*) SystemManager::GetInputSystem ();
        switch ( message )
        {
            case WM_CLOSE:
            {
                // Notify the program to quit.
                PostMessage ( windowHandle, WM_QUIT, null, null );
                break;
            }
            case WM_KEYDOWN:
            {
                switch ( wParam )
                {
                    case VK_SHIFT:
                    {
                        // Update the modifier key's state.
                        input->UpdateModifierKey ( VK_LSHIFT, VK_RSHIFT, InputModifier::MOD_LEFT_SHIFT, InputModifier::MOD_RIGHT_SHIFT );
                        break;
                    }
                    case VK_CONTROL:
                    {
                        // Update the modifier key's state.
                        input->UpdateModifierKey ( VK_LCONTROL, VK_RCONTROL, InputModifier::MOD_LEFT_CTRL, InputModifier::MOD_RIGHT_CTRL );
                        break;
                    }
                    default:
                    {
                        // Fire the appropriate input event.
                        if ( input->FireKeyDown ( wParam ) )
                        {
                            return 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // Check if we are done.
                if ( wParam == VK_ESCAPE )
                {
                    // Notify the program to quit.
                    PostMessage ( windowHandle, WM_QUIT, null, null );
                }
                break;
            }
            case WM_KEYUP:
            {
                switch ( wParam )
                {
                    case VK_SHIFT:
                    {
                        // Update the modifier key's state.
                        input->UpdateModifierKey ( VK_LSHIFT, VK_RSHIFT, InputModifier::MOD_LEFT_SHIFT, InputModifier::MOD_RIGHT_SHIFT );
                        break;
                    }
                    case VK_CONTROL:
                    {
                        // Update the modifier key's state.
                        input->UpdateModifierKey ( VK_LCONTROL, VK_RCONTROL, InputModifier::MOD_LEFT_CTRL, InputModifier::MOD_RIGHT_CTRL );
                        break;
                    }
                    default:
                    {
                        // Fire the appropriate input event.
                        if ( input->FireKeyUp ( wParam ) )
                        {
                            return 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                break;
            }
            case WM_SYSKEYDOWN:
            {
                switch ( wParam )
                {
                    case VK_MENU:
                    {
                        // Update the modifier key's state.
                        input->UpdateModifierKey ( VK_LMENU, VK_RMENU, InputModifier::MOD_LEFT_ALT, InputModifier::MOD_RIGHT_ALT );
                        break;
                    }
                    case VK_F10:
                    case VK_F12:
                    {
                        // Fire the appropriate input event.
                        if ( input->FireKeyDown ( wParam ) )
                        {
                            return 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                    default:
                        break;
                }
                break;
            }
            case WM_SYSKEYUP:
            {
                switch ( wParam )
                {
                    case VK_MENU:
                    {
                        // Update the modifier key's state.
                        input->UpdateModifierKey ( VK_LMENU, VK_RMENU, InputModifier::MOD_LEFT_ALT, InputModifier::MOD_RIGHT_ALT );
                        break;
                    }
                    case VK_F10:
                    case VK_F12:
                    {
                        // Fire the appropriate input event.
                        if ( input->FireKeyUp ( wParam ) )
                        {
                            return 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                    default:
                        break;
                }
                break;
            }
            case WM_LBUTTONDOWN:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonDown ( MOUSE_LEFT ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_LBUTTONUP:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonUp ( MOUSE_LEFT ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_LBUTTONDBLCLK:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonDoubleClick ( MOUSE_LEFT ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_RBUTTONDOWN:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonDown ( MOUSE_RIGHT ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_RBUTTONUP:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonUp ( MOUSE_RIGHT ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_RBUTTONDBLCLK:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonDoubleClick ( MOUSE_RIGHT ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_MBUTTONDOWN:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonDown ( MOUSE_MIDDLE ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_MBUTTONUP:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonUp ( MOUSE_MIDDLE ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_MBUTTONDBLCLK:
            {
                // Fire the appropriate input event.
                if ( input->FireMouseButtonDoubleClick ( MOUSE_MIDDLE ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_MOUSEMOVE:
            {
                // Fire the appropriate input event.
                MouseMoveEventParam param;
                param.x = GET_X_LPARAM ( lParam );
                param.y = GET_Y_LPARAM ( lParam );
                param.modifierKeys = input->GetModifierKeys ();
                
                if ( input->mouseMove.Fire ( input, param ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            case WM_MOUSEWHEEL:
            {
                // Fire the appropriate input event.
                MouseScrollEventParam param;
                param.y = GET_WHEEL_DELTA_WPARAM ( wParam );
                param.modifierKeys = input->GetModifierKeys ();
                
                if ( input->mouseScroll.Fire ( input, param ) )
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
            default:
                break;
        }
        
        // Pass unhandled messages on to the default handler.
        return DefWindowProc ( windowHandle, message, wParam, lParam );
    }
    
    WindowsInput::WindowsInput ( Config* config ) :
        Input ( config )
    {
        this->waitMutex = Mutex::GetNewMutex ();
    }
    
    WindowsInput::~WindowsInput ()
    {
        delete this->waitMutex;
    }
    
    void WindowsInput::Start ()
    {
        // If the video system is running in a
        // separate thread, perform window creation
        // and video initialization in the proper order.
        WindowsVideo* video = (WindowsVideo*) SystemManager::GetVideoSystem ();
        if ( video->IsInSeparateThread () )
        {
            // Lock the input system's wait mutex.
            LockMutex ( this->waitMutex );
            
            // Wait until the video system is ready.
            video->GetWaitMutex ()->Wait ();
            
            // Show the window.
            ShowWindow ( video->GetWindowHandle (), SW_NORMAL );
            
            // Now notify the video system that the window is
            // shown so that it can start updating the screen;
            // we do this by unlocking the wait mutex (done
            // automatically at the end of the code block).
        }
        else
        {
            // Show the window.
            ShowWindow ( video->GetWindowHandle (), SW_NORMAL );
        }
    }
    
    Mutex* WindowsInput::GetWaitMutex ()
    {
        return this->waitMutex;
    }
    
    void WindowsInput::UpdateModifierKey ( short leftVirtualKey, short rightVirtualKey, short leftInputModifier, short rightInputModifier )
    {
        // Get the state of the left and right modifier keys.
        short leftKeyState = GetKeyState ( leftVirtualKey );
        short rightKeyState = GetKeyState ( rightVirtualKey );
        
        // Update the state within the input system.
        if ( ( leftKeyState & KEY_STATE_DOWN ) != 0 )
        {
            this->AddModifiers ( leftInputModifier );
        }
        else
        {
            this->RemoveModifiers ( leftInputModifier );
        }
        
        if ( ( rightKeyState & KEY_STATE_DOWN ) != 0 )
        {
            this->AddModifiers ( rightInputModifier );
        }
        else
        {
            this->RemoveModifiers ( rightInputModifier );
        }
    }
    
    bool WindowsInput::FireKeyDown ( WPARAM wParam )
    {
        // Build the event parameter data.
        KeyEventParam param;
        param.key = GetKey ( wParam, this->ModifiersPressed ( InputModifier::MOD_SHIFT_KEY ) );
        param.modifierKeys = this->GetModifierKeys ();
        
        // Fire the event.
        return this->keyDown.Fire ( this, param );
    }
    
    bool WindowsInput::FireKeyUp ( WPARAM wParam )
    {
        // Build the event parameter data.
        KeyEventParam param;
        param.key = GetKey ( wParam, this->ModifiersPressed ( InputModifier::MOD_SHIFT_KEY ) );
        param.modifierKeys = this->GetModifierKeys ();
        
        // Fire the event.
        return this->keyUp.Fire ( this, param );
    }
    
    bool WindowsInput::FireMouseButtonDown ( MouseButton mouseButton )
    {
        // Build the event parameter data.
        MouseButtonEventParam param;
        param.button = mouseButton;
        param.modifierKeys = this->GetModifierKeys ();
        
        // Fire the event.
        return this->mouseButtonDown.Fire ( this, param );
    }
    
    bool WindowsInput::FireMouseButtonUp ( MouseButton mouseButton )
    {
        // Build the event parameter data.
        MouseButtonEventParam param;
        param.button = mouseButton;
        param.modifierKeys = this->GetModifierKeys ();
        
        // Fire the event.
        return this->mouseButtonUp.Fire ( this, param );
    }
    
    bool WindowsInput::FireMouseButtonDoubleClick ( MouseButton mouseButton )
    {
        // Build the event parameter data.
        MouseButtonEventParam param;
        param.button = mouseButton;
        param.modifierKeys = this->GetModifierKeys ();
        
        // Fire the event.
        return this->mouseButtonDoubleClick.Fire ( this, param );
    }

}

#endif
