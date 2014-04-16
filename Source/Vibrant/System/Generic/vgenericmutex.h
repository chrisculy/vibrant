/*
 * =======================================
 * =============== Vibrant ===============
 * =======================================
 *
 * 
 * File: vgenericmutex.h
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

#ifndef VIBRANT_GENERICMUTEX_H
#define VIBRANT_GENERICMUTEX_H

#include "vmutex.h"

namespace Vibrant
{
    
    /**
     * @brief Stub implementation of Mutex.
     * 
     * @author Chris Culy
     */
    class VAPI GenericMutex : public Mutex
    {
        public:
            
            /**
             * @see Mutex#Wait
             */
            void Wait ()
            {
                /* stub function */
            }
            
        protected:
            
            /**
             * @see Mutex#Lock
             */
            void Lock ()
            {
                /* stub function */
            }
            
            /**
             * @see Mutex#Unlock
             */
            void Unlock ()
            {
                /* stub function */
            }
    };

}

#endif
