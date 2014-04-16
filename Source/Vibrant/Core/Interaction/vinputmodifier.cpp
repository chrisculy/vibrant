/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vinputmodifier.cpp
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

namespace Vibrant
{
    // Initialize static members.
    const unsigned short InputModifier::MOD_LEFT_SHIFT = 0x001;
    const unsigned short InputModifier::MOD_RIGHT_SHIFT = 0x002;
    const unsigned short InputModifier::MOD_SHIFT_KEY = 0x00F;
    const unsigned short InputModifier::MOD_LEFT_CTRL = 0x010;
    const unsigned short InputModifier::MOD_RIGHT_CTRL = 0x020;
    const unsigned short InputModifier::MOD_CTRL_KEY = 0x0F0;
    const unsigned short InputModifier::MOD_LEFT_ALT = 0x100;
    const unsigned short InputModifier::MOD_RIGHT_ALT = 0x200;
    const unsigned short InputModifier::MOD_ALT_KEY = 0xF00;
}
