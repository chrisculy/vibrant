/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinput.cpp
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

#include "vinput.h"
#include "vinputmodifier.h"
#include "vinputsystem.h"

namespace Vibrant
{
    
    Input::Input ( Config *config )
    {
        InputModifier::ClearModifiers ( this->modifierKeys );
    }
    
    Input::~Input ()
    {
        /* stub function */
    }
    
    void Input::Start ()
    {
        /* stub function */
    }
    
    bool Input::DoUpdate ()
    {
        return true;
    }
    
    bool Input::KeyIsPressed ( const Key& key )
    {
        return this->keys[ key ];
    }
    
    bool Input::MouseButtonIsPressed ( const MouseButton& mouseButton )
    {
        return this->mouseButtons[ mouseButton ];
    }
    
    unsigned short Input::GetModifierKeys ()
    {
        return this->modifierKeys;
    }
    
    void Input::AddModifiers ( unsigned short modifierKeys )
    {
        InputModifier::SetModifiers ( modifierKeys, this->modifierKeys );
    }
    
    void Input::RemoveModifiers ( unsigned short modifierKeys )
    {
        InputModifier::UnsetModifiers ( modifierKeys, this->modifierKeys );
    }
    
    bool Input::ModifiersPressed ( unsigned short modifierKeys )
    {
        return InputModifier::ModifiersPressed ( modifierKeys, this->modifierKeys );
    }

}
