/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowscodemodule.cpp
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

#include "vstring.h"
#include "vwindowscodemodule.h"

namespace Vibrant
{
    
    WindowsCodeModule::WindowsCodeModule ( String module ) :
        CodeModule ( module )
    {
        this->moduleHandle = LoadLibrary ( module.CString () );
    }
    
    WindowsCodeModule::~WindowsCodeModule ()
    {
        FreeLibrary ( this->moduleHandle );
    }
    
    bool WindowsCodeModule::IsLoaded ()
    {
        return this->moduleHandle != null;
    }
    
    void* WindowsCodeModule::GetFunction ( String function )
    {
        return (void*) GetProcAddress ( this->moduleHandle, function.CString () );
    }

}

#endif
