/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowscodemodule.h
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

#ifndef VIBRANT_WINDOWSCODEMODULE_H
#define VIBRANT_WINDOWSCODEMODULE_H

#include "vcodemodule.h"

namespace Vibrant
{
    
    /**
     * @brief Implements code module functionality for Windows systems.
     * 
     * @author Chris Culy
     */
    class VAPI WindowsCodeModule : public CodeModule
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @see CodeModule#CodeModule(String)
             */
            WindowsCodeModule ( String module );

            /**
             * @see CodeModule#~CodeModule
             */
            ~WindowsCodeModule ();

            /**
             * @see CodeModule#IsLoaded()
             */
            bool IsLoaded ();

            /**
             * @see CodeModule#GetFunction(String)
             */
            void* GetFunction ( String function );
            
            //************************ General Interface ***********************//
    };

}

#endif

#endif
