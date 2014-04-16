/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vwindowsmutex.h
 * 
 * 
 * --  Copyright (c) 2007-2008 Alterr.  --
 * ---------------------------------------
 * 
 * Last changed:
 * $Revision: 130 $
 * $Author: Chris $
 * $Date: 2008-01-16 22:31:42 -0500 (Wed, 16 Jan 2008) $
 */

#include "vsystem.h"

#ifdef SYSTEM_WINDOWS

#ifndef VIBRANT_WINDOWSMUTEX_H
#define VIBRANT_WINDOWSMUTEX_H

#include "vmutex.h"
#include "vstring.h"

namespace Vibrant
{
    
    /**
     * @brief Implements mutexes for Windows systems.
     * 
     * @see Mutex
     * @author Chris Culy
     */
    class VAPI WindowsMutex : public Mutex
    {
        public:
            
            //************************ General Interface ***********************//

            /**
             * @brief Constructor.
             */
            WindowsMutex ();

            /**
             * @brief Destructor.
             */
            ~WindowsMutex ();

            /**
             * @see Mutex#Wait()
             */
            void Wait ();

            //************************ General Interface ***********************//

        protected:
            
            //************************ General Interface ***********************//

            /**
             * @see Mutex#Lock()
             */
            void Lock ();

            /**
             * @see Mutex#Unlock()
             */
            void Unlock ();

            /**
             * @brief Retrieves the next available mutex name.
             * 
             * @return The next mutex name.
             */
            String GetNextName ();

            //************************ General Interface ***********************//

        private:
            
            /** @brief Holds the mutex's handle. */
            HANDLE handle;

            /** @brief Holds the mutex's name. */
            String name;
    };

}

#endif

#endif
