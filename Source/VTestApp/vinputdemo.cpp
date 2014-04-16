/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinputdemo.cpp
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

#include "veventsystem.h"
#include "vinput.h"
#include "vinputdemo.h"
#include "vinputmodifier.h"
#include "vlog.h"

int VInputDemo ()
{
    // Create the input system and the input demo.
    Input* input = new Input ( null );
    InputDemo* inputDemo = new InputDemo ();
    
    // Subscribe to the input events.
    input->keyDown.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnKeyDown ) );
    input->keyUp.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnKeyUp ) );
    input->mouseButtonDown.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnMouseButtonDown ) );
    input->mouseButtonUp.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnMouseButtonUp ) );
    input->mouseButtonDoubleClick.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnMouseButtonDoubleClick ) );
    input->mouseMove.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnMouseMove ) );
    input->mouseScroll.Subscribe ( EventSystem::MakeListener ( inputDemo, &InputDemo::OnMouseScroll ) );
    
    // Start the input system.
    input->Start ();
    
    // Programmatically test the input events.
    KeyEventParam keyParam;
    MouseButtonEventParam buttonParam;
    MouseMoveEventParam moveParam;
    MouseScrollEventParam scrollParam;
    
    keyParam.key = KEY_A;
    InputModifier::SetModifiers ( InputModifier::MOD_LEFT_SHIFT, keyParam.modifierKeys );
    input->keyDown.Fire ( input, keyParam );
    input->keyUp.Fire ( input, keyParam );
    
    buttonParam.button = MOUSE_LEFT;
    input->mouseButtonDown.Fire ( input, buttonParam );
    input->mouseButtonUp.Fire ( input, buttonParam );
    
    moveParam.x = 4;
    moveParam.y = 27;
    input->mouseMove.Fire ( input, moveParam );
    
    scrollParam.y = 3;
    input->mouseScroll.Fire ( input, scrollParam );
    
    // Clean up memory.
    delete inputDemo;
    delete input;
    
    system ( "pause" );
    return 0;
}

bool InputDemo::OnKeyDown ( Input* input, KeyEventParam param )
{
    vlog << INF << "Key " << KeyToString ( param.key, InputModifier::ModifiersPressed ( InputModifier::MOD_SHIFT_KEY, param.modifierKeys ) );
    vlog << " was pressed with modifier keys: " << GetModifierKeys ( param.modifierKeys );
    vlog << "\n";
    return false;
}

bool InputDemo::OnKeyUp ( Input* input, KeyEventParam param )
{
    vlog << INF << "Key " << KeyToString ( param.key, InputModifier::ModifiersPressed ( InputModifier::MOD_SHIFT_KEY, param.modifierKeys ) );
    vlog << " was released with modifier keys: " << GetModifierKeys ( param.modifierKeys );
    vlog << "\n";
    return false;
}

bool InputDemo::OnMouseButtonDown ( Input* input, MouseButtonEventParam param )
{
    switch ( param.button )
    {
        case MOUSE_LEFT:
            vlog << INF << "Left mouse button was pressed.\n";
            return true;
        case MOUSE_MIDDLE:
            vlog << INF << "Middle mouse button was pressed.\n";
            return true;
        case MOUSE_RIGHT:
            vlog << INF << "Right mouse button was pressed.\n";
            return true;
        default:
            break;
    }
    return false;
}

bool InputDemo::OnMouseButtonUp ( Input* input, MouseButtonEventParam param )
{
    switch ( param.button )
    {
        case MOUSE_LEFT:
            vlog << INF << "Left mouse button was released.\n";
            return true;
        case MOUSE_MIDDLE:
            vlog << INF << "Middle mouse button was released.\n";
            return true;
        case MOUSE_RIGHT:
            vlog << INF << "Right mouse button was released.\n";
            return true;
        default:
            break;
    }
    return false;
}

bool InputDemo::OnMouseButtonDoubleClick ( Input* input, MouseButtonEventParam param )
{
    switch ( param.button )
    {
        case MOUSE_LEFT:
            vlog << INF << "Left mouse button was double clicked.\n";
            return true;
        case MOUSE_MIDDLE:
            vlog << INF << "Middle mouse button was double clicked.\n";
            return true;
        case MOUSE_RIGHT:
            vlog << INF << "Right mouse button was double clicked.\n";
            return true;
        default:
            break;
    }
    return false;
}

bool InputDemo::OnMouseMove ( Input* input, MouseMoveEventParam param )
{
    vlog << INF << "Mouse moved to: " << param.x << ", " << param.y << ".\n";
    return true;
}

bool InputDemo::OnMouseScroll ( Input* input, MouseScrollEventParam param )
{
    vlog << INF << "Mouse scrolled by: " << param.y << ".\n";
    return true;
}
