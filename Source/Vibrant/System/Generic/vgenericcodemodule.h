/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgenericcodemodule.h
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

#ifdef SYSTEM_GENERIC

#ifndef VIBRANT_GENERICCODEMODULE_H
#define VIBRANT_GENERICCODEMODULE_H

#include "vcodemodule.h"

namespace Vibrant
{
    
    /**
     * @brief Implements code module functionality for the generic system.
     * 
     * @author Chris Culy
     */
    class VAPI GenericCodeModule : public CodeModule
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @see CodeModule#LoadModule(String)
             */
            CodeModuleHandle LoadModule ( String module )
            {
                /* stub function */
                return null;
            }
            
            /**
             * @see CodeModule#GetFunction(String)
             */
            void* GetFunction ( CodeModuleHandle moduleHandle, String function )
            {
                /* stub function */
                return null;
            }
            
            /**
             * @see CodeModule#ReleaseModule(String)
             */
            void ReleaseModule ( CodeModuleHandle moduleHandle )
            {
                /* stub function */
            }
            
            //************************ General Interface ***********************//
    };

}

#endif

#endif
