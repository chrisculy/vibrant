/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vcodemodule.h
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

#ifndef VIBRANT_CODEMODULE_H
#define VIBRANT_CODEMODULE_H

#include "vstring.h"
#include "vsystem.h"

namespace Vibrant
{
    
    /**
     * @brief Provides an interface to system independent code module loading.
     * 
     * @author Chris Culy
     */
    class VAPI CodeModule
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Loads the given module.
             * 
             * @param module The module name.
             * @return The handle of the module or <code>null</code>
             *      if the module could not be loaded.
             */
            CodeModule ( String module );

            /**
             * @brief Releases (unloads) the given module.
             */
            virtual ~CodeModule ();

            /**
             * @brief Retrieves whether the module is properly loaded.
             * 
             * @return <code>true</code> if the module loaded successfully;
             *      <code>false</code> otherwise.
             */
            virtual bool IsLoaded () = 0;

            /**
             * @brief Gets a pointer to the given function from the given module.
             * 
             * @param function The function name.
             * @return The function pointer or <code>null</code> if the
             *      function could not be loaded (this can occur if the module does not load properly.
             */
            virtual void* GetFunction ( String function ) = 0;

            //************************ General Interface ***********************//

        protected:
            
            /** @brief The system dependent handle of the code module. */
            CodeModuleHandle moduleHandle;
    };

}

#endif
