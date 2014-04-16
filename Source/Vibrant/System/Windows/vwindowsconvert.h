/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsconvert.h
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

#ifndef VIBRANT_WINDOWSCONVERT_H
#define VIBRANT_WINDOWSCONVERT_H

#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Converts normal strings to 
     * wide characters for Windows systems.
     * 
     * @param str The string to convert.
     * @return The wide character conversion.
     */
    inline LPCWSTR WideCharConvert ( String str )
    {
#ifndef UNICODE
        wchar_t* tmp = new wchar_t[ str.Length () ];
        for ( unsigned int i = 0; i < str.Length (); i++ )
        {
            tmp[ i ] = str.At ( i );
        }
        
        return tmp;
#elif
        return str.CString ();
#endif
    }

}

#endif

#endif
