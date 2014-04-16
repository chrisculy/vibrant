/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsexception.h
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

#ifndef VIBRANT_WINDOWSEXCEPTION_H
#define VIBRANT_WINDOWSEXCEPTION_H

#include "vexception.h"

namespace Vibrant
{
    
    /**
     * @brief Encapsulates exceptions specific to Windows systems.
     * 
     * @see Exception
     * @author Chris Culy
     */
    class VAPI WindowsException : public Exception
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @see Exception#Exception(String)
             */
            WindowsException ( String message = "" ) :
                Exception ( message )
            {
                /* stub function */
            }
            
            //************************ General Interface ***********************//
    };

}

#endif

#endif
